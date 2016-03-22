#include <FL/Fl.h>
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/* color trace enhancement windowから、
有効無効のON/OFF時等で、画像の再表示するとき使用 */
void gts_master::cb_color_trace_src_redraw_image( void )
{
	this->_iipg_view_redraw();
}

/* color trace enhancement windowから、
番号指定してhistogram windowを開く時 */
void  gts_master::cb_color_trace_src_open_01( void )
{ (void)this->cl_color_trace_enhancement.src_open_histogram_window(
			E_COLOR_TRACE_HAB_01 );
}
void  gts_master::cb_color_trace_src_open_02( void )
{ (void)this->cl_color_trace_enhancement.src_open_histogram_window(
			E_COLOR_TRACE_HAB_02 );
}
void  gts_master::cb_color_trace_src_open_03( void )
{ (void)this->cl_color_trace_enhancement.src_open_histogram_window(
			E_COLOR_TRACE_HAB_03 );
}
void  gts_master::cb_color_trace_src_open_04( void )
{ (void)this->cl_color_trace_enhancement.src_open_histogram_window(
			E_COLOR_TRACE_HAB_04 );
}
void  gts_master::cb_color_trace_src_open_05( void )
{ (void)this->cl_color_trace_enhancement.src_open_histogram_window(
			E_COLOR_TRACE_HAB_05 );
}
void  gts_master::cb_color_trace_src_open_06( void )
{ (void)this->cl_color_trace_enhancement.src_open_histogram_window(
			E_COLOR_TRACE_HAB_06 );
}

/* color trace enhancement windowの、
Scroll Bar,Value Inputの値を変えたとき */
void gts_master::cb_color_trace_src_edit_value( void )
{
	/* histogram windowが表示しているなら、値の変更表示 */
	if (cl_gts_gui.window_hab_histogram->visible()) {
	 this->cl_color_trace_enhancement.src_set_histogram_window(
	  this->cl_color_trace_enhancement.src_get_e_color_range()
	 );
	}

	/* 画像の表示変更 */
	this->_iipg_view_redraw();

	if (cl_gts_gui.window_hab_histogram->visible()) {
		cl_gts_gui.window_hab_histogram->redraw();
	}
}

/*--------------------------------------------------------*/
/* histogram windowで値を変えたとき */

void gts_master::cb_color_trace_src_edit_hh( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...359.xxx) */
	this->cl_color_trace_enhancement.src_set_hh_min_max(
		d_min, d_max );

	/* エリアhistogram生成、画像の表示変更 */
	this->_iipg_view_redraw();

	/* color trace enhancement windowの指定番号の値の表示変更 */
	if (OK != this->cl_color_trace_enhancement.src_edit_hh(
		this->cl_color_trace_enhancement.src_get_e_color_range(),
		d_min, d_max
	)) {
		return;
	}
}
void gts_master::cb_color_trace_src_edit_aa( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...1) */
	this->cl_color_trace_enhancement.src_set_aa_min_max(
		d_min, d_max );

	/* エリアhistogram生成、画像の表示変更 */
	this->_iipg_view_redraw();

	/* color trace enhancement windowの指定番号の値の表示変更 */
	if (OK != this->cl_color_trace_enhancement.src_edit_aa(
		this->cl_color_trace_enhancement.src_get_e_color_range(),
		d_min, d_max
	)) {
		return;
	}
}
void gts_master::cb_color_trace_src_edit_bb( double d_min, double d_max )
{
	/* histogram生成する色立体の範囲(0...1) */
	this->cl_color_trace_enhancement.src_set_bb_min_max(
		d_min, d_max );

	/* エリアhistogram生成、画像の表示変更 */
	this->_iipg_view_redraw();

	/* color trace enhancement windowの指定番号の値の表示変更 */
	if (OK != this->cl_color_trace_enhancement.src_edit_bb(
		this->cl_color_trace_enhancement.src_get_e_color_range(),
		d_min, d_max
	)) {
		return;
	}
}
/*--------------------------------------------------------*/
void gts_master::cb_color_trace_src_limit_nothing( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_nothing();

	this->_iipg_view_redraw();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_hab_histogram->redraw();
}
void gts_master::cb_color_trace_src_limit_hh( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_hh();

	this->_iipg_view_redraw();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_hab_histogram->redraw();
}
void gts_master::cb_color_trace_src_limit_aa( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_aa();

	this->_iipg_view_redraw();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_hab_histogram->redraw();
}
void gts_master::cb_color_trace_src_limit_bb( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_bb();

	this->_iipg_view_redraw();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_hab_histogram->redraw();
}
