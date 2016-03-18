#if defined _WIN32
# include <stdlib.h>	/* getenv() */
#else
# include <unistd.h>	/* getlogin() */
#endif

#include "ptbl_funct.h"

/* login名を得る(Windowsではログオン名)見つからないときはNULLを戻す */
char *ptbl_get_cp_loginname( void )
{
	char	*cp_loginname;

#if defined _WIN32
	/* Windowsでは(ログオン名は)環境変数USERNAMEからとる */
	/* getenv()は環境文字列への値へのポインタを返す */
	cp_loginname = getenv( "USERNAME" );
#else
	/* getlogin()はユーザー名の文字列へのポインタを返す */
	cp_loginname = getlogin();
#endif

	return cp_loginname;
}

