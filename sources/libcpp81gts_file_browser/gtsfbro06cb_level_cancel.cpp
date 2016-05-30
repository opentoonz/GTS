#include <string.h> /* strncpy() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::_cancel( void )
{
	/*
	 * Cancel用のメモリから画面を元に戻す
	 */

	/* 01. Dirパス */
	cl_gts_gui.filinp_level_dir->value(
		this->cp_memory()
	);
	cl_gts_gui.filinp_level_dir->position(
		strlen(this->cp_memory())
	);

	/* 02. file/levelのlist表示切替(Renumberボタンの表示OFF/ONも) */
	cl_gts_gui.choice_level_list_form->value(
		this->_i_list_form_memory
	);
	if (0 == cl_gts_gui.choice_level_list_form->value()) {
		cl_gts_gui.button_level_shift_number->hide();
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->hide();
	} else {
		cl_gts_gui.button_level_shift_number->show();
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->show();
	}

	/* 03. Level名 */
	cl_gts_gui.strinp_level_file->value(
		this->level_filename_memory_
	);

	/* 04. Level開始番号 */
	cl_gts_gui.valinp_level_start->value(
		(double)this->_i_start_memory );

	/* 05. Level終端番号 */
	cl_gts_gui.valinp_level_end->value(
		(double)this->_i_end_memory );

	/* 06. 等倍画像表示スイッチ */
	cl_gts_gui.ligbut_level_image_x1_sw->value(
		this->_i_x1view_sw_memory
	);

	/* 07. 画像全体表示スイッチ */
	cl_gts_gui.ligbut_level_view_sw->value(
		this->_i_view_sw_memory
	);

	/* 08. _full dirパス */
	cl_gts_gui.filinp_level_rgb_scan_dir->value(
		this->_ca_rgb_scan_dir_memory
	);
	cl_gts_gui.filinp_level_rgb_scan_dir->position(
		strlen(this->_ca_rgb_scan_dir_memory)
	);

	/* 09. RGBスキャン時、トレスを実行し保存するスイッチ */
	cl_gts_gui.chkbtn_level_color_trace_save_sw->value(
		this->_i_save_color_trace_level_sw_memory
	);
	/* 10. dirパス/_full dirパスのブラウジング切替えスイッチ */
	cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value(
		this->_i_rgb_scan_browse_sw_memory
	);
	if (cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
		cl_gts_gui.filinp_level_dir->deactivate();
		cl_gts_gui.filinp_level_rgb_scan_dir->activate();
	} else {
		cl_gts_gui.filinp_level_dir->activate();
		cl_gts_gui.filinp_level_rgb_scan_dir->deactivate();
	}

	/* 11. _full等倍画像表示スイッチ */
	cl_gts_gui.ligbut_level_info_rgb_sub_sw->value(
		this->_i_info_rgb_sub_sw_memory
	);

	/* listを再表示 */
	if (OK != this->change_level_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list(%s) returns NG" );
		return;
	}
}
void gtsfbro06cb_level::cb_cancel( void )
{
	this->_cancel();

	/* add 2013-09-25 level名からfileが上書きなら注意表示 */
	this->cb_level_name();

	/* levelの終了に伴うx1view windowの閉じでは、
	表示スイッチをOFFにしない */
	cl_gts_gui.window_x1view->hide(); /* x1 Window閉じる */
	cl_gts_gui.menite_level->clear(); /* menuのcheckを消す */
	cl_gts_gui.window_level->hide();  /* Window閉じる */
}
