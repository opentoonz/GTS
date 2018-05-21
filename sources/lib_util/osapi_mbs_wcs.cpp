#ifdef _WIN32 // win32 or win64
#include "osapi_mbs_wcs_win.cpp"
#else
#include "osapi_mbs_wcs_unix.cpp"
#endif

//------------------------------------------------------------
#ifdef DEBUG_RSRC_MBS_WCS
#include <iostream>

/*
2byte文字コード
+-- 引数で渡す場合	OSの文字コード
    +-- Windows	--> cp932
    +-- unix	--> utf-8
+-- 埋め込む場合	保存ファイルとしての文字コード
    +-- MS-C	--> cp932 ,utf-8(with Warning)
    +-- g++	--> utf-8
+-- コメントとして記入する場合
    +-- MS-C	--> cp932 ,utf-8/euc-jp(with Warning)
    +-- g++	--> utf-8
*/

int main(int argc, char *argv[])
{
	if (argc != 2) {
		return 1;
	}

	osapi::init_locale_to_jp();

	std::cout <<   "argv[1](cp932) =\"" << argv[1] << "\"" << std::endl;

	std::wstring wcs( osapi::wcs_from_mbs( argv[1] ) );
	std::wcout << L"mbs->wcs(cp932)=\"" << wcs << L"\"" << std::endl;

	std::string  mbs( osapi::mbs_from_wcs( wcs ) );
	std::cout   << "wcs->mbs(cp932)=\"" << mbs << "\"" << std::endl;

#ifdef _WIN32 // win32 or win64
	std::string utf8( osapi::utf8_from_cp932( argv[1] ) );
	std::cout << "cb932->utf8=\"" << utf8 << "\"" << std::endl;
	std::string cp932( osapi::cp932_from_utf8( utf8 ) );
	std::cout << "utf8->cp932=\"" << cp932 << "\"" << std::endl;
#else
	std::string cp932( osapi::cp932_from_utf8( argv[1] ) );
	std::cout << "utf8->cp932=\"" << cp932 << "\"" << std::endl;
	std::string utf8( osapi::utf8_from_cp932( cp932 ) );
	std::cout << "cb932->utf8=\"" << utf8 << "\"" << std::endl;
#endif

	return 0;
}
#endif  /* !DEBUG_RSRC_MBS_WCS */
/*
rem :57,59 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /DDEBUG_RSRC_MBS_WCS osapi_mbs_wcs.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_RSRC_MBS_WCS osapi_mbs_wcs.cpp /Fea_u08
del osapi_mbs_wcs.obj
# :61,62 w! make.sh
#!/bin/bash -x
g++ -Wall osapi_mbs_wcs.cpp -DDEBUG_RSRC_MBS_WCS -std=c++11
*/
