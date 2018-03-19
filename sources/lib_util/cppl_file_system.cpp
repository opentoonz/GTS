#include "cppl_file_system.h"

namespace cppl {

std::vector<std::string> get_directory_list( const cppl::file_system_path& pa )
{
	std::vector<std::string> vecstr;
	for (	cppl::file_system::directory_iterator it(pa);
	it !=	cppl::file_system::directory_iterator() ;++it) {
		cppl::file_system_path tgt = *it;
		vecstr.push_back( tgt.string() );
	}
	return vecstr; /* NRVO(Named Return Value Optimization)必要 */
}

} // cppl

#ifdef DEBUG_CPPL_FILE_SYSTEM

#include <iostream>
#include "cppl_file_system_path.cpp"

#ifdef _WIN32
#include "osapi_mbs_wcs.cpp"
#endif

namespace {

int check_file_or_dir_( const cppl::file_system_path& path )
{
	/* 注：OS Nativeな文字コードに変換してから利用する */
#ifdef _WIN32
 const cppl::file_system_path pa(osapi::cp932_from_utf8(path.string()));
#else
	const cppl::file_system_path pa(path);
#endif

	/* ファイルあるいはフォルダーの存在の有無 */
	if (cppl::file_system::exists(pa) == false) {
		std::cout << "\"" << pa << "\" is Not exists\n";
	}

	/* 存在するならフォルダーか */
	else if (cppl::file_system::is_directory(pa)) {
		std::cout << "\"" << pa << "\" is Folder\n";

		/* フォルダーのリストを表示する */
		std::vector<std::string> vstr(cppl::get_directory_list(pa));
		for (unsigned ii=0; ii < vstr.size() ;++ii) {
			std::cout << ii+1 << "/" << vstr.size()
				<< "\t\"" << vstr.at(ii) << "\"\n";
		}
	}
	/* 存在するがフォルダーでない、ファイル？ */
	else {
		std::cout << "\"" << pa << "\" is File("
			<< cppl::file_system::file_size(pa) << "bytes)\n";
	}
	return 0;
}
int mkdir_( const cppl::file_system_path& path )
{
	/* 注：OS Nativeな文字コードに変換してから利用する */
#ifdef _WIN32
 const cppl::file_system_path pa(osapi::cp932_from_utf8(path.string()));
#else
	const cppl::file_system_path pa(path);
#endif

	//if (cppl::file_system::create_directory( pa ) == false ) {
	std::string pa_str( pa.string() );
	if (cppl::file_system::create_directory(
	cppl::file_system_path( pa_str.c_str() ) ) == false ) {
		std::cerr << "Can not mkdir \"" << pa << "\"\n";
		return 1;
	}
		std::cout << "mkdir \"" << pa << "\"\n";
	return 0;
}
int rename_(
	const cppl::file_system_path& path1
	, const cppl::file_system_path& path2
)
{
	/* 注：OS Nativeな文字コードに変換してから利用する */
#ifdef _WIN32
 const cppl::file_system_path pa1(osapi::cp932_from_utf8(path1.string()));
 const cppl::file_system_path pa2(osapi::cp932_from_utf8(path2.string()));
#else
	const cppl::file_system_path pa1(path1);
	const cppl::file_system_path pa2(path2);
#endif

	/* 注：rename()はエラーハンドリングが違う。
		Windowsは戻り値
		Unixは例外を投げる
	*/
#ifdef _WIN32
	if (cppl::file_system::rename( pa1 , pa2 ) == false ) {
		std::cerr << "Can not rename \"" << pa1
					<< "\" \"" << pa2 << "\"\n";
		return 1;
	}
#else
try {
	cppl::file_system::rename( pa1 , pa2 );
}
/*catch (std::filesystem_error& e) {
		std::cerr << "Can not rename \"" << e.path1()
					<< "\" \"" << e.path2() << "\"\n";
		std::cerr << e.what() << std::endl;
		return 1;
}*/
catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
}
#endif
		std::cout << "rename \"" << pa1 << "\" \"" << pa2 << "\"\n";
	return 0;
}
void usage_( const std::string& comm )
{
	std::cout << comm
		<< " filepath/folderpath/-md folderpath/-rn filename\n";
}

} // namespace

/*
引数例:
"C:\\users\\tmp.0001.txt"
"../..//users///tmp.0001.txt"
"C://users///tmp.0001.txt"
"C:\\users"	"/home"
"C:\\users/"	"/home/"
"C:\\users\\tmp.0001.txt"	"/home/tmp.0001.txt"
"C:/Users/masafumi_inoue/Desktop/一時的フォルダ→すぐ削除する"
*/
int main(int argc ,const char* argv[])
{
	if (argc == 1) {
		usage_(argv[0]);
		return 0;
	}
	else if (argc == 2) {
		/* 注：パスはutf8で格納する */
#ifdef _WIN32
		cppl::file_system_path pa(osapi::utf8_from_cp932(argv[1]));
#else
		cppl::file_system_path pa(argv[1]);
#endif
		return check_file_or_dir_( pa );
	}
	else if (argc == 3 && std::string("-md") == argv[1]) {
		/* 注：パスはutf8で格納する */
#ifdef _WIN32
		cppl::file_system_path pa(osapi::utf8_from_cp932(argv[2]));
#else
		cppl::file_system_path pa(argv[2]);
#endif
		return mkdir_( pa );
	}
	else if (argc == 4 && std::string("-rn") == argv[1]) {
		/* 注：パスはutf8で格納する */
#ifdef _WIN32
		cppl::file_system_path pa1(osapi::utf8_from_cp932(argv[2]));
		cppl::file_system_path pa2(osapi::utf8_from_cp932(argv[3]));
#else
		cppl::file_system_path pa1(argv[2]);
		cppl::file_system_path pa2(argv[3]);
#endif
		return rename_( pa1 , pa2 );
	}

	std::cerr << "Error:Bad argument.\n";
	return 1;
}
#endif /* !DEBUG_CPPL_FILE_SYSTEM */
/*
rem :181,183 w! make.bat
cl /W4 /WX /MD /EHa /O2 /wd4819 /DDEBUG_CPPL_FILE_SYSTEM cppl_file_system.cpp /Fea_u08
cl /W4 /WX /MD /EHa /O2 /wd4819 /DUNICODE /DDEBUG_CPPL_FILE_SYSTEM cppl_file_system.cpp /Fea_u16
del cppl_file_system.obj
# :168,168 w! make.sh
g++ -Wall -DDEBUG_CPPL_FILE_SYSTEM -std=c++11 cppl_file_system.cpp -lstdc++fs
*/
