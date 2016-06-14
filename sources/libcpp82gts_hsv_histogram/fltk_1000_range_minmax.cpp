#include <stdio.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "fltk_1000_range_minmax.h"
#if !defined GTS_DEBUG
#include "gts_master.h"
#endif

fltk_1000_range_minmax::fltk_1000_range_minmax(int x,int y,int w,int h,const char *l) : Fl_Box(x,y,w,h,l)
{
	this->_l_x_min = 0;
	this->_l_x_max = 1;
	this->_cp_title = NULL;

	this->_l_y_pos = 24;
	this->_l_minmax_radius = 24;
	this->_l_center_radius = 12;

	this->_e_select_type = E_NO_SELECT_TYPE;
	this->_l_x_min_backup = 0;
	this->_l_x_max_backup = 0;
	this->_l_x_drag_start = 0;
}

/*--------------------------------------------------------*/

void fltk_1000_range_minmax::_draw_minmax( long l_x, long l_y, char *cp_name )
{
	fl_color(FL_DARK3);

	/* 選択枠 */
	fl_loop(
		l_x - this->_l_minmax_radius,
		l_y - this->_l_minmax_radius,
		l_x + this->_l_minmax_radius,
		l_y - this->_l_minmax_radius,
		l_x + this->_l_minmax_radius,
		l_y + this->_l_minmax_radius,
		l_x - this->_l_minmax_radius,
		l_y + this->_l_minmax_radius
	);
	/* 文字表示 */
	fl_draw(
		cp_name,
		l_x - this->_l_minmax_radius*5/6,
		l_y + this->_l_minmax_radius*5/6
	);

	fl_color(FL_BLACK);

	/* 矢印 */
	fl_line(
		l_x - this->_l_minmax_radius/3,
		l_y - this->_l_minmax_radius/3,
		l_x,
		l_y - this->_l_minmax_radius + 1,
		l_x + this->_l_minmax_radius/3,
		l_y - this->_l_minmax_radius/3
	);
	/* 値の位置 */
	fl_line(
		l_x,
		l_y + this->_l_minmax_radius*1/6,
		l_x,
		l_y - this->_l_minmax_radius
	);
}
void fltk_1000_range_minmax::_draw_center( long l_x, long l_y )
{
	fl_color(FL_DARK3);
	/* 選択枠 */
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
	fl_color(FL_BLACK);
	/* 値の位置 */
	fl_line(
		l_x,
		l_y + this->_l_center_radius*2/5,
		l_x,
		l_y - this->_l_center_radius*2/5
	);
}

void fltk_1000_range_minmax::draw()
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

	/* 範囲外横線 */
	fl_xyline(	x(),
			y()+this->_l_y_pos,
			x()+this->_l_x_min );
	fl_xyline(	x()+this->_l_x_max,
			y()+this->_l_y_pos,
			x()+w()-1 );

	/* 範囲内横線 */
	/******fl_xyline(	x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+(this->_l_x_max+this->_l_x_min)/2);
	fl_xyline(	x()+(this->_l_x_max+this->_l_x_min)/2,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max );******/

	fl_xyline(	x()+this->_l_x_min,
			y()+this->_l_y_pos + this->_l_center_radius/3,
			x()+this->_l_x_max );
	fl_xyline(	x()+this->_l_x_min,
			y()+this->_l_y_pos - this->_l_center_radius/3,
			x()+this->_l_x_max );

	/* min,max持ち手 */
	this->_draw_minmax(x()+this->_l_x_min,y()+this->_l_y_pos,"Min");
	this->_draw_minmax(x()+this->_l_x_max,y()+this->_l_y_pos,"Max");
	this->_draw_center(
		x()+(this->_l_x_max+this->_l_x_min)/2,
		y()+this->_l_y_pos );
}

/*--------------------------------------------------------*/

int fltk_1000_range_minmax::_select_minmax( long l_x_mouse, long l_y_mouse, long l_x_pos, long l_y_pos )
{
	if (
	((l_x_pos - this->_l_minmax_radius) <= l_x_mouse) &&
	(l_x_mouse <= (l_x_pos + this->_l_minmax_radius)) &&
	((l_y_pos - this->_l_minmax_radius) <= l_y_mouse) &&
	(l_y_mouse <= (l_y_pos + this->_l_minmax_radius))
	) {
		return -1;
	}
	return 0;
}
int fltk_1000_range_minmax::_select_center( long l_x_mouse, long l_y_mouse, long l_x_pos, long l_y_pos )
{
	if (
	((l_x_pos - this->_l_center_radius) <= l_x_mouse) &&
	(l_x_mouse <= (l_x_pos + this->_l_center_radius)) &&
	((l_y_pos - this->_l_center_radius) <= l_y_mouse) &&
	(l_y_mouse <= (l_y_pos + this->_l_center_radius))
	) {
		return -1;
	}
	return 0;
}

/*--------------------------------------------------------*/

void fltk_1000_range_minmax::_mouse_push( int i_mouse_button, long l_mouse_x, long l_mouse_y )
{
	if (1 != i_mouse_button) { return; }

	l_mouse_x -= x();
	l_mouse_y -= y();

	this->_e_select_type = E_NO_SELECT_TYPE;

	if (this->_select_center( l_mouse_x, l_mouse_y,
	(this->_l_x_max+this->_l_x_min)/2, this->_l_y_pos )) {
		this->_e_select_type = E_CENTER_SELECT_TYPE;
		this->_l_x_drag_start = l_mouse_x;
		this->_l_x_min_backup = this->_l_x_min;
		this->_l_x_max_backup = this->_l_x_max;
	}
	else if (this->_select_minmax( l_mouse_x, l_mouse_y,
				this->_l_x_min, this->_l_y_pos )) {
		this->_e_select_type = E_MIN_SELECT_TYPE;
		this->_l_x_drag_start = l_mouse_x;
		this->_l_x_min_backup = this->_l_x_min;
		this->_l_x_max_backup = this->_l_x_max;
	}
	else if (this->_select_minmax( l_mouse_x, l_mouse_y,
				this->_l_x_max, this->_l_y_pos )) {
		this->_e_select_type = E_MAX_SELECT_TYPE;
		this->_l_x_drag_start = l_mouse_x;
		this->_l_x_min_backup = this->_l_x_min;
		this->_l_x_max_backup = this->_l_x_max;
	}
}
void fltk_1000_range_minmax::_mouse_drag( long l_mouse_x, long l_mouse_y )
{
	l_mouse_x -= x();
	l_mouse_y -= y();

	switch (this->_e_select_type) {
	case E_NO_SELECT_TYPE:
		return;
	case E_MIN_SELECT_TYPE:
		this->_l_x_min = this->_l_x_min_backup +
			l_mouse_x - this->_l_x_drag_start;

		if (this->_l_x_max <= this->_l_x_min)
		{ this->_l_x_min = this->_l_x_max-1; }
		else if (this->_l_x_min < 0)
		{ this->_l_x_min = 0; }
		else if (w() < this->_l_x_min)
		{ this->_l_x_min = w(); }

		this->redraw();
		break;
	case E_MAX_SELECT_TYPE:
		this->_l_x_max = this->_l_x_max_backup +
			l_mouse_x - this->_l_x_drag_start;

		if (this->_l_x_max <= this->_l_x_min)
		{ this->_l_x_max = this->_l_x_min+1; }
		else if (this->_l_x_max < 0)
		{ this->_l_x_max = 0; }
		else if (w() < this->_l_x_max)
		{ this->_l_x_max = w(); }

		this->redraw();
		break;
	case E_CENTER_SELECT_TYPE:
	{	long l_min, l_max, l_length;

		l_min = this->_l_x_min_backup +
			l_mouse_x - this->_l_x_drag_start;
		l_max = this->_l_x_max_backup +
			l_mouse_x - this->_l_x_drag_start;
		l_length = l_max-l_min;

		if (l_min < 0) {
			this->_l_x_min = 0;
			this->_l_x_max = l_length;
		}
		else if (w() < l_max) {
			this->_l_x_min = w() - l_length;
			this->_l_x_max = w();
		} else {
			this->_l_x_min = l_min;
			this->_l_x_max = l_max;
		}
		this->redraw();
	}
		break;
	default:
		return;
	}
}
void fltk_1000_range_minmax::_mouse_release( int i_mouse_button )
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

int fltk_1000_range_minmax::_key_in(int key)
{
	if (E_NO_SELECT_TYPE != this->_e_select_type) {
		if (FL_Escape == key) {
			this->_l_x_min = this->_l_x_min_backup;
			this->_l_x_max = this->_l_x_max_backup;
			this->_mouse_release( 1 );
			this->redraw();
			return 1;
		}
	}
	return 0;
}

/*--------------------------------------------------------*/
/* d_min -> d_max is 0.0 -> 1.0 */
void fltk_1000_range_minmax::set_dd_minmax( double d_min, double d_max )
{
	this->_l_x_min = (long)(d_min * (w()+0.999999));
	this->_l_x_max = (long)(d_max * (w()+0.999999));
	//this->redraw();
}
void fltk_1000_range_minmax::set_cp_title( char *cp_title )
{
	this->_cp_title = cp_title;
}
double fltk_1000_range_minmax::get_d_x_min( void )
{
	return (double)(this->_l_x_min) / w();
}
double fltk_1000_range_minmax::get_d_x_max( void )
{
	return (double)(this->_l_x_max) / w();
}

/*--------------------------------------------------------*/

int fltk_aa_minmax::handle(int event)
{
	switch(event) {
	/***case FL_MOVE:
	(void)fprintf(stdout,"FL_MOVE %d %d\n",
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
		this->_mouse_drag(
			(long)(Fl::event_x()),
			(long)(Fl::event_y())
		);
#if !defined GTS_DEBUG
		cl_gts_master.cb_color_trace_src_edit_aa(
			this->get_d_x_min(),
			this->get_d_x_max()
		);
#else
(void)fprintf(stdout,"aa min %4ld,%20.15f max %4ld,%20.15f\r",
this->get_l_x_min(),
this->get_d_x_min(),
this->get_l_x_max(),
this->get_d_x_max());
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

int fltk_bb_minmax::handle(int event)
{
	switch(event) {
	/***case FL_MOVE:
	(void)fprintf(stdout,"FL_MOVE %d %d\n",
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
		this->_mouse_drag(
			(long)(Fl::event_x()),
			(long)(Fl::event_y())
		);
#if !defined GTS_DEBUG
		cl_gts_master.cb_color_trace_src_edit_bb(
			this->get_d_x_min(),
			this->get_d_x_max()
		);
#else
(void)fprintf(stdout,"bb min %4ld,%20.15f max %4ld,%20.15f\r",
this->get_l_x_min(),
this->get_d_x_min(),
this->get_l_x_max(),
this->get_d_x_max());
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

