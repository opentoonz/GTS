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
	assert( 0L <= this->_l_area_xpos );
	assert( 0L <= this->_l_area_ypos );
	assert( (this->_l_area_xpos + this->_l_area_xsize)
		<= this->get_l_width() );
	assert(	(this->_l_area_ypos + this->_l_area_ysize)
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
			this->_l_area_xpos,
			this->_l_area_ypos
		);
		pri_funct_msg_ttvr(
			" area w %ld h %ld",
			this->_l_area_xsize,
			this->_l_area_ysize
		);
	}

	/* カウントダウン表示始め */
	if (ON == this->get_i_cv_sw()) {
		pri_funct_cv_start( this->_l_area_ysize );
	}

	switch (this->cl_ch_info.get_e_ch_num_type()) {
	case E_CH_NUM_UCHAR:
		this->_exec_uchar(
			this->get_l_width(),
			this->get_l_height(),
			this->_l_area_xpos,
			this->_l_area_ypos,
			this->_l_area_xsize,
			this->_l_area_ysize,
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
