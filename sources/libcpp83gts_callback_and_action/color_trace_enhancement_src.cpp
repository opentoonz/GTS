#include <FL/Fl.H>
#include "ptbl_returncode.h"
#include "pri.h"
#include "color_trace_enhancement.h"
#include "gts_gui.h"
#include "gts_master.h"

int color_trace_enhancement::_src_get_p_hh_valinp( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Value_Input **pp_min, Fl_Value_Input **pp_max )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		*pp_min = cl_gts_gui.valinp_color_trace_01_src_hh_min;
		*pp_max = cl_gts_gui.valinp_color_trace_01_src_hh_max; break;
	case E_COLOR_TRACE_HAB_02:
		*pp_min = cl_gts_gui.valinp_color_trace_02_src_hh_min;
		*pp_max = cl_gts_gui.valinp_color_trace_02_src_hh_max; break;
	case E_COLOR_TRACE_HAB_03:
		*pp_min = cl_gts_gui.valinp_color_trace_03_src_hh_min;
		*pp_max = cl_gts_gui.valinp_color_trace_03_src_hh_max; break;
	case E_COLOR_TRACE_HAB_04:
		*pp_min = cl_gts_gui.valinp_color_trace_04_src_hh_min;
		*pp_max = cl_gts_gui.valinp_color_trace_04_src_hh_max; break;
	case E_COLOR_TRACE_HAB_05:
		*pp_min = cl_gts_gui.valinp_color_trace_05_src_hh_min;
		*pp_max = cl_gts_gui.valinp_color_trace_05_src_hh_max; break;
	case E_COLOR_TRACE_HAB_06:
		*pp_min = cl_gts_gui.valinp_color_trace_06_src_hh_min;
		*pp_max = cl_gts_gui.valinp_color_trace_06_src_hh_max; break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}
int color_trace_enhancement::_src_get_p_aa_valinp( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Value_Input **pp_min, Fl_Value_Input **pp_max )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		*pp_min = cl_gts_gui.valinp_color_trace_01_src_aa_min;
		*pp_max = cl_gts_gui.valinp_color_trace_01_src_aa_max; break;
	case E_COLOR_TRACE_HAB_02:
		*pp_min = cl_gts_gui.valinp_color_trace_02_src_aa_min;
		*pp_max = cl_gts_gui.valinp_color_trace_02_src_aa_max; break;
	case E_COLOR_TRACE_HAB_03:
		*pp_min = cl_gts_gui.valinp_color_trace_03_src_aa_min;
		*pp_max = cl_gts_gui.valinp_color_trace_03_src_aa_max; break;
	case E_COLOR_TRACE_HAB_04:
		*pp_min = cl_gts_gui.valinp_color_trace_04_src_aa_min;
		*pp_max = cl_gts_gui.valinp_color_trace_04_src_aa_max; break;
	case E_COLOR_TRACE_HAB_05:
		*pp_min = cl_gts_gui.valinp_color_trace_05_src_aa_min;
		*pp_max = cl_gts_gui.valinp_color_trace_05_src_aa_max; break;
	case E_COLOR_TRACE_HAB_06:
		*pp_min = cl_gts_gui.valinp_color_trace_06_src_aa_min;
		*pp_max = cl_gts_gui.valinp_color_trace_06_src_aa_max; break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}
int color_trace_enhancement::_src_get_p_bb_valinp( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Value_Input **pp_min, Fl_Value_Input **pp_max )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		*pp_min = cl_gts_gui.valinp_color_trace_01_src_bb_min;
		*pp_max = cl_gts_gui.valinp_color_trace_01_src_bb_max; break;
	case E_COLOR_TRACE_HAB_02:
		*pp_min = cl_gts_gui.valinp_color_trace_02_src_bb_min;
		*pp_max = cl_gts_gui.valinp_color_trace_02_src_bb_max; break;
	case E_COLOR_TRACE_HAB_03:
		*pp_min = cl_gts_gui.valinp_color_trace_03_src_bb_min;
		*pp_max = cl_gts_gui.valinp_color_trace_03_src_bb_max; break;
	case E_COLOR_TRACE_HAB_04:
		*pp_min = cl_gts_gui.valinp_color_trace_04_src_bb_min;
		*pp_max = cl_gts_gui.valinp_color_trace_04_src_bb_max; break;
	case E_COLOR_TRACE_HAB_05:
		*pp_min = cl_gts_gui.valinp_color_trace_05_src_bb_min;
		*pp_max = cl_gts_gui.valinp_color_trace_05_src_bb_max; break;
	case E_COLOR_TRACE_HAB_06:
		*pp_min = cl_gts_gui.valinp_color_trace_06_src_bb_min;
		*pp_max = cl_gts_gui.valinp_color_trace_06_src_bb_max; break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}
int color_trace_enhancement::_src_get_p_hh_scrbar( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Valuator **pp_min, Fl_Valuator **pp_max )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		*pp_min = cl_gts_gui.scrbar_color_trace_01_src_hh_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_01_src_hh_max; break;
	case E_COLOR_TRACE_HAB_02:
		*pp_min = cl_gts_gui.scrbar_color_trace_02_src_hh_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_02_src_hh_max; break;
	case E_COLOR_TRACE_HAB_03:
		*pp_min = cl_gts_gui.scrbar_color_trace_03_src_hh_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_03_src_hh_max; break;
	case E_COLOR_TRACE_HAB_04:
		*pp_min = cl_gts_gui.scrbar_color_trace_04_src_hh_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_04_src_hh_max; break;
	case E_COLOR_TRACE_HAB_05:
		*pp_min = cl_gts_gui.scrbar_color_trace_05_src_hh_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_05_src_hh_max; break;
	case E_COLOR_TRACE_HAB_06:
		*pp_min = cl_gts_gui.scrbar_color_trace_06_src_hh_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_06_src_hh_max; break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}
int color_trace_enhancement::_src_get_p_aa_scrbar( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Valuator **pp_min, Fl_Valuator **pp_max )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		*pp_min = cl_gts_gui.scrbar_color_trace_01_src_aa_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_01_src_aa_max; break;
	case E_COLOR_TRACE_HAB_02:
		*pp_min = cl_gts_gui.scrbar_color_trace_02_src_aa_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_02_src_aa_max; break;
	case E_COLOR_TRACE_HAB_03:
		*pp_min = cl_gts_gui.scrbar_color_trace_03_src_aa_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_03_src_aa_max; break;
	case E_COLOR_TRACE_HAB_04:
		*pp_min = cl_gts_gui.scrbar_color_trace_04_src_aa_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_04_src_aa_max; break;
	case E_COLOR_TRACE_HAB_05:
		*pp_min = cl_gts_gui.scrbar_color_trace_05_src_aa_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_05_src_aa_max; break;
	case E_COLOR_TRACE_HAB_06:
		*pp_min = cl_gts_gui.scrbar_color_trace_06_src_aa_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_06_src_aa_max; break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}
int color_trace_enhancement::_src_get_p_bb_scrbar( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Valuator **pp_min, Fl_Valuator **pp_max )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		*pp_min = cl_gts_gui.scrbar_color_trace_01_src_bb_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_01_src_bb_max; break;
	case E_COLOR_TRACE_HAB_02:
		*pp_min = cl_gts_gui.scrbar_color_trace_02_src_bb_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_02_src_bb_max; break;
	case E_COLOR_TRACE_HAB_03:
		*pp_min = cl_gts_gui.scrbar_color_trace_03_src_bb_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_03_src_bb_max; break;
	case E_COLOR_TRACE_HAB_04:
		*pp_min = cl_gts_gui.scrbar_color_trace_04_src_bb_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_04_src_bb_max; break;
	case E_COLOR_TRACE_HAB_05:
		*pp_min = cl_gts_gui.scrbar_color_trace_05_src_bb_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_05_src_bb_max; break;
	case E_COLOR_TRACE_HAB_06:
		*pp_min = cl_gts_gui.scrbar_color_trace_06_src_bb_min;
		*pp_max = cl_gts_gui.scrbar_color_trace_06_src_bb_max; break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}

int color_trace_enhancement::_src_set_crnt_to_histogram( E_COLOR_TRACE_HAB_COLORS e_num )
{
	Fl_Value_Input
		*flp_src_hh_min = NULL, *flp_src_hh_max = NULL,
		*flp_src_aa_min = NULL, *flp_src_aa_max = NULL,
		*flp_src_bb_min = NULL, *flp_src_bb_max = NULL;

	if ( NG == this->_src_get_p_hh_valinp(
	e_num,&flp_src_hh_min,&flp_src_hh_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_hh_valinp(-) returns NG");
		return NG;
	}
	if ( NG == this->_src_get_p_aa_valinp(
	e_num,&flp_src_aa_min,&flp_src_aa_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_aa_valinp(-) returns NG");
		return NG;
	}
	if ( NG == this->_src_get_p_bb_valinp(
	e_num,&flp_src_bb_min,&flp_src_bb_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_bb_valinp(-) returns NG");
		return NG;
	}

	/* historgramデータ生成時の、色立体のlimit */
	this->src_set_hh_min_max(
		flp_src_hh_min->value() / flp_src_hh_min->maximum(),
		flp_src_hh_max->value() / flp_src_hh_max->maximum()
	);

	this->src_set_aa_min_max(
		flp_src_aa_min->value() / flp_src_aa_min->maximum(),
		flp_src_aa_max->value() / flp_src_aa_max->maximum()
	);

	this->src_set_bb_min_max(
		flp_src_bb_min->value() / flp_src_bb_min->maximum(),
		flp_src_bb_max->value() / flp_src_bb_max->maximum()
	);

	/* histogram windowのmin,max設定 */
	cl_gts_gui.fltkp_hh_cyclic->set_dd_minmax(
		flp_src_hh_min->value() / flp_src_hh_min->maximum(),
		flp_src_hh_max->value() / flp_src_hh_max->maximum()
	);
	cl_gts_gui.fltkp_aa_minmax->set_dd_minmax(
		flp_src_aa_min->value() / flp_src_aa_min->maximum(),
		flp_src_aa_max->value() / flp_src_aa_max->maximum()
	);
	cl_gts_gui.fltkp_bb_minmax->set_dd_minmax(
		flp_src_bb_min->value() / flp_src_bb_min->maximum(),
		flp_src_bb_max->value() / flp_src_bb_max->maximum()
	);
	return OK;
}

/*--------------------------------------------------------*/

int color_trace_enhancement::src_open_histogram_window( E_COLOR_TRACE_HAB_COLORS e_num )
{
	this->_e_source_color_range = e_num;

	if (OK != this->_src_set_crnt_to_histogram( e_num )) {
		pri_funct_err_bttvr(
	 "Error : this->src_set_crnt_to_histogram(%d) returns NG",
			e_num);
		return NG;
	}
	cl_gts_gui.window_hab_histogram->redraw();
	cl_gts_gui.window_hab_histogram->show();
	return OK;
}
int color_trace_enhancement::src_set_histogram_window( E_COLOR_TRACE_HAB_COLORS e_num )
{
	if (OK != this->_src_set_crnt_to_histogram( e_num )) {
		pri_funct_err_bttvr(
	 "Error : this->src_set_crnt_to_histogram(%d) returns NG",
			e_num);
		return NG;
	}
	return OK;
}

int color_trace_enhancement::src_edit_hh( E_COLOR_TRACE_HAB_COLORS e_num, double d_min, double d_max )
{
	Fl_Value_Input	*inpp_min, *inpp_max;
	Fl_Valuator	*scrp_min, *scrp_max;

	if ( NG == this->_src_get_p_hh_valinp(
	e_num,&inpp_min,&inpp_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_hh_valinp(-) returns NG");
		return NG;
	}
	if ( NG == this->_src_get_p_hh_scrbar(
	e_num,&scrp_min,&scrp_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_hh_scrbar(-) returns NG");
		return NG;
	}

	/* 元値の表示変更 */
	inpp_min->value(d_min);
	scrp_min->value(d_min);
	inpp_max->value(d_max);
	scrp_max->value(d_max);
	return OK;
}
int color_trace_enhancement::src_edit_aa( E_COLOR_TRACE_HAB_COLORS e_num, double d_min, double d_max )
{
	Fl_Value_Input	*inpp_min, *inpp_max;
	Fl_Valuator	*scrp_min, *scrp_max;

	if ( NG == this->_src_get_p_aa_valinp(
	e_num,&inpp_min,&inpp_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_aa_valinp(-) returns NG");
		return NG;
	}
	if ( NG == this->_src_get_p_aa_scrbar(
	e_num,&scrp_min,&scrp_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_aa_scrbar(-) returns NG");
		return NG;
	}

	/* 元値の表示変更 */
	inpp_min->value(d_min*100.0);
	scrp_min->value(d_min*100.0);
	inpp_max->value(d_max*100.0);
	scrp_max->value(d_max*100.0);

	/* 元値の変更に合わせて"thickness"ウインドウのGUIの変更 */
	cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(e_num);

	return OK;
}
int color_trace_enhancement::src_edit_bb( E_COLOR_TRACE_HAB_COLORS e_num, double d_min, double d_max )
{
	Fl_Value_Input	*inpp_min, *inpp_max;
	Fl_Valuator	*scrp_min, *scrp_max;

	if ( NG == this->_src_get_p_bb_valinp(
	e_num,&inpp_min,&inpp_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_bb_valinp(-) returns NG");
		return NG;
	}
	if ( NG == this->_src_get_p_bb_scrbar(
	e_num,&scrp_min,&scrp_max) ) {
		pri_funct_err_bttvr(
	  "Error : this->_src_get_p_bb_scrbar(-) returns NG");
		return NG;
	}

	/* 元値の表示変更 */
	inpp_min->value(d_min*100.0);
	scrp_min->value(d_min*100.0);
	inpp_max->value(d_max*100.0);
	scrp_max->value(d_max*100.0);

	/* 元値の変更に合わせて"thickness"ウインドウのGUIの変更 */
	cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(e_num);

	return OK;
}

/*--------------------------------------------------------*/

void color_trace_enhancement::src_set_histogram_max( void )
{
	/* color trace histogram maxの設定 */
	cl_gts_gui.fltkp_hh_histogram->set_l_max(
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_hh.l_max
	);
	cl_gts_gui.fltkp_aa_histogram->set_l_max(
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_aa.l_max
	);
	cl_gts_gui.fltkp_bb_histogram->set_l_max(
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_bb.l_max
	);
}

void color_trace_enhancement::src_set_hh_min_max( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...359.xxx) */
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_hh_min = d_min;
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_hh_max = d_max;
}
void color_trace_enhancement::src_set_aa_min_max( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...1) */
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_aa_min = d_min;
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_aa_max = d_max;
}
void color_trace_enhancement::src_set_bb_min_max( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...1) */
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_bb_min = d_min;
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_bb_max = d_max;
}

void color_trace_enhancement::src_set_range_is_nothing( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_HAB_FREE;
}
void color_trace_enhancement::src_set_range_is_hh( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_HH;
}
void color_trace_enhancement::src_set_range_is_aa( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_AA;
}
void color_trace_enhancement::src_set_range_is_bb( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_BB;
}
void color_trace_enhancement::src_init_histogram_window( void )
{
	/* color trace enhancement */
	cl_gts_gui.fltkp_hh_histogram->set_histogram(
		CALCU_HISTOGRAM_SIZE,
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_hh.l_max,
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_hh.la1000 );
	cl_gts_gui.fltkp_hh_cyclic->set_cp_title( "Hue" );

	cl_gts_gui.fltkp_aa_histogram->set_histogram(
		CALCU_HISTOGRAM_SIZE,
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_aa.l_max,
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_aa.la1000 );
	cl_gts_gui.fltkp_aa_minmax->set_cp_title( "Saturation" );

	cl_gts_gui.fltkp_bb_histogram->set_histogram(
		CALCU_HISTOGRAM_SIZE,
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_bb.l_max,
		cl_gts_master.cl_iip_trac.cl_hab_hist.cl_bb.la1000 );
	cl_gts_gui.fltkp_bb_minmax->set_cp_title( "Value(Brightness)" );
}
void color_trace_enhancement::src_set_from_gui( void )
{
	unsigned char	uchar_red,
			uchar_gre,
			uchar_blu;
	calcu_col_area_hab	*clp_para;

	/*--- 01 ---*/
 clp_para=&(cl_gts_master.cl_cal_trac.cla_area_param[E_COLOR_TRACE_HAB_01]);

	clp_para->i_exec_sw=
		cl_gts_gui.chkbtn_color_trace_01_chk->value();
	clp_para->d_hh_min= 360.0 *
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value() /
		cl_gts_gui.valinp_color_trace_01_src_hh_min->maximum();
	clp_para->d_hh_max= 360.0 *
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value() /
		cl_gts_gui.valinp_color_trace_01_src_hh_max->maximum();
	clp_para->d_aa_min=
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value() /
		cl_gts_gui.valinp_color_trace_01_src_aa_min->maximum();
	clp_para->d_aa_max=
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value() /
		cl_gts_gui.valinp_color_trace_01_src_aa_max->maximum();
	clp_para->d_bb_min=
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value() /
		cl_gts_gui.valinp_color_trace_01_src_bb_min->maximum();
	clp_para->d_bb_max=
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value() /
		cl_gts_gui.valinp_color_trace_01_src_bb_max->maximum();

	Fl::get_color( (Fl_Color)(FL_FREE_COLOR + 0),
			uchar_red, uchar_gre, uchar_blu );
	clp_para->d_red = (double)uchar_red/0xff;
	clp_para->d_gre = (double)uchar_gre/0xff;
	clp_para->d_blu = (double)uchar_blu/0xff;

	/*--- 02 ---*/
 clp_para=&(cl_gts_master.cl_cal_trac.cla_area_param[E_COLOR_TRACE_HAB_02]);

	clp_para->i_exec_sw=
		cl_gts_gui.chkbtn_color_trace_02_chk->value();
	clp_para->d_hh_min= 360.0 *
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value() /
		cl_gts_gui.valinp_color_trace_02_src_hh_min->maximum();
	clp_para->d_hh_max= 360.0 *
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value() /
		cl_gts_gui.valinp_color_trace_02_src_hh_max->maximum();
	clp_para->d_aa_min=
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value() /
		cl_gts_gui.valinp_color_trace_02_src_aa_min->maximum();
	clp_para->d_aa_max=
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value() /
		cl_gts_gui.valinp_color_trace_02_src_aa_max->maximum();
	clp_para->d_bb_min=
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value() /
		cl_gts_gui.valinp_color_trace_02_src_bb_min->maximum();
	clp_para->d_bb_max=
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value() /
		cl_gts_gui.valinp_color_trace_02_src_bb_max->maximum();
	Fl::get_color( (Fl_Color)(FL_FREE_COLOR + 1),
			uchar_red, uchar_gre, uchar_blu );
	clp_para->d_red = (double)uchar_red/0xff;
	clp_para->d_gre = (double)uchar_gre/0xff;
	clp_para->d_blu = (double)uchar_blu/0xff;

	/*--- 03 ---*/
 clp_para=&(cl_gts_master.cl_cal_trac.cla_area_param[E_COLOR_TRACE_HAB_03]);

	clp_para->i_exec_sw=
		cl_gts_gui.chkbtn_color_trace_03_chk->value();
	clp_para->d_hh_min= 360.0 *
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value() /
		cl_gts_gui.valinp_color_trace_03_src_hh_min->maximum();
	clp_para->d_hh_max= 360.0 *
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value() /
		cl_gts_gui.valinp_color_trace_03_src_hh_max->maximum();
	clp_para->d_aa_min=
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value() /
		cl_gts_gui.valinp_color_trace_03_src_aa_min->maximum();
	clp_para->d_aa_max=
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value() /
		cl_gts_gui.valinp_color_trace_03_src_aa_max->maximum();
	clp_para->d_bb_min=
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value() /
		cl_gts_gui.valinp_color_trace_03_src_bb_min->maximum();
	clp_para->d_bb_max=
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value() /
		cl_gts_gui.valinp_color_trace_03_src_bb_max->maximum();
	Fl::get_color( (Fl_Color)(FL_FREE_COLOR + 2),
			uchar_red, uchar_gre, uchar_blu );
	clp_para->d_red = (double)uchar_red/0xff;
	clp_para->d_gre = (double)uchar_gre/0xff;
	clp_para->d_blu = (double)uchar_blu/0xff;

	/*--- 04 ---*/
 clp_para=&(cl_gts_master.cl_cal_trac.cla_area_param[E_COLOR_TRACE_HAB_04]);

	clp_para->i_exec_sw=
		cl_gts_gui.chkbtn_color_trace_04_chk->value();
	clp_para->d_hh_min= 360.0 *
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value() /
		cl_gts_gui.valinp_color_trace_04_src_hh_min->maximum();
	clp_para->d_hh_max= 360.0 *
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value() /
		cl_gts_gui.valinp_color_trace_04_src_hh_max->maximum();
	clp_para->d_aa_min=
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value() /
		cl_gts_gui.valinp_color_trace_04_src_aa_min->maximum();
	clp_para->d_aa_max=
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value() /
		cl_gts_gui.valinp_color_trace_04_src_aa_max->maximum();
	clp_para->d_bb_min=
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value() /
		cl_gts_gui.valinp_color_trace_04_src_bb_min->maximum();
	clp_para->d_bb_max=
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value() /
		cl_gts_gui.valinp_color_trace_04_src_bb_max->maximum();
	Fl::get_color( (Fl_Color)(FL_FREE_COLOR + 3),
			uchar_red, uchar_gre, uchar_blu );
	clp_para->d_red = (double)uchar_red/0xff;
	clp_para->d_gre = (double)uchar_gre/0xff;
	clp_para->d_blu = (double)uchar_blu/0xff;

	/*--- 05 ---*/
 clp_para=&(cl_gts_master.cl_cal_trac.cla_area_param[E_COLOR_TRACE_HAB_05]);

	clp_para->i_exec_sw=
		cl_gts_gui.chkbtn_color_trace_05_chk->value();
	clp_para->d_hh_min= 360.0 *
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value() /
		cl_gts_gui.valinp_color_trace_05_src_hh_min->maximum();
	clp_para->d_hh_max= 360.0 *
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value() /
		cl_gts_gui.valinp_color_trace_05_src_hh_max->maximum();
	clp_para->d_aa_min=
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value() /
		cl_gts_gui.valinp_color_trace_05_src_aa_min->maximum();
	clp_para->d_aa_max=
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value() /
		cl_gts_gui.valinp_color_trace_05_src_aa_max->maximum();
	clp_para->d_bb_min=
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value() /
		cl_gts_gui.valinp_color_trace_05_src_bb_min->maximum();
	clp_para->d_bb_max=
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value() /
		cl_gts_gui.valinp_color_trace_05_src_bb_max->maximum();
	Fl::get_color( (Fl_Color)(FL_FREE_COLOR + 4),
			uchar_red, uchar_gre, uchar_blu );
	clp_para->d_red = (double)uchar_red/0xff;
	clp_para->d_gre = (double)uchar_gre/0xff;
	clp_para->d_blu = (double)uchar_blu/0xff;

	/*--- 06 ---*/
 clp_para=&(cl_gts_master.cl_cal_trac.cla_area_param[E_COLOR_TRACE_HAB_06]);

	clp_para->i_exec_sw=
		cl_gts_gui.chkbtn_color_trace_06_chk->value();
	clp_para->d_hh_min= 360.0 *
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value() /
		cl_gts_gui.valinp_color_trace_06_src_hh_min->maximum();
	clp_para->d_hh_max= 360.0 *
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value() /
		cl_gts_gui.valinp_color_trace_06_src_hh_max->maximum();
	clp_para->d_aa_min=
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value() /
		cl_gts_gui.valinp_color_trace_06_src_aa_min->maximum();
	clp_para->d_aa_max=
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value() /
		cl_gts_gui.valinp_color_trace_06_src_aa_max->maximum();
	clp_para->d_bb_min=
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value() /
		cl_gts_gui.valinp_color_trace_06_src_bb_min->maximum();
	clp_para->d_bb_max=
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value() /
		cl_gts_gui.valinp_color_trace_06_src_bb_max->maximum();
	Fl::get_color( (Fl_Color)(FL_FREE_COLOR + 5),
			uchar_red, uchar_gre, uchar_blu );
	clp_para->d_red = (double)uchar_red/0xff;
	clp_para->d_gre = (double)uchar_gre/0xff;
	clp_para->d_blu = (double)uchar_blu/0xff;
}
