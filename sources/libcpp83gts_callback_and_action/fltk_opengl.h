#ifndef fltk_opengl_h
#define fltk_opengl_h

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

class fltk_opengl : public Fl_Gl_Window {
public:
	fltk_opengl(int x,int y,int w,int h,const char *l=0)
	: Fl_Gl_Window(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !fltk_opengl_h */
