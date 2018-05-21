#ifndef osapi_mkdir_h
#define osapi_mkdir_h

/*
フォルダーを(一段階のみ)作成する
作成できないときはfalseを返す
*/

#ifdef _WIN32
#include "osapi_mbs_wcs.h"
namespace osapi {
bool mkdir(const std::TSTRING& dir_path);
} // namespace osapi

#else	// unix
#include <string>
namespace osapi {
bool mkdir(const std::string& dir_path);
} // namespace osapi
#endif

#endif /* !osapi_mkdir_h */
