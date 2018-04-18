#include <string>
#include "osapi_mbs_wcs_win.h"

namespace osapi {

void init_locale_to_jp(void)
{
	/*
	(しないと日本語文字部分のみ処理しない)
	ただし数値カテゴリはC localeのままに
	(しないと3桁ごとにカンマが付く(1000-->1,000))
	*/
#ifdef UNICODE	/* vc2015からUNICODE以外でこの処理すると表示しない  */
	std::locale::global(
	std::locale(std::locale(),"japanese",std::locale::ctype)
	);
	/* std::locale::global(std::locale("")); ダメ
	*/
	/* std::locale::global(std::locale("japanese")); ダメ
	std::setlocale(LC_ALL,"japanese");
	*/
#endif
}

/*
汎用データ型  ワイド文字(UNICODE)(※1)	マルチバイト文字(_MBCS)(※2)
TCHAR	      wchar_t			char 
LPTSTR	      wchar_t *			char * 
LPCTSTR	      const wchar_t *		const char * 
※1  1文字を16ビットのワイド文字として表すUnicode を使う方法
	すべての文字が 16 ビットに固定されます。
	マルチバイト文字に比べ、メモリ効率は低下しますが処理速度は向上します
※2  1文字を複数のバイトで表すマルチバイト文字
	MBCS(Multibyte Character Set) と呼ばれる文字集合を使う方法
	可変長だが、事実上、サポートされているのは 2 バイト文字までなので、
	マルチバイト文字の 1 文字は 1 バイトまたは 2 バイトとなります。
	Windows 2000 以降、Windows は内部で Unicode を使用しているため、
	マルチバイト文字を使用すると内部で文字列の変換が発生するため
	オーバーヘッドが発生します。
	UNICODEも_MBCSも未定義のときはこちらになる。
*/

/* マルチバイト文字列 --> ワイド文字文字列 */
std::wstring wcs_from_mbs(
	const std::string&mbs ,const UINT code_page
) {
	/* 生成するワイド文字数の大きさを(終端含んで)得る */
	int length = ::MultiByteToWideChar(
		code_page	/* 変換に使うコードページを指定		*/
		,0		/* 一連のビットフラグをセット		*/
		,mbs.c_str()	/* 変換する文字列へのポインタを指定	*/
		,-1	/* -1指定により終端文字を含む大きさを計算し返す	*/
		,0	/* 変換後の文字列を受け取るバッファへのポインタ	*/
		,0	/* 0を指定すると必要なバッファのワイド文字数が返る
				受け取るバッファは使われません		*/
	);

	/* 終端以外の文字がないなら何もしない */
	if (length <= 1) { return std::wstring(); }

	/* ワイド文字列バッファーを確保 */
	std::wstring wcs; wcs.resize(length);

	/* マルチバイト文字列 を ワイド文字文字列 に変換 */
	length = ::MultiByteToWideChar(
		code_page
		,0
		,mbs.c_str()
		,-1
		,const_cast<LPWSTR>(wcs.data())
		,static_cast<int>(wcs.size())
	);

	/* ゼロを返したときはエラーである */
	if (length == 0) {
		/* エラーの場合、空文字列を返す */
		return std::wstring();
		/*
		本来は、::GetLastError()から、
		ERROR_INSUFFICIENT_BUFFER
		 (システム コールに渡されるデータ領域が小さすぎます。)
		ERROR_INVALID_FLAGS:
		 (フラグが無効です。)
		ERROR_INVALID_PARAMETER
		 (パラメーターが間違っています。)
		ERROR_NO_UNICODE_TRANSLATION
		 (Unicode 文字のマッピングがターゲットのマルチバイト コード ページにありません。)
		のエラー例外を返すのだが、
		この関数は、
		エラー例外処理の中で使うので、エラー例外を投げない
		また
		"/DUNICODE"時エラーメッセージはstd::wstringの型になるが、
		std::exceptionの引数はstd::stringのみなので、
		例外処理の引数として与えることができない
		*/
	}

	/* 終端文字を消す。end()は終端より先位置 */
	//wcs = std::wstring(buf.begin() ,buf.end()-1); /* 終端以外を */
	wcs.erase(wcs.end()-1);

	return wcs;
}

/* ワイド文字文字列 --> マルチバイト文字列 */
std::string mbs_from_wcs(
	const std::wstring&wcs ,const UINT code_page
) {
	/* 終端文字を含む大きさを返す(第４引数で -1 指定により) */
	int length = ::WideCharToMultiByte(
		code_page ,0 ,wcs.c_str() ,-1 ,0,0,0,0
	);

	/* 終端以外の文字がないなら何もしない */
	if (length <= 1) {
		return std::string();
	}

	/* 文字列バッファーを確保 */
	std::string mbs; mbs.resize(length);

	/* ワイド文字文字列 を マルチバイト文字列 に変換 */
	length = ::WideCharToMultiByte(
		code_page ,0 ,wcs.c_str() ,-1
		,const_cast<LPSTR>(mbs.data())
		,static_cast<int>(mbs.size()) ,0 ,NULL
	);

	/* ゼロを返したときはエラーである */
	if (length == 0) {
		/* エラーの場合、空文字列を返す */
		return std::string();
		/*
		本来は、::GetLastError()から、
		ERROR_INSUFFICIENT_BUFFER
		ERROR_INVALID_FLAGS
		ERROR_INVALID_PARAMETER
		のエラー例外を返すのだが、
		この関数は、
		エラー例外処理の中で使うので、エラー例外を投げない
		また
		"/DUNICODE"時エラーメッセージはstd::wstringの型になるが、
		std::exceptionの引数はstd::stringのみなので、
		例外処理の引数として与えることができない
		*/
	}

	/* 終端文字を消す。end()は終端より先位置 */
	//mbs = std::string(buf.begin() ,buf.end()-1); /* 終端以外を */
	mbs.erase(mbs.end()-1);

	return mbs;
}

/* マルチバイト文字列でcp932を含む文字列をutf-8に変換 */
std::string utf8_from_cp932( const std::string& cp932 )
{
	std::wstring wcs;
	wcs = osapi::wcs_from_mbs( cp932 );
	std::string mbs;
	mbs = osapi::mbs_from_wcs( wcs ,CP_UTF8 );
	return mbs;
}

/* マルチバイト文字列でutf-8を含む文字列をcp932に変換 */
std::string cp932_from_utf8( const std::string& utf8 )
{
	std::wstring wcs;
	wcs = osapi::wcs_from_mbs( utf8 ,CP_UTF8 );
	std::string mbs;
	mbs = osapi::mbs_from_wcs( wcs ,932 );
	return mbs;
}

} /* !namespace osapi */

#ifdef DEBUG_RSRC_MBS_WCS_WIN_MultiByteToWideChar
int main(int argc ,char *argv[])
{
	if (argc != 2) {
		return 1;
	}
	const int length = ::MultiByteToWideChar(
		CP_ACP
		,0
		,argv[1]
		,-1
		,0
		,0
	);
	std::cout << "length=" << length << std::endl;

	return 0;
}
#endif
