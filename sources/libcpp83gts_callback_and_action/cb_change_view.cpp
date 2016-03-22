#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_change_view_main_or_lr_or_sub( void )
{
	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		return;
	}

	/* メニュー選択が、RGBフルカラーでないと実行しない */
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:
	case 1:
		return;
	}

	/* トレス準備をまだやっていないときは実行 */
	if (this->cl_iip_trac.get_l_channels() < 3L) {
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			return;
		}
	}

	/* 表示準備 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}

	/* 画面の表示変更 */
	switch (this->cl_ogl_view.get_e_wview_type()) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		this->_wview_lr_parallel();
		break;
	case E_WVIEW_TYPE_SUB:
		this->_wview_main();
		break;
	case E_WVIEW_TYPE_LR_PARALLEL:
		//this->_wview_sub();
		this->_wview_main();
		break;
	case E_WVIEW_TYPE_LR_ONION: break;
	case E_WVIEW_TYPE_UD_PARALLEL: break;
	case E_WVIEW_TYPE_UD_ONION: break;
	}

	/* 表示 */
	this->_iipg_view_redraw();
}

void gts_master::cb_change_view_lr_or_ud( void )
{
	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		return;
	}

	/* メニュー選択が、RGBフルカラーでないと実行しない */
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:
	case 1:
		return;
	}

	/* トレス準備をまだやっていないときは実行 */
	if (this->cl_iip_trac.get_l_channels() < 3L) {
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			return;
		}
	}

	/* 表示準備 */
	/***if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}***/

	/* 画面のlrとud表示変更 */
	switch (this->cl_ogl_view.get_e_wview_type()) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN: break;
	case E_WVIEW_TYPE_SUB: break;
	case E_WVIEW_TYPE_LR_PARALLEL:
		this->_wview_ud_parallel();
		break;
	case E_WVIEW_TYPE_LR_ONION: break;
	case E_WVIEW_TYPE_UD_PARALLEL:
		this->_wview_lr_parallel();
		break;
	case E_WVIEW_TYPE_UD_ONION: break;
	}

	/* 表示 */
	this->_iipg_view_redraw();
}

void gts_master::cb_real_time_on_off( void )
{
	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		return;
	}

	/* メニュー選択が、RGBフルカラーでないと実行しない */
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:
	case 1:
		return;
	}

	/* トレス準備をまだやっていないときは実行 */
	if (this->cl_iip_trac.get_l_channels() < 3L) {
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			return;
		}
	}

	/* 表示準備 */
	/***if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}***/

	/* 分割画面でなければなにもしない */
	switch (this->cl_ogl_view.get_e_wview_type()) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN: break;
	case E_WVIEW_TYPE_SUB: this->_iipg_view_redraw(); break;
	case E_WVIEW_TYPE_LR_PARALLEL: this->_iipg_view_redraw(); break;
	case E_WVIEW_TYPE_UD_PARALLEL: this->_iipg_view_redraw(); break;
	case E_WVIEW_TYPE_LR_ONION: break;
	case E_WVIEW_TYPE_UD_ONION: break;
	}
}
