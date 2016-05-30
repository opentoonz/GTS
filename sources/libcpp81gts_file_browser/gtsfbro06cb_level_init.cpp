#include <string.h>
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

int gtsfbro06cb_level::i_init( void )
{
	/* 画像情報表示用テキスト */
	this->init_text_buffer();

	/*
	 * 値の取り出しとCancel用のメモリ
	 */

	/* 01. Dirパス */
	/* ここではデフォルト設定を使う */
	// gtsfbro01path_base.h

	/* 02. file/levelのlist表示切替(Renumberボタンの表示OFF/ONも) */
	this->_i_list_form_memory =
		cl_gts_gui.choice_level_list_form->value();

	/* 03. Level名 */
	this->level_filename_memory(
		cl_gts_gui.strinp_level_file->value()
	);

	/* 04. Level開始番号 */
	this->_i_start_memory =
		(int)cl_gts_gui.valinp_level_start->value();

	/* 05. Level終端番号 */
	this->_i_end_memory   =
		(int)cl_gts_gui.valinp_level_end->value();

	/* 06. 等倍画像表示スイッチ */
	this->_i_x1view_sw_memory =
		cl_gts_gui.ligbut_level_image_x1_sw->value();

	/* 07. 画像全体表示スイッチ */
	this->_i_view_sw_memory =
		cl_gts_gui.ligbut_level_view_sw->value();

	/* 08. _full dirパス */
	this->_rgb_scan_dir_memory(
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	);

	/* 09. RGBスキャン時、トレスを実行し保存するスイッチ */
	this->_i_save_color_trace_level_sw_memory =
		cl_gts_gui.chkbtn_level_rgb_trace_save_sw->value();

	/* 10. dirパス/_full dirパスのブラウジング切替えスイッチ */
	this->_i_rgb_scan_browse_sw_memory =
		cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value();

	/* 11. _full等倍画像表示スイッチ */
	this->_i_info_rgb_sub_sw_memory =
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->value();

	/* GUIにpath設定 */
	this->change_level_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return NG;
	}

	return OK;
}
