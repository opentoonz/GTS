#include <stdlib.h>	/* getenv() */
#include <string.h>	/* strrchr() */
#include <assert.h>	/* assert() */
#include <stdio.h>

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

char *ptbl_getenv(const char *name) {
	size_t length = 0;
	char *value = (char*)malloc(_MAX_ENV);
    if (value == NULL) {
        printf("malloc() failure\n");
        exit(-1);
    }
	value[0] = '\0';
# ifdef _WIN32
	{ // for vc2010
	 errno_t err_no = getenv_s(&length, value, _MAX_ENV, name);
	 if (err_no != 0) {
		printf("getenv_s() returned an error (%d)\n", err_no);
	 }
	} // for vc2010
	if ((length <= 0) || (length >= _MAX_ENV)) {
		printf("getenv_s() got a bad length (%d)\n", length);
	}
# else
    const char* env_ptr = getenv(name);
    if(env_ptr != NULL) {
        length = strlen(env_ptr);
        if (length >= _MAX_ENV) {
            length = _MAX_ENV - 1;
        }
        strncpy(value, env_ptr, length);
    }
# endif
	value[length] = '\0';
	return value;
}

