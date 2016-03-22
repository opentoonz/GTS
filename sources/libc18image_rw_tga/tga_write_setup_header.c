#include <string.h> /* for memset() */

#include "ptbl_returncode.h"
#include "pri.h"

#include "tga.h"

int tga_write_setup_header( short s_width, short s_height, short s_samples, short s_bytes, int i_rle_sw, TGA_FILE_HEADER *tp_header )
{
	if (s_samples < 3 || 4 < s_samples) {
		pri_funct_err_bttvr(
			"Error : s_samples<%d> is bad.", s_samples );
		return NG;
	}
	if (1 != s_bytes) {
		pri_funct_err_bttvr(
			"Error : s_bytes<%d> is bad.", s_bytes );
		return NG;
	}
	tp_header->uc_numid	= 0;
	tp_header->uc_maptyp	= 0;
	if (ON == i_rle_sw) {
	 /* 10 run_length encoded true_color image */
	 tp_header->uc_imgtyp	= 10;
	} else {
	 /*  2 uncompressed, true_color image      */
	 tp_header->uc_imgtyp	= 2;
	}
	tp_header->s_maporig	= 0;
	tp_header->s_mapsize	= 0;
	tp_header->uc_mapbits	= 0;
	tp_header->s_xorig	= 0;
	tp_header->s_yorig	= 0;
	tp_header->s_xsize	= s_width;
	tp_header->s_ysize	= s_height;

	/* 8bit X 3/4plane(RGB/RGBO) */
	tp_header->uc_pixsize	= (unsigned char)(8*s_samples);

	tp_header->uc_imgdes	= 8; /* ???? */
	
	return OK;
}

