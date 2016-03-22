#include "ptbl_returncode.h"
#include "pri.h"

#include "tga.h"

int tga_write_close( TGA_WRITE *tp_write )
{
	/* ファイルを閉じる */
	if (OK != bwrite_close( &(tp_write->t_bwrite) )) {
		pri_funct_err_bttvr(
	 "Error : bwrite_close(-) returns NG." );
		return NG;
	}
	return OK;
}
