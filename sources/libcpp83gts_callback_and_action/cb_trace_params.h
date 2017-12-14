#ifndef cb_trace_params_h
#define cb_trace_params_h

#include <vector>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Scrollbar.H>

#include "calc_trace_by_hsv.h"	// calc::trace_by_hsv_params

class cb_trace_params {
public:
	cb_trace_params()
		:number_(0)
		,r_(0)
		,g_(0)
		,b_(0)
		,hmin_(0.)
		,hmax_(0.)
		,rotate360_sw_(false)
		,param_sets_(6)
		,widget_sets(6)
	{}

	/* 初期化 */
	void init_color(void);

	/* target rgb color editor */
	void cb_target_rgb_color_open_editor(
		Fl_Double_Window* flwin
		,Fl_Button* flbut
		,const int number
	);
	void cb_target_rgb_color_change(const bool change_hsv_sw=false);
	void cb_target_rgb_color_cancel(void);

	/* hue min max editor */
	void cb_hue_minmax_open_editor( const int number );
	void cb_hue_min_or_max_cancel(void);

	/* traceの目的色を得る */
	void get_target_rgb(
		const int number
		, unsigned char& r , unsigned char& g , unsigned char& b
	);
	void set_target_rgb(
		const int number
		, unsigned char r , unsigned char g , unsigned char b
	);

	/* trace paramの各項目を配列として扱うための処置
		"上下入れ替え"　と　"memory_config save&load"　で利用
	*/
	class widget_set {
	public:
		Fl_Check_Button*	chebut_enable_sw;
		Fl_Group*		group_trace;
		Fl_Button*		button_target_rgb;
		Fl_Value_Input*		valinp_thickness;
		Fl_Scrollbar*		scrbar_thickness;
		Fl_Value_Input*		valinp_hue_min;
		Fl_Value_Input*		valinp_hue_max;
		Fl_Button*		button_hue_minmax;
		Fl_Value_Input*		valinp_slope_deg;
		Fl_Value_Input*		valinp_intercept;
		Fl_Check_Button*	chebut_display_sw;
		Fl_Check_Button*	chebut_rotate360_sw;
	};
	std::vector<widget_set> widget_sets;
	void init_widget_set(void) { this->init_widget_set_(); }

	void set_params_for_speedup(void);
	const std::vector<calc::trace_by_hsv_params>& get_param_sets(void) {
		return this->param_sets_;
	}

	void cb_swap_widget_set( const unsigned num1 ,const unsigned num2 );
	int cb_get_window_height_active( void );
private:
	int number_;
	uchar r_ ,g_ ,b_;
	double hmin_ ,hmax_;
	bool rotate360_sw_;

	/* 計算する時のみ使う一時変数 */
	std::vector<calc::trace_by_hsv_params> param_sets_;

	void init_widget_set_(void);
	void cb_hue_min_or_max_open_editor_( const int number );
};

//--------------------

class fltk_button_trace_params : public Fl_Button {
public:
	fltk_button_trace_params(
	int x,int y,int w,int h,const char *l=0)
	: Fl_Button(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !cb_trace_params_h */
