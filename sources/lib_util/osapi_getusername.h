#ifndef osapi_getusername_h
#define osapi_getusername_h

/*
現在のユーザー名を得る
見つからないときはnull文字列(nullptrではない)を返す
*/

#ifdef _WIN32
#include "osapi_mbs_wcs.h"
namespace osapi {
std::TSTRING getusername(void);
} // namespace osapi

#else	// unix
#include <string>
namespace osapi {
/* 注意：login名ではない場合あり。CygwinではAdmin... */
std::string getusername(void);
} // namespace osapi
#endif

#endif /* !osapi_getusername_h */
