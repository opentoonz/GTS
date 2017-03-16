#ifndef cb_trace_parameters_h
#define cb_trace_parameters_h

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class fltk_button_trace_parameters : public Fl_Button {
public:
	fltk_button_trace_parameters(
	int x,int y,int w,int h,const char *l=0)
	: Fl_Button(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !cb_trace_parameters_h */
