#ifndef __iip_opengl_l3event_h__
#define __iip_opengl_l3event_h__

#include "iip_opengl_l2data.h"

typedef enum {
	E_WVIEW_TYPE_NOTHING = 1,
	E_WVIEW_TYPE_MAIN,
	E_WVIEW_TYPE_SUB,
	E_WVIEW_TYPE_LR_PARALLEL,	/* Left/Right */
	E_WVIEW_TYPE_LR_ONION,
	E_WVIEW_TYPE_UD_PARALLEL,	/* Up/Down */
	E_WVIEW_TYPE_UD_ONION,
} E_WVIEW_TYPE;

typedef enum {
	E_WVIEW_AREA_EXCEPT = 1,
	E_WVIEW_AREA_MAIN,
	E_WVIEW_AREA_SEPARATOR,
	E_WVIEW_AREA_SUB,
} E_WVIEW_AREA;

class iip_opengl_l3event {
public:
	iip_opengl_l3event( void )
	{
		this->_i_mv_sw = OFF;
		this->_i_pv_sw = OFF;
		this->_i_cv_sw = OFF;

		this->_e_wview_type = E_WVIEW_TYPE_MAIN;
		this->_d_separete_x_ratio = 0.5;
		this->_d_separete_y_ratio = 0.5;
		this->_l_seaprete_thickness = 5L;

		this->_l_view_x_size = 0L;
		this->_l_view_y_size = 0L;

		this->_clp_main = NULL;
		this->_clp_sub = NULL;
		this->temporary_display_main_sw_ = false;
	}
	void set_i_mv_sw( int sw ) {
		this->_i_mv_sw = sw;
		this->_cl_unt_view[0].set_i_mv_sw( sw );
		this->_cl_unt_view[1].set_i_mv_sw( sw );
	}
	void set_i_pv_sw( int sw ) {
		this->_i_pv_sw = sw;
		this->_cl_unt_view[0].set_i_pv_sw( sw );
		this->_cl_unt_view[1].set_i_pv_sw( sw );
	}
	void set_i_cv_sw( int sw ) {
		this->_i_cv_sw = sw;
		this->_cl_unt_view[0].set_i_cv_sw( sw );
		this->_cl_unt_view[1].set_i_cv_sw( sw );
	}
	int get_i_mv_sw( void ) { return this->_i_mv_sw; }
	int get_i_pv_sw( void ) { return this->_i_pv_sw; }
	int get_i_cv_sw( void ) { return this->_i_cv_sw; }

	int set_imagedata( iip_canvas *clp_parent_main, iip_canvas *clp_parent_sub );
	void init_viewparam( long l_view_xs, long l_view_ys );

	void init_opengl( void );
	void clear_opengl( long l_xs, long l_ys );

	void reshape_opengl( long l_view_xs, long l_view_ys );

	void draw_opengl( void );

	void wview_main( void );
	void wview_sub( void );
	void wview_lr_parallel( void );
	void wview_lr_onion( void );
	void wview_ud_parallel( void );
	void wview_ud_onion( void );

	void all_view( void );
	void scroll_center( void );
	void zoom_twice_at_center( void );
	void zoom_half_at_center( void );
	void zoom_up_at_center( void );
	void zoom_down_at_center( void );
	void zoom_num( long l_zoom );
	void scroll_left( void );
	void scroll_to_left_side( void );
	void fit_to_left_side( void );
	void scroll_down( void );
	void scroll_to_down_side( void );
	void fit_to_down_side( void );
	void scroll_up( void );
	void scroll_to_up_side( void );
	void fit_to_up_side( void );
	void scroll_right( void );
	void scroll_to_right_side( void );
	void fit_to_right_side( void );

	void set_channel( int i_src, int i_tgt );

	void zoom_twice_at_pos( long l_x, long l_y );
	void zoom_half_at_pos( long l_x, long l_y );
	void zoom_up_at_pos( long l_x, long l_y );
	void zoom_down_at_pos( long l_x, long l_y );
	void drag_move_start( void );
	void drag_move_stop( long l_move_x, long l_move_y );
	void drag_moving(
		long l_move_x ,long l_move_y
		,double crop_aspect_ratio_w ,double crop_aspect_ratio_h
	);
	int mouse_moving( long l_mouse_x, long l_mouse_y );
	void move_smooth( void );
	void move_pixel( void );
	void crop_area( int sw );
	void escape_motion( void );

	void scrollbar_x(long l_val, long l_min, long l_max);
	void scrollbar_y(long l_val, long l_min, long l_max);

	double get_d_scrollbar_x_min( void );
	double get_d_scrollbar_x_max( void );
	double get_d_scrollbar_y_min( void );
	double get_d_scrollbar_y_max( void );

	long get_l_zoom( void );

	iip_opengl_l1edit *get_clp_iip_view( void );

	void set_i_bw_use_uchar_sw( int sw ) {
		this->_cl_unt_view[0].set_i_bw_use_uchar_sw( sw );
		this->_cl_unt_view[1].set_i_bw_use_uchar_sw( sw );
	}
	int is_main_canvas( void )
	{	return	(NULL != this->_clp_main) &&
			(NULL != this->_clp_main->get_vp_canvas());
	}
	void no_view_canvas( void )
	{
		this->_clp_main = NULL;
		this->_clp_sub = NULL;
		//this->_e_wview_type = E_WVIEW_TYPE_NOTHING;
	}

	/* 切抜き編集情報 */
	long get_l_width( void );
	long get_l_height( void );
	long get_l_crop_xp( void );
	long get_l_crop_yp( void );
	long get_l_crop_width( void );
	long get_l_crop_height( void );
	E_SELECT_PART get_e_select_part( void );
	void set_crop_area(long l_xpos, long l_ypos, long l_xsize, long l_ysize );

	/* 部分処理用情報 */
	int get_i_glcrop_xpos( void );
	int get_i_glcrop_ypos( void );
	int get_i_glcrop_width( void );
	int get_i_glcrop_height( void );
	iip_canvas *get_clp_sub_canvas( void );

	E_WVIEW_TYPE get_e_wview_type( void )
	{  return this->_e_wview_type; }

	void set_temporary_display_main_sw(bool sw)
	{ this->temporary_display_main_sw_ = sw; }

private:
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	E_WVIEW_TYPE	_e_wview_type;
	double	_d_separete_x_ratio,
		_d_separete_y_ratio;
	long	_l_seaprete_thickness;

	long	_l_view_x_size,_l_view_y_size;

	/* ２分割画面の参照 */
	iip_opengl_l1edit *_clp_main, *_clp_sub;

	/* ２分割したときの全体を表す
	init_opengl(),viewport(),ortho2d()使用 */
	iip_opengl_l1edit _cl_all;

	/* ２分割画面の本体 */
	iip_opengl_l2data _cl_unt_view[2];

	/* 2値化表示を同位置でスキャン画像に切替表示するためのスイッチ */
	bool temporary_display_main_sw_;

	void _draw_separeter( void );
	void _draw_main_no_hamidasi_by_sub_view( void );

	void _wview( E_WVIEW_TYPE e_type );
	char *_get_cp_wview_type( E_WVIEW_TYPE e_type );
	void _set_pos_and_zoom_from_main_to_sub( void );
	void _set_pos_and_zoom_from_sub_to_main( void );
	E_WVIEW_AREA _select_area( long l_mouse_xp, long l_mouse_yp );
};

#endif /* !__iip_opengl_l3event_h__ */
