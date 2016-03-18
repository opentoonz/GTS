#include "pri.h"
#include "iip_scale_by_subpixel.h"

/* "子の解像度×subpixel"よりも親の解像度のほうが高い場合
pixel抜けが出来てしまうので絵としてよくない */
void iip_scale_by_subpixel::exec( void )
{
	iip_canvas *clpp;

	clpp = this->get_clp_parent();
	/* 親がなければ処理できない */
	if (NULL == clpp) {
		pri_funct_err_bttvr(
			"Error : this->get_clp_parent() returns NULL");
		return;
	}

	/* 多きさが変わらないときはコピーか、なにもしない */
	if (	(clpp->get_l_width() == this->get_l_width()) &&
		(clpp->get_l_height() == this->get_l_height()) &&
		(clpp->get_l_channels() == this->get_l_channels()) &&
		(clpp->cl_ch_info.get_e_ch_num_type()
			== this->cl_ch_info.get_e_ch_num_type())
	) {
		/*
		(親と同じ大きさで)
		親がいて、
		かつ、親が画像をもっていて、
		かつ、自分が独立したカンバスメモリをもっているなら、
		親の画像を処理して自分の画像にする
		(自分のカンバスに複写して処理する) */
		this->copy_image_from_parent(
			this->get_ccp_object_name_of_mv()
		);

		return;
	}

	/* インクリメンタル値配列設定 */
	this->_lp_width[this->get_l_width() *
			this->_l_x_subpixel_division - 1] = '\0';

	this->_calcu_bresenham(
		clpp->get_l_width() - 1L,
		this->get_l_width()*this->_l_x_subpixel_division - 1L,
		this->_lp_width,
		clpp->get_l_channels()
	);
	this->_lp_height[this->get_l_height() *
			 this->_l_y_subpixel_division - 1] = '\0';
	this->_calcu_bresenham(
		clpp->get_l_height() - 1L,
		this->get_l_height()*this->_l_y_subpixel_division - 1L,
		this->_lp_height,
		clpp->get_l_width() * clpp->get_l_channels()
	);

	/* ユーザーへの実行メッセージ */
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr(
			"%s : execute",
			this->get_ccp_object_name_of_mv()
		);
	}
	/* ユーザーへのパラメータ値メッセージ */
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
			" in  w %ld  h %ld c %ld  b %ld",
			clpp->get_l_width(),
			clpp->get_l_height(),
			clpp->get_l_channels(),
			clpp->cl_ch_info.get_l_bytes()
		);
		pri_funct_msg_ttvr(
			" out w %ld  h %ld  xd %ld yd %ld",
			this->get_l_width(),
			this->get_l_height(),
			this->_l_x_subpixel_division,
			this->_l_y_subpixel_division
		);
		if (
		(this->get_l_width()*this->_l_x_subpixel_division) <
		clpp->get_l_width()
		) {
			pri_funct_msg_ttvr(
			" Caution! in_w is bgger than out_w x out_xd");
		}
		if (
		(this->get_l_height()*this->_l_y_subpixel_division) <
		clpp->get_l_height()
		) {
			pri_funct_msg_ttvr(
			" Caution! in_h is bgger than out_h x out_yd");
		}
	}

	/* カウントダウン表示始め */
	if (ON == this->get_i_cv_sw()) {
		pri_funct_cv_start( this->get_l_height() );
	}

	switch (this->cl_ch_info.get_e_ch_num_type()) {
	/* char byteサンプリングのデータの処理 */
	case E_CH_NUM_UCHAR:
		this->_exec_uchar(
			(unsigned char *)clpp->get_vp_canvas(),
			(unsigned char *)this->get_vp_canvas(),
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			this->_l_x_subpixel_division,
			this->_l_y_subpixel_division,
			this->_lp_width,
			this->_lp_height,
			this->_lp_scanline);
		break;
	/* short byteサンプリングのデータの処理 */
	case E_CH_NUM_USHRT:
		this->_exec_ushrt(
			(unsigned short *)clpp->get_vp_canvas(),
			(unsigned short *)this->get_vp_canvas(),
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			this->_l_x_subpixel_division,
			this->_l_y_subpixel_division,
			this->_lp_width,
			this->_lp_height,
			this->_lp_scanline);
		break;
	case E_CH_NUM_ULONG: break;
	case E_CH_NUM_DOUBL: break;
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	/* カウントダウン表示終了 */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_end(); }
}
