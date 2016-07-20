#ifndef cb_color_trace_thickness_h
#define cb_color_trace_thickness_h

#include "calcu_color_trace_hab.h"

class cb_color_trace_thickness {
public:
	cb_color_trace_thickness()
	{
	}

	/* tgtボタン : edit color window(設定して)表示/隠す */
	void cb_tgt_show_hide_01( void );
	void cb_tgt_show_hide_02( void );
	void cb_tgt_show_hide_03( void );
	void cb_tgt_show_hide_04( void );
	void cb_tgt_show_hide_05( void );
	void cb_tgt_show_hide_06( void );

	/* tgt is blackボタン : 黒線として扱うただ一つのトレス色を選ぶ */
	void cb_tgt_change_black_01( void );
	void cb_tgt_change_black_02( void );
	void cb_tgt_change_black_03( void );
	void cb_tgt_change_black_04( void );
	void cb_tgt_change_black_05( void );
	void cb_tgt_change_black_06( void );

	/* srcボタン : edit HSV MinMax window(設定して)表示/隠す */
	void cb_src_show_hide_01( void );
	void cb_src_show_hide_02( void );
	void cb_src_show_hide_03( void );
	void cb_src_show_hide_04( void );
	void cb_src_show_hide_05( void );
	void cb_src_show_hide_06( void );

	/* スクロールバー&数値 */
	void cb_scrbar_01( const double value );
	void cb_scrbar_02( const double value );
	void cb_scrbar_03( const double value );
	void cb_scrbar_04( const double value );
	void cb_scrbar_05( const double value );
	void cb_scrbar_06( const double value );
	void cb_valinp_01( const double value );
	void cb_valinp_02( const double value );
	void cb_valinp_03( const double value );
	void cb_valinp_04( const double value );
	void cb_valinp_05( const double value );
	void cb_valinp_06( const double value );

	//------------------------------------------------------------

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	void cb_enh_01( void );
	void cb_enh_02( void );
	void cb_enh_03( void );
	void cb_enh_04( void );
	void cb_enh_05( void );
	void cb_enh_06( void );

	/* "指定のトレス番号の値を"Color Trace Enhancement"で再表示 */
	void set_scrbar_inpval( E_COLOR_TRACE_HAB_COLORS col_tra_num );

	/*
	トレス色番号から、GUIのボタン(色)を再表示
	トレス色番号を選択してない場合はなにもしない
	*/
	void tgt_redraw_rgb_color(
		E_COLOR_TRACE_HAB_COLORS trace_list_pos
	);

private:
	/* "Color Trace Enhancement"ウインドウの各val値を、
	"Thickness"ウインドウの各値に移し再表示 */
	void set_thickness_(
		const E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, const bool black_line_sw
	);

	/* 指定値で"Color Trace Enhancement"ウインドウの
	各scr,val値を設定再表示 */
	void set_enh_val_and_scr_(
		const E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, const bool black_line_sw
		, double value
	);

	/* edit color window(設定して)表示/隠す */
	void tgt_open_edit_color_(E_COLOR_TRACE_HAB_COLORS trace_list_pos);

	/* 黒線として扱うただ一つのトレス色を選ぶ */
	void tgt_change_black_( E_COLOR_TRACE_HAB_COLORS trace_list_pos );
};

#endif /* !cb_color_trace_thickness_h */
