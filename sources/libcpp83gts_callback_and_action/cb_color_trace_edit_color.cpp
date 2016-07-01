#include "gts_master.h"

/* edit color windowで値を変えたとき */
void cb_color_trace_edit_color::cb_change_color( void )
{
	/*
	"edit_color"のRGB色を、
	カレントのトレス色番号から、対応するfltkカラーテーブル色に変更する
	*/
	cl_gts_master.cl_color_trace_enhancement.tgt_edit_rgb_color(
	 cl_gts_master.cl_color_trace_enhancement.tgt_get_e_rgb_color()
	);

	/* 再表示 */
	cl_gts_master.cl_color_trace_enhancement.tgt_redraw_rgb_color(
	 cl_gts_master.cl_color_trace_enhancement.tgt_get_e_rgb_color()
	);
	cl_gts_master.cl_color_trace_thickness.tgt_redraw_rgb_color(
	 cl_gts_master.cl_color_trace_enhancement.tgt_get_e_rgb_color()
	);
}

