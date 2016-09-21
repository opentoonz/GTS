#ifndef __gts_master_h__
#define __gts_master_h__

#include <FL/Fl_Value_Input.H>
#include "fltk_event.h"

#include "gtsfbro06cb_config.h"
#include "gtsfbro06cb_level.h"
#include "gtsfbro06cb_trace_batch.h"

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
#include "cb_file_number_list.h"
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

	/* color histogram Min-Max windowの色ベルト画像表示設定 */
	void make_hab_belt_image( void );

	/* ユーザインターフェースからの実行(fltk callback) */
	void cb_config_load_dir( void );
	void cb_config_load_list( void );
	void cb_config_load_ok( void );
	void cb_config_save( void );
	void cb_config_save_as_dir( void );
	void cb_config_save_as_list( void );
	void cb_config_save_as_ok( void );
	void cb_choice_pixel_type( void );
	void cb_level_dir( void );
	void cb_level_rgb_scan_dir( void );
	void cb_level_mkdir( void );
	void cb_level_list( void );
	void cb_level_list_form_change( void );
	void cb_level_ok( void );
	void cb_quit( void );

	void cb_read_and_preview( void );
	void cb_read_and_trace( void );
	void cb_read_and_trace_and_preview( void );

	void cb_read_and_save_start( void );
	void cb_scan_and_preview( void );
	void cb_scan_and_save_start( void );
	void cb_scan_and_save_next( void );
	void cb_scan_and_save_prev( void );

	void cb_area_selecter( void );
	void cb_scnr_area_x_pos( void );
	void cb_scnr_area_y_pos( void );
	void cb_scnr_area_x_size( void );
	void cb_scnr_area_y_size( void );
	void cb_scnr_area_x_pixel( void );
	void cb_scnr_area_y_pixel( void );
	void cb_scnr_area_reso( void );
	void cb_area_aspect_ratio_selecter( void );
	void cb_scan_full_area_and_crop( void );
	void cb_rotate_per_90( void );

	void cb_color_trace_full_area( void );

	void cb_color_trace_src_edit_value( void );
	void cb_color_trace_src_redraw_image( void );
	void cb_color_trace_src_limit_nothing( void );
	void cb_color_trace_src_limit_hh( void );
	void cb_color_trace_src_limit_aa( void );
	void cb_color_trace_src_limit_bb( void );

	void cb_real_time_on_off( void );

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

	void change_level_dir_by_key_in( const char *cp_dir );
	void change_level_dir_by_click_list( const char *cp_dir );
	void change_level_dir_by_read_file( const char *cp_dir );

	/* マウス、キーボードからの実行(set_idle()使用) */
	void reserve( E_ACT e_act );
	void reserve_by_menu( E_ACT e_act );
	void reserve_by_key_event( E_ACT e_act );
	void reserve_by_scroll_x( int ii );
	void reserve_by_scroll_y( int ii );

	/* メニュー、クロップエリア、画像を同時に回転する */
	int rotate_per_90( void );

	/* スクロールバー設定 */
	void set_scrollbar( void );

	/* 回転値のメモリ */
	void set_i_rotate_per_90( int ii ) { this->_i_rotate_per_90=ii; }

	/* 表示エリアのみのトレス線処理 */
	void color_trace_in_view_area( void );


	/* クラスコンポーネント */
	gtsfbro06cb_config      cl_bro_config;
	gtsfbro06cb_level       cl_bro_level;
	gtsfbro06cb_trace_batch	cl_bro_trace_batch;

	fltk_event	cl_fltk_event;	/* イベントドリブン */
	memory_desktop	cl_memo_desktop;	/* desktopの再現 */
	memory_config	cl_memo_config;	/* 各パラメータの再現 */
	memory_scan_area	cl_memo_scan_area;
	memory_short_cut_key	cl_memo_short_cut_key;
	memory_install_setup	cl_memo_install_setup;

	cb_file_number_list	cl_file_number_list;

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

	int _print_window_headline( void );

private:
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	const char	*const _cp_release_name,
			*const _cp_release_date,
			*const _cp_release_number;

	int	_i_enable_act_menu_sw,
		_i_enable_act_key_event_sw;

	int	_i_rotate_per_90;

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
	void _move_start( void );
	void _move_drag( void );
	void _move_stop( void );
	void _move_passive( void );
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
	void __crop_area( int sw );
	void _crop_on( void );
	void _crop_off( void );
	void _escape( void );
	void _quit( void );

	int _iipg_rot90( iip_canvas *clp_parent, int i_rotate_per_90 = 0);

	void _iipg_color_trace_get_from_gui( void );
	int _iipg_color_trace_setup( void );
	void _iipg_color_trace_exec( int i_area_sw=OFF );

	void _iipg_mem_free( void );

	int _iipg_save( iip_canvas *clp_canvas, char *cp_path, double d_dpi, int i_rot90 = 0, iip_read *clp_read = NULL );

	int _iipg_view_setup( int i_max_area_sw=OFF );
	void iipg_view_redraw_( void );

	void _iipg_scan_set_physical_param( void );
	void _iipg_scan_get_from_gui( const bool full_area_sw );
	int _iipg_scan_action( const bool full_area_sw );
	iip_canvas *_iipg_scan( const bool full_area_sw=false );
	int _iipg_scan_get_scanner_info( void );

	void __area_rot90_d_pos_and_size( int i_rot90, double d_x, double d_y, double d_w, double d_h, double d_max_w, double d_max_h, double *dp_x, double *dp_y, double *dp_w, double *dp_h );
	void __area_rot90_l_pos_and_size( int i_rot90, long l_x, long l_y, long l_w, long l_h, long l_max_w, long l_max_h, long *lp_x, long *lp_y, long *lp_w, long *lp_h );
	void __area_rot90_size( int i_rot90, double d_w, double d_h, double *dp_w, double *dp_h );
	void _area_rot90_menu( int i_rot90_old, int i_rot90_new );
	void _area_rot90_openglrect( int i_rot90_old, int i_rot90_new );
	void _from_opengl_rect_to_area_val( void );
	void _from_area_val_to_opengl_rect( void );

	int _cb_open_text( char *cp_path );

	void _trace_batch_run( char *cp_path );
	void _trace_batch_add( char *cp_path );
	void _change_view_main( void );

	int next_scan_and_save_( void );
	int read_and_save_crnt_( void );

	void cb_change_wview_( E_WVIEW_TYPE wview_type );
};
extern gts_master cl_gts_master;

#endif /* !__gts_master_h__ */
