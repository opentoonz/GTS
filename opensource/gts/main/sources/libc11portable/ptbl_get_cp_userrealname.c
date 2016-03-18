#include "ptbl_funct.h"

/* 現在のユーザー名を得る(CygwinではAdmin...)
   見つからないときはNULLを戻す */
char *ptbl_get_cp_userrealname( void )
{
#if defined i386_redhat_cygwin1_3_15
//	return ptbl_get_cp_loginname();
#else
	return ptbl_get_cp_username();
#endif
}

