#ifndef __iip_opengl_l1edit_h__
#define __iip_opengl_l1edit_h__

# if defined(HAVE_CONFIG_H)
#  include <config.h>
# endif

#if defined _WIN32
#include <windows.h>
#endif

# if defined(HAVE_CONFIG_H)
#  if defined(HAVE_GL_GLU_H)
#   include <GL/glu.h>
#  elif defined(HAVE_OPENGL_GLU_H)
#   include <OpenGL/glu.h>
#  else
#   error no glu.h
#  endif
# else
// non-autotools build
#  include <GL/glu.h>
# endif

#include "iip_canvas.h"

/* iip_canvas.h CH_RED,CH_GRE,CH_BLU,CH_ALP,and... */
#ifndef	CH_RGB
#define	CH_RGB (CH_ALP+1)
#endif

typedef enum {
	E_SELECT_NOTHING = 1
	,E_SELECT_IMAGE
	,E_SELECT_LEFTBOTTOM
	,E_SELECT_LEFT
	,E_SELECT_LEFTTOP
	,E_SELECT_TOP
	,E_SELECT_RIGHTTOP
	,E_SELECT_RIGHT
	,E_SELECT_RIGHTBOTTOM
	,E_SELECT_BOTTOM
	,E_SELECT_CENTER
} E_SELECT_PART;

class iip_opengl_l1edit : public iip_canvas {
public:
	iip_opengl_l1edit() {
		this->_l_view_x_pos = 0L;
		this->_l_view_y_pos = 0L;
		this->_l_view_x_size = 0L;
		this->_l_view_y_size = 0L;

		this->_l_xp = 0L;
		this->_l_yp = 0L;
		this->_l_movestart_xp = 0L;
		this->_l_movestart_yp = 0L;
		this->_d_zoom = 1.0;
		this->_l_zoom = 1L;

		this->_glsi_width = (GLsizei)0;
		this->_glsi_height = (GLsizei)0;
		this->_gli_skip_pixels = (GLint)0;
		this->_gli_skip_rows = (GLint)0;
		this->_gli_rasterpos_x = (GLint)0;
		this->_gli_rasterpos_y = (GLint)0;
		this->_gle_format = GL_RGB;
		this->_gle_type = GL_UNSIGNED_BYTE;
		this->_i_disp_ch = CH_RGB;

		this->_ucharp_rrggbbaa = NULL;
		this->_l_key_scroll_step = /*100L*/1L;

		/*	
		 0L Pixel単位スクロールI
		16L 拡大表示時もスムーススクロール(x16倍まで)
		*/
		this->_l_margin_for_zoomup_smooth_scroll = 0L/*16L*/;

		this->_d_scrollbar_x_min = 0.0;
		this->_d_scrollbar_x_max = 0.0;
		this->_d_scrollbar_y_min = 0.0;
		this->_d_scrollbar_y_max = 0.0;

		this->_l_crop_xp = 0L;
		this->_l_crop_yp = 0L;
		this->_l_crop_width = 0L;
		this->_l_crop_height = 0L;
		this->_l_crop_xp_backup_for_cancel = 0L;
		this->_l_crop_yp_backup_for_cancel = 0L;
		this->_l_crop_width_backup_for_cancel = 0L;
		this->_l_crop_height_backup_for_cancel = 0L;

		this->_i_crop_disp_sw = OFF;
		this->_l_crop_select_radius = 8L;

		this->_e_select_part = E_SELECT_NOTHING;

		this->crop_aspect_ratio_w = 0.0; /* 2013-11-28追加 */
		this->crop_aspect_ratio_h = 0.0; /* 2013-11-28追加 */
	}

	/* rgb(a)画像の時、channel表示のための画像参照 */
	void set_ucp_rrggbbaa( unsigned char *ucp ) {
		this->_ucharp_rrggbbaa = ucp;
	}

	/* 新しい画面(Window or Widget等)で一回実行 */
	void init_viewport( long l_xs, long l_ys, long l_xp = 0L, long l_yp = 0L);

	/* init_viewport()のエリアをglClear()する */
	void clear_viewport( void );

	long get_l_view_x_size( void ) { return this->_l_view_x_size; }
	long get_l_view_y_size( void ) { return this->_l_view_y_size; }

	void init_opengl( void );

	/* 画像データ変更のとき設定 */
	void init_channel( void );

	/* 表示エリア変更のとき実行
	引数あり→なおかつエリア変更→表示エリア変更
	引数なし→記憶してあるエリアに再設定
	*/
	void reshape_opengl( long l_xp = 0L, long l_yp = 0L, long l_xs = 0L, long l_ys = 0L );

	/* 拡大縮小、スクロール、チャンネル変更 */
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
	void drag_moving( long l_move_x, long l_move_y );
	int mouse_moving( long l_mouse_x, long l_mouse_y );
	void move_smooth( void )
	{ this->_l_margin_for_zoomup_smooth_scroll = 16L; }
	void move_pixel( void )
	{ this->_l_margin_for_zoomup_smooth_scroll = 0L; }
	void move_xy_pos( long l_xp, long l_yp );


	/* Scroll Barよるスクロール */
	void scrollbar_x( long l_val, long l_min, long l_max);
	void scrollbar_y( long l_val, long l_min, long l_max);

	/* Scroll Barを変更 */
	double      get_d_scrollbar_x_min( void )
	{ return this->_d_scrollbar_x_min; }
	double      get_d_scrollbar_x_max( void )
	{ return this->_d_scrollbar_x_max; }
	double      get_d_scrollbar_y_min( void )
	{ return this->_d_scrollbar_y_min; }
	double      get_d_scrollbar_y_max( void )
	{ return this->_d_scrollbar_y_max; }

	/* 情報表示のためにズーム値を得る */
	long get_l_zoom() { return this->_l_zoom; }
	/* 2画面表示で位置を合わせるために位置を得る */
	long get_l_xp( void ) { return this->_l_xp; }
	long get_l_yp( void ) { return this->_l_yp; }

	/* 表示(OpenGL) */
	void draw_opengl( void );

	/* 切抜きエリアの表示 */
	void set_i_crop_disp_sw( int sw )
	{
		this->_i_crop_disp_sw=sw;
		if (OFF == sw) {
			this->_e_select_part = E_SELECT_IMAGE;
		}
	}
	/* 切抜きエリア */
	void set_crop_full_image( void ) {
		if (this->_l_crop_width == 0) {
			this->_l_crop_xp = 0L;
			this->_l_crop_yp = 0L;
			this->_l_crop_width = this->get_l_width();
			this->_l_crop_height = this->get_l_height();
		}
	}

	void edit_crop_cancel( void );

	/* 切抜き情報 */
	long get_l_crop_xp( void ) { return this->_l_crop_xp; }
	long get_l_crop_yp( void ) { return this->_l_crop_yp; }
	long get_l_crop_width( void ) { return this->_l_crop_width; }
	long get_l_crop_height( void ) { return this->_l_crop_height; }

	E_SELECT_PART get_e_select_part( void )
	{ return this->_e_select_part; }

	void set_crop_area(long l_xpos, long l_ypos, long l_xsize, long l_ysize );

	/* 表示データの部分処理のための情報 */
	int get_i_glcrop_xpos(void) { return this->_gli_skip_pixels; }
	int get_i_glcrop_ypos(void) { return this->_gli_skip_rows; }
	int get_i_glcrop_width(void) { return this->_glsi_width; }
	int get_i_glcrop_height(void) { return this->_glsi_height; }

	double crop_aspect_ratio_w; /* 2013-11-28追加 */
	double crop_aspect_ratio_h; /* 2013-11-28追加 */
private:
	long	_l_view_x_pos,
		_l_view_y_pos,
		_l_view_x_size,
		_l_view_y_size;

	long	_l_xp,
		_l_yp;
	long	_l_movestart_xp,
		_l_movestart_yp;
	long	_l_zoom;
	double	_d_zoom;

	GLsizei	_glsi_width,
		_glsi_height;
	GLint	_gli_skip_pixels,
		_gli_skip_rows;
	GLint	_gli_rasterpos_x,
		_gli_rasterpos_y;
	GLenum	_gle_format,
		_gle_type;
	int	_i_disp_ch;

	unsigned char *_ucharp_rrggbbaa;
	long	_l_key_scroll_step;
	long	_l_margin_for_zoomup_smooth_scroll;
	double	_d_scrollbar_x_min, _d_scrollbar_x_max,
		_d_scrollbar_y_min, _d_scrollbar_y_max;

	/* zoom関係 */
	void __incr_l_zoom( void );
	void __decr_l_zoom( void );
	void __set_d_zoom( double d_zoom, long l_x_pos, long l_y_pos );

	void _decr_zoom( long l_xp, long l_yp );
	void _incr_zoom( long l_xp, long l_yp );
	void _zoom_twice( long l_xp, long l_yp );
	void _zoom_half( long l_xp, long l_yp );
	void _direct_zoom( long l_xp, long l_yp, long l_zoom );
	void _set_zoom_x1_and_center( void );
	void _zoom_allview_and_scroll_center( void );

	/* scroll関係 */
	void _set_l_xp_left_scroll( void );
	void _set_l_xp_right_scroll( void );
	void _set_l_xp_left_side( void );
	void _set_l_xp_right_side( void );
	void _set_l_xp_center( void );
	void _set_l_yp_up_scroll( void );
	void _set_l_yp_down_scroll( void );
	void _set_l_yp_up_side( void );
	void _set_l_yp_down_side( void );
	void _set_l_yp_center( void );

	/* 表示の内部計算 */
	void _set_position( void );

	/* 各パーツの表示 */
	void _draw_image( void );
	void _draw_crop( void );
	void _draw_crop_picker( double d_xp, double d_yp );
	void _get_crop_disp_area( double d_image_xp, double d_image_yp, double d_crop_xp, double d_crop_yp, double d_crop_xs, double d_crop_ys, double *dp_x1, double *dp_y1, double *dp_x2, double *dp_y2 );

	/* channelの情報の表示 */
	void _pri_ch_info( void );

	void edit_crop_fix_aspect_ratio_(	
		int i_xp_moved_sw, int i_yp_moved_sw
	); /* 2013-11-28追加 */

	/* 切抜きパラメータ */
	long	_l_crop_xp,
		_l_crop_yp,	/* 切り取る画像の開始位置 */
		_l_crop_width,
		_l_crop_height;	/* 切り取る画像の大きさ */
	long	_l_crop_xp_backup_for_cancel,
		_l_crop_yp_backup_for_cancel,
		_l_crop_width_backup_for_cancel,
		_l_crop_height_backup_for_cancel;

	int	_i_crop_disp_sw;
	long	_l_crop_select_radius;	/* 掴む部分の半径 */

	E_SELECT_PART _e_select_part;

	int _select( long l_xp, long l_yp );
	E_SELECT_PART _selection_crop_picker( long l_xp, long l_yp );

	void _edit_crop_start( void );
	void _edit_crop_end( void );
	void _edit_crop_moving( long l_move_x, long l_move_y );

	void _edit_crop_move_part(long l_move_x, long l_move_y, int *ip_xp_moved_sw, int *ip_yp_moved_sw);
	void _edit_crop_limit(int i_xp_moved_sw, int i_yp_moved_sw);
};

#endif /* !__iip_opengl_l1edit_h__ */
