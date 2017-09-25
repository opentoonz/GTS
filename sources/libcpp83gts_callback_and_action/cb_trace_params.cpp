#include <iostream>
//#include <string>
//#include <iomanip> // std;;setw()
//#include <sstream> // std::ostringstream
//#include "ids_path_level_from_files.h"
#include "cb_trace_params.h"
#include "gts_gui.h"
#include "gts_master.h"

void cb_trace_params::cb_open_color_editor(
	Fl_Double_Window* flwin
	,Fl_Button* flbut
	,const int number
)
{
	/* rgb値を記憶 */
	Fl::get_color(static_cast<Fl_Color>( number + 16 )
		,this->r_ ,this->g_ ,this->b_
	);

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

namespace {

void from_tbl_to_button_(void)
{
	cl_gts_gui.but_trace_0_target_rgb->color(static_cast<Fl_Color>(16));
	cl_gts_gui.but_trace_1_target_rgb->color(static_cast<Fl_Color>(17));
	cl_gts_gui.but_trace_2_target_rgb->color(static_cast<Fl_Color>(18));
	cl_gts_gui.but_trace_3_target_rgb->color(static_cast<Fl_Color>(19));
	cl_gts_gui.but_trace_4_target_rgb->color(static_cast<Fl_Color>(20));
	cl_gts_gui.but_trace_5_target_rgb->color(static_cast<Fl_Color>(21));
	cl_gts_gui.but_trace_6_target_rgb->color(static_cast<Fl_Color>(22));
}

void tgt_to_tbl_( const int number , const calcu_sep_hsv& pa )
{
	const double mx = (std::numeric_limits<uchar>::max)() + 0.999999;
	Fl::set_color(static_cast<Fl_Color>(number)
		,static_cast<unsigned char>(pa.target_r * mx)
		,static_cast<unsigned char>(pa.target_g * mx)
		,static_cast<unsigned char>(pa.target_b * mx)
 	);
}

void from_tgt_to_tbl0_(void)
{
	tgt_to_tbl_(16,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(0));
}
void from_tgt_to_tbl1_(void)
{
	tgt_to_tbl_(17,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(1));
}
void from_tgt_to_tbl2_(void)
{
	tgt_to_tbl_(18,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(2));
}
void from_tgt_to_tbl3_(void)
{
	tgt_to_tbl_(19,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(3));
}
void from_tgt_to_tbl4_(void)
{
	tgt_to_tbl_(20,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(4));
}
void from_tgt_to_tbl5_(void)
{
	tgt_to_tbl_(21,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(5));
}
void from_tgt_to_tbl6_(void)
{
	tgt_to_tbl_(22,cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(6));
}

} // namespace

void cb_trace_params::init_color(void)
{
	from_tbl_to_button_();
	from_tgt_to_tbl0_();
	from_tgt_to_tbl1_();
	from_tgt_to_tbl2_();
	from_tgt_to_tbl3_();
	from_tgt_to_tbl4_();
	from_tgt_to_tbl5_();
	from_tgt_to_tbl6_();
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
	switch (this->number_) {
	case 0:
		from_editor_to_tgt_( 0);
		      from_tgt_to_tbl0_();
		cl_gts_gui.but_trace_0_target_rgb->redraw(); break;
	case 1:
		from_editor_to_tgt_( 1);
		      from_tgt_to_tbl1_();
		cl_gts_gui.but_trace_1_target_rgb->redraw(); break;
	case 2:
		from_editor_to_tgt_( 2);
		      from_tgt_to_tbl2_();
		cl_gts_gui.but_trace_2_target_rgb->redraw(); break;
	case 3:
		from_editor_to_tgt_( 3);
		      from_tgt_to_tbl3_();
		cl_gts_gui.but_trace_3_target_rgb->redraw(); break;
	case 4:
		from_editor_to_tgt_( 4);
		      from_tgt_to_tbl4_();
		cl_gts_gui.but_trace_4_target_rgb->redraw(); break;
	case 5:
		from_editor_to_tgt_( 5);
		      from_tgt_to_tbl5_();
		cl_gts_gui.but_trace_5_target_rgb->redraw(); break;
	case 6:
		from_editor_to_tgt_( 6);
		      from_tgt_to_tbl6_();
		cl_gts_gui.but_trace_6_target_rgb->redraw(); break;
	}
	cl_gts_gui.image_view->redraw();
}

void cb_trace_params::cb_cancel(void)
{
	/* rgb値を表示用カラーテーブルに戻す */
	Fl::set_color(static_cast<Fl_Color>( this->number_ + 16 )
		,this->r_ ,this->g_ ,this->b_
	);

	/* GUIの色表示をredraw */
	switch (this->number_) {
	case 0: cl_gts_gui.but_trace_0_target_rgb->redraw(); break;
	case 1: cl_gts_gui.but_trace_1_target_rgb->redraw(); break;
	case 2: cl_gts_gui.but_trace_2_target_rgb->redraw(); break;
	case 3: cl_gts_gui.but_trace_3_target_rgb->redraw(); break;
	case 4: cl_gts_gui.but_trace_4_target_rgb->redraw(); break;
	case 5: cl_gts_gui.but_trace_5_target_rgb->redraw(); break;
	case 6: cl_gts_gui.but_trace_6_target_rgb->redraw(); break;
	}

	/* rgb値をtgt変数に戻す */
	const double mx = (std::numeric_limits<uchar>::max)();
	cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(this->number_).target_r = this->r_ / mx;
	cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(this->number_).target_g = this->g_ / mx;
	cl_gts_master.cl_calcu_sep_hsv.cla_area_param.at(this->number_).target_b = this->b_ / mx;

	/* OpenGLの表示をredraw */
	cl_gts_gui.image_view->redraw();
}
