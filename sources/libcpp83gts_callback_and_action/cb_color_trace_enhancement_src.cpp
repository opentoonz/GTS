#include <cmath>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include "ptbl_returncode.h"
#include "pri.h"
#include "cb_color_trace_enhancement.h"
#include "gts_gui.h"
#include "gts_master.h"

int cb_color_trace_enhancement::_src_get_p_hh_valinp( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Value_Input **pp_min, Fl_Value_Input **pp_max )
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
int cb_color_trace_enhancement::_src_get_p_aa_valinp( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Value_Input **pp_min, Fl_Value_Input **pp_max )
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
int cb_color_trace_enhancement::_src_get_p_bb_valinp( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Value_Input **pp_min, Fl_Value_Input **pp_max )
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
int cb_color_trace_enhancement::_src_get_p_hh_scrbar( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Valuator **pp_min, Fl_Valuator **pp_max )
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
int cb_color_trace_enhancement::_src_get_p_aa_scrbar( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Valuator **pp_min, Fl_Valuator **pp_max )
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
int cb_color_trace_enhancement::_src_get_p_bb_scrbar( E_COLOR_TRACE_HAB_COLORS e_num, Fl_Valuator **pp_min, Fl_Valuator **pp_max )
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

int cb_color_trace_enhancement::_src_set_crnt_to_histogram( E_COLOR_TRACE_HAB_COLORS e_num )
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

	/* ValueInputに表示する */
 cl_gts_gui.valinp_hab_histogram_hh_min->value( flp_src_hh_min->value() );
 cl_gts_gui.valinp_hab_histogram_hh_max->value( flp_src_hh_max->value() );
 cl_gts_gui.valinp_hab_histogram_aa_min->value( flp_src_aa_min->value() );
 cl_gts_gui.valinp_hab_histogram_aa_max->value( flp_src_aa_max->value() );
 cl_gts_gui.valinp_hab_histogram_bb_min->value( flp_src_bb_min->value() );
 cl_gts_gui.valinp_hab_histogram_bb_max->value( flp_src_bb_max->value() );

	return OK;
}

/*--------------------------------------------------------*/

namespace {
 void resize_src_button_(
	E_COLOR_TRACE_HAB_COLORS e_num
	,const int mgn
	,const char *label
	,Fl_Boxtype btype
 )
 {
 	Fl_Button *tbut=nullptr;
 	Fl_Button *ebut=nullptr;
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		tbut= cl_gts_gui.button_thickness_01_src;
		ebut= cl_gts_gui.button_color_trace_01_src;
		break;
	case E_COLOR_TRACE_HAB_02:
		tbut= cl_gts_gui.button_thickness_02_src;
		ebut= cl_gts_gui.button_color_trace_02_src;
		break;
	case E_COLOR_TRACE_HAB_03:
		tbut= cl_gts_gui.button_thickness_03_src;
		ebut= cl_gts_gui.button_color_trace_03_src;
		break;
	case E_COLOR_TRACE_HAB_04:
		tbut= cl_gts_gui.button_thickness_04_src;
		ebut= cl_gts_gui.button_color_trace_04_src;
		break;
	case E_COLOR_TRACE_HAB_05:
		tbut= cl_gts_gui.button_thickness_05_src;
		ebut= cl_gts_gui.button_color_trace_05_src;
		break;
	case E_COLOR_TRACE_HAB_06:
		tbut= cl_gts_gui.button_thickness_06_src;
		ebut= cl_gts_gui.button_color_trace_06_src;
		break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		break;
	}
	if (tbut != nullptr) {
		//tbut->size( 30+mgn ,20+mgn );
		//tbut->label( label );
		tbut->box( btype );
		cl_gts_gui.window_trace_thickness->redraw();
	}
	if (ebut != nullptr) {
		//ebut->size( 30+mgn ,25+mgn );
		//ebut->label( label );
		ebut->box( btype );
		cl_gts_gui.window_trace_parameters->redraw();
	}
 }
}

int cb_color_trace_enhancement::src_open_histogram_window_( E_COLOR_TRACE_HAB_COLORS e_num )
{
	if (this->_e_source_color_range != e_num)
	{
		resize_src_button_(
			this->_e_source_color_range
			,0 ,"src" ,FL_UP_BOX
		);
		resize_src_button_(
			e_num
			,0 ,"src" ,FL_ROUND_UP_BOX
		);
		this->_e_source_color_range = e_num;
	}


	if (OK != this->_src_set_crnt_to_histogram( e_num )) {
		pri_funct_err_bttvr(
	 "Error : this->src_set_crnt_to_histogram(%d) returns NG",
			e_num);
		return NG;
	}
	cl_gts_gui.window_main_view->show();/* Need for Minimize */
	cl_gts_gui.window_trace_input_color->redraw();
	cl_gts_gui.window_trace_input_color->show();
	cl_gts_gui.menite_trace_input_color->set();//Check menu sw

	return OK;
}
int cb_color_trace_enhancement::src_set_histogram_window( E_COLOR_TRACE_HAB_COLORS e_num )
{
	if (OK != this->_src_set_crnt_to_histogram( e_num )) {
		pri_funct_err_bttvr(
	 "Error : this->src_set_crnt_to_histogram(%d) returns NG",
			e_num);
		return NG;
	}
	return OK;
}

int cb_color_trace_enhancement::src_edit_hh( E_COLOR_TRACE_HAB_COLORS e_num, double d_min, double d_max )
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

	/* 元値の変更に合わせて"thickness"ウインドウのGUIの変更-->はない */

	return OK;
}
int cb_color_trace_enhancement::src_edit_aa( E_COLOR_TRACE_HAB_COLORS e_num, double d_min, double d_max )
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

	/* "指定のトレス番号の値を"Color Trace Enhancement"で再表示 */
	cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(e_num);

	return OK;
}
int cb_color_trace_enhancement::src_edit_bb( E_COLOR_TRACE_HAB_COLORS e_num, double d_min, double d_max )
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

	/* "指定のトレス番号の値を"Color Trace Enhancement"で再表示 */
	cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(e_num);

	return OK;
}

/*--------------------------------------------------------*/

void cb_color_trace_enhancement::src_set_histogram_max( void )
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

void cb_color_trace_enhancement::src_set_hh_min_max( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...359.xxx) */
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_hh_min = d_min;
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_hh_max = d_max;
}
void cb_color_trace_enhancement::src_set_aa_min_max( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...1) */
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_aa_min = d_min;
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_aa_max = d_max;
}
void cb_color_trace_enhancement::src_set_bb_min_max( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...1) */
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_bb_min = d_min;
	cl_gts_master.cl_iip_trac.cl_hab_hist.d_bb_max = d_max;
}

void cb_color_trace_enhancement::src_set_range_is_nothing( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_HAB_FREE;
}
void cb_color_trace_enhancement::src_set_range_is_hh( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_HH;
}
void cb_color_trace_enhancement::src_set_range_is_aa( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_AA;
}
void cb_color_trace_enhancement::src_set_range_is_bb( void )
{
	cl_gts_master.cl_iip_trac.cl_hab_hist.e_hab_is = E_BB;
}
void cb_color_trace_enhancement::src_init_histogram_window( void )
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
void cb_color_trace_enhancement::src_set_from_gui( void )
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

/* color trace enhancement windowから番号指定してhistogram windowを開く */
void cb_color_trace_enhancement::cb_src_show_01( void )
{ (void)this->src_open_histogram_window_(
			   E_COLOR_TRACE_HAB_01 );
}
void cb_color_trace_enhancement::cb_src_show_02( void )
{ (void)this->src_open_histogram_window_(
			   E_COLOR_TRACE_HAB_02 );
}
void cb_color_trace_enhancement::cb_src_show_03( void )
{ (void)this->src_open_histogram_window_(
			   E_COLOR_TRACE_HAB_03 );
}
void cb_color_trace_enhancement::cb_src_show_04( void )
{ (void)this->src_open_histogram_window_(
			   E_COLOR_TRACE_HAB_04 );
}
void cb_color_trace_enhancement::cb_src_show_05( void )
{ (void)this->src_open_histogram_window_(
			   E_COLOR_TRACE_HAB_05 );
}
void cb_color_trace_enhancement::cb_src_show_06( void )
{ (void)this->src_open_histogram_window_(
			   E_COLOR_TRACE_HAB_06 );
}

//----------
/* Saturationの色変化 GUIの値を見て再表示する */
void cb_color_trace_enhancement::reset_saturation_belt_when_modify_hue_min_or_max(void)
{
	const E_COLOR_TRACE_HAB_COLORS num = this->src_get_e_color_range();
	double h_min = 0.0;
	double h_max = 0.0;
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
	h_min = cl_gts_gui.valinp_color_trace_01_src_hh_min->value();
	h_max = cl_gts_gui.valinp_color_trace_01_src_hh_max->value();
		break;
	case E_COLOR_TRACE_HAB_02:
	h_min = cl_gts_gui.valinp_color_trace_02_src_hh_min->value();
	h_max = cl_gts_gui.valinp_color_trace_02_src_hh_max->value();
		break;
	case E_COLOR_TRACE_HAB_03:
	h_min = cl_gts_gui.valinp_color_trace_03_src_hh_min->value();
	h_max = cl_gts_gui.valinp_color_trace_03_src_hh_max->value();
		break;
	case E_COLOR_TRACE_HAB_04:
	h_min = cl_gts_gui.valinp_color_trace_04_src_hh_min->value();
	h_max = cl_gts_gui.valinp_color_trace_04_src_hh_max->value();
		break;
	case E_COLOR_TRACE_HAB_05:
	h_min = cl_gts_gui.valinp_color_trace_05_src_hh_min->value();
	h_max = cl_gts_gui.valinp_color_trace_05_src_hh_max->value();
		break;
	case E_COLOR_TRACE_HAB_06:
	h_min = cl_gts_gui.valinp_color_trace_06_src_hh_min->value();
	h_max = cl_gts_gui.valinp_color_trace_06_src_hh_max->value();
 		break;
	}

	const unsigned char *const* image_p =
		reinterpret_cast<const unsigned char *const*>(
			cl_gts_gui.box_hh_color_belt->image()->data()
		);
	int depth = cl_gts_gui.box_hh_color_belt->image()->d();
	int width = cl_gts_gui.box_hh_color_belt->image()->w();

	/* 0〜1の範囲をヒストグラム配列の範囲に変更 */
	double h_middle = 0.0;
	if (h_min <= h_max) {
		h_middle =  (h_min + h_max) / 2.0;
	}
	else {
		h_middle =  std::fmod(
			((h_min + h_max + 360.0) / 2.0) , 360.0
		);
	}
	const int i_pos = static_cast<int>(
		(width + 0.999999) * h_middle / 360.0
	);

	unsigned char rr = image_p[0][i_pos*depth+0];
	unsigned char gg = image_p[0][i_pos*depth+1];
	unsigned char bb = image_p[0][i_pos*depth+2];

	cl_gts_gui.fltkp_aa_color_belt->set_right_color(rr,gg,bb);

	//cl_gts_gui.window_trace_input_color->redraw();
	cl_gts_gui.fltkp_aa_color_belt->redraw();
/*
Bug	2016-08-01
	画像を表示せず、histogramを非表示の場合、
	cl_gts_gui.fltkp_aa_color_belt->redraw();で、
	fltk_1000x10_color_belt::draw();を実行するはずが実行しない。
	cl_gts_gui.window_trace_input_color->redraw();に替えても同じ。
	原因不明。重要性低く今のところ保留
*/

	if (cl_gts_gui.fltkp_aa_histogram->is_color_left_right()) {
		cl_gts_gui.fltkp_aa_histogram->set_color_left_right(
		 	true
			,cl_gts_gui.fltkp_aa_color_belt->get_left_r()
			,cl_gts_gui.fltkp_aa_color_belt->get_left_g()
			,cl_gts_gui.fltkp_aa_color_belt->get_left_b()
			,cl_gts_gui.fltkp_aa_color_belt->get_right_r()
			,cl_gts_gui.fltkp_aa_color_belt->get_right_g()
			,cl_gts_gui.fltkp_aa_color_belt->get_right_b()
		);
		cl_gts_gui.fltkp_aa_histogram->redraw();
	}
}

namespace {
void cb_src_hh_min_(
	E_COLOR_TRACE_HAB_COLORS num
	,const double val
	,const bool scr_sw
	,const bool val_sw
)
{
	if (scr_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_01_src_hh_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_02: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_02_src_hh_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_03: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_03_src_hh_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_04: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_04_src_hh_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_05: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_05_src_hh_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_06: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_06_src_hh_min)->value(val);
 		break;
	}
	if (val_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.valinp_color_trace_01_src_hh_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.valinp_color_trace_02_src_hh_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.valinp_color_trace_03_src_hh_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.valinp_color_trace_04_src_hh_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.valinp_color_trace_05_src_hh_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.valinp_color_trace_06_src_hh_min->value(val);
 		break;
	}

	cl_gts_master.cb_color_trace_src_edit_value();
	if (num ==
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()) {
		cl_gts_gui.valinp_hab_histogram_hh_min->value(val);

		/* Saturationの色変化 */
	 cl_gts_master.cl_color_trace_enhancement.reset_saturation_belt_when_modify_hue_min_or_max();
	}
}
void cb_src_hh_max_(
	E_COLOR_TRACE_HAB_COLORS num
	,const double val
	,const bool scr_sw
	,const bool val_sw
)
{
	if (scr_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_01_src_hh_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_02: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_02_src_hh_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_03: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_03_src_hh_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_04: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_04_src_hh_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_05: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_05_src_hh_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_06: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_06_src_hh_max)->value(val);
 		break;
	}
	if (val_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.valinp_color_trace_01_src_hh_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.valinp_color_trace_02_src_hh_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.valinp_color_trace_03_src_hh_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.valinp_color_trace_04_src_hh_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.valinp_color_trace_05_src_hh_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.valinp_color_trace_06_src_hh_max->value(val);
 		break;
	}
	cl_gts_master.cb_color_trace_src_edit_value();
	if (num ==
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()) {
		cl_gts_gui.valinp_hab_histogram_hh_max->value(val);

		/* Saturationの色変化 */
	 cl_gts_master.cl_color_trace_enhancement.reset_saturation_belt_when_modify_hue_min_or_max();
	}
}

void cb_src_aa_min_(
	E_COLOR_TRACE_HAB_COLORS num
	,const double val
	,const bool scr_sw
	,const bool val_sw
)
{
	if (scr_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_01_src_aa_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_02: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_02_src_aa_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_03: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_03_src_aa_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_04: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_04_src_aa_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_05: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_05_src_aa_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_06: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_06_src_aa_min)->value(val);
 		break;
	}
	if (val_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.valinp_color_trace_01_src_aa_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.valinp_color_trace_02_src_aa_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.valinp_color_trace_03_src_aa_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.valinp_color_trace_04_src_aa_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.valinp_color_trace_05_src_aa_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.valinp_color_trace_06_src_aa_min->value(val);
 		break;
	}
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_master.cl_color_trace_thickness.cb_enh_01();
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_master.cl_color_trace_thickness.cb_enh_02();
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_master.cl_color_trace_thickness.cb_enh_03();
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_master.cl_color_trace_thickness.cb_enh_04();
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_master.cl_color_trace_thickness.cb_enh_05();
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_master.cl_color_trace_thickness.cb_enh_06();
		break;
	}
	cl_gts_master.cb_color_trace_src_edit_value();
	if (num ==
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()) {
		cl_gts_gui.valinp_hab_histogram_aa_min->value(val);
	}
}
void cb_src_aa_max_(
	E_COLOR_TRACE_HAB_COLORS num
	,const double val
	,const bool scr_sw
	,const bool val_sw
)
{
	if (scr_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_01_src_aa_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_02: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_02_src_aa_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_03: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_03_src_aa_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_04: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_04_src_aa_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_05: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_05_src_aa_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_06: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_06_src_aa_max)->value(val);
 		break;
	}
	if (val_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.valinp_color_trace_01_src_aa_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.valinp_color_trace_02_src_aa_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.valinp_color_trace_03_src_aa_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.valinp_color_trace_04_src_aa_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.valinp_color_trace_05_src_aa_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.valinp_color_trace_06_src_aa_max->value(val);
 		break;
	}
	cl_gts_master.cb_color_trace_src_edit_value();
	if (num ==
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()) {
		cl_gts_gui.valinp_hab_histogram_aa_max->value(val);
	}
}

void cb_src_bb_min_(
	E_COLOR_TRACE_HAB_COLORS num
	,const double val
	,const bool scr_sw
	,const bool val_sw
)
{
	if (scr_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_01_src_bb_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_02: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_02_src_bb_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_03: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_03_src_bb_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_04: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_04_src_bb_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_05: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_05_src_bb_min)->value(val);
		break;
	case E_COLOR_TRACE_HAB_06: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_06_src_bb_min)->value(val);
 		break;
	}
	if (val_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.valinp_color_trace_01_src_bb_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.valinp_color_trace_02_src_bb_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.valinp_color_trace_03_src_bb_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.valinp_color_trace_04_src_bb_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.valinp_color_trace_05_src_bb_min->value(val);
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.valinp_color_trace_06_src_bb_min->value(val);
 		break;
	}
	cl_gts_master.cb_color_trace_src_edit_value();
	if (num ==
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()) {
		cl_gts_gui.valinp_hab_histogram_bb_min->value(val);
	}
}
void cb_src_bb_max_(
	E_COLOR_TRACE_HAB_COLORS num
	,const double val
	,const bool scr_sw
	,const bool val_sw
)
{
	if (scr_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_01_src_bb_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_02: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_02_src_bb_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_03: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_03_src_bb_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_04: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_04_src_bb_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_05: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_05_src_bb_max)->value(val);
		break;
	case E_COLOR_TRACE_HAB_06: ((Fl_Valuator *)
 cl_gts_gui.scrbar_color_trace_06_src_bb_max)->value(val);
 		break;
	}
	if (val_sw)
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.valinp_color_trace_01_src_bb_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.valinp_color_trace_02_src_bb_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.valinp_color_trace_03_src_bb_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.valinp_color_trace_04_src_bb_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.valinp_color_trace_05_src_bb_max->value(val);
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.valinp_color_trace_06_src_bb_max->value(val);
 		break;
	}
	switch (num) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_master.cl_color_trace_thickness.cb_enh_01();
		break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_master.cl_color_trace_thickness.cb_enh_02();
		break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_master.cl_color_trace_thickness.cb_enh_03();
		break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_master.cl_color_trace_thickness.cb_enh_04();
		break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_master.cl_color_trace_thickness.cb_enh_05();
		break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_master.cl_color_trace_thickness.cb_enh_06();
		break;
	}
	cl_gts_master.cb_color_trace_src_edit_value();
	if (num ==
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()) {
		cl_gts_gui.valinp_hab_histogram_bb_max->value(val);
	}
}
}

//---------- color trace enhancedment scrbar
void cb_color_trace_enhancement::cb_scrbar_src_hh_min_01(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_01 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_hh_max_01(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_01 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_min_01(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_01 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_max_01(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_01 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_min_01(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_01 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_max_01(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_01 ,val,false,true ); }

void cb_color_trace_enhancement::cb_scrbar_src_hh_min_02(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_02 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_hh_max_02(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_02 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_min_02(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_02 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_max_02(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_02 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_min_02(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_02 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_max_02(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_02 ,val,false,true ); }

void cb_color_trace_enhancement::cb_scrbar_src_hh_min_03(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_03 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_hh_max_03(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_03 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_min_03(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_03 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_max_03(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_03 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_min_03(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_03 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_max_03(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_03 ,val,false,true ); }

void cb_color_trace_enhancement::cb_scrbar_src_hh_min_04(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_04 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_hh_max_04(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_04 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_min_04(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_04 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_max_04(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_04 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_min_04(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_04 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_max_04(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_04 ,val,false,true ); }

void cb_color_trace_enhancement::cb_scrbar_src_hh_min_05(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_05 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_hh_max_05(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_05 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_min_05(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_05 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_max_05(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_05 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_min_05(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_05 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_max_05(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_05 ,val,false,true ); }

void cb_color_trace_enhancement::cb_scrbar_src_hh_min_06(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_06 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_hh_max_06(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_06 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_min_06(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_06 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_aa_max_06(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_06 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_min_06(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_06 ,val,false,true ); }
void cb_color_trace_enhancement::cb_scrbar_src_bb_max_06(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_06 ,val,false,true ); }

//---------- color trace enhancedment valinp
void cb_color_trace_enhancement::cb_valinp_src_hh_min_01(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_01 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_hh_max_01(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_01 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_min_01(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_01 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_max_01(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_01 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_min_01(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_01 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_max_01(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_01 ,val,true,false ); }

void cb_color_trace_enhancement::cb_valinp_src_hh_min_02(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_02 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_hh_max_02(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_02 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_min_02(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_02 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_max_02(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_02 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_min_02(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_02 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_max_02(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_02 ,val,true,false ); }

void cb_color_trace_enhancement::cb_valinp_src_hh_min_03(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_03 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_hh_max_03(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_03 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_min_03(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_03 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_max_03(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_03 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_min_03(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_03 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_max_03(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_03 ,val,true,false ); }

void cb_color_trace_enhancement::cb_valinp_src_hh_min_04(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_04 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_hh_max_04(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_04 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_min_04(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_04 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_max_04(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_04 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_min_04(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_04 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_max_04(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_04 ,val,true,false ); }

void cb_color_trace_enhancement::cb_valinp_src_hh_min_05(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_05 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_hh_max_05(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_05 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_min_05(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_05 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_max_05(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_05 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_min_05(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_05 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_max_05(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_05 ,val,true,false ); }

void cb_color_trace_enhancement::cb_valinp_src_hh_min_06(const double val )
{				 cb_src_hh_min_(
			     E_COLOR_TRACE_HAB_06 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_hh_max_06(const double val )
{				 cb_src_hh_max_(
			     E_COLOR_TRACE_HAB_06 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_min_06(const double val )
{				 cb_src_aa_min_(
			     E_COLOR_TRACE_HAB_06 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_aa_max_06(const double val )
{				 cb_src_aa_max_(
			     E_COLOR_TRACE_HAB_06 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_min_06(const double val )
{				 cb_src_bb_min_(
			     E_COLOR_TRACE_HAB_06 ,val,true,false ); }
void cb_color_trace_enhancement::cb_valinp_src_bb_max_06(const double val )
{				 cb_src_bb_max_(
			     E_COLOR_TRACE_HAB_06 ,val,true,false ); }

//---------- Use edit hsv minmax valinp
void cb_color_trace_enhancement::cb_src_hh_min( const double val )
{				 cb_src_hh_min_(
	this->src_get_e_color_range() ,val,true,true ); }
void cb_color_trace_enhancement::cb_src_hh_max( const double val )
{				 cb_src_hh_max_(
	this->src_get_e_color_range() ,val,true,true ); }
void cb_color_trace_enhancement::cb_src_aa_min( const double val )
{				 cb_src_aa_min_(
	this->src_get_e_color_range() ,val,true,true ); }
void cb_color_trace_enhancement::cb_src_aa_max( const double val )
{				 cb_src_aa_max_(
	this->src_get_e_color_range() ,val,true,true ); }
void cb_color_trace_enhancement::cb_src_bb_min( const double val )
{				 cb_src_bb_min_(
	this->src_get_e_color_range() ,val,true,true ); }
void cb_color_trace_enhancement::cb_src_bb_max( const double val )
{				 cb_src_bb_max_(
	this->src_get_e_color_range() ,val,true,true ); }

//----------
