#if defined _WIN32
#include <windows.h>	/* ::CreateDirectory(-) */
#include "osapi_mkdir.h"
namespace osapi {
bool mkdir(const std::TSTRING& dir_path)
{
	/* Kernel32.lib のリンク必要 */
	if (::CreateDirectory( dir_path.c_str() ,nullptr ) == 0) {
		// ::GetLastError()
		return false;
	}

	return true;
}
} // namespace osapi

#else // unix
#include <sys/stat.h>	/* ::mkdir(-) */
#include <sys/types.h>	/* ::mkdir(-) */
#include "osapi_mkdir.h"
namespace osapi {
bool mkdir(const std::string& dir_path)
{
	if (::mkdir(dir_path.c_str(), 0777) != 0) {
		// errno
		return false;
	}
	return true;
}
} // namespace osapi
#endif

#ifdef DEBUG_OSAPI_MKDIR
#ifdef _WIN32
#include <tchar.h>	/* _T("")  注意:/DUNICODEの場合/D_UNICODE必須 */
#endif
#include <iostream>
#include "osapi_mbs_wcs.cpp"
int main(int argc ,const char* argv[])
{
	if (argc != 2) {
		std::cout << argv[0] << " dir_path\n";
		return 1;
	}
// try {
	osapi::init_locale_to_jp();
#ifdef UNICODE
	std::TSTRING dir_path(osapi::wcs_from_mbs(argv[1]));
#else
	std::string dir_path(argv[1]);
#endif

	osapi::mkdir( dir_path );

#ifdef _WIN32
	std::TCOUT <<_T("mkdir=\"") << dir_path <<_T("\"\n");
#else
	std::cout << "mkdir=\"" <<  dir_path << "\"\n";
#endif

// }
// catch (std::exception& e) { std::cerr << e.what(); return 1; }
// catch (...) { std::cerr << "other exception\n"; return 2; } 
	return 0;
}
#endif
/*
rem :69,71 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /D_UNICODE /DDEBUG_OSAPI_MKDIR osapi_mkdir.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8                      /DDEBUG_OSAPI_MKDIR osapi_mkdir.cpp /Fea_u08
del osapi_mkdir.obj
# :74,74 w! make.sh
#!/bin/bash -x
g++ -Wall -std=c++11 osapi_mkdir.cpp -DDEBUG_OSAPI_MKDIR
*/
