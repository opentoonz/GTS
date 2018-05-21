#ifndef fl_gl_hsv_view_h
#define fl_gl_hsv_view_h

#if defined DEBUG_FL_GL_HSV_VIEW
#include <vector>
//#define GLEW_STATIC	/* glew32s.libを使う場合必要 */
//#include <GL/glew.h>	/* gl.hより前に必要 */
#include <FL/gl.h>	/* GLubyte */
#endif

//#include <FL/Fl.H>
//#include <FL/Fl_Gl_Window.H>
#include "opengl_camera_eye.h"
#include "opengl_vertex_buffer_object.h"

class fl_gl_hsv_view : public Fl_Gl_Window {
public:
	fl_gl_hsv_view(int x ,int y ,int w ,int h ,const char*l=0);

	void rgb_to_xyz( const double r ,const double g ,const double b );

	opengl::camera_eye eye;
	opengl::vertex_buffer_object vbo;
private:
	/* 表示の状態 */	
	bool depth_sw_;		/* デプス(Z)バッファーのON/OFF	*/
	bool fog_sw_;		/* フォグ処理のON/OFF		*/
	float bg_rgba_[4];	/* 背景色			*/

	/* カメラ変更のための変数 */
	int	mouse_x_when_push_
		,mouse_y_when_push_;

	/* pixel位置表示 */
	double	pixel_x_ ,pixel_y_ ,pixel_z_;

	//----------

	void draw();
	void draw_object_();

	int handle(int event);
	void handle_push_( const int mx ,const int my );

	void handle_rotate_( const int mx ,const int my );
	void handle_updownleftright_( const int mx ,const int my );
	void handle_frontback_( const int mx , const int my );
	void set_mouse_when_push_( const int mx , const int my );
	void handle_scale_( const int mx ,const int my );

	void handle_keyboard_( const int key , const char* text );

#if defined DEBUG_FL_GL_HSV_VIEW
	/* ダミーの入力画像 */
	void dummy_reset_vbo( const int pixel_size );
	void dummy_create_rgb_image_(const int pixel_size);
	const int dummy_w_;
	const int dummy_h_;
	std::vector<GLubyte>  dummy_rgb_image_;
#endif
};

#endif /* !fl_gl_hsv_view_h */
