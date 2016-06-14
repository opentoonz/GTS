#ifndef __color_trace_enhancement_h__
#define __color_trace_enhancement_h__

#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Valuator.H>
#include "calcu_color_trace_hab.h"

class color_trace_enhancement {
public:
	color_trace_enhancement()
	{
	 this->_e_source_color_range = E_COLOR_TRACE_HAB_NOT_SELECT;
	 this->_e_target_rgb_color   = E_COLOR_TRACE_HAB_NOT_SELECT;
	}

	E_COLOR_TRACE_HAB_COLORS src_get_e_color_range( void )
	{	   return this->_e_source_color_range; }
	int src_open_histogram_window( E_COLOR_TRACE_HAB_COLORS e_num );
	int src_set_histogram_window( E_COLOR_TRACE_HAB_COLORS e_num );
	int src_edit_hh( E_COLOR_TRACE_HAB_COLORS e_num,
		double d_min, double d_max );
	int src_edit_aa( E_COLOR_TRACE_HAB_COLORS e_num,
		double d_min, double d_max );
	int src_edit_bb( E_COLOR_TRACE_HAB_COLORS e_num,
		double d_min, double d_max );

	void src_set_histogram_max( void );
	void src_set_hh_min_max( double d_min, double d_max );
	void src_set_aa_min_max( double d_min, double d_max );
	void src_set_bb_min_max( double d_min, double d_max );
	void src_set_range_is_nothing( void );
	void src_set_range_is_hh( void );
	void src_set_range_is_aa( void );
	void src_set_range_is_bb( void );
	void src_init_histogram_window( void );
	void src_set_from_gui( void );

	void tgt_set_e_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num )
	{ this->_e_target_rgb_color = e_num; }
	E_COLOR_TRACE_HAB_COLORS tgt_get_e_rgb_color( void )
	{	   return this->_e_target_rgb_color; }
	void tgt_open_edit_color( E_COLOR_TRACE_HAB_COLORS e_num );
	void tgt_edit_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num );
	void tgt_get_uchar_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num,
		unsigned char *ucharp_red, unsigned char *ucharp_gre,
		unsigned char *ucharp_blu );
	void tgt_set_uchar_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num,
		int i_red, int i_gre, int i_blu );

private:
	E_COLOR_TRACE_HAB_COLORS _e_source_color_range;
	E_COLOR_TRACE_HAB_COLORS _e_target_rgb_color;

	int _src_get_p_hh_valinp( E_COLOR_TRACE_HAB_COLORS e_num,
		Fl_Value_Input **pp_min, Fl_Value_Input **pp_max );
	int _src_get_p_aa_valinp( E_COLOR_TRACE_HAB_COLORS e_num,
		Fl_Value_Input **pp_min, Fl_Value_Input **pp_max );
	int _src_get_p_bb_valinp( E_COLOR_TRACE_HAB_COLORS e_num,
		Fl_Value_Input **pp_min, Fl_Value_Input **pp_max );
	int _src_get_p_hh_scrbar( E_COLOR_TRACE_HAB_COLORS e_num,
		Fl_Valuator **pp_min, Fl_Valuator **pp_max );
	int _src_get_p_aa_scrbar( E_COLOR_TRACE_HAB_COLORS e_num,
		Fl_Valuator **pp_min, Fl_Valuator **pp_max );
	int _src_get_p_bb_scrbar( E_COLOR_TRACE_HAB_COLORS e_num,
		Fl_Valuator **pp_min, Fl_Valuator **pp_max );
	int _src_set_crnt_to_histogram( E_COLOR_TRACE_HAB_COLORS e_num );

	int _tgt_get_i_color_number( E_COLOR_TRACE_HAB_COLORS e_num );
	int _tgt_set_rgb_color( int i_color_number );
	int _tgt_set_uchar_rgb_color( int i_color_number,
		unsigned char uchar_red, unsigned char uchar_gre,
		unsigned char uchar_blu );
	int _tgt_redraw_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num );
	int _tgt_get_uchar_rgb_color( int i_color_number, unsigned char *ucharp_red, unsigned char *ucharp_gre, unsigned char *ucharp_blu );
	void _tgt_set_uchar_edit_color( unsigned char uchar_red, unsigned char uchar_gre, unsigned char uchar_blu );
};

#endif /* !__color_trace_enhancement_h__ */
