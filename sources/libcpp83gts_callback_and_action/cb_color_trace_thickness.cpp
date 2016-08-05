#include "cb_color_trace_thickness.h"
#include "gts_gui.h"
#include "gts_master.h"

/* "Color Trace Enhancement"ウインドウの各val値を、
"Thickness"ウインドウの各値に移し再表示 */
void cb_color_trace_thickness::set_thickness_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const bool black_line_sw
)
{
	double thickness;
	if (black_line_sw) // BL
	{
		switch (trace_list_pos)
		{
		case      E_COLOR_TRACE_HAB_01:
  thickness = cl_gts_gui.valinp_color_trace_01_src_bb_max->value();
			break;
		case      E_COLOR_TRACE_HAB_02:
  thickness = cl_gts_gui.valinp_color_trace_02_src_bb_max->value();
			break;
		case      E_COLOR_TRACE_HAB_03:
  thickness = cl_gts_gui.valinp_color_trace_03_src_bb_max->value();
			break;
		case      E_COLOR_TRACE_HAB_04:
  thickness = cl_gts_gui.valinp_color_trace_04_src_bb_max->value();
			break;
		case      E_COLOR_TRACE_HAB_05:
  thickness = cl_gts_gui.valinp_color_trace_05_src_bb_max->value();
			break;
		case      E_COLOR_TRACE_HAB_06:
  thickness = cl_gts_gui.valinp_color_trace_06_src_bb_max->value();
			break;
		}
	}
	else { // R,G,B
		switch (trace_list_pos)
		{
		case      E_COLOR_TRACE_HAB_01:
  thickness = cl_gts_gui.valinp_color_trace_01_src_aa_min->value();
			break;
		case      E_COLOR_TRACE_HAB_02:
  thickness = cl_gts_gui.valinp_color_trace_02_src_aa_min->value();
			break;
		case      E_COLOR_TRACE_HAB_03:
  thickness = cl_gts_gui.valinp_color_trace_03_src_aa_min->value();
			break;
		case      E_COLOR_TRACE_HAB_04:
  thickness = cl_gts_gui.valinp_color_trace_04_src_aa_min->value();
			break;
		case      E_COLOR_TRACE_HAB_05:
  thickness = cl_gts_gui.valinp_color_trace_05_src_aa_min->value();
			break;
		case      E_COLOR_TRACE_HAB_06:
  thickness = cl_gts_gui.valinp_color_trace_06_src_aa_min->value();
			break;
		}
		thickness = 100.0 - thickness;
 	}

	switch (trace_list_pos)
	{
	case		  E_COLOR_TRACE_HAB_01:
((Fl_Valuator *)cl_gts_gui.scrbar_thickness_01)->value(thickness);
		cl_gts_gui.valinp_thickness_01->value(thickness);
		break;
	case		  E_COLOR_TRACE_HAB_02:
((Fl_Valuator *)cl_gts_gui.scrbar_thickness_02)->value(thickness);
		cl_gts_gui.valinp_thickness_02->value(thickness);
		break;
	case		  E_COLOR_TRACE_HAB_03:
((Fl_Valuator *)cl_gts_gui.scrbar_thickness_03)->value(thickness);
		cl_gts_gui.valinp_thickness_03->value(thickness);
		break;
	case		  E_COLOR_TRACE_HAB_04:
((Fl_Valuator *)cl_gts_gui.scrbar_thickness_04)->value(thickness);
		cl_gts_gui.valinp_thickness_04->value(thickness);
		break;
	case		  E_COLOR_TRACE_HAB_05:
((Fl_Valuator *)cl_gts_gui.scrbar_thickness_05)->value(thickness);
		cl_gts_gui.valinp_thickness_05->value(thickness);
		break;
	case		  E_COLOR_TRACE_HAB_06:
((Fl_Valuator *)cl_gts_gui.scrbar_thickness_06)->value(thickness);
		cl_gts_gui.valinp_thickness_06->value(thickness);
		break;
	}
}

//----------
 /* 指定値で"Color Trace Enhancement"ウインドウの各scr,val値を設定再表示 */
void cb_color_trace_thickness::set_enh_val_and_scr_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const bool black_line_sw
	, double value
)
{
	if (black_line_sw) // BL
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
	 case E_COLOR_TRACE_HAB_05:
  cl_gts_gui.valinp_color_trace_05_src_bb_max->value(value);
  ((Fl_Valuator *)
  cl_gts_gui.scrbar_color_trace_05_src_bb_max)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_06:
  cl_gts_gui.valinp_color_trace_06_src_bb_max->value(value);
  ((Fl_Valuator *)
  cl_gts_gui.scrbar_color_trace_06_src_bb_max)->value(value);
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
	 case E_COLOR_TRACE_HAB_05:
  cl_gts_gui.valinp_color_trace_05_src_aa_min->value(value);
  ((Fl_Valuator *)
  cl_gts_gui.scrbar_color_trace_05_src_aa_min)->value(value);
		break;
	 case E_COLOR_TRACE_HAB_06:
  cl_gts_gui.valinp_color_trace_06_src_aa_min->value(value);
  ((Fl_Valuator *)
  cl_gts_gui.scrbar_color_trace_06_src_aa_min)->value(value);
		break;
	 }
	}
}

//----------
/* edit color window(設定して)表示/隠す */
void cb_color_trace_thickness::tgt_open_edit_color_( E_COLOR_TRACE_HAB_COLORS trace_list_pos )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.tgt_get_e_rgb_color();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_edit_color->shown();

 	cl_gts_master.cl_color_trace_enhancement.tgt_open_edit_color(
		trace_list_pos
	);

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.tgt_get_e_rgb_color()
	) {
		cl_gts_gui.window_edit_color->hide();
	}*/
}

//----------
/* 黒線として扱うただ一つのトレス色を選ぶ */
void cb_color_trace_thickness::tgt_change_black_( E_COLOR_TRACE_HAB_COLORS trace_list_pos )
{
	/* black off */
	if (	      E_COLOR_TRACE_HAB_01 != trace_list_pos
	 && cl_gts_gui.roubut_thickness_01_tgt_is_bl->value()) {
	    cl_gts_gui.roubut_thickness_01_tgt_is_bl->value(0);
			   this->cb_enh_01();
	}
	if (	      E_COLOR_TRACE_HAB_02 != trace_list_pos
	 && cl_gts_gui.roubut_thickness_02_tgt_is_bl->value()) {
	    cl_gts_gui.roubut_thickness_02_tgt_is_bl->value(0);
			   this->cb_enh_02();
	}
	if (	      E_COLOR_TRACE_HAB_03 != trace_list_pos
	 && cl_gts_gui.roubut_thickness_03_tgt_is_bl->value()) {
	    cl_gts_gui.roubut_thickness_03_tgt_is_bl->value(0);
			   this->cb_enh_03();
	}
	if (	      E_COLOR_TRACE_HAB_04 != trace_list_pos
	 && cl_gts_gui.roubut_thickness_04_tgt_is_bl->value()) {
	    cl_gts_gui.roubut_thickness_04_tgt_is_bl->value(0);
			   this->cb_enh_04();
	}
	if (	      E_COLOR_TRACE_HAB_05 != trace_list_pos
	 && cl_gts_gui.roubut_thickness_05_tgt_is_bl->value()) {
	    cl_gts_gui.roubut_thickness_05_tgt_is_bl->value(0);
			   this->cb_enh_05();
	}
	if (	      E_COLOR_TRACE_HAB_06 != trace_list_pos
	 && cl_gts_gui.roubut_thickness_06_tgt_is_bl->value()) {
	    cl_gts_gui.roubut_thickness_06_tgt_is_bl->value(0);
			   this->cb_enh_06();
	}
	/* black on */
	switch (trace_list_pos)
	{
	case E_COLOR_TRACE_HAB_01: this->cb_enh_01(); break;
	case E_COLOR_TRACE_HAB_02: this->cb_enh_02(); break;
	case E_COLOR_TRACE_HAB_03: this->cb_enh_03(); break;
	case E_COLOR_TRACE_HAB_04: this->cb_enh_04(); break;
	case E_COLOR_TRACE_HAB_05: this->cb_enh_05(); break;
	case E_COLOR_TRACE_HAB_06: this->cb_enh_06(); break;
	}
}

//--------------------------------------------------

/* tgtボタン : edit color window(設定して)表示/隠す */
void cb_color_trace_thickness::cb_tgt_show_hide_01( void )
{
	this->tgt_open_edit_color_(   E_COLOR_TRACE_HAB_01 );
}
void cb_color_trace_thickness::cb_tgt_show_hide_02( void )
{
	this->tgt_open_edit_color_(   E_COLOR_TRACE_HAB_02 );
}
void cb_color_trace_thickness::cb_tgt_show_hide_03( void )
{
	this->tgt_open_edit_color_(   E_COLOR_TRACE_HAB_03 );
}
void cb_color_trace_thickness::cb_tgt_show_hide_04( void )
{
	this->tgt_open_edit_color_(   E_COLOR_TRACE_HAB_04 );
}
void cb_color_trace_thickness::cb_tgt_show_hide_05( void )
{
	this->tgt_open_edit_color_(   E_COLOR_TRACE_HAB_05 );
}
void cb_color_trace_thickness::cb_tgt_show_hide_06( void )
{
	this->tgt_open_edit_color_(   E_COLOR_TRACE_HAB_06 );
}

//----------

/* tgt is blackボタン : 黒線として扱うただ一つのトレス色を選ぶ */
void cb_color_trace_thickness::cb_tgt_change_black_01( void )
{
	this->tgt_change_black_(   E_COLOR_TRACE_HAB_01 );
}
void cb_color_trace_thickness::cb_tgt_change_black_02( void )
{
	this->tgt_change_black_(   E_COLOR_TRACE_HAB_02 );
}
void cb_color_trace_thickness::cb_tgt_change_black_03( void )
{
	this->tgt_change_black_(   E_COLOR_TRACE_HAB_03 );
}
void cb_color_trace_thickness::cb_tgt_change_black_04( void )
{
	this->tgt_change_black_(   E_COLOR_TRACE_HAB_04 );
}
void cb_color_trace_thickness::cb_tgt_change_black_05( void )
{
	this->tgt_change_black_(   E_COLOR_TRACE_HAB_05 );
}
void cb_color_trace_thickness::cb_tgt_change_black_06( void )
{
	this->tgt_change_black_(   E_COLOR_TRACE_HAB_06 );
}

//----------

/* srcボタン : edit HSV MinMax window(設定して)表示/隠す */
void cb_color_trace_thickness::cb_src_show_hide_01( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cl_color_trace_enhancement.cb_src_show_01();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}*/
}
void cb_color_trace_thickness::cb_src_show_hide_02( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cl_color_trace_enhancement.cb_src_show_02();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}*/
}
void cb_color_trace_thickness::cb_src_show_hide_03( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cl_color_trace_enhancement.cb_src_show_03();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}*/
}
void cb_color_trace_thickness::cb_src_show_hide_04( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cl_color_trace_enhancement.cb_src_show_04();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}*/
}
void cb_color_trace_thickness::cb_src_show_hide_05( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cl_color_trace_enhancement.cb_src_show_05();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}*/
}
void cb_color_trace_thickness::cb_src_show_hide_06( void )
{
	/* トレス番号を取っておく */
	E_COLOR_TRACE_HAB_COLORS col = 
	cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range();

	/* 表示状態を取っておく */
//	const int before_shown_sw=cl_gts_gui.window_hab_histogram->shown();

	/* このトレス番号での表示を行い内部トレス番号も再セット */
	cl_gts_master.cl_color_trace_enhancement.cb_src_show_06();

	/* 既に、同じトレス番号で表示している場合、ウインドウを隠す */
/*	if ( before_shown_sw &&
 col == cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	) {
		cl_gts_gui.window_hab_histogram->hide();
	}*/
}

//----------
/* スクロールバー&数値 */
void cb_color_trace_thickness::cb_scrbar_01( const double value )
{
	cl_gts_gui.valinp_thickness_01->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_01
	    ,cl_gts_gui.roubut_thickness_01_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_01( const double value )
{
	((Fl_Valuator *)
	cl_gts_gui.scrbar_thickness_01)->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_01
	    ,cl_gts_gui.roubut_thickness_01_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_02( const double value )
{
	cl_gts_gui.valinp_thickness_02->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_02
	    ,cl_gts_gui.roubut_thickness_02_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_02( const double value )
{
	((Fl_Valuator *)
	cl_gts_gui.scrbar_thickness_02)->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_02
	    ,cl_gts_gui.roubut_thickness_02_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_03( const double value )
{
	     cl_gts_gui.valinp_thickness_03->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_03
	    ,cl_gts_gui.roubut_thickness_03_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_03( const double value )
{
	((Fl_Valuator *)
	     cl_gts_gui.scrbar_thickness_03)->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_03
	    ,cl_gts_gui.roubut_thickness_03_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_04( const double value )
{
	     cl_gts_gui.valinp_thickness_04->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_04
	    ,cl_gts_gui.roubut_thickness_04_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_04( const double value )
{
	((Fl_Valuator *)
	     cl_gts_gui.scrbar_thickness_04)->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_04
	    ,cl_gts_gui.roubut_thickness_04_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_05( const double value )
{
	     cl_gts_gui.valinp_thickness_05->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_05
	    ,cl_gts_gui.roubut_thickness_05_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_05( const double value )
{
	((Fl_Valuator *)
	     cl_gts_gui.scrbar_thickness_05)->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_05
	    ,cl_gts_gui.roubut_thickness_05_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

void cb_color_trace_thickness::cb_scrbar_06( const double value )
{
	     cl_gts_gui.valinp_thickness_06->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_06
	    ,cl_gts_gui.roubut_thickness_06_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}
void cb_color_trace_thickness::cb_valinp_06( const double value )
{
	((Fl_Valuator *)
	     cl_gts_gui.scrbar_thickness_06)->value(value);
	this->set_enh_val_and_scr_(
		       E_COLOR_TRACE_HAB_06
	    ,cl_gts_gui.roubut_thickness_06_tgt_is_bl->value()?true:false
		,value
	);
	cl_gts_master.cb_color_trace_src_edit_value();
}

//--------------------------------------------------

/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
void cb_color_trace_thickness::cb_enh_01( void )
{
	this->set_thickness_(
		    E_COLOR_TRACE_HAB_01
	 ,cl_gts_gui.roubut_thickness_01_tgt_is_bl->value()?true:false
	);
}

void cb_color_trace_thickness::cb_enh_02( void )
{
	this->set_thickness_(
		    E_COLOR_TRACE_HAB_02
	 ,cl_gts_gui.roubut_thickness_02_tgt_is_bl->value()?true:false
	);
}

void cb_color_trace_thickness::cb_enh_03( void )
{
	this->set_thickness_(
		    E_COLOR_TRACE_HAB_03
	 ,cl_gts_gui.roubut_thickness_03_tgt_is_bl->value()?true:false
	);
}

void cb_color_trace_thickness::cb_enh_04( void )
{
	this->set_thickness_(
		    E_COLOR_TRACE_HAB_04
	 ,cl_gts_gui.roubut_thickness_04_tgt_is_bl->value()?true:false
	);
}

void cb_color_trace_thickness::cb_enh_05( void )
{
	this->set_thickness_(
		    E_COLOR_TRACE_HAB_05
	 ,cl_gts_gui.roubut_thickness_05_tgt_is_bl->value()?true:false
	);
}

void cb_color_trace_thickness::cb_enh_06( void )
{
	this->set_thickness_(
		    E_COLOR_TRACE_HAB_06
	 ,cl_gts_gui.roubut_thickness_06_tgt_is_bl->value()?true:false
	);
}

//----------
/* "指定のトレス番号の値を"Color Trace Enhancement"で再表示 */
void cb_color_trace_thickness::set_scrbar_inpval(
	E_COLOR_TRACE_HAB_COLORS col_tra_num
)
{
	switch (col_tra_num) {
	case E_COLOR_TRACE_HAB_01: this->cb_enh_01(); break;
	case E_COLOR_TRACE_HAB_02: this->cb_enh_02(); break;
	case E_COLOR_TRACE_HAB_03: this->cb_enh_03(); break;
	case E_COLOR_TRACE_HAB_04: this->cb_enh_04(); break;
	case E_COLOR_TRACE_HAB_05: this->cb_enh_05(); break;
	case E_COLOR_TRACE_HAB_06: this->cb_enh_06(); break;
	}
}

//----------
/*
トレス色番号から、GUIのボタン(色)を再表示
トレス色番号を選択してない場合はなにもしない
*/
void cb_color_trace_thickness::tgt_redraw_rgb_color(
	E_COLOR_TRACE_HAB_COLORS trace_list_pos
)
{
	switch (trace_list_pos) {
	case E_COLOR_TRACE_HAB_01:
   cl_gts_gui.button_thickness_01_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_02:
   cl_gts_gui.button_thickness_02_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_03:
   cl_gts_gui.button_thickness_03_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_04:
   cl_gts_gui.button_thickness_04_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_05:
   cl_gts_gui.button_thickness_05_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_06:
   cl_gts_gui.button_thickness_06_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_NOT_SELECT: break;
	}
}

//----------
