#ifdef _WIN32
#include <windows.h>	/* ::GetEnvironmentVariable(-) */
#include <tchar.h>	/* _T("")  注意:/DUNICODEの場合/D_UNICODE必須 */
#include <stdexcept>	/* std::length_error() */
#include "osapi_log_with_msg_and_id.h"	/* osapi_log_with_msg(-) */
#include "osapi_getenv.h"
namespace osapi {
std::TSTRING getenv(const std::TSTRING& name)
{
	TCHAR env_array[_MAX_ENV];
	DWORD length = ::GetEnvironmentVariable(
		name.c_str()	/* 環境変数の名前、NULLで終わる文字列 */
		,env_array	/* 変数の値が格納されるバッファ */
		,_MAX_ENV	/* バッファのサイズ */
	);
	/* バッファに格納された終端のNULL文字を除く文字の数を返す */

	/* 指定の環境変数の名前が見つからないとき0が返る */
	if (length == 0) {
		return std::TSTRING();
	}
	/* バッファのサイズが足りないとき、(=programming error)
	指定された環境変数の値を格納するために、
	必要なバッファの終端のNULL文字を含むサイズ、
	を返す */
	if (_MAX_ENV < length) {
		throw std::length_error( osapi_log_with_msg(
	_T("Buffer size is insufficient for GetEnvironmentVariable(-)")
		) );
	}

	return std::TSTRING( env_array );
}
} // namespace osapi

#else
#include <cstring>
#include <string>
#include <cstdlib>	/* secure_getenv(-) */
#include "osapi_getenv.h"
namespace osapi {
std::string getenv(const std::string& name)
{
	const char* env_array = ::secure_getenv(name.c_str());

	if (env_array == nullptr) {
	/* 安全な実行が必要な場合 or 対象の環境変数がない */
		return std::string();
	}
	if (strlen(env_array) <= 0) {
	/* 対象の環境変数がない */
		return std::string();
	}
	return std::string( env_array );
}
} // namespace osapi
#endif

#ifdef DEBUG_OSAPI_GETENV
#include <iostream>
#include "osapi_mbs_wcs.cpp"
#include "osapi_log_with_msg_and_id.cpp"
#include "osapi_str_from_errid.cpp"
int main(void)
{
try {
	osapi::init_locale_to_jp();

#ifdef _WIN32
	std::TCOUT <<	_T("homehrive      =\"") << osapi::getenv(
			_T("HOMEDRIVE"))	<< _T("\"\n");
	std::TCOUT <<	_T("homepath       =\"") << osapi::getenv(
			_T("HOMEPATH"))		<< _T("\"\n");
	std::TCOUT <<	_T("home           =\"") << osapi::getenv(
			_T("HOME"))		<< _T("\"\n");
	std::TCOUT <<	_T("allusersprofile=\"") << osapi::getenv(
			_T("ALLUSERSPROFILE"))	<< _T("\"\n");
	std::TCOUT <<	_T("public         =\"") << osapi::getenv(
			_T("PUBLIC"))		<< _T("\"\n");
	std::TCOUT <<	_T("hogehoge       =\"") << osapi::getenv(
			_T("HOGEHOGE"))		<< _T("\"\n");
#else
	std::cout <<	"homehrive      =\"" << osapi::getenv(
			"HOMEDRIVE")		<< "\"\n";
	std::cout <<	"homepath       =\"" << osapi::getenv(
			"HOMEPATH")		<< "\"\n";
	std::cout <<	"home           =\"" << osapi::getenv(
			"HOME")			<< "\"\n";
	std::cout <<	"allusersprofile=\"" << osapi::getenv(
			"ALLUSERSPROFILE")	<< "\"\n";
	std::cout <<	"public         =\"" << osapi::getenv(
			"PUBLIC")		<< "\"\n";
	std::cout <<	"hogehoge       =\"" << osapi::getenv(
			"HOGEHOGE")		<< "\"\n";
#endif

}
catch (std::exception& e) {
	std::cerr << e.what();
}
catch (...) {
	std::cerr << "other exception\n";
}

	return 0;
}
#endif
/*
rem :110,112 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /D_UNICODE /DDEBUG_OSAPI_GETENV osapi_getenv.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8                      /DDEBUG_OSAPI_GETENV osapi_getenv.cpp /Fea_u08
del osapi_getenv.obj
# :115,115 w! make.sh
#!/bin/bash -x
g++ -Wall -std=c++11 osapi_getenv.cpp -DDEBUG_OSAPI_GETENV
*/
