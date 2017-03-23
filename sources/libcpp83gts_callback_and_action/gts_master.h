#ifndef __gts_master_h__
#define __gts_master_h__

#include <FL/Fl_Value_Input.H>
#include "fltk_event.h"

#if defined _WIN32
#include "tw_win_l4_scan.h"
#else
#include "sane_scan.h"
#endif

#include "iip_rot90.h"
#include "iip_write.h"
#include "iip_read.h"
#include "iip_opengl_l3event.h"
#include "calcu_color_trace_hab.h"
#include "iip_color_trace_hab.h"
#include "iip_erase_dot_noise.h"

#include "memory_desktop.h"
#include "memory_config.h"
#include "cb_config.h"
#include "cb_area_and_rot90.h"
#include "cb_scan_and_save.h"
#include "cb_trace_files.h"
#include "cb_number.h"
#include "cb_trace_batch.h"
#include "cb_input_number_format.h"
#include "cb_color_trace_edit_color.h"
#include "cb_color_trace_edit_hsv_minmax.h"
#include "cb_color_trace_enhancement.h"
#include "cb_color_trace_thickness.h"
#include "memory_scan_area.h"
#include "memory_short_cut_key.h"
#include "memory_install_setup.h"

class gts_master {
public:
	gts_master(
		const char *const app_name
		,const char *const rele_num
		,const char *const rele_date
	);

	int  i_mv_sw( void ) const;
	void i_mv_sw( int sw );
	int  i_pv_sw( void ) const;
	void i_pv_sw( int sw );
	int  i_cv_sw( void ) const;
	void i_cv_sw( int sw );

	const char *const cp_release_name( void ) const;
	//void  cp_release_name( char *cp_name );
	const char *const cp_release_date( void ) const;
	//void  cp_release_date( char *cp_date );
	const char *const cp_release_number( void ) const;
	//void  cp_release_number( char *cp_num );

	/* fltkウインドウ表示、イベントループへ */
	int exec( const char *comm );

	/* 関数から呼ぶためMethodにしてあるが、意味としてはprivate */
	void action( E_ACT e_act );

	/* 実行 */
	void cb_choice_pixel_type_title( const std::string& str );
	void cb_choice_pixel_type_menu( void );
	void cb_quit( void );

	void cb_read_and_preview( void );
	void cb_read_and_trace_and_preview( void );
	void cb_rot_trace_enoise_preview( void );

	void cb_scan_and_preview( void );

	void cb_color_trace_src_edit_value( void );
	void cb_color_trace_src_limit_nothing( void );
	void cb_color_trace_src_limit_hh( void );
	void cb_color_trace_src_limit_aa( void );
	void cb_color_trace_src_limit_bb( void );

	bool check_change_wview( void );
	void cb_change_wview_main( void );
	void cb_change_wview_sub( void );
	void cb_change_wview_lr( void );
	void cb_change_wview_ud( void );

	void cb_trace_batch_add( void );
	void cb_trace_batch_alladd( void );
	void cb_trace_batch_dir( void );
	void cb_trace_batch_list( void );
	void cb_trace_batch_run( void );

	/* ディレクトリ移動時のgui表示の変更 */
	void change_config_dir_by_input_load_dir( const char *cp_dir );
	void change_config_dir_by_input_save_as_dir( const char *cp_dir );
	void change_config_dir_by_click_list( const char *cp_dir );
	void change_config_dir_by_read_file( const char *cp_dir );

	void change_trace_batch_dir( const char *cp_dir );

	/* マウス、キーボードからの実行(set_idle()使用) */
	void reserve( E_ACT e_act );
	void reserve_by_menu( E_ACT e_act );
	void reserve_by_key_event( E_ACT e_act );
	void reserve_by_scroll_x( int ii );
	void reserve_by_scroll_y( int ii );

	/* スクロールバー設定 */
	void set_scrollbar( void );

	/* 表示エリアのみのトレス線処理 */
	void color_trace_in_view_area( void );


	/* クラスコンポーネント */
	fltk_event	cl_fltk_event;	/* イベントドリブン */
	memory_desktop	cl_memo_desktop;	/* desktopの再現 */
	memory_config	cl_memo_config;	/* 各パラメータの再現 */
	memory_scan_area	cl_memo_scan_area;
	memory_short_cut_key	cl_memo_short_cut_key;
	memory_install_setup	cl_memo_install_setup;

	cb_config		cl_config;
	cb_area_and_rot90	cl_area_and_rot90;
	cb_scan_and_save	cl_scan_and_save;
	cb_trace_files		cl_trace_files;
	cb_number		cl_number;
	cb_trace_batch		cl_trace_batch;
	cb_input_number_format	cl_input_number_format;

	cb_color_trace_edit_color	cl_color_trace_edit_color;
	cb_color_trace_edit_hsv_minmax	cl_color_trace_edit_hsv_minmax;
	cb_color_trace_enhancement	cl_color_trace_enhancement;
	cb_color_trace_thickness	cl_color_trace_thickness;

	iip_scan	cl_iip_scan;	/* 画像読み込み */
	iip_read	cl_iip_read;	/* 画像読込み */
	iip_rot90	cl_iip_ro90;	/* 画像の正対 */
	calcu_color_trace_hab	cl_cal_trac;
	iip_color_trace_hab	cl_iip_trac;	/* BL,R,G,Bトレース */
	iip_erase_dot_noise	cl_iip_edot;
	iip_opengl_l3event cl_ogl_view;	/* OpenGL表示用unit */
	iip_write	cl_iip_writ;	/* 画像保存 */

	int print_window_headline( void );

	int rot_and_trace_and_enoise( // Rot90 and Effects
		iip_canvas *parent
		, int rotate_per_90_type 
	);
	void rot_and_trace_and_enoise_and_preview(
		iip_canvas *parent
		,int rotate_per_90_type
		,const bool crop_sw=false
		,const bool force_view_scanimage_sw=false
	);

	int redraw_image(
		iip_canvas *parent
		, const bool crop_sw
		, const bool force_view_scanimage_sw
	);

	int iipg_save(
		iip_canvas *clp_canvas ,char *cp_path ,double d_dpi
		,int i_rot90 = 0 ,iip_read *clp_read = NULL
	);
	iip_canvas *iipg_scan(
		int&return_code/* OK/NG/CANCEL*/
		,const bool full_area_sw=false
	);

private:
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	const char	*const _cp_release_name,
			*const _cp_release_date,
			*const _cp_release_number;

	int	_i_enable_act_menu_sw,
		_i_enable_act_key_event_sw;

	int _make_level_frame_number_list( void );
	int _read_and_view_frame_number_list_1st_image( void );

	void _next_scan_number( void );
	void _all_view( void );
	void _zoom_up_twice_at_cen( void );
	void _zoom_down_half_at_cen( void );
	void _zoom_up_step_at_cen( void );
	void _zoom_down_step_at_cen( void );
	void __zoom_num( long l_zoom );
	void _zoom_d16( void );
	void _zoom_d08( void );
	void _zoom_d04( void );
	void _zoom_d02( void );
	void _zoom_e01( void );
	void _zoom_u02( void );
	void _zoom_u04( void );
	void _zoom_u08( void );
	void _zoom_u16( void );
	void _zoom_up_twice_at_pos( void );
	void _zoom_down_half_at_pos( void );
	void _zoom_up_step_at_pos( void );
	void _zoom_down_step_at_pos( void );
	void _scroll_center( void );
	void _scroll_left_side( void );
	void _scroll_right_side( void );
	void _scroll_up_side( void );
	void _scroll_down_side( void );
	void _scroll_left_step( void );
	void _scroll_right_step( void );
	void _scroll_up_step( void );
	void _scroll_down_step( void );
	void _scroll_leftside_step( void );
	void _scroll_rightside_step( void );
	void _scroll_upside_step( void );
	void _scroll_downside_step( void );
	void _scroll_block( void );
	void _scroll_smooth( void );
	void _scroll_x_absolute( void );
	void _scroll_y_absolute( void );

	void _move_hover( void );
	void _move_start( void );
	void _move_drag( void );
	void _move_stop( void );

	void __set_channel( int i_src, int i_tgt );
	void _channel_rgb_to_rgb( void );
	void _channel_red_to_red( void );
	void _channel_gre_to_gre( void );
	void _channel_blu_to_blu( void );
	void _channel_alp_to_gray( void );
	void _channel_red_to_gray( void );
	void _channel_gre_to_gray( void );
	void _channel_blu_to_gray( void );
	void _wview_main( void );
	void _wview_sub( void );
	void _wview_lr_parallel( void );
	void _wview_ud_parallel( void );
	void _wview_lr_onion( void );
	void _wview_ud_onion( void );
	void _crop_on( void );
	void _crop_off( void );
	void _escape( void );
	void _quit( void );

	int _iipg_rot90( iip_canvas *clp_parent, int i_rotate_per_90 = 0);

	void _iipg_color_trace_get_from_gui( void );
	int _iipg_color_trace_setup( void );
	void _iipg_color_trace_exec( int i_area_sw=OFF );

	void _iipg_mem_free( void );

	int _iipg_view_setup( int i_max_area_sw=OFF );


	int _cb_open_text( char *cp_path );

	void _trace_batch_run( char *cp_path );
	void _trace_batch_add( char *cp_path );

	void cb_change_wview_( E_WVIEW_TYPE wview_type );

	int iipg_scan_get_scanner_info_( void );

	int iipg_scan_open_setup_unit_get_spec_( void );
	int iipg_scan_action_( const bool scan_full_area_sw );
};
extern gts_master cl_gts_master;

#endif /* !__gts_master_h__ */
