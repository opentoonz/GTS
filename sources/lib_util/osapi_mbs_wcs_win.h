#ifndef osapi_mbs_wcs_win_h
#define osapi_mbs_wcs_win_h

#include <windows.h>	/* CP_THREAD_ACP */

#include <string>	/* std::string ,std::wstring */
#include <sstream>	/* std::ostringstream ,std::wostringstream */
#include <iostream>	/* std::cout ,std::cerr ,std::wcout ,std::wcerr */

#ifdef UNICODE
/* Wide Character対応 */
# define TSTRING wstring
# define TOSTRINGSTREAM wostringstream
# define TISTRINGSTREAM wistringstream
# define TCOUT wcout
# define TCERR wcerr
#else /* !UNICODE */
/* Multi Byte Character対応 */
# define TSTRING string
# define TOSTRINGSTREAM ostringstream
# define TISTRINGSTREAM istringstream
# define TCOUT cout
# define TCERR cerr
#endif/* !UNICODE */

/*
	文字コード変換(for windows)

	エラー例外処理の中で使うのでエラー例外を投げない
	エラー時は空文字列を返す
*/
namespace osapi {

/* UNICODEのときはstd::wcoutのため必須 */
void init_locale_to_jp(void);

/* マルチバイト文字列 --> ワイド文字文字列 */
std::wstring wcs_from_mbs(
	const std::string&mbs ,const UINT code_page = CP_THREAD_ACP
);

/* ワイド文字文字列 --> マルチバイト文字列 */
std::string mbs_from_wcs(
	const std::wstring&wcs ,const UINT code_page = CP_THREAD_ACP
);

/* マルチバイト文字列で cp932 --> utf-8 */
std::string utf8_from_cp932( const std::string& cp932 );

/* マルチバイト文字列で utf-8 --> cp932 */
std::string cp932_from_utf8( const std::string& utf8 );

} // namespace osapi

#endif /* !osapi_mbs_wcs_win_h */
