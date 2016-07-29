#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "fltk_1000x10_color_belt.h"

fltk_1000x10_color_belt::fltk_1000x10_color_belt(int x,int y,int w,int h,const char *l)
	:Fl_Box(x,y,w,h,l)
	,left_r_(0xff)  ,left_g_(0xff)  ,left_b_(0xff) /* White(Fix) */
	,right_r_(0xff) ,right_g_(0xff) ,right_b_(0x00)/* Red(Depend Hue) */
{
}

void fltk_1000x10_color_belt::set_right_color(
	const int r ,const int g ,const int b
)
{
	this->right_r_ = r;
	this->right_g_ = g;
	this->right_b_ = b;
}

void fltk_1000x10_color_belt::draw()
{
	/* 画面クリア */
	//fl_color(FL_BACKGROUND_COLOR);
	//fl_rectf(x(),y(),w(),h());

	/* グラディーション表示 */
	for (long ii = 0L; ii < this->w(); ++ii) {
		fl_color(
		static_cast<uchar>(
 this->left_r_ + ( this->right_r_ - this->left_r_ ) * ii / (this->w() - 1)
		)
		,static_cast<uchar>(
 this->left_g_ + ( this->right_g_ - this->left_g_ ) * ii / (this->w() - 1)
		)
		,static_cast<uchar>(
 this->left_b_ + ( this->right_b_ - this->left_b_ ) * ii / (this->w() - 1)
		)
		);
		fl_yxline(
			this->x()+ ii , this->y() , this->y()+ this->h()- 1
		);
	}
}
