#include <iconv.h>	/* iconv_open(-) */
#include <cstring>	/* memset(-) */
#include <vector>
#include "osapi_mbs_wcs_unix.h"

namespace osapi {

void init_locale_to_jp(void)
{
	/*
	使う文字コードは"locale -a"で調べる
	*/
	setlocale(LC_CTYPE, "ja_JP.utf8");
}

/* マルチバイト文字列 --> ワイド文字文字列 */
std::wstring wcs_from_mbs( const std::string& mbs )
{
	size_t length = 0;
 {
	const char *src_ptr = mbs.c_str();
	mbstate_t ss; memset(&ss ,0 ,sizeof(ss));
	length = ::mbsrtowcs(NULL ,&src_ptr ,0 ,&ss);
	if (length == (size_t)(-1)) {
		/*
		"got bad multi byte character,when size"
		不正なマルチバイト列に遭遇した
		*/
		return std::wstring();
	}
	if (length <= 0) {
		/*
		文字がないなら何もしない
		*/
		return std::wstring();
	}
	++length;
 }
	//std::vector<wchar_t> dst(length);
	std::wstring wcs;
	wcs.resize(length);
 {
	const char *src_ptr = mbs.c_str();
	mbstate_t ss; memset(&ss ,0 ,sizeof(ss));
	//length = ::mbsrtowcs(&dst.at(0) ,&src_ptr ,length ,&ss);
	length = ::mbsrtowcs(
		const_cast<wchar_t *>(wcs.c_str()) ,&src_ptr ,length ,&ss);
	if (length == (size_t)(-1)) {
		/*
		"got bad multi byte character,when conv"
		不正なマルチバイト列に遭遇した
		*/
		return std::wstring();
	}
	if (length <= 0) {
		/*
		"got zero or under equal -2"
		文字がないなら何もしない
		*/
		return std::wstring();
	}
 }
	//wcs = std::wstring(dst.begin() ,dst.end()-1);/* 終端以外を */
	wcs.erase(wcs.end()-1); /* 終端文字を消す */

	return wcs;
}
/* ワイド文字文字列 --> マルチバイト文字列 */
std::string mbs_from_wcs( const std::wstring& wcs )
{
	size_t length = 0;
 {
	const wchar_t *src_ptr = wcs.c_str();
	mbstate_t ss; memset(&ss ,0 ,sizeof(ss));
	length = ::wcsrtombs(NULL ,&src_ptr ,0 ,&ss);
	if (length <= 0) {
		/*
		"got bad wide character"
		文字がないなら何もしない
		*/
		return std::string();
	}
	++length;
 }
	//std::vector<char> dst(length);
	std::string mbs;
	mbs.resize(length);
 {
	const wchar_t *src_ptr = wcs.c_str();
	mbstate_t ss; memset(&ss ,0 ,sizeof(ss));
	//length = ::wcsrtombs(&dst.at(0) ,&src_ptr ,length ,&ss);
	length = ::wcsrtombs(
		const_cast<char *>(mbs.c_str()) ,&src_ptr ,length ,&ss);
	if (length <= 0) {
		/*
		"got bad wide character"
		文字がないなら何もしない
		*/
		return std::string();
	}
 }
	//mbs = std::string(dst.begin() ,dst.end()-1);/* 終端以外を */
	mbs.erase(mbs.end()-1); /* 終端文字を消す */

	return mbs;
}

} /* !namespace osapi */

namespace {
 const std::string iconv_to_from_(
	const std::string&text
	,const char *tocode
	,const char *fromcode
 ) {
	iconv_t icd = ::iconv_open(tocode, fromcode); // "iconv --list"
	if (reinterpret_cast<iconv_t>(-1) == icd) {
		return std::string();
		/* errno?*/
	}

	std::vector<char> dst(text.size()*4);
	char *inbuf = const_cast<char *>(text.c_str());
	char *outbuf = &dst.at(0);
	size_t inbytesleft = text.size();
	size_t outbytesleft = dst.size();
	size_t ret = ::iconv(
		icd, &inbuf, &inbytesleft, &outbuf, &outbytesleft
	);
	*outbuf = '\0';

	/*
	retに処理した数が入るはずだが、rhel5ではゼロが帰るので、
	処理数を別途計算する
	*/
	ret = dst.size() - outbytesleft;
	if (ret <= 0) {
	//if (static_cast<size_t>(-1) == ret) {
		::iconv_close(icd);

		return std::string();
		/* errno? */
	}

	if (-1 == ::iconv_close(icd)) {
		return std::string(); 
		/* errno? */
	}

	std::string mbs(std::string( dst.begin(),dst.begin() +ret ));
	return mbs;
 }
}

namespace osapi {

/* マルチバイト文字列でcp932を含む文字列をutf-8に変換 */
std::string utf8_from_cp932(const std::string& cp932) {
	return iconv_to_from_( cp932 ,"UTF-8", "CP932" ); // "iconv --list"
}

/* マルチバイト文字列でutf-8を含む文字列をcp932に変換 */
std::string cp932_from_utf8(const std::string& utf8) {
	return iconv_to_from_( utf8 ,"CP932" ,"UTF-8" ); // "iconv --list"
}

} /* !namespace osapi */
