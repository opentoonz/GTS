#include <iostream>
#include "pri.h"
#include "iip_opengl_l3event.h"

void iip_opengl_l3event::init_opengl( void )
{
	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l3event::init_opengl(-)" );
	}

	this->_cl_all.init_opengl();
}

void iip_opengl_l3event::clear_opengl( long l_xs, long l_ys )
{
	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l3event::clear_opengl(-)" );
	}
	this->_cl_all.init_viewport( l_xs, l_ys );
	this->_cl_all.clear_viewport();
}

void iip_opengl_l3event::reshape_opengl( long l_view_xs, long l_view_ys )
{
	long	l_xp,l_yp,
		l_xs,l_ys,
		l_x1,l_x2,
		l_y1,l_y2;

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l3event::reshape_opengl(-)" );
	}

	this->_l_view_x_size = l_view_xs;
	this->_l_view_y_size = l_view_ys;

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
		break;
	case E_WVIEW_TYPE_MAIN:
		this->_cl_all.reshape_opengl(    0,0, l_view_xs,l_view_ys );
		this->_clp_main->reshape_opengl( 0,0, l_view_xs,l_view_ys );
		if (this->_clp_sub != nullptr) {
		 this->_clp_sub->reshape_opengl( 0,0, l_view_xs,l_view_ys );
		}
		break;
	case E_WVIEW_TYPE_SUB:
		this->_cl_all.reshape_opengl(    0,0, l_view_xs,l_view_ys );
		this->_clp_sub->reshape_opengl(  0,0, l_view_xs,l_view_ys );
		this->_clp_main->reshape_opengl( 0,0, l_view_xs,l_view_ys );
		break;

	/* 左右分割 */
	/* ここでは表示エリアを記憶するのみ */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		this->_cl_all.reshape_opengl(
			0,0, l_view_xs,l_view_ys);

		/* 左画像の右端+1(separeterの表示開始)位置 */
		l_x1 = (long)(this->_d_separete_x_ratio * l_view_xs)
			- (this->_l_seaprete_thickness / 2L);
		/* 右画像の左端(表示開始)位置 */
		l_x2 = l_x1 + this->_l_seaprete_thickness;

		l_xp = 0L;
		l_yp = 0L;
		l_xs = l_x1;
		l_ys = l_view_ys;
		this->_clp_main->reshape_opengl(
			l_xp,l_yp,
			l_xs,l_ys
		);

		l_xp = l_x2;
		l_yp = 0L;
		l_xs = l_view_xs - l_x2;
		l_ys = l_view_ys;
		this->_clp_sub->reshape_opengl(
			l_xp,l_yp,
			l_xs,l_ys
		);
		break;

	/* 上下分割 */
	/* ここでは表示エリアを記憶するのみ */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		this->_cl_all.reshape_opengl(
			0,0, l_view_xs,l_view_ys);

		/* 下画像の上端+1(separeterの表示開始)位置 */
		l_y1 = (long)(this->_d_separete_y_ratio * l_view_ys)
			- (this->_l_seaprete_thickness / 2L);
		/* 上画像の下端(表示開始)位置 */
		l_y2 = l_y1 + this->_l_seaprete_thickness;

		l_xp = 0L;
		l_yp = 0L;
		l_xs = l_view_xs;
		l_ys = l_y1;
		this->_clp_main->reshape_opengl(
			l_xp,l_yp,
			l_xs,l_ys
		);

		l_xp = 0L;
		l_yp = l_y2;
		l_xs = l_view_xs;
		l_ys = l_view_ys - l_y2;
		this->_clp_sub->reshape_opengl(
			l_xp,l_yp,
			l_xs,l_ys
		);
		break;
	}
}
void iip_opengl_l3event::from_cursor_pos_to_image_pos(
	const int cursor_pos_x ,const int cursor_pos_y	/* 左上原点 */
	,const int view_xs ,const int view_ys
	,int& image_pos_x ,int& image_pos_y		/* (注意)左下原点 */
)
{
	const int cursor_y_ = view_ys - cursor_pos_y;

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
		image_pos_x = -1;
		image_pos_y = -1;
		break;
	case E_WVIEW_TYPE_MAIN:
		this->_clp_main->from_cursor_pos_to_image_pos(
			cursor_pos_x ,cursor_y_
			,image_pos_x ,image_pos_y
		);
		break;
	case E_WVIEW_TYPE_SUB:
		this->_clp_sub->from_cursor_pos_to_image_pos(
			cursor_pos_x ,cursor_y_
			,image_pos_x ,image_pos_y
		);
		break;
	/* 左右分割 */
	/* ここでは表示エリアを記憶するのみ */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION: {
		/* 左画像の右端(separeterの表示開始)位置 */
		const int x1 = static_cast<int>(
			this->_d_separete_x_ratio * view_xs
		) - (this->_l_seaprete_thickness / 2L);

		/* 右画像の左端(表示開始)位置 */
		const int x2 = x1 + this->_l_seaprete_thickness;

		if (cursor_pos_x < x1) {	/* 左 */
			this->_clp_main->from_cursor_pos_to_image_pos(
				cursor_pos_x ,cursor_y_
				,image_pos_x ,image_pos_y
			);
		} else
		if (x2 <= cursor_pos_x) {	/* 右 */
			this->_clp_sub->from_cursor_pos_to_image_pos(
				cursor_pos_x-x2 ,cursor_y_
				,image_pos_x ,image_pos_y
			);
		}
		else {			/* どちらでもない(=separeter上) */
			image_pos_x = -1;
			image_pos_y = -1;
		}
		} break;
	/* 上下分割 */
	/* ここでは表示エリアを記憶するのみ */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION: {
		/* 下画像の上端(separeterの表示開始)位置 */
		const int y1 = static_cast<long>(
			this->_d_separete_y_ratio * view_ys
		) - (this->_l_seaprete_thickness / 2L);

		/* 上画像の下端(表示開始)位置 */
		const int y2 = y1 + this->_l_seaprete_thickness;

		if (cursor_y_ < y1) {	/* 下 */
			this->_clp_main->from_cursor_pos_to_image_pos(
				cursor_pos_x ,cursor_y_
				,image_pos_x ,image_pos_y
			);
		} else
		if (y2 <= cursor_y_) {	/* 上 */
			this->_clp_sub->from_cursor_pos_to_image_pos(
				cursor_pos_x ,cursor_y_ - y2
				,image_pos_x ,image_pos_y
			);
		}
		else {			/* どちらでもない(=separeter上) */
			image_pos_x = -1;
			image_pos_y = -1;
		}
		} break;
	default:
		image_pos_x = -1;
		image_pos_y = -1;
		break;
	}
}

void iip_opengl_l3event::draw_image_pixel_pos(
	const int image_pos_x ,const int image_pos_y
)
{
	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
		break;
	case E_WVIEW_TYPE_MAIN:
		this->_clp_main->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		);
		break;
	case E_WVIEW_TYPE_SUB:
		if (this->temporary_display_main_sw_) {
		 this->_clp_main->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		 );
		} else {
		 this->_clp_sub->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		 );
		}
		break;
	/* 左右分割 */
	/* ここでは表示エリアを記憶するのみ */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		this->_clp_main->reshape_opengl();
		this->_clp_main->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		);

		this->_clp_sub->reshape_opengl();
		if (this->temporary_display_main_sw_) {
		 this->_clp_main->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		 );
		} else {
		 this->_clp_sub->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		 );
		}
		break;
	/* 上下分割 */
	/* ここでは表示エリアを記憶するのみ */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		this->_clp_main->reshape_opengl();
		this->_clp_main->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		);

		this->_clp_sub->reshape_opengl();
		if (this->temporary_display_main_sw_) {
		 this->_clp_main->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		 );
		} else {
		 this->_clp_sub->draw_image_pixel_pos(
			image_pos_x ,image_pos_y
		 );
		}
		break;
	default:
		break;
	}
}
void iip_opengl_l3event::get_image_pixel(
	const int image_pos_x ,const int image_pos_y
	,int&r ,int&g ,int&b ,int&ch ,int&by ,int&bt
)
{
	this->_clp_main->get_image_pixel(
		image_pos_x ,image_pos_y
		,r,g,b,ch,by,bt
	);
}

void iip_opengl_l3event::draw_opengl( void )
{
	glClear( GL_COLOR_BUFFER_BIT );
	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
		break;
	case E_WVIEW_TYPE_MAIN:
		this->_clp_main->draw_opengl();
		break;
	case E_WVIEW_TYPE_SUB:
		if (this->temporary_display_main_sw_) {
		 this->_clp_main->draw_opengl();
		} else {
		 this->_clp_sub->draw_opengl();
		}
		break;

	/* 左右分割 */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		this->_clp_main->reshape_opengl();
		this->_clp_main->draw_opengl();

		this->_clp_sub->reshape_opengl();
		/* main画像のはみ出しをクリアする */
		if (1L < this->_clp_main->get_l_zoom()) {
			this->_draw_main_no_hamidasi_by_sub_view();
		}

		if (this->temporary_display_main_sw_) {
		 this->_clp_main->draw_opengl();
		} else {
		 this->_clp_sub->draw_opengl();
		}

		this->_cl_all.reshape_opengl();
		this->_draw_separeter();
		break;

	/* 上下分割 */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		this->_clp_main->reshape_opengl();
		this->_clp_main->draw_opengl();

		this->_clp_sub->reshape_opengl();
		/* main画像のはみ出しをクリアする */
		if (1L < this->_clp_main->get_l_zoom()) {
			this->_draw_main_no_hamidasi_by_sub_view();
		}

		if (this->temporary_display_main_sw_) {
		 this->_clp_main->draw_opengl();
		} else {
		 this->_clp_sub->draw_opengl();
		}

		this->_cl_all.reshape_opengl();
		this->_draw_separeter();
		break;
	}
	glFlush(); /* Redhat9ではこれがないとGL_LINE_LOOP表示しない */
}

/*--------------------------------------------------------*/

void iip_opengl_l3event::_draw_separeter( void )
{
	GLdouble gld_x1=0,gld_y1=0, gld_x2=0,gld_y2=0;

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
	case E_WVIEW_TYPE_MAIN:
	case E_WVIEW_TYPE_SUB:
		return;

	/* 左右分割 */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		/* 左画像の右端+1(separeterの表示開始)位置 */
		gld_x1 = (long)
			(this->_d_separete_x_ratio * this->_l_view_x_size)
			- (this->_l_seaprete_thickness / 2L);
		/* 右画像の左端(表示開始)位置 */
		gld_x2 = gld_x1 + this->_l_seaprete_thickness;
		gld_y1 = 0.0;
		gld_y2 = this->_l_view_y_size - 1.0;
		break;

	/* 上下分割 */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		gld_x1 = 0.0;
		gld_x2 = this->_l_view_x_size - 1.0;
		/* 下画像の上端+1(separeterの表示開始)位置 */
		gld_y1 = (long)
			(this->_d_separete_y_ratio * this->_l_view_y_size)
			- (this->_l_seaprete_thickness / 2L);
		/* 上画像の下端(表示開始)位置 */
		gld_y2 = gld_y1 + this->_l_seaprete_thickness;
		break;
	}

	glColor3d( 0.75, 0.75, 0.75 );
	glBegin(GL_QUADS);

	glVertex2d( gld_x1, gld_y1 );
	glVertex2d( gld_x1, gld_y2 );
	glVertex2d( gld_x2, gld_y2 );
	glVertex2d( gld_x2, gld_y1 );

	glEnd();
}

void iip_opengl_l3event::_draw_main_no_hamidasi_by_sub_view( void )
{
	GLdouble gld_x1=0,gld_y1=0, gld_x2=0,gld_y2=0;

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
	case E_WVIEW_TYPE_MAIN:
	case E_WVIEW_TYPE_SUB:
		return;

	/* 左右分割 */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		gld_x1 = 0.0;
		gld_x2 = 16.0;
		gld_y1 = 0.0;
		gld_y2 = this->_l_view_y_size - 1.0;
		break;

	/* 上下分割 */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		gld_x1 = 0.0;
		gld_x2 = this->_l_view_x_size - 1.0;
		gld_y1 = 0.0;
		gld_y2 = 16.0;
		break;
	}

	glColor3d( 0.5, 0.5, 0.5 );
	glBegin(GL_QUADS);
	glVertex2d( gld_x1, gld_y1 );
	glVertex2d( gld_x1, gld_y2 );
	glVertex2d( gld_x2, gld_y2 );
	glVertex2d( gld_x2, gld_y1 );
	glEnd();
}
