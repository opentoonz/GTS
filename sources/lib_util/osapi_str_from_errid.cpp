#ifdef _WIN32 // win32 or win64
#include "osapi_str_from_errid_win.cpp"
#else
#include "osapi_str_from_errid_unix.cpp"
#endif

//-----------------------------------------------------------
#if defined DEBUG_RSRC_STR_FROM_ERRID
#include <iostream>	/* for unix */
#include "osapi_mbs_wcs.cpp"
int main(int argc , char *argv[])
{
	osapi::init_locale_to_jp();

 if (argc == 2) {
	const int num = std::stoi( argv[1] );
#ifdef _WIN32 // win32 or win64
	std::TSTRING msg( osapi::tstr_from_errid(num) );
	std::TCOUT << msg.size() << TEXT("\"") << msg << TEXT("\"") << std::endl;
#else
	std::string msg( osapi::str_from_errid(num) );
	std::cout << msg.size() << "\"" << msg << "\"" << std::endl;
#endif
 }
	return 0;
}
#endif
/*
rem :30,32 w! make.bat
cl /W4 /WX /MD /EHa /O2 /wd4819 /DUNICODE /DDEBUG_RSRC_STR_FROM_ERRID osapi_str_from_errid.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /wd4819 /DDEBUG_RSRC_STR_FROM_ERRID osapi_str_from_errid.cpp /Fea_u08
del osapi_str_from_errid.obj
# :34,35 w! make.sh
#!/bin/bash -x
g++ -Wall osapi_str_from_errid.cpp -DDEBUG_RSRC_STR_FROM_ERRID -std=c++11
*/
