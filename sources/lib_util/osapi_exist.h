#ifndef osapi_exist_h
#define osapi_exist_h

#include "osapi_mbs_wcs.h"	// TSTRING

namespace osapi {

/*
> 目的
file あるいは directory の存在を確認する(不存在の確認はできない)

> 戻り値
true(存在する),false(存在しない(エラー含む))

> 利用上の注意
以下の理由で使える場合が限られる
-falseでも存在しないのではなくアクセスできない(エラー)場合がある。
-存在のチェックと利用のタイミングが同時にならない
*/

#if defined _WIN32 // win32 or win64
/* pathの文字コードはcp932で渡す(Windows) */
const bool exist(const std::TSTRING& path);
#else // unix
/* pathの文字コードはutf8で渡す(Ubuntu16.04) */
const bool exist(const std::string& path);
#endif

/* 文字コードはutf8(=mbs)を渡す
Windowsでは中でcp932に変換してwin32関数に渡している */
const bool exist_utf8_mbs(const std::string& path);

}

#endif /* !osapi_exist_h */
