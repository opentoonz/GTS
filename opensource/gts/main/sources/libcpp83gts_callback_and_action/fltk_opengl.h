#ifndef __fltk_opengl_h__
#define __fltk_opengl_h__

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>

class fltk_opengl : public Fl_Gl_Window {
	void draw();    
	int handle(int);
public:
	fltk_opengl(int x,int y,int w,int h,const char *l=0);
private:
};
#endif /* !__fltk_opengl_h__ */
