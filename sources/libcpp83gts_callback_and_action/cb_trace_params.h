#ifndef cb_trace_params_h
#define cb_trace_params_h

#include "calcu_color_trace_sep_hsv.h"
#include "gts_gui.h"

class cb_trace_params {
public:
	cb_trace_params()
		:number_(0)
		,r_(0)
		,g_(0)
		,b_(0)
	{}

	/* 初期化 */
	void init_color(void);

	/* fltk GUIからの呼出し動作 */
	void cb_open_color_editor(
		Fl_Double_Window* flwin
		,Fl_Button* flbut
		,const int number
	);
	void cb_change_color(void);
	void cb_cancel(void);

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
		Fl_Roller*		roller_thickness;
		Fl_Value_Input*		valinp_hue_min;
		Fl_Value_Input*		valinp_hue_max;
		Fl_Value_Input*		valinp_slope_deg;
		Fl_Value_Input*		valinp_intercept;
		Fl_Check_Button*	chebut_display_sw;
	};
	std::vector<widget_set> widget_sets;
	void init_widget_set(void) { this->init_widget_set_(); }
	void set_params_for_speedup(
		std::vector<calcu_sep_hsv>& param_sets
	);
private:
	int number_;
	uchar r_ ,g_ ,b_;

	void init_widget_set_(void);
};

#endif /* !cb_trace_params_h */
