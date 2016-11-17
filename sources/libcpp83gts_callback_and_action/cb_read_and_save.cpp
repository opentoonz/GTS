#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h"
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

int gts_master::read_and_save_crnt_( void )
{
	char *filepath;
	int crnt_file_num = this->cl_file_number_list.get_crnt_file_num();
	int crnt_list_num = this->cl_file_number_list.get_crnt_list_num();

	/*------------------------------------------------*/

	/* リストのセンタースクロール */
	cl_gts_gui.selbro_fnum_list->middleline(crnt_list_num);

	/*------------------------------------------------*/

	/* 読み込み(番号に対する)ファイルパスを得る */
	filepath = this->cl_bro_level.cp_filepath_full(crnt_file_num);
	if (nullptr == filepath) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath_full(%d) returns nullptr",
		crnt_file_num
		);
		return NG;
	}

	/* 画像ファイルがないなら読み込みはしないでその番号キャンセル */
	if (!ptbl_dir_or_file_is_exist( filepath )) {
		return OK;
	}

	/* 読み込み元ファイルパス設定 */
	if (OK != this->cl_iip_read.cl_name.set_name(filepath)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.cl_name.set_name(%s) returns NG",
			filepath);
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

	/* ２値化処理を実行 */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return NG;
	}
	this->_iipg_color_trace_exec();

	/*------------------------------------------------*/

	/* Trace保存する(番号に対する)ファイルパスを得る */

	filepath = this->cl_bro_level.cp_filepath(crnt_file_num);
	if (nullptr == filepath) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns nullptr.",
		crnt_file_num
		);
		return NG;
	}

	/* 保存する */
	if (OK != this->_iipg_save(
		&(cl_gts_master.cl_iip_trac),
		filepath,
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
	if (OK != this->cl_file_number_list.marking_trace_file(crnt_list_num)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_file_number_list.marking_trace_file(%d) returns NG",
			crnt_list_num
		);
		return NG;
	}

	/*------------------------------------------------*/

	/* リストの選択解除 */
	this->cl_file_number_list.unselect(crnt_list_num);

	/* level browser listの再表示 */
	this->cl_bro_level.cb_list_redisplay();

	/* 表示 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return NG;
	}
	this->iipg_view_redraw_();

	return OK;
}

/*--------------------------------------------------------*/

void gts_master::cb_read_and_save_start( void )
{
	int	ekey;

	/* 先頭を得る - End設定で選択したフレーム番号をたどっていく */
	this->cl_file_number_list.counter_start(
		cl_gts_master.cl_file_number_list.get_end_type_value()
	);

	/* 最初に番号が選択がない */
	if (this->cl_file_number_list.get_crnt_file_num() < 1) {
		fl_alert("Select number!");
		return;
	}

	/* 保存dir,filehead,extからfilepathを得る */
	if (nullptr == this->cl_bro_level.cp_filepath(
		this->cl_file_number_list.get_crnt_file_num()
	)) {
		pri_funct_err_bttvr(
	"Error : this->cl_bro_level.cp_filepath(%d) returns nullptr."
		, this->cl_file_number_list.get_crnt_file_num()
		);
		return;
	}

	/* 保存するタイプで画像を表示する */
	if ( cl_gts_gui.chkbtn_filter_rgb_color_trace->value() ) {
		/* TracenImage画像のみ表示 */
		cl_gts_master.cb_change_wview_sub();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_sub->setonly();
	}
	else {
		/* ScanImage(メイン)画像のみ表示 */
		cl_gts_master.cb_change_wview_main();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_main->setonly();
	}

	while (1 <= this->cl_file_number_list.get_crnt_list_num()) {
		/* カレントの読み込みと処理と保存をして */
		if (OK != this->read_and_save_crnt_()) {
			pri_funct_err_bttvr(
		 "Error : this->read_and_save_crnt_() returns NG" );
			return;
		}
		/* 次を得る - End設定で選択したフレーム番号をたどっていく */
		this->cl_file_number_list.counter_next(
		 cl_gts_master.cl_file_number_list.get_end_type_value()
		);

		Fl::check();
		ekey = Fl::event_key();

		/* FL_Escapeと'q'と't'は効かない */
		//if (FL_Escape == ekey) {
		//if ('q' == ekey) {
		//if ('t' == ekey) { /* Tで開始し、tで終る */

		if ('e' == ekey) {
			break;
		}
	}
}
