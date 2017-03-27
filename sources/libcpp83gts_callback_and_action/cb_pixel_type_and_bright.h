#ifndef cb_pixel_type_and_bright_h
#define cb_pixel_type_and_bright_h

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class fltk_button_pixel_type_and_bright : public Fl_Button {
public:
	fltk_button_pixel_type_and_bright(
	int x,int y,int w,int h,const char *l=0)
	: Fl_Button(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !cb_pixel_type_and_bright_h */
