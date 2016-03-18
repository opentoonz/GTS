#if defined _WIN32
# include <stdlib.h>	/* getenv() */
#else
# include <unistd.h>	/* gethostname() */
# include <string.h>	/* strchr() */
# ifndef  HOST_NAME_MAX
#  define HOST_NAME_MAX 255
# endif
  /*注意  'man gethostname'より
	SUSv2では
		「ホスト名が255バイトに制限される」
	ことを保証している
	POSIX 1003.1-2001 では
		「ホスト名(終端のヌル文字は含まない)が
		HOST_NAME_MAXバイトに制限される」
	ことを保証している
  */
#endif

#include "ptbl_funct.h"

/* ホスト名を得る、ホスト名が見つからないときはNULLを戻す */
char *ptbl_get_cp_hostname( void )
{
	char	*cp_hostname;

#if defined _WIN32
	/* Windowsでは、ホスト名は環境変数からとる */
	cp_hostname = getenv( "COMPUTERNAME" );
#else
	static char ca_hostname[HOST_NAME_MAX];
	char *cp_tmp;

	if (0 != gethostname(ca_hostname, HOST_NAME_MAX)) {
		cp_hostname = NULL;
	}
	else {
		cp_hostname = ca_hostname;

		/* ドメイン名からホスト名に当る部分のみ切り出す */
		/* hostname.co.jp --> hostname */
		cp_tmp = strchr( cp_hostname, (int)'.' );
		if (NULL != cp_tmp) { cp_tmp[0] = '\0'; }
	}
#endif
	return cp_hostname;
}

