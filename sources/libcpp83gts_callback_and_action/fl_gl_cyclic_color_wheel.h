#ifndef fl_gl_cyclic_color_wheel_h
#define fl_gl_cyclic_color_wheel_h

#include <FL/gl.h>	/* GLfloat GLubyte GLuint GLenum */

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>

class fl_gl_cyclic_color_wheel : public Fl_Gl_Window {
public:
	fl_gl_cyclic_color_wheel(int x,int y ,int w,int h ,const char*l=0);
	void set_hue_range_pos(const int num ,const bool is_max);
	void set_hue_range_is_max(const bool is_max );
	void set_hue_range_value(
		const int num ,const double mini ,const double maxi
		,const bool enable_sw
	);
	void set_position_between_min_max( const double ratio );

	double get_hue(void);
private:
	/* マウスドラッグ開始位置 */
	int	mouse_x_when_push_
		,mouse_y_when_push_;

	/* Hue Color Wheel表示開始位置 */
	double	x_offset_;
	double	hue_offset_;

	/* 各Hue min,maxの範囲を参考表示 */
	class min_max_enable_set_ {
	public:
		double minimum
			,maximum;
		bool enable_sw;
	};
	std::vector< min_max_enable_set_ > hue_ranges_;

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

	double limit_new_xpos_( double xpos );
	double limit_new_hue_( double hue );

	void set_position_to_min_or_max_();
};

#endif /* !fl_gl_cyclic_color_wheel_h */
