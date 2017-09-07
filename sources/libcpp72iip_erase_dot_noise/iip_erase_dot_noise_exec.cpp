#include <assert.h>

#include "ptbl_returncode.h"
#include "pri.h"
#include "iip_erase_dot_noise.h"

/* 親のカンバスも自分のカンバスも必要、また同じ大きさであること */
void iip_erase_dot_noise::exec( void )
{
	iip_canvas	*clpp;

	clpp = this->get_clp_parent();

	/*
	 * 処理のためのデータチェック
	 */

	/* 親が必要 */
	assert(NULL != clpp);

	/* 親が画像をもっていること */
	assert(NULL != clpp->get_vp_canvas());

	/* 親と同じサイズであること */
	assert(this->get_l_width() == clpp->get_l_width());
	assert(this->get_l_height() == clpp->get_l_height());
	assert(this->get_l_channels() == clpp->get_l_channels());
	assert(this->cl_ch_info.get_l_bytes() ==
		clpp->cl_ch_info.get_l_bytes());

	/* channel数は3(RGB)か4(RGBA) */
	assert(SZ_RGB <= this->get_l_channels());

	/* channel毎のサイズは(uchar,ushrt,ulong,double)のみ */
	assert(E_CH_NUM_BITBW != this->cl_ch_info.get_e_ch_num_type());

	/* 処理エリアの確認、実際の画像をはみだしたらだめ */
	assert( 0L <= this->area_xpos_ );
	assert( 0L <= this->area_ypos_ );
	assert( (this->area_xpos_ + this->area_xsize_)
		<= this->get_l_width() );
	assert(	(this->area_ypos_ + this->area_ysize_)
		<= this->get_l_height() );

	/*
	 * 処理
	 */

	/* Method表示 */
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr(
			"%s : execute",
			this->get_ccp_object_name_of_mv()
		);
	}

	/* Parameter表示 */
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
			" sampling %s",
			this->cl_ch_info.get_cp_ch_num_type()
		);
		pri_funct_msg_ttvr(
			" data w %ld h %ld",
			this->get_l_width(),
			this->get_l_height()
		);
		pri_funct_msg_ttvr(
			" area x %ld y %ld",
			this->area_xpos_,
			this->area_ypos_
		);
		pri_funct_msg_ttvr(
			" area w %ld h %ld",
			this->area_xsize_,
			this->area_ysize_
		);
	}

	/* カウントダウン表示始め */
	if (ON == this->get_i_cv_sw()) {
		pri_funct_cv_start( this->area_ysize_ );
	}

	switch (this->cl_ch_info.get_e_ch_num_type()) {
	case E_CH_NUM_UCHAR:
		this->_exec_uchar(
			this->get_l_width(),
			this->get_l_height(),
			this->area_xpos_,
			this->area_ypos_,
			this->area_xsize_,
			this->area_ysize_,
			this->get_l_channels(),
			(unsigned char *)clpp->get_vp_canvas(),
			(unsigned char *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_USHRT: break;
	case E_CH_NUM_ULONG: break;
	case E_CH_NUM_DOUBL: break;
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	/* カウントダウン表示終了 */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_end(); }
}
