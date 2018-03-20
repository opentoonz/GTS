#ifndef osapi_log_with_msg_and_id_win_h
#define osapi_log_with_msg_and_id_win_h

#include <windows.h>
#include <string>
#include "osapi_mbs_wcs.h"

#define to_str_(n) to_str__(n)	/* Exsample:__LINE__ -->  56   */
#define to_str__(n) #n		/* Exsample:56       --> "56" */

/*
	エラーログを生成する元関数(for windows)

	直によんではいけない
	例外で投げる用途で使うため戻り値の文字はmbs(std::string)固定
	msgに日本語を含んだ場合の文字コードは、
	そのまま何も変換せず埋め込まれる
	message_idによるエラーメッセージは、
	日本語環境においてcp932文字コードが返る
*/
namespace osapi {
const std::string log_with_msg_and_id_(
	const std::TSTRING& msg
	,const DWORD message_id
	,const std::string& file
	,const std::string& line
	,const std::string& funcsig
	,const std::string& comp_type
	,const std::string& msc_full_ver
	,const std::string& date
	,const std::string& time
);
} // osapi

/* メッセージと::GetLastError()によるエラーメッセージを付加したエラーログを生成 */
#define osapi_log_with_msg_and_id(msg,message_id) osapi::log_with_msg_and_id_(msg     ,message_id,__FILE__,to_str_(__LINE__),__FUNCSIG__,to_str__(_MSC_VER),to_str_(_MSC_FULL_VER),__DATE__,__TIME__)
/*
osapi_log_with_msg_and_id("msg",::GetLastError())
--> 実行結果例
--> "osapi_log_with_msg_and_id_win.cxx 58;int __cdecl main(int,char *[]);_MSC_VER 150030729;2012-Jan-30 15:37:59;msg;指定されたモジュールが見つかりません。" */
/* メッセージを付加したエラーログを生成 */
#define osapi_log_with_msg( msg                 ) osapi::log_with_msg_and_id_(msg     ,NO_ERROR  ,__FILE__,to_str_(__LINE__),__FUNCSIG__,to_str__(_MSC_VER),to_str_(_MSC_FULL_VER),__DATE__,__TIME__)
/* ::GetLastError()によるエラーメッセージを付加したエラーログを生成 */
#define osapi_log_with_id(           message_id ) osapi::log_with_msg_and_id_(TEXT(""),message_id,__FILE__,to_str_(__LINE__),__FUNCSIG__,to_str__(_MSC_VER),to_str_(_MSC_FULL_VER),__DATE__,__TIME__)

#endif /* !osapi_log_with_msg_and_id_win_h */
