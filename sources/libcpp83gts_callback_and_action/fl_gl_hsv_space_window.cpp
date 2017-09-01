#include <cassert>	/* assert(-) */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>	/* sin(-) cos(-) */
#include <random>	/* mt19937 */

#define GLEW_STATIC	/* use glew32s.lib */
#include <GL/glew.h>

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include "FL/fl_ask.H"  // fl_alert(-)
#include <FL/gl.h>
#include <FL/glu.h>	/* gluPerspective(-) , gluLookAt(-) */
#include <FL/glut.h>	/* glutWireTeapot(-) glutWireCone(-) */
			/* glutExtensionSupported(-) --> link error */
#include "../../sources/libcpp38calcu_rgb_to_hsv/calcu_rgb_to_hsv.h"
#include "../../sources/libcpp38calcu_rgb_to_hsv/to_hsv.cpp"

#include <chrono>

namespace gts {
class stop_watch {
public:
	void start(void) {
		/* 計測スタート時刻を保存 */
		this->start_ = std::chrono::system_clock::now();
	}

	std::chrono::milliseconds stop_ms(void) {
		return	std::chrono::duration_cast<
			std::chrono::milliseconds>(
			std::chrono::system_clock::now() - this->start_
		);
	}
private:
	std::chrono::system_clock::time_point start_;
};
} // gts

//--------------------

namespace gts {
double rad_from_deg( const double deg )
{
	return 3.14159265358979323846264338327950288 * deg / 180.0;
}
} // gts

//--------------------

namespace gts {
class opengl_camera_eye {
public:
	opengl_camera_eye()
	:eye_x_(0.) ,eye_y_(0.) ,eye_z_(10.)
	,cen_x_(0.) ,cen_y_(0.) ,cen_z_(0.)
	,upp_x_(0.) ,upp_y_(1.) ,upp_z_(10.)
	,fovy_(30.) ,znear_(9.) ,zfar_(-11.)
	{
		assert (0. < this->fovy_); /* ゼロ以下は致命的エラー */
		this->reset_eye();
	}

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

	/* マウスカーソルのクリックした位置からのx,yの差を回転値にする
		x方向のマウス移動はy軸回転
		y方向のマウス移動はx軸回転
	あとで全面的に作り直し必要 */

	/* 回転 */
	void rotate( const double move_x ,const double move_y );

	/* カメラの上下左右移動 */
	void updownleftright( const double move_x ,const double move_y );

	/* カメラの前後移動 */
	void frontback( const double track);

	/* 拡大縮小 */
	void scale( const double move_x ,const double move_y );

	/* defaultに戻す */
	void reset_eye(void);
private:
	double	 eye_x_ ,eye_y_ ,eye_z_
		,cen_x_ ,cen_y_ ,cen_z_
		,upp_x_ ,upp_y_ ,upp_z_
		,fovy_  ,znear_ ,zfar_;
};
} // gts

void gts::opengl_camera_eye::reset_eye(void)
{
	/* 視点 注視点 の距離
	視野角がfovy_で、(0,0,0)を注視点としたとき、
	注視点を中心とした半径1の球全体がピッタリ入るような視点の位置 */
	const double zlen = 1. / sin( gts::rad_from_deg(this->fovy_) / 2. );

	/*	視点   (0,0,z)
		注視点 (0,0,0)
		頭上点 (0,1,z) */
	this->eye_x_ = 0.; this->eye_y_ = 0.; this->eye_z_ = zlen;
	this->cen_x_ = 0.; this->cen_y_ = 0.; this->cen_z_ = 0.;
	this->upp_x_ = 0.; this->upp_y_ = 1.; this->upp_z_ = zlen;

	/* z depth値 */
	const double len = sqrt(
		  (this->eye_x_ - this->cen_x_)
		* (this->eye_x_ - this->cen_x_)
		+ (this->eye_y_ - this->cen_y_)
		* (this->eye_y_ - this->cen_y_)
		+ (this->eye_z_ - this->cen_z_)
		* (this->eye_z_ - this->cen_z_)
	);

	if (1. < len) {
		this->znear_  = len - 1.;
		this->zfar_   = len + 1.;
	}
	else {
		this->znear_  = 0.;
		this->zfar_   = 2.;
	}
}

namespace {
void rotate2d( const double x , const double y , const double radian , double& x2 , double& y2 ) {
	x2 = x * cos( radian ) - y * sin( radian );
	y2 = x * sin( radian ) + y * cos( radian );
}
void rotate3d_vector(
const double x , const double y , const double z
, const double ox , const double oy , const double oz /* 回転の中心 */
, const double nx , const double ny , const double nz /* 回転の軸ベクトル */
, const double rad
, double& x2 , double& y2 , double& z2 )
{
	const double x_ = x - ox;
	const double y_ = y - oy;
	const double z_ = z - oz;
	x2 =	  ( nx * nx * (1. - cos(rad)) +      cos(rad) ) * x_
		+ ( nx * ny * (1. - cos(rad)) - nz * sin(rad) ) * y_
		+ ( nz * nx * (1. - cos(rad)) + ny * sin(rad) ) * z_;
	y2 =	  ( nx * ny * (1. - cos(rad)) + nz * sin(rad) ) * x_
		+ ( ny * ny * (1. - cos(rad)) +      cos(rad) ) * y_
		+ ( ny * nz * (1. - cos(rad)) - nx * sin(rad) ) * z_;
	z2 =	  ( nz * nx * (1. - cos(rad)) - ny * sin(rad) ) * x_
		+ ( ny * nz * (1. - cos(rad)) + nx * sin(rad) ) * y_
		+ ( nz * nz * (1. - cos(rad)) +      cos(rad) ) * z_;
	x2 += ox;
	y2 += oy;
	z2 += oz;
}
} // namespace

void gts::opengl_camera_eye::rotate( const double move_x ,const double move_y )
{
	const double yr=gts::rad_from_deg(move_x);/* x方向マウス移動はy軸回転 */
	const double xr=gts::rad_from_deg(move_y);/* y方向マウス移動はx軸回転 */
	rotate2d( this->eye_x_ ,this->eye_z_ ,yr ,this->eye_x_ ,this->eye_z_
	);
	rotate2d( this->upp_x_ ,this->upp_z_ ,yr ,this->upp_x_ ,this->upp_z_
	);
	rotate2d( this->eye_z_ ,this->eye_y_ ,xr ,this->eye_z_ ,this->eye_y_
	);
	rotate2d( this->upp_z_ ,this->upp_y_ ,xr ,this->upp_z_ ,this->upp_y_
	);
} 
void gts::opengl_camera_eye::updownleftright( const double move_x ,const double move_y )
{
	/* カメラ上方向のベクトル */
	const double vx1 = this->upp_x_ - this->eye_x_;
	const double vy1 = this->upp_y_ - this->eye_y_;
	const double vz1 = this->upp_z_ - this->eye_z_;

	/* カメラ後ろ方向のベクトル */
	const double vx2 = this->cen_x_ - this->eye_x_;
	const double vy2 = this->cen_y_ - this->eye_y_;
	const double vz2 = this->cen_z_ - this->eye_z_;

	/* カメラ横方向のベクトル */
	const double vx3 = vy1*vz2-vz1*vy2;
	const double vy3 = vz1*vx2-vx1*vz2;
	const double vz3 = vx1*vy2-vy1*vx2;

	this->eye_x_ += vx3 * move_x * 0.001;
	this->eye_y_ += vy3 * move_x * 0.001;
	this->eye_z_ += vz3 * move_x * 0.001;
	this->upp_x_ += vx3 * move_x * 0.001;
	this->upp_y_ += vy3 * move_x * 0.001;
	this->upp_z_ += vz3 * move_x * 0.001;
	this->cen_x_ += vx3 * move_x * 0.001;
	this->cen_y_ += vy3 * move_x * 0.001;
	this->cen_z_ += vz3 * move_x * 0.001;

	/* 横移動しない！左右に回転しながら移動する？！ */
	this->eye_x_ += vx1 * move_y * 0.001;
	this->eye_y_ += vy1 * move_y * 0.001;
	this->eye_z_ += vz1 * move_y * 0.001;
	this->upp_x_ += vx1 * move_y * 0.001;
	this->upp_y_ += vy1 * move_y * 0.001;
	this->upp_z_ += vz1 * move_y * 0.001;
	this->cen_x_ += vx1 * move_y * 0.001;
	this->cen_y_ += vy1 * move_y * 0.001;
	this->cen_z_ += vz1 * move_y * 0.001;
/*
std::cout << "vx3=" << vx3 << std::endl;
std::cout << "vy3=" << vy3 << std::endl;
std::cout << "vz3=" << vz3 << std::endl;
std::cout << "cen_x=" << this->cen_x_ << std::endl;
std::cout << "cen_y=" << this->cen_y_ << std::endl;
std::cout << "cen_z=" << this->cen_z_ << std::endl;
std::cout << "eye_x=" << this->eye_x_ << std::endl;
std::cout << "eye_y=" << this->eye_y_ << std::endl;
std::cout << "eye_z=" << this->eye_z_ << std::endl;
std::cout << "upp_x=" << this->upp_x_ << std::endl;
std::cout << "upp_y=" << this->upp_y_ << std::endl;
std::cout << "upp_z=" << this->upp_z_ << std::endl << std::endl;
*/
}

void gts::opengl_camera_eye::frontback( const double track)
{
	const double vx = this->eye_x_ - this->cen_x_;
	const double vy = this->eye_y_ - this->cen_y_;
	const double vz = this->eye_z_ - this->cen_z_;

	this->eye_x_ += vx * track * 0.02;
	this->eye_y_ += vy * track * 0.02;
	this->eye_z_ += vz * track * 0.02;
	this->upp_x_ += vx * track * 0.02;
	this->upp_y_ += vy * track * 0.02;
	this->upp_z_ += vz * track * 0.02;
	this->cen_x_ += vx * track * 0.02;
	this->cen_y_ += vy * track * 0.02;
	this->cen_z_ += vz * track * 0.02;
}

void gts::opengl_camera_eye::scale( const double move_x , const double move_y )
{
	double ux = this->upp_x_ - this->cen_x_;
	double uy = this->upp_y_ - this->cen_y_;
	double uz = this->upp_z_ - this->cen_z_;
	double ex = this->eye_x_ - this->cen_x_;
	double ey = this->eye_y_ - this->cen_y_;
	double ez = this->eye_z_ - this->cen_z_;

	ux *= move_x * 0.01 + 1.0;
	uy *= move_x * 0.01 + 1.0;
	uz *= move_x * 0.01 + 1.0;
	ex *= move_x * 0.01 + 1.0;
	ey *= move_x * 0.01 + 1.0;
	ez *= move_x * 0.01 + 1.0;

	this->upp_x_ = this->cen_x_ + ux;
	this->upp_y_ = this->cen_y_ + uy;
	this->upp_z_ = this->cen_z_ + uz;
	this->eye_x_ = this->cen_x_ + ex;
	this->eye_y_ = this->cen_y_ + ey;
	this->eye_z_ = this->cen_z_ + ez;

	/* z depth値 */
	const double len = sqrt(
		  (this->eye_x_ - this->cen_x_)
		* (this->eye_x_ - this->cen_x_)
		+ (this->eye_y_ - this->cen_y_)
		* (this->eye_y_ - this->cen_y_)
		+ (this->eye_z_ - this->cen_z_)
		* (this->eye_z_ - this->cen_z_)
	);
	/* 仮想球半径 */
	const double sr = len * sin( gts::rad_from_deg(this->fovy_) / 2. );

	if (sr < len) {
		this->znear_  = len - sr;
		this->zfar_   = len + sr;
	}
	else {
		this->znear_  = 0.;
		this->zfar_   = sr * 2.;
	}
}

//--------------------

namespace gts {
void pr_opengl_info(void)
{
	std::string info;
	info += "Vender\t";
	info += reinterpret_cast<const char *>(glGetString(GL_VENDOR));
	info += '\n';
	info += "GPU\t";
	info += reinterpret_cast<const char *>(glGetString(GL_RENDERER));
	info += '\n';
	info += "OpenGL Version\t";
	info += reinterpret_cast<const char *>(glGetString(GL_VERSION));
	info += '\n';
	info += "OpenGL Extensions\n";
	std::string gle(reinterpret_cast<const char *>(
		glGetString(GL_EXTENSIONS)
	));
	std::replace(gle.begin() ,gle.end() ,' ' ,'\n');
	info += gle;
	std::cout << info;
	//----------
/*	if (glutExtensionSupported("GL_ARB_vertex_buffer_object") == 0) {
		std::cerr
		<< "Not Support GL_ARB_vertex_buffer_object"
		<< " , Need OpenGL 1.5 or later";
	}*/
}
} // gts

//--------------------

namespace gts {
class opengl_vbo {
public:
	opengl_vbo();
	~opengl_vbo();

	/* vboメモリで浮動小数の型 vbo_type_と合わせること*/
	//using vbo_float = GLdouble;
	using vbo_float = GLfloat;

	/* 処理開始と終了、あるいは
	pixel_size数の変更のときは一旦close()してから再度open_or_reopen()する */
	bool open_or_reopen( unsigned pixel_size ); /* false=OK , true=Error */
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
};
} // gts

void gts::opengl_vbo::clear_id_vbo_(void)
{
	for (int ii=0;ii<sizeof(this->id_vbo_) / sizeof(GLuint) ;++ii) {
		this->id_vbo_[0] = 0;
	}
}

gts::opengl_vbo::opengl_vbo()
	:pixel_size_(0)
	/* vboメモリで浮動小数の型 vbo_floatと合わせること*/
	//,vbo_type_(GL_DOUBLE)
	,vbo_type_(GL_FLOAT)
{
	this->clear_id_vbo_();
}
gts::opengl_vbo::~opengl_vbo()
{
	this->close();
}
bool gts::opengl_vbo::open_or_reopen( unsigned pixel_size )
{
	/* 以前のvboバッファが残っていれば閉じる */
	this->close();

	/* vboバッファのIDを得る。座標と色の二つ */
	glGenBuffers( sizeof(this->id_vbo_)/sizeof(GLuint) ,this->id_vbo_ );

	/* 頂点用VBOを確保 */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[0] );
	glBufferData( GL_ARRAY_BUFFER
	 ,pixel_size * sizeof(vbo_float) * 3 ,nullptr ,GL_DYNAMIC_DRAW );

	/* 頂点用VBO確保の確認 */
	{
	GLint chk_sz=0;
	glGetBufferParameteriv( GL_ARRAY_BUFFER ,GL_BUFFER_SIZE ,&chk_sz );
	if ( pixel_size * sizeof(vbo_float) * 3 != chk_sz ) {
		if (0 < chk_sz) {
			glDeleteBuffers( 1 , &this->id_vbo_[0] );
		}

		/* bindを指定なしにする */
		glBindBuffer( GL_ARRAY_BUFFER ,0 );

		this->clear_id_vbo_();

		std::ostringstream ost;
		ost	<< "Error:Can not get vbo for vertex:"
			<< "pixel_size*sizeof(vbo_float)*3="
			<< pixel_size*sizeof(vbo_float)*3
			<< ":chk_sz="
			<< chk_sz;
		fl_alert( ost.str().c_str() );

		return true;
	}
	}

	/* 色用VBOを確保 */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[1] );
	glBufferData( GL_ARRAY_BUFFER
	 ,pixel_size * sizeof(GLubyte) * 3 ,nullptr ,GL_DYNAMIC_DRAW );

	/* 色用VBO確保の確認 */
	{
	GLint chk_sz=0;
	glGetBufferParameteriv( GL_ARRAY_BUFFER ,GL_BUFFER_SIZE ,&chk_sz );
	if ( pixel_size * sizeof(GLubyte) * 3 != chk_sz ) {
		if (0 < chk_sz) {
			glDeleteBuffers(
				sizeof(this->id_vbo_) / sizeof(GLuint)
				, this->id_vbo_ );
		}
		else {
			/* すでに確保したVBOを削除 */
			glDeleteBuffers( 1 , &this->id_vbo_[0] );
		}

		/* bindを指定なしにする */
		glBindBuffer( GL_ARRAY_BUFFER ,0 );

		this->clear_id_vbo_();

		std::ostringstream ost;
		ost	<< "Error:Can not get vbo for color:"
			<< "pixel_size*sizeof(GLubyte)*3="
			<< pixel_size*sizeof(GLubyte)*3
			<< ":chk_sz="
			<< chk_sz;
		fl_alert( ost.str().c_str() );

		return true;
	}
	}

	this->pixel_size_ = pixel_size;

	/* bindを指定なしにする */
	glBindBuffer( GL_ARRAY_BUFFER ,0 );

	return false;
}
void gts::opengl_vbo::close(void)
{
	/* VBO用ID破棄 */
	if (this->id_vbo_[0] != 0) {
		glDeleteBuffers(
			sizeof(this->id_vbo_) / sizeof(GLuint)
			, this->id_vbo_ );
		this->clear_id_vbo_();
	}
}

gts::opengl_vbo::vbo_float* gts::opengl_vbo::start_vertex( void )
{
	if (this->id_vbo_[0] == 0) {
		return nullptr;
	}
	/* 頂点用VBO */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[0] );
	return static_cast<vbo_float *>(glMapBuffer(
				GL_ARRAY_BUFFER , GL_READ_WRITE ));
}
void gts::opengl_vbo::end_vertex( void )
{
	if (this->id_vbo_[0] == 0) {
		return;
	}
	glUnmapBuffer( GL_ARRAY_BUFFER );
}
GLubyte* gts::opengl_vbo::start_color( void )
{
	if (this->id_vbo_[1] == 0) {
		return nullptr;
	}
	/* 色用VBO */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[1] );
	return static_cast<GLubyte *>(glMapBuffer(
				GL_ARRAY_BUFFER , GL_READ_WRITE ));
	/* ここからend_color()までcolorbufferがbind状態 */
}
void gts::opengl_vbo::end_color( void )
{
	if (this->id_vbo_[1] == 0) {
		return;
	}
	glUnmapBuffer( GL_ARRAY_BUFFER );
}

void gts::opengl_vbo::draw(void)
{
	if (this->id_vbo_[0] == 0) {
		return;
	}
	/* 頂点の格納場所を伝える */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[0] );
	glVertexPointer( 3 ,this->vbo_type_ ,0 ,0 );

	/* 色の格納場所を伝える */
	glBindBuffer( GL_ARRAY_BUFFER ,this->id_vbo_[1] );
	glColorPointer( 3 ,GL_UNSIGNED_BYTE ,0 ,0 );

	/* 描画を有効化 */
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );

	/* 描画 */
	glDrawArrays( GL_POINTS ,0 ,this->pixel_size_ );

	/* 描画を無効化 */
	glDisableClientState( GL_COLOR_ARRAY );
	glDisableClientState( GL_VERTEX_ARRAY );

	/* bind指定なしにする。エラー除け??? */
	glBindBuffer( GL_ARRAY_BUFFER ,0 );
}

void gts::opengl_vbo::pr_vbo_info(void)
{
	std::cout << "vertex buffer="
		<< this->get_pixel_size()*sizeof(vbo_float)*3 << "bytes\n";
	std::cout << " color buffer="
		<< this->get_pixel_size()*sizeof(GLubyte)*3 << "bytes\n";
	std::cout << "        total="
		<< this->get_pixel_size()*sizeof(vbo_float)*3
		+this->get_pixel_size()*sizeof(GLubyte)*3 << "bytes\n";
}

//--------------------

class fl_gl_hsv_space_window : public Fl_Gl_Window {
public:
	fl_gl_hsv_space_window(int x ,int y ,int w ,int h ,const char*l=0);

	gts::opengl_camera_eye eye;
	gts::opengl_vbo        vbo;
private:
	void draw();
	void draw_object_();

	int handle(int event);
	void handle_push_( const int mx ,const int my );

	void handle_rotate_( const int mx ,const int my );
	void handle_updownleftright_( const int mx ,const int my );
	void handle_frontback_( const int wheel );
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

namespace {

void init_glew_(void)
{
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::ostringstream ost;
		ost	<< "Critical Error:"
			<< glewGetErrorString(err);
		fl_alert( ost.str().c_str() );
		assert( !ost.str().c_str() );
	}

	std::cout << "GLEW Version:" << glewGetString(GLEW_VERSION)
		<< std::endl;

	if (!glewIsSupported( "GL_ARB_vertex_buffer_object" )) {
		fl_alert(
	"Critical Error:GL_ARB_vertex_buffer_object is not Supported"
		);
		assert(
	!"Critical Error:GL_ARB_vertex_buffer_object is not Supported"
		);
	}
}

} // namespace

fl_gl_hsv_space_window::fl_gl_hsv_space_window(int x ,int y ,int w ,int h ,const char*l)
	: Fl_Gl_Window(x,y,w,h,l)
	,depth_sw_(true)
	,fog_sw_(true)
	,mouse_x_when_push_(0)
	,mouse_y_when_push_(0)
	//,dummy_w_(1000) ,dummy_h_(500) // test
	//,dummy_w_(3013) ,dummy_h_(1710) // 200dpi
	//,dummy_w_(3400) ,dummy_h_(2340) // 200dpi
	,dummy_w_(5100) ,dummy_h_(3510) // 300dpi
	//,dummy_w_(6800) ,dummy_h_(4680) // 400dpi
	//,dummy_w_(8500) ,dummy_h_(5850) // 500dpi too big when double
	//,dummy_w_(10200) ,dummy_h_(7020) // 600dpi too big when double
{
	/* 初期化できない？ので代入 */
	this->bg_rgba_[0] = this->bg_rgba_[1] = this->bg_rgba_[2] = 0.f;
	this->bg_rgba_[3] = 1.f;

	/* dummy_rgb_image_ に8bitサンプリングでランダムなrgb画像を生成 */
	this->dummy_create_rgb_image_( this->dummy_w_ * this->dummy_h_ );
}

void fl_gl_hsv_space_window::dummy_create_rgb_image_(
	const int pixel_size
)
{
	std::cout << "create_rgb_image size=" << pixel_size << "pixel\n";

	gts::stop_watch stwa; stwa.start();

	const int count = pixel_size * 3;

	std::mt19937 engine;
	std::uniform_int_distribution<> dist( 0 ,255 );
	this->dummy_rgb_image_.clear();
	this->dummy_rgb_image_.reserve( count );
	for (int ii=0 ;ii<count;++ii) {
		this->dummy_rgb_image_.push_back( dist(engine) );
	}

	std::cout << "create_rgb_image time="
		<< stwa.stop_ms().count() << "milisec\n";

	std::cout << "create_rgb_image size="
		<< this->dummy_rgb_image_.size() << "bytes\n";
}

void fl_gl_hsv_space_window::draw_object_()
{
	/* エリアガイド表示 */
	glColor3d(1.0, 1.0, 1.0);
	glutWireCone(1.0 ,1.0 ,36 ,10);

	/* 中心軸ガイド表示 */
	glColor3d(1.0, 1.0, 1.0); // Draw red 
	glBegin(GL_LINE_STRIP);
		glVertex3d(0. , 0. , 0.0);
		glVertex3d(0. , 0. , 1.0);
	glEnd();

	/* hsv 3d表示 */
	vbo.draw();
}

namespace {
void rgb_to_xyz(
	const double r , const double g , const double b
	, gts::opengl_vbo::vbo_float* vtx
)
{
	/* rgb --> hsv */
	double h=0. ,s=0. ,v=0.;
	calcu_rgb_to_hsv rgb2hsv;
	rgb2hsv.to_hsv( r ,g ,b ,&h ,&s ,&v );

	/* hsv --> xyz */
	double x = cos( gts::rad_from_deg(h) ) * s * v;
	double y = sin( gts::rad_from_deg(h) ) * s * v;
	double z = 1. - v;
	vtx[0] = static_cast<gts::opengl_vbo::vbo_float>(x);
	vtx[1] = static_cast<gts::opengl_vbo::vbo_float>(y);
	vtx[2] = static_cast<gts::opengl_vbo::vbo_float>(z);
}
} // namespace

void fl_gl_hsv_space_window::reset_vbo( const int pixel_size )
{
/*
	この処理が必要な場所で同等の処理を行うよう変更する
	fl_gl_hsv_space_window::vboを使いデータサイズと内容の設定
*/
	/* vbo初期化 */
	if (this->vbo.open_or_reopen( pixel_size )) {
		return; // by Error
	}
	this->vbo.pr_vbo_info();

	/* ダミーの画像サイズも変更しランダムし直し */
	this->dummy_create_rgb_image_( pixel_size );

	/* vbo colorデータ書き込み */
	GLubyte* col = this->vbo.start_color();
	if (col == nullptr) { /* open出来ていればここはこないはず */
	 assert(!"Error:vbo.start_color() return null");
	}
	unsigned char* da = this->dummy_rgb_image_.data();
	unsigned sz = this->dummy_rgb_image_.size();
	for (unsigned ii=0 ;ii< sz ;ii+=3, da+=3 ,col+=3) {
		col[0] = da[0];
		col[1] = da[1];
		col[2] = da[2];
	}
	this->vbo.end_color();

	/* vbo vertexデータ書き込み */
	gts::stop_watch stwa; stwa.start();
	gts::opengl_vbo::vbo_float* vtx= this->vbo.start_vertex();
	if (vtx == nullptr) { /* open出来ていればここはこないはず */
	 assert(!"Error:vbo.start_vertex() return null");
	}
	da = this->dummy_rgb_image_.data();
	sz = this->dummy_rgb_image_.size();
	for (unsigned ii=0 ;ii< sz ;ii+=3, da+=3 ,vtx+=3) {
		rgb_to_xyz(
		 da[0]/255. ,da[1]/255. ,da[2]/255. ,vtx
		);
	}
	this->vbo.end_vertex();
 std::cout << "from_rgb_to_xyz time=" << stwa.stop_ms().count() << "milisec\n";
}
void fl_gl_hsv_space_window::draw()
{
	if (!valid()) {
		/* FLTKがこのウィンドウの新しいコンテキストを作成するとき、
		またはウィンドウのサイズが変更されたときここに来る */

		static bool only_sw = true;
		if (only_sw) {
			/* ここはアプリ立上げ後一回のみ実行する場所 */
			only_sw = false;

			/* glewの初期化 */
			init_glew_();

			/* Graphic Hardware & OpenGL情報表示 */
			//gts::pr_opengl_info();

			/*--- 画面モード ---*/
			/*
			const int win_mode = FL_RGB | FL_DOUBLE | FL_ALPHA;
			if (this->depth_sw_) { win_mode |= FL_DEPTH; }
			this->mode( win_mode );
			*/

			/* シェーディング */
			//glShadeModel( GL_FLAT );

			/*--- クリアのための初期値 ---*/

			/* カラーバッファの初期値設定 背景(画面クリア)色 */
			glClearColor(
				this->bg_rgba_[0]
				,this->bg_rgba_[1]
				,this->bg_rgba_[2]
				,this->bg_rgba_[3]
			);

			/* デプスバッファーの初期値設定 最遠(=1)でクリア */
			if (this->depth_sw_) { glClearDepth( 1.0 ); }

			/* フォグの色 */
			if (this->fog_sw_) {
				glFogfv( GL_FOG_COLOR , this->bg_rgba_ );
			}
		}

std::cout << "fl_gl_hsv_space_window w=" << this->w() << " h=" << this->h() << std::endl;
		/* ピクセル値あるいはサイズの変更 */
		this->reset_vbo( this->w() * this->h() );

		/* 表示範囲の再設定 */
		glViewport( 0 ,0 ,this->w(), this->h());
	}
	/* 射影行列の設定 */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	gluPerspective(
		 this->eye.get_fovy()
		,static_cast<double>(this->w())/this->h()
		,this->eye.get_znear()
		,this->eye.get_zfar()
	);

	/* モデルビュー行列の設定 */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	gluLookAt(
		 this->eye.get_eye_x()
		,this->eye.get_eye_y()
		,this->eye.get_eye_z()
		,this->eye.get_cen_x()
		,this->eye.get_cen_y()
		,this->eye.get_cen_z()
		,this->eye.get_upp_x()
		,this->eye.get_upp_y()
		,this->eye.get_upp_z()
	);

	/* fog */
	if (this->fog_sw_) {
		glFogf( GL_FOG_START ,static_cast<GLfloat>(
			(this->eye.get_znear() + this->eye.get_zfar()) / 2.
		));

		glFogf( GL_FOG_END ,static_cast<GLfloat>(
			this->eye.get_zfar())
		);
		glFogf( GL_FOG_MODE  ,GL_LINEAR );
		glFogf( GL_FOG_HINT  ,GL_NEAREST );
		//glFogf( GL_FOG_HINT  ,GL_FASTEST );
	}

	/* バッファの初期化 */
	int clr_mode = GL_COLOR_BUFFER_BIT;
	if (this->depth_sw_) { clr_mode |= GL_DEPTH_BUFFER_BIT; }
	glClear( clr_mode );

	/* 有効化 */
	if (this->depth_sw_) { glEnable( GL_DEPTH_TEST ); }
	if (this->fog_sw_)   { glEnable( GL_FOG ); }

	/* 描画	 */
 //gts::stop_watch stwa; stwa.start();
	this->draw_object_();
 //std::cout << stwa.stop_ms().count() << "milisec\n";

	/* 無効化 */
	if (this->fog_sw_)   { glDisable( GL_FOG ); }
	if (this->depth_sw_) { glDisable( GL_DEPTH_TEST ); }
}

void fl_gl_hsv_space_window::handle_push_( const int mx ,const int my )
{
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;
}
void fl_gl_hsv_space_window::handle_rotate_( const int mx ,const int my )
{
	this->eye.rotate(
		static_cast<double>(mx - this->mouse_x_when_push_)
		,static_cast<double>(my - this->mouse_y_when_push_)
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}
void fl_gl_hsv_space_window::handle_updownleftright_( const int mx ,const int my )
{
	this->eye.updownleftright(
		static_cast<double>(mx - this->mouse_x_when_push_)
		,static_cast<double>(my - this->mouse_y_when_push_)
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}
void fl_gl_hsv_space_window::handle_frontback_( const int wheel )
{
	this->eye.frontback(
		static_cast<double>(wheel)
	);

	this->redraw();
}
void fl_gl_hsv_space_window::handle_scale_( const int mx ,const int my )
{
	this->eye.scale(
		static_cast<double>(mx - this->mouse_x_when_push_)
		,static_cast<double>(my - this->mouse_y_when_push_)
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}

void fl_gl_hsv_space_window::handle_keyboard_( const int key , const char* text )
{
	if (text != nullptr) {
	 switch (text[0]) {
	 case 'm':
		this->eye.reset_eye();
		this->redraw();
		break;
	 case 'd':
		if (this->depth_sw_)	{ this->depth_sw_ = false; }
		else			{ this->depth_sw_ = true; }
		this->redraw();
		break;
	 case 'f':
		if (this->fog_sw_)	{ this->fog_sw_ = false; }
		else			{ this->fog_sw_ = true; }
		this->redraw();
		break;
	 }
	}
}
int fl_gl_hsv_space_window::handle(int event)
{
	switch(event) {
	case FL_PUSH:	// mouse down event
		this->handle_push_( Fl::event_x() , Fl::event_y() );
		return 1;
	case FL_DRAG:	// mouse moved while down event
		if (Fl::event_state() & FL_SHIFT) {
			this->handle_updownleftright_(
				Fl::event_x() ,Fl::event_y() );
		}
		else if (Fl::event_state() & FL_CTRL) {
			this->handle_scale_( Fl::event_x() ,Fl::event_y() );
		}
		else {
			this->handle_rotate_( Fl::event_x(),Fl::event_y() );
		}
		return 1;
	case FL_MOVE:	// mouse moved
		return 1;
	case FL_RELEASE:	// mouse up event
		return 1;
	case FL_MOUSEWHEEL:
//std::cout << "wheel " << "dx=" <<  Fl::event_dx() << "dy=" <<  Fl::event_dy() << std::endl;
		this->handle_frontback_( Fl::event_dy() );
		return 1;

	case FL_FOCUS:	// Return 1 if you want keyboard events, 0 otherwise
		return 1;
	case FL_UNFOCUS:// Return 1 if you want keyboard events, 0 otherwise
		return 1;

	case FL_KEYBOARD:
//... keypress, key is in Fl::event_key(), ascii in Fl::event_text()
//... Return 1 if you understand/use the keyboard event, 0 otherwise...
		this->handle_keyboard_( Fl::event_key(), Fl::event_text() );
		return 1;
	case FL_SHORTCUT: /* FL_KEYBOARDに取られてここにはこない */
//... shortcut, key is in Fl::event_key(), ascii in Fl::event_text()
//... Return 1 if you understand/use the shortcut event, 0 otherwise...
		return 1;
	default:
		// pass other events to the base class...
		return Fl_Gl_Window::handle(event);
	}
}

//--------------------
#if defined DEBUG_FL_GL_HSV_SPACE_WINDOW
int main(void) {
	Fl_Window win(1000, 500, "OpenGL");
	fl_gl_hsv_space_window ogl(0, 0, win.w(), win.h());
	win.end();
	win.resizable(ogl);
	win.show();
	return Fl::run();
}
#endif /* !DEBUG_FL_GL_HSV_SPACE_WINDOW */
/*
rem
rem :773,774 w! make.bat
cl /W3 /MD /EHa /O2 /wd4819 /DWIN32 /DDEBUG_FL_GL_HSV_SPACE_WINDOW /I..\..\thirdparty\fltk\fltk-1.3.4-1 /I..\thirdparty\glew\glew-2.1.0\include ..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltk-1.3.4-1-vc2013-32.lib ..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltkgl-1.3.4-1-vc2013-32.lib ..\thirdparty\glew\glew-2.1.0\lib\Release\Win32\glew32s.lib glu32.lib advapi32.lib shlwapi.lib opengl32.lib comctl32.lib wsock32.lib user32.lib gdi32.lib shell32.lib ole32.lib comdlg32.lib t28.cpp /Fea
del t28.obj
*/
