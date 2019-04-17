#if defined _WIN32
# include <windows.h>
# include "osapi_mbs_wcs_win.h"		/* osapi::wcs_from_mbs(-) */
# include "osapi_log_with_msg_and_id.h" /* osapi_log_with_msg_and_id(-) */
#else
# include <dlfcn.h>	/* dlopen(),dlerror(),dlsym(),dlclose() */
#endif
#include <stdexcept>	/* std::runtime_error */
#include "image_common_plugin.h"

using image::common::plugin;

plugin::~plugin()
{ try { this->close(); } catch(...) {} } /* destractorの例外を無効化 */

namespace {
 void *get_instance_(
#if defined _WIN32
	HMODULE handle
#else /* unix */
	void* handle
#endif /* !_WIN32 */
	,const char* func_name
 ) {
	void *(*func)(void);
#if defined _WIN32
	/* 関数シンボルへのアドレスを返す
		FARPROC GetProcAddress(
		 HMODULE hModule	// DLL モジュールのハンドル
		 ,LPCSTR lpProcName	// 関数名
		);
		typedef const char* LPCSTR;
	*/
	*(void **)(&func) = ::GetProcAddress( handle ,func_name );
#else /* unix */
	*(void **)(&func) = ::dlsym( handle ,func_name );
#endif /* !_WIN32 */
	void* instance_ptr = nullptr;
	if ( func != nullptr ) {
		/* 関数が返す値がプラグインの本体(のアドレス) */
		instance_ptr = func();
	}
	return instance_ptr;
 }
}
void plugin::add( const std::string& utf8_file_path ) {
#if defined _WIN32
# ifdef UNICODE
/* https://ja.wikipedia.org/wiki/UTF-16 より
"Windowsでは、リトルエンディアンのUTF-16符号化スキームが使われている" */
/* utf8 --> utf-16le */
	std::wstring win_file_path( osapi::wcs_from_mbs(utf8_file_path) );
# else
/* utf8 --> cp932 */
	std::string win_file_path( osapi::cp932_from_utf8(utf8_file_path) );
# endif /* !UNICODE */

	/* .dllファイルをロードしハンドルを返す */
	HMODULE handle = ::LoadLibrary( win_file_path.c_str() );
	if (    handle == nullptr ) {
		throw std::runtime_error( osapi_log_with_msg_and_id(
			win_file_path , ::GetLastError()
		) );
	}
#else /* unix */
	/* .soファイルをロードしハンドルを返す */
	void* handle = ::dlopen( utf8_file_path.c_str() ,RTLD_LAZY );
	if ( *handle == nullptr ) {
		throw std::runtime_error( osapi_log_with_msg_and_id(
			utf8_file_path , ::dlerror()
		) );
	}
#endif /* !_WIN32 */
	/* 保持 */
	this->utf8_file_paths_.push_back( utf8_file_path );
	this->module_handles_.push_back( handle );

	//-------------------------------------
	void* r_instance = get_instance_( handle ,this->func_name_reader_ );
	void* w_instance = get_instance_( handle ,this->func_name_writer_ );

	/* 保持 */
	if ( r_instance != nullptr ) {
		this->r_instance_handles_.push_back( r_instance );
	}
	if ( w_instance != nullptr ) {
		this->w_instance_handles_.push_back( w_instance );
	}
}

size_t plugin::get_r_instance_size(void) {
	return this->r_instance_handles_.size();
}
void*  plugin::get_r_instance(size_t count) {
	return this->r_instance_handles_.at(count);
}
size_t plugin::get_w_instance_size(void) {
	return this->w_instance_handles_.size();
}
void*  plugin::get_w_instance(size_t count) {
	return this->w_instance_handles_.at(count);
}

void plugin::close( void ) {
	this->w_instance_handles_.clear();
	this->r_instance_handles_.clear();
	for (
#if defined _WIN32
	std::vector<HMODULE>::iterator
#else /* unix */
	std::vector<void *>::iterator
#endif /* !_WIN32 */
	  it =  this->module_handles_.begin()
	; it != this->module_handles_.end() ;++it) {
		if (*it != nullptr) {
#if defined _WIN32
			::FreeLibrary( *it );
#else /* unix */
			::dlclose( *it );
#endif /* !_WIN32 */
			*it = nullptr;
		}
	}
	this->module_handles_.clear();
	this->utf8_file_paths_.clear();
}

#if defined DEBUG_IMAGE_COMMON_PLUGIN_R //--------------------------------
#include <iostream>			/* std::cerr */
#include <fstream>			/* std::ofstream */
#include "image_common.h"		/* image::common::reader */
#include "osapi_mbs_wcs_win.cpp"	/* osapi::wcs_from_mbs(-) */
#include "osapi_log_with_msg_and_id.cpp"/* osapi_log_with_msg_and_id(-) */
#include "osapi_str_from_errid.cpp"	/* osapi_log_with_msg_and_id(-) */
namespace {
bool r_action_(
	const std::string& fpath
	, image::common::reader& rdr
	, image::common::properties& props
	, std::vector<uint8_t>& image
	, size_t& image_bytes
	, std::string& history_str
	, size_t& history_bytes
) {
 try {
	std::cout << "format_name=" << rdr.format_name() << std::endl;
	for (size_t ii=0 ;ii < rdr.ext_count() ;++ii) {
	 //const char *const *const lists = this->ext_name_lists();
	 //std::cout << "ext_name=" << lists[ii] << std::endl;
	 std::cout << ii << " ext_name=" << rdr.ext_name(ii) << std::endl;
	}

	if (fpath.empty()) {
		return true;
	}

	std::string line_info;
	rdr.get_info( fpath , line_info );
	std::cout << "get_info=" << line_info;

	rdr.get_size( fpath ,image_bytes ,history_bytes );
	std::cout << "get_size image_bytes=" << image_bytes
		<< " history_bytes=" << history_bytes
		<< std::endl;

	image.resize(image_bytes);

	static bool break_sw=false;
	rdr.get_data( fpath , props
	, image_bytes , image.data() , history_str
	, break_sw /* 中断Switch。外からtureで中断 */
	, 0 /* 分割読込の個々サイズ(tif以外で使用する) */
	);
	return false;
 }
 catch (std::exception& e) {
/* vc2017 x86 .dll使う場合、例外を中継ぎしないとcatchできず落ちてしまう
   原因不明!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	throw std::runtime_error( e.what() );
 }
}
void w_action_(
	const image::common::properties& props
	, const std::vector<uint8_t>& image
	, const size_t& image_bytes
	, const std::string& history_str
	, const size_t& history_bytes
	, image::common::writer& wtr
	, const std::string& fpath
) {
 try {
	history_bytes;
//	std::ofstream ofs( "tmp.raw" ,std::ios_base::binary );
//	ofs.write( (char *)(image.data()) ,image.size() );
//	ofs.close();

	std::ostringstream error_or_warning_msg;

	const bool w_chk = wtr.error_from_properties(
		props
		, 0
		, error_or_warning_msg
	);
	if (w_chk) {
		std::cerr << error_or_warning_msg.str();
		return;
	}
	wtr.put_data(
		props
		, image_bytes
		, image.data()
		, 0
		, history_str
		, fpath
	);
 }
 catch (std::exception& e) {
/* vc2017 x86 .dll使う場合、例外を中継ぎしないとcatchできず落ちてしまう
   原因不明!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	throw std::runtime_error( e.what() );
 }
}
}

int main( int argc ,char *argv[] )
{
 try {
	if (argc < 2) {
		std::cout << "Usage : " << argv[0]
		<< " [-in in.tif] [-out out.tif] plugin(.dll/.so) ...\n";
		return 1;
	}

	std::string in_path;
	std::string out_path;

	image::common::plugin	i_c_plugin;
	for (int ii=1 ; ii < argc ;++ii) {
		if (std::string("-in") == argv[ii]) {
			in_path = argv[++ii];
			continue;
		}
		if (std::string("-out") == argv[ii]) {
			out_path = argv[++ii];
			continue;
		}
#if defined _WIN32
		std::string file_path( osapi::utf8_from_cp932( argv[ii] ) );
#else
		std::string file_path( argv[ii] );
#endif
		i_c_plugin.add( file_path );
	}
	if (in_path.empty()) {
		std::cout << "Error : Need '-in in.tif'" << std::endl;
		return 2;
	}
	if (out_path.empty()) {
		std::cout << "Error : Need '-out out.tif'" << std::endl;
		return 3;
	}
	std::cout << "iin=" << in_path << std::endl;
	std::cout << "out=" << out_path << std::endl;

	/* Image Proparty & history */
	image::common::properties props;
	std::vector<uint8_t> image;
	size_t image_bytes=0;
	std::string history_str;
	size_t history_bytes=0;

	/* Image Reader */
	std::cout << "r_action" << std::endl;
	for (size_t ii = 0; ii < i_c_plugin.get_r_instance_size() ;++ii) {
		if (r_action_(
			in_path
			, *static_cast<image::common::reader *>(
				i_c_plugin.get_r_instance( ii )
			)
			, props
			, image
			, image_bytes
			, history_str
			, history_bytes
		)) {
			return 4;
		}
	}

	/* 画像バッファ確保 */
	std::cout << "image.resize=" << image_bytes << std::endl;
	//image.resize(image_bytes);

	/* Image Writer */
	std::cout << "w_action" << std::endl;
	for (size_t ii = 0; ii < i_c_plugin.get_w_instance_size() ;++ii) {
	  image::common::writer *wtr_ptr =
		static_cast<image::common::writer *>(
			i_c_plugin.get_w_instance( ii ) );
	  std::cout << "format_name=\""
	  	<< wtr_ptr->format_name() << "\"\n";
	  for (unsigned jj = 0; jj < wtr_ptr->ext_count(); ++jj) {
	  	std::cout
			<< "ext=\""
			<< wtr_ptr->ext_name( jj )
			<< "\"\n";
	  }
	  w_action_(
		props
		, image
		, image_bytes
		, history_str
		, history_bytes
		, *wtr_ptr
		, out_path );
	}

	i_c_plugin.close();
 }
 catch (std::exception& e) {
	std::cerr << "exception=<" << e.what() << ">" << std::endl;
 }
 catch (...) {
	std::cerr << "other exception" << std::endl;
 }
	return 0;
}
#endif  /* !DEBUG_IMAGE_COMMON_PLUGIN_R */
/*
rem make .exe
rem /DUNICODE /D_UNICODE
rem UNICODEがWindows SDK用，_UNICODEがCRT用です。
rem TEXTマクロはWindowsSDKの領域で，UNICODEの定義の有無で動作が変化します
rem 同様に，_TマクロはCRTの領域で，_UNICODEの定義の有無で動作が変化します
rem ついでに，TCHARはWindows SDKとCRTの両方で定義されて複雑な変化をします
rem :323,324 w! make.bat
rem cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_IMAGE_COMMON_PLUGIN_R /I. /I../../../sources/lib_util /I../../thirdparty/libtiff/tiff-4.0.9/libtiff image_common_plugin.cpp ../../thirdparty/libtiff/tiff-4.0.9/libtiff/libtiff.lib /Fea
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_IMAGE_COMMON_PLUGIN_R /I. /I../../../sources/lib_util image_common_plugin.cpp /Fea
del image_common_plugin.obj
# :674,675 w! make.sh
#g++ -Wall -std=c++11 -DDEBUG_IMAGE_COMMON_PLUGIN_R -I. image_common_plugin.cpp -ltiff
g++ -Wall -std=c++11 -DDEBUG_IMAGE_COMMON_PLUGIN_R -I. image_common_plugin.cpp
*/
