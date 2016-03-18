#include "ptbl_returncode.h"
#include "pri.h"

#include "tga.h"

int tga_read_close( TGA_READ *tp_read )
{
	/* ファイルを閉じる */
	if (OK != bread_close( &(tp_read->t_bread) )) {
		pri_funct_err_bttvr(
	 "Error : bread_close(-) returns NG." );
		return NG;
	}
	return OK;
}
