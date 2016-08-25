#include "ptbl_funct.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_read_and_trace( void )
{
	int i_crnt_list_num;
	char *cp_path;

	i_crnt_list_num = this->cl_file_number_list.set_first_number();

	/* ゼロは、リストがない */
	if (0 == i_crnt_list_num) {
		pri_funct_err_bttvr(
	 "Error : this->cl_file_number_list.set_first_number() returns zero"
		);
		return;
	}
	/* マイナスは、リストのチェックでエラーが起きた */
	else if (i_crnt_list_num < 0) {
		pri_funct_err_bttvr(
	 "Error : this->cl_file_number_list.set_first_number() returns minus"
		);
		return;
	}
	/* プラスはリストを選んだ */

	/*------------------------------------------------*/

	/* リストのセンタースクロール */
	cl_gts_gui.selbro_fnum_list->middleline(i_crnt_list_num);

	/*------------------------------------------------*/

	/* 読み込み(番号に対する)ファイルパスを得る */
	/**********if (OK != this->cl_bro_level.i_path_cpy_dir(
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_path_cpy_dir(%s) returns NULL.",
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
		);
		return;
	}
	if (OK != this->cl_bro_level.i_lpath_cat_file_for_full(
		cl_gts_gui.strinp_level_file->value(),
		this->cl_file_number_list.get_crnt_file_num(),ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_lpath_cat_file_for_full(%s,%d,%d) returns NULL.",
		cl_gts_gui.strinp_level_file->value(),
		this->cl_file_number_list.get_crnt_file_num(),ON
		);
		return;
	}
	cp_path = this->cl_bro_level.cp_path();**********/


	cp_path = this->cl_bro_level.cp_filepath_full(
		this->cl_file_number_list.get_crnt_file_num()
	);
	if (NULL == cp_path) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath_full(%d) returns NULL.",
		this->cl_file_number_list.get_crnt_file_num()
		);
		return;
	}

	/* 画像ファイルがないなら読み込みはしない */
	if (!ptbl_dir_or_file_is_exist( cp_path )) {
		pri_funct_err_bttvr(
			"Error : <%s> is not exist",cp_path);
		return;
	}

	/* 読み込み元ファイルパス設定 */
	if (OK != this->cl_iip_read.cl_name.set_name(cp_path)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.cl_name.set_name(%s) returns NG",
			cp_path);
		return;
	}

	/* 画像読み込み */
	if (OK != this->cl_iip_read.file()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.file() returns NG" );
		return;
	}

	/* 回転処理はしない(ゼロ度回転) */
	if (OK != this->_iipg_rot90(
		&(this->cl_iip_read),
		0
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return;
	}

	/* データが、RGBフルカラーでなければ実行しない */
	if (this->cl_iip_read.get_l_channels() < 3L) {
		return;
	}

	/* RGB画像の処理となるので、モードを自動切替えする */
	cl_gts_gui.choice_pixel_type->value(2);

	/* トレスを実行 */
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

	/* color trace histogram windowの再描画 */
	cl_gts_gui.window_hab_histogram->redraw();

	/* トレス用画面分割表示 */
	this->_wview_lr_parallel();
}
