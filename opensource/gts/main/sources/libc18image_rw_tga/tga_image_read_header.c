#include <stdlib.h>

#include "ptbl_returncode.h"
#include "pri.h"

#include "tga.h"
#include "tga_image_rw.h"

int tga_image_read_header( char *cp_fname, long *lp_width, long *lp_height, long *lp_channels, long *lp_bytes )
{
	TGA_READ	t_read;

	/* ヘッダー全体初期化 */
	tga_read_init( &t_read );

	/* ファイル開く、へッダー情報を得る */
	if (OK != tga_read_open( cp_fname, &t_read )) {
		pri_funct_err_bttvr(
			"Error : tga_read_open(-) returns NG." );
		tga_read_close( &t_read );
		return NG;
	}
	*lp_width  = t_read.t_tga_file_header.s_xsize;
	*lp_height = t_read.t_tga_file_header.s_ysize;
	switch (t_read.t_tga_file_header.uc_pixsize) {
	case 32: *lp_channels = 4; break;
	case 24: *lp_channels = 3; break;
	case 16:
	case 15: *lp_channels = 3; break;
	}
	/* 1で固定 */
 	*lp_bytes = 1;

	/* メモリバッファを解放し、ファイル閉じる */
	tga_read_close( &t_read );

	return OK;
}
