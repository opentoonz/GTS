#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_read_and_trace_and_preview( void )
{
	/* "View Action for Heavy"メニューがなくなったらここは削除 */
	if (cl_gts_gui.menite_heavy_view_mode_in->value() != 0) {
		return;
	}

	/* File Number Listの選択の先頭項目を得る */
	this->cl_file_number_list.counter_start(
		cl_gts_master.cl_file_number_list.get_end_type_value()
	);

	/* 選択がない */
	if (this->cl_file_number_list.get_crnt_file_num() < 1) {
		// fl_alert("Select number!");
/* alertは必要なら呼出元で出す */
		return;
	}
	const int crnt_file_num =
		this->cl_file_number_list.get_crnt_file_num();

	//----------

	/* 選択の先頭を中心位置にスクロール */
	cl_gts_gui.selbro_fnum_list->middleline(
		this->cl_file_number_list.get_crnt_list_num()
	);

	//----------

	/* 番号に対する_full付きのファイルパスを得ることはできるか */
	if (nullptr == this->cl_bro_level.cp_filepath_full(crnt_file_num)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath_full(%d) returns nullptr."
			, crnt_file_num
		);
		return;
	}

	/* 番号に対する_full無しファイルパスを得ることはできるか */
	if (nullptr == this->cl_bro_level.cp_filepath( crnt_file_num )) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns nullptr."
			, crnt_file_num
		);
		return;
	}

	/* 各画像ファイルの存在確認 */
	const bool full_sw = (1==ptbl_dir_or_file_is_exist( 
		this->cl_bro_level.cp_filepath_full( crnt_file_num )
	));
	const bool nofull_sw = (1==ptbl_dir_or_file_is_exist( 
		this->cl_bro_level.cp_filepath( crnt_file_num )
	));

	/* どちらの画像ファイルも存在しない */
	if (!full_sw && !nofull_sw) {
		pri_funct_err_bttvr( "Warning : <%s> and <%s> is not exist"
			,this->cl_bro_level.cp_filepath_full(crnt_file_num)
			,this->cl_bro_level.cp_filepath( crnt_file_num )
		);
/* 画面は空白表示するべき */
		return;
	}

	/* _full付きファイルを優先してどちらかのファイルパスを選ぶ */
	char* filepath;
	if (full_sw) {
	 filepath = this->cl_bro_level.cp_filepath_full( crnt_file_num );
	} else {
	 filepath = this->cl_bro_level.cp_filepath( crnt_file_num );
	}

	/* 読込前に画像のタイプを得ておく */
	const long before_channels = this->cl_iip_read.get_l_channels();

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

	//----------

	/* ファイルからの読み込み時は回転処理はしない(ゼロ度回転をする) */
	if (OK != this->_iipg_rot90(
		&(this->cl_iip_read),
		0
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return;
	}

	//----------

	/* RGB画像のときは */
	if (3L <= this->cl_iip_read.get_l_channels()) {
		/* 2値化(トレス)を実行 */
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			return;
		}
		this->_iipg_color_trace_exec();
	}

	//----------

	/* 表示準備 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}

	/* 分割表示とメイン表示の切替 */
	if (3L <= this->cl_iip_read.get_l_channels()) {
	 if (before_channels< 3L) {/* 以前はRGB以外の画像だったら表示切替 */
		cl_gts_gui.menite_wview_main_or_lr_ud->set();/* ON(lr/ud) */
		if (cl_gts_gui.menite_wview_lr_or_ud->value()==0) {
			this->_wview_lr_parallel();
		}
		else {
			this->_wview_ud_parallel();
		}
	 }
	}
	/* BW,Grayscale画像のときは */
	else {
		cl_gts_gui.menite_wview_main_or_lr_ud->clear();/* OFF(main) */
		/* メインのみ画面表示 */
		this->_wview_main();
	}

	/* 表示 */
	this->iipg_view_redraw_();

	/* color trace histogram表示設定 */
	if (3L <= this->cl_iip_read.get_l_channels()) {
		/* color trace histogram maxの設定 */
		this->cl_color_trace_enhancement.src_set_histogram_max();

		/* color trace histogram windowの再描画 */
		cl_gts_gui.window_hab_histogram->redraw();
	}
}
