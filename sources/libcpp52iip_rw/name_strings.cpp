#include <stdlib.h>	/* malloc(), free() */
#include <string.h>	/* strcpy() */
#include <assert.h>	/* assert() */
#include "ptbl_returncode.h"
#include "pri.h"
#include "name_strings.h"

void name_strings::_mem_free(void)
{
	if (NULL !=  this->_cp_name) {
		free(this->_cp_name);
		     this->_cp_name = NULL;
	}
}

int name_strings::set_name( const char *cp_name )
{
	/* 引数がNULLであってはならない */
	assert(NULL != cp_name);

	/* 名前バッファに名前があるなら、領域解放 */
	this->_mem_free();

	/* 新たな名前のバッファを確保 */
	this->_cp_name = (char *)malloc(
		sizeof(char) * (strlen(cp_name) + 1)
	);
	if (NULL == this->_cp_name) {
		pri_funct_err_bttvr(
		"Error : malloc(%d x %d) returns NULL.",
		sizeof(char), strlen( cp_name )+1 );
		return NG;
	}

	/* バッファを名前ポインタへセット */
	strcpy( this->_cp_name, cp_name );

	return OK;
}

