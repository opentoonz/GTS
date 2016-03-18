#include <stdlib.h>	/* labs() */
#include <math.h>	/* ceil() */
#include "iip_opengl_l1edit.h"

void iip_opengl_l1edit::_set_l_xp_left_scroll( void )
{
	long	l_pos;

	/* このスクロール後もまだ絵の一番左側は見えない */
	if ( ( this->_l_xp + this->_l_key_scroll_step ) < 0L ) {
		this->_l_xp = this->_l_xp + this->_l_key_scroll_step;
	}
	else {
		l_pos = 0L;
		/* 絵の一番左側が見えている場合 */
		if (this->_l_key_scroll_step < this->_gli_rasterpos_x) {
			l_pos = this->_gli_rasterpos_x -
				this->_l_key_scroll_step;
		}
		this->_l_xp = l_pos;
	}
}
void iip_opengl_l1edit::_set_l_xp_right_scroll( void )
{
	double	dd;

	/* ウインドウの右側を絵の右側に会わせるための、絵の位置 */
	dd = (	(double)this->_l_view_x_size -
		(this->_d_zoom * (double)this->get_l_width())
	);

	if ((this->_l_margin_for_zoomup_smooth_scroll <= 0L)
	&&  (1.0 < this->_d_zoom)) {
		/* 右端が見える位置へ */
		dd /= this->_d_zoom;
		dd = floor(dd);
		dd *= this->_d_zoom;
	}

	/* 絵の一番右側が見えている場合 */
	if ( (this->_l_xp+this->_l_key_scroll_step) < (long)floor(dd) ) {
		this->_l_xp = this->_l_xp + this->_l_key_scroll_step;
	} else {

		/* このスクロール後もまだ絵の一番右側は見えない */
		if (0L < (
			labs( this->_l_xp - (long)floor(dd) ) -
			this->_l_key_scroll_step
		) ) {
			this->_l_xp = this->_l_xp -
					this->_l_key_scroll_step;
		}
		/* 絵の一番右側 */
		else {
			this->_l_xp = (long)floor(dd);
		}
	}
}
void iip_opengl_l1edit::_set_l_xp_left_side( void )
{
	this->_l_xp = 0L;
}
void iip_opengl_l1edit::_set_l_xp_right_side( void )
{
	double	dd;

	/* ウインドウの右側を絵の右側に会わせるための、絵の位置 */
	dd = (	(double)this->_l_view_x_size -
		(this->_d_zoom * (double)this->get_l_width())
	);

	if ((this->_l_margin_for_zoomup_smooth_scroll <= 0L)
	&&  (1.0 < this->_d_zoom)) {
		/* 右端が見える位置へ */
		dd /= this->_d_zoom;
		dd = floor(dd);
		dd *= this->_d_zoom;
	}

	this->_l_xp = (long)floor(dd);
}

void iip_opengl_l1edit::_set_l_xp_center( void )
{
	double	dd;
	dd = (	(double)this->_l_view_x_size -
		(this->_d_zoom * (double)this->get_l_width())
	) / 2.0;
	this->_l_xp = (long)floor(dd);
}

/*-------------------------------------------------------*/

void iip_opengl_l1edit::_set_l_yp_down_scroll( void )
{
	long	l_pos;

	/* このスクロール後もまだ絵の一番下側は見えない */
	if ( ( this->_l_yp + this->_l_key_scroll_step ) < 0L ) {
		this->_l_yp = this->_l_yp + this->_l_key_scroll_step;
	}
	else {
		l_pos = 0L;
		/* 絵の一番下側が見えている場合 */
		if (this->_l_key_scroll_step < this->_gli_rasterpos_y) {
			l_pos = this->_gli_rasterpos_y -
				this->_l_key_scroll_step;
		}
		this->_l_yp = l_pos;
	}
}
void iip_opengl_l1edit::_set_l_yp_up_scroll( void )
{
	double	dd;

	/* ウインドウの上側を絵の上側に会わせるための、絵の位置 */
	dd = (	(double)this->_l_view_y_size -
		(this->_d_zoom * (double)this->get_l_height())
	);

	if ((this->_l_margin_for_zoomup_smooth_scroll <= 0L)
	&&  (1.0 < this->_d_zoom)) {
		/* 上端が見える位置へ */
		dd /= this->_d_zoom;
		dd = floor(dd);
		dd *= this->_d_zoom;
	}

	/* 絵の一番上側が見えている場合 */
	if ( (this->_l_yp+this->_l_key_scroll_step) < (long)floor(dd) ) {
		this->_l_yp = this->_l_yp + this->_l_key_scroll_step;
	} else {

		/* このスクロール後もまだ絵の一番上側は見えない */
		if (0L < (
			labs( this->_l_yp - (long)floor(dd) ) -
			this->_l_key_scroll_step
		) ) {
			this->_l_yp = this->_l_yp -
					this->_l_key_scroll_step;
		}
		/* 絵の一番上側 */
		else {
			this->_l_yp = (long)floor(dd);
		}
	}
}
void iip_opengl_l1edit::_set_l_yp_up_side( void )
{
	double	dd;

	/* ウインドウの上側を絵の上側に会わせるための、絵の位置 */
	dd = (	(double)this->_l_view_y_size -
		(this->_d_zoom * (double)this->get_l_height())
	);

	/* 上位置が見える位置 */
	if ((this->_l_margin_for_zoomup_smooth_scroll <= 0L)
	&&  (1.0 < this->_d_zoom)) {
		/* 上端が見える位置へ */
		dd /= this->_d_zoom;
		dd = floor(dd);
		dd *= this->_d_zoom;
	}

	this->_l_yp = (long)floor(dd);
}
void iip_opengl_l1edit::_set_l_yp_down_side( void )
{
	this->_l_yp = (long)0;
}
void iip_opengl_l1edit::_set_l_yp_center( void )
{
	double	dd;
	dd = (	(double)this->_l_view_y_size -
		(this->_d_zoom * (double)this->get_l_height())
	) / 2.0;
	this->_l_yp = (long)floor(dd);
}

/*-------------------------------------------------------*/
/*************** void iip_opengl_l1edit::scrollbar_x( double d_pos )
{
	this->_l_xp = (long)(
		d_pos *
		this->_d_zoom *
		(double)this->get_l_width()
	);
}
void iip_opengl_l1edit::scrollbar_y( double d_pos )
{
	this->_l_yp = (long)(
		d_pos *
		this->_d_zoom *
		(double)this->get_l_height()
	);
}****************/
