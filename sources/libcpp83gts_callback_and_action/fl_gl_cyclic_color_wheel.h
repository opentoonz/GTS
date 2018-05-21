#ifndef fl_gl_cyclic_color_wheel_h
#define fl_gl_cyclic_color_wheel_h

#include <FL/gl.h>	/* GLfloat GLubyte GLuint GLenum */

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Check_Button.H>

class fl_gl_cyclic_color_wheel : public Fl_Gl_Window {
public:
	fl_gl_cyclic_color_wheel(int x,int y ,int w,int h ,const char*l=0);

	void init_widget_set(
		const int number
		,Fl_Value_Input* valinp_hue_min
		,Fl_Value_Input* valinp_hue_max
		,Fl_Check_Button* chebut_enable_sw
		,Fl_Check_Button* chebut_rotate360_sw
	);
	void init_number_and_is_max( const int number ,const bool is_max);
	void set_min_or_max(const bool is_max );
	void set_reset(void);

private:
	/* マウスドラッグ開始位置 */
	int	mouse_x_when_push_
		,mouse_y_when_push_;

	/* Hue Color Wheel表示開始位置 */
	double	x_offset_;
	double	hue_offset_;

	/* 各Hue min,maxの範囲を参考表示 */
	class guide_widget_set_ {
	public:
		Fl_Value_Input* valinp_hue_min;
		Fl_Value_Input* valinp_hue_max;
		Fl_Check_Button* chebut_enable_sw;
		Fl_Check_Button* chebut_rotate360_sw;
	};
	std::vector< guide_widget_set_ > guide_widget_sets_;

	int hue_range_number_;
	bool hue_range_is_max_;

	//----------

	void draw();
	void draw_object_();

	int handle(int event);
	void handle_push_( const int mx ,const int my );
	void handle_updownleftright_( const int mx ,const int my );
	void handle_keyboard_( const int key , const char* text );

	double xpos_from_hue_(const double hue);
	double hue_from_xpos_(const double xpos);

	double limit_new_hue_( double hue_o_new ,bool& rotate360_sw );

	void set_min_or_max_to_gui_( const bool rot360_sw );
};

#endif /* !fl_gl_cyclic_color_wheel_h */
