#include "osapi_str_from_errid.h"

/* 引数がSccessの時(message_id == NO_ERROR)も、対応する言葉を返す */
std::TSTRING osapi::tstr_from_errid( const DWORD message_id )
{
	LPTSTR lpBuffer = nullptr;
	if (::FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER
		| FORMAT_MESSAGE_FROM_SYSTEM
		| FORMAT_MESSAGE_IGNORE_INSERTS
					/* 入力元と処理方法のオプション */
		,NULL			/* メッセージの入力元 */
		,message_id	/* メッセージ識別子 */
		,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT)
					/* 言語識別子(=既定言語) */
		,reinterpret_cast<LPTSTR>(&lpBuffer)
					/* メッセージバッファ
			FORMAT_MESSAGE_ALLOCATE_BUFFERを指定した場合、
				&lpBuffer
			を
				LPTSTR
			型で与えなければならない、という不可解な仕様!!!
					*/
		,0			/* メッセージバッファの最大サイズ */
		,NULL	/* 複数のメッセージ挿入シーケンスからなる配列 */
	) == 0) { /* エラー */
		std::TOSTRINGSTREAM ost;
		ost	<< TEXT("FormatMessage(-) caused an error<")
			<< ::GetLastError()
			<< TEXT(">")
			;
		return ost.str();
	}

	/* std::TSTRINGに移し替える */
	std::TSTRING errmsg( lpBuffer );

	/* 文字の最後に改行コードがあるので削除する */
	std::TSTRING::size_type index = errmsg.find_first_of(
		TEXT("\r\n"));
	if (std::TSTRING::npos != index) {
		errmsg.erase(index); }

	/* 取り出したメッセージバッファーを開放する */
	::LocalFree(lpBuffer);

	return errmsg;
}
