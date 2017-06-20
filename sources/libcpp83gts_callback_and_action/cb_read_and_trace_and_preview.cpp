#include <fstream>	//std::ifstream
#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_number_read_and_trace_and_preview( void )
{
	/*------ ファイル番号を得て、その位置にスクロールする ------*/

	/* File Number Listの選択の先頭項目を得る... */
	this->cl_number.counter_start(
		cl_gts_master.cl_number.get_end_type_value()
	);

	/* ...選択がない */
#if 0
	if (this->cl_number.get_crnt_file_num() < 1) {
		// fl_alert("Select number!");
/* alertは必要なら呼出元で出す */
		return;
	}
#endif
	const int crnt_file_num =
		this->cl_number.get_crnt_file_num();

	/* 選択の先頭を中心位置にスクロール */
	cl_gts_gui.selbro_number_list->middleline(
		this->cl_number.get_crnt_list_num()
	);

	/*------ ファイルパス ------*/

	std::string fpath_open;
	if ( this->cl_number.is_scan() ) {
	 fpath_open = this->cl_scan_and_save.get_save_path(crnt_file_num);
	} else
	if ( this->cl_number.is_trace() ) {
	 fpath_open = this->cl_trace_files.get_open_path(crnt_file_num);
	} else {
		fl_alert("Click [Set Number]!");
		return;
	}

	this->cb_read_and_trace_and_preview( fpath_open );
}
void gts_master::cb_read_and_trace_and_preview( 
	const std::string& fpath_open
)
{
	/* 番号に対するファイルパスを得ることはできるか */
	if (fpath_open.empty()) {
		pri_funct_err_bttvr(
   "Error : fpath_open(%s) returns nullptr."
	  , fpath_open.c_str()
		);
		return;
	}

	/* 画像ファイル存在しない */
	if (!ptbl_dir_or_file_is_exist(
		const_cast<char *>(fpath_open.c_str())
	)) {
		pri_funct_err_bttvr( "Warning : <%s> is not exist"
			,fpath_open.c_str()
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

	/*------ ファイルの読込み ------*/

	/* 読込前に画像のタイプを得ておく */
	//const long before_channels = this->cl_iip_read.get_l_channels();

	/* 読み込み元ファイルパス設定 */
	if (OK != this->cl_iip_read.cl_name.set_name(fpath_open.c_str())) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.cl_name.set_name(%s) returns NG",
			fpath_open.c_str());
		return;
	}

	/* 画像読み込み */
	if (OK != this->cl_iip_read.file()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_read.file() returns NG" );
		return;
	}

	/*------ 画像を回転、２値化、ドットノイズ消去、表示する ------*/
	/* ファイルからの読み込み時は回転処理はしない(ゼロ度回転をする) */
	this->rot_and_trace_and_enoise_and_preview(
		&(this->cl_iip_read), 0
	);

	/* Crop以外の画像表示をした場合 */
	this->cl_area_and_rot90.reset_dpi_to_zero_by_scan_or_preview();
}

/* (画像生成(Scan/Open)以外の)再処理、再表示 */
void gts_master::cb_rot_trace_enoise_preview( void )
{
	/* ファイル読込後の再表示 */
	if ( &(this->cl_iip_read) == this->cl_iip_ro90.get_clp_parent() ) {
		/* 画像を回転、２値化、ドットノイズ消去、表示する */
		this->rot_and_trace_and_enoise_and_preview(
			&(this->cl_iip_read)
			,0
		);
	}
	else
	/* スキャン後の再表示 */
	if ( this->cl_iip_scan.get_clp_canvas()
	==   this->cl_iip_ro90.get_clp_parent() ) {
		/* 画像を回転、２値化、ドットノイズ消去、表示する */
		this->rot_and_trace_and_enoise_and_preview(
			this->cl_iip_scan.get_clp_canvas()
			,cl_gts_gui.choice_rot90->value()
		);
	}
}

//------------------------------------------------------------

void gts_master::rot_and_trace_and_enoise_and_preview(
	iip_canvas *parent
	, int rotate_per_90_type 
	, const bool crop_sw
	, const bool force_view_scanimage_sw
)
{
	this->rot_and_trace_and_enoise( parent , rotate_per_90_type );
	this->redraw_image( parent , crop_sw , force_view_scanimage_sw );
}
int gts_master::rot_and_trace_and_enoise( // Rot90 and Effects
	iip_canvas *parent
	, int rotate_per_90_type 
)
{
	/* 回転処理 */
	if (OK != this->_iipg_rot90( parent, rotate_per_90_type )) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return NG;
	}

	/* Effect Node Treeを繋ぎ、準備する */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return NG;
	}
	/* 2値化(トレス)処理とドットノイズ消去、あるいは画像受継ぎ処理 */
	this->_iipg_color_trace_exec();

	return OK;
}
int gts_master::redraw_image(
	iip_canvas *parent
	, const bool crop_sw
	, const bool force_view_scanimage_sw
)
{
	/* 表示準備 */
	if (OK != this->_iipg_view_setup( crop_sw ?ON :OFF )) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return NG;
	}

	/* 表示準備2 */
	if (force_view_scanimage_sw	/* ScanImage表示強制指定のとき */
	||  parent->get_l_channels() < 3L) {/* あるいは、BW,Grayscale画像 */
		/* ScanImage(メイン)画像のみ表示 */
		this->_wview_main();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_main->setonly();
	} /* それ以外の場合は現在の表示モードを維持する */

	/* 表示 */
	cl_gts_gui.opengl_view->redraw(); /* 画像再表示 */

	/* color trace histogram表示設定 */
	if (3L <= parent->get_l_channels()) {
		/* color trace histogram maxの設定 */
		this->cl_color_trace_enhancement.src_set_histogram_max();

		/* color trace histogram windowの再描画 */
		cl_gts_gui.window_trace_input_color->flush();
	}
	return OK;
}

