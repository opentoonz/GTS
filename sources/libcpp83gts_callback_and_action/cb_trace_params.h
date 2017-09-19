#ifndef cb_trace_params_h
#define cb_trace_params_h

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>

class cb_trace_params {
public:
	cb_trace_params()
		:number_(0)
		,r_(0)
		,g_(0)
		,b_(0)
	{}

	void init_color(void);

	void cb_open_color_editor(
		Fl_Double_Window* flwin
		,Fl_Button* flbut
		,const int number
	);

	void cb_change_color(void);
	void cb_cancel(void);
private:
	int number_;
	uchar r_ ,g_ ,b_;
};

#endif /* !cb_trace_params_h */
