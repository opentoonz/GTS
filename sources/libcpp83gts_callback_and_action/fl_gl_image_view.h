#ifndef fl_gl_image_view_h
#define fl_gl_image_view_h

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

class fl_gl_image_view : public Fl_Gl_Window {
public:
	fl_gl_image_view(int x,int y,int w,int h,const char *l=0)
	: Fl_Gl_Window(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !fl_gl_image_view_h */
