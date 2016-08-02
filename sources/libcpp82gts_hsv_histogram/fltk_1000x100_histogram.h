#ifndef fltk_1000x100_histogram_h
#define fltk_1000x100_histogram_h

#include <FL/Fl_Box.H>
#include <FL/Fl_Image.H>

class fltk_1000x100_histogram : public Fl_Box {
public:
	fltk_1000x100_histogram(int x,int y,int w,int h,const char *l=0);
	void draw();
	int handle(int);
	void set_histogram( long l_size, long l_max, long *lp1000 );
	void set_l_max( long l_max );

	void set_l_max_from_histogram( void );
	void set_l_average_from_histogram( void );

	void set_color_belt_image(const Fl_Image* image);
	void set_color_left_right(
		const bool sw
		,const int lr , const int lg , const int lb
		, const int rr , const int rg , const int rb
	);
	bool is_color_left_right(void) {
		return this->modified_gradation_sw_;
	}
private:
	long _l_size;
	long _l_max;
	long _l_max_valuator;
	long _l_max_valuator_backup;
	long _l_max_drag_start;
	long *_lp1000;

	/* 表示するHistogramの色を決める場合の参照対象 */
	const Fl_Image* color_belt_image_;
	bool modified_gradation_sw_;
	int	 left_r_  ,left_g_  ,left_b_
		,right_r_ ,right_g_ ,right_b_
	;
};

#endif /* !fltk_1000x100_histogram_h */
