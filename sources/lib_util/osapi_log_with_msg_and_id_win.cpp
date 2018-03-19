#include "osapi_mbs_wcs_win.h"		/* osapi::mbs_from_wcs(-) */
#include "osapi_str_from_errid.h"	/* osapi::str_from_errid(-) */
#include "osapi_log_with_msg_and_id_win.h"

/* エラーログを生成する元関数、直接呼び出すことはしない */
const std::string
osapi::log_with_msg_and_id_(
	const std::TSTRING& msg
	,const DWORD message_id
	,const std::string& file
	,const std::string& line
	,const std::string& funcsig
	,const std::string& comp_type
	,const std::string& msc_full_ver
	,const std::string& date
	,const std::string& time
)
{
/*
#define osapi_log_with_msg_and_id(msg,message_id) osapi::log_with_msg_and_id_(
msg
,message_id
,__FILE__
,to_str_(__LINE__)
,__FUNCSIG__
,to_str__(_MSC_VER)
,to_str_(_MSC_FULL_VER)
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
	errmsg += ':'; errmsg += funcsig;
	/* コンパイラータイプ */
	errmsg += ':'; errmsg += comp_type;
	/* コンパイラーバージョン */
	errmsg += ":"; errmsg += msc_full_ver;
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
#ifdef UNICODE
	errmsg += osapi::mbs_from_wcs(msg);
#else
	errmsg += msg;
#endif
	}
	/* エラー番号→エラーメッセージ */
	if (NO_ERROR != message_id) {
	errmsg += ':';
#ifdef UNICODE
	errmsg += osapi::mbs_from_wcs(osapi::tstr_from_errid(message_id));
#else
	errmsg += osapi::tstr_from_errid(message_id);
#endif
	}

	/* MBCSで返す */
	return errmsg;
}
