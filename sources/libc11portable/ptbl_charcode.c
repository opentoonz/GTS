#if defined _WIN32

//#include "winnls.h"
#include "windows.h"
#include "ptbl_funct.h"

/* utf-8を含む文字列をcp932に変換(マルチバイト文字列) */
char* ptbl_charcode_cp932_from_utf8(const char* utf8)
{
	/* 第4引数で-1指定により終端文字を含む変換後の文字列長を得る */
	const int wcs_len = MultiByteToWideChar(
		CP_UTF8,0,utf8,-1,NULL,0
	);

	/* 終端以外の文字がないなら */
	if (wcs_len <= 1) {
		return "";
	}

	/* 必要な分だけUnicode文字列のバッファを確保 */
	wchar_t* wcs = calloc( wcs_len , sizeof(wchar_t) );
	if (wcs == NULL) {
		return "";
	}

	/* Unicode(UTF16)へ変換 */
	if (MultiByteToWideChar(CP_UTF8,0,utf8,-1 ,wcs,wcs_len ) == 0) {
		free(wcs);
		return "";
	}

	/* 第4引数で-1指定により終端文字を含む変換後の文字列長を得る */
	const int mbs_len = WideCharToMultiByte(
		CP_THREAD_ACP ,WC_NO_BEST_FIT_CHARS
		,wcs ,-1 ,NULL ,0 ,NULL ,NULL
	);

	/* 終端以外の文字がないなら空文字を返す */
	if (mbs_len <= 1) {
		free(wcs);
		return "";
	}

	/* 必要な分だけUnicode文字列のバッファを確保 */
	char* mbs = calloc( mbs_len , sizeof(char) );
	if (mbs == NULL) {
		free(wcs);
		return "";
	}

	/* UnicodeからShiftJISへ変換 */
	/* 第2引数でWC_NO_BEST_FIT_CHARS指定により
	対応する文字がない時に近い文字に勝手に変換するのを防ぎ?と変換する */
	if (WideCharToMultiByte(
		CP_THREAD_ACP ,WC_NO_BEST_FIT_CHARS
		,wcs ,-1 ,mbs ,mbs_len ,NULL ,NULL
	) == 0) {
		free(wcs);
		free(mbs);
		return "";
	}
	free(wcs);
	return mbs;
}

#endif // _WIN32
