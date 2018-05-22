#include <cstring>	/* strerror(-) , strerror_r(-) */
#include "osapi_str_from_errid.h"
#include <cerrno>	/* EINVAL */
#if defined(HAVE_CONFIG_H)
#  include <config.h>
#endif

/* 引数がSccessの時(erno == 0)も対応する言葉を返す */
std::string osapi::str_from_errid( const int erno )
{
#ifdef HAVE_STRERROR_R
	char buff[4096]; buff[0] = '\0';
#  ifdef STRERROR_R_CHAR_P
	/*
	 * strerror_r() returns a char*
	*/
	char* ptr = ::strerror_r(erno, buff, sizeof(buff));
	return ptr == nullptr? std::string(): std::string(ptr);
#  else
	/*
	 * strerror_r() returns an int
	*/
	const int ret = ::strerror_r(erno, buff, sizeof(buff));

	if (-1 == ret) {
	 switch (erno) {	/* エラーメッセージをとる時のエラー! */
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
#  endif
#else
	/*
	 * strerror_r() not defined
	*/
	char* ptr = ::strerror(erno);
	return ptr == nullptr? std::string(): std::string(ptr);
#endif
}

