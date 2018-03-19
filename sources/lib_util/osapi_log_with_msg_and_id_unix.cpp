#include <sstream>
#include "osapi_mbs_wcs_unix.h"		/* osapi::mbs_from_wcs(-) */
#include "osapi_str_from_errid.h"	/* osapi::str_from_errid(-) */
#include "osapi_log_with_msg_and_id_unix.h"

/* エラーログを生成する元関数、直接呼び出すことはしない */
const std::string
osapi::log_with_msg_and_id_(
	const std::string& msg
	,const int erno
	,const std::string& file
	,const std::string& line
	,const std::string& pretty_function
	,const std::string& comp_type
	,const std::string& gnuc
	,const std::string& gnuc_minor
	,const std::string& gnuc_patchlevel
	,const std::string& gnuc_rh_release
	,const std::string& date
	,const std::string& time
) {
/*
#define osapi_log_with_msg_and_id(tit,erno) osapi::log_with_msg_and_id_(
tit
,erno
,__FILE__
,tostr(__LINE__)
,__PRETTY_FUNCTION__
,igs_tostr_(__GNUC__)
,tostr(__GNUC__)
,tostr(__GNUC_MINOR__)
,tostr(__GNUC_PATCHLEVEL__)
,tostr(__GNUC_RH_RELEASE__)
,__DATE__
,__TIME__
)
*/
	std::string errmsg;

	/* 発生場所 ファイル名:フルパスの場合ファイル名だけにする */
	std::string::size_type index = file.find_last_of("/\\");
	if (std::string::npos != index) {
	 errmsg += file.substr(index+1);
	} else {
	 errmsg += file;
	}
	/* 発生場所 行番号 */
	errmsg += ':'; errmsg += line;
	/* 発生場所 関数名 */
	errmsg += ':'; errmsg += pretty_function;
	/* コンパイラータイプ */
	errmsg += ':'; errmsg += comp_type;
	/* コンパイラーバージョン */
	errmsg += ':'; errmsg += gnuc;
	errmsg += '.'; errmsg += gnuc_minor;
	errmsg += '.'; errmsg += gnuc_patchlevel;
	errmsg += '-'; errmsg += gnuc_rh_release;
	/* ビルド年:月:日 */
	std::istringstream ist(date);
	std::string month,day,year; ist >> month; ist >> day; ist >> year;
	errmsg += ':'; errmsg += year;
	errmsg += ':'; errmsg += month;
	errmsg += ':'; errmsg += day;
	/* ビルド自:分:秒 */
	errmsg += ':'; errmsg += time;
	/* メッセージ */
 if (0 < msg.size()) {
	errmsg += ':';
	errmsg += msg;
 }
	/* エラー番号→エラーメッセージ */
 if (0 != erno) {
	errmsg += ':'; errmsg += osapi::str_from_errid(erno);
 }
	/* MBCSで返す */
	return errmsg;
}
