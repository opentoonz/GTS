#ifndef osapi_log_with_msg_and_id_unix_h
#define osapi_log_with_msg_and_id_unix_h

#include <string>

#define to_str_(n) to_str__(n)	/* Exsample:__LINE__ -->  56   */
#define to_str__(n) #n		/* Exsample:56       --> "56" */

/*
	エラーログを生成する元関数(for unix)

	直によんではいけない
	例外で投げる用途で使うため戻り値の文字はmbs(std::string)固定
*/
namespace osapi {
const std::string log_with_msg_and_id_(
	const std::string& msg
	,const int erno
	,const std::string& file
	,const std::string& line
	,const std::string& pretty_function
	,const std::string& comp_type
	,const std::string& gnuc
	,const std::string& gnuc_minor
	,const std::string& gnuc_patchlevel
	,const std::string& date
	,const std::string& time
);
} // osapi

/* メッセージと::errnoによるエラーメッセージを付加したエラーログを生成 */
#define osapi_log_with_msg_and_id(msg,erno) osapi::log_with_msg_and_id_(msg,erno,__FILE__,to_str_(__LINE__),__PRETTY_FUNCTION__,to_str__(__GNUC__),to_str_(__GNUC__),to_str_(__GNUC_MINOR__),to_str_(__GNUC_PATCHLEVEL__),__DATE__,__TIME__)
/*
osapi_log_with_msg_and_id("msg",errno)
--> 実行結果例
--> "osapi_log_with_msg_and_id.cxx 86;int main(int, char**);__GNUC__ 4.1.2-48;2012-Jan-30 15:36:27;msg;No such file or directory"
*/
/* メッセージを付加したエラーログを生成 */
#define osapi_log_with_msg(msg            ) osapi::log_with_msg_and_id_(msg,0   ,__FILE__,to_str_(__LINE__),__PRETTY_FUNCTION__,to_str__(__GNUC__),to_str_(__GNUC__),to_str_(__GNUC_MINOR__),to_str_(__GNUC_PATCHLEVEL__),__DATE__,__TIME__)
/* errnoによるエラーメッセージを付加したエラーログを生成 */
#define osapi_log_with_id(           erno ) osapi::log_with_msg_and_id_("",erno ,__FILE__,to_str_(__LINE__),__PRETTY_FUNCTION__,to_str__(__GNUC__),to_str_(__GNUC__),to_str_(__GNUC_MINOR__),to_str_(__GNUC_PATCHLEVEL__),__DATE__,__TIME__)

#endif /* !osapi_log_with_msg_and_id_unix_h */
