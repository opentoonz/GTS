#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/*--------------------------------------------------------*/
int gts_master::scan_and_save_( void )
{
	const int list_num = this->cl_file_number_list.get_crnt_list_num();
	const int file_num = this->cl_file_number_list.get_crnt_file_num();
	const char* cp_path = nullptr;
	iip_canvas* clp_scan = nullptr;

	/* 01 フレーム番号(list_num)を表示するようリストをスクロール */
	cl_gts_gui.selbro_fnum_list->middleline(list_num);

	/* 02 スキャンを実行 */
	clp_scan = this->_iipg_scan();
	if (nullptr == clp_scan) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_scan() returns nullptr" );
		return NG;
	}

	/* 03 回転処理を実行 */
	if (OK != this->_iipg_rot90(
		clp_scan ,cl_gts_gui.choice_rot90->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return NG;
	}

	/* 04 保存する(番号に対する)ファイルパスを得る */
	if (3L <= this->cl_iip_ro90.get_l_channels() &&
	cl_gts_gui.chkbtn_level_rgb_with_full_sw->value() == 1
	) {
		/* RGB画像(専用の名前)(_full付)(A_full.0001.tif) */
		/* 読み込み(番号に対する)ファイルパスを得る */
		cp_path = this->cl_bro_level.cp_filepath_full( file_num );
		if (cp_path == nullptr) {
			pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath_full(%d) returns nullptr."
				, file_num );
			return NG;
		}
	} else {
		/* BW,Grayscale,RGB(通常の名前)は
		ノーマルな名前(A.0001.tif)で保存 */
		cp_path = this->cl_bro_level.cp_filepath( file_num );
		if (cp_path == nullptr) {
			pri_funct_err_bttvr(
	"Error : this->cl_bro_level.cp_filepath(%d) returns nullptr."
				, file_num );
			return NG;
		}
	}

	/* 05 BWか、Grayscaleか、RGBで保存SWがONのどれかの場合 */
	if ((this->cl_iip_ro90.get_l_channels() < 3L) ||//BW or Grayscale
	    (this->cl_iip_ro90.get_l_channels() == 3L &&//RGB & SW is ON
	     cl_gts_gui.chkbtn_level_rgb_full_save_sw->value() == 1
	    )
	) {
	 /* スキャン画像保存 */
	 if (OK != this->_iipg_save(
		&(this->cl_iip_ro90),
		cp_path,
		cl_gts_gui.valinp_area_reso->value()
		/* 回転値はゼロ固定にする */
	 ) ) {
		pri_funct_err_bttvr(
	 "Error : this->_iip_save(-) returns NG" );
		return NG;
	 }

	 /* リストにScanimage(src)保存済マーク付け "0000" --> "0000 S" */
	 if (OK != this->cl_file_number_list.marking_scan_file(list_num)) {
		pri_funct_err_bttvr(
	  "Error : this->cl_file_number_list.marking_scan_file(%d) returns NG",
			list_num
		);
		return NG;
	 }
	}

	/*------------------------------------------------*/
	/* 06 RGB画像でトレス画像保存SWがONの場合 */
	if (	(this->cl_iip_ro90.get_l_channels() == 3L) &&
		(cl_gts_gui.chkbtn_level_rgb_trace_save_sw->value() == 1)
	) {

	 /* ２値化処理の準備 */
	 if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	  "Error : this->_iipg_color_trace_setup() returns NG" );
		return NG;
	 }

	 /* ２値化処理を実行 */
	 this->_iipg_color_trace_exec();

	 /* ２値化画像を保存する(番号に対する)ファイルパスを得る */
	 cp_path = this->cl_bro_level.cp_filepath( file_num );
	 if (NULL == cp_path) {
		pri_funct_err_bttvr(
	  "Error : this->cl_bro_level.cp_filepath(%d) returns NULL."
	 		, file_num
		);
		return NG;
	 }

	 /* ２値化画像を保存する */
	 if (OK != this->_iipg_save(
		&(cl_gts_master.cl_iip_trac)
		, cp_path , cl_gts_gui.valinp_area_reso->value()
		/* rot90実行後なので(デフォルト)0度とする */
	 ) ) {
		pri_funct_err_bttvr(
	  "Error : this->_iipg_save(-) returns NG" );
		return NG;
	 }

	 /* リストにTracenimage(tgt)保存済マーク付け "0000" --> "0000 T" */
	 if (OK != this->cl_file_number_list.marking_trace_file(list_num)) {
		pri_funct_err_bttvr(
	  "Error : this->cl_file_number_list.marking_trace_file(%d) returns NG"
	 		, list_num
		);
		return NG;
	 }
	}
	/*------------------------------------------------*/

	/* 08 リストの選択解除 */
	this->cl_file_number_list.unselect(list_num);

	/* 09 level browser listの(保存したファイルも含めて)再表示 */
	this->cl_bro_level.cb_list_redisplay();

	/* 10 再表示準備 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return NG;
	}

	/* 11 再表示 */
	this->iipg_view_redraw_();

	return OK;
}

void gts_master::set_next_scan_info_(
	const int file_prev ,const int file_next
)
{
	char	ca8_but[8];

	(void)sprintf( ca8_but, "%d", file_prev );
	cl_gts_gui.norout_crnt_scan_number->value(ca8_but);

	(void)sprintf( ca8_but, "%d", file_next );
	cl_gts_gui.norout_next_scan_number->value(ca8_but);

	cl_gts_gui.norout_crnt_scan_level->value(
		this->cl_bro_level.cp_levelname()
	);
}

/* 必ず、カレントの番号は有効の状態で、このmethodを呼ぶ */
int gts_master::next_scan_and_save_( void )
{
	/* GUIのリストから処理する番号を得ておく */
	if (OK != this->cl_file_number_list.set_next_number()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_file_number_list.set_next_number() returns NG");
		return NG;
	}

	/* スキャンと保存を実行する */
	if (OK != this->scan_and_save_()) {
		/* 次のスキャン番号をキャンセルしてエラーリターン */
		this->cl_file_number_list.reset_next_number();

		pri_funct_err_bttvr(
	 "Error : this->scan_and_save_(%d,%d) returns NG",
		this->cl_file_number_list.get_crnt_list_num()
		, this->cl_file_number_list.get_crnt_file_num()
		);

//std::string str("Critical Error!\nSave Config and Restart!");
//fl_alert(str.c_str());

		return NG;
	}

	/* 切抜きはしないのでOFFにしておく */
	this->cl_ogl_view.crop_area(OFF);

	/* 次のフレーム番号があるなら、
	次の処理を促すwindowの設定をしておく */
	if (0 < this->cl_file_number_list.get_next_file_num()) {
		this->set_next_scan_info_(
		 this->cl_file_number_list.get_crnt_file_num(),
		 this->cl_file_number_list.get_next_file_num()
		);
	}

	return OK;
}

int gts_master::cb_scan_and_save_start_child_( void )
{
	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (0 < this->cl_file_number_list.get_crnt_file_num()) {
	 /* この中でnext_file_numセットしている */
	 if (OK != this->next_scan_and_save_()) {
		pri_funct_err_bttvr(
	  "Error : this->next_scan_and_save_() returns NG" );

// std::string str("Error of scaning!\nSave Config and Restart!";
// fl_alert(str.c_str());
		return NG;
	 }
	}
	return OK;
}

int gts_master::cb_scan_and_save_next_child_( void )
{
	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (0 < this->cl_file_number_list.get_crnt_file_num()) {
	 /* この中でnext_file_numセットしている */
	 if (OK != this->next_scan_and_save_()) {
		/*
		ここでエラーになると次の番号がカレントに
		なってしまうので元に戻す
	this->cl_file_number_list.set_next_to_crnt_number();
		と対で使うこと
		*/
		this->cl_file_number_list.reset_next_to_crnt_number();

		pri_funct_err_bttvr(
	  "Error : this->next_scan_and_save_() returns NG" );
		return NG;
	 }
	}
	return OK;
}

/*--------------------------------------------------------*/

void gts_master::cb_scan_and_save_start( void )
{
	/* 01 選択されたフレームの先頭の順番を得る */
	const int crnt_list_num = this->cl_file_number_list.set_first_number();

	/* 02 選択されていない */
	if (crnt_list_num == 0) {
		pri_funct_err_bttvr(
	 "Error : this->cl_file_number_list.set_first_number() returns zero"
		);
fl_alert("Select number!");
		return;
	}

	/* 03 選択されているのにフレーム番号名がない */
	else if (crnt_list_num < 0) {
		pri_funct_err_bttvr(
	 "Error : this->cl_file_number_list.set_first_number() returns minus"
		);
fl_alert("No frame number.");
		return;
	}

	/* 04 levelの名前を得る */
	if (NULL == this->cl_bro_level.cp_filepath(
		this->cl_file_number_list.get_crnt_file_num()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns NULL.",
		this->cl_file_number_list.get_crnt_file_num()
		);
fl_alert("Input level name!");
		return;
	}

	/* --> crnt_list_numがプラス-->リストを選んだ */

	/* 05 カレントのスキャンと保存をして、次があるなら準備もする */
	if ( 0 != cl_gts_gui.chkbtn_endless->value() ) {
		cl_gts_master.cl_file_number_list.set_endress_sw(true);
	}
	if (this->cb_scan_and_save_start_child_() != OK) {
// std::string str("Error in scaning at 1st!";
// fl_alert(str.c_str());
		return;
	}
	cl_gts_master.cl_file_number_list.set_endress_sw(false);

	/* 06 次のスキャンがあるなら */
	if (0 < this->cl_file_number_list.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
void gts_master::cb_scan_and_save_next( void )
{
	/* windowを消す */
	cl_gts_gui.window_next_scan->hide();

	/* 次の番号をカレントにする */
	this->cl_file_number_list.set_next_to_crnt_number();

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if ( 0 != cl_gts_gui.chkbtn_endless->value() ) {
		cl_gts_master.cl_file_number_list.set_endress_sw(true);
	}
	if (this->cb_scan_and_save_next_child_() != OK) {
// std::string str("Error in scaning at next!";
// fl_alert(str.c_str());
		return;
	}
	cl_gts_master.cl_file_number_list.set_endress_sw(false);

	/* 次のスキャンがあるなら */
	if (0 < this->cl_file_number_list.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
void gts_master::cb_scan_and_save_prev( void )
{
	/* windowを消す */
	cl_gts_gui.window_next_scan->hide();

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (0 < this->cl_file_number_list.get_crnt_file_num()) {
	 if (OK != this->next_scan_and_save_()) {
		pri_funct_err_bttvr(
	  "Error : this->next_scan_and_save_() returns NG" );
		return;
	 }
	}
	/* 次のスキャンがあるなら */
	if (0 < this->cl_file_number_list.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
