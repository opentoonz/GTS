#include <stdlib.h>	/* getenv() */
#include <string.h>	/* strrchr() */
#include <assert.h>	/* assert() */

#include "ptbl_funct.h"

/* ファイルパスからファイル名のみ得る(尻の.exe等は残る) */
char *ptbl_get_cp_filename_from_path( char *cp_filepath )
{
	char	*cp_sepa, *cp_tmp, *cp_comm_body;

	cp_comm_body = cp_filepath;
	cp_sepa = ptbl_get_cp_path_separeter();

	cp_tmp = strrchr( cp_filepath, (int)(cp_sepa[0]) );
	if (NULL != cp_tmp) { cp_comm_body = &cp_tmp[1]; }

	return cp_comm_body;
}

/* パスの区切り文字を得る(文字列の方が使いやすいので) */
char *ptbl_get_cp_path_separeter( void )
{
#if defined _WIN32
	return "\\";
#else
	return "/";
#endif
}

