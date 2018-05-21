#include "cppl_file_system_path.h"

#ifdef DEBUG_CPPL_FILE_SYSTEM_PATH

#include <iostream>
#include "osapi_mbs_wcs.cpp"

namespace {
void path_info_print_( const cppl::file_system_path& pa )
{
std::cout << "----- OS Path format A:\tmp\tmp.0001.tif -----" << "\n";
std::cout << pa.string().size() << "            Path=\""
	  << pa.string() << "\"\n";
std::cout << pa.root_name().string().size() << "     root_name()=\""
	  << pa.root_name().string() << "\"\n";
std::cout << pa.root_directory().string().size() << "root_directory()=\""
	  << pa.root_directory().string() <<"\"\n";
std::cout << pa.root_path().string().size() << "     root_path()=\""
	  << pa.root_path().string() << "\"\n";
std::cout << pa.relative_path().string().size() << " relative_path()=\""
	  << pa.relative_path().string() << "\"\n";
std::cout << pa.parent_path().string().size() << "   parent_path()=\""
	  << pa.parent_path().string() << "\"\n";
std::cout << pa.filename().string().size() << "      filename()=\""
	  << pa.filename().string() << "\"\n";
std::cout << pa.stem().string().size() << "          stem()=\""
	  << pa.stem().string() << "\"\n";
std::cout << pa.extension().string().size() << "     extension()=\""
	  << pa.extension().string() << "\"\n";
std::cout << "----- general Path format A:/tmp/tmp.0001.tif -----" << "\n";
std::cout << pa.generic_string().size() << "            Path=\""
	  << pa.generic_string() << "\"\n";
std::cout << pa.root_name().generic_string().size() << "     root_name()=\""
	  << pa.root_name().generic_string() << "\"\n";
std::cout << pa.root_directory().generic_string().size() << "root_directory()=\""
	  << pa.root_directory().generic_string() <<"\"\n";
std::cout << pa.root_path().generic_string().size() << "     root_path()=\""
	  << pa.root_path().generic_string() << "\"\n";
std::cout << pa.relative_path().generic_string().size() << " relative_path()=\""
	  << pa.relative_path().generic_string() << "\"\n";
std::cout << pa.parent_path().generic_string().size() << "   parent_path()=\""
	  << pa.parent_path().generic_string() << "\"\n";
std::cout << pa.filename().generic_string().size() << "      filename()=\""
	  << pa.filename().generic_string() << "\"\n";
std::cout << pa.stem().generic_string().size() << "          stem()=\""
	  << pa.stem().generic_string() << "\"\n";
std::cout << pa.extension().generic_string().size() << "     extension()=\""
	  << pa.extension().generic_string() << "\"\n";
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
	osapi::init_locale_to_jp();	/* for std::wcout */

	/* utf8でファイル保存する */
	std::string filepath( "C:/Users/public/フォルダ表/ファイル.0001.tga");
	std::string filehead( "表ファイル.0001" );
	std::string fileexte( ".tif" );

	if (2 <= argc) {
		filepath = argv[1];
#ifdef _WIN32
		/* argvはcp932で来る */
		filepath = osapi::utf8_from_cp932( argv[1] );
#endif
	}

	/* 初期化 & win/unix共通利用関数テスト */
	cppl::file_system_path pa( filepath );
	std::cout << "----------- initial test\n";
	path_info_print_(pa);
/*
	cppl::file_system_pathから文字を取り出す".string()"では、
	cp932が返るらしい
*/

	/* パス結合のテスト */
	std::cout << "----------- set & connect test\n";
	cppl::file_system_path pa2( pa.parent_path() );
	cppl::file_system_path fh2( filehead );
	cppl::file_system_path fe2( fileexte );
	std::cout << "     folder=\"" << pa2.string() << "\"\n";
	std::cout << "   filehead=\"" << fh2.string() << "\"\n";
	std::cout << "   fileexte=\"" << fe2.string() << "\"\n";
	pa2 /= fh2;
	pa2 += fe2;
	std::cout << "cp932 filepath=\"" << pa2.string() << "\"\n";
	std::cout << "cp932<filepath=\"" << osapi::cp932_from_utf8( pa2.u8string() ) << "\"\n";
	std::cout << " utf8 filepath=\"" << pa2.u8string() << "\"\n";
	std::cout << " utf8<filepath=\"" << osapi::utf8_from_cp932( pa2.string() ) << "\"\n";

	path_info_print_(pa2);

	/* path オブジェクトは std::wstring または std::string に暗黙的に変換できます by vc2015
	*/
	str_( pa2.string() );
	wstr_( osapi::wcs_from_mbs( pa2.string() ) );

        return 0;
}
#endif /* !DEBUG_CPPL_FILE_SYSTEM_PATH */
/*
rem :120,122 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /DDEBUG_CPPL_FILE_SYSTEM_PATH cppl_file_system_path.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_CPPL_FILE_SYSTEM_PATH cppl_file_system_path.cpp /Fea_u08
del cppl_file_system_path.obj
# :124,124 w! make.sh
g++ -Wall -DDEBUG_CPPL_FILE_SYSTEM_PATH -std=c++11 cppl_file_system_path.cpp -lstdc++fs
*/
