#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* 4→5  アプリ：ソースをイネーブルにする
	1. イネーブルを発行する
	2. 「TWAIN 画面(※)」を表示(非表示)
	(※)エンドユーザから直接各種設定及び転送(?)まで実行できる
	  ダイアログボックス
	3. 状態4(Source Open)から状態5(Source Enable)となる
	4. ソースは転送準備にかかる
	5. 準備が整うとソースはイベント(MSG_XFERREADY)を発生する
	6. 状態5(Source Enable)から状態6(Transfer Ready)となる

TWAIN GUI画面表示
	this->_tw_ui.hParent = this->_hWnd;
	this->_tw_ui.ShowUI  = TRUE; --> TWAIN 画面を表示する
	this->_tw_ui.ModalUI = TRUE;

TWAIN CUI実行
	this->_tw_ui.hParent = NULL;
	this->_tw_ui.ShowUI  = FALSE; --> TWAIN 画面を非表示(※)とする
	this->_tw_ui.ModalUI = FALSE;
	(※)この場合、TWAIN ドライバ側が画面非表示に対応
	    している必要がある。
*/
int tw_win_l3_dsi::state4to5( HWND h_wnd, unsigned short us_show_ui, unsigned short us_model_ui )
{
	TW_UINT16 rc;

	/* 状態(state)が4でないときは何もしない */
	if (TWAIN_STATE4_SOURCE_OPENED != this->twain_state) {
		return OK;
	}
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "tw_win_l3_dsi::state4to5()" );
	}

	this->_tw_ui.hParent = h_wnd;
	this->_tw_ui.ShowUI  = us_show_ui;
	this->_tw_ui.ModalUI = us_model_ui;

	rc = this->ds_entry(
		DG_CONTROL, DAT_USERINTERFACE, MSG_ENABLEDS,
		(TW_MEMREF)&(this->_tw_ui)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_USERINTERFACE,MSG_ENABLEDS", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* 状態(state)を5に進める */
	this->twain_state = TWAIN_STATE5_SOURCE_ENABLE;
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
		"twain state 4 --> 5 : source enable" );
		pri_funct_msg_ttvr(
		" _tw_ui.hParent is 0x%p, ShowUI is %s, ModalUIis %s",
			this->_tw_ui.hParent,
			(TRUE==this->_tw_ui.ShowUI)?"TRUE":"FALSE",
			(TRUE==this->_tw_ui.ModalUI)?"TRUE":"FALSE"
		);
	}

	return OK;
}
