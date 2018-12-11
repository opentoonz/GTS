// #include <GL/glut.h>
#include "pri.h"
#include "iip_opengl_l2data.h"

int iip_opengl_l2data::set_imagedata( iip_canvas *clp_parent )
{
	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l2data::set_imagedata(-)" );
	}

	/*
	 * 親子接続し、関係を設定する
	 */

	/*  clp_parent - 元画像
	    +-- cl_iip_prec 精度変換
		+-- cl_iip_chan RGB(A)チャンネル表示専用
		+-- cl_iip_view OpenGL画像表示機能
	*/
	this->cl_iip_prec.set_clp_parent( clp_parent );
	this->cl_iip_chan.set_clp_parent(
		&(this->cl_iip_prec) );
	this->cl_iip_view.set_clp_parent(
		&(this->cl_iip_prec) );

	/*
	 * 親から子へ画像の大きさをセット
	 */

	this->cl_iip_prec.set_canvas_size( clp_parent );

	/* 以下の精度の場合は、表示用の精度に変更する */
	switch(this->cl_iip_prec.cl_ch_info.get_e_ch_num_type()){
	case E_CH_NUM_USHRT:
	case E_CH_NUM_ULONG:
	case E_CH_NUM_FLOAT:
	case E_CH_NUM_DOUBL:
	case E_CH_NUM_FLOAT:
		this->cl_iip_prec.cl_ch_info.set_e_ch_num_type(
			E_CH_NUM_UCHAR);
		break;
	case E_CH_NUM_BITBW:
		if (ON == this->_i_bw_use_uchar_sw) {
			this->cl_iip_prec.cl_ch_info.set_e_ch_num_type(
				E_CH_NUM_UCHAR);
		}
		break;
	case E_CH_NUM_EMPTY:
	case E_CH_NUM_UCHAR:
		break;
	}

	this->cl_iip_chan.set_canvas_size(
		&(this->cl_iip_prec) );
	this->cl_iip_view.set_canvas_size(
		&(this->cl_iip_prec) );

	/* 切抜きエリアを(画像の大きさに)初期設定 */
	this->cl_iip_view.set_crop_full_image();

	/*
	 * 画像カンバスの準備(メモリ確保あるいは参照)
	 */

	if (OK != this->cl_iip_prec.set_canvas()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_prec.set_canvas() returns NG" );
		return NG;
        }
	/* RGB(A)のときだけ、channel毎表示用メモリが必要 */
	if (3L <= this->cl_iip_chan.get_l_channels()) {
	 /* channel毎表示メモリを確保 */
	 if (OK != this->cl_iip_chan.mem_alloc_canvas()) {
		pri_funct_err_bttvr(
	  "Error : this->cl_iip_chan.mem_alloc_canvas() returns NG" );
		return NG;
         }
	 /* channel毎のメモリを表示classへ登録する */
/* 2017-05-09 使わないためコメントアウト　あとで全体refactoringで削除する
	 this->cl_iip_view.set_ucp_rrggbbaa(
	  (unsigned char *)(this->cl_iip_chan.get_vp_canvas())
	 );
*/
	}

	/*
	this->cl_iip_viewは
	this->cl_iip_prec(親)を参照するのみ
	*/
	this->cl_iip_view.set_vp_reference_canvas(
		this->cl_iip_prec.get_vp_canvas()
	);

	/*
	 * 画像を作成、あるいは参照
	 */

	this->cl_iip_prec.exec();

	/* RGB(A)のときだけ、channel毎の画像を作成 */
	if (3L <= this->cl_iip_chan.get_l_channels()) {
	 this->_from_uchar_rgbargba_to_rrggbbaa(
		(unsigned char *)
		this->cl_iip_prec.get_vp_canvas(),

		this->cl_iip_prec.get_l_width(),
		this->cl_iip_prec.get_l_height(),
		this->cl_iip_prec.get_l_channels(),

		(unsigned char *)
		this->cl_iip_chan.get_vp_canvas()
	 );
	}

	return OK;
}

/*--------------------------------------------------------*/

/* unsigned charサンプリングのRGB(A)画像を
	RGB(A)RGB(A)RGB(A)...から、
	RRR...GGG..BBB..(AAA..)に変換
*/
void iip_opengl_l2data::_from_uchar_rgbargba_to_rrggbbaa( unsigned char *ucharp_rgbargba, long l_w, long l_h, long l_ch, unsigned char *ucharp_rrggbbaa )
{
	long	xx,yy,zz, ii;
	unsigned char *ucharp_ch[SZ_RGBA];

	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr(
			"iip_opengl_l2data::_copy_channels(-)" );
	}

	for (ii = CH_RED; ii < l_ch; ++ii) {
		ucharp_ch[ii] =
			(unsigned char *)(ucharp_rrggbbaa +
			ii * l_w * l_h * sizeof(unsigned char));
	}
	for (yy = 0L; yy < l_h; ++yy) {
	for (xx = 0L; xx < l_w; ++xx) {
	for (zz = 0L; zz < l_ch; ++zz, ++ucharp_rgbargba) {
		*(ucharp_ch[zz] + yy * l_w + xx) = *ucharp_rgbargba;
	}
	}
	}
}
