#include <stdio.h>
#include <limits.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "fltk_1000x100_histogram.h"

#define HISTOGRAM_MINIMUM_COUNT 10

fltk_1000x100_histogram::fltk_1000x100_histogram(int x,int y,int w,int h,const char *l)
	:Fl_Box(x,y,w,h,l)
	,_l_size(0L)
	,_l_max(0L)
	,_l_max_valuator(0L)
	,_l_max_valuator_backup(0L)
	,_l_max_drag_start(-1000L)
	,_lp1000(nullptr)
	,color_belt_image_(nullptr)
{
}

void fltk_1000x100_histogram::set_histogram( long l_size, long l_max, long *lp1000 )
{
	this->_l_size = l_size;
	this->_l_max_valuator = this->_l_max = l_max;
	this->_lp1000 = lp1000;
}
void fltk_1000x100_histogram::set_l_max( long l_max )
{
	this->_l_max_valuator = this->_l_max = l_max;
}
void fltk_1000x100_histogram::set_l_max_from_histogram( void )
{
	long	ii, l_max;

	if (NULL == this->_lp1000) { return; }

	l_max = 0L;
	for (ii = 0L; ii < this->_l_size; ++ii) {
		if (l_max < this->_lp1000[ii]) {
			l_max = this->_lp1000[ii];
		}
	}
	if (l_max < HISTOGRAM_MINIMUM_COUNT) {
		this->_l_max_valuator= HISTOGRAM_MINIMUM_COUNT;
	}
	else {
		this->_l_max_valuator = this->_l_max = l_max;
	}
}
void fltk_1000x100_histogram::set_l_average_from_histogram( void )
{
	long	ii;
	double	d_max;

	if (NULL == this->_lp1000) { return; }

	d_max = 0.0;
	for (ii = 0L; ii < this->_l_size; ++ii) {
		d_max += this->_lp1000[ii];
	}

	long	l_max = (long)(d_max/this->_l_size);
	if (l_max < HISTOGRAM_MINIMUM_COUNT) {
		this->_l_max_valuator= HISTOGRAM_MINIMUM_COUNT;
	}
	else {
		this->_l_max_valuator = this->_l_max = l_max;
	}
}

void fltk_1000x100_histogram::set_color_belt_image(const Fl_Image* image)
{
	this->color_belt_image_ = image;
}

void fltk_1000x100_histogram::draw()
{
	double	dd;
	long	ll;
	long	ii;
	char ca_buf[64];

	/* 画面クリア */
	fl_color(FL_BACKGROUND_COLOR);
	//fl_color(FL_DARK1);
	fl_rectf(x(),y(),w(),h());

#if 0
	if (this->color_belt_image_ != nullptr &&
	this->color_belt_image_->data() != nullptr &&
	this->_l_size <=
	this->color_belt_image_->w() * this->color_belt_image_->d()
	) {
	 const char *const* image_p = this->color_belt_image_->data();
	 int depth = this->color_belt_image_->d();

	 /* histogram */
	 for (ii = 0L; ii < this->_l_size; ++ii) {
		dd =	(double)(this->_lp1000[ii]) *
			h() /				/* 0...h() */
			this->_l_max_valuator +
			0.999999;
		if ((h()-1) < dd) {
			ll = h()-1;
		} else {
			ll = (long)dd;
		}

		Fl_Color rr= static_cast<Fl_Color>(image_p[0][ii*depth+0]);
		Fl_Color gg= static_cast<Fl_Color>(image_p[0][ii*depth+1]);
		Fl_Color bb= static_cast<Fl_Color>(image_p[0][ii*depth+2]);
		fl_color( (rr<<24) | (gg<<16) | (bb<<8) );

		fl_yxline(
			x()+ii,
			y() + h()-1,
			y() + h()-1 - ll
		);
	 }
	}
	else {
#endif
	 /* 描画色 */
	 fl_color(FL_BLACK);

	 /* histogram */
	 for (ii = 0L; ii < this->_l_size; ++ii) {
		dd =	(double)(this->_lp1000[ii]) *
			h() /				/* 0...h() */
			this->_l_max_valuator +
			0.999999;
		if ((h()-1) < dd) {
			ll = h()-1;
		} else {
			ll = (long)dd;
		}
		fl_yxline(
			x()+ii,
			y() + h()-1,
			y() + h()-1 - ll
		);
	 }
//	}

	/* 文字色 */
	fl_color(FL_DARK3);

	sprintf( ca_buf, "%ld", this->_l_max_valuator );
	fl_draw( ca_buf, x()+4,y()+16 );
}

int fltk_1000x100_histogram::handle(int event)
{
	int	i_key;
	switch(event) {
	case FL_PUSH:
		this->_l_max_valuator_backup = this->_l_max_valuator;
		this->_l_max_drag_start = (long)(Fl::event_y() - y());
		return 1;
	case FL_DRAG:
		if (-1000 != this->_l_max_drag_start) {
			this->_l_max_valuator =
				this->_l_max_valuator_backup +
				this->_l_max_valuator_backup *
				((long)(Fl::event_y() - y()) -
					this->_l_max_drag_start) / h() ;
		 
			/* limit */
			if (this->_l_max_valuator<HISTOGRAM_MINIMUM_COUNT) {
			 this->_l_max_valuator = HISTOGRAM_MINIMUM_COUNT;
			}
			else if ((LONG_MAX/h())<this->_l_max_valuator) {
				this->_l_max_valuator = LONG_MAX/h();
			}
			this->redraw();
			return 1;
		}
	case FL_RELEASE:
		/* -1000であればDRAGしていないことを示す */
		this->_l_max_drag_start = -1000;
		return 1;
	case FL_SHORTCUT:
		i_key = Fl::event_key();
		/* DRAG中のcancel */
		if (-1000 != this->_l_max_drag_start) {
			if (FL_Escape == i_key) {
				this->_l_max_valuator =
				this->_l_max_valuator_backup;
				this->_l_max_drag_start = -1000;
				this->redraw();
				return 1;
			}
		}
		/* DRAGでないときのcancel */
		else {
			if (	(FL_Escape == i_key) &&
				(this->_l_max_valuator != this->_l_max)
			) {
				this->_l_max_valuator =
				this->_l_max;
				this->redraw();
				return 1;
			}
			/* smaple数を幅で割った大きさをmaxとした表示 */
			else if ('n' == i_key) {
				this->set_l_average_from_histogram();
				this->redraw();
				return 1;
			}
			/* 最大値をmaxとした表示(全景表示) */
			else if ('m' == i_key) {
				this->set_l_max_from_histogram();
				this->redraw();
				return 1;
			}
		}
		return 0;
	default:
		return Fl_Widget::handle(event);
	}
	return 0;
}

