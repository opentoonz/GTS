#if defined _WIN32
# include <direct.h>
#else
# include <sys/stat.h>
# include <sys/types.h>
#endif
#include "ptbl_funct.h"

/* ディレクトリを１個作成する(戻り値 0:成功,-1:失敗) */
int ptbl_mkdir( const char *cp_dirpath )
{
#if defined _WIN32
	return _mkdir( cp_dirpath );
#else
	return mkdir( cp_dirpath, 0777 );
#endif
}

