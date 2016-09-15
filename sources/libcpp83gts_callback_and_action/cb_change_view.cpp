#include <FL/fl_ask.H> // fl_alert()
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_change_wview_main_or_lr_ud( void )
{
	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		cl_gts_gui.menite_wview_main_or_lr_ud->clear();
		fl_alert("No Image");
		return;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		cl_gts_gui.menite_wview_main_or_lr_ud->clear();
		fl_alert("Not RGB Image");
		return;
	}

	/*
		"Pixel Type and Bright"ウインドウの"Pixel Type"選択
			"cl_gts_gui.choice_pixel_type->value()"
		は、
		Scanの画像タイプなので、ここには関係しない
	*/

	/* トレス準備をまだやっていないときは実行 */
	if (this->cl_iip_trac.get_l_channels() < 3L) {
		/* ２値化処理の準備 */
/* ここにくることはあるのか？なぜ、BW,Grayscaleでトレス準備する？
   後日refactoringで整理する　*/
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			cl_gts_gui.menite_wview_main_or_lr_ud->clear();
			return;
		}

/* なぜ、トレス処理してない?
   後日refactoringで整理する　*/
		/* ２値化処理を実行 */
		//this->_iipg_color_trace_exec();
	}

	/* 表示準備 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		cl_gts_gui.menite_wview_main_or_lr_ud->clear();
		return;
	}

	/* 画面の表示変更 */
	if (	cl_gts_gui.menite_wview_main_or_lr_ud->value() ==  0) {
		this->_wview_main();
	}
	else {
		if (cl_gts_gui.menite_wview_lr_or_ud->value() == 0) {
			this->_wview_lr_parallel();
		}
		else {
			this->_wview_ud_parallel();
		}
	}

	/* 表示 */
	this->iipg_view_redraw_();
}

void gts_master::cb_change_wview_lr_or_ud( void )
{
	if (cl_gts_gui.menite_wview_main_or_lr_ud->value() == 0) {
		return;
	}

	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		cl_gts_gui.menite_wview_lr_or_ud->clear();
		fl_alert("No Image");
		return;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		cl_gts_gui.menite_wview_lr_or_ud->clear();
		fl_alert("Not RGB Image");
		return;
	}

	/*
		"Pixel Type and Bright"ウインドウの"Pixel Type"選択
			"cl_gts_gui.choice_pixel_type->value()"
		は、
		Scanの画像タイプなので、ここには関係しない
	*/

	/* トレス準備をまだやっていないときは実行 */
	if (this->cl_iip_trac.get_l_channels() < 3L) {
		/* ２値化処理の準備 */
/* ここにくることはあるのか？なぜ、BW,Grayscaleでトレス準備する？
   後日refactoringで整理する　*/
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			cl_gts_gui.menite_wview_lr_or_ud->clear();
			return;
		}

/* なぜ、トレス処理してない?
   後日refactoringで整理する　*/
		/* ２値化処理を実行 */
		//this->_iipg_color_trace_exec();
	}

	/*
		表示準備
			this->_iipg_view_setup()
		はしない。
		既に表示している状態で呼ばれるため
	*/

	/* 画面のlrとud表示変更 */
	if (	cl_gts_gui.menite_wview_lr_or_ud->value() == 0) {
		this->_wview_lr_parallel();
	}
	else {
		this->_wview_ud_parallel();
	}

	/* 表示 */
	this->iipg_view_redraw_();
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
	case E_WVIEW_TYPE_SUB: this->iipg_view_redraw_(); break;
	case E_WVIEW_TYPE_LR_PARALLEL: this->iipg_view_redraw_(); break;
	case E_WVIEW_TYPE_UD_PARALLEL: this->iipg_view_redraw_(); break;
	case E_WVIEW_TYPE_LR_ONION: break;
	case E_WVIEW_TYPE_UD_ONION: break;
	}
}
