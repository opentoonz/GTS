#include "ptbl_returncode.h"
#include "pri.h"
#include "tga.h"
#include "tga_stat.h"

int tga_image_write( void *vp_image, long l_width, long l_height, long l_channels, long l_bytes, int i_rle_sw, char *cp_fname, int i_mv_sw, int i_pv_sw, int i_cv_sw )
{
	unsigned char	*ucp_;
	long	yy;
	TGA_WRITE  t_write;

	/* Method and Parameter表示 */
	if ((ON == i_mv_sw) || (ON == i_pv_sw)) {
		pri_funct_msg_ttvr( "Write %s",cp_fname );
	}

	/* 画像用ヘッダー初期化 */
	tga_write_init( &t_write );

	/* 画像用ヘッダー初期値設定 */
	if (OK != tga_write_setup_header(
		(short)l_width,
		(short)l_height,
		(short)l_channels,
		(short)l_bytes,
		i_rle_sw, &(t_write.t_tga_file_header) )
	) {
		pri_funct_err_bttvr(
	 "Error : tga_write_setup_header(-) returns NG." );
		return NG;
	}

	/* Parameter表示 */
	if (ON == i_pv_sw) {
		tga_stat_for_pv( &(t_write.t_tga_file_header) );
	}

	/* ファイル開く、一時バッファの確保 */
	if (OK != tga_write_open( cp_fname, &t_write )) {
		pri_funct_err_bttvr(
			"Error : tga_write_open(%s,) returns NG.",
			cp_fname);
		tga_write_close( &t_write );
		return NG;
	}

	/* カウントダウン表示始め */
	if (ON == i_cv_sw) { pri_funct_cv_start( l_height ); }

	ucp_ = (unsigned char *)vp_image;

	for ( yy = 0L; yy < l_height; ++yy ) {
		/* カウントダウン表示中 */
		if (ON == i_cv_sw) { pri_funct_cv_run(yy); }

		if (NG == tga_write_scanline( yy, ucp_, &t_write )) {
			pri_funct_err_bttvr(
		"Warning: tga_write_scanline(%ld,,) returns NG.",
				yy );
			(void)fflush(stderr);
			tga_write_close( &t_write );
			return NG;
		}
		ucp_ += l_width * l_channels * 1;
	}

	/* カウントダウン表示終了 */
	if (ON == i_cv_sw) { pri_funct_cv_end(); }

	tga_write_close( &t_write );

	return OK;
}
