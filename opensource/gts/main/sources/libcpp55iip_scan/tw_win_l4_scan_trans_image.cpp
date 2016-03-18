#include "pri.h"
#include "tw_win_l4_scan.h"

/* DIB(Device Independent Bitmap) */
void iip_scan::_trans_from_4bytes_threshold( long l_w, long l_h, long l_d_bits, unsigned char *ucharp_dib, unsigned char *ucharp_canvas )
{
	long	l_scanline;
	long	xx,yy;
	long	l_d, l_w_bytes;
	unsigned char *ucharp_dib_x;

	l_d = l_d_bits/8;

	/* DIP画像は左下原点、OpenGLも左下原点なのでそのままコピー */
	switch (l_d_bits) {
	case 1:
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"BW copy from DIP to OpenGLimage"
			);
		}
		/* dib imageの各ラインは4バイト境界にそろっている */
		l_w_bytes = l_w/8 + ((l_w%8)?1:0);
		l_scanline = l_w_bytes + ((4-(l_w_bytes%4)) % 4);

		if (ON == this->get_i_pv_sw()) {
			pri_funct_msg_ttvr(
				" w %ld h %ld  dib_w %ld  ogl_w %ld",
				l_w,l_h,l_scanline,l_w_bytes
			);
		}

		for (yy = 0L; yy < l_h; ++yy) {
		 for (xx = 0L; xx < l_w_bytes; ++xx) {
			ucharp_canvas[xx] = ucharp_dib[xx];
		 }
		 ucharp_dib += l_scanline;
		 ucharp_canvas += l_w_bytes;
		}
		break;
	case 8:
	case 24:
	case 32:
		/* dib imageの各ラインは4バイト境界にそろっている */
		l_scanline = l_w*l_d + ((4-((l_w*l_d)%4)) % 4);

		for (yy = 0L; yy < l_h; ++yy) {
		 ucharp_dib_x = ucharp_dib;
		 for (xx = 0L; xx < l_w; ++xx) {
			if (1 == l_d) {
				ucharp_canvas[0] = ucharp_dib_x[0];
			} else if (3 == l_d) {
				ucharp_canvas[0] = ucharp_dib_x[2];
				ucharp_canvas[1] = ucharp_dib_x[1];
				ucharp_canvas[2] = ucharp_dib_x[0];
			} else if (4 == l_d) {
				ucharp_canvas[0] = ucharp_dib_x[1];
				ucharp_canvas[1] = ucharp_dib_x[2];
				ucharp_canvas[2] = ucharp_dib_x[3];
				ucharp_canvas[3] = ucharp_dib_x[0];
			}
			ucharp_dib_x += l_d;
			ucharp_canvas += l_d;
		 }
		 ucharp_dib += l_scanline;
		}
		break;
	}
}

/*--------------------------------------------------------*/

/* exec(-)を使う時はバーボーズとファイル名はすでに設定してあること */
int iip_scan::_trans_image( BITMAPINFO *p_dib_bitmapinfo, iip_canvas *clp_canvas )
{
	BITMAPINFOHEADER *tp_bmih;
	unsigned char *ucp_image_top=0;

	tp_bmih = &(p_dib_bitmapinfo->bmiHeader);

	/* ヘッダー情報のチェック */
	if (tp_bmih->biHeight < 0) {
		pri_funct_err_bttvr(
 "Warning : tp_bmih->biHeight<%d> is munis, not support.",
	    tp_bmih->biHeight);
	}
	if (1 != tp_bmih->biPlanes) {
		pri_funct_err_bttvr(
      "Warning : tp_bmih->biPlanes<%d> is not 1, not support",
		 tp_bmih->biPlanes);
	}
	/***if (0 != tp_bmih->biCompression) {***/
	if (BI_RGB != tp_bmih->biCompression) {
		pri_funct_err_bttvr(
      "Warning : tp_bmih->biCompression<%d> is not zero, not support",
		 tp_bmih->biCompression);
	}
/*****
biSizeImageはgtsソースコードで使っていない
rgbスキャンではゼロ以外が返るのでWarningやめる
	if (0 != tp_bmih->biSizeImage) {
		pri_funct_err_bttvr(
      "Warning : tp_bmih->biSizeImage<%d> is not zero, not support",
		 tp_bmih->biSizeImage);
	}******/

	/* 画像の大きさ、その他もろもろ設定して... */
	clp_canvas->set_i_mv_sw(  this->get_i_mv_sw() );
	clp_canvas->set_i_pv_sw(  this->get_i_pv_sw() );
	clp_canvas->set_i_cv_sw(  this->get_i_cv_sw() );
	clp_canvas->set_l_width(  tp_bmih->biWidth );
	clp_canvas->set_l_height( tp_bmih->biHeight );
	switch (tp_bmih->biBitCount) {
	case 1:
		clp_canvas->set_l_channels( 1L );
		clp_canvas->cl_ch_info.set_e_ch_num_type(
			E_CH_NUM_BITBW );
#if defined _WIN64
		ucp_image_top = (unsigned char *)tp_bmih+
			tp_bmih->biSize +
			sizeof(RGBQUAD) * (1i64<<tp_bmih->biBitCount);
#else
		ucp_image_top = (unsigned char *)tp_bmih+
			tp_bmih->biSize +
			sizeof(RGBQUAD) * (1<<tp_bmih->biBitCount);
#endif
/***		{
		unsigned char *tmpptr = (unsigned char *)tp_bmih;
		ucp_image_top = &tmpptr[tp_bmih->biSize +
			sizeof(RGBQUAD) * (1i64<<tp_bmih->biBitCount)];
		}***/
		break;
	case 4:
		pri_funct_err_bttvr(
		"Error : tp_bmih->biBitCount<%d> is not support.",
			 tp_bmih->biBitCount);
		return NG;
		break;
	case 8:
		clp_canvas->set_l_channels( tp_bmih->biBitCount/8 );
		clp_canvas->cl_ch_info.set_e_ch_num_type(
			E_CH_NUM_UCHAR );
#if defined _WIN64
		ucp_image_top = (unsigned char *)tp_bmih+
			tp_bmih->biSize +
			sizeof(RGBQUAD) * (1i64<<tp_bmih->biBitCount);
#else
		ucp_image_top = (unsigned char *)tp_bmih+
			tp_bmih->biSize +
			sizeof(RGBQUAD) * (1<<tp_bmih->biBitCount);
#endif
/***		{
		unsigned char *tmpptr = (unsigned char *)tp_bmih;
		ucp_image_top = &tmpptr[tp_bmih->biSize +
			sizeof(RGBQUAD) * (1i64<<tp_bmih->biBitCount)];
		}***/
		break;
	case 16:
		pri_funct_err_bttvr(
		"Error : tp_bmih->biBitCount<%d> is not support.",
			 tp_bmih->biBitCount);
		return NG;
		break;
	case 24:
		clp_canvas->set_l_channels( tp_bmih->biBitCount/8 );
		clp_canvas->cl_ch_info.set_e_ch_num_type(
			E_CH_NUM_UCHAR );
		ucp_image_top =(unsigned char *)tp_bmih+tp_bmih->biSize;
		break;
	case 32:
		clp_canvas->set_l_channels( tp_bmih->biBitCount/8 );
		clp_canvas->cl_ch_info.set_e_ch_num_type(
			E_CH_NUM_UCHAR );
		ucp_image_top =(unsigned char *)tp_bmih+tp_bmih->biSize;
		break;
	}

	/* ...メモリ確保 */
	if (OK != clp_canvas->mem_alloc_canvas()) {
		pri_funct_err_bttvr(
	 "Error : clp_canvas->mem_alloc_canvas() returns NG."
		);
		return NG;
	}

	/* 画像を移設 */
	this->_trans_from_4bytes_threshold(
		tp_bmih->biWidth,
		tp_bmih->biHeight,
		tp_bmih->biBitCount,
		ucp_image_top,
		(unsigned char *)(clp_canvas->get_vp_canvas())
	);

	return OK;
}
