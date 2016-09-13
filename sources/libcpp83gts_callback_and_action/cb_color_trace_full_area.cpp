#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_color_trace_full_area( void )
{
	/* データがなければ実行しない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* メニューは関係なし */
	/***if (2 != cl_gts_gui.choice_pixel_type->value()) {
		return;
	}***/

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		return;
	}

	/* RGB画像の処理となるので、モードを自動切替えする */
	//cl_gts_gui.choice_pixel_type->value(2);

	/* 画像全体に処理を実行 */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return;
	}
	this->_iipg_color_trace_exec();

	/* 表示 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}
	this->iipg_view_redraw_();

	/* color trace histogram maxの設定 */
	this->cl_color_trace_enhancement.src_set_histogram_max();

	/* color trace histogram window の再描画 */
	cl_gts_gui.window_hab_histogram->redraw();

	/* 画面分割(中でredraw()もやってる) */
	this->_wview_lr_parallel();

	/* 再表示 */
	/***cl_gts_gui.opengl_view->redraw();***/
}
