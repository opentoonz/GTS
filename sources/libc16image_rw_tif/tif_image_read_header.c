#include "ptbl_returncode.h"
#include "pri.h"
#include "tif.h"
#include "tif_image_rw.h"

int tif_image_read_header(
char *cp_fname,
long *lp_width,
long *lp_height,
long *lp_channels,
long *lp_bytes,
long *lp_bits,
double *dp_dpi_x,
double *dp_dpi_y,
long *lp_tile_width,
long *lp_tile_height,
long *lp_how_to_compression,
long *lp_orientation )
{
	TIF_IMAGE_RW	t_read;

	/* ヘッダー初期化 */
	tif_init_rw_header( &t_read );

	/* ファイルを開く */
	if (OK != tif_read_open( cp_fname, &t_read )) {
		pri_funct_err_bttvr(
			"Error : tif_read_open(-) returns NG.");
		tif_read_close( &t_read );
		return NG;
	}

	/* ヘッダー情報を受け取る */
	*lp_width    = t_read.ui32_image_width; /* 幅 */
	*lp_height   = t_read.ui32_image_length; /* 高さ */
	*lp_channels = t_read.ui16_samples_per_pixel;
	*lp_bytes    = t_read.ui16_bits_per_sample/8;
	*lp_bits     = t_read.ui16_bits_per_sample;
	*dp_dpi_x = t_read.f_dpi_x;
	*dp_dpi_y = t_read.f_dpi_y;

	/* スキャンラインフォーマットのとき */
	if (0 == t_read.i_tile_sw) {
		*lp_tile_width  = 0;
		*lp_tile_height = 0;
	}
	/* タイルフォーマットである */
	else {
		*lp_tile_width  = t_read.ui32_tile_width;
		*lp_tile_height = t_read.ui32_tile_length;
	}

	*lp_how_to_compression = t_read.ui16_compression;
	*lp_orientation = t_read.ui16_orientation;

	/* ファイルを閉じる */
	tif_read_close( &t_read );

	return OK;
}

