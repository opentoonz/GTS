#ifndef osapi_mbs_wcs_unix_h
#define osapi_mbs_wcs_unix_h

#include <string>

/*
	文字コード変換(for unix)

	エラー例外処理の中で使うのでエラー例外を投げない
	エラー時は空文字列を返す
*/

namespace osapi {

/* UNICODEのときはstd::wcoutのため必須 */
void init_locale_to_jp(void);

/* マルチバイト文字列 --> ワイド文字文字列 */
std::wstring wcs_from_mbs( const std::string& mbs );

/* ワイド文字文字列 --> マルチバイト文字列 */
std::string mbs_from_wcs( const std::wstring& wcs );

/* マルチバイト文字列でcp932を含む文字列をutf-8に変換 */
std::string utf8_from_cp932( const std::string& cp932 );

/* マルチバイト文字列でutf-8を含む文字列をcp932に変換 */
std::string cp932_from_utf8( const std::string& utf8 );

} // namespace osapi

#endif /* !osapi_mbs_wcs_unix_h */
