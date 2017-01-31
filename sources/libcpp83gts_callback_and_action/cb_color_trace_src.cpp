#include <FL/Fl.H>
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/* color trace enhancement windowから、
有効無効のON/OFF時等で、画像の再表示するとき使用 */
void gts_master::cb_color_trace_src_redraw_image( void )
{
	this->iipg_view_redraw_();
}

/* color trace enhancement windowの、
Scroll Bar,Value Inputの値を変えたとき */
void gts_master::cb_color_trace_src_edit_value( void )
{
	/* histogram windowが表示しているなら、値の変更表示 */
	if (cl_gts_gui.window_trace_input_color->visible()) {
	 this->cl_color_trace_enhancement.src_set_histogram_window(
	  this->cl_color_trace_enhancement.src_get_e_color_range()
	 );
	}

	/* 画像の表示変更 */
	this->iipg_view_redraw_();

	if (cl_gts_gui.window_trace_input_color->visible()) {
		cl_gts_gui.window_trace_input_color->redraw();
	}
}

/*--------------------------------------------------------*/
void gts_master::cb_color_trace_src_limit_nothing( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_nothing();

	this->iipg_view_redraw_();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_trace_input_color->redraw();
}
void gts_master::cb_color_trace_src_limit_hh( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_hh();

	this->iipg_view_redraw_();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_trace_input_color->redraw();
}
void gts_master::cb_color_trace_src_limit_aa( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_aa();

	this->iipg_view_redraw_();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_trace_input_color->redraw();
}
void gts_master::cb_color_trace_src_limit_bb( void )
{
	this->cl_color_trace_enhancement.src_set_range_is_bb();

	this->iipg_view_redraw_();

	/* histogram windowは必ず開いている */
	cl_gts_gui.window_trace_input_color->redraw();
}
