#ifdef _WIN32 // win32 or win64
#include "osapi_log_with_msg_and_id_win.cpp"
#else
#include "osapi_log_with_msg_and_id_unix.cpp"
#endif

//--------------------------------------------------------------------
#ifdef DEBUG_OSAPI_LOG_WITH_MSG_AND_ID
#include <iostream>	/* for unix */
#include <stdexcept>	/* std::runtime_error(-) */
#include "osapi_mbs_wcs.cpp"		/* osapi::init_locale_to_jp() */
					/* osapi::mbs_from_wcs(-) */
#include "osapi_str_from_errid.cpp"	/* osapi::str_from_errid(-) */

/*
埋め込む2byte文字コードは、
MS-C --> cp932 ,g++ --> utf-8としてそれぞれに分けないと駄目!!!
コメント内は
MS-C --> euc-jp/utf-8 (with Warning) ,cp932
*/

int main(int argc, char *argv[])
{
	if (argc != 2) {
		return 1;
	}

	osapi::init_locale_to_jp();

#ifdef UNICODE // only windiws
	std::wstring msg;
#else
	std::string msg;
#endif
	int message_id = -1;
	if ( isdigit( argv[1][0] ) ) {
		message_id = std::stoi( std::string( argv[1] ) );
	}
	else {
#ifdef UNICODE // only windiws
		msg = osapi::wcs_from_mbs( argv[1] );
#else
		msg = argv[1];
#endif
	}
	std::cout  <<      "id.........=\"" << message_id << "\"\n";
#ifdef UNICODE // only windiws
	std::TCOUT << TEXT("msg........=\"") << msg << TEXT("\"\n");
#else
	std::cout << "msg........=\"" << msg << "\"\n";
#endif

	std::cout << "msg_and_id=\""
		<< osapi_log_with_msg_and_id( msg ,message_id )
		<< "\"\n";
	std::cout << "msg       =\""
		<< osapi_log_with_msg( msg )
		<< "\"\n";
	std::cout << "id        =\""
		<< osapi_log_with_id( message_id )
		<< "\"\n";

  try {
#ifdef _WIN32
  	std::TSTRING path( TEXT("C\\Users\\public\\tmp.txt") );
	std::TCOUT << TEXT("path=") << path << std::endl;

	const void *hdlr = ::LoadLibrary( path.c_str() );
	if (hdlr == nullptr) {
		throw std::runtime_error(
		osapi_log_with_msg_and_id( path ,::GetLastError())
		);
	}
#else	// unix
  	std::string path( "/home/tmp.txt" );
	std::cout << "path=" << path << std::endl;

	const void *hdlr = fopen( path.c_str() , "r" );
	if (hdlr == nullptr) {
		throw std::runtime_error(
		osapi_log_with_msg_and_id( path ,errno )
		);
	}
#endif
  }
  catch (std::exception&e){
	std::cerr << "exception=\"" << e.what() << "\"\n";
  }
  catch (...) {
	std::cerr << "other exception" << std::endl;
  }
	return 0;
}
#endif  /* !DEBUG_OSAPI_LOG_WITH_MSG_AND_ID */
/*
rem :97,99 w! make.bat
cl /W4 /WX /MD /EHa /O2 /wd4819 /DUNICODE /DDEBUG_OSAPI_LOG_WITH_MSG_AND_ID osapi_log_with_msg_and_id.cpp /Fea_u16
cl /W4 /WX /MD /EHa /O2 /wd4819           /DDEBUG_OSAPI_LOG_WITH_MSG_AND_ID osapi_log_with_msg_and_id.cpp /Fea_u08
del osapi_log_with_msg_and_id.obj
# :101,102 w! make.sh
#!/bin/bash -x
g++ -Wall osapi_log_with_msg_and_id.cpp -DDEBUG_OSAPI_LOG_WITH_MSG_AND_ID -std=c++11
*/
