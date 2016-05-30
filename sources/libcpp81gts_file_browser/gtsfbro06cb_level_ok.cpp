#include <stdlib.h>	/* atoi() */
#include <string.h>
#include <FL/fl_ask.H>	/* fl_alert(-) */
#include "gtsfbro06cb_level.h"
#if !defined GTS_DEBUG
# include "gts_master.h"
#endif
#include "gts_gui.h"

void gtsfbro06cb_level::level_filename_memory( const char *ccp_fname )
{
	/* strncpy()は、
	最初のnバイトの中にNULL文字が無ければ、
	コピーの結果としてできる文字列は
	NULLで終端していないものになる。
	*/
	strncpy(
	this->level_filename_memory_ ,ccp_fname ,PTBL_PATH_MAX
	);
	this->level_filename_memory_[PTBL_PATH_MAX-1] = '\0';
}
void gtsfbro06cb_level::_rgb_scan_dir_memory( const char *ccp_fname )
{
	strncpy(
	this->_ca_rgb_scan_dir_memory,ccp_fname,PTBL_PATH_MAX);
	this->_ca_rgb_scan_dir_memory[PTBL_PATH_MAX-1] = '\0';
}

void gtsfbro06cb_level::cb_ok( void )
{
	const char *ccp_file;
	int i_sta,i_end;

	ccp_file = cl_gts_gui.strinp_level_file->value();
	if ((NULL == ccp_file) || ('\0' == ccp_file[0])) {
		pri_funct_err_bttvr(
	  "Error : cl_gts_gui.strinp_level_file->value() is null string"
	  	);
		fl_alert("bad level name");
		return;
	}

	i_sta = (int)cl_gts_gui.valinp_level_start->value();
	if ((i_sta < 1) || (9999 < i_sta)) {
		pri_funct_err_bttvr(
	    "Error : cl_gts_gui.valinp_level_start->value()<%d> is zero or minus",
			i_sta);
		fl_alert("bad level start number");
		return;
	}

	i_end = (int)cl_gts_gui.valinp_level_end->value();
	if ((i_end < 1) || (9999 < i_end)) {
		pri_funct_err_bttvr(
	    "Error : cl_gts_gui.valinp_level_end->value()<%d> is zero or minus",
			i_end);
		fl_alert("bad level end number");
		return;
	}
	if (i_end < i_sta) {
		pri_funct_err_bttvr(
 "Error : cl_gts_gui.valinp_level_start->value()<%d> is bigger than end<%d>",
			i_sta, i_end);
		fl_alert("level start is bigger than end number");
		return;
	}

#if !defined GTS_DEBUG
	/* 以前のリストをすべて削除 */
	cl_gts_master.cl_list_access.remove_all();

	/* ファイルの存在をチェックしながらリストを設定 */
	cl_gts_master.cl_image_mark_access.make_fnum_list_with_chk_mark(
		i_sta, i_end
	);

	/* frame number listにlevel名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
		cl_gts_master.cl_bro_level.cp_levelname()
	);

	/* 新たに作ったリストは全て選択状態にする */
	cl_gts_master.cl_list_access.select_all();

	/* ファイル名表示 */
	cl_gts_master._print_window_headline();

	/* 切抜きはしないのでOFFにしておく */
	//cl_gts_master.cl_ogl_view.crop_area(OFF);
#endif

	/*
	 * 値の取り出しとCancel用のメモリ
	 */

	/* 01. Dirパス */
	if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_level_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
		cl_gts_gui.filinp_level_dir->value()
		);
		return;
	}
	this->v_path_memory();

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
		cl_gts_gui.chkbtn_level_color_trace_save_sw->value();

	/* 10. dirパス/_full dirパスのブラウジング切替えスイッチ */
	this->_i_rgb_scan_browse_sw_memory =
		cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value();

	/* 11. _full等倍画像表示スイッチ */
	this->_i_info_rgb_sub_sw_memory =
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->value();

	/* levelの終了に伴うx1view windowの閉じでは、
	表示スイッチをOFFにしない */
	cl_gts_gui.window_x1view->hide(); /* x1 Window閉じる */
	cl_gts_gui.menite_level->clear(); /* menuのcheckを消す */
	cl_gts_gui.window_level->hide();  /* Window閉じる */
}
