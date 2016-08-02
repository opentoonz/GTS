#include <stdio.h>
#include <math.h>	/* floor() */
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "ptbl_returncode.h"
#include "fltk_1000_range_cyclic.h"
#if !defined GTS_DEBUG
#include "gts_master.h"
#endif

fltk_1000_range_cyclic::fltk_1000_range_cyclic(int x,int y,int w,int h,const char *l) : Fl_Box(x,y,w,h,l)
{
	//this->_l_x_min = -1000;
	//this->_l_x_max = -1000;
	this->_l_x_min = 0;
	this->_l_x_max = 1;
	this->_cp_title = NULL;

	this->_l_x_min_at_push = -1000;
	this->_l_x_max_at_push = -1000;
	this->_l_x_min_at_drag = -1000,
	this->_l_x_max_at_drag = -1000;


	this->_l_x_min2 = -1000;
	this->_l_x_max2 = -1000;
	this->_l_x_center = -1000;
	this->_l_x_center2 = -1000;

	this->_l_y_pos = 24;
	this->_l_term_radius = 24;
	this->_l_center_radius = 12;

	this->_e_select_type = E_NO_SELECT_TYPE;
	this->_l_x_drag_start = 0;
}

/*--------------------------------------------------------*/

void fltk_1000_range_cyclic::_draw_term_mark( long l_x, long l_y, char *cp_name )
{
	/* 選択枠と文字表示 */
	fl_color(FL_DARK3);
	fl_loop(
		l_x - this->_l_term_radius,
		l_y - this->_l_term_radius,
		l_x + this->_l_term_radius,
		l_y - this->_l_term_radius,
		l_x + this->_l_term_radius,
		l_y + this->_l_term_radius,
		l_x - this->_l_term_radius,
		l_y + this->_l_term_radius
	);
	fl_draw(
		cp_name,
		l_x - this->_l_term_radius*5/6,
		l_y + this->_l_term_radius*5/6
	);

	/* 矢印 */
	fl_color(FL_BLACK);
	fl_line(
		l_x - this->_l_term_radius/3,
		l_y - this->_l_term_radius/3,
		l_x,
		l_y - this->_l_term_radius + 1,
		l_x + this->_l_term_radius/3,
		l_y - this->_l_term_radius/3
	);
	fl_line(
		l_x,
		l_y + this->_l_term_radius*1/6,
		l_x,
		l_y - this->_l_term_radius
	);
}
void fltk_1000_range_cyclic::_draw_cent_mark( long l_x, long l_y )
{
	/* 選択枠 */
	fl_color(FL_DARK3);
	fl_loop(
		l_x - this->_l_center_radius,
		l_y - this->_l_center_radius,
		l_x + this->_l_center_radius,
		l_y - this->_l_center_radius,
		l_x + this->_l_center_radius,
		l_y + this->_l_center_radius,
		l_x - this->_l_center_radius,
		l_y + this->_l_center_radius
	);

	/* 中心線 */
	fl_color(FL_BLACK);
	fl_line(
		l_x,
		l_y + this->_l_center_radius*2/5,
		l_x,
		l_y - this->_l_center_radius*2/5
	);
}

void fltk_1000_range_cyclic::_draw_all_mark( void )
{
	/* 範囲内(Min<Max) */
	if (this->_l_x_min < this->_l_x_max) {
		/* 範囲の線(Min...Max) */
		fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max
		);
		fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+this->_l_x_max
		);
		/******fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+this->_l_x_center
		);
		fl_xyline(
			x()+this->_l_x_center,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max
		);******/
		/* 横線 */
		fl_xyline(
			x(),
			y()+this->_l_y_pos,
			x()+this->_l_x_min
		);
		fl_xyline(
			x()+this->_l_x_max,
			y()+this->_l_y_pos,
			x()+w()
		);
	}
	/* 範囲をまたがる(Min>Max) */
	else {
		/* 範囲の線(0...Max Min...w()) */
#if 0	/* ------------------ comment out ----------------------*/
		if (this->_l_x_min < this->_l_x_center) {
			/* 範囲の中心がMin側(右)である */
			fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+this->_l_x_center
			);
			fl_xyline(
			x()+this->_l_x_center,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+w()
			);
			fl_xyline(
			x(),
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max
			);
		} else {
			/* 範囲の中心がMax側(左)である */
			fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+w()
			);
			fl_xyline(
			x(),
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+this->_l_x_center
			);
			fl_xyline(
			x()+this->_l_x_center,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max
			);
		}
#endif	/* ------------------ comment out ----------------------*/
		fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+w()
		);
		fl_xyline(
			x(),
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max
		);
		fl_xyline(
			x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+w()
		);
		fl_xyline(
			x(),
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+this->_l_x_max
		);

		/* 横線 */
		fl_xyline(
			x()+this->_l_x_max,
			y()+this->_l_y_pos,
			x()+this->_l_x_min
		);
	}

	if (-1000 != this->_l_x_min) {
		this->_draw_term_mark( x()+
		  this->_l_x_min,y()+this->_l_y_pos,"Min" );
	}
	if (-1000 != this->_l_x_max) {
		this->_draw_term_mark( x()+
		  this->_l_x_max,y()+this->_l_y_pos,"Max" );
	}
	if (-1000 != this->_l_x_center) {
		this->_draw_cent_mark( x()+
		  this->_l_x_center, y()+this->_l_y_pos );
	}
	if (-1000 != this->_l_x_min2) {
		this->_draw_term_mark( x()+
		  this->_l_x_min2,y()+this->_l_y_pos,"Min" );
	}
	if (-1000 != this->_l_x_max2) {
		this->_draw_term_mark( x()+
		  this->_l_x_max2,y()+this->_l_y_pos,"Max" );
	}
	if (-1000 != this->_l_x_center2) {
		this->_draw_cent_mark( x()+
		  this->_l_x_center2, y()+this->_l_y_pos );
	}
}
void fltk_1000_range_cyclic::draw()
{
	/* 画面クリア */
	fl_color(FL_BACKGROUND_COLOR);
	//fl_color(FL_DARK1);
	fl_rectf(x(),y(),w(),h());

//(void)fprintf(stdout,"draw x%d y%d w%d h%d\n", x(),y(),w(),h());
//(void)fflush(stdout);

	/* 描画色 */
	fl_color(FL_BLACK);

	/* タイトル文字 */
	if (NULL != this->_cp_title) {
		fl_draw( this->_cp_title, x()+4,y()+16 );
	}

	/* mark */
	this->_draw_all_mark();

	/* Saturationの色変化 GUIの値を見て再表示する */
	cl_gts_master.cl_color_trace_enhancement.reset_saturation_belt_when_modify_hue_min_or_max();
}

/*--------------------------------------------------------*/

int fltk_1000_range_cyclic::_select_mark( long l_x_pos, long l_y_pos, long l_radius, long l_x_cursor, long l_y_cursor )
{
	if (
	((l_x_pos - l_radius) <= l_x_cursor) &&
	(l_x_cursor <= (l_x_pos + l_radius)) &&
	((l_y_pos - l_radius) <= l_y_cursor) &&
	(l_y_cursor <= (l_y_pos + l_radius))
	) {
		return -1;
	}
	return 0;
}

void fltk_1000_range_cyclic::_select( long l_x, long l_y )
{
	this->_e_select_type = E_NO_SELECT_TYPE;

	if ((-1000 != this->_l_x_center) && this->_select_mark(
		this->_l_x_center, this->_l_y_pos,
		this->_l_center_radius, l_x, l_y
	)) {
		this->_e_select_type = E_CENTER_SELECT_TYPE;
	}
	else if ((-1000 != this->_l_x_center2) && this->_select_mark(
		this->_l_x_center2, this->_l_y_pos,
		this->_l_center_radius, l_x, l_y
	)) {
		this->_e_select_type = E_CENTER_SELECT_TYPE;
	}
	else if ((-1000 != this->_l_x_max) && this->_select_mark(
		this->_l_x_max, this->_l_y_pos,
		this->_l_term_radius, l_x, l_y
	)) {
		this->_e_select_type = E_MAX_SELECT_TYPE;
	}
	else if ((-1000 != this->_l_x_max2) && this->_select_mark(
		this->_l_x_max2, this->_l_y_pos,
		this->_l_term_radius, l_x, l_y
	)) {
		this->_e_select_type = E_MAX_SELECT_TYPE;
	}
	else if ((-1000 != this->_l_x_min) && this->_select_mark(
		this->_l_x_min, this->_l_y_pos,
		this->_l_term_radius, l_x, l_y
	)) {
		this->_e_select_type = E_MIN_SELECT_TYPE;
	}
	else if ((-1000 != this->_l_x_min2) && this->_select_mark(
		this->_l_x_min2, this->_l_y_pos,
		this->_l_term_radius, l_x, l_y
	)) {
		this->_e_select_type = E_MIN_SELECT_TYPE;
	}
}

/*--------------------------------------------------------*/

void fltk_1000_range_cyclic::_set_min_center_max( long l_x_min, long l_x_max )
{
	if (l_x_min < 0) {
		l_x_min = w()+l_x_min;
		this->_l_x_min_at_drag = -1000;
	}
	else if (w() <= l_x_min) {
		l_x_min = l_x_min-w();
		this->_l_x_min_at_drag = -1000;
	}

	if (l_x_min < this->_l_term_radius) {
		this->_l_x_min = l_x_min;
		this->_l_x_min2 = w()+l_x_min;
	}
	else if ((w()-this->_l_term_radius) <= l_x_min) {
		this->_l_x_min = l_x_min;
		this->_l_x_min2 = l_x_min-w();
	}
	else {
		this->_l_x_min = l_x_min;
		this->_l_x_min2 = -1000;
	}

	if (l_x_max < 0) {
		l_x_max = w()+l_x_max;
		this->_l_x_max_at_drag = -1000;
	}
	else if (w() <= l_x_max) {
		l_x_max = l_x_max-w();
		this->_l_x_max_at_drag = -1000;
	}

	if (l_x_max < this->_l_term_radius) {
		this->_l_x_max = l_x_max;
		this->_l_x_max2 = w()+l_x_max;
	}
	else if ((w()-this->_l_term_radius) <= l_x_max) {
		this->_l_x_max = l_x_max;
		this->_l_x_max2 = l_x_max-w();
	}
	else {
		this->_l_x_max = l_x_max;
		this->_l_x_max2 = -1000;
	}

	if (this->_l_x_min < this->_l_x_max) {
		this->_l_x_center = (this->_l_x_min + this->_l_x_max)/2;
	} else {
		this->_l_x_center = this->_l_x_min +
		( w() - (this->_l_x_min - this->_l_x_max) )/2;
	}

	if (this->_l_x_center < 0) {
		this->_l_x_center = w()+this->_l_x_center;
	}
	else if (w() <= this->_l_x_center) {
		this->_l_x_center = this->_l_x_center-w();
	}

	if (this->_l_x_center < this->_l_center_radius) {
		this->_l_x_center = this->_l_x_center;
		this->_l_x_center2 = w()+this->_l_x_center;
	}
	else if ((w()-this->_l_center_radius) <= this->_l_x_center) {
		this->_l_x_center = this->_l_x_center;
		this->_l_x_center2 = this->_l_x_center-w();
	}
	else {
		this->_l_x_center = this->_l_x_center;
		this->_l_x_center2 = -1000;
	}

}

/*--------------------------------------------------------*/

void fltk_1000_range_cyclic::_mouse_push( int i_mouse_button, long l_mouse_x, long l_mouse_y )
{
	if (1 != i_mouse_button) { return; }

	l_mouse_x -= x();
	l_mouse_y -= y();

	this->_select( l_mouse_x, l_mouse_y );

	this->_l_x_drag_start = l_mouse_x;
	this->_l_x_min_at_push= this->_l_x_min;
	this->_l_x_max_at_push= this->_l_x_max;
}
void fltk_1000_range_cyclic::_mouse_drag( long l_mouse_x )
{
	l_mouse_x -= x(); /* このwidget内のローカル座標値にする */

	switch (this->_e_select_type) {
	case E_NO_SELECT_TYPE:
		return;
	case E_MIN_SELECT_TYPE:
		this->_l_x_min = this->_l_x_min_at_push +
				(l_mouse_x - this->_l_x_drag_start); 

		/* limit */
		if (-1000 != this->_l_x_min_at_drag) {
			/* maxより小さいから、大きいか同じ値のとき */
			if (
			(this->_l_x_min_at_drag < this->_l_x_max) &&
			(this->_l_x_max <= this->_l_x_min)
			) {
				this->_l_x_min = this->_l_x_max-1;
			}
			/* maxより大きいか同じから、小さい値のとき */
			else if (
			(this->_l_x_max <= this->_l_x_min_at_drag) &&
			(this->_l_x_min < this->_l_x_max)
			) {
				this->_l_x_min = this->_l_x_max;
			}
		}
		/**this->_l_x_max = this->_l_x_max_at_push -
			(this->_l_x_min - this->_l_x_min_at_push);**/
		break;
	case E_MAX_SELECT_TYPE:
		this->_l_x_max = this->_l_x_max_at_push +
				l_mouse_x - this->_l_x_drag_start ; 

		/* limit */
		if (-1000 != this->_l_x_max_at_drag) {
			/* minより大きいか同じから、小さい値のとき */
			if (
			(this->_l_x_min < this->_l_x_max_at_drag) &&
			(this->_l_x_max <= this->_l_x_min)
			) {
				this->_l_x_max = this->_l_x_min+1;
			}
			/* minより小さいから、大きいか同じ値のとき */
			else if (
			(this->_l_x_max_at_drag <= this->_l_x_min) &&
			(this->_l_x_min < this->_l_x_max)
			) {
				this->_l_x_max = this->_l_x_min;
			}
		}
		/**this->_l_x_min = this->_l_x_min_at_push -
			(this->_l_x_max - this->_l_x_max_at_push);**/
		break;
	case E_CENTER_SELECT_TYPE:
		this->_l_x_min = this->_l_x_min_at_push +
				l_mouse_x - this->_l_x_drag_start ; 
		this->_l_x_max = this->_l_x_max_at_push +
				l_mouse_x - this->_l_x_drag_start ; 
		break;
	default:
		return;
	}

	this->_l_x_min_at_drag = this->_l_x_min;
	this->_l_x_max_at_drag = this->_l_x_max;

	this->_set_min_center_max( this->_l_x_min,this->_l_x_max );

	this->redraw();
}
void fltk_1000_range_cyclic::_mouse_release( int i_mouse_button )
{
	if (1 != i_mouse_button) { return; }

	switch (this->_e_select_type) {
	case E_NO_SELECT_TYPE:
		return;
	case E_MIN_SELECT_TYPE:
		break;
	case E_MAX_SELECT_TYPE:
		break;
	case E_CENTER_SELECT_TYPE:
		break;
	}
	this->_e_select_type = E_NO_SELECT_TYPE;
}

int fltk_1000_range_cyclic::_key_in(int key)
{
	if (E_NO_SELECT_TYPE != this->_e_select_type) {
		if (FL_Escape == key) {
			this->_set_min_center_max(
				this->_l_x_min_at_push,
				this->_l_x_max_at_push
			);
			this->_mouse_release( 1 );
			this->redraw();
			return 1;
		}
	}
	return 0;
}

/* d_x_min,d_x_max is 0.0 --> 1.0 */
void fltk_1000_range_cyclic::set_dd_minmax( double d_x_min, double d_x_max )
{
	this->_set_min_center_max(
		(long)(d_x_min * w()-1.0+0.999999),
		(long)(d_x_max * w()-1.0+0.999999)
	);
}
void fltk_1000_range_cyclic::set_cp_title( char *cp_title )
{
	this->_cp_title = cp_title;
}
double fltk_1000_range_cyclic::get_d360_x_min( void )
{
	double d_val;
	d_val = (double)(this->_l_x_min) / w(); /* 0 ... <1 */
	d_val *= 360.0 * 2.0;	/* 0 ... <720.x */
	d_val = floor(d_val);	/* 0 ... <720.0 */
	return d_val/2.0;
}
double fltk_1000_range_cyclic::get_d360_x_max( void )
{
	double d_val;
	d_val = (double)(this->_l_x_max) / w(); /* 0 ... <1 */
	d_val *= 360.0 * 2.0;	/* 0 ... <720.x */
	d_val = floor(d_val);	/* 0 ... <720.0 */
	return d_val/2.0;
}

/*--------------------------------------------------------*/

int fltk_hh_cyclic::handle(int event)
{
	switch(event) {
	/***case FL_MOVE:
	(void)fprintf(stdout,"fltk_1000_range_cyclic FL_MOVE %d %d\n",
			Fl::event_x(),Fl::event_y() );
	(void)fflush(stdout);
		return 1;***/
	case FL_PUSH:
		this->_mouse_push(
			Fl::event_button(),
			(long)(Fl::event_x()),
			(long)(Fl::event_y())
		);
		return 1;
	case FL_DRAG:
		this->_mouse_drag( (long)(Fl::event_x()) );
#if !defined GTS_DEBUG
		cl_gts_master.cl_color_trace_edit_hsv_minmax.cb_hh_minmax(
			this->get_d360_x_min(),
			this->get_d360_x_max()
		);
#else
(void)fprintf(stdout,"hh min %4ld,%20.16f max %4ld,%20.16f\r",
this->get_l_x_min(),
this->get_d360_x_min(),
this->get_l_x_max(),
this->get_d360_x_max()
);
(void)fflush(stdout);
#endif
		return 1;
	case FL_RELEASE:
		this->_mouse_release( Fl::event_button() );
		return 1;

	case FL_SHORTCUT:
		return this->_key_in(Fl::event_key());

	default:
		return Fl_Widget::handle(event);
	}
	return 0;
}

