#include <math.h>
#include "pri.h"
#include "iip_opengl_l1edit.h"

void iip_opengl_l1edit::all_view( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_zoom_allview_and_scroll_center();
	this->_set_position();
}

void iip_opengl_l1edit::scroll_center( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_xp_center();
	this->_set_l_yp_center();
	this->_set_position();
}

void iip_opengl_l1edit::zoom_twice_at_center( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_zoom_twice( this->_l_view_x_size/2L, this->_l_view_y_size/2L );
	this->_set_position();
}
void iip_opengl_l1edit::zoom_half_at_center( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_zoom_half( this->_l_view_x_size/2L, this->_l_view_y_size/2L );
	this->_set_position();
}
void iip_opengl_l1edit::zoom_up_at_center( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_incr_zoom( this->_l_view_x_size/2L, this->_l_view_y_size/2L );
	this->_set_position();
}
void iip_opengl_l1edit::zoom_down_at_center( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_decr_zoom( this->_l_view_x_size/2L, this->_l_view_y_size/2L );
	this->_set_position();
}

void iip_opengl_l1edit::zoom_num( long l_zoom )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_direct_zoom(
		this->_l_view_x_size/2L,
		this->_l_view_y_size/2L,
		l_zoom );
	this->_set_position();
}

void iip_opengl_l1edit::scroll_left( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_l_xp -= this->_l_key_scroll_step;
	this->_set_position();
}
void iip_opengl_l1edit::scroll_to_left_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_xp_left_scroll();
	this->_set_position();
}
void iip_opengl_l1edit::fit_to_left_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_xp_left_side();
	this->_set_position();
}

void iip_opengl_l1edit::scroll_down( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_l_yp -= this->_l_key_scroll_step;
	this->_set_position();
}
void iip_opengl_l1edit::scroll_to_down_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_yp_down_scroll();
	this->_set_position();
}
void iip_opengl_l1edit::fit_to_down_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_yp_down_side();
	this->_set_position();
}

void iip_opengl_l1edit::scroll_up( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_l_yp += this->_l_key_scroll_step;
	this->_set_position();
}
void iip_opengl_l1edit::scroll_to_up_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_yp_up_scroll();
	this->_set_position();
}
void iip_opengl_l1edit::fit_to_up_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_yp_up_side();
	this->_set_position();
}

void iip_opengl_l1edit::scroll_right( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_l_xp += this->_l_key_scroll_step;
	this->_set_position();
}
void iip_opengl_l1edit::scroll_to_right_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_xp_right_scroll();
	this->_set_position();
}
void iip_opengl_l1edit::fit_to_right_side( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_set_l_xp_right_side();
	this->_set_position();
}

void iip_opengl_l1edit::zoom_twice_at_pos( long l_x, long l_y )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_zoom_twice(
		l_x - this->_l_view_x_pos,
		l_y - this->_l_view_y_pos
	);
	this->_set_position();
}
void iip_opengl_l1edit::zoom_half_at_pos( long l_x, long l_y )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_zoom_half(
		l_x - this->_l_view_x_pos,
		l_y - this->_l_view_y_pos
	);
	this->_set_position();
}
void iip_opengl_l1edit::zoom_up_at_pos( long l_x, long l_y )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_incr_zoom(
		l_x - this->_l_view_x_pos,
		l_y - this->_l_view_y_pos
	);
	this->_set_position();
}
void iip_opengl_l1edit::zoom_down_at_pos( long l_x, long l_y )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_decr_zoom(
		l_x - this->_l_view_x_pos,
		l_y - this->_l_view_y_pos
	);
	this->_set_position();
}

void iip_opengl_l1edit::drag_move_start( void )
{
	if (NULL == this->get_vp_canvas()) { return; }

	if (E_SELECT_IMAGE == this->_e_select_part) {
		this->_l_movestart_xp = this->_l_xp;
		this->_l_movestart_yp = this->_l_yp;
	} else {
		this->_edit_crop_start();
	}
}
void iip_opengl_l1edit::drag_move_stop( long l_move_x, long l_move_y )
{
	l_move_x;
	l_move_y;

	if (NULL == this->get_vp_canvas()) { return; }

	if (E_SELECT_IMAGE == this->_e_select_part) {
	/***
		this->_l_xp = this->_l_movestart_xp + l_move_x;
		this->_l_yp = this->_l_movestart_yp - l_move_y;
		this->_set_position();
	***/
	} else {
		this->_edit_crop_end();
	}
}
void iip_opengl_l1edit::drag_moving( long l_move_x, long l_move_y )
{
	if (NULL == this->get_vp_canvas()) { return; }

	if (E_SELECT_IMAGE == this->_e_select_part) {
		this->_l_xp = this->_l_movestart_xp + l_move_x;
		this->_l_yp = this->_l_movestart_yp - l_move_y;
		this->_set_position();
	} else {
		this->_edit_crop_moving(l_move_x,l_move_y);
	}
}
int iip_opengl_l1edit::mouse_moving( long l_mouse_x, long l_mouse_y )
{
	if (NULL == this->get_vp_canvas()) { return OFF; }

	return this->_select( l_mouse_x, l_mouse_y );/* Hover中に選択する */
}

void iip_opengl_l1edit::move_xy_pos( long l_xp, long l_yp )
{
	if (NULL == this->get_vp_canvas()) { return; }

	this->_l_xp = l_xp;
	this->_l_yp = l_yp;

	this->_set_position();
}

void iip_opengl_l1edit::scrollbar_x( long l_val, long l_min, long l_max)
{
	if (NULL == this->get_vp_canvas()) { return; }

	if (l_val == l_min) {
		this->_set_l_xp_left_side();
	} else if (l_val == l_max) {
		this->_set_l_xp_right_side();
	} else {
		this->_l_xp = -(long)(
			this->_d_zoom *
			this->get_l_width() *
			l_val / this->_l_view_x_size

			/*********this->_d_zoom *
			floor(	(double)l_val /
				this->_l_view_x_size *
				this->get_l_width()
			)*********/
		);
	}
	this->_set_position();
}
void iip_opengl_l1edit::scrollbar_y( long l_val, long l_min, long l_max)
{
	if (NULL == this->get_vp_canvas()) { return; }

	if (l_val == l_min) {
		this->_set_l_yp_up_side();
	} else if (l_val == l_max) {
		this->_set_l_yp_down_side();
	} else {
		this->_l_yp = -(long)(
			this->_d_zoom *
			this->get_l_height() *

		 (	(1.0 - (double)l_val / this->_l_view_y_size) -
		 	(double)(this->_l_view_y_size) /
		 	(this->_d_zoom * (double)this->get_l_height())
		 )
		);
	};
	this->_set_position();
}
