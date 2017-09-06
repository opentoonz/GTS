#include <vector>
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>

namespace gts {
class opengl_camera_eye {
public:
	opengl_camera_eye();

	double get_eye_x() const { return this->eye_x_; }
	double get_eye_y() const { return this->eye_y_; }
	double get_eye_z() const { return this->eye_z_; }
	double get_cen_x() const { return this->cen_x_; }
	double get_cen_y() const { return this->cen_y_; }
	double get_cen_z() const { return this->cen_z_; }
	double get_upp_x() const { return this->upp_x_; }
	double get_upp_y() const { return this->upp_y_; }
	double get_upp_z() const { return this->upp_z_; }
	double get_fovy()  const { return this->fovy_; }
	double get_znear() const { return this->znear_; }
	double get_zfar()  const { return this->zfar_; }

	/* defaultに戻す */
	void reset_eye(void);

	/* cen中心に回転 */
	void rotate( const double degree_x ,const double degree_y );

	/* カメラの上下左右移動 */
	void updownleftright( const double move_x ,const double move_y );

	/* カメラの前後移動 */
	void frontback( const double track_scale);

	/* cen中心に拡大縮小 */
	void scale_self( const double scale );
private:
	void set_full_range_about_near_far_(void);

	double	 eye_x_ ,eye_y_ ,eye_z_
		,cen_x_ ,cen_y_ ,cen_z_
		,upp_x_ ,upp_y_ ,upp_z_
		,fovy_  ,znear_ ,zfar_;
}; // class opengl_camera_eye
} // gts

namespace gts {
class opengl_vbo {
public:
	opengl_vbo();
	~opengl_vbo();

	/* vboメモリで浮動小数の型 vbo_type_と合わせること*/
	//using vbo_float = GLdouble;
	using vbo_float = GLfloat;

	/* 処理開始と終了、あるいは pixel_size数の変更のときは
	一旦close()してから再度open_or_reopen()する */
	bool open_or_reopen( unsigned pixel_size );/* false=OK,true=Error */
	void close(void);

	/* 始めの値のセット、あるいは
	数が同じで値のみ変更 */
	vbo_float* start_vertex( void );
	/* 注:start_vertex()からend_vertex()までvertex bufferがbind状態 */
	void end_vertex( void );

	GLubyte* start_color( void );
	/* 注:start_color()からend_color()までcolor bufferがbind状態 */
	void end_color( void );

	/* 描画実行 */
	void draw(void);

	GLuint get_pixel_size(void) { return this->pixel_size_; }
	void pr_vbo_info(void);
private:
	GLuint id_vbo_[2];
	GLuint pixel_size_;
	const GLenum vbo_type_;// use glVertexPointer(,vbo_type,,)

	void clear_id_vbo_(void);
}; // class opengl_vbo
} // gts

//--------------------

class fl_gl_hsv_viewer : public Fl_Gl_Window {
public:
	fl_gl_hsv_viewer(int x ,int y ,int w ,int h ,const char*l=0);

	gts::opengl_camera_eye eye;
	gts::opengl_vbo        vbo;
private:
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
	void reset_vbo( const int pixel_size );

	/* 表示の状態 */	
	bool depth_sw_;		/* デプス(Z)バッファーのON/OFF	*/
	bool fog_sw_;		/* フォグ処理のON/OFF		*/
	float bg_rgba_[4];	/* 背景色			*/

	/* カメラ変更のための変数 */
	int	mouse_x_when_push_
		,mouse_y_when_push_;

	/* ダミーの入力画像 */
	void dummy_create_rgb_image_(const int pixel_size);
	const int dummy_w_;
	const int dummy_h_;
	std::vector<GLubyte>  dummy_rgb_image_;
};
