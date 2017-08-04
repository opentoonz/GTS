#include <cassert>
#include <cstring>	// memcpy()
#include <iostream>	// std::cerr
#include <string>	// std::string
#include <sstream>	// std::ostringstream

#include "ptbl_returncode.h"
#include "pri.h"
#include "calcu_precision.h"
#include "iip_color_trace_hab.h"

/* 親のカンバスも自分のカンバスも必要、また同じ大きさであること */
void iip_color_trace_hab::exec( calcu_color_trace_base *clp_calcu_color_trace_hab )
{
	iip_canvas	*clpp;
	double	d_in_max_div;
	double	d_out_max_mul;
	calcu_precision cl_prec;

	clpp = this->get_clp_parent();

	/*
	 * 処理のためのデータチェック
	 */

	/* 親が必要 */
	assert(NULL != clpp);

	/* 親が画像をもっていること */
	assert(NULL != clpp->get_vp_canvas());

	/* 自分が独立したカンバスメモリをもっていること */
	assert(ON == this->get_i_must_be_free_self_sw());

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

	/* 2011-11-14 Assertion failed! here!!! */
	/******assert( (this->_l_area_xpos + this->_l_area_xsize)
		<= this->get_l_width() );******/
	/* 2011-11-14 tempolaly debug */
	if (	
		this->get_l_width() <
		(this->_l_area_xpos + this->_l_area_xsize)
	) {
		// log
std::string str;
str += "this->_l_area_xpos<";
{ std::ostringstream ost; ost<<this->_l_area_xpos; str+=ost.str(); }
str += "> + this->_l_area_xsize<";
{ std::ostringstream ost; ost<<this->_l_area_xsize; str+=ost.str(); }
str += "> <= this->get_l_width()<";
{ std::ostringstream ost; ost<<this->get_l_width(); str+=ost.str(); }
str += ">";
std::cerr << str << std::endl;

		this->_l_area_xsize =
			this->get_l_width() - this->_l_area_xpos;
	}

	/* 2011-11-04 Assertion failed! here!!! */
	/******assert(	(this->_l_area_ypos + this->_l_area_ysize)
		<= this->get_l_height() );******/
	/* 2011-11-04 tempolaly debug */
	if (	
		this->get_l_height() <
		(this->_l_area_ypos + this->_l_area_ysize)
	) {
		// log
std::string str;
str += "this->_l_area_ypos<";
{ std::ostringstream ost; ost<<this->_l_area_ypos; str+=ost.str(); }
str += "> + this->_l_area_ysize<";
{ std::ostringstream ost; ost<<this->_l_area_ysize; str+=ost.str(); }
str += "> <= this->get_l_height()<";
{ std::ostringstream ost; ost<<this->get_l_height(); str+=ost.str(); }
str += ">";
std::cerr << str << std::endl;

		this->_l_area_ysize =
			this->get_l_height() - this->_l_area_ypos;
	}

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

	/* 正規化値計算のための値 */
	d_in_max_div = (double)cl_prec.bytes_to_max(
		clpp->cl_ch_info.get_l_bytes());
	d_out_max_mul = cl_prec.max_to_double(cl_prec.bytes_to_max(
		this->cl_ch_info.get_l_bytes()));

	/* Parameter表示 */
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
			" sampling %s  in_max_div %.16g out_max_mul %.16g",
			this->cl_ch_info.get_cp_ch_num_type(),
			d_in_max_div, d_out_max_mul
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
			d_in_max_div,
			clp_calcu_color_trace_hab,
			(unsigned char *)this->get_vp_canvas(),
			d_out_max_mul
		);
		break;
	case E_CH_NUM_USHRT:
		this->_exec_ushrt(
			this->get_l_width(),
			this->get_l_height(),
			this->_l_area_xpos,
			this->_l_area_ypos,
			this->_l_area_xsize,
			this->_l_area_ysize,
			this->get_l_channels(),
			(unsigned short *)clpp->get_vp_canvas(),
			d_in_max_div,
			clp_calcu_color_trace_hab,
			(unsigned short *)this->get_vp_canvas(),
			d_out_max_mul
		);
		break;
	case E_CH_NUM_ULONG:
		this->_exec_ulong(
			this->get_l_width(),
			this->get_l_height(),
			this->_l_area_xpos,
			this->_l_area_ypos,
			this->_l_area_xsize,
			this->_l_area_ysize,
			this->get_l_channels(),
			(unsigned long *)clpp->get_vp_canvas(),
			d_in_max_div,
			clp_calcu_color_trace_hab,
			(unsigned long *)this->get_vp_canvas(),
			d_out_max_mul
		);
		break;
	case E_CH_NUM_DOUBL:
		this->_exec_doubl(
			this->get_l_width(),
			this->get_l_height(),
			this->_l_area_xpos,
			this->_l_area_ypos,
			this->_l_area_xsize,
			this->_l_area_ysize,
			this->get_l_channels(),
			(double *)clpp->get_vp_canvas(),
			clp_calcu_color_trace_hab,
			(double *)this->get_vp_canvas()
		);
		break;
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	/* カウントダウン表示終了 */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_end(); }
}
