#if defined _WIN32
# include <stdlib.h>	/* getenv() */
#else
# include <sys/types.h>	/* getuid(),getpwuid() */
# include <unistd.h>	/* getuid() */
# include <pwd.h>	/* getpwuid() */
#endif
#include "ptbl_funct.h"

/* 現在のユーザー名を得る(CygwinではAdmin...)
   見つからないときはNULLを戻す */
char *ptbl_get_cp_username( void )
{
	char	*cp_username;

#if defined _WIN32
	/* Windowsでは(user名は)環境変数USERNAMEからとる */
	/* getenv()は環境文字列への値へのポインタを返す */
	cp_username = getenv( "USERNAME" );
#else
	/* getlogin()はlogin時のユーザー名の文字列へのポインタを返す */
	// cp_loginname = getlogin();

	/* cp_username = tp_pw->pw_name;が示す先は、
	   関数からぬけても存在する? */
	struct passwd *tp_pw; /* staticでなくてもいい? */
	tp_pw = getpwuid( getuid() );
	if (NULL == tp_pw) { cp_username = NULL; }
	else               { cp_username = tp_pw->pw_name; }

#endif
	return cp_username;
}

