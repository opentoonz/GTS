#ifndef fl_gl_image_view_h
#define fl_gl_image_view_h

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

class fl_gl_image_view : public Fl_Gl_Window {
public:
	fl_gl_image_view(int x,int y,int w,int h,const char *l=0)
	: Fl_Gl_Window(x,y,w,h,l)
	,pixel_x_(-1)
	,pixel_y_(-1)
	,pixel_r_(0)
	,pixel_g_(0)
	,pixel_b_(0)
	,pixel_channel_(0)
	,pixel_byte_(0)
	,pixel_bit_(0)
	{}
private:
	int pixel_x_ ,pixel_y_;
	int pixel_r_ ,pixel_g_ ,pixel_b_;
	int pixel_channel_ ,pixel_byte_ ,pixel_bit_;

	void draw();    
	int handle(int);
};

#endif /* !fl_gl_image_view_h */
