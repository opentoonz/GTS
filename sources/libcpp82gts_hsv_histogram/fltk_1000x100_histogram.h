#ifndef __fltk_1000x100_histogram_h__
#define __fltk_1000x100_histogram_h__

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
private:
	long _l_size;
	long _l_max;
	long _l_max_valuator;
	long _l_max_valuator_backup;
	long _l_max_drag_start;
	long *_lp1000;

	const Fl_Image* color_belt_image_;
};

#endif /* !__fltk_1000x100_histogram_h__ */
