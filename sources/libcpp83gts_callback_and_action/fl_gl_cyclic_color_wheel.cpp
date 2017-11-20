#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <FL/glu.h>	/* gluOrtho2D(-) */
#include "fl_gl_cyclic_color_wheel.h"
#include "gts_gui.h"
#include "gts_master.h"

fl_gl_cyclic_color_wheel::fl_gl_cyclic_color_wheel(int x ,int y ,int w ,int h ,const char*l)
	:Fl_Gl_Window(x,y,w,h,l)
	,mouse_x_when_push_(0)
	,mouse_y_when_push_(0)
	,x_offset_(0.)
	,hue_offset_(0.)
	,guide_widget_sets_(
	5,{ nullptr ,nullptr ,nullptr ,nullptr }
	)
	,hue_range_number_(0)
	,hue_range_is_max_(false)
{
}

/* cb_trace_params使用(GUIで各値が変更したとき設定する) */
void fl_gl_cyclic_color_wheel::init_widget_set(
	const int number
	,Fl_Value_Input* valinp_hue_min
	,Fl_Value_Input* valinp_hue_max
	,Fl_Check_Button* chebut_enable_sw
	,Fl_Check_Button* chebut_rotate360_sw
)
{
	assert(	(0 <= number)
	&& (number < static_cast<int>(this->guide_widget_sets_.size())) );

	/* 値を記憶 */
	auto& aa = this->guide_widget_sets_.at(number);
	aa.valinp_hue_min = valinp_hue_min;
	aa.valinp_hue_max = valinp_hue_max;
	aa.chebut_enable_sw = chebut_enable_sw;
	aa.chebut_rotate360_sw = chebut_rotate360_sw;
}

namespace {
double cyclic_hue_degree_( double hue )
{
	while (hue < 0.) { hue += 360.; }
	while (360. <= hue) { hue -= 360.; }
	return hue;
}
}
void fl_gl_cyclic_color_wheel::init_number_and_is_max( const int number ,const bool is_max)
{
	assert(	(0 <= number)
	&& (number < static_cast<int>(this->guide_widget_sets_.size())) );

	/* GUI値からhue現在位置をセット */
	auto& aa = this->guide_widget_sets_.at( number );
	auto hh = (is_max	?aa.valinp_hue_max->value()
				:aa.valinp_hue_min->value() );
	this->hue_offset_ = cyclic_hue_degree_( 180. - hh );
	this->x_offset_ = this->xpos_from_hue_(this->hue_offset_);

	/* パラメータ位置を記憶 */
	this->hue_range_number_ = number;
	this->hue_range_is_max_ = is_max;
}

namespace {
double calc_between_min_max_( const double mini ,const double maxi ,const bool min_sw ,const double ratio )
{
	/* mini...maxiの間の長さ */
	double len = 0.;
	if (mini < maxi) { len = maxi - mini; }
	else             { len = maxi + (360. - mini); }

	/* 色相の値 360以上の値もあり */
	double hh = 0.;
	if (min_sw) { hh = len *       ratio  + mini; }
	else        { hh = len * (1. - ratio) + mini; }
	return hh;
}
}
void fl_gl_cyclic_color_wheel::set_min_or_max(const bool is_max )
{
#if 0
	/* 動作しない--> redraw() しない --> ひとまず保留*/
	const int sz = 10;
	for (int ii=1 ;ii<sz ;++ii) {
		Sleep(100);
		auto ratio = static_cast<double>(ii)/sz;

		auto& aa = this->guide_widget_sets_.at(
						this->hue_range_number_);
		auto mini = aa.valinp_hue_min->value();
		auto maxi = aa.valinp_hue_max->value();
		bool min_sw = (cl_gts_gui.radbut_hue_min_sw->value() != 0);
		auto hh = calc_between_min_max_( mini ,maxi ,min_sw ,ratio);
		/* 0...360の範囲で設定 */
		this->hue_offset_ = cyclic_hue_degree_( 180. - hh );
		/* 現在のwidgetの横幅内の位置 */
		this->x_offset_ = this->xpos_from_hue_(this->hue_offset_);

		this->redraw();
	}
#endif
	this->init_number_and_is_max( this->hue_range_number_ ,is_max );
}

//--------------------

/* 現在位置を最大/最小値にセットする */
void fl_gl_cyclic_color_wheel::set_min_or_max_to_gui_(const bool rot360_sw)
{
	auto& aa = this->guide_widget_sets_.at(this->hue_range_number_);
	if ( cl_gts_gui.radbut_hue_min_sw->value() != 0 ) {
		aa.valinp_hue_min->value(
			cyclic_hue_degree_( 180. - this->hue_offset_ )
		);
	} else {
		aa.valinp_hue_max->value(
			cyclic_hue_degree_( 180. - this->hue_offset_ )
		);;
	}

	/* 0回転、あるいは1回転 */
	aa.chebut_rotate360_sw->value( rot360_sw ? 1 :0 );
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

	/* display each hue range */
	auto sz = this->guide_widget_sets_.size();
	auto he = 1./(sz+1.);
	for (unsigned ii=0 ;ii<sz ;++ii) {
		/* 各パラメータ */
		auto& aa = this->guide_widget_sets_.at(ii);

		/* 色 */
		if (ii == this->hue_range_number_) {
			glColor3d(1.  ,1.  ,1. );
		} else if (aa.chebut_enable_sw->value() != 0) {
			glColor3d(0.7 ,0.7 ,0.7);
		} else {glColor3d(0.3 ,0.3 ,0.3); }

		/* 上下位置 */
		double yy = (sz-ii) / (sz+1.);
		double y1 = yy - he/2.;
		double y2 = yy + he/2.;

		/* 左右位置 */
		double x1 = cyclic_hue_degree_(
			aa.valinp_hue_min->value()+this->hue_offset_) /360.;
		double x2 = cyclic_hue_degree_(
			aa.valinp_hue_max->value()+this->hue_offset_) /360.;
		bool rotate360_sw = (aa.chebut_rotate360_sw->value() != 0);

		/* 表示 */
		if (x1 < x2 || ((x1 == x2) && rotate360_sw==false)) {
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

namespace {
void clamp_cyclic_color_wheel_(
const bool change_min_sw
,const double hmin
,const double hmax
,const double hold
,const double hnew
,double& huedeg
,bool& rotate360_sw
)
{
	rotate360_sw = false;	/* 0回転 --> これがdefault */

	if (change_min_sw) {/* min値を変更中 */
		if ((hold < hmax) && (hmax <= hnew)) {
		/* max値と同じか小さい値から、maxより大きい値に移動したら */
			huedeg = hmax;
			rotate360_sw = false;	/* 0回転 */
		} else
		if ((hmax < hold) && (hnew <= hmax)) {
		/* max値と同じか大さい値から、maxより小さい値に移動したら */
			huedeg = hmax;
			rotate360_sw = true;	/* 1回転 */
		} else
		if (hold == hmax) { /* 前回hmaxと交差した */
			if (rotate360_sw==false && (hnew < hmax)) {
				huedeg = hnew; /* 0回転の状態から戻る */
			} else
			if (rotate360_sw==true && (hmax < hnew)) {
				huedeg = hnew; /* 360回転の状態から戻る */
			} else {
				huedeg = hmax;
			}
		} else {
			huedeg = hnew;
		}
	}
	else {	/* max値を変更中 */
		if ((hold < hmin) && (hmin <= hnew)) {
		/* min値と同じか小さい値から、minより大きい値に移動したら */
			huedeg = hmin;
			rotate360_sw = true;	/* 1回転 */
		} else
		if ((hmin < hold) && (hnew <= hmin)) {
		/* min値と同じか大さい値から、minより小さい値に移動したら */
			huedeg = hmin;
			rotate360_sw = false;	/* 0回転 */
		} else
		if (hold == hmin) { /* 前回hminと交差した */
			if (rotate360_sw==false && (hmin < hnew)) {
				huedeg = hnew; /* 0回転の状態から戻る */
			} else
			if (rotate360_sw==true && (hnew < hmin)) {
				huedeg = hnew; /* 360回転の状態から戻る */
			} else
			{
				huedeg = hmax;
			}
		} else {
			huedeg = hnew;
		}
	}
}
}

double fl_gl_cyclic_color_wheel::limit_new_hue_( double hue_o_new ,bool& rotate360_sw )
{
	auto& aa = this->guide_widget_sets_.at(this->hue_range_number_);
	auto hmin = aa.valinp_hue_min->value();
	auto hmax = aa.valinp_hue_max->value();
	auto hold = 180. - this->hue_offset_; /* 0...360 --> 180...-180 */
	auto hnew = 180. - hue_o_new;
	while (hold < 0.) {	/* 同じサイクルで0-360範囲にする */
		hold = hold + 360.;
		hnew = hnew + 360.;
	}

	double huedeg=0.;
	clamp_cyclic_color_wheel_(
		cl_gts_gui.radbut_hue_min_sw->value()!=0
		,hmin
		,hmax
		,hold
		,hnew
		,huedeg
		,rotate360_sw
	);

	return huedeg;
}

void fl_gl_cyclic_color_wheel::handle_updownleftright_( const int mx ,const int my )
{
	/* マウスの移動で変化した位置からhue offset値を得る */
	auto hue_o = this->hue_from_xpos_( 
		this->x_offset_ + (mx - this->mouse_x_when_push_)
	);

	/* 現在地を記憶 */
	this->mouse_x_when_push_ = mx;
	this->mouse_y_when_push_ = my;

	/* hue degree値を移動限界でclampし、あるいは0-360度範囲にする */
	auto& aa = this->guide_widget_sets_.at(this->hue_range_number_);
	bool rotate360_sw = (aa.chebut_rotate360_sw->value() != 0);
	auto huedeg = this->limit_new_hue_( hue_o ,rotate360_sw );

	/* セット */
	this->hue_offset_ = rint( cyclic_hue_degree_( 180. - huedeg ) );
	this->x_offset_ = this->xpos_from_hue_( this->hue_offset_ );

	/* 再表示 */
	this->set_min_or_max_to_gui_( rotate360_sw );
	this->redraw();
	cl_gts_gui.image_view->redraw();
}

void fl_gl_cyclic_color_wheel::handle_keyboard_( const int key , const char* text )
{
	if (text != nullptr) {
	 switch (key) {
	 case FL_Left:
		{
	auto& aa = this->guide_widget_sets_.at(this->hue_range_number_);
	bool rotate360_sw = (aa.chebut_rotate360_sw->value() != 0);
	auto huedeg = this->limit_new_hue_( ceil(this->hue_offset_-1.)
							,rotate360_sw );
	/* セット */
	this->hue_offset_ = cyclic_hue_degree_( 180. - huedeg );
	this->x_offset_ = this->xpos_from_hue_( this->hue_offset_ );

	/* 再表示 */
	this->set_min_or_max_to_gui_( rotate360_sw );
	this->redraw();
	cl_gts_gui.image_view->redraw();
		}
		break;
	 case FL_Right:
		{
	auto& aa = this->guide_widget_sets_.at(this->hue_range_number_);
	bool rotate360_sw = (aa.chebut_rotate360_sw->value() != 0);
	auto huedeg = this->limit_new_hue_( floor(this->hue_offset_+1.)
							,rotate360_sw );
	/* セット */
	this->hue_offset_ = cyclic_hue_degree_( 180. - huedeg );
	this->x_offset_ = this->xpos_from_hue_( huedeg );
	/* 再表示 */
	this->set_min_or_max_to_gui_( rotate360_sw );
	this->redraw();
	cl_gts_gui.image_view->redraw();
		}
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
	ogl.init_number_and_is_max(4,true);
	return Fl::run();
}
#endif /* !DEBUG_FL_GL_CYCLIC_COLOR_WHEEL */
/*
:401,402 w! make.bat
cl /W3 /MD /EHa /O2 /wd4819 /DWIN32 /DDEBUG_FL_GL_CYCLIC_COLOR_WHEEL /I..\..\..\sources\libcpp71iip_color_trace_hab /I..\..\..\thirdparty\fltk\fltk-1.3.4-1 ..\..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltk-1.3.4-1-vc2013-32.lib ..\..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltkgl-1.3.4-1-vc2013-32.lib glu32.lib advapi32.lib shlwapi.lib opengl32.lib comctl32.lib wsock32.lib user32.lib gdi32.lib shell32.lib ole32.lib comdlg32.lib fl_gl_cyclic_color_wheel.cpp /Fea
del fl_gl_cyclic_color_wheel.obj
*/
