#include <iostream>
#include "cb_trace_params.h"
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
void set_target_color_( const int number , Fl_Button* button )
{
	button->color( static_cast<Fl_Color>( number + 16 ) );
}

void tgt_to_tbl_( const int number , const calcu_sep_hsv& pa )
{
	const double mx = (std::numeric_limits<uchar>::max)() + 0.999999;

	set_target_rgb_( number
		,static_cast<unsigned char>(pa.target_r * mx)
		,static_cast<unsigned char>(pa.target_g * mx)
		,static_cast<unsigned char>(pa.target_b * mx)
	);
}

} // namespace

void cb_trace_params::cb_open_color_editor(
	Fl_Double_Window* flwin
	,Fl_Button* flbut
	,const int number
)
{
	/* rgb値を記憶 */
	get_target_rgb_( number ,this->r_ ,this->g_ ,this->b_ );

	/* Editorにrgb初期値を設定 */
	cl_gts_gui.valinp_set_color_red->value(this->r_);
	cl_gts_gui.scrbar_set_color_red->value(this->r_);
	cl_gts_gui.valinp_set_color_gre->value(this->g_);
	cl_gts_gui.scrbar_set_color_gre->value(this->g_);
	cl_gts_gui.valinp_set_color_blu->value(this->b_);
	cl_gts_gui.scrbar_set_color_blu->value(this->b_);

	/* 色テーブル番号を記憶 */
	this->number_ = number;

	/* window開く */
	cl_gts_gui.window_set_color->show();
	cl_gts_gui.window_set_color->position(
		 flwin->x() + flbut->x() - 10
		,flwin->y() + flbut->y() - 130
	);
}

//------------------------------------------------------------

void cb_trace_params::init_color(void)
{
	std::vector<cb_trace_params::widget_set>& vwset(
		cl_gts_master.cl_trace_params.widget_sets
	);
	for (int ii = 0 ; ii < static_cast<int>(vwset.size()) ; ++ii) {
		set_target_color_( ii ,vwset.at(ii).button_target_rgb );
		tgt_to_tbl_(
		 ii ,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(ii)
		);
	}
}

//------------------------------------------------------------

namespace {

void from_editor_to_tgt_( const int number )
{
	cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(number).target_r =
	cl_gts_gui.valinp_set_color_red->value() /
	cl_gts_gui.valinp_set_color_red->maximum() ;

	cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(number).target_g =
	cl_gts_gui.valinp_set_color_gre->value() /
	cl_gts_gui.valinp_set_color_gre->maximum() ;

	cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(number).target_b =
	cl_gts_gui.valinp_set_color_blu->value() /
	cl_gts_gui.valinp_set_color_blu->maximum() ;
}

} // namespace

void cb_trace_params::cb_change_color(void)
{
	/* GUIの保持値を表示用高速アクセスパラメータにコピー */
	from_editor_to_tgt_( this->number_ );

	/* 表示用高速アクセスパラメータをGUIカラーテーブルにセット */
	calcu_sep_hsv& vset(
	 cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(this->number_)
	);
	tgt_to_tbl_( this->number_ , vset );

	/* GUIカラーテーブルでボタンのターゲット色を再表示 */
	cb_trace_params::widget_set& wset(
		cl_gts_master.cl_trace_params.widget_sets.at(this->number_)
	);
	wset.button_target_rgb->redraw();

	/* Image(& hsvも中でredrawしてる)の再表示 */
	cl_gts_gui.image_view->redraw();
}

void cb_trace_params::cb_cancel(void)
{
	/* rgb値を表示用カラーテーブルに戻す */
	this->set_target_rgb( this->number_ ,this->r_ ,this->g_ ,this->b_ );

	/* GUIの色表示をredraw */
	cb_trace_params::widget_set& wset(
	 cl_gts_master.cl_trace_params.widget_sets.at(this->number_)
	);
	wset.button_target_rgb->redraw();

	/* rgb値をtgt変数に戻す */
	const double mx = (std::numeric_limits<uchar>::max)();
	calcu_sep_hsv& vset(
	 cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(this->number_)
	);
	vset.target_r = this->r_ / mx;
	vset.target_g = this->g_ / mx;
	vset.target_b = this->b_ / mx;

	/* OpenGLの表示をredraw */
	cl_gts_gui.image_view->redraw();
}

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

void cb_trace_params::init_widget_set_(void) {
	this->widget_sets = {
	{cl_gts_gui.chebut_trace_0_enable_sw
	,cl_gts_gui.group_trace_0
	,cl_gts_gui.button_trace_0_target_rgb
	,cl_gts_gui.valinp_trace_0_thickness
	,cl_gts_gui.roller_trace_0_thickness
	,cl_gts_gui.valinp_trace_0_hue_min
	,cl_gts_gui.valinp_trace_0_hue_max
	,cl_gts_gui.valinp_trace_0_slope_deg
	,cl_gts_gui.valinp_trace_0_intercept
	,cl_gts_gui.chebut_trace_0_display_sw
	}
	,{cl_gts_gui.chebut_trace_1_enable_sw
	,cl_gts_gui.group_trace_1
	,cl_gts_gui.button_trace_1_target_rgb
	,cl_gts_gui.valinp_trace_1_thickness
	,cl_gts_gui.roller_trace_1_thickness
	,cl_gts_gui.valinp_trace_1_hue_min
	,cl_gts_gui.valinp_trace_1_hue_max
	,cl_gts_gui.valinp_trace_1_slope_deg
	,cl_gts_gui.valinp_trace_1_intercept
	,cl_gts_gui.chebut_trace_1_display_sw
	}
	,{cl_gts_gui.chebut_trace_2_enable_sw
	,cl_gts_gui.group_trace_2
	,cl_gts_gui.button_trace_2_target_rgb
	,cl_gts_gui.valinp_trace_2_thickness
	,cl_gts_gui.roller_trace_2_thickness
	,cl_gts_gui.valinp_trace_2_hue_min
	,cl_gts_gui.valinp_trace_2_hue_max
	,cl_gts_gui.valinp_trace_2_slope_deg
	,cl_gts_gui.valinp_trace_2_intercept
	,cl_gts_gui.chebut_trace_2_display_sw
	}
	,{cl_gts_gui.chebut_trace_3_enable_sw
	,cl_gts_gui.group_trace_3
	,cl_gts_gui.button_trace_3_target_rgb
	,cl_gts_gui.valinp_trace_3_thickness
	,cl_gts_gui.roller_trace_3_thickness
	,cl_gts_gui.valinp_trace_3_hue_min
	,cl_gts_gui.valinp_trace_3_hue_max
	,cl_gts_gui.valinp_trace_3_slope_deg
	,cl_gts_gui.valinp_trace_3_intercept
	,cl_gts_gui.chebut_trace_3_display_sw
	}
	,{cl_gts_gui.chebut_trace_4_enable_sw
	,cl_gts_gui.group_trace_4
	,cl_gts_gui.button_trace_4_target_rgb
	,cl_gts_gui.valinp_trace_4_thickness
	,cl_gts_gui.roller_trace_4_thickness
	,cl_gts_gui.valinp_trace_4_hue_min
	,cl_gts_gui.valinp_trace_4_hue_max
	,cl_gts_gui.valinp_trace_4_slope_deg
	,cl_gts_gui.valinp_trace_4_intercept
	,cl_gts_gui.chebut_trace_4_display_sw
	}
	,{cl_gts_gui.chebut_trace_5_enable_sw
	,cl_gts_gui.group_trace_5
	,cl_gts_gui.button_trace_5_target_rgb
	,cl_gts_gui.valinp_trace_5_thickness
	,cl_gts_gui.roller_trace_5_thickness
	,cl_gts_gui.valinp_trace_5_hue_min
	,cl_gts_gui.valinp_trace_5_hue_max
	,cl_gts_gui.valinp_trace_5_slope_deg
	,cl_gts_gui.valinp_trace_5_intercept
	,cl_gts_gui.chebut_trace_5_display_sw
	}
	,{cl_gts_gui.chebut_trace_6_enable_sw
	,cl_gts_gui.group_trace_6
	,cl_gts_gui.button_trace_6_target_rgb
	,cl_gts_gui.valinp_trace_6_thickness
	,cl_gts_gui.roller_trace_6_thickness
	,cl_gts_gui.valinp_trace_6_hue_min
	,cl_gts_gui.valinp_trace_6_hue_max
	,cl_gts_gui.valinp_trace_6_slope_deg
	,cl_gts_gui.valinp_trace_6_intercept
	,cl_gts_gui.chebut_trace_6_display_sw
	}
	};
}
