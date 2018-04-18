#if defined _WIN32
#include <windows.h>	/* MAX_COMPUTERNAME_LENGTH , ::GetComputerName(-) */
#include "osapi_gethostname.h"
namespace osapi {
std::TSTRING gethostname( void )
{
	TCHAR buf[MAX_COMPUTERNAME_LENGTH + 1] = {};
	DWORD len = MAX_COMPUTERNAME_LENGTH + 1;

	/* Kernel32.lib のリンク必要 */
	if (::GetComputerName( buf ,&len ) == 0) {
		// ::GetLastError()
		return std::TSTRING();
	}

	return std::TSTRING(buf);
}
} // namespace osapi

#else // unix
#include <unistd.h>	/* ::gethostname(-) */
#include <cstring>	/* strchr() */
#ifndef  HOST_NAME_MAX
# define HOST_NAME_MAX 255
#endif
/* 注意  'man gethostname'より
	SUSv2では
		「ホスト名が255バイトに制限される」
	ことを保証している
	POSIX 1003.1-2001 では
		「ホスト名(終端のヌル文字は含まない)が
		HOST_NAME_MAXバイトに制限される」
	ことを保証している
*/
#include "osapi_gethostname.h"
namespace osapi {
std::string gethostname( void )
{
	char buf[HOST_NAME_MAX] = {};

	if (::gethostname(buf, HOST_NAME_MAX) != 0) {
		// errno
		return std::string();
	}
	else {
		char *cp_tmp;
		/* ドメイン名からホスト名に当る部分のみ切り出す */
		/* hostname.co.jp --> hostname */
		cp_tmp = strchr( buf, (int)'.' );
		if (NULL != cp_tmp) { cp_tmp[0] = '\0'; }
	}
	return std::string(buf);
}
} // namespace osapi
#endif

#ifdef DEBUG_OSAPI_GETHOSTNAME
#ifdef _WIN32
#include <tchar.h>	/* _T("")  注意:/DUNICODEの場合/D_UNICODE必須 */
#endif
#include <iostream>
#include "osapi_mbs_wcs.cpp"
int main(void)
{
// try { osapi::init_locale_to_jp();
#ifdef _WIN32
	std::TCOUT <<_T("hostname=\"") <<osapi::gethostname() <<_T("\"\n");
#else
	std::cout << "hostname=\"" << osapi::gethostname() << "\"\n";
#endif

// }
// catch (std::exception& e) { std::cerr << e.what(); return 1; }
// catch (...) { std::cerr << "other exception\n"; return 2; } 
	return 0;
}
#endif
/*
rem :80,82 w! make.bat
cl /W4 /WX /MD /EHa /O2 /wd4819 /DUNICODE /D_UNICODE /DDEBUG_OSAPI_GETHOSTNAME osapi_gethostname.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /wd4819 /DDEBUG_OSAPI_GETHOSTNAME osapi_gethostname.cpp /Fea_u08
del osapi_gethostname.obj
# :85,85 w! make.sh
#!/bin/bash -x
g++ -Wall -std=c++11 osapi_gethostname.cpp -DDEBUG_OSAPI_GETHOSTNAME
*/
