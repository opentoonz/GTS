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
	int src_open_histogram_window( E_COLOR_TRACE_HAB_COLORS trace_list_pos );
	int src_set_histogram_window( E_COLOR_TRACE_HAB_COLORS trace_list_pos );
	int src_edit_hh( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		double d_min, double d_max );
	int src_edit_aa( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		double d_min, double d_max );
	int src_edit_bb( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
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

	/*
	トレス色番号から、fltkカラーテーブル番号を得る
	トレス色番号を選択してない場合は-1を返す
	*/
	int tgt_fl_color_number_from_trace_list_pos(
		E_COLOR_TRACE_HAB_COLORS trace_list_pos
	);
	/*
	トレス色番号から、GUIのボタン(色)を再表示
	トレス色番号を選択してない場合はなにもしない
	*/
	void tgt_redraw_rgb_color(
		E_COLOR_TRACE_HAB_COLORS trace_list_pos
	);

	/* 各8-bitのrgb値を、fltkカラーテーブル指定色に設定する */
	void tgt_fl_set_color(
		int color_number
		, unsigned char red , unsigned char gre , unsigned char blu
	);

	/*
	rgb値を、
	トレス色番号に対応する、fltkカラーテーブル指定色に設定する
	*/
	void tgt_set_uchar_rgb_color(
		E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, int red, int gre, int blu
	);
	/*
	トレス色番号に対応する、fltkカラーテーブル指定色から
	rgb値を得る
	*/
	void tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, unsigned char *red
		, unsigned char *gre
		, unsigned char *blu
	);

	/*
	edit color windowで値を変えたとき
	トレス色番号に対応する、fltkカラーテーブル指定色を設定する
	void color_trace_enhancement::tgt_redraw_rgb_color(-)も実行必要
	*/
	void tgt_edit_rgb_color( E_COLOR_TRACE_HAB_COLORS trace_list_pos );

	/*
	edit color windowを設定して表示する
	*/
	void tgt_open_edit_color( E_COLOR_TRACE_HAB_COLORS trace_list_pos );

	/*
	トレス色番号のゲッター/セッター
	*/
	void tgt_set_e_rgb_color( E_COLOR_TRACE_HAB_COLORS trace_list_pos )
	{
		this->_e_target_rgb_color = trace_list_pos;
	}
	E_COLOR_TRACE_HAB_COLORS tgt_get_e_rgb_color( void ) const
	{
		return this->_e_target_rgb_color;
	}

private:
	/* fltkカラーテーブル指定色から、各8-bitのrgb値を得る */
	void tgt_fl_get_color_(
		int color_number
		, unsigned char *red, unsigned char *gre, unsigned char *blu
	);

	int _src_get_p_hh_valinp( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		Fl_Value_Input **pp_min, Fl_Value_Input **pp_max );
	int _src_get_p_aa_valinp( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		Fl_Value_Input **pp_min, Fl_Value_Input **pp_max );
	int _src_get_p_bb_valinp( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		Fl_Value_Input **pp_min, Fl_Value_Input **pp_max );
	int _src_get_p_hh_scrbar( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		Fl_Valuator **pp_min, Fl_Valuator **pp_max );
	int _src_get_p_aa_scrbar( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		Fl_Valuator **pp_min, Fl_Valuator **pp_max );
	int _src_get_p_bb_scrbar( E_COLOR_TRACE_HAB_COLORS trace_list_pos,
		Fl_Valuator **pp_min, Fl_Valuator **pp_max );
	int _src_set_crnt_to_histogram( E_COLOR_TRACE_HAB_COLORS trace_list_pos );

	E_COLOR_TRACE_HAB_COLORS _e_source_color_range;
	E_COLOR_TRACE_HAB_COLORS _e_target_rgb_color;
};

#endif /* !__color_trace_enhancement_h__ */
