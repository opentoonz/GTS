#include <stdio.h>
#include <string.h>	/* memcpy() */
#include <assert.h>

#include "ptbl_returncode.h"
#include "pri.h"
#include "iip_rot90.h"

int iip_rot90::set_canvas( void )
{
	/* 画像メモリは独立していなければいけません */
	if (OK != this->mem_alloc_canvas()) {
		pri_funct_err_bttvr(
	 "Error : this->mem_alloc_canvas() returns NG." );
		return NG;
	}

	return OK;
}

/* 元サイズ(w,h,c,type)を設定してから実行(rot_canvas_size())すること */
void iip_rot90::rot_canvas_size( void )
{
	long	l_val;

	switch (this->_e_clockwork) {
	case IIP_ROT_CLOCKWORK_000:
		break;
	case IIP_ROT_CLOCKWORK_090:
		l_val = this->get_l_width();
		this->set_l_width( this->get_l_height() );
		this->set_l_height( l_val );
		break;
	case IIP_ROT_CLOCKWORK_180:
		break;
	case IIP_ROT_CLOCKWORK_270:
		l_val = this->get_l_width();
		this->set_l_width( this->get_l_height() );
		this->set_l_height( l_val );
		break;
	}
}

void iip_rot90::exec( void )
{
	iip_canvas	*clpp;

	clpp = this->get_clp_parent();

	/*
	ユーザーによるノーアクションの指定、つまりゼロ度回転
	の時は処理せず、親をコピーする */
	if (IIP_ROT_CLOCKWORK_000 == this->_e_clockwork) {
		(void)memcpy(
			this->get_vp_canvas(),
			clpp->get_vp_canvas(),
			this->get_l_height() *
			this->get_l_channels() *
			this->get_l_scanline_channel_bytes() );
		/* Method表示 */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
		"%s : no rotation, then copy from parent canvas",
				this->get_ccp_object_name_of_mv()
			);
		}
		return;
	}

	/* Method表示 */
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr(
			"%s : execute",
			this->get_ccp_object_name_of_mv()
		);
	}

	/* Parameter表示 */
	if (ON == this->get_i_pv_sw()) {
		switch (this->_e_clockwork) {
		case IIP_ROT_CLOCKWORK_000:
			/* 動作上ここには来ないが、
			warning表示を止めるため記述 */
			break;
		case IIP_ROT_CLOCKWORK_090:
		 pri_funct_msg_ttvr( " clockwork 90 degree" ); break;
		case IIP_ROT_CLOCKWORK_180:
		 pri_funct_msg_ttvr( " clockwork 180 degree" ); break;
		case IIP_ROT_CLOCKWORK_270:
		 pri_funct_msg_ttvr( " clockwork 270 degree" ); break;
		}
	}

	/* カウントダウン表示始め */
	if (ON == this->get_i_cv_sw()) {
		pri_funct_cv_start(this->get_l_height());
	}

	switch ( this->cl_ch_info.get_e_ch_num_type() ) {
	case E_CH_NUM_UCHAR:
		this->_exec_uchar(
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			(unsigned char *)clpp->get_vp_canvas(),
			(unsigned char *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_USHRT:
		this->_exec_ushrt(
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			(unsigned short *)clpp->get_vp_canvas(),
			(unsigned short *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_ULONG:
		this->_exec_ulong(
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			(unsigned long *)clpp->get_vp_canvas(),
			(unsigned long *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_DOUBL:
		this->_exec_doubl(
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			(double *)clpp->get_vp_canvas(),
			(double *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_BITBW:
		this->_exec_bitbw(
			this->get_l_width(),
			this->get_l_height(),
			//this->get_l_channels(),
			clpp->get_l_scanline_channel_bytes(),
			(unsigned char *)clpp->get_vp_canvas(),
			this->get_l_scanline_channel_bytes(),
			(unsigned char *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	/* カウントダウン表示終了 */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_end(); }
}
