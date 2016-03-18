#include <stdlib.h>

#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"
#include "tif_image_rw.h"
#include "tif_stat.h"

static void *_tif_image_read( TIF_IMAGE_RW *tp_read, long *lp_width, long *lp_height, long *lp_channels, long *lp_bytes, long *lp_bits, double *dp_dpi_x, double *dp_dpi_y, long *lp_tile_width, long *lp_tile_height, long *lp_how_to_compression, long *lp_orientation, int i_mv_sw, int i_pv_sw, int i_cv_sw )
{
	int	i_reverse_sw;
	void	*vp_image;


	/* ヘッダー情報を受け取る */
	*lp_width    = tp_read->ui32_image_width;
	*lp_height   = tp_read->ui32_image_length;
	*lp_channels = tp_read->ui16_samples_per_pixel;
	*lp_bits     = tp_read->ui16_bits_per_sample;
	*lp_bytes    = tp_read->ui16_bits_per_sample/8;

	/* スキャンラインフォーマットのとき */
	if (0 == tp_read->i_tile_sw) {
		*lp_tile_width  = 0;
		*lp_tile_height = 0;
	}
	/* タイルフォーマットである */
	else {
		*lp_tile_width  = tp_read->ui32_tile_width;
		*lp_tile_height = tp_read->ui32_tile_length;
	}

	*dp_dpi_x = tp_read->f_dpi_x;
	*dp_dpi_y = tp_read->f_dpi_y;
	*lp_how_to_compression = tp_read->ui16_compression;
	*lp_orientation = tp_read->ui16_orientation;

	/**************************************************/

	/* 上下の判別
		Ｘウインドウ用のオーダーのときは
		上下反転して読み込む
		BOT... is order
		TOP... is reverse
	*/
	i_reverse_sw = tif_read_get_reverse_sw( tp_read );

	/* 白黒２値画像のとき別の読み込み処理 */
	if (1 == tp_read->ui16_bits_per_sample) {
		return (void *)tif_bw_read(
			tp_read, i_reverse_sw, i_pv_sw );
	}

	/* Method and Parameter表示 */
	if ((ON == i_mv_sw) || (ON == i_pv_sw)) {
		pri_funct_msg_ttvr(
		"Alloc. read(tif) %d bytes(%d x %d x %d x %d(%d bits))",
			(*lp_width) *
			(*lp_height) *
			(*lp_channels) *
			(*lp_bytes),

			(*lp_width),
			(*lp_height),
			(*lp_channels),
			(*lp_bytes),
			(*lp_bits)
		);
	}

	/* OpenGLで表示用の画像バッファ確保 */
	vp_image = calloc(
		(*lp_width) *
		(*lp_height) *
		(*lp_channels),
		(*lp_bytes)
	);
	if (NULL == vp_image) {
		pri_funct_err_bttvr(
		"Error : calloc(%u*%u*%u,%u) returns NULL.",
			(*lp_width),
			(*lp_height),
			(*lp_channels),
			(*lp_bytes) );
		return NULL;
	}

	/**************************************************/

	/* スキャンライン読み込み */
	if (0 == (*lp_tile_width)) {
		if (OK != tif_read_sca_all(
			tp_read,
			vp_image,
			(uint32_t)(*lp_width),
			(uint32_t)(*lp_height),

			(uint16_t)(*lp_channels),
			(uint16_t)(*lp_bytes),

			i_reverse_sw,
 			i_cv_sw
		)) {
			pri_funct_err_bttvr(
		"Error : tif_read_sca_all(-) returns NG." );
			free( vp_image );
			return NULL;
		}
	}
	/* タイル読み込み */
	else {
		if (OK != tif_read_til_all(
			tp_read,
			vp_image,
			(uint32_t)(*lp_width),
			(uint32_t)(*lp_height),
			(uint32_t)(*lp_tile_width),
			(uint32_t)(*lp_tile_height),

			(uint16_t)(*lp_channels),
			(uint16_t)(*lp_bytes),

			i_reverse_sw,
 			i_cv_sw
		)) {
			pri_funct_err_bttvr(
		 "Error : tif_read_til_all(-) returns NG." );
			free( vp_image );
			return NULL;
		}
	}

	return vp_image;
}
void *tif_image_read(
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
long *lp_orientation,
int i_mv_sw,
int i_pv_sw,
int i_cv_sw )
{
	void	*vp_image;
	TIF_IMAGE_RW	t_read;

	/* ヘッダー初期化 */
	tif_init_rw_header( &t_read );

	/* Method and Parameter表示 */
	if ((ON == i_mv_sw) || (ON == i_pv_sw)) {
		pri_funct_msg_ttvr( "Read %s",cp_fname );
	}

	/* ファイルを開く */
	if (OK != tif_read_open( cp_fname, &t_read )) {
		pri_funct_err_bttvr(
			"Error : tif_read_open(-) returns NG.");
		return NULL;
	}

	/* Parameter表示 */
	if (ON == i_pv_sw) {
		tif_stat_for_pv( &t_read );
	}

	/* ファイルを読む */
	vp_image = _tif_image_read(
		&t_read,
		lp_width,
		lp_height,
		lp_channels,
		lp_bytes,
		lp_bits,
		dp_dpi_x,
		dp_dpi_y,
		lp_tile_width,
		lp_tile_height,
		lp_how_to_compression,
		lp_orientation,
		i_mv_sw,
		i_pv_sw,
		i_cv_sw
	);
	if (NULL == vp_image) {
		pri_funct_err_bttvr(
		"Error : _tif_image_read(-) returns NG." );
	}

	/* 正常でもエラーでもファイルを閉じる */
	tif_read_close( &t_read );

	return vp_image;
}

