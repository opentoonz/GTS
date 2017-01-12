#include <FL/Fl.H>
#include "pri.h"
#include "ptbl_returncode.h"
#include "cb_color_trace_enhancement.h"
#include "gts_gui.h"

/*
トレス色番号から、fltkカラーテーブル番号を得る
トレス色番号を選択してない場合は-1を返す
*/
int cb_color_trace_enhancement::tgt_fl_color_number_from_trace_list_pos(
	E_COLOR_TRACE_HAB_COLORS trace_list_pos
)
{
	switch (trace_list_pos) {
	case E_COLOR_TRACE_HAB_01: return FL_FREE_COLOR + 0;
	case E_COLOR_TRACE_HAB_02: return FL_FREE_COLOR + 1;
	case E_COLOR_TRACE_HAB_03: return FL_FREE_COLOR + 2;
	case E_COLOR_TRACE_HAB_04: return FL_FREE_COLOR + 3;
	case E_COLOR_TRACE_HAB_05: return FL_FREE_COLOR + 4;
	case E_COLOR_TRACE_HAB_06: return FL_FREE_COLOR + 5;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		return -1;
	}
	return -1;
}

/*
トレス色番号から、GUIのボタン(色)を再表示
トレス色番号を選択してない場合はなにもしない
*/
void cb_color_trace_enhancement::tgt_redraw_rgb_color(
	E_COLOR_TRACE_HAB_COLORS trace_list_pos
)
{
	switch (trace_list_pos) {
	case E_COLOR_TRACE_HAB_01:
 cl_gts_gui.button_color_trace_01_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_02:
 cl_gts_gui.button_color_trace_02_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_03:
 cl_gts_gui.button_color_trace_03_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_04:
 cl_gts_gui.button_color_trace_04_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_05:
 cl_gts_gui.button_color_trace_05_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_06:
 cl_gts_gui.button_color_trace_06_tgt_rgb->redraw(); break;
	case E_COLOR_TRACE_HAB_NOT_SELECT: break;
	}
}

//------------------------------

/* 各8-bitのrgb値を、fltkカラーテーブル指定色に設定する */
void cb_color_trace_enhancement::tgt_fl_set_color(
	int color_number
	, unsigned char red, unsigned char gre, unsigned char blu
)
{
	if (-1 < color_number) {
	 Fl::set_color( static_cast<Fl_Color>(color_number), red, gre, blu );
	}
}

/* fltkカラーテーブル指定色から、各8-bitのrgb値を得る */
void cb_color_trace_enhancement::tgt_fl_get_color(
	int color_number
	, unsigned char *red
	, unsigned char *gre
	, unsigned char *blu
)
{
	if (-1 < color_number) {
	 Fl::get_color(static_cast<Fl_Color>(color_number),*red,*gre,*blu);
	}
}

//------------------------------

/*
rgb値を、
トレス色番号に対応する、fltkカラーテーブル指定色に設定する
*/
void cb_color_trace_enhancement::tgt_set_uchar_rgb_color(
	E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, int red, int gre, int blu
)
{
	if ((red < 0) || (0xff < red)) {
		pri_funct_err_bttvr( "Error : red<%d>",red);
		return;
	}
	if ((gre < 0) || (0xff < gre)) {
		pri_funct_err_bttvr( "Error : gre<%d>",gre);
		return;
	}
	if ((blu < 0) || (0xff < blu)) {
		pri_funct_err_bttvr( "Error : blu<%d>",blu);
		return;
	}

	/* rgb値を
	指定のFlカラーテーブルのアドレス番号に設定する */
	this->tgt_fl_set_color(
	 this->tgt_fl_color_number_from_trace_list_pos( trace_list_pos )
	 , static_cast<unsigned char>(red)
	 , static_cast<unsigned char>(gre)
	 , static_cast<unsigned char>(blu)
	);
}

/*
トレス色番号に対応する、fltkカラーテーブル指定色から
rgb値を得る
*/
void cb_color_trace_enhancement::tgt_get_uchar_rgb_color(
	E_COLOR_TRACE_HAB_COLORS trace_list_pos
	, unsigned char *ucharp_red
	, unsigned char *ucharp_gre
	, unsigned char *ucharp_blu
)
{
	this->tgt_fl_get_color(
	 this->tgt_fl_color_number_from_trace_list_pos( trace_list_pos )
	 , ucharp_red, ucharp_gre, ucharp_blu
	);
}

//------------------------------

/*
edit color windowで値を変えたとき
トレス色番号に対応する、fltkカラーテーブル指定色を設定する
void cb_color_trace_enhancement::tgt_redraw_rgb_color(-)も実行必要
*/
void cb_color_trace_enhancement::tgt_edit_rgb_color(
	E_COLOR_TRACE_HAB_COLORS trace_list_pos
)
{
	this->tgt_set_uchar_rgb_color(
	 trace_list_pos
	 , static_cast<int>(cl_gts_gui.valinp_edit_color_red->value())
	 , static_cast<int>(cl_gts_gui.valinp_edit_color_gre->value())
	 , static_cast<int>(cl_gts_gui.valinp_edit_color_blu->value())
	);
}

namespace {
 void resize_tgt_button_(
	E_COLOR_TRACE_HAB_COLORS e_num
	,const int mgn
	,const char *label
	,Fl_Boxtype btype
 )
 {
 	Fl_Button *tbut=nullptr;
 	Fl_Button *ebut=nullptr;
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01:
		tbut= cl_gts_gui.button_thickness_01_tgt_rgb;
		ebut= cl_gts_gui.button_color_trace_01_tgt_rgb;
		break;
	case E_COLOR_TRACE_HAB_02:
		tbut= cl_gts_gui.button_thickness_02_tgt_rgb;
		ebut= cl_gts_gui.button_color_trace_02_tgt_rgb;
		break;
	case E_COLOR_TRACE_HAB_03:
		tbut= cl_gts_gui.button_thickness_03_tgt_rgb;
		ebut= cl_gts_gui.button_color_trace_03_tgt_rgb;
		break;
	case E_COLOR_TRACE_HAB_04:
		tbut= cl_gts_gui.button_thickness_04_tgt_rgb;
		ebut= cl_gts_gui.button_color_trace_04_tgt_rgb;
		break;
	case E_COLOR_TRACE_HAB_05:
		tbut= cl_gts_gui.button_thickness_05_tgt_rgb;
		ebut= cl_gts_gui.button_color_trace_05_tgt_rgb;
		break;
	case E_COLOR_TRACE_HAB_06:
		tbut= cl_gts_gui.button_thickness_06_tgt_rgb;
		ebut= cl_gts_gui.button_color_trace_06_tgt_rgb;
		break;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		break;
	}
	if (tbut != nullptr) {
		//tbut->size( 30+mgn ,20+mgn );
		//tbut->label( label );
		tbut->box( btype );
		cl_gts_gui.window_trace_thickness->redraw();
	}
	if (ebut != nullptr) {
		//ebut->size( 30+mgn ,45+mgn );
		//ebut->label( label );
		ebut->box( btype );
		cl_gts_gui.window_trace_parameters->redraw();
	}
 }
}

/*
edit color windowを設定して表示する
*/
void cb_color_trace_enhancement::tgt_open_edit_color( E_COLOR_TRACE_HAB_COLORS trace_list_pos )
{
	/* fltkカラーテーブル番号を得る */
	const int color_number =
	 this->tgt_fl_color_number_from_trace_list_pos( trace_list_pos );
	if (color_number < 0) { return; } /* 未選択はキャンセル */

	/* 使用中トレス色番号を設定 */
	if (this->_e_target_rgb_color != trace_list_pos)
	{
		resize_tgt_button_(
			this->_e_target_rgb_color
			,0 ,"tgt" ,FL_UP_BOX
		);
		resize_tgt_button_(
			trace_list_pos
			,0 ,"tgt" ,FL_ROUND_UP_BOX
		);
		this->_e_target_rgb_color = trace_list_pos;
	}

	/* 指定のFlカラーテーブルのrgb値を得る */
	unsigned char red, gre, blu;
	this->tgt_fl_get_color(
		color_number, &red, &gre, &blu
	);

	/* rgb値を、edit color windowに設定 */
	cl_gts_gui.valinp_edit_color_red->value(
		(double)red);
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_red)->value(
		(double)red);

	cl_gts_gui.valinp_edit_color_gre->value(
		(double)gre);
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_gre)->value(
		(double)gre);

	cl_gts_gui.valinp_edit_color_blu->value(
		(double)blu);
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_blu)->value(
		(double)blu);

	/* edit color windowを表示 */
	cl_gts_gui.menite_trace_output_color->set();
	cl_gts_gui.window_opengl->show();/* Need for Minimize */
	cl_gts_gui.window_trace_output_color->show();
}

/* color trace enhancement windowから、
番号指定してedit color windowを開く時 */
void cb_color_trace_enhancement::cb_tgt_show_01( void )
{this->tgt_open_edit_color(E_COLOR_TRACE_HAB_01);
}
void cb_color_trace_enhancement::cb_tgt_show_02( void )
{this->tgt_open_edit_color(E_COLOR_TRACE_HAB_02);
}
void cb_color_trace_enhancement::cb_tgt_show_03( void )
{this->tgt_open_edit_color(E_COLOR_TRACE_HAB_03);
}
void cb_color_trace_enhancement::cb_tgt_show_04( void )
{this->tgt_open_edit_color(E_COLOR_TRACE_HAB_04);
}
void cb_color_trace_enhancement::cb_tgt_show_05( void )
{this->tgt_open_edit_color(E_COLOR_TRACE_HAB_05);
}
void cb_color_trace_enhancement::cb_tgt_show_06( void )
{this->tgt_open_edit_color(E_COLOR_TRACE_HAB_06);
}

/*--------------------------------------------------------*/
