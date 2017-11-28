#include <cassert>
#include <iomanip>
#include <iostream>
#include "calc_hsv_rgb.h"
#include "cb_trace_params.h"
#include "ids_path_level_from_files.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {
void set_target_rgb_( const int number , uchar r , uchar g , uchar b )
{
	Fl::set_color( static_cast<Fl_Color>( number + 16 ) ,r ,g ,b );
}
void get_target_rgb_( const int number , uchar& r , uchar& g , uchar& b )
{
	Fl::get_color( static_cast<Fl_Color>( number + 16 ) ,r ,g ,b );
}
void set_target_color_( const int number , Fl_Widget* button )
{
	button->color( static_cast<Fl_Color>( number + 16 ) );
}
} // namespace

//---------------

void cb_trace_params::init_color(void)
{
	std::vector<cb_trace_params::widget_set>& vwset(this->widget_sets);
	for (int ii = 0 ; ii < static_cast<int>( vwset.size() ) ; ++ii) {
		cb_trace_params::widget_set& wset( vwset.at( ii ) );

		/* カラーテーブル番号を目的色ボタンの色に設定 */
		set_target_color_( ii ,wset.button_target_rgb );
	}
}

namespace {
void gui_hsv_to_rgb_( void ) { 
	double	r=0. ,g=0. ,b=0.;
	calc::hsv_to_rgb(
		calc::clamp_cyclic360(
		cl_gts_gui.valinp_set_color_hue->value() )
		,cl_gts_gui.valinp_set_color_sat->value()/
		 cl_gts_gui.valinp_set_color_sat->maximum()
		,cl_gts_gui.valinp_set_color_val->value()/
		 cl_gts_gui.valinp_set_color_val->maximum()
		,r,g,b
	);
	/*r *= (cl_gts_gui.valinp_set_color_red->maximum()+.999999);
	g *= (cl_gts_gui.valinp_set_color_gre->maximum()+.999999);
	b *= (cl_gts_gui.valinp_set_color_blu->maximum()+.999999);
	r = floor(r);
	g = floor(g);
	b = floor(b);*/
	r *= cl_gts_gui.valinp_set_color_red->maximum();
	g *= cl_gts_gui.valinp_set_color_gre->maximum();
	b *= cl_gts_gui.valinp_set_color_blu->maximum();
	r = rint(r);
	g = rint(g);
	b = rint(b);
	cl_gts_gui.valinp_set_color_red->value(r);
	cl_gts_gui.valinp_set_color_gre->value(g);
	cl_gts_gui.valinp_set_color_blu->value(b);
	static_cast<Fl_Valuator *>(
	cl_gts_gui.scrbar_set_color_red)->value(r);
	static_cast<Fl_Valuator *>(
	cl_gts_gui.scrbar_set_color_gre)->value(g);
	static_cast<Fl_Valuator *>(
	cl_gts_gui.scrbar_set_color_blu)->value(b);
}
void gui_rgb_to_hsv_( void ) { 
	double	h=0. ,s=0. ,v=0.;
	calc::rgb_to_hsv(
		 cl_gts_gui.valinp_set_color_red->value()/
		 cl_gts_gui.valinp_set_color_red->maximum()
		,cl_gts_gui.valinp_set_color_gre->value()/
		 cl_gts_gui.valinp_set_color_gre->maximum()
		,cl_gts_gui.valinp_set_color_blu->value()/
		 cl_gts_gui.valinp_set_color_blu->maximum()
		,h,s,v
	);
	s *= cl_gts_gui.valinp_set_color_sat->maximum();
	v *= cl_gts_gui.valinp_set_color_val->maximum();
	h = rint( h );
	s = rint( s );
	v = rint( v );
	cl_gts_gui.valinp_set_color_hue->value(h);
	cl_gts_gui.valinp_set_color_sat->value(s);
	cl_gts_gui.valinp_set_color_val->value(v);
	static_cast<Fl_Valuator *>(
	cl_gts_gui.scrbar_set_color_hue)->value(h);
	static_cast<Fl_Valuator *>(
	cl_gts_gui.scrbar_set_color_sat)->value(s);
	static_cast<Fl_Valuator *>(
	cl_gts_gui.scrbar_set_color_val)->value(v);
}
}

void cb_trace_params::cb_target_rgb_color_open_editor(
	Fl_Double_Window* flwin
	,Fl_Button* flbut
	,const int number
)
{
	assert( number < static_cast<int>(this->widget_sets.size()) );

	/* rgb値を記憶 */
	get_target_rgb_( number ,this->r_ ,this->g_ ,this->b_ );

	/* Cancel(now) rgb値を設定 */
	set_target_rgb_(
		static_cast<int>(this->widget_sets.size())+0
		,this->r_ ,this->g_ ,this->b_
	);
	/* OK(new) rgb値を設定 */
	set_target_color_( number , cl_gts_gui.box_set_color_ok );

	/* 色テーブル番号を記憶 */
	this->number_ = number;

	/* Color Editorにrgb初期値を設定 */
	cl_gts_gui.valinp_set_color_red->value(this->r_);
	cl_gts_gui.scrbar_set_color_red->value(this->r_);
	cl_gts_gui.valinp_set_color_gre->value(this->g_);
	cl_gts_gui.scrbar_set_color_gre->value(this->g_);
	cl_gts_gui.valinp_set_color_blu->value(this->b_);
	cl_gts_gui.scrbar_set_color_blu->value(this->b_);

	/* rgb初期値からhsv値を設定 */
	gui_rgb_to_hsv_();

	/* window開く */
	cl_gts_gui.window_set_color->position(
		 flwin->x() + flbut->x() + 10
		,flwin->y() + flbut->y() - 220
	);
	cl_gts_gui.window_set_color->show();
}

void cb_trace_params::cb_target_rgb_color_change(const bool change_hsv_sw)
{
	if (change_hsv_sw) { gui_hsv_to_rgb_(); }
	else		   { gui_rgb_to_hsv_(); }

	/* Color Editorのrgb値をGUIカラーテーブルにセット */
	set_target_rgb_( this->number_
	,static_cast<uchar>(cl_gts_gui.valinp_set_color_red->value())
	,static_cast<uchar>(cl_gts_gui.valinp_set_color_gre->value())
	,static_cast<uchar>(cl_gts_gui.valinp_set_color_blu->value())
	);

	/* ボタンのターゲット色を再表示 */
	std::vector<cb_trace_params::widget_set>& vwset(this->widget_sets);
	cb_trace_params::widget_set& wset( vwset.at(this->number_) );
	wset.button_target_rgb->redraw();

	cl_gts_gui.box_set_color_ok->redraw();

	/* Image(& hsv viewもredrawしてる)の再表示 */
	cl_gts_gui.image_view->redraw();
}

void cb_trace_params::cb_target_rgb_color_cancel(void)
{
	/* rgb値を戻す */
	set_target_rgb_( this->number_ ,this->r_ ,this->g_ ,this->b_ );

	/* ボタンのターゲット色を再表示 */
	std::vector<cb_trace_params::widget_set>& vwset(this->widget_sets);
	cb_trace_params::widget_set& wset( vwset.at(this->number_) );
	wset.button_target_rgb->redraw();

	/* OpenGLの表示をredraw */
	cl_gts_gui.image_view->redraw();
}

//---------------

void cb_trace_params::cb_hue_min_or_max_open_editor(
	Fl_Double_Window* flwin
	,Fl_Button* flbut
	,const int number
)
{
	assert( number < static_cast<int>(this->widget_sets.size()) );

	/* 各min,maxを補助表示するため色線のみ初期化設定する */
	std::vector<cb_trace_params::widget_set>& vwset(this->widget_sets);
	int crnt_num = number;
	for (int ii=0,jj=0 ;ii<static_cast<int>(vwset.size()) ;++ii) {
		auto& ws = this->widget_sets.at(ii);
		if ((0. <= ws.valinp_hue_min->value())
		&&  (0. <= ws.valinp_hue_max->value())) {
			/* 色線のみセットする */
			cl_gts_gui.cyclic_color_wheel->init_widget_set(
				jj++
				,ws.valinp_hue_min
				,ws.valinp_hue_max
				,ws.chebut_enable_sw
				,ws.chebut_rotate360_sw
			);
		} else {
			/* メニュー上の現在位置より先に黒線があるとき */
			/* 黒線の数の分... */
			if (ii < number) {
				--crnt_num; /* 位置が減少方向に減る */
			}
		}
	}

	/* color wheel におけるカレント位置をセット */
	cl_gts_gui.cyclic_color_wheel->init_number_and_is_max(
		crnt_num
		,(cl_gts_gui.radbut_hue_min_sw->value()!=0) ?false :true
	);

	/* Cancelのとき戻す値を記憶 */
	cb_trace_params::widget_set& wset( vwset.at( number ) );
	this->hmin_         = wset.valinp_hue_min->value();
	this->hmax_         = wset.valinp_hue_max->value();
	this->rotate360_sw_ = wset.chebut_rotate360_sw->value();

	/* 色テーブル番号を記憶 */
	this->number_ = number;

	/* window開く */
	cl_gts_gui.window_set_hue_min_or_max->position(
		 flwin->x() + flbut->x() + 10
		,flwin->y() + flbut->y() -
			(cl_gts_gui.window_set_hue_min_or_max->h() + 10)
	);
	cl_gts_gui.window_set_hue_min_or_max->show();
}

void cb_trace_params::cb_hue_min_or_max_cancel(void)
{
	std::vector<cb_trace_params::widget_set>& vwset(this->widget_sets);
	cb_trace_params::widget_set& wset( vwset.at(this->number_) );

	/* 元の値をTrace Paramsウインドウに戻す */
	wset.valinp_hue_min->value( this->hmin_ );
	wset.valinp_hue_max->value( this->hmax_ );
	wset.chebut_rotate360_sw->value( this->rotate360_sw_ ?1 :0 );

	/* OpenGLの表示をredraw */
	cl_gts_gui.image_view->redraw();
}

//---------------

void cb_trace_params::get_target_rgb(
	const int number
	, unsigned char& r , unsigned char& g , unsigned char& b
)
{
	get_target_rgb_( number ,r ,g ,b );
}

void cb_trace_params::set_target_rgb(
	const int number
	, unsigned char r , unsigned char g , unsigned char b
)
{
	set_target_rgb_( number ,r ,g ,b );
}

//---------------

void cb_trace_params::init_widget_set_(void) {
	this->widget_sets = {
	{cl_gts_gui.chebut_trace_0_enable_sw
	,cl_gts_gui.group_trace_0
	,cl_gts_gui.button_trace_0_target_rgb
	,cl_gts_gui.valinp_trace_0_thickness
	,cl_gts_gui.scrbar_trace_0_thickness
	,cl_gts_gui.valinp_trace_0_hue_min
	,cl_gts_gui.valinp_trace_0_hue_max
	,cl_gts_gui.button_trace_0_hue_min_max
	,cl_gts_gui.valinp_trace_0_slope_deg
	,cl_gts_gui.valinp_trace_0_intercept
	,cl_gts_gui.chebut_trace_0_display_sw
	,cl_gts_gui.chebut_trace_0_rotate360_sw
	}
	,{cl_gts_gui.chebut_trace_1_enable_sw
	,cl_gts_gui.group_trace_1
	,cl_gts_gui.button_trace_1_target_rgb
	,cl_gts_gui.valinp_trace_1_thickness
	,cl_gts_gui.scrbar_trace_1_thickness
	,cl_gts_gui.valinp_trace_1_hue_min
	,cl_gts_gui.valinp_trace_1_hue_max
	,cl_gts_gui.button_trace_1_hue_min_max
	,cl_gts_gui.valinp_trace_1_slope_deg
	,cl_gts_gui.valinp_trace_1_intercept
	,cl_gts_gui.chebut_trace_1_display_sw
	,cl_gts_gui.chebut_trace_1_rotate360_sw
	}
	,{cl_gts_gui.chebut_trace_2_enable_sw
	,cl_gts_gui.group_trace_2
	,cl_gts_gui.button_trace_2_target_rgb
	,cl_gts_gui.valinp_trace_2_thickness
	,cl_gts_gui.scrbar_trace_2_thickness
	,cl_gts_gui.valinp_trace_2_hue_min
	,cl_gts_gui.valinp_trace_2_hue_max
	,cl_gts_gui.button_trace_2_hue_min_max
	,cl_gts_gui.valinp_trace_2_slope_deg
	,cl_gts_gui.valinp_trace_2_intercept
	,cl_gts_gui.chebut_trace_2_display_sw
	,cl_gts_gui.chebut_trace_2_rotate360_sw
	}
	,{cl_gts_gui.chebut_trace_3_enable_sw
	,cl_gts_gui.group_trace_3
	,cl_gts_gui.button_trace_3_target_rgb
	,cl_gts_gui.valinp_trace_3_thickness
	,cl_gts_gui.scrbar_trace_3_thickness
	,cl_gts_gui.valinp_trace_3_hue_min
	,cl_gts_gui.valinp_trace_3_hue_max
	,cl_gts_gui.button_trace_3_hue_min_max
	,cl_gts_gui.valinp_trace_3_slope_deg
	,cl_gts_gui.valinp_trace_3_intercept
	,cl_gts_gui.chebut_trace_3_display_sw
	,cl_gts_gui.chebut_trace_3_rotate360_sw
	}
	,{cl_gts_gui.chebut_trace_4_enable_sw
	,cl_gts_gui.group_trace_4
	,cl_gts_gui.button_trace_4_target_rgb
	,cl_gts_gui.valinp_trace_4_thickness
	,cl_gts_gui.scrbar_trace_4_thickness
	,cl_gts_gui.valinp_trace_4_hue_min
	,cl_gts_gui.valinp_trace_4_hue_max
	,cl_gts_gui.button_trace_4_hue_min_max
	,cl_gts_gui.valinp_trace_4_slope_deg
	,cl_gts_gui.valinp_trace_4_intercept
	,cl_gts_gui.chebut_trace_4_display_sw
	,cl_gts_gui.chebut_trace_4_rotate360_sw
	}
	,{cl_gts_gui.chebut_trace_5_enable_sw
	,cl_gts_gui.group_trace_5
	,cl_gts_gui.button_trace_5_target_rgb
	,cl_gts_gui.valinp_trace_5_thickness
	,cl_gts_gui.scrbar_trace_5_thickness
	,cl_gts_gui.valinp_trace_5_hue_min
	,cl_gts_gui.valinp_trace_5_hue_max
	,cl_gts_gui.button_trace_5_hue_min_max
	,cl_gts_gui.valinp_trace_5_slope_deg
	,cl_gts_gui.valinp_trace_5_intercept
	,cl_gts_gui.chebut_trace_5_display_sw
	,cl_gts_gui.chebut_trace_5_rotate360_sw
	}
	};
}

//---------------

void cb_trace_params::set_params_for_speedup(void)
{
	assert( this->widget_sets.size() == this->param_sets_.size() );

	for (unsigned ii = 0 ; ii < this->widget_sets.size() ; ++ii) {
		auto& wset = this->widget_sets.at(ii);
		auto& vset = this->param_sets_.at(ii);

		vset.enable_sw = (wset.chebut_enable_sw->value()==1
				?true:false);

		uchar r=0,g=0,b=0;
		this->get_target_rgb( ii,r,g,b );
		const double mx = (std::numeric_limits<uchar>::max)();

		vset.target_r = static_cast<double>(r) / mx;
		vset.target_g = static_cast<double>(g) / mx;
		vset.target_b = static_cast<double>(b) / mx;
		vset.thickness = wset.valinp_thickness->value()
				/wset.valinp_thickness->maximum();
		vset.hue_min = wset.valinp_hue_min->value();
		vset.hue_max = wset.valinp_hue_max->value();

		vset.slope_line_len =
			calc::line_len_from_rad( calc::rad_from_deg(
					wset.valinp_slope_deg->value()
			));

		vset.intercept = 1. -	(wset.valinp_intercept->value()
					/wset.valinp_intercept->maximum());
		vset.rotate360_sw =
			(wset.chebut_rotate360_sw->value()!=0) ?true :false;
	}
}

void cb_trace_params::cb_swap_widget_set( const unsigned num1 , const unsigned num2 )
{
	assert( num1 < this->widget_sets.size() );
	assert( num2 < this->widget_sets.size() );

	auto& wset1 = this->widget_sets.at(num1);
	auto& wset2 = this->widget_sets.at(num2);

	int tmpint = 0;
	tmpint = wset1.chebut_enable_sw->value();
	wset1.chebut_enable_sw->value( wset2.chebut_enable_sw->value() );
	wset2.chebut_enable_sw->value(tmpint);
	if (	wset1.chebut_enable_sw->value()==1) {
		wset1.group_trace->activate();
	} else {wset1.group_trace->deactivate(); }
	if (	wset2.chebut_enable_sw->value()==1) {
		wset2.group_trace->activate();
	} else {wset2.group_trace->deactivate(); }

	uchar r1=0 ,g1=0 ,b1=0, r2=0 ,g2=0 ,b2=0;
	this->get_target_rgb( num1 ,r1,g1,b1 );
	this->get_target_rgb( num2 ,r2,g2,b2 );
	this->set_target_rgb( num1 ,r2,g2,b2 );
	this->set_target_rgb( num2 ,r1,g1,b1 );
	wset1.button_target_rgb->redraw();
	wset2.button_target_rgb->redraw();

	double tmpdbl = 0.;
	tmpdbl = wset1.valinp_thickness->value();
	wset1.valinp_thickness->value( wset2.valinp_thickness->value() );
	((Fl_Valuator *)wset1.scrbar_thickness)->value( wset2.valinp_thickness->value() );
	wset2.valinp_thickness->value(tmpdbl);
	((Fl_Valuator *)wset2.scrbar_thickness)->value( tmpdbl );

	tmpdbl = wset1.valinp_hue_min->value();
	wset1.valinp_hue_min->value( wset2.valinp_hue_min->value() );
	wset2.valinp_hue_min->value(tmpdbl);
	tmpdbl = wset1.valinp_hue_max->value();
	wset1.valinp_hue_max->value( wset2.valinp_hue_max->value() );
	wset2.valinp_hue_max->value(tmpdbl);

	if ((wset1.valinp_hue_min->value() < 0.)
	||  (wset1.valinp_hue_max->value() < 0.)) {
		wset1.valinp_hue_min->hide();
		wset1.valinp_hue_max->hide();
		wset1.button_hue_min_max->hide();
	} else {
		wset1.valinp_hue_min->show();
		wset1.valinp_hue_max->show();
		wset1.button_hue_min_max->show();
	}

	if ((wset2.valinp_hue_min->value() < 0.)
	||  (wset2.valinp_hue_max->value() < 0.)) {
		wset2.valinp_hue_min->hide();
		wset2.valinp_hue_max->hide();
		wset2.button_hue_min_max->hide();
	} else {
		wset2.valinp_hue_min->show();
		wset2.valinp_hue_max->show();
		wset2.button_hue_min_max->show();
	}

	tmpdbl = wset1.valinp_slope_deg->value();
	wset1.valinp_slope_deg->value( wset2.valinp_slope_deg->value() );
	wset2.valinp_slope_deg->value(tmpdbl);

	tmpdbl = wset1.valinp_intercept->value();
	wset1.valinp_intercept->value( wset2.valinp_intercept->value() );
	wset2.valinp_intercept->value(tmpdbl);

	tmpint = wset1.chebut_display_sw->value();
	wset1.chebut_display_sw->value( wset2.chebut_display_sw->value() );
	wset2.chebut_display_sw->value(tmpint);

	tmpint = wset1.chebut_rotate360_sw->value();
	wset1.chebut_rotate360_sw->value(wset2.chebut_rotate360_sw->value());
	wset2.chebut_rotate360_sw->value(tmpint);
}

int cb_trace_params::cb_get_window_height_active( void )
{
	/* Trace Params Window有効上下サイズ */
	for (unsigned ii=this->widget_sets.size()-1 ;0<=ii ;--ii) {
		auto& wset = this->widget_sets.at(ii);
		if (wset.chebut_enable_sw->value() == 1) {
		 return wset.group_trace->y() + wset.group_trace->h() + 5;
		}
	}
	return 0;
}

//--------------------

void fltk_button_trace_params::draw()
{
	Fl_Button::draw();
}

namespace {

/* エラーがあればその情報を文字で返す、成功ならempty文字列を返す */
const std::string dnd_paste_( const std::string &dnd_str )
{
	/* 複数のファイルパスはエラー */
	if (std::string::npos != dnd_str.find("\n")) {
		return "Error : Need Only 1 Filepath";
	}

	/* 必要な情報に変える */
	std::string dpath , head , num_form , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		dnd_str ,dpath ,head ,num_form ,number ,ext ,nums
	);

	/* Config file */
	if (ext == ".txt") {
		if (cl_gts_master.cl_memo_config.load_only_trace_params(
		dnd_str ) == NG) {
		 return "Error : loading trace_params in config";
		}
	}
	/* 拡張子が対応外エラー */
	else {
		return "Error : Need extension .txt";
	}
	return std::string();
}

} // namespace

#include <FL/fl_ask.H>	// fl_alert(-) 
int fltk_button_trace_params::handle( int event )
{
	switch (event) {
	case FL_DND_ENTER:
	case FL_DND_DRAG:
	case FL_DND_RELEASE:
		return 1;

	case FL_PASTE: // DND Paste
	{
		std::string err(dnd_paste_( Fl::event_text() ));
		if (!err.empty()) {
			fl_alert( err.c_str() );
		}
	}
		return 1;

	default:
		/* pass other events to the base class */
		return Fl_Button::handle(event);
	}
	return 0;
}

//---------------
