#include "cb_color_trace_thickness.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {
 void set_tgt_color_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const int color_choice_from_gui
 )
 {
	unsigned char tgt_r;
	unsigned char tgt_g;
	unsigned char tgt_b;
	switch (color_choice_from_gui)
	{
	case 0: tgt_r = 0;    tgt_g = 0;    tgt_b = 0;    break; // BL
	case 1: tgt_r = 0xff; tgt_g = 0;    tgt_b = 0;    break; // R
	case 2: tgt_r = 0;    tgt_g = 0xff; tgt_b = 0;    break; // G
	case 3: tgt_r = 0;    tgt_g = 0;    tgt_b = 0xff; break; // B
	}
	cl_gts_master.cl_color_trace_enhancement.set_fl_color_of_table(
		cl_gts_master.cl_color_trace_enhancement.fl_color_table_from_trace_list_pos(trace_list_pos)
		,tgt_r ,tgt_g ,tgt_b
	);
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
 void set_src_color_(
	const E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, const int color_choice_from_gui
 )
 {
	int hmin,hmax;
	int smin,smax;
	int vmin,vmax;
	switch (color_choice_from_gui)
	{
	case 0: hmin=  0; hmax=360; smin=  0; smax=100; vmin=  0;vmax=-1;
		break; // BL
	case 1: hmin=300; hmax= 60; smin= -1; smax=100; vmin=  0;vmax=100;
		break; // R
	case 2: hmin= 60; hmax=180; smin= -1; smax=100; vmin=  0;vmax=100;
		break; // G
	case 3: hmin=180; hmax=300; smin= -1; smax=100; vmin=  0;vmax=100;
		break; // B
	}
	switch (trace_list_pos)
	{
	case E_COLOR_TRACE_HAB_01:
		if (0 <= hmin) {
 cl_gts_gui.scrbar_color_trace_01_src_hh_min->value(hmin);
 cl_gts_gui.valinp_color_trace_01_src_hh_min->value(hmin);
 		}
		if (0 <= hmax) {
 cl_gts_gui.scrbar_color_trace_01_src_hh_max->value(hmax);
 cl_gts_gui.valinp_color_trace_01_src_hh_max->value(hmax);
 		}
		if (0 <= smin) {
 cl_gts_gui.scrbar_color_trace_01_src_aa_min->value(smin);
 cl_gts_gui.valinp_color_trace_01_src_aa_min->value(smin);
 		}
		if (0 <= smax) {
 cl_gts_gui.scrbar_color_trace_01_src_aa_max->value(smax);
 cl_gts_gui.valinp_color_trace_01_src_aa_max->value(smax);
 		}
		if (0 <= vmin) {
 cl_gts_gui.scrbar_color_trace_01_src_bb_min->value(vmin);
 cl_gts_gui.valinp_color_trace_01_src_bb_min->value(vmin);
 		}
		if (0 <= vmax) {
 cl_gts_gui.scrbar_color_trace_01_src_bb_max->value(vmax);
 cl_gts_gui.valinp_color_trace_01_src_bb_max->value(vmax);
 		}
		break;
	case E_COLOR_TRACE_HAB_02:
		if (0 <= hmin) {
 cl_gts_gui.scrbar_color_trace_02_src_hh_min->value(hmin);
 cl_gts_gui.valinp_color_trace_02_src_hh_min->value(hmin);
 		}
		if (0 <= hmax) {
 cl_gts_gui.scrbar_color_trace_02_src_hh_max->value(hmax);
 cl_gts_gui.valinp_color_trace_02_src_hh_max->value(hmax);
 		}
		if (0 <= smin) {
 cl_gts_gui.scrbar_color_trace_02_src_aa_min->value(smin);
 cl_gts_gui.valinp_color_trace_02_src_aa_min->value(smin);
 		}
		if (0 <= smax) {
 cl_gts_gui.scrbar_color_trace_02_src_aa_max->value(smax);
 cl_gts_gui.valinp_color_trace_02_src_aa_max->value(smax);
 		}
		if (0 <= vmin) {
 cl_gts_gui.scrbar_color_trace_02_src_bb_min->value(vmin);
 cl_gts_gui.valinp_color_trace_02_src_bb_min->value(vmin);
 		}
		if (0 <= vmax) {
 cl_gts_gui.scrbar_color_trace_02_src_bb_max->value(vmax);
 cl_gts_gui.valinp_color_trace_02_src_bb_max->value(vmax);
 		}
		break;
	case E_COLOR_TRACE_HAB_03:
		if (0 <= hmin) {
 cl_gts_gui.scrbar_color_trace_03_src_hh_min->value(hmin);
 cl_gts_gui.valinp_color_trace_03_src_hh_min->value(hmin);
 		}
		if (0 <= hmax) {
 cl_gts_gui.scrbar_color_trace_03_src_hh_max->value(hmax);
 cl_gts_gui.valinp_color_trace_03_src_hh_max->value(hmax);
 		}
		if (0 <= smin) {
 cl_gts_gui.scrbar_color_trace_03_src_aa_min->value(smin);
 cl_gts_gui.valinp_color_trace_03_src_aa_min->value(smin);
 		}
		if (0 <= smax) {
 cl_gts_gui.scrbar_color_trace_03_src_aa_max->value(smax);
 cl_gts_gui.valinp_color_trace_03_src_aa_max->value(smax);
 		}
		if (0 <= vmin) {
 cl_gts_gui.scrbar_color_trace_03_src_bb_min->value(vmin);
 cl_gts_gui.valinp_color_trace_03_src_bb_min->value(vmin);
 		}
		if (0 <= vmax) {
 cl_gts_gui.scrbar_color_trace_03_src_bb_max->value(vmax);
 cl_gts_gui.valinp_color_trace_03_src_bb_max->value(vmax);
 		}
		break;
	case E_COLOR_TRACE_HAB_04:
		if (0 <= hmin) {
 cl_gts_gui.scrbar_color_trace_04_src_hh_min->value(hmin);
 cl_gts_gui.valinp_color_trace_04_src_hh_min->value(hmin);
 		}
		if (0 <= hmax) {
 cl_gts_gui.scrbar_color_trace_04_src_hh_max->value(hmax);
 cl_gts_gui.valinp_color_trace_04_src_hh_max->value(hmax);
 		}
		if (0 <= smin) {
 cl_gts_gui.scrbar_color_trace_04_src_aa_min->value(smin);
 cl_gts_gui.valinp_color_trace_04_src_aa_min->value(smin);
 		}
		if (0 <= smax) {
 cl_gts_gui.scrbar_color_trace_04_src_aa_max->value(smax);
 cl_gts_gui.valinp_color_trace_04_src_aa_max->value(smax);
 		}
		if (0 <= vmin) {
 cl_gts_gui.scrbar_color_trace_04_src_bb_min->value(vmin);
 cl_gts_gui.valinp_color_trace_04_src_bb_min->value(vmin);
 		}
		if (0 <= vmax) {
 cl_gts_gui.scrbar_color_trace_04_src_bb_max->value(vmax);
 cl_gts_gui.valinp_color_trace_04_src_bb_max->value(vmax);
 		}
		break;
	}
 }
}
//-----------------------------------------------------------
void cb_color_trace_thickness::init( void )
{
	this->cb_preset01(
		cl_gts_gui.choice_thickness_01_tgt_src_preset->value()
	);
	this->cb_preset02(
		cl_gts_gui.choice_thickness_02_tgt_src_preset->value()
	);
	this->cb_preset03(
		cl_gts_gui.choice_thickness_03_tgt_src_preset->value()
	);
	this->cb_preset04(
		cl_gts_gui.choice_thickness_04_tgt_src_preset->value()
	);
}

void cb_color_trace_thickness::cb_preset01( const int choice )
{
	set_tgt_color_( E_COLOR_TRACE_HAB_01 ,choice );
	set_src_color_( E_COLOR_TRACE_HAB_01 ,choice );
}

void cb_color_trace_thickness::cb_preset02( const int choice )
{
	set_tgt_color_( E_COLOR_TRACE_HAB_02 ,choice );
	set_src_color_( E_COLOR_TRACE_HAB_02 ,choice );
}

void cb_color_trace_thickness::cb_preset03( const int choice )
{
	set_tgt_color_( E_COLOR_TRACE_HAB_03 ,choice );
	set_src_color_( E_COLOR_TRACE_HAB_03 ,choice );
}

void cb_color_trace_thickness::cb_preset04( const int choice )
{
	set_tgt_color_( E_COLOR_TRACE_HAB_04 ,choice );
	set_src_color_( E_COLOR_TRACE_HAB_04 ,choice );
}
