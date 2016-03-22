#include <stdlib.h>	/* for calloc() */
#include <string.h>	/* for memcpy() */

#include "ptbl_funct.h"
#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"
#include "tif_stat.h"
#include "tif_image_rw.h"

static void _tif_image_write_body_byte_swap( uint8_t *ui8p_src, uint8_t *ui8p_tgt, uint32_t ui32_length, uint16_t ui16_bytes )
{
	uint32_t	ii;
	for (ii = 0; ii < ui32_length; ++ii) {
		ui8p_tgt[0] = ui8p_src[1];
		ui8p_tgt[1] = ui8p_src[0];

		ui8p_src += ui16_bytes;
		ui8p_tgt += ui16_bytes;
	}
}

static int _tif_image_write_body( TIF_IMAGE_RW *tp_write, uint8_t *ui8p_image, uint8_t *ui8p_buffer, uint32_t ui32_width, uint32_t ui32_height, uint16_t ui16_samples, uint16_t ui16_bytes, int i_byte_swap_mode, int i_cv_sw )
{
	int	i_cpu_is_little_endian,
		i_byte_swap_sw,
		i_yy;
	uint8_t	*ui8p_scanline;

	/* 2バイトサンプリングのデータで、
	   バイトスワップが必要なときのためのスイッチ */
	i_byte_swap_sw = OFF;
	if (2 == ui16_bytes) {
		i_cpu_is_little_endian = ptbl_cpu_is_little_endian();
		if (
		  ( i_cpu_is_little_endian && ('b'==i_byte_swap_mode))
		||(!i_cpu_is_little_endian && ('l'==i_byte_swap_mode))
		) {
			i_byte_swap_sw = ON;
		}
	}

	/* カウントダウン表示始め */
	if (ON == i_cv_sw) { pri_funct_cv_start( ui32_height ); }

	/* .tifファイルは、左上原点だが、
	   ui8p_imageデータは、左下が原点なので、上下反転する */
	ui8p_scanline = ui8p_image +
		ui32_width *
		(ui32_height-1) *
		ui16_samples *
		ui16_bytes;
	for ( i_yy = 0; i_yy < (int)ui32_height; ++i_yy ) {

		/* カウントダウン表示中 */
		if (ON == i_cv_sw) { pri_funct_cv_run(i_yy); }

		/* 2バイトサンプリングのデータで、
		バイトスワップが必要なとき */
		if (ON == i_byte_swap_sw) {
			_tif_image_write_body_byte_swap(
				ui8p_scanline,
				ui8p_buffer,
				ui32_width * ui16_samples,
				ui16_bytes );

		}
		/* ...でない時は、スワップせずコピーする */
		else {
			(void)memcpy(
				ui8p_buffer,
				ui8p_scanline,
				ui32_width * ui16_samples * ui16_bytes);
		}

		/* スキャンライン書き出し */
		if (NG == tif_write_scanline(
			i_yy, ui8p_buffer, tp_write
		)) {
			pri_funct_err_bttvr(
		 "Error : tif_write_scanline(%ld,,) returns NG.",
				i_yy );
			return NG;
		}
		/* 画像のスキャンライン位置を下(マイナス)へ移動する */
		ui8p_scanline -= ui32_width * ui16_samples * ui16_bytes;
	}

	/* カウントダウン表示終了 */
	if (ON == i_cv_sw) { pri_funct_cv_end(); }

	return OK;
}

/* l_channels is 3/4 */
/* l_bytes  is 2/1 */
/* d_dpi_x is 162.665 */
int tif_image_write( void *vp_image, long l_width, long l_height, long l_channels, long l_bytes, long l_bits, double d_dpi_x, double d_dpi_y, long l_how_to_compression, long l_lzw_prediction_scheme, long l_orientation, long l_byte_swap_mode, char *cp_fname, int i_mv_sw, int i_pv_sw, int i_cv_sw )
{
	int	i_ret;
	TIF_IMAGE_RW	t_write;

	/* 初期化 */
	tif_init_rw_header( &t_write );

	/* Method and Parameter表示 */
	if ((ON == i_mv_sw) || (ON == i_pv_sw)) {
		pri_funct_msg_ttvr( "Write %s",cp_fname );
	}

	/* ファイル開く */
	if (OK != tif_write_open(
		cp_fname, l_byte_swap_mode, &t_write
	) ) {
		pri_funct_err_bttvr(
			"Error : tif_write_open(-) returns NG." );
		tif_write_close( &t_write );
		return NG;
	}

	/* ヘッダー情報セット */
	if (OK != tif_write_header(
		(uint32_t)l_width,
		(uint32_t)l_height,
		(uint16_t)l_channels,
		(uint16_t)l_bits,
		(float)d_dpi_x,
		(float)d_dpi_y,
		(int)l_how_to_compression,
		(int)l_lzw_prediction_scheme,
		(uint16_t)l_orientation,
		&t_write
	) ) {
		pri_funct_err_bttvr(
			"Error : tif_write_header(-) returns NG." );
		tif_write_close( &t_write );
		return NG;
	}

	/* モノクロ２階調保存の場合 */
	if (1L == l_bits) {
		i_ret = tif_bw_write(
			l_width, l_height, vp_image, &t_write, i_pv_sw
		);
		tif_write_close( &t_write );
		return i_ret;
	}

	/* スキャンライン用バッファの確保 */
	t_write.vp_tile = (void *)calloc(
		l_width * l_channels, l_bytes );
	if (NULL == (t_write.vp_tile)) {
		pri_funct_err_bttvr(
			"Error : calloc(%ld x %ld,%ld) returns NULL.",
			l_width, l_channels, l_bytes );
		tif_write_close( &t_write );
		return NG;
	}

	/* Parameter表示 */
	if (ON == i_pv_sw) {
		tif_stat_for_pv( &t_write );
	}

	/* 画像の書き出し */
	if (OK != _tif_image_write_body(
		&t_write,
		(uint8_t *)vp_image,
		(uint8_t *)(t_write.vp_tile),
		(uint32_t)l_width,
		(uint32_t)l_height,
		(uint16_t)l_channels,
		(uint16_t)(l_bytes),
		(int)l_byte_swap_mode,
		i_cv_sw
	) ) {
		pri_funct_err_bttvr(
		"Error : _tif_image_write_body(-) returns NG." );
		tif_write_close( &t_write );
		return NG;
	}

	tif_write_close( &t_write );

	return OK;
}
