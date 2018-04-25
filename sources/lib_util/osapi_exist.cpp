#if defined _WIN32 // win32 or win64

#include <shlwapi.h> // PathFileExists() ,Need shlwapi.lib
#include "osapi_mbs_wcs.h"
#include "osapi_exist.h"
namespace {
const bool osapi_exist_(LPCTSTR path ,DWORD& error_no) {
	if (::PathFileExists(path)==FALSE) {/* FileあるいはDirectory存在 */
		error_no = ::GetLastError(); /* エラーコードセット */
		return false;
	}
	return true; /* FileあるいはDirectoryである */
}
} // namespace
namespace osapi {
const bool exist(const std::TSTRING& path) {
	DWORD error_no = NO_ERROR;
	bool sw = osapi_exist_( path.c_str() ,error_no );
/* throw std::runtime_error(osapi_log_with_msg_and_id(path,error_no));
懸案事項：エラーなのか、存在しないのかの判断は今度検討する
trueの場合、
	"\"はカレントドライブのルートを示す、Unixの"/"のようなもの
	"..." ,"...."は"."を示しているらしい、いいのか？
falseの場合、
	error_noに以下のような(存在しない)理由がある
	ERROR_FILE_NOT_FOUND 2 指定されたファイルが見つかりません。
	"C:\users\NOT_EXIST_file.txt"
	ERROR_PATH_NOT_FOUND 3 指定されたパスが見つかりません。
	"C:\NOT_EXIST_users\file.txt"
	"NOT_EXIST_DRIVE:\users\file.txt"
	ERROR_BAD_NETPATH 53 ネットワーク パスが見つかりません。
	"\\NOT_EXIST_netpath\netname"
	ERROR_BAD_NET_NAME 67 ネットワーク名が見つかりません。"
	"\\netpath\NOT_EXIST_netname"
	ERROR_ACCESS_DENIED 5 アクセスが拒否されました。
	"C:\users\NOT_OWNER_folder\"
	ERROR_BAD_PATHNAME 161 :指定されたパスは無効です。
	"\\EXIST_netpath\"
	ERROR_INVALID_NAME 123 ファイル名、ディレクトリ名、またはボリューム ラベルの構文が間違っています。
	"\\"
	他...
*/
	return sw;
}
} // namespace osapi

#else // unix

#include <sys/stat.h>	// stat()
#include <cstring>	// ::memset()
#include <cerrno>	// errno
#include "osapi_exist.h"
namespace {
const bool osapi_exist_(const char* path,int& error_no,struct stat& t_stat){
	if (::stat(path ,&t_stat) != 0) {
		error_no = errno; /* エラーコードセット */
		return false; /* FileもDirectoryも存在しないかエラー */
	}
	return ( S_ISREG(t_stat.st_mode) || S_ISDIR(t_stat.st_mode)
	)? true: false; /* FileあるいはDirectoryであるならtrueを返す */
}
} // namespace
namespace osapi {
const bool exist(const std::string& path) {
	int error_no = 0;
	struct stat t_stat; ::memset(&t_stat,0,sizeof(t_stat));
	bool sw = osapi_exist_( path.c_str() ,error_no ,t_stat );
/* throw std::runtime_error(osapi_log_with_msg_and_id(path,error_no));
懸案事項：エラーなのか、存在しないのかの判断は今度検討する
falseの場合、
	error_noが0でない場合は存在しない理由としてコードがある
	error_noが0である場合はFileでもDirectoryでもない
		t_stat.st_modeフィールドのビットをチェックする
			ソケット
			シンボリックリンク
			ブロックデバイス
			キャラクターデバイス
			FIFO
*/
	return sw;
}
} // namespace osapi

#endif

namespace osapi {
const bool exist_utf8_mbs(const std::string& path) {
#ifdef WIN32
	/* utf8で受け取りcp932に変換してwin32関数に渡す */
	std::string cp932( osapi::cp932_from_utf8(path) );
# ifdef UNICODE
	std::TSTRING str(osapi::wcs_from_mbs(cp932));
# else
	std::string str(cp932);
# endif
#else
	std::string str(path);
#endif
	return osapi::exist(str);
}
} // namespace osapi

#if defined DEBUG_OSAPI_EXIST
#include <iostream>
#include "osapi_mbs_wcs.cpp"
int main( int argc, char *argv[] )
{
	if (argc != 2) {
		std::cout << "Usage : " << argv[0] << " file_or_directory"
			<< "\n";
		return 1;
	}
 try {
	if ( osapi::exist_utf8_mbs( osapi::utf8_from_cp932( argv[1] ) ) ) {
		std::cout << argv[1] << " is Exist as file or directory\n";
	} else {
		std::cout << argv[1] << " is Not exist as file or directory\n";
	}
 }
 catch (std::exception& e) {std::cerr<<"exception=\""<<e.what()<<"\"\n"; }
 catch (...) { std::cerr << "other exception\n"; }
	return 0;
}
#endif  /* !DEBUG_OSAPI_EXIST */
/*
rem :128,130 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /D_UNICODE /DDEBUG_OSAPI_EXIST osapi_exist.cpp shlwapi.lib /Fea_u16
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8                      /DDEBUG_OSAPI_EXIST osapi_exist.cpp shlwapi.lib /Fea_u08
del osapi_exist.obj
# :133,133 w! make.sh
#!/bin/bash -x
g++ -Wall -std=c++11 osapi_exist.cpp -DDEBUG_OSAPI_EXIST
*/
