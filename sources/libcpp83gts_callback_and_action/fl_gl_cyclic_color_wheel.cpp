#include <iostream>
#include <iomanip>
#include <vector>
#include <FL/glu.h>	/* gluOrtho2D(-) */
#include "fl_gl_cyclic_color_wheel.h"
#include "gts_master.h"

fl_gl_cyclic_color_wheel::fl_gl_cyclic_color_wheel(int x ,int y ,int w ,int h ,const char*l)
	:Fl_Gl_Window(x,y,w,h,l)
	,mouse_x_when_push_(0)
	,mouse_y_when_push_(0)
	,x_offset_(0.)
	,hue_offset_(0.)
	,hue_ranges_({
	// double minimum ,maximum; bool enable_sw;
	 { 330. , 60. ,true  }	// 0
	,{ 180. ,300. ,true  }	// 1
	,{  60. ,180. ,true  }	// 2
	,{ 300. ,301. ,false }	// 3
	,{ 301. ,330. ,false }	// 4
	})
	,hue_range_number_(0)
	,hue_range_is_max_(false)
{
}

namespace {
double cyclic_hue_degree_( double hue )
{
	while (hue < 0.) { hue += 360.; }
	while (360. <= hue) { hue -= 360.; }
	return hue;
}
}

void fl_gl_cyclic_color_wheel::set_hue_range_pos(const int num ,const bool is_max)
{
	/* 範囲外error */
	if ( num < 0 || static_cast<int>(this->hue_ranges_.size()) <= num)
	{ return; }

	/* hue現在位置を記憶 */
	auto& aa = this->hue_ranges_.at( num );
	auto& hh = ( is_max ?aa.maximum :aa.minimum );
	this->hue_offset_ = cyclic_hue_degree_( 180. - hh );
	this->x_offset_ = this->xpos_from_hue_(this->hue_offset_);

	/* パラメータ位置を記憶 */
	this->hue_range_number_ = num;
	this->hue_range_is_max_ = is_max;
}

void fl_gl_cyclic_color_wheel::set_hue_range_value(
 const int num ,const double mini ,const double maxi ,const bool enable_sw
)
{
	/* 範囲外error */
	if ( num < 0 || static_cast<int>(this->hue_ranges_.size()) <= num)
	{ return; }

	/* 値を記憶 */
	auto& aa = this->hue_ranges_.at(num);
	aa.minimum = mini;
	aa.maximum = maxi;
	aa.enable_sw = enable_sw;
}
double fl_gl_cyclic_color_wheel::get_hue(void)
{
	return rint( cyclic_hue_degree_( 180. - this->hue_offset_ ) );
}

/* 現在位置を最大/最小値にセットする */
void fl_gl_cyclic_color_wheel::set_position_to_min_or_max_()
{
	auto& aa = this->hue_ranges_.at(this->hue_range_number_);
	if (this->hue_range_is_max_) {
		//aa.maximum = std::fmod(180.-this->hue_offset_ ,360.);
		aa.maximum = cyclic_hue_degree_( 180. - this->hue_offset_ );
	} else {
		//aa.minimum = std::fmod(180.-this->hue_offset_ ,360.);
		aa.minimum = cyclic_hue_degree_( 180. - this->hue_offset_ );
	}
}
void fl_gl_cyclic_color_wheel::set_position_between_min_max( const double ratio )
{
	auto& aa = this->hue_ranges_.at(this->hue_range_number_);

	/* mini...maxiの間の長さ */
	double len = 0.;
	if (aa.minimum < aa.maximum) {
		len = aa.maximum - aa.minimum;
	} else {
		len = (360. - aa.minimum) + aa.maximum;
	}

	/* 色相の値 360以上の値もあり */
	double hh = 0.;
	if (this->hue_range_is_max_) {
		hh = len * (1. - ratio) + aa.minimum;
	} else {
		hh = len *       ratio  + aa.minimum;
	}

	/* 0...360の範囲で設定 */
	this->hue_offset_ = cyclic_hue_degree_( 180. - hh );

	/* 現在のwidgetの横幅内の位置 */
	this->x_offset_ = this->xpos_from_hue_(this->hue_offset_);
}
void fl_gl_cyclic_color_wheel::set_hue_range_is_max(const bool is_max )
{
	/*const int sz = 10;
	for (int ii=1 ;ii<sz ;++ii) {
		Sleep(100);
		auto ratio = static_cast<double>(ii)/sz;
		this->set_position_between_min_max( ratio );
		this->redraw();
	}*/ /* 動作しない--> redraw() しない */
	this->set_hue_range_pos( this->hue_range_number_ ,is_max );
}

void fl_gl_cyclic_color_wheel::draw_object_()
{
	/* display cyclic color wheel */
	std::vector<double> xp{
		-1./6.	// 0
		,0./6.	// 1
		,1./6.	// 2
		,2./6.	// 3
		,3./6.	// 4
		,4./6.	// 5
		,5./6.	// 6
		,6./6.	// 7
	};
	std::vector< std::vector<double> > rgb{
		 {1. ,0. ,0.}	// 0
		,{1. ,1. ,0.}	// 1
		,{0. ,1. ,0.}	// 2
		,{0. ,1. ,1.}	// 3
		,{0. ,0. ,1.}	// 4
		,{1. ,0. ,1.}	// 5
	};

	const int xpos = static_cast<int>(this->x_offset_) % this->w();
	const double value = static_cast<double>(rgb.size())*xpos/this->w();
	double integer=0.;
	const double fraction = std::modf(value, &integer);
	int pos = 5 - static_cast<int>(integer);

	for (auto& a : xp) { a += fraction / rgb.size(); }

/*std::cout
<< "x_offset_=" << this->x_offset_
<< " xpos=" << xpos
<< " value=" << value
<< " franction=" << fraction
<< " integer=" << integer
<< " pos=" << pos
<< "\n";*/

	const double* v0 = rgb.at(pos).data(); ++pos; if (5<pos) {pos=0;}
	const double* v1 = rgb.at(pos).data(); ++pos; if (5<pos) {pos=0;}
	const double* v2 = rgb.at(pos).data(); ++pos; if (5<pos) {pos=0;}
	const double* v3 = rgb.at(pos).data(); ++pos; if (5<pos) {pos=0;}
	const double* v4 = rgb.at(pos).data(); ++pos; if (5<pos) {pos=0;}
	const double* v5 = rgb.at(pos).data(); ++pos; if (5<pos) {pos=0;}

	/* 中心軸ガイド表示 */
	glBegin(GL_QUADS);
	glColor3dv(v0);glVertex2d(xp.at(0),1.);glVertex2d(xp.at(0),0.);
	glColor3dv(v1);glVertex2d(xp.at(1),0.);glVertex2d(xp.at(1),1.);
	glEnd();

	glBegin(GL_QUADS);
	glColor3dv(v1);glVertex2d(xp.at(1),1.);glVertex2d(xp.at(1),0.);
	glColor3dv(v2);glVertex2d(xp.at(2),0.);glVertex2d(xp.at(2),1.);
	glEnd();

	glBegin(GL_QUADS);
	glColor3dv(v2);glVertex2d(xp.at(2),1.);glVertex2d(xp.at(2),0.);
	glColor3dv(v3);glVertex2d(xp.at(3),0.);glVertex2d(xp.at(3),1.);
	glEnd();

	glBegin(GL_QUADS);
	glColor3dv(v3);glVertex2d(xp.at(3),1.);glVertex2d(xp.at(3),0.);
	glColor3dv(v4);glVertex2d(xp.at(4),0.);glVertex2d(xp.at(4),1.);
	glEnd();

	glBegin(GL_QUADS);
	glColor3dv(v4);glVertex2d(xp.at(4),1.);glVertex2d(xp.at(4),0.);
	glColor3dv(v5);glVertex2d(xp.at(5),0.);glVertex2d(xp.at(5),1.);
	glEnd();

	glBegin(GL_QUADS);
	glColor3dv(v5);glVertex2d(xp.at(5),1.);glVertex2d(xp.at(5),0.);
	glColor3dv(v0);glVertex2d(xp.at(6),0.);glVertex2d(xp.at(6),1.);
	glEnd();

	glBegin(GL_QUADS);
	glColor3dv(v0);glVertex2d(xp.at(6),1.);glVertex2d(xp.at(6),0.);
	glColor3dv(v1);glVertex2d(xp.at(7),0.);glVertex2d(xp.at(7),1.);
	glEnd();

	/* display current position */
	glBegin(GL_LINES);
	glColor3d(1.,1.,1.);glVertex2d(0.5,0.);glVertex2d(0.5,0.05);
	glEnd();
	glBegin(GL_LINES);
	glColor3d(0.,0.,0.);glVertex2d(0.5,0.05);glVertex2d(0.5,0.95);
	glEnd();
	glBegin(GL_LINES);
	glColor3d(1.,1.,1.);glVertex2d(0.5,0.95);glVertex2d(0.5,1.0);
	glEnd();

	/* 現在位置を最大/最小値にセットする */
	/*{
	auto& aa = this->hue_ranges_.at(this->hue_range_number_);
	if (this->hue_range_is_max_) {
		aa.maximum = std::fmod(180.-this->hue_offset_ ,360.);
	} else {
		aa.minimum = std::fmod(180.-this->hue_offset_ ,360.);
	}
	}*/

	/* display each hue range */
	auto sz = this->hue_ranges_.size();
	auto he = 1./(sz+1.);
	for (unsigned ii=0 ;ii<sz ;++ii) {
		/* 各パラメータ */
		auto& aa = this->hue_ranges_.at(ii);

		/* 色 */
		if (ii == this->hue_range_number_) {
			glColor3d(1.  ,1.  ,1. );
		} else if (aa.enable_sw) {
			glColor3d(0.7 ,0.7 ,0.7);
		} else {glColor3d(0.3 ,0.3 ,0.3); }

		/* 上下位置 */
		double yy = (sz-ii) / (sz+1.);
		double y1 = yy - he/2.;
		double y2 = yy + he/2.;

		/* 左右位置 */
		//double x1=std::fmod(aa.minimum+this->hue_offset_ ,360.)/360;
		//double x2=std::fmod(aa.maximum+this->hue_offset_ ,360.)/360;
		double x1=cyclic_hue_degree_(aa.minimum+this->hue_offset_)
								/360;
		double x2=cyclic_hue_degree_(aa.maximum+this->hue_offset_)
								/360;

		/* 表示 */
		if (x1 <= x2) {
			glBegin(GL_LINES);
			glVertex2d(x1,yy);glVertex2d(x2,yy);
			glVertex2d(x1,y1);glVertex2d(x1,y2);
			glVertex2d(x2,y1);glVertex2d(x2,y2);
			glEnd();
		}
		else {
			glBegin(GL_LINES);
			glVertex2d(x1,yy);glVertex2d(1.,yy);
			glVertex2d(0.,yy);glVertex2d(x2,yy);
			glVertex2d(x1,y1);glVertex2d(x1,y2);
			glVertex2d(x2,y1);glVertex2d(x2,y2);
			glEnd();
		}
	}
}

double fl_gl_cyclic_color_wheel::xpos_from_hue_(const double hue)
{
	return this->w() * hue / 360.;
}
double fl_gl_cyclic_color_wheel::hue_from_xpos_(const double xpos)
{
	return 360. * xpos / this->w();
}

void fl_gl_cyclic_color_wheel::draw()
{
	static bool first_of_all_sw_ = true;
	if (!valid()) {
		/* FLTKがこのウィンドウの新しいコンテキストを作成するとき、
		またはウィンドウのサイズが変更されたときここに来る */

		if (first_of_all_sw_) {
			/* ここはアプリ立上げ後一回のみ実行する場所 */
			/* ウインドウのOpenGLが初期化された */
			first_of_all_sw_ = false;

			/* カラーバッファの初期値設定 背景(画面クリア)色 */
			glClearColor( 0.f ,0.f ,0.f ,1.f );
		}

		/* 表示範囲の再設定 */
		glViewport( 0 ,0 ,this->w(), this->h());

		/* 射影行列の設定 */
		glMatrixMode( GL_PROJECTION );
		glLoadIdentity();
		gluOrtho2D( 0. ,1. ,0. ,1. );

		/* モデルビュー行列の設定 */
		glMatrixMode( GL_MODELVIEW );
		glLoadIdentity();
	}

	/* バッファの初期化 */
	glClear( GL_COLOR_BUFFER_BIT );

	/* 画面のリサイズのときは前の色相から新しい位置を再設定 */
	this->x_offset_ = this->xpos_from_hue_(this->hue_offset_);

	/* 描画	 */
	if (!first_of_all_sw_) {
		this->draw_object_();
	}
}

void fl_gl_cyclic_color_wheel::handle_push_( const int mx ,const int my )
{
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;
}

double fl_gl_cyclic_color_wheel::limit_new_hue_( double new_hue )
{
	/* 位置(h1,h2,h3) */
	auto& aa = this->hue_ranges_.at(this->hue_range_number_);
	auto& min_or_max= ((this->hue_range_is_max_)?aa.minimum:aa.maximum);
	      double h1 = this->hue_offset_ + min_or_max;
	const double h2 = 180.;
	      double h3 = new_hue           + min_or_max;
	while (360. < h1) {
		h1 -= 360.;
		h3 -= 360.;
	}

	/* 新位置と旧位置の間に中間(180度の)位置をはさむ */
	if ((h1 <= h2 && h2 <= h3)
	||  (h3 <= h2 && h2 <= h1)) {
		new_hue = 180. - min_or_max;

		/* わずかに元来た場所に寄せてどちらから来たかわかるように */
		new_hue += ((h1 < h2) || (h2 < h3)) ?-0.000001 :0.000001;
	}

	/* cyclic about 360 */
	new_hue = cyclic_hue_degree_( new_hue );

	return new_hue;
}
double fl_gl_cyclic_color_wheel::limit_new_xpos_( double new_xpos )
{
	auto hh = this->hue_from_xpos_( new_xpos );
	//hh = floor( hh ); /* 整数値化-->動き悪くなる-->ダメ */
	auto h2 = this->limit_new_hue_( hh );
	auto xp = this->xpos_from_hue_( h2 );
	return xp;
}

void fl_gl_cyclic_color_wheel::handle_updownleftright_( const int mx ,const int my )
{
	auto xpos = this->limit_new_xpos_(
		this->x_offset_ + (mx - this->mouse_x_when_push_)
	);

	/* セット */
	this->x_offset_ = xpos;
	this->hue_offset_ = this->hue_from_xpos_( xpos );
//std::cout << std::fixed << std::setprecision(7) << "x_o=" << this->x_offset_ << " hue_o=" << this->hue_offset_ << " h=" << this->get_hue() << std::endl;

	/* 現在地を記憶 */
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	/* 再表示 */
	cl_gts_master.cl_trace_params.cb_hue_min_or_max_change();
	this->set_position_to_min_or_max_();
	this->redraw();
}
/*
if (radbut_set_hue_min->value() == 1) {
valinp_set_hue_min->value( o->value() );
} else {
valinp_set_hue_max->value( o->value() );
}
cl_gts_master.cl_trace_params.cb_hue_min_or_max_change();
*/

void fl_gl_cyclic_color_wheel::handle_keyboard_( const int key , const char* text )
{
	if (text != nullptr) {
	 switch (key) {
	 case FL_Left:
		{
		auto hue = this->limit_new_hue_(ceil(this->hue_offset_-1.));
		this->hue_offset_ = hue;
		this->x_offset_ = this->xpos_from_hue_( hue );
//std::cout << std::fixed << std::setprecision(7) << "x_o=" << this->x_offset_ << " hue_o=" << this->hue_offset_ << " h=" << this->get_hue() << std::endl;
		}
		cl_gts_master.cl_trace_params.cb_hue_min_or_max_change();
		this->set_position_to_min_or_max_();
		this->redraw();
		break;
	 case FL_Right:
		{
		auto hue= this->limit_new_hue_(floor(this->hue_offset_+1.));
		this->hue_offset_ = hue;
		this->x_offset_ = this->xpos_from_hue_( hue );
//std::cout << std::fixed << std::setprecision(7) << "x_o=" << this->x_offset_ << " hue_o=" << this->hue_offset_ << " h=" << this->get_hue() << std::endl;
		}
		cl_gts_master.cl_trace_params.cb_hue_min_or_max_change();
		this->set_position_to_min_or_max_();
		this->redraw();
		break;
	 }
	}
}
int fl_gl_cyclic_color_wheel::handle(int event)
{
	switch(event) {
	case FL_PUSH:	// mouse down event
		this->handle_push_( Fl::event_x() , Fl::event_y() );
		return 1;
	case FL_DRAG:	// mouse moved while down event
		if (Fl::event_state() & FL_SHIFT) {
		}
		else if (Fl::event_state() & FL_CTRL) {
		}
		else {
		this->handle_updownleftright_(Fl::event_x(),Fl::event_y());
		}
		return 1;
	case FL_MOVE:	// mouse moved
		return 1;
	case FL_RELEASE:	// mouse up event
		return 1;
	case FL_MOUSEWHEEL:
//std::cout << "wheel " << "dx=" <<  Fl::event_dx() << "dy=" <<  Fl::event_dy() << std::endl;
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
#if defined DEBUG_FL_GL_CYCLIC_COLOR_WHEEL
int main(void) {
	Fl_Window win(200, 50, "OpenGL");
	fl_gl_cyclic_color_wheel ogl( 0, 10, 200, 30 );
	win.end();
	win.resizable(ogl);
	win.size_range(200,50,1000,100);
	win.show();
	ogl.set_hue_range_pos(4,true);
	return Fl::run();
}
#endif /* !DEBUG_FL_GL_CYCLIC_COLOR_WHEEL */
/*
:401,402 w! make.bat
cl /W3 /MD /EHa /O2 /wd4819 /DWIN32 /DDEBUG_FL_GL_CYCLIC_COLOR_WHEEL /I..\..\..\sources\libcpp71iip_color_trace_hab /I..\..\..\thirdparty\fltk\fltk-1.3.4-1 ..\..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltk-1.3.4-1-vc2013-32.lib ..\..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltkgl-1.3.4-1-vc2013-32.lib glu32.lib advapi32.lib shlwapi.lib opengl32.lib comctl32.lib wsock32.lib user32.lib gdi32.lib shell32.lib ole32.lib comdlg32.lib fl_gl_cyclic_color_wheel.cpp /Fea
del fl_gl_cyclic_color_wheel.obj
*/
