#ifndef osapi_getenv_h
#define osapi_getenv_h

/*
	環境変数を得る
	対応する変数がなければnull文字列(nullptrではない)を返す
*/

#ifdef _WIN32
#include "osapi_mbs_wcs.h"
namespace osapi {
std::TSTRING getenv(const std::TSTRING& name);
} // namespace osapi

#else	// unix
#include <string>
namespace osapi {
std::string getenv(const std::string& name);
} // namespace osapi
#endif


#endif /* !osapi_getenv_h */
