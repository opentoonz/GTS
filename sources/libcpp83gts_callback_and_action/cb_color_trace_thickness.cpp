#include "cb_color_trace_thickness.h"
#include "gts_gui.h"
#include "gts_master.h"

/* "Color Trace Enhancement"ウインドウの各tgtボタンの色を設定して再表示 */
void cb_color_trace_thickness::set_tgt_color_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const int color_choice_from_gui
)
{
	/* "tgt"色 */
	unsigned char tgt_r;
	unsigned char tgt_g;
	unsigned char tgt_b;
	switch (color_choice_from_gui)
	{
	case 0: // BL
		tgt_r = this->tgt_bla_red_;
		tgt_g = this->tgt_bla_gre_;
		tgt_b = this->tgt_bla_blu_;
		break;
	case 1: // R
		tgt_r = this->tgt_red_red_;
		tgt_g = this->tgt_red_gre_;
		tgt_b = this->tgt_red_blu_;
		break;
	case 2: // G
		tgt_r = this->tgt_gre_red_;
		tgt_g = this->tgt_gre_gre_;
		tgt_b = this->tgt_gre_blu_;
		break;
	case 3: // B
		tgt_r = this->tgt_blu_red_;
		tgt_g = this->tgt_blu_gre_;
		tgt_b = this->tgt_blu_blu_;
		break;
	}
	/* "color trace enhancement"ウインドウの"tgt"ボタンの色を設定 */
	cl_gts_master.cl_color_trace_enhancement.set_fl_color_of_table(
		cl_gts_master.cl_color_trace_enhancement.fl_color_table_from_trace_list_pos(trace_list_pos)
		,tgt_r ,tgt_g ,tgt_b
	);
	/* 設定した色を再表示 */
	switch (trace_list_pos)
	{
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.button_color_trace_01_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.button_color_trace_02_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.button_color_trace_03_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.button_color_trace_04_tgt_rgb->redraw(); break;
	}
}

/* "Color Trace Enhancement"ウインドウの各scr,val値を設定再表示 */
void cb_color_trace_thickness::set_src_color_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const int color_choice_from_gui
)
{
	/* "src"色範囲 */
	double hmin,hmax;
	double smin,smax;
	double vmin,vmax;
	switch (color_choice_from_gui)
	{
	case 0: // BL
		hmin = this->src_bla_hue_min_; hmax= this->src_bla_hue_max_;
		smin = this->src_bla_sat_min_; smax= this->src_bla_sat_max_;
		vmin = this->src_bla_val_min_; vmax= this->src_bla_val_max_;
		break;
	case 1: // R
		hmin = this->src_red_hue_min_; hmax= this->src_red_hue_max_;
		smin = this->src_red_sat_min_; smax= this->src_red_sat_max_;
		vmin = this->src_red_val_min_; vmax= this->src_red_val_max_;
		break;
	case 2: // G
		hmin = this->src_gre_hue_min_; hmax= this->src_gre_hue_max_;
		smin = this->src_gre_sat_min_; smax= this->src_gre_sat_max_;
		vmin = this->src_gre_val_min_; vmax= this->src_gre_val_max_;
		break;
	case 3: // B
		hmin = this->src_blu_hue_min_; hmax= this->src_blu_hue_max_;
		smin = this->src_blu_sat_min_; smax= this->src_blu_sat_max_;
		vmin = this->src_blu_val_min_; vmax= this->src_blu_val_max_;
		break;
	}
	/* "color trace enhancement"ウインドウの"src"色範囲を設定 */
	//Fl_Scrollbar *scrbar_hh_min;
	Fl_Valuator
		 *scrbar_hmin=nullptr,*scrbar_hmax=nullptr
		,*scrbar_smin=nullptr,*scrbar_smax=nullptr
		,*scrbar_vmin=nullptr,*scrbar_vmax=nullptr
	;
	Fl_Value_Input
		 *valinp_hmin=nullptr,*valinp_hmax=nullptr
		,*valinp_smin=nullptr,*valinp_smax=nullptr
		,*valinp_vmin=nullptr,*valinp_vmax=nullptr
	;
	switch (trace_list_pos)
	{
	case E_COLOR_TRACE_HAB_01:
		if (0. <= hmin) {
		scrbar_hmin = cl_gts_gui.scrbar_color_trace_01_src_hh_min;
		valinp_hmin = cl_gts_gui.valinp_color_trace_01_src_hh_min;
 		}
		if (0. <= hmax) {
		scrbar_hmax = cl_gts_gui.scrbar_color_trace_01_src_hh_max;
		valinp_hmax = cl_gts_gui.valinp_color_trace_01_src_hh_max;
 		}
		if (0 <= smin) {
		scrbar_smin = cl_gts_gui.scrbar_color_trace_01_src_aa_min;
		valinp_smin = cl_gts_gui.valinp_color_trace_01_src_aa_min;
 		}
		if (0 <= smax) {
		scrbar_smax = cl_gts_gui.scrbar_color_trace_01_src_aa_max;
		valinp_smax = cl_gts_gui.valinp_color_trace_01_src_aa_max;
 		}
		if (0 <= vmin) {
		scrbar_vmin = cl_gts_gui.scrbar_color_trace_01_src_bb_min;
		valinp_vmin = cl_gts_gui.valinp_color_trace_01_src_bb_min;
 		}
		if (0 <= vmax) {
		scrbar_vmax = cl_gts_gui.scrbar_color_trace_01_src_bb_max;
		valinp_vmax = cl_gts_gui.valinp_color_trace_01_src_bb_max;
 		}
		break;

	case E_COLOR_TRACE_HAB_02:
		if (0. <= hmin) {
		scrbar_hmin = cl_gts_gui.scrbar_color_trace_02_src_hh_min;
		valinp_hmin = cl_gts_gui.valinp_color_trace_02_src_hh_min;
 		}
		if (0. <= hmax) {
		scrbar_hmax = cl_gts_gui.scrbar_color_trace_02_src_hh_max;
		valinp_hmax = cl_gts_gui.valinp_color_trace_02_src_hh_max;
 		}
		if (0 <= smin) {
		scrbar_smin = cl_gts_gui.scrbar_color_trace_02_src_aa_min;
		valinp_smin = cl_gts_gui.valinp_color_trace_02_src_aa_min;
 		}
		if (0 <= smax) {
		scrbar_smax = cl_gts_gui.scrbar_color_trace_02_src_aa_max;
		valinp_smax = cl_gts_gui.valinp_color_trace_02_src_aa_max;
 		}
		if (0 <= vmin) {
		scrbar_vmin = cl_gts_gui.scrbar_color_trace_02_src_bb_min;
		valinp_vmin = cl_gts_gui.valinp_color_trace_02_src_bb_min;
 		}
		if (0 <= vmax) {
		scrbar_vmax = cl_gts_gui.scrbar_color_trace_02_src_bb_max;
		valinp_vmax = cl_gts_gui.valinp_color_trace_02_src_bb_max;
 		}
		break;

	case E_COLOR_TRACE_HAB_03:
		if (0. <= hmin) {
		scrbar_hmin = cl_gts_gui.scrbar_color_trace_03_src_hh_min;
		valinp_hmin = cl_gts_gui.valinp_color_trace_03_src_hh_min;
 		}
		if (0. <= hmax) {
		scrbar_hmax = cl_gts_gui.scrbar_color_trace_03_src_hh_max;
		valinp_hmax = cl_gts_gui.valinp_color_trace_03_src_hh_max;
 		}
		if (0 <= smin) {
		scrbar_smin = cl_gts_gui.scrbar_color_trace_03_src_aa_min;
		valinp_smin = cl_gts_gui.valinp_color_trace_03_src_aa_min;
 		}
		if (0 <= smax) {
		scrbar_smax = cl_gts_gui.scrbar_color_trace_03_src_aa_max;
		valinp_smax = cl_gts_gui.valinp_color_trace_03_src_aa_max;
 		}
		if (0 <= vmin) {
		scrbar_vmin = cl_gts_gui.scrbar_color_trace_03_src_bb_min;
		valinp_vmin = cl_gts_gui.valinp_color_trace_03_src_bb_min;
 		}
		if (0 <= vmax) {
		scrbar_vmax = cl_gts_gui.scrbar_color_trace_03_src_bb_max;
		valinp_vmax = cl_gts_gui.valinp_color_trace_03_src_bb_max;
 		}
		break;

	case E_COLOR_TRACE_HAB_04:
		if (0. <= hmin) {
		scrbar_hmin = cl_gts_gui.scrbar_color_trace_04_src_hh_min;
		valinp_hmin = cl_gts_gui.valinp_color_trace_04_src_hh_min;
 		}
		if (0. <= hmax) {
		scrbar_hmax = cl_gts_gui.scrbar_color_trace_04_src_hh_max;
		valinp_hmax = cl_gts_gui.valinp_color_trace_04_src_hh_max;
 		}
		if (0 <= smin) {
		scrbar_smin = cl_gts_gui.scrbar_color_trace_04_src_aa_min;
		valinp_smin = cl_gts_gui.valinp_color_trace_04_src_aa_min;
 		}
		if (0 <= smax) {
		scrbar_smax = cl_gts_gui.scrbar_color_trace_04_src_aa_max;
		valinp_smax = cl_gts_gui.valinp_color_trace_04_src_aa_max;
 		}
		if (0 <= vmin) {
		scrbar_vmin = cl_gts_gui.scrbar_color_trace_04_src_bb_min;
		valinp_vmin = cl_gts_gui.valinp_color_trace_04_src_bb_min;
 		}
		if (0 <= vmax) {
		scrbar_vmax = cl_gts_gui.scrbar_color_trace_04_src_bb_max;
		valinp_vmax = cl_gts_gui.valinp_color_trace_04_src_bb_max;
 		}
		break;

	}
	scrbar_hmin->value(hmin); valinp_hmin->value(hmin);
	scrbar_hmax->value(hmax); valinp_hmax->value(hmax);
	scrbar_smin->value(smin); valinp_smin->value(smin);
	scrbar_smax->value(smax); valinp_smax->value(smax);
	scrbar_vmin->value(vmin); valinp_vmin->value(vmin);
	scrbar_vmax->value(vmax); valinp_vmax->value(vmax);
}

/* "Color Trace Enhancement"ウインドウの各val値を、
"Thickness"ウインドウの各値に移し再表示 */
void cb_color_trace_thickness::set_thickness_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const int color_choice_from_gui
)
{
	double thickness;
	if (color_choice_from_gui == 0) // BL
	{
		switch (trace_list_pos)
		{
		case E_COLOR_TRACE_HAB_01:
	thickness = cl_gts_gui.valinp_color_trace_01_src_bb_max->value();
			break;
		case E_COLOR_TRACE_HAB_02:
	thickness = cl_gts_gui.valinp_color_trace_02_src_bb_max->value();
			break;
		case E_COLOR_TRACE_HAB_03:
	thickness = cl_gts_gui.valinp_color_trace_03_src_bb_max->value();
			break;
		case E_COLOR_TRACE_HAB_04:
	thickness = cl_gts_gui.valinp_color_trace_04_src_bb_max->value();
			break;
		}
	}
	else { // R,G,B
		switch (trace_list_pos)
		{
		case E_COLOR_TRACE_HAB_01:
	thickness = cl_gts_gui.valinp_color_trace_01_src_aa_min->value();
			break;
		case E_COLOR_TRACE_HAB_02:
	thickness = cl_gts_gui.valinp_color_trace_02_src_aa_min->value();
			break;
		case E_COLOR_TRACE_HAB_03:
	thickness = cl_gts_gui.valinp_color_trace_03_src_aa_min->value();
			break;
		case E_COLOR_TRACE_HAB_04:
	thickness = cl_gts_gui.valinp_color_trace_04_src_aa_min->value();
			break;
		}
		thickness = 100.0 - thickness;
 	}

	switch (trace_list_pos)
	{
	case E_COLOR_TRACE_HAB_01:
		((Fl_Valuator *)cl_gts_gui.scrbar_thickness_01)->value(thickness);
		cl_gts_gui.valinp_thickness_01->value(thickness);
		break;
	case E_COLOR_TRACE_HAB_02:
		((Fl_Valuator *)cl_gts_gui.scrbar_thickness_02)->value(thickness);
		cl_gts_gui.valinp_thickness_02->value(thickness);
		break;
	case E_COLOR_TRACE_HAB_03:
		((Fl_Valuator *)cl_gts_gui.scrbar_thickness_03)->value(thickness);
		cl_gts_gui.valinp_thickness_03->value(thickness);
		break;
	case E_COLOR_TRACE_HAB_04:
		((Fl_Valuator *)cl_gts_gui.scrbar_thickness_04)->value(thickness);
		cl_gts_gui.valinp_thickness_04->value(thickness);
		break;
	}
}

//----------
namespace {
 /* 指定値で"Color Trace Enhancement"ウインドウの各scr,val値を設定再表示 */
 void set_enh_val_and_scr(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const int color_choice_from_gui
	, double value
 )
 {
	if (color_choice_from_gui == 0) // BL
	{
	 switch (trace_list_pos)
	 {
	 case E_COLOR_TRACE_HAB_01:
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_01_src_bb_max)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_02:
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_02_src_bb_max)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_03:
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_03_src_bb_max)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_04:
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_04_src_bb_max)->value(value);
		break;
	 }
	}
	else { // R,G,B
	 value = 100.0 - value;
	 switch (trace_list_pos)
	 {
	 case E_COLOR_TRACE_HAB_01:
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_01_src_aa_min)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_02:
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_02_src_aa_min)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_03:
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_03_src_aa_min)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_04:
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value(value);
		((Fl_Valuator *)
		cl_gts_gui.scrbar_color_trace_04_src_aa_min)->value(value);
		break;
	 }
	}
 }
}

//----------------------------------------------------------------------

//----------
void cb_color_trace_thickness::init( void )
{
	this->cb_preset_01(
		cl_gts_gui.choice_thickness_01_tgt_src_preset->value()
	);
	this->cb_preset_02(
		cl_gts_gui.choice_thickness_02_tgt_src_preset->value()
	);
	this->cb_preset_03(
		cl_gts_gui.choice_thickness_03_tgt_src_preset->value()
	);
	this->cb_preset_04(
		cl_gts_gui.choice_thickness_04_tgt_src_preset->value()
	);
}

//----------
void cb_color_trace_thickness::cb_preset_01( const int choice )
{
	this->set_tgt_color_( E_COLOR_TRACE_HAB_01 ,choice );
	this->set_src_color_( E_COLOR_TRACE_HAB_01 ,choice );
	this->set_thickness_( E_COLOR_TRACE_HAB_01 ,choice );

	/* "Edit HSV-MinMax"の表示変更 */
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_preset_02( const int choice )
{
	this->set_tgt_color_( E_COLOR_TRACE_HAB_02 ,choice );
	this->set_src_color_( E_COLOR_TRACE_HAB_02 ,choice );
	this->set_thickness_( E_COLOR_TRACE_HAB_02 ,choice );

	/* "Edit HSV-MinMax"の表示変更 */
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_preset_03( const int choice )
{
	this->set_tgt_color_( E_COLOR_TRACE_HAB_03 ,choice );
	this->set_src_color_( E_COLOR_TRACE_HAB_03 ,choice );
	this->set_thickness_( E_COLOR_TRACE_HAB_03 ,choice );

	/* "Edit HSV-MinMax"の表示変更 */
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_preset_04( const int choice )
{
	this->set_tgt_color_( E_COLOR_TRACE_HAB_04 ,choice );
	this->set_src_color_( E_COLOR_TRACE_HAB_04 ,choice );
	this->set_thickness_( E_COLOR_TRACE_HAB_04 ,choice );

	/* "Edit HSV-MinMax"の表示変更 */
	cl_gts_master.cb_color_trace_src_edit_value();
}

//----------
void cb_color_trace_thickness::cb_src_01( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cb_color_trace_src_open_01();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}
}
void cb_color_trace_thickness::cb_src_02( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cb_color_trace_src_open_02();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}
}
void cb_color_trace_thickness::cb_src_03( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cb_color_trace_src_open_03();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}
}
void cb_color_trace_thickness::cb_src_04( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cb_color_trace_src_open_04();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}
}

//----------
void cb_color_trace_thickness::cb_scrbar_01( const double value )
{
	cl_gts_gui.valinp_thickness_01->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_01
		,cl_gts_gui.choice_thickness_01_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_01( const double value )
{
	((Fl_Valuator *)
	cl_gts_gui.scrbar_thickness_01)->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_01
		,cl_gts_gui.choice_thickness_01_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_02( const double value )
{
	cl_gts_gui.valinp_thickness_02->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_02
		,cl_gts_gui.choice_thickness_02_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_02( const double value )
{
	((Fl_Valuator *)
	cl_gts_gui.scrbar_thickness_02)->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_02
		,cl_gts_gui.choice_thickness_02_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_03( const double value )
{
	cl_gts_gui.valinp_thickness_03->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_03
		,cl_gts_gui.choice_thickness_03_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_03( const double value )
{
	((Fl_Valuator *)
	cl_gts_gui.scrbar_thickness_03)->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_03
		,cl_gts_gui.choice_thickness_03_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_04( const double value )
{
	cl_gts_gui.valinp_thickness_04->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_04
		,cl_gts_gui.choice_thickness_04_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_04( const double value )
{
	((Fl_Valuator *)
	cl_gts_gui.scrbar_thickness_04)->value(value);
	set_enh_val_and_scr(
		E_COLOR_TRACE_HAB_04
		,cl_gts_gui.choice_thickness_04_tgt_src_preset->value()
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

//----------
void cb_color_trace_thickness::cb_enh_01( void )
{
	this->set_thickness_(
		E_COLOR_TRACE_HAB_01
		,cl_gts_gui.choice_thickness_01_tgt_src_preset->value()
	);
}

void cb_color_trace_thickness::cb_enh_02( void )
{
	this->set_thickness_(
		E_COLOR_TRACE_HAB_02
		,cl_gts_gui.choice_thickness_02_tgt_src_preset->value()
	);
}

void cb_color_trace_thickness::cb_enh_03( void )
{
	this->set_thickness_(
		E_COLOR_TRACE_HAB_03
		,cl_gts_gui.choice_thickness_03_tgt_src_preset->value()
	);
}

void cb_color_trace_thickness::cb_enh_04( void )
{
	this->set_thickness_(
		E_COLOR_TRACE_HAB_04
		,cl_gts_gui.choice_thickness_04_tgt_src_preset->value()
	);
}

//----------
void cb_color_trace_thickness::set_scrbar_inpval(
	E_COLOR_TRACE_HAB_COLORS col_tra_num
)
{
	switch (col_tra_num) {
	case E_COLOR_TRACE_HAB_01: this->cb_enh_01(); break;
	case E_COLOR_TRACE_HAB_02: this->cb_enh_02(); break;
	case E_COLOR_TRACE_HAB_03: this->cb_enh_03(); break;
	case E_COLOR_TRACE_HAB_04: this->cb_enh_04(); break;
	}
}
//----------
