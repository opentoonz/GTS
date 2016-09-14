#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_read_and_trace( void )
{
	char *filepath;

	/* 先頭を得る - End設定で選択したフレーム番号をたどっていく */
	this->cl_file_number_list.counter_start(
		cl_gts_master.cl_file_number_list.get_end_type_value()
	);

	/* 最初に番号が選択がない */
	if (this->cl_file_number_list.get_crnt_file_num() < 1) {
		fl_alert("Select number!");
		return;
	}

	//--------------------------------------------------

	/* リストのセンタースクロール */
	cl_gts_gui.selbro_fnum_list->middleline(
		this->cl_file_number_list.get_crnt_list_num()
	);

	//--------------------------------------------------

	/* 読み込み(番号に対する)ファイルパスを得る */
	filepath = this->cl_bro_level.cp_filepath_full(
		this->cl_file_number_list.get_crnt_file_num()
	);
	if (NULL == filepath) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath_full(%d) returns NULL.",
		this->cl_file_number_list.get_crnt_file_num()
		);
		return;
	}

	/* 画像ファイルがないなら読み込みはしない */
	if (!ptbl_dir_or_file_is_exist( filepath )) {
		pri_funct_err_bttvr(
			"Error : <%s> is not exist",filepath);
		return;
	}

	/* 読み込み元ファイルパス設定 */
	if (OK != this->cl_iip_read.cl_name.set_name(filepath)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.cl_name.set_name(%s) returns NG",
			filepath);
		return;
	}

	/* 画像読み込み */
	if (OK != this->cl_iip_read.file()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.file() returns NG" );
		return;
	}

	/* データが、RGBフルカラーでなければ実行しない */
	if (this->cl_iip_read.get_l_channels() < 3L) {
		pri_funct_err_bttvr(
   "Error : this->cl_iip_read.get_l_channels() smaller than 3L" );
		return;
	}

	//--------------------------------------------------

	/* 回転処理はしない(ゼロ度回転) */
	if (OK != this->_iipg_rot90(
		&(this->cl_iip_read),
		0
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return;
	}

	/* RGB画像の処理となるので、モードを自動切替えする */
	//cl_gts_gui.choice_pixel_type->value(2);

	/* トレスを実行 */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return;
	}
	this->_iipg_color_trace_exec();

	//--------------------------------------------------

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
