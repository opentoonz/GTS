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

//------------------------------------------------------------
char *ptbl_getenv(const char *name)
{
	size_t length = 0;
	char *value = (char*)calloc( _MAX_ENV ,sizeof(char) );
	if (value == NULL) {
		fprintf(stderr,"ptbl_getenv(-):malloc(_MAX_ENV) failure\n");
		return NULL;
	}
#ifdef _WIN32
	{ // for vc2010
	 errno_t err_no = getenv_s(&length, value, _MAX_ENV, name);
	 if (err_no != 0) {
		fprintf(stderr,"getenv_s(,,,%s) returned err_no (%d)\n"
			,name ,err_no);
		free(value);
		return NULL;
	 }
	} // for vc2010
	if ((length <= 0) || (length >= _MAX_ENV)) {
		fprintf(stderr,"getenv_s(,,,%s) got a bad length (%d)\n"
			,name ,length);
		free(value);
		return NULL;
	}
#else
	const char* env_ptr = getenv(name);
	if (env_ptr == NULL) {
		fprintf(stderr,"getenv(%s) returned NULL\n", name);
		free(value);
		return NULL;
	}
	length = strlen(env_ptr);
	if ((length <= 0) || (length >= _MAX_ENV)) {
		fprintf(stderr,"getenv(%s) got a bad length (%d)\n"
			,name ,length);
		free(value);
		return NULL;
	}
	strncpy( value ,env_ptr ,length );
#endif
	value[length] = '\0';
	return value;
}

