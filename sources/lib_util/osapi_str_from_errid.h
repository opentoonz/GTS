#ifndef osapi_str_from_errid_h
#define osapi_str_from_errid_h

#ifdef _WIN32 // win32 or win64
#include "osapi_mbs_wcs.h"	/* TOSTRINGSTREAM ,TSTRING ,TCOUT */
#else
#include <string>
#endif

/*
	OSのAPIが返すエラー番号を渡し、メッセージの文字列を得る

	引数(=エラー番号)
		Sccessの場合			-->	対応する言葉を返す
		引数に対応する文字列がない場合	-->	エラーの言葉を返す
	注意1：エラーが起きたらそのエラーメッセージを返す
	注意2：アプリのエラー(例外)処理の中で使うので、例外は投げない
*/

namespace osapi {
#ifdef _WIN32 // win32 or win64
std::TSTRING tstr_from_errid( const DWORD message_id );
#else
std::string str_from_errid( const int erno );
#endif
} // namespace osapi

#endif /* !osapi_str_from_errid_h */
