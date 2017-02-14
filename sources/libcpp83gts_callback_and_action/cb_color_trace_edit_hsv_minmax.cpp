#include "cb_color_trace_edit_hsv_minmax.h"
#include "gts_gui.h"
#include "gts_master.h"

void cb_color_trace_edit_hsv_minmax::cb_hh_minmax( double minval, double maxval )
{
	/* histogram生成する色立体の範囲(0...359.xxx) */
	cl_gts_master.cl_color_trace_enhancement.src_set_hh_min_max(
		minval, maxval
	);

	/* エリアhistogram生成、画像の表示変更 */
	cl_gts_gui.opengl_view->redraw(); /* 画像再表示 */

	/* "edit hsv minmax"ウインドウの数値表示入力GUIの変更 */
	cl_gts_gui.valinp_hab_histogram_hh_min->value(minval);
	cl_gts_gui.valinp_hab_histogram_hh_max->value(maxval);

	/* color trace enhancement windowの指定番号の値の表示変更 */
	if (OK != cl_gts_master.cl_color_trace_enhancement.src_edit_hh(
	 cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	 ,minval, maxval
	)) {
		return;
	}
}
void cb_color_trace_edit_hsv_minmax::cb_aa_minmax( double minval, double maxval )
{
	/* histogram生成する色立体の範囲(0...1) */
	cl_gts_master.cl_color_trace_enhancement.src_set_aa_min_max(
		minval, maxval
	);

	/* エリアhistogram生成、画像の表示変更 */
	cl_gts_gui.opengl_view->redraw(); /* 画像再表示 */

	/* "edit hsv minmax"ウインドウの数値表示入力GUIの変更 */
	cl_gts_gui.valinp_hab_histogram_aa_min->value(minval*100.0);
	cl_gts_gui.valinp_hab_histogram_aa_max->value(maxval*100.0);

	/* color trace enhancement windowの指定番号の値の表示変更 */
	if (OK != cl_gts_master.cl_color_trace_enhancement.src_edit_aa(
	 cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	 ,minval, maxval
	)) {
		return;
	}
}
void cb_color_trace_edit_hsv_minmax::cb_bb_minmax( double minval, double maxval )
{
	/* histogram生成する色立体の範囲(0...1) */
	cl_gts_master.cl_color_trace_enhancement.src_set_bb_min_max(
		minval, maxval
	);

	/* エリアhistogram生成、画像の表示変更 */
	cl_gts_gui.opengl_view->redraw(); /* 画像再表示 */

	/* "edit hsv minmax"ウインドウの数値表示入力GUIの変更 */
	cl_gts_gui.valinp_hab_histogram_bb_min->value(minval*100.0);
	cl_gts_gui.valinp_hab_histogram_bb_max->value(maxval*100.0);

	/* color trace enhancement windowの指定番号の値の表示変更 */
	if (OK != cl_gts_master.cl_color_trace_enhancement.src_edit_bb(
	 cl_gts_master.cl_color_trace_enhancement.src_get_e_color_range()
	 ,minval, maxval
	)) {
		return;
	}
}
void cb_color_trace_edit_hsv_minmax::cb_hh_min( double minval )
{
	cl_gts_master.cl_color_trace_enhancement.cb_src_hh_min( minval );
}
void cb_color_trace_edit_hsv_minmax::cb_hh_max( double maxval )
{
	cl_gts_master.cl_color_trace_enhancement.cb_src_hh_max( maxval );
}
void cb_color_trace_edit_hsv_minmax::cb_aa_min( double minval )
{
	cl_gts_master.cl_color_trace_enhancement.cb_src_aa_min( minval );
}
void cb_color_trace_edit_hsv_minmax::cb_aa_max( double maxval )
{
	cl_gts_master.cl_color_trace_enhancement.cb_src_aa_max( maxval );
}
void cb_color_trace_edit_hsv_minmax::cb_bb_min( double minval )
{
	cl_gts_master.cl_color_trace_enhancement.cb_src_bb_min( minval );
}
void cb_color_trace_edit_hsv_minmax::cb_bb_max( double maxval )
{
	cl_gts_master.cl_color_trace_enhancement.cb_src_bb_max( maxval );
}
