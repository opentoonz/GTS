#ifndef cb_color_trace_enhancement_h
#define cb_color_trace_enhancement_h

#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Valuator.H>
#include "calcu_color_trace_hab.h"

class cb_color_trace_enhancement {
public:
	cb_color_trace_enhancement()
		:_e_source_color_range(E_COLOR_TRACE_HAB_NOT_SELECT)
		,_e_target_rgb_color(  E_COLOR_TRACE_HAB_NOT_SELECT)
	{
	}

	//---------- color trace enhancedment scrbar
	void cb_scrbar_src_hh_min_01( const double val );
	void cb_scrbar_src_hh_max_01( const double val );
	void cb_scrbar_src_aa_min_01( const double val );
	void cb_scrbar_src_aa_max_01( const double val );
	void cb_scrbar_src_bb_min_01( const double val );
	void cb_scrbar_src_bb_max_01( const double val );

	void cb_scrbar_src_hh_min_02( const double val );
	void cb_scrbar_src_hh_max_02( const double val );
	void cb_scrbar_src_aa_min_02( const double val );
	void cb_scrbar_src_aa_max_02( const double val );
	void cb_scrbar_src_bb_min_02( const double val );
	void cb_scrbar_src_bb_max_02( const double val );

	void cb_scrbar_src_hh_min_03( const double val );
	void cb_scrbar_src_hh_max_03( const double val );
	void cb_scrbar_src_aa_min_03( const double val );
	void cb_scrbar_src_aa_max_03( const double val );
	void cb_scrbar_src_bb_min_03( const double val );
	void cb_scrbar_src_bb_max_03( const double val );

	void cb_scrbar_src_hh_min_04( const double val );
	void cb_scrbar_src_hh_max_04( const double val );
	void cb_scrbar_src_aa_min_04( const double val );
	void cb_scrbar_src_aa_max_04( const double val );
	void cb_scrbar_src_bb_min_04( const double val );
	void cb_scrbar_src_bb_max_04( const double val );

	void cb_scrbar_src_hh_min_05( const double val );
	void cb_scrbar_src_hh_max_05( const double val );
	void cb_scrbar_src_aa_min_05( const double val );
	void cb_scrbar_src_aa_max_05( const double val );
	void cb_scrbar_src_bb_min_05( const double val );
	void cb_scrbar_src_bb_max_05( const double val );

	void cb_scrbar_src_hh_min_06( const double val );
	void cb_scrbar_src_hh_max_06( const double val );
	void cb_scrbar_src_aa_min_06( const double val );
	void cb_scrbar_src_aa_max_06( const double val );
	void cb_scrbar_src_bb_min_06( const double val );
	void cb_scrbar_src_bb_max_06( const double val );

	//---------- color trace enhancedment valinp
	void cb_valinp_src_hh_min_01( const double val );
	void cb_valinp_src_hh_max_01( const double val );
	void cb_valinp_src_aa_min_01( const double val );
	void cb_valinp_src_aa_max_01( const double val );
	void cb_valinp_src_bb_min_01( const double val );
	void cb_valinp_src_bb_max_01( const double val );

	void cb_valinp_src_hh_min_02( const double val );
	void cb_valinp_src_hh_max_02( const double val );
	void cb_valinp_src_aa_min_02( const double val );
	void cb_valinp_src_aa_max_02( const double val );
	void cb_valinp_src_bb_min_02( const double val );
	void cb_valinp_src_bb_max_02( const double val );

	void cb_valinp_src_hh_min_03( const double val );
	void cb_valinp_src_hh_max_03( const double val );
	void cb_valinp_src_aa_min_03( const double val );
	void cb_valinp_src_aa_max_03( const double val );
	void cb_valinp_src_bb_min_03( const double val );
	void cb_valinp_src_bb_max_03( const double val );

	void cb_valinp_src_hh_min_04( const double val );
	void cb_valinp_src_hh_max_04( const double val );
	void cb_valinp_src_aa_min_04( const double val );
	void cb_valinp_src_aa_max_04( const double val );
	void cb_valinp_src_bb_min_04( const double val );
	void cb_valinp_src_bb_max_04( const double val );

	void cb_valinp_src_hh_min_05( const double val );
	void cb_valinp_src_hh_max_05( const double val );
	void cb_valinp_src_aa_min_05( const double val );
	void cb_valinp_src_aa_max_05( const double val );
	void cb_valinp_src_bb_min_05( const double val );
	void cb_valinp_src_bb_max_05( const double val );

	void cb_valinp_src_hh_min_06( const double val );
	void cb_valinp_src_hh_max_06( const double val );
	void cb_valinp_src_aa_min_06( const double val );
	void cb_valinp_src_aa_max_06( const double val );
	void cb_valinp_src_bb_min_06( const double val );
	void cb_valinp_src_bb_max_06( const double val );

	// Use edit hsv minmax valinp
	void cb_src_hh_min( const double val );
	void cb_src_hh_max( const double val );
	void cb_src_aa_min( const double val );
	void cb_src_aa_max( const double val );
	void cb_src_bb_min( const double val );
	void cb_src_bb_max( const double val );

	//-------------
	void cb_tgt_show_01( void );
	void cb_tgt_show_02( void );
	void cb_tgt_show_03( void );
	void cb_tgt_show_04( void );
	void cb_tgt_show_05( void );
	void cb_tgt_show_06( void );

 /* color trace enhancement windowから番号指定してhistogram windowを開く */
	void cb_src_show_01( void );
	void cb_src_show_02( void );
	void cb_src_show_03( void );
	void cb_src_show_04( void );
	void cb_src_show_05( void );
	void cb_src_show_06( void );

	//-------------
	E_COLOR_TRACE_HAB_COLORS src_get_e_color_range( void )
	{
		return this->_e_source_color_range;
	}
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
	/* fltkカラーテーブル指定色から、各8-bitのrgb値を得る */
	void tgt_fl_get_color(
		int color_number
		, unsigned char *red, unsigned char *gre, unsigned char *blu
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
	void cb_color_trace_enhancement::tgt_redraw_rgb_color(-)も実行必要
	*/
	void tgt_edit_rgb_color( E_COLOR_TRACE_HAB_COLORS trace_list_pos );

	/*
	トレス色番号のゲッター/セッター
	*/
	E_COLOR_TRACE_HAB_COLORS tgt_get_e_rgb_color( void ) const
	{
		return this->_e_target_rgb_color;
	}

	/* edit color windowを設定して表示する */
	void tgt_open_edit_color(E_COLOR_TRACE_HAB_COLORS trace_list_pos);

private:
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

	/* edit hsv minmax windowを設定して表示する */
	int src_open_histogram_window_( E_COLOR_TRACE_HAB_COLORS trace_list_pos );

	E_COLOR_TRACE_HAB_COLORS _e_source_color_range;
	E_COLOR_TRACE_HAB_COLORS _e_target_rgb_color;
};

#endif /* !cb_color_trace_enhancement_h */
