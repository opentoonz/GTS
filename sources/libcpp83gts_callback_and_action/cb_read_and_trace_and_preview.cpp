#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_read_and_trace_and_preview( void )
{
	/* Regacy→将来削除:画像大処理重用操作の時は何もしない */
	if (cl_gts_gui.menite_heavy_view_mode_in->value() != 0) {
		return;
	}

	/*------ ファイル番号を得て、その位置にスクロールする ------*/

	/* File Number Listの選択の先頭項目を得る... */
	this->cl_file_number_list.counter_start(
		cl_gts_master.cl_file_number_list.get_end_type_value()
	);

	/* ...選択がない */
	if (this->cl_file_number_list.get_crnt_file_num() < 1) {
		// fl_alert("Select number!");
/* alertは必要なら呼出元で出す */
		return;
	}
	const int crnt_file_num =
		this->cl_file_number_list.get_crnt_file_num();

	/* 選択の先頭を中心位置にスクロール */
	cl_gts_gui.selbro_fnum_list->middleline(
		this->cl_file_number_list.get_crnt_list_num()
	);

	/*------ _full付きファイルを優先してファイルの読込み ------*/

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

		/* 画面は空白表示する指定(データは残っている) */
		cl_gts_master.cl_ogl_view.no_view_canvas();
		/* 画面クリア設定 */
		cl_gts_master.cl_ogl_view.clear_opengl(
			cl_gts_gui.opengl_view->w(),
			cl_gts_gui.opengl_view->h()
		);
		/* 画面クリア */
		cl_gts_gui.opengl_view->flush();

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

	/*------ 読込んだ画像を回転、２値化、表示する ------*/
	/* ファイルからの読み込み時は回転処理はしない(ゼロ度回転をする) */
	this->rot_and_trace_and_preview_(
		&(this->cl_iip_read), 0 ,before_channels
	);
}

void gts_master::rot_and_trace_and_preview_(
	iip_canvas *parent
	, int rotate_per_90_type 
	, const long before_channels 
	, const bool crop_sw
	, const bool force_view_scanimage_sw
)
{
	/* 回転処理 */
	if (OK != this->_iipg_rot90( parent, rotate_per_90_type )) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return;
	}

	/* RGB画像のときは2値化(トレス)処理 */
	if (3L <= parent->get_l_channels()) {
		if (OK != this->_iipg_color_trace_setup()) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_color_trace_setup() returns NG" );
			return;
		}
		this->_iipg_color_trace_exec();
	}

	/* 表示準備 */
	if (OK != this->_iipg_view_setup( crop_sw ?ON :OFF )) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}

	/* 表示準備2 */
	if (force_view_scanimage_sw	/* ScanImage表示強制指定のとき */
	||  parent->get_l_channels() < 3L) {/* あるいは、BW,Grayscale画像 */
		/* ScanImage(メイン)画像のみ表示 */
		this->_wview_main();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_main->setonly();
	} else
	if (3L <= parent->get_l_channels()	/* 今回RGB画像 */
	&&  before_channels < 3L) {	/* かつ、以前RGB以外なら表示切替 */
		/* 左右分割表示 */
		this->_wview_lr_parallel();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_lr->setonly();
	}

	/* 表示 */
	this->iipg_view_redraw_();

	/* color trace histogram表示設定 */
	if (3L <= parent->get_l_channels()) {
		/* color trace histogram maxの設定 */
		this->cl_color_trace_enhancement.src_set_histogram_max();

		/* color trace histogram windowの再描画 */
		cl_gts_gui.window_hab_histogram->redraw();
	}
}

