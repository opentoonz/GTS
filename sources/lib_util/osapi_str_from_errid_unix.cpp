#include <cstring>	/* strerror(-) , strerror_r(-) */
#include "osapi_str_from_errid.h"

/* 引数がSccessの時(erno == 0)も対応する言葉を返す */
std::string osapi::str_from_errid( const int erno )
{
#ifdef __HP_aCC
	/* 
	HP-UX(v11.23)では、strerror_r()をサポートしない。
	注意::strerror()はThread SafeではなくMulti Threadでは正常動作しない
	エラー番号が不明な場合は「Unknown error nnn」というメッセージが返る
	*/
	char* ptr = ::strerror(erno);
	return ptr == nullptr? std::string(): std::string(ptr);

#elif (_POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600) && !_GNU_SOURCE

	/*
	POSIX.1-2001 で規定された XSI 準拠(XSI-compliant)のバージョン
	(glibc 2.3.4 以降で利用可能)
	*/
	char buff[4096]; buff[0] = '\0';
	const int ret = ::strerror_r(erno,buff,sizeof(buff));

	if (-1 == ret) {
	 swtich (errno) {	/* エラーメッセージをとる時のエラー! */
	 case EINVAL:
		return std::string(
 "Error:strerror_r():The value of errnum is not a valid error number"
		);
		/* errnum の値が有効なエラー番号ではない */
	 case ERANGE:
		return std::string(
 "Error:strerror_r():Insufficient storage was supplied via strerrbuf and buflen  to contain the generated message string."
		);
 		/* エラーコードを説明する文字列のために、
			充分な領域が確保できな かった */
	 deatult:
		return std::string(
 "Error:strerror_r():returns bad error number"
		);
	 }
	} else
	if (ret != 0) {
		return std::string(
 "Error:strerror_r():returns bad value"
		);
	}

	return std::string( buff );
#else
	/*
	rhel4はここに来る、、、
	GNU 仕様(GNU-specific)のバージョン
	(glibc 2.0 以降で利用可能)
	エラー番号が不明な場合は「Unknown error nnn」というメッセージが返る
	*/
	char buff[4096]; buff[0] = '\0';
	char* ptr = ::strerror_r( erno ,buff ,sizeof(buff) );
	return ptr == nullptr? std::string(): std::string(ptr);
#endif
}
