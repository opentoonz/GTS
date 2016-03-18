#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::color_trace_in_view_area( void )
{
	//static int _i_mouse_middle_dragging_sw = OFF;

	/* マウスドラッグ中は処理しない */
	if (ON == this->cl_fltk_event.get_i_mouse_middle_dragging()) {
		return;
	}

	/* メニューのリアルタイム指示を確認 */
	if (0 == cl_gts_gui.chkbtn_color_trace_real_time->value()) {
		return;
	}

	/* データがなければ実行しない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		return;
	}

	/* 分割画面でなければなにもしない */
	switch (this->cl_ogl_view.get_e_wview_type()) {
	case E_WVIEW_TYPE_NOTHING: return;
	case E_WVIEW_TYPE_MAIN: return;
	case E_WVIEW_TYPE_SUB: return;
	case E_WVIEW_TYPE_LR_PARALLEL: break;
	case E_WVIEW_TYPE_LR_ONION: return;
	case E_WVIEW_TYPE_UD_PARALLEL: break;
	case E_WVIEW_TYPE_UD_ONION: return;
	}

	/* zoom値がとれないか、1/2より小さいときは実行しない */
	if (	(this->cl_ogl_view.get_l_zoom() < -2) ||
		(0L == this->cl_ogl_view.get_l_zoom())
	) {
		return;
	}

	/* トレス準備 */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return;
	}

	/* 表示準備 */
	/**if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}**/

	/* トレス(viewエリアのみ) */
	this->_iipg_color_trace_exec(ON);

	/* color trace histogramの再描画 */
	cl_gts_gui.window_hab_histogram->redraw();
}
