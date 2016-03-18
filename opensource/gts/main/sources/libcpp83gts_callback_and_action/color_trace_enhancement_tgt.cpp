#include <FL/Fl.h>
#include "pri.h"
#include "ptbl_returncode.h"
#include "color_trace_enhancement.h"
#include "gts_gui.h"

/* 使用中トレス色番号から、Flカラーテーブルのアドレス番号を得る */
int color_trace_enhancement::_tgt_get_i_color_number( E_COLOR_TRACE_HAB_COLORS e_num )
{
	switch (e_num) {
	case E_COLOR_TRACE_HAB_01: return FL_FREE_COLOR + 0;
	case E_COLOR_TRACE_HAB_02: return FL_FREE_COLOR + 1;
	case E_COLOR_TRACE_HAB_03: return FL_FREE_COLOR + 2;
	case E_COLOR_TRACE_HAB_04: return FL_FREE_COLOR + 3;
	case E_COLOR_TRACE_HAB_05: return FL_FREE_COLOR + 4;
	case E_COLOR_TRACE_HAB_06: return FL_FREE_COLOR + 5;
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return -1;
	}
	return -1;
}

/* rgb値を
指定のFlカラーテーブルのアドレス番号に設定する */
int color_trace_enhancement::_tgt_set_uchar_rgb_color( int i_color_number, unsigned char uchar_red, unsigned char uchar_gre, unsigned char uchar_blu )
{
	if (-1 == i_color_number) {
		pri_funct_err_bttvr(
			"Error : i_color_number is -1");
		return NG;
	}
	Fl::set_color(
		Fl_Color(i_color_number),
		uchar_red,
		uchar_gre,
		uchar_blu
	);
	return OK;
}

/* edit color windowのrgb値を
指定のFlカラーテーブルのアドレス番号に設定する */
int color_trace_enhancement::_tgt_set_rgb_color( int i_color_number )
{
	if (OK != this->_tgt_set_uchar_rgb_color( i_color_number,
		(unsigned char)(cl_gts_gui.valinp_edit_color_red->value()),
		(unsigned char)(cl_gts_gui.valinp_edit_color_gre->value()),
		(unsigned char)(cl_gts_gui.valinp_edit_color_blu->value())
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_tgt_set_uchar_rgb_color(-) returns NG");
		return NG;
	}
	return OK;
}

/* 指定のトレス色番号を再表示 */
int color_trace_enhancement::_tgt_redraw_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num )
{
	switch (e_num) {
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
	case E_COLOR_TRACE_HAB_NOT_SELECT:
		pri_funct_err_bttvr(
			"Error : e_num is E_COLOR_TRACE_HAB_NOT_SELECT");
		return NG;
	}
	return OK;
}

/* 指定のFlカラーテーブルのrgb値を得る */
int color_trace_enhancement::_tgt_get_uchar_rgb_color( int i_color_number, unsigned char *ucharp_red, unsigned char *ucharp_gre, unsigned char *ucharp_blu )
{
	if (-1 == i_color_number) {
		pri_funct_err_bttvr(
			"Error : i_color_number is -1");
		return NG;
	}
	Fl::get_color(
		Fl_Color(i_color_number),
		*ucharp_red,
		*ucharp_gre,
		*ucharp_blu
	);
	return OK;
}

/* rgb値を、edit color windowに設定 */
void color_trace_enhancement::_tgt_set_uchar_edit_color( unsigned char uchar_red, unsigned char uchar_gre, unsigned char uchar_blu )
{
	cl_gts_gui.valinp_edit_color_red->value(
		(double)uchar_red);
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_red)->value(
		(double)uchar_red);

	cl_gts_gui.valinp_edit_color_gre->value(
		(double)uchar_gre);
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_gre)->value(
		(double)uchar_gre);

	cl_gts_gui.valinp_edit_color_blu->value(
		(double)uchar_blu);
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_blu)->value(
		(double)uchar_blu);
}

/*--------------------------------------------------------*/

void color_trace_enhancement::tgt_open_edit_color( E_COLOR_TRACE_HAB_COLORS e_num )
{
	int	i_num;
	unsigned char
		uchar_red,
		uchar_gre,
		uchar_blu;

	/* 使用中トレス色番号を設定 */
	this->tgt_set_e_rgb_color(e_num);

	/* Flカラーテーブルのアドレス番号を得る */
	i_num = this->_tgt_get_i_color_number( e_num );
	if (i_num < 0) {
		pri_funct_err_bttvr(
	"Error : this->_tgt_get_i_color_number(-) returns minus");
		return;
	}

	/* 指定のFlカラーテーブルのrgb値を得る */
	if (OK != this->_tgt_get_uchar_rgb_color(
		i_num, &uchar_red, &uchar_gre, &uchar_blu
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_tgt_get_uchar_rgb_color() returns NG");
		return;
	}

	/* rgb値を、edit color windowに設定 */
	this->_tgt_set_uchar_edit_color(
		uchar_red, uchar_gre, uchar_blu
	);

	/* edit color windowを表示 */
	cl_gts_gui.window_edit_color->show();
}

/* edit color windowで値を変えたとき */
void color_trace_enhancement::tgt_edit_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num )
{
	int	i_color_number;

	/* 使用中トレス色番号から、
	Flカラーテーブルのアドレス番号を得る */
	i_color_number = this->_tgt_get_i_color_number( e_num );
	if (i_color_number < 0) {
		pri_funct_err_bttvr(
	"Error : this->_tgt_get_i_color_number(-) returns minus");
		return;
	}

	/* edit color windowのrgb値を
	指定のFlカラーテーブルのアドレス番号に設定する */
	if (OK != this->_tgt_set_rgb_color( i_color_number )) {
		pri_funct_err_bttvr(
	"Error : this->_tgt_set_rgb_color(-) returns minus");
		return;
	}

	/* 指定のトレス色番号を再表示 */
	if (OK != this->_tgt_redraw_rgb_color( e_num )) {
		pri_funct_err_bttvr(
	"Error : this->_tgt_redraw_rgb_color(-) returns minus");
		return;
	}
}

/*--------------------------------------------------------*/

void color_trace_enhancement::tgt_get_uchar_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num, unsigned char *ucharp_red, unsigned char *ucharp_gre, unsigned char *ucharp_blu )
{
	int	i_color_number;

	/* 使用中トレス色番号から、
	Flカラーテーブルのアドレス番号を得る */
	i_color_number = this->_tgt_get_i_color_number( e_num );
	if (i_color_number < 0) {
		pri_funct_err_bttvr(
	"Error : this->_tgt_get_i_color_number(-) returns minus");
		return;
	}

	/* 指定のFlカラーテーブルのrgb値を得る */
	if (OK != this->_tgt_get_uchar_rgb_color(
	i_color_number, ucharp_red, ucharp_gre, ucharp_blu )) {
		pri_funct_err_bttvr(
	 "Error : this->_tgt_get_uchar_rgb_color(-) returns NG");
		return;
	}
}
void color_trace_enhancement::tgt_set_uchar_rgb_color( E_COLOR_TRACE_HAB_COLORS e_num, int i_red, int i_gre, int i_blu )
{
	int	i_color_number;

	/* 使用中トレス色番号から、
	Flカラーテーブルのアドレス番号を得る */
	i_color_number = this->_tgt_get_i_color_number( e_num );
	if (i_color_number < 0) {
		pri_funct_err_bttvr(
	"Error : this->_tgt_get_i_color_number(-) returns minus");
		return;
	}

	/* 色の値のチェック */
	if ((i_red < 0) || (0xff < i_red)) {
		pri_funct_err_bttvr( "Error : i_red<%d>",i_red);
		return;
	}
	if ((i_gre < 0) || (0xff < i_gre)) {
		pri_funct_err_bttvr( "Error : i_gre<%d>",i_gre);
		return;
	}
	if ((i_blu < 0) || (0xff < i_blu)) {
		pri_funct_err_bttvr( "Error : i_blu<%d>",i_blu);
		return;
	}

	/* rgb値を
	指定のFlカラーテーブルのアドレス番号に設定する */
	if (OK != this->_tgt_set_uchar_rgb_color( i_color_number,
		(unsigned char)i_red,
		(unsigned char)i_gre,
		(unsigned char)i_blu
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_tgt_set_uchar_rgb_color(-) returns NG");
		return;
	}
}
/*--------------------------------------------------------*/
