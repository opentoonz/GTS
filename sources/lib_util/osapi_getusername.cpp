#if defined _WIN32
#include <windows.h>	/* ::GetUserName(-) */
#include <Lmcons.h>	/* UNLEN */
#include "osapi_getusername.h"
namespace osapi {
std::TSTRING getusername( void )
{
	TCHAR buf[UNLEN + 1] = {};
	DWORD len = UNLEN + 1;

	/* Advapi32.lib のリンク必要 */
	if (::GetUserName( buf ,&len ) == 0) {
		// ::GetLastError()
		return std::TSTRING();
	}

	return std::TSTRING(buf);
}
} // namespace osapi

#else // unix
#include <sys/types.h> /* getuid(),getpwuid() */
#include <unistd.h>    /* getuid() */
#include <pwd.h>       /* getpwuid() */
#include "osapi_getusername.h"
namespace osapi {
std::string getusername( void )
{
	/* getlogin()はlogin時のユーザー名の文字列へのポインタを返す */
	struct passwd *tp_pw;
	tp_pw = ::getpwuid( ::getuid() );
	if (NULL == tp_pw) {
		// errno
		return std::string();
	}
	return std::string(tp_pw->pw_name);
}
} // namespace osapi
#endif

#ifdef DEBUG_OSAPI_GETUSERNAME
#ifdef _WIN32
#include <tchar.h>	/* _T("")  注意:/DUNICODEの場合/D_UNICODE必須 */
#endif
#include <iostream>
#include "osapi_mbs_wcs.cpp"
int main(void)
{
// try {
	osapi::init_locale_to_jp();
#ifdef _WIN32
	std::TCOUT <<_T("username=\"") <<osapi::getusername() <<_T("\"\n");
#else
	std::cout << "username=\"" << osapi::getusername() << "\"\n";
#endif

// }
// catch (std::exception& e) { std::cerr << e.what(); return 1; }
// catch (...) { std::cerr << "other exception\n"; return 2; } 
	return 0;
}
#endif
/*
rem :64,66 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /D_UNICODE /DDEBUG_OSAPI_GETUSERNAME osapi_getusername.cpp /Fea_u16 advapi32.lib
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8                      /DDEBUG_OSAPI_GETUSERNAME osapi_getusername.cpp /Fea_u08 advapi32.lib
del osapi_getusername.obj
# :69,69 w! make.sh
#!/bin/bash -x
g++ -Wall -std=c++11 osapi_getusername.cpp -DDEBUG_OSAPI_GETUSERNAME
*/
