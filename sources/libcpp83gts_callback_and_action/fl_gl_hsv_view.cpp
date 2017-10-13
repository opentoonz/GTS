#include <cassert>	/* assert(-) */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>	/* sin(-) cos(-) */
#include <random>	/* mt19937 */
#include <chrono>

#define GLEW_STATIC	/* use glew32s.lib */
#include <GL/glew.h>	/* gl.hより前に必要 */

//#include <FL/Fl.H>
//#include <FL/Fl_Gl_Window.H>
#include "FL/fl_ask.H"  // fl_alert(-)
//#include <FL/gl.h>	/* GLfloat GLubyte GLuint GLenum */
#include <FL/glu.h>	/* gluPerspective(-) , gluLookAt(-) */
#include <FL/glut.h>	/* glutWireTeapot(-) glutWireCone(-) */
			/* glutExtensionSupported(-) --> link error */
#include "calcu_rgb_to_hsv.h"
#include "calcu_color_trace_sep_hsv.h"
#include "fl_gl_hsv_view.h"
#include "gts_master.h"
#include "gts_gui.h"


/*---------- 時間計測 ----------*/
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

/*---------- 単位変換 ----------*/

namespace gts {

double rad_from_deg( const double deg )
{
	return 3.14159265358979323846264338327950288 * deg / 180.0;
}
double liner_from_rad( const double rad )
{
	const double si = sin(rad);
	const double co = cos(rad);
	const double x = si / (si+co);
	const double z = 1. - co / (si+co);
	return sqrt( x * x + z * z ) / sqrt(2.);
}

} // gts

/*---------- opengl_camera_eye関数 ----------*/

gts::opengl_camera_eye::opengl_camera_eye()
	:eye_x_(0.) ,eye_y_(0.) ,eye_z_(10.)
	,cen_x_(0.) ,cen_y_(0.) ,cen_z_(0.)
	,upp_x_(0.) ,upp_y_(1.) ,upp_z_(0.)
	,fovy_(30.) ,znear_(9.) ,zfar_(-11.)
{
	assert (0. < this->fovy_); /* ゼロ以下は致命的エラー */
	this->reset_eye();
}

void gts::opengl_camera_eye::set_full_range_about_near_far_(void)
{
	double x = this->eye_x_ - this->cen_x_;
	double y = this->eye_y_ - this->cen_y_;
	double z = this->eye_z_ - this->cen_z_;
	const double len = sqrt( x * x + y * y + z * z );
	this->znear_ = len / 100.0;
	this->zfar_  = len * 2.0 - len / 100.0;
}

void gts::opengl_camera_eye::reset_eye(void)
{
	/* 視点 注視点 の距離
	視野角がfovy_で、(0,0,0)を注視点としたとき、
	注視点を中心とした半径1の球全体がピッタリ入るような視点の位置 */
	const double zlen= 1. / sin( gts::rad_from_deg(this->fovy_) / 2. );

	/*	視点位置	(0,0,z)
		注視点位置	(0,0,0)
		頭上ベクトル	(0,1,0) */
	this->eye_x_ = 0.; this->eye_y_ = 0.; this->eye_z_ = zlen;// Pos.
	this->cen_x_ = 0.; this->cen_y_ = 0.; this->cen_z_ = 0.;  // Pos.
	this->upp_x_ = 0.; this->upp_y_ = 1.; this->upp_z_ = 0.;  // Vector

	/* z depth値再設定 */
	this->set_full_range_about_near_far_();
}

namespace {
void rotate2d( const double x , const double y , const double radian , double& x2 , double& y2 ) {
	x2 = x * cos( radian ) - y * sin( radian );
	y2 = x * sin( radian ) + y * cos( radian );
}
void rotate3d_vector_(
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
void cross_product_(
  const double x1 , const double y1 , const double z1
, const double x2 , const double y2 , const double z2
, double& x , double& y , double& z
)
{
	x = y1*z2 - z1*y2;
	y = z1*x2 - x1*z2;
	z = x1*y2 - y1*x2;
}
void vector_to_unit_( double& vx ,double& vy ,double& vz )
{
	const double len = sqrt( vx*vx + vy*vy + vz*vz );
	vx /= len;
	vy /= len;
	vz /= len;
}
void camera_to_x_vector_(
double evx , double evy , double evz
,const double uvx ,const double uvy ,const double uvz
,double& vx ,double& vy ,double& vz
)
{
	/* 視線ベクトル単位化 */
	vector_to_unit_( evx ,evy ,evz );

	/* カメラ横方向ベクトル */
	cross_product_( uvx ,uvy ,uvz ,evx ,evy ,evz ,vx ,vy ,vz );

	/* カメラ横方向ベクトル単位化 */
	vector_to_unit_( vx ,vy ,vz );
}
} // namespace

void gts::opengl_camera_eye::rotate( const double degree_x ,const double degree_y )
{
  if (degree_x != 0) {
	/* x方向マウス移動は視点をカメラ座標系y軸回転 */
	rotate3d_vector_(
	 this->eye_x_ ,this->eye_y_ ,this->eye_z_
	,this->cen_x_ ,this->cen_y_ ,this->cen_z_/* 回転の中心 */
	,this->upp_x_ ,this->upp_y_ ,this->upp_z_/* 回転軸ベクトル */
	, - gts::rad_from_deg(degree_x)
	, this->eye_x_ , this->eye_y_ , this->eye_z_
	);
  }
  if (degree_y != 0) {
	/* y方向マウス移動はx軸回転 */
	const double xr=gts::rad_from_deg(degree_y);

	/* カメラ横方向ベクトル */
	double lr_x = 0.;
	double lr_y = 0.;
	double lr_z = 0.;
	camera_to_x_vector_(
		this->cen_x_ - this->eye_x_
		,this->cen_y_ - this->eye_y_
		,this->cen_z_ - this->eye_z_
		,this->upp_x_ ,this->upp_y_ ,this->upp_z_
		,lr_x ,lr_y ,lr_z
	);

	rotate3d_vector_(
		 this->eye_x_ , this->eye_y_ , this->eye_z_
		,this->cen_x_ , this->cen_y_ , this->cen_z_/* 回転の中心 */
		, lr_x , lr_y , lr_z /* 回転の軸ベクトル */
		, xr
		, this->eye_x_ , this->eye_y_ , this->eye_z_
	);
	rotate3d_vector_(
		 this->upp_x_ , this->upp_y_ , this->upp_z_
		,0. ,0. ,0./* 回転の中心 */
		, lr_x , lr_y , lr_z /* 回転の軸ベクトル */
		, xr
		, this->upp_x_ , this->upp_y_ , this->upp_z_
	);
	vector_to_unit_( this->upp_x_ ,this->upp_y_ ,this->upp_z_ );
  }
} 
void gts::opengl_camera_eye::updownleftright( const double scale_camera_x ,const double scale_camera_y )
{
	/* カメラ横方向ベクトル */
	double lr_x = 0.;
	double lr_y = 0.;
	double lr_z = 0.;
	camera_to_x_vector_(
		this->cen_x_ - this->eye_x_
		,this->cen_y_ - this->eye_y_
		,this->cen_z_ - this->eye_z_
		,this->upp_x_ ,this->upp_y_ ,this->upp_z_
		,lr_x ,lr_y ,lr_z
	);

	this->eye_x_ += lr_x * scale_camera_x;
	this->eye_y_ += lr_y * scale_camera_x;
	this->eye_z_ += lr_z * scale_camera_x;
	this->cen_x_ += lr_x * scale_camera_x;
	this->cen_y_ += lr_y * scale_camera_x;
	this->cen_z_ += lr_z * scale_camera_x;

	this->eye_x_ += this->upp_x_ * scale_camera_y;
	this->eye_y_ += this->upp_y_ * scale_camera_y;
	this->eye_z_ += this->upp_z_ * scale_camera_y;
	this->cen_x_ += this->upp_x_ * scale_camera_y;
	this->cen_y_ += this->upp_y_ * scale_camera_y;
	this->cen_z_ += this->upp_z_ * scale_camera_y;
}

void gts::opengl_camera_eye::frontback( const double scale_camera_z)
{
	/* 視線ベクトル */
	double fb_x = this->cen_x_ - this->eye_x_;
	double fb_y = this->cen_y_ - this->eye_y_;
	double fb_z = this->cen_z_ - this->eye_z_;
	vector_to_unit_( fb_x ,fb_y ,fb_z );

	/* 視線ベクトルでカメラ移動 */
	this->eye_x_ += fb_x * scale_camera_z;
	this->eye_y_ += fb_y * scale_camera_z;
	this->eye_z_ += fb_z * scale_camera_z;
	this->cen_x_ += fb_x * scale_camera_z;
	this->cen_y_ += fb_y * scale_camera_z;
	this->cen_z_ += fb_z * scale_camera_z;
}

void gts::opengl_camera_eye::scale_self( const double scale )
{
	/* 注視点から視点へのベクトル */
	double vx = this->eye_x_ - this->cen_x_;
	double vy = this->eye_y_ - this->cen_y_;
	double vz = this->eye_z_ - this->cen_z_;

	/* 注視点を中心にして、ベクトルを拡大縮小 */
	vx *= scale;
	vy *= scale;
	vz *= scale;

	/* 拡大縮小したベクトルを元にした視点 */
	this->eye_x_ = vx + this->cen_x_;
	this->eye_y_ = vy + this->cen_y_;
	this->eye_z_ = vz + this->cen_z_;

	this->set_full_range_about_near_far_();
}

/*---------- OpenGLの情報表示 ----------*/

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

/*---------- opengl_vbo関数 ----------*/

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
	,hsv_view_start_sw_(false)
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
	glGenBuffers( sizeof(this->id_vbo_)/sizeof(GLuint),this->id_vbo_ );

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
		<< this->pixel_size_ * sizeof(vbo_float) * 3 << "bytes\n";
	std::cout << " color buffer="
		<< this->pixel_size_ * sizeof(GLubyte)   * 3 << "bytes\n";
	std::cout << "        total="
		<< this->pixel_size_ * sizeof(vbo_float) * 3
		 + this->pixel_size_ * sizeof(GLubyte)   * 3 << "bytes\n";
}

namespace {
void hsv_to_xyz_(
	const double h , const double s , const double v
	,double& x , double& y , double& z
)
{
	x = cos( gts::rad_from_deg(h) ) * s * v;
	y = sin( gts::rad_from_deg(h) ) * s * v;
	z = 1. - v;
}
} // namespace

void gts::opengl_vbo::hsv_to_xyz(
	const double h , const double s , const double v
	, gts::opengl_vbo::vbo_float* xyz
)
{
	/* hsv --> xyz */
	double x = 0.;
	double y = 0.;
	double z = 0.;
	hsv_to_xyz_( h,s,v ,x,y,z );

	xyz[0] = static_cast<gts::opengl_vbo::vbo_float>(x);
	xyz[1] = static_cast<gts::opengl_vbo::vbo_float>(y);
	xyz[2] = static_cast<gts::opengl_vbo::vbo_float>(z);
}

/*---------- fl_gl_hsv_view関数 ----------*/

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

fl_gl_hsv_view::fl_gl_hsv_view(int x ,int y ,int w ,int h ,const char*l)
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
	,pixel_x_(-1.)
	,pixel_y_(-1.)
	,pixel_z_(-1.)
{
	/* 初期化できない？ので代入 */
	this->bg_rgba_[0] = this->bg_rgba_[1] = this->bg_rgba_[2] = 0.f;
	this->bg_rgba_[3] = 1.f;

	/* dummy_rgb_image_ に8bitサンプリングでランダムなrgb画像を生成 */
//	this->dummy_create_rgb_image_( this->dummy_w_ * this->dummy_h_ / 2);
}

void fl_gl_hsv_view::dummy_create_rgb_image_(
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

/*
	0  -------x----->  X
	0  -------S----->  1
    0 1 t------S-----------i   1
        | \   /          /
        |  \  /        /
    | ^ |    o       /
    | | |   /  \   /
    z V |  /     T   T
    | | |  /   /
    v | | /  /
        |/ /
        |/
    1 0 s   0

	上記平面をxz平面としたとき
		i = ( 1 , 0 )
	Sを通る２点の座標値
		S = ( S*X , 0 ) // ( x1 , z1 )
		s = ( 0   , 1 ) // ( x2 , z2 )
	Tを通る２点の座標値
		T = ( T*X , (1-T) + (1-Offset) ) // ( x1 , z1 )
		t = ( 0   ,       + (1-Offset) ) // ( x2 , z2 )
	1-T      = omT 
	1-Offset = omO とすると
		T = ( T*X , omT+omO ) // ( x1 , z1 )
		t = ( 0   ,    +omO ) // ( x2 , z2 )
	直線の方程式
		z - z1 = (z2 - z1) / (x2 - x1) * (x - x1)
	よりS-s直線は
		z -  0 = ( 1 -  0) / ( 0 - S*X) * (x -  S*X)
		z = 1 / (-S*X) * (x - S*X)
		z = -1 / (S*X) * x - (-1) / (S*X) * S*X
		z = -x/(S*X) + 1 .............................(1)
	T-t直線は
		z - (omT+omO) = (omO-(omT+omO)) / (0-(T*X)) * (x-(T*X))
		z - (omT+omO) = (omO-omT-omO)   / (0-(T*X)) * (x-(T*X))
		z - (omT+omO) = (-omT) / (-(T*X)) * (x-(T*X))
		z = omT/(T*X)*(x-(T*X)) + (omT+omO)
		z = omT/(T*X)*x - omT/(T*X)*(T*X) + (omT+omO)
		z = x*omT/(T*X) - omT + omT + omO
		z = x*omT/(T*X) + omO .........................(2)
  ○交点oを求める
	S-s直線(1)とT-t直線(2)より
		x*omT/(T*X) + omO      = -x/(S*X) + 1
		x*omT/(T*X) + x/(S*X)  = 1-omO
		x(omT/(T*X) + 1/(S*X)) = 1-omO
		x = (1-omO) / (omT/(T*X) + 1/(S*X))
		x = (1-omO)*S*T*X / (omT*S + T)
		x = (1-(1-Offset))*S*T*X / ((1-T)*S + T)
		x = Offset*S*T*X / ((1-T)*S + T) ..............(3)
	(3)を(2)に代入して
		z = x*omT/(T*X) + omO
		z = x*(1-T)/(T*X) + (1-Offset) ................(4)

  ○交点Tを求める
	Tを通る２点の座標値
		s = ( 0 , 1 )	// ( x1 , z1 )
		i = ( X , 0 )	// ( x2 , z2 )
	よりs-i直線
		z - 1 = ( 0 - 1 ) / ( X - 0 ) * (x - 0)
		z - 1 = (-1) / X * x
		z = -x/X + 1 ----------------------------------(5)
	T-t直線(2)より
		x*omT/(T*X) + omO   = -x/X + 1
		x*omT/(T*X) + x/X   = 1 - omO
		x*(omT/(T*X) + 1/X) = 1 - omO
		x = (1-omO) / (omT/(T*X) + 1/X)
		x = (1-(1-Offset)) / ((1-T)/(T*X) + 1/X)
		x = Offset / ((1-T)/(T*X) + 1/X)
		x = Offset*T*X / ((1-T) + T)
		x = Offset*T*X --------------------------------(6)
	(6)を(2)に代入して
		z = Offset*T*X*omT/(T*X) + omO
		z = Offset*omT + omO
		z = Offset*(1-T) + (1-Offset)
		z = Offset - Offset*T + 1 - Offset
		z = - Offset*T + 1
		z = 1 - Offset*T ------------------------------(7)
*/
namespace {

void xyzout_to_xyzin_(
	const double xout , const double yout
	,const double ss , const double tt ,const double offset
	,double& xin , double& yin , double& zin
)
{
	xin = offset * ss * tt * xout / ((1.-tt) * ss + tt);
	yin = offset * ss * tt * yout / ((1.-tt) * ss + tt);
	if (tt == 0.) {
	 zin = 1.;
	} else {
	 zin = xin * (1. - tt) / (tt * xout) + (1. - offset);
	}
}

void xyzout_to_xyzmid_(
	const double xout , const double yout
	,const double tt ,const double offset
	,double& xin , double& yin , double& zin
)
{
	xin = offset * tt * xout;
	yin = offset * tt * yout;
	zin = 1. - offset * tt;
}

void draw_one_partition_(
	const double x1 ,const double y1 ,const double z1
	,const double x4 ,const double y4 ,const double z4
	,const double x5 ,const double y5 ,const double z5
	,const double x8 ,const double y8 ,const double z8
	,const double hue_r ,const double hue_g ,const double hue_b
	,const double tgt_r ,const double tgt_g ,const double tgt_b
	,const double s_e_r ,const double s_e_g ,const double s_e_b
)
{
	double	 x3 = x4+(x1-x4)*2./3.
		,y3 = y4+(y1-y4)*2./3.
		,z3 = z4+(z1-z4)*2./3.
		,x6 = x5+(x8-x5)*2./3.
		,y6 = y5+(y8-y5)*2./3.
		,z6 = z5+(z8-z5)*2./3. ;
	double	 x2 = x3+(x1-x3)*2./3.
		,y2 = y3+(y1-y3)*2./3.
		,z2 = z3+(z1-z3)*2./3.
		,x7 = x6+(x8-x6)*2./3.
		,y7 = y6+(y8-y6)*2./3.
		,z7 = z6+(z8-z6)*2./3. ;

	/* 外側 現位置のHue色 */
	glColor3d( hue_r ,hue_g ,hue_b );

	/* 外側 Hue開始表示 */
	glBegin(GL_QUADS);
	glVertex3d(x1,y1,z1);
	glVertex3d(x2,y2,z2);
	glVertex3d(x7,y7,z7);
	glVertex3d(x8,y8,z8);
	glEnd();

	/* 中側 Target色 */
	glColor3d( tgt_r ,tgt_g ,tgt_b );

	/* 中側 Hue色表示 */
	glBegin(GL_QUADS);
	glVertex3d(x2,y2,z2);
	glVertex3d(x3,y3,z3);
	glVertex3d(x6,y6,z6);
	glVertex3d(x7,y7,z7);
	glEnd();

	/* 内側 Hue開始/終了色 & 色点用背景色 */
	glColor3d( s_e_r ,s_e_g ,s_e_b );

	/* 内側 Target色表示 */
	glBegin(GL_QUADS);
	glVertex3d(x3,y3,z3);
	glVertex3d(x4,y4,z4);
	glVertex3d(x5,y5,z5);
	glVertex3d(x6,y6,z6);
	glEnd();

	/* 現位置のHue色 */
	glColor3d( hue_r ,hue_g ,hue_b );

	/* 裏でも存在を示すためのワイヤーフレーム表示 */
	glBegin(GL_LINE_LOOP);
	glVertex3d(x1,y1,z1);
	glVertex3d(x4,y4,z4);
	glVertex3d(x5,y5,z5);
	glVertex3d(x8,y8,z8);
	glEnd();
}

void draw_color_partition_(
	const double thickness
	,const double hue_min
	,const double hue_max
	,const double thre_slope_line
	,const double thre_intercept
	,const double target_r
	,const double target_g
	,const double target_b
)
{
/*
	HSV View
	Color Area
	Guide Partition

	White   --> S -->      Color
	    4             3  2  1
	+---+------------------+
	|   |           \    \
	|   |         \    \
	|  |        \    \
	|  +     \     \
	| 5 /  \     \
	|    +     \
	|   6 /  \
	|    7 +
	|    \ 8
	|  \
	|\
	+
	Black

	1 2 7 8	--> Hue Start or End Color 白/黒
	2 3 6 7	--> その位置でのHue色
	3 4 5 6	--> Target色
*/

	/*---------- hue_min ----------*/
	glEnable(GL_CULL_FACE);	/* 片面表示（glCullFace）を有効に */
	glCullFace(GL_BACK);	/* 後面を破棄 */

	{
	const auto tt = 1. - thickness;
	const double	x1 = cos( gts::rad_from_deg(hue_min) )
			,y1 = sin( gts::rad_from_deg(hue_min) )
			,z1 = 0.;
	double		x5 = 0. ,y5 = 0. ,z5 = 0.;
	xyzout_to_xyzin_( x1,y1 ,tt,thre_slope_line,thre_intercept ,x5,y5,z5 );
	const double	x4 = x1*tt ,y4 = y1*tt ,z4 = 0.;
	double		x8 = 0. ,y8 = 0. ,z8 = 0.;
	xyzout_to_xyzmid_( x1,y1 ,thre_slope_line,thre_intercept ,x8,y8,z8 );

	/* 現位置Hue色 */
	calcu_rgb_to_hsv cl_hsv;
	double r=0.,g=0.,b=0.;
	cl_hsv.from_hsv( hue_min,1.,1. ,&r,&g,&b );

	draw_one_partition_(
		x1,y1,z1 ,x4,y4,z4 ,x5,y5,z5 ,x8,y8,z8
		,r,g,b
		,target_r ,target_g ,target_b
		,0.666666 ,0.666666 ,0.666666
	);

	/* 色点用背景色 */
	const double hdiff = (hue_min <= hue_max)? hue_max-hue_min: hue_max+360.-hue_min;
	glColor3d( 0.5 ,0.5 ,0.5 );
	glBegin(GL_QUAD_STRIP);
	for (double ii=0.; ii<=hdiff; ii+=1.) {
		const double rad = gts::rad_from_deg( ii );
		double x1=0. ,y1=0.;
		double x2=0. ,y2=0.;
		rotate2d( x4,y4, rad , x1,y1 );
		rotate2d( x5,y5, rad , x2,y2 );
		glVertex3d( x2,y2,z5 );
		glVertex3d( x1,y1,z4 );
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (double ii=0.; ii<=hdiff; ii+=1.) {
		const double rad = gts::rad_from_deg( ii );
		double x1=0. ,y1=0.;
		double x2=0. ,y2=0.;
		rotate2d( x5,y5, rad , x1,y1 );
		rotate2d( x8,y8, rad , x2,y2 );
		glVertex3d( x2,y2,z8 );
		glVertex3d( x1,y1,z5 );
	}
	glEnd();

	/* 回転部分ワイヤーフレーム */
	glColor3d( target_r ,target_g ,target_b );
	glBegin(GL_LINE_STRIP);
	for (double ii=0.; ii<=hdiff; ii+=1.) {
		const double rad = gts::rad_from_deg( ii );
		double x1=0. ,y1=0.;
		rotate2d( x4,y4, rad , x1,y1 );
		glVertex3d( x1,y1,z4 );
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (double ii=0.; ii<=hdiff; ii+=1.) {
		const double rad = gts::rad_from_deg( ii );
		double x1=0. ,y1=0.;
		rotate2d( x5,y5, rad , x1,y1 );
		glVertex3d( x1,y1,z5 );
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for (double ii=0.; ii<=hdiff; ii+=1.) {
		const double rad = gts::rad_from_deg( ii );
		double x1=0. ,y1=0.;
		rotate2d( x8,y8, rad , x1,y1 );
		glVertex3d( x1,y1,z8 );
	}
	glEnd();
	}

	/*---------- hue_max ----------*/
	glEnable(GL_CULL_FACE);	/* 片面表示（glCullFace）を有効に */
	glCullFace(GL_FRONT);	/* 表面を破棄 */

	{
	const auto tt = 1. - thickness;
	const double	x1 = cos( gts::rad_from_deg(hue_max) )
			,y1 = sin( gts::rad_from_deg(hue_max) )
			,z1 = 0.;
	double		x5 = 0. ,y5 = 0. ,z5 = 0.;
	xyzout_to_xyzin_( x1,y1 ,tt,thre_slope_line,thre_intercept,x5,y5,z5 );
	const double	x4 = x1*tt ,y4 = y1*tt ,z4 = 0.;
	double		x8 = 0. ,y8 = 0. ,z8 = 0.;
	xyzout_to_xyzmid_( x1,y1 ,thre_slope_line,thre_intercept ,x8,y8,z8 );

	/* 外側 現位置Hue色 */
	calcu_rgb_to_hsv cl_hsv;
	double r=0.,g=0.,b=0.;
	cl_hsv.from_hsv( hue_max,1.,1. ,&r,&g,&b );

	draw_one_partition_(
		x1,y1,z1 ,x4,y4,z4 ,x5,y5,z5 ,x8,y8,z8
		,r,g,b
		,target_r ,target_g ,target_b
		,0.333333 ,0.333333 ,0.333333
	);
	}
}

void draw_black_partition_(
	double thickness
	,double slope_line
	,double intercept
)
{
	/* 現位置が範囲外 --> 表示しない */
	//if (z < (1. - intercept)) { return; }

	/* 白側
		z = x*omT/(T*X) + omO .........................(2)

		z - omO = x*omT/(T*X)
		x*omT/(T*X) = z - omO
		x*omT/(T*X) = (z - omO)
		x = (z-(1-Offset)) * (T*X) / (1-T)
	xがゼロになるz値は
		0 = (z-(1-Offset)) * (T*X) / (1-T)
		0 = z * (T*X) / (1-T) - (1-Offset) * (T*X) / (1-T)
		z * (T*X) / (1-T) = (1-Offset) * (T*X) / (1-T)
		z = (1-Offset) * (T*X) / (1-T) / (T*X) * (1-T) 
		z = 1-Offset
	*/

	/* 太さ値からz位置に */
	double z = 1. - thickness;

	/* (7)式より、最外点のz位置 */
	const double zfar = 1. - intercept * slope_line;

	double x = 0.;
	if (z < zfar) {
		x =
	(z - (1. - intercept)) * slope_line * 1. / (1. - slope_line);
	}
	/* 黒側 */
	else if (zfar <= z) {
		x = thickness;
	}

	/*---------- 表示 ----------*/
	glEnable(GL_CULL_FACE);	/* 片面表示（glCullFace）を有効に */
	glCullFace(GL_BACK);	/* 後面を破棄 */

	glColor3d(1.,1.,1.);

	/* 傘天板 */
	if ((1. - intercept) <= z) {
	 glBegin(GL_TRIANGLE_FAN);
	 glVertex3d( 0. ,0. ,z );
	 for (int ii=0; ii<=360; ++ii) {
		const double rad = gts::rad_from_deg(
					static_cast<double>(ii) );
		glVertex3d( x*cos(rad) ,x*sin(rad) ,z );
	 }
	 glEnd();
	}

	/* 傘円錐 */
	if (z < zfar) {
	 /* (6)式より、最外点の横位置 */
	 const double xfar = intercept * slope_line * 1.;
	 if (x < 0.) {
		x = 0.;
		z = 1. - intercept;
	 }
	 glBegin(GL_QUAD_STRIP);
	 for (int ii=0; ii<=360; ++ii) {
		const double rad = gts::rad_from_deg( ii );
		double x1=0. ,y1=0.;
		double x2=0. ,y2=0.;
		rotate2d( x  ,0. ,rad ,x1,y1 );
		rotate2d( xfar ,0. ,rad ,x2,y2 );
		glVertex3d( x1,y1,z );
		glVertex3d( x2,y2,zfar );
	 }
	 glEnd();
	}
}

void draw_guide_display_()
{
	/* マスタースイッチがオフならガイドはすべて表示しない */
	if (cl_gts_gui.chebut_trace_display_main_sw->value() == 0) {
		return;
	}

	/* 各2値化範囲のガイド表示 */
	for (unsigned ii=0
	;ii<cl_gts_master.cl_trace_params.widget_sets.size() ;++ii) {
		auto&wset=cl_gts_master.cl_trace_params.widget_sets.at(ii);

		/* 無効かガイド表示オフなら次へ */
		if (wset.chebut_enable_sw->value()==0
		||  wset.chebut_display_sw->value()==0) {
			continue;
		}

		/* 黒線範囲ガイド表示 */
		if (wset.valinp_hue_min->value() < 0.
		||  wset.valinp_hue_max->value() < 0.) {
			draw_black_partition_(
				wset.valinp_thickness->value()
				/wset.valinp_thickness->maximum()
 ,gts::liner_from_rad(gts::rad_from_deg(wset.valinp_slope_deg->value()))
				,wset.valinp_intercept->value()
				/wset.valinp_intercept->maximum()
			);
		}
		/* 色線範囲ガイド表示 */
		else {
			uchar r=0,g=0,b=0;
			cl_gts_master.cl_trace_params.get_target_rgb( ii,r,g,b );
			const double mx = (std::numeric_limits<uchar>::max)();
			draw_color_partition_(
				wset.valinp_thickness->value()
				/wset.valinp_thickness->maximum()
				,wset.valinp_hue_min->value()
				,wset.valinp_hue_max->value()
 ,gts::liner_from_rad(gts::rad_from_deg(wset.valinp_slope_deg->value()))
				,wset.valinp_intercept->value()
				/wset.valinp_intercept->maximum()
				,static_cast<double>(r) / mx
				,static_cast<double>(g) / mx
				,static_cast<double>(b) / mx
			);
		}
	}
}

void draw_pixel_mark_( const double x ,const double y ,const double z )
{
	if (z < 0.) {
		return;
	}

	/* 現位置のhue色 */
	glColor3d( 1. ,1. ,1. );

	/* 裏でも存在を示すためのワイヤーフレーム表示 */
	const double n=0.005 ,f=0.1;
	glBegin(GL_LINES);glVertex3d(x+n,y,z);glVertex3d(x+f,y,z);glEnd();
	glBegin(GL_LINES);glVertex3d(x,y+n,z);glVertex3d(x,y+f,z);glEnd();
	glBegin(GL_LINES);glVertex3d(x,y,z+n);glVertex3d(x,y,z+f);glEnd();
	glBegin(GL_LINES);glVertex3d(x-n,y,z);glVertex3d(x-f,y,z);glEnd();
	glBegin(GL_LINES);glVertex3d(x,y-n,z);glVertex3d(x,y-f,z);glEnd();
	glBegin(GL_LINES);glVertex3d(x,y,z-n);glVertex3d(x,y,z-f);glEnd();
}

void draw_camera_center_mark_(
 const double cx ,const double cy ,const double cz
,const double ex ,const double ey ,const double ez
,const double vvx ,const double vvy ,const double vvz
,const double zfar
)
{
	/* マスタースイッチがオフならガイドはすべて表示しない */
	if (cl_gts_gui.chebut_trace_display_main_sw->value() == 0) {
		return;
	}
	if (cl_gts_gui.chebut_trace_display_target_sw->value() == 0) {
		return;
	}

	/* 現位置のhue色 */
	glColor3d( 1. ,1. ,1. );

	/* ワールド座標軸方向表示 */
	const double n = zfar * 0.01;
	glBegin(GL_LINES);
	glVertex3d(cx-n,cy,cz);
	glVertex3d(cx+n,cy,cz);
	glEnd();
	glBegin(GL_LINES);
	glVertex3d(cx,cy-n,cz);
	glVertex3d(cx,cy+n,cz);
	glEnd();
	glBegin(GL_LINES);
	glVertex3d(cx,cy,cz-n);
	glVertex3d(cx,cy,cz+n);
	glEnd();

	/* カメラ注視点位置を示す */
	double hvx = 0. ,hvy = 0. ,hvz = 0.;
	camera_to_x_vector_(
		cx-ex ,cy-ey ,cz-ez ,vvx ,vvy ,vvz ,hvx ,hvy ,hvz
	);

	const double h1x = hvx * zfar * 0.01;
	const double h1y = hvy * zfar * 0.01;
	const double h1z = hvz * zfar * 0.01;
	const double h2x = hvx * zfar * 0.04;
	const double h2y = hvy * zfar * 0.04;
	const double h2z = hvz * zfar * 0.04;

	const double v1x = vvx * zfar * 0.01;
	const double v1y = vvy * zfar * 0.01;
	const double v1z = vvz * zfar * 0.01;
	const double v2x = vvx * zfar * 0.04;
	const double v2y = vvy * zfar * 0.04;
	const double v2z = vvz * zfar * 0.04;

	glEnable(GL_CULL_FACE);	/* 片面表示（glCullFace）を有効に */
	glCullFace(GL_BACK);	/* 後面を破棄 */

	glBegin(GL_TRIANGLES);
	glVertex3d(cx + h1x       ,cy + h1y       ,cz + h1z);
	glVertex3d(cx + h2x + v1x ,cy + h2y + v1y ,cz + h2z + v1z);
	glVertex3d(cx + h2x - v1x ,cy + h2y - v1y ,cz + h2z - v1z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3d(cx - h1x       ,cy - h1y       ,cz - h1z);
	glVertex3d(cx - h2x - v1x ,cy - h2y - v1y ,cz - h2z - v1z);
	glVertex3d(cx - h2x + v1x ,cy - h2y + v1y ,cz - h2z + v1z);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3d(cx + v1x       ,cy + v1y       ,cz + v1z);
	glVertex3d(cx + v2x - h1x ,cy + v2y - h1y ,cz + v2z - h1z);
	glVertex3d(cx + v2x + h1x ,cy + v2y + h1y ,cz + v2z + h1z);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3d(cx - v1x       ,cy - v1y       ,cz - v1z);
	glVertex3d(cx - v2x + h1x ,cy - v2y + h1y ,cz - v2z + h1z);
	glVertex3d(cx - v2x - h1x ,cy - v2y - h1y ,cz - v2z - h1z);
	glEnd();
}

} // namespace

void fl_gl_hsv_view::draw_object_()
{
	/* エリアガイド表示 */
	glColor3d(1.0, 1.0, 1.0);
	glutWireCone(1.0 ,1.0 ,36 ,2);

	/* 中心軸ガイド表示 */
	glColor3d(1.0, 1.0, 1.0); // Draw red 
	glBegin(GL_LINE_STRIP);
		glVertex3d(0. , 0. , 0.0);
		glVertex3d(0. , 0. , 1.0);
	glEnd();

	/* 区切ガイド */
	draw_guide_display_();

	/* ポイント表示 */
	this->vbo.draw();

	/* 指定の画像pixelのrgb値からhsv-->xyz位置のマーキング表示 */
	draw_pixel_mark_( this->pixel_x_ ,this->pixel_y_ ,this->pixel_z_ );

	/* カメラ注視点マーク */
/* 未公開 */
	draw_camera_center_mark_( 
		this->eye.get_cen_x()
		,this->eye.get_cen_y()
		,this->eye.get_cen_z()
		,this->eye.get_eye_x()
		,this->eye.get_eye_y()
		,this->eye.get_eye_z()
		,this->eye.get_upp_x()
		,this->eye.get_upp_y()
		,this->eye.get_upp_z()
		,this->eye.get_zfar()
	);
}

void fl_gl_hsv_view::rgb_to_xyz(
	const double r
	,const double g
	,const double b
)
{
	if (r < 0 || g < 0. || b < 0.) {
		this->pixel_x_ = -1.;
		this->pixel_y_ = -1.;
		this->pixel_z_ = -1.;
		return;
	}

	double h = 0.;
	double s = 0.;
	double v = 0.;
	calcu_rgb_to_hsv rgb2hsv;
	rgb2hsv.to_hsv( r,g,b ,&h ,&s ,&v );
	hsv_to_xyz_(h,s,v ,this->pixel_x_ ,this->pixel_y_ ,this->pixel_z_);
}

void fl_gl_hsv_view::dummy_reset_vbo( const int pixel_size )
{
/*
	この処理が必要な場所で同等の処理を行うよう変更する
	fl_gl_hsv_view::vboを使いデータサイズと内容の設定
*/
	/* vbo初期化 */
	if (this->vbo.open_or_reopen( pixel_size )) {
		return; // by Error
	}
	this->vbo.pr_vbo_info();

	/* ダミーの画像サイズも変更しランダムし直し */
	this->dummy_create_rgb_image_( pixel_size / 2 );

	/* vbo colorデータ書き込み */
	GLubyte* rgb = this->vbo.start_color();
	if (rgb == nullptr) { /* open出来ていればここはこないはず */
	 assert(!"Error:vbo.start_color() return null");
	}
	unsigned char* da = this->dummy_rgb_image_.data();
	unsigned sz = this->dummy_rgb_image_.size();
	for (unsigned ii=0 ;ii< sz ;ii+=3, da+=3 ,rgb+=3) {
		rgb[0] = da[0];
		rgb[1] = da[1];
		rgb[2] = da[2];
	}
	this->vbo.end_color();

	/* dummy vbo vertexデータ書き込み */
	gts::stop_watch stwa; stwa.start();
	gts::opengl_vbo::vbo_float* xyz= this->vbo.start_vertex();
	if (xyz == nullptr) { /* open出来ていればここはこないはず */
	 assert(!"Error:vbo.start_vertex() return null");
	}
	da = this->dummy_rgb_image_.data();
	sz = this->dummy_rgb_image_.size();
	for (unsigned ii=0 ;ii< sz ;ii+=3, da+=3 ,xyz+=3) {
		/* rgb --> hsv */
		double h=0. ,s=0. ,v=0.;
		calcu_rgb_to_hsv rgb2hsv;
		rgb2hsv.to_hsv(
			da[0]/255. ,da[1]/255. ,da[2]/255. ,&h ,&s ,&v );

		this->vbo.hsv_to_xyz( h ,s ,v ,xyz );
	}
	this->vbo.end_vertex();
 std::cout << "from_rgb_to_xyz time=" << stwa.stop_ms().count() << "milisec\n";
}
void fl_gl_hsv_view::draw()
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
			/* HSV ViewウインドウのOpenGLが初期化された */
			this->vbo.set_hsv_view_start_sw(true);
		}

		/* ピクセル値あるいはサイズの変更 */
		//this->dummy_reset_vbo( this->w() * this->h() / 2 );
	}

	/* 表示範囲の再設定 */
	glViewport( 0 ,0 ,this->w(), this->h());

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

void fl_gl_hsv_view::handle_push_( const int mx ,const int my )
{
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;
}
void fl_gl_hsv_view::handle_rotate_( const int mx ,const int my )
{
	this->eye.rotate(
		static_cast<double>(mx - this->mouse_x_when_push_)
		,static_cast<double>(my - this->mouse_y_when_push_)
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}
void fl_gl_hsv_view::handle_updownleftright_( const int mx ,const int my )
{
	this->eye.updownleftright(
		static_cast<double>(mx - this->mouse_x_when_push_) * 0.002
		,static_cast<double>(my - this->mouse_y_when_push_) * 0.002
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}
void fl_gl_hsv_view::handle_frontback_( const int mx , const int my )
{
	this->eye.frontback(
		static_cast<double>(mx - this->mouse_x_when_push_) * 0.002
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}
void fl_gl_hsv_view::set_mouse_when_push_( const int mx , const int my )
{
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;
}
void fl_gl_hsv_view::handle_scale_( const int mx ,const int my )
{
	this->eye.scale_self(
	  static_cast<double>(mx - this->mouse_x_when_push_) * 0.1 + 1.0
	);
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	this->redraw();
}

void fl_gl_hsv_view::handle_keyboard_( const int key , const char* text )
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
	 case 'z':
		this->set_mouse_when_push_( 0 , 0 );
		this->handle_scale_( -1 ,-1 );
		break;
	 case 'x':
		this->set_mouse_when_push_( 0 , 0 );
		this->handle_scale_( 1 ,1 );
		break;
	 }
	}
}
int fl_gl_hsv_view::handle(int event)
{
	switch(event) {
	case FL_PUSH:	// mouse down event
		this->handle_push_( Fl::event_x() , Fl::event_y() );
		return 1;
	case FL_DRAG:	// mouse moved while down event
		if (Fl::event_state() & FL_SHIFT) {
/* 未公開 */
		this->handle_updownleftright_(Fl::event_x(),Fl::event_y());
		}
		else if (Fl::event_state() & FL_CTRL) {
/* 未公開 */
		this->handle_frontback_( Fl::event_x(),Fl::event_y() );
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
		this->set_mouse_when_push_( 0 , 0 );
		this->handle_scale_( Fl::event_dy() ,Fl::event_dy() );
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
#if defined DEBUG_FL_GL_HSV_VIEW
#include "to_hsv.cpp"
int main(void) {
	Fl_Window win(1000, 500, "OpenGL");
	fl_gl_hsv_view ogl(0, 0, win.w(), win.h());
	win.end();
	win.resizable(ogl);
	win.show();
	return Fl::run();
}
#endif /* !DEBUG_FL_GL_HSV_VIEW */
/*
rem
rem :956,957 w! make.bat
cl /W3 /MD /EHa /O2 /wd4819 /DWIN32 /DDEBUG_FL_GL_HSV_VIEW /I..\..\..\sources\libcpp38calcu_rgb_to_hsv /I..\..\..\sources\libcpp71iip_color_trace_hab /I..\..\thirdparty\glew\glew-2.1.0\include /I..\..\..\thirdparty\fltk\fltk-1.3.4-1 ../../../sources/build/lib/libcpp38calcu_rgb_to_hsv.lib ..\..\thirdparty\glew\glew-2.1.0\lib\Release\Win32\glew32s.lib ..\..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltk-1.3.4-1-vc2013-32.lib ..\..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltkgl-1.3.4-1-vc2013-32.lib glu32.lib advapi32.lib shlwapi.lib opengl32.lib comctl32.lib wsock32.lib user32.lib gdi32.lib shell32.lib ole32.lib comdlg32.lib fl_gl_hsv_view.cpp /Fea
del fl_gl_hsv_view.obj
*/
