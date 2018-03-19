#include "cppl_file_system_path.h"

#ifdef DEBUG_CPPL_FILE_SYSTEM_PATH
#ifdef _WIN32
#include <io.h> /* _isatty(-) */
#else
#include <iostream>
#endif
#include "osapi_mbs_wcs.cpp"

#ifdef _WIN32
/*
コマンド・プロンプトへの文字列出力がUTF-8であると仮定して、Shift-JISへ変換して出力するようにoperator<<(std::ostream&, …)をオーバーロードする
*/
inline std::ostream& operator<<(std::ostream& iOStream, const std::string& iString)
{
	if (((&iOStream == &std::cout) && (_isatty(_fileno(stdout))))
	||  ((&iOStream == &std::cerr) && (_isatty(_fileno(stderr))))
	) {
		std::operator<<(iOStream, osapi::cp932_from_utf8(iString));
	
	}
	else {
		std::operator<<(iOStream, iString.c_str());
	}
	return iOStream;
}
#endif

namespace {
void path_info_print_( const cppl::file_system_path& pa )
{
	std::string orig_path( pa.string() );
	std::string root_name( pa.root_name() );
	std::string extension( pa.extension() );
	std::string root_dire( pa.root_directory() );
	std::string file_name( pa.filename() );
	std::string stem_name( pa.stem() );
std::cout << "            Path=\"" << orig_path << "\"\n";
std::cout << "     root_name()=\"" << root_name << "\"\n";
std::cout << "root_directory()=\"" << root_dire << "\"\n";
std::cout << "     root_path()=\"" << pa.root_path().string() << "\"\n";
std::cout << " relative_path()=\"" << pa.relative_path().string() << "\"\n";
std::cout << "   parent_path()=\"" << pa.parent_path().string() << "\"\n";
std::cout << "      filename()=\"" << file_name << "\"\n";
std::cout << "          stem()=\"" << stem_name << "\"\n";
std::cout << "     extension()=\"" << extension << "\"\n";
}
void str_( const std::string& str) {std::cout << "m " << str << std::endl;}
void wstr_(const std::wstring&wstr){std::wcout<< L"w " <<wstr << std::endl;}
} // namespace

/*
引数例:
"C:\\users\\tmp.0001.txt"
"../..//users///tmp.0001.txt"
"C://users///tmp.0001.txt"
"C:\\users"	"/home"
"C:\\users/"	"/home/"
"C:\\users\\tmp.0001.txt"	"/home/tmp.0001.txt"
"C:/Users/public/一時フォルダ/サブフォルダ/ファイル.0001.tga"
*/
int main(int argc ,const char* argv[])
{
	/* utf8でファイル保存する */
	std::string filepath( "C:/Users/public/一時フォルダ表/ファイル.0001.tga");
	std::string filename( "表ファイル.0001.tif" );

	if (2 <= argc) {
		filepath = argv[1];
#ifdef _WIN32
		/* argvはcp932で来る */
		filepath = osapi::utf8_from_cp932( argv[1] );
#endif
	}
	osapi::init_locale_to_jp();	/* for std::wcout */

	/* 初期化 & win/unix共通利用関数テスト */
	cppl::file_system_path pa( filepath );
	std::cout << "----------- initial test\n";
	path_info_print_(pa);

	/* パス結合のテスト */
	std::cout << "----------- set & connect test\n";
	cppl::file_system_path pa2;

	pa2 = pa.parent_path();
	std::cout << "     folder=\"" << pa2.string() << "\"\n";

	pa2 /= filename;
	std::cout << "   filepath=\"" << pa2.string() << "\"\n";

	path_info_print_(pa2);

	/* path オブジェクトは std::wstring または std::string に暗黙的に変換できます by vc2015
	*/
	str_( pa2 );
	wstr_( osapi::wcs_from_mbs( pa2 ) ); // vc2013

        return 0;
}
#endif /* !DEBUG_CPPL_FILE_SYSTEM_PATH */
/*
rem :105,107 w! make.bat
cl /W4 /WX /MD /EHa /O2 /wd4819 /DUNICODE /DDEBUG_CPPL_FILE_SYSTEM_PATH cppl_file_system_path.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /wd4819 /DDEBUG_CPPL_FILE_SYSTEM_PATH cppl_file_system_path.cpp /Fea_u08
del cppl_file_system_path.obj
# :109,109 w! make.sh
g++ -Wall -DDEBUG_CPPL_FILE_SYSTEM_PATH -std=c++11 cppl_file_system_path.cpp -lstdc++fs
*/
