#include "ptbl_funct.h"
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

int gts_master::_read_and_save( int i_file_num, int i_list_num )
{
	char *cp_path;

	/*------------------------------------------------*/

	/* リストのセンタースクロール */
	cl_gts_gui.selbro_fnum_list->middleline(i_list_num);

	/*------------------------------------------------*/

	/* 読み込み(番号に対する)ファイルパスを得る */
	/****************if (OK != this->cl_bro_level.i_path_cpy_dir(
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_path_cpy_dir(%s) returns NULL.",
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
		);
		return NG;
	}
	if (OK != this->cl_bro_level.i_lpath_cat_file_for_full(
		cl_gts_gui.strinp_level_file->value(),
		i_file_num,ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_lpath_cat_file_for_full(%s,%d,%d) returns NULL.",
		cl_gts_gui.strinp_level_file->value(),
		i_file_num,ON
		);
		return NG;
	}
	cp_path = this->cl_bro_level.cp_path();***************/

	cp_path = this->cl_bro_level.cp_filepath_full(i_file_num);
	if (NULL == cp_path) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath_full(%d) returns NULL",
		i_file_num
		);
		return NG;
	}

	/* 画像ファイルがないなら読み込みはしないでその番号キャンセル */
	if (!ptbl_dir_or_file_is_exist( cp_path )) {
		/******pri_funct_err_bttvr(
			"Error : <%s> is not exist",cp_path);
		return NG;******/
		return OK;
	}

	/* 読み込み元ファイルパス設定 */
	if (OK != this->cl_iip_read.cl_name.set_name(cp_path)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.cl_name.set_name(%s) returns NG",
			cp_path);
		return NG;
	}

	/* 画像読み込み */
	if (OK != this->cl_iip_read.file()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.file() returns NG" );
		return NG;
	}

	/* 読み込んだ画像がフルカラーでないとエラー */
	if (this->cl_iip_read.get_l_channels() < 3) {
		pri_funct_err_bttvr(
   "Error : this->cl_iip_read.get_l_channels() is less than 3" );
		return NG;
	}

	/*------------------------------------------------*/

	/* 回転処理を実行 */
	if (OK != this->_iipg_rot90(
		&(this->cl_iip_read),
		0	/* 画像コンバート処理のみで、回転はしない */
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return NG;
	}

	/* 画像処理を実行 */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return NG;
	}
	this->_iipg_color_trace_exec();

	/*------------------------------------------------*/

	/* Trace保存する(番号に対する)ファイルパスを得る */
	/*******************if (OK != this->cl_bro_level.i_path_cpy_dir(
		cl_gts_gui.filinp_level_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_path_cpy_dir(%s) returns NULL.",
		cl_gts_gui.filinp_level_dir->value()
		);
		return NG;
	}
	if (OK != this->cl_bro_level.i_lpath_cat_file_by_num(
			cl_gts_gui.strinp_level_file->value(),
			i_file_num,ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_lpath_cat_file_by_num(%s,%d,%d) returns NULL.",
			cl_gts_gui.strinp_level_file->value(),
			i_file_num,ON
		);
		return NG;
	}
	cp_path = this->cl_bro_level.cp_path();***********/

	cp_path = this->cl_bro_level.cp_filepath(i_file_num);
	if (NULL == cp_path) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns NULL.",
		i_file_num
		);
		return NG;
	}

	/* 保存する */
	if (OK != this->_iipg_save(
		&(cl_gts_master.cl_iip_trac),
		cp_path,
// cl_gts_gui.valinp_area_reso->value()
this->cl_iip_read.get_d_tif_dpi_x()
		/* rot90実行後なので(デフォルト)0度とする */
		/* (デフォルト)なしとする、
			&(this->cl_iip_read)は参照しない */
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_save(-) returns NG" );
		return NG;
	}

	/*------------------------------------------------*/

	/* リストにマーク付け */
	if (OK != this->cl_list_access.marking_tgt(i_list_num)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.marking_tgt(%d) returns NG",
			i_list_num
		);
		return NG;
	}

	/*------------------------------------------------*/

	/* リストの選択解除 */
	this->cl_list_access.unselect(i_list_num);

	/* level browser listの再表示 */
	this->cl_bro_level.cb_list_redisplay();

	/* 表示 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return NG;
	}
	this->_iipg_view_redraw();

	return OK;
}

/* 必ず、カレントの番号は有効の状態で、このmethodを呼ぶ */
int gts_master::read_and_save_crnt( void )
{
	if (OK != this->cl_list_access.set_next_number()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.set_next_number() returns NG");
		return NG;
	}

	/* ファイル読み込みと保存を実行する */
	if (OK != this->_read_and_save(
		this->cl_list_access.get_i_crnt_file_num(),
		this->cl_list_access.get_i_crnt_list_num()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_scan_and_save(%d,%d) returns NG",
		this->cl_list_access.get_i_crnt_file_num(),
		this->cl_list_access.get_i_crnt_list_num()
		);
		return NG;
	}

	/* 切抜きはしないのでOFFにしておく */
	/*******this->cl_ogl_view.crop_area(OFF);******/

	return OK;
}

/*--------------------------------------------------------*/

void gts_master::cb_read_and_save_start( void )
{
	int	i_crnt_list_num;
	int	i_key;
	// char *cp_path;

	i_crnt_list_num = this->cl_list_access.set_first_number();
	/*
		プラスはリストを選んだ
		ゼロを返したらリストがない
		マイナスはエラー
	*/

	if (0 == i_crnt_list_num) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.set_first_number() returns zero"
		);
		return;
	}
	else if (i_crnt_list_num < 0) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.set_first_number() returns minus"
		);
		return;
	}

	/* 保存dir,filehead,extが得られるか確認 */
	/**************if (OK != this->cl_bro_level.i_path_cpy_dir(
		cl_gts_gui.filinp_level_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_path_cpy_dir(%s) returns NULL.",
		cl_gts_gui.filinp_level_dir->value()
		);
		return;
	}
	if (OK != this->cl_bro_level.i_lpath_cat_file_by_num(
		cl_gts_gui.strinp_level_file->value(),
		this->cl_list_access.get_i_crnt_file_num(),ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_lpath_cat_file_by_num(%s,%d,%d) returns NULL.",
		cl_gts_gui.strinp_level_file->value(),
		this->cl_list_access.get_i_crnt_file_num(),ON
		);
		return;
	}***************/
	// cp_path = this->cl_bro_level.cp_path();

	if (NULL == this->cl_bro_level.cp_filepath(
		this->cl_list_access.get_i_crnt_file_num()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns NULL.",
		this->cl_list_access.get_i_crnt_file_num()
		);
		return;
	}

	/* RGB画像の処理となるので、モードを自動切替えする */
	cl_gts_gui.choice_pixel_type->value(2);

	while (0 < this->cl_list_access.get_i_crnt_list_num()) {
		/* カレントの読み込みと処理と保存をして */
		if (OK != this->read_and_save_crnt()) {
			pri_funct_err_bttvr(
		 "Error : this->read_and_save_crnt() returns NG" );
			return;
		}
		this->cl_list_access.set_next_to_crnt_number();

		Fl::check();
		i_key = Fl::event_key();

		/* FL_Escapeと'q'と't'は効かない */
		//if (FL_Escape == i_key) {
		//if ('q' == i_key) {
		//if ('t' == i_key) { /* Tで開始し、tで終る */

		if ('e' == i_key) {
			break;
		}
	}
}
