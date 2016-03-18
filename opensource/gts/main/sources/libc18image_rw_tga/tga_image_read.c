#include <stdlib.h>

#include "ptbl_returncode.h"
#include "pri.h"

#include "tga.h"
#include "tga_stat.h"
#include "tga_image_rw.h"

void *tga_image_read( char *cp_fname, long *lp_width, long *lp_height, long *lp_channels, long *lp_bytes, int i_mv_sw, int i_pv_sw, int i_cv_sw )
{
	void	*vp_image;
	unsigned char	*ucp_image;
	long	yy;
	TGA_READ	t_read;

	/* ヘッダー全体初期化 */
	tga_read_init( &t_read );

	/* Method and Parameter表示 */
	if ((ON == i_mv_sw) || (ON == i_pv_sw)) {
		pri_funct_msg_ttvr( "Read %s",cp_fname );
	}

	/* ファイル開く、へッダー情報を得る */
	if (OK != tga_read_open( cp_fname, &t_read )) {
		pri_funct_err_bttvr(
			"Error : tga_read_open(-) returns NG." );
		tga_read_close( &t_read );
		return NULL;
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

	/* Parameter表示 */
	if (ON == i_pv_sw) {
		tga_stat_for_pv( &(t_read.t_tga_file_header) );
	}

	/* Method and Parameter表示 */
	if ((ON == i_mv_sw) || (ON == i_pv_sw)) {
		pri_funct_msg_ttvr(
			"Alloc. read(tga) %d bytes(%d x %d x %d x %d)",
			(*lp_width) *
			(*lp_height) *
			(*lp_channels) *
			(*lp_bytes),

			(*lp_width),
			(*lp_height),
			(*lp_channels),
			(*lp_bytes)
		);
	}
	/* OpenGLで表示用の画像バッファ確保 */
	vp_image = calloc(
		(*lp_width) *
		(*lp_height) *
		(*lp_channels),
		(*lp_bytes) );
	if (NULL == vp_image) {
		pri_funct_err_bttvr(
	  "Error : calloc(%ldx%ldx%ld,%ld) returns NULL.",
			*lp_width,
			*lp_height,
			*lp_channels,
			*lp_bytes );
		tga_read_close( &t_read );
		return NULL;
	}

	/* カウントダウン表示始め */
	if (ON == i_cv_sw) { pri_funct_cv_start( *lp_height ); }

	ucp_image = (unsigned char *)vp_image;
	/* スキャンラインで読み込む */
	for ( yy = 0L; yy < (*lp_height); ++yy ) {

		/* カウントダウン表示中 */
		if (ON == i_cv_sw) { pri_funct_cv_run(yy); }

		if (OK != tga_read_scanline(
		&t_read, yy, (void *)ucp_image )) {
			pri_funct_err_bttvr(
	     "7Error : tga_read_scanline(,yy<%ld>,) returns NG.",
				yy );
			free( vp_image );
			tga_read_close( &t_read );
			return NULL;
		}
		ucp_image +=	(*lp_width) *
				(*lp_channels) *
				(*lp_bytes);
	}

	/* カウントダウン表示終了 */
	if (ON == i_cv_sw) { pri_funct_cv_end(); }

	/* メモリバッファを解放し、ファイル閉じる */
	tga_read_close( &t_read );

	return vp_image;
}
