#if defined _WIN32

#include "windows.h"
#include "ptbl_funct.h"
#include "ptbl_path_max.h"

/* utf-8を含む文字列をcp932に変換(マルチバイト文字列) */
char* ptbl_charcode_cp932_from_utf8(const char* utf8)
{
	wchar_t wcs[PTBL_PATH_MAX];
	static char mbs[PTBL_PATH_MAX];
	wcs[0] = L'\0';
	mbs[0] = '\0';

	/* 第4引数で-1指定により終端文字を含む変換後の文字列長を得る */
	const int wcs_len = MultiByteToWideChar( CP_UTF8,0,utf8,-1,NULL,0 );

	/* 終端以外の文字がない、あるいはバッファーのサイズを超えた */
	if (wcs_len <= 1 || PTBL_PATH_MAX <= wcs_len) {
		return mbs;
	}

	/* Unicode(UTF16)へ変換 */
	if (MultiByteToWideChar(CP_UTF8,0,utf8,-1 ,wcs,wcs_len ) == 0) {
		return mbs;
	}

	/* 第4引数で-1指定により終端文字を含む変換後の文字列長を得る */
	const int mbs_len = WideCharToMultiByte(
		CP_THREAD_ACP ,WC_NO_BEST_FIT_CHARS
		,wcs ,-1 ,NULL ,0 ,NULL ,NULL
	);

	/* 終端以外の文字がない、あるいはバッファーのサイズを超えた */
	if (mbs_len <= 1 || PTBL_PATH_MAX <= mbs_len) {
		return mbs;
	}

	/* UnicodeからShiftJISへ変換 */
	/* 第2引数でWC_NO_BEST_FIT_CHARS指定により
	対応する文字がない時に近い文字に勝手に変換するのを防ぎ?と変換する */
	if (WideCharToMultiByte(
		CP_THREAD_ACP ,WC_NO_BEST_FIT_CHARS
		,wcs ,-1 ,mbs ,mbs_len ,NULL ,NULL
	) == 0) {
		mbs[0] = '\0';
		return mbs;
	}
	return mbs;
}

#endif // _WIN32
