#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/*--------------------------------------------------------*/
int gts_master::next_scan_and_save_( void )
{
	int crnt_list_num;
	int crnt_file_num;
	int next_file_num;
	const char* cp_path = nullptr;
	iip_canvas* clp_scan = nullptr;
	char	ca8_but[8];

	/* 01 次(始め)の位置を得る */
	crnt_list_num = this->cl_file_number_list.get_crnt_list_num();
	crnt_file_num = this->cl_file_number_list.get_crnt_file_num();
	next_file_num = this->cl_file_number_list.get_next_file_num();
	if (crnt_list_num< 1 || crnt_file_num< 1) {
		pri_funct_err_bttvr(
   "Error : crnt_list_num=%d or crnt_file_num=%d"
			,crnt_list_num ,crnt_file_num );
		return NG;
	}

	/* 02 フレーム番号(crnt_list_num)を表示するようリストをスクロール */
	cl_gts_gui.selbro_fnum_list->middleline(crnt_list_num);

	/* 03 スキャンを実行 */
	clp_scan = this->_iipg_scan();
	if (nullptr == clp_scan) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_scan() returns nullptr" );
// std::string str("Error in scaning at next!";
// fl_alert(str.c_str());
		return NG;
	}

	/* 04 回転処理を実行 */
	if (OK != this->_iipg_rot90(
		clp_scan ,cl_gts_gui.choice_rot90->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return NG;
	}

	/* 05 保存する(番号に対する)ファイルパスを得る */
	if (3L <= this->cl_iip_ro90.get_l_channels() &&
	cl_gts_gui.chkbtn_level_rgb_with_full_sw->value() == 1
	) {
		/* RGB画像(専用の名前)(_full付)(A_full.0001.tif) */
		/* 読み込み(番号に対する)ファイルパスを得る */
		cp_path = this->cl_bro_level.cp_filepath_full( crnt_file_num );
		if (cp_path == nullptr) {
			pri_funct_err_bttvr(
		 "Error : this->cl_bro_level.cp_filepath_full(%d) returns nullptr."
				, crnt_file_num );
			return NG;
		}
	} else {
		/* BW,Grayscale,RGB(通常の名前)は
		ノーマルな名前(A.0001.tif)で保存 */
		cp_path = this->cl_bro_level.cp_filepath( crnt_file_num );
		if (cp_path == nullptr) {
			pri_funct_err_bttvr(
	"Error : this->cl_bro_level.cp_filepath(%d) returns nullptr."
				, crnt_file_num );
			return NG;
		}
	}

	/* 06 BWか、Grayscaleか、RGBで保存SWがONのどれかの場合 */
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
	 if (OK != this->cl_file_number_list.marking_scan_file(crnt_list_num)) {
		pri_funct_err_bttvr(
	  "Error : this->cl_file_number_list.marking_scan_file(%d) returns NG",
			crnt_list_num
		);
		return NG;
	 }
	}

	/*------------------------------------------------*/
	/* 07 RGB画像でトレス画像保存SWがONの場合 */
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
	 cp_path = this->cl_bro_level.cp_filepath( crnt_file_num );
	 if (nullptr == cp_path) {
		pri_funct_err_bttvr(
	  "Error : this->cl_bro_level.cp_filepath(%d) returns nullptr."
	 		, crnt_file_num
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
	 if (OK != this->cl_file_number_list.marking_trace_file(crnt_list_num)) {
		pri_funct_err_bttvr(
	  "Error : this->cl_file_number_list.marking_trace_file(%d) returns NG"
	 		, crnt_list_num
		);
		return NG;
	 }
	}
	/*------------------------------------------------*/

	/* 08 リストの選択解除 */
	this->cl_file_number_list.unselect(crnt_list_num);

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

	/* 12 切抜きはしないのでOFFにしておく */
	this->cl_ogl_view.crop_area(OFF);

	/* 13 次のフレーム番号があるなら、
	次の処理を促すwindowの設定をしておく */
	if (0 < this->cl_file_number_list.get_next_file_num()) {
		(void)sprintf( ca8_but ,"%d" ,crnt_file_num );
		cl_gts_gui.norout_crnt_scan_number->value(ca8_but);

		(void)sprintf( ca8_but ,"%d" ,next_file_num );
		cl_gts_gui.norout_next_scan_number->value(ca8_but);

		cl_gts_gui.norout_crnt_scan_level->value(
			this->cl_bro_level.cp_levelname()
		);
	}

	return OK;
}

/*--------------------------------------------------------*/

void gts_master::cb_scan_and_save_start( void )
{
	/* 先頭を得る */
	this->cl_file_number_list.counter_start();

	/* 最初に番号が選択がない/設定できない */
	if (this->cl_file_number_list.get_crnt_file_num() < 1) {
		if (cl_gts_gui.choice_level_end_type->value() == 0) {/*End*/
			fl_alert("Not select number!");
		}
		else {/* Endless */
			fl_alert("Bad number in Start!");
		}
		return;
	}

	/* levelの名前を得る */
	if (nullptr == this->cl_bro_level.cp_filepath(
		this->cl_file_number_list.get_crnt_file_num()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns nullptr.",
		this->cl_file_number_list.get_crnt_file_num()
		);
fl_alert("Input level name!");
		return;
	}

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (this->next_scan_and_save_() != OK) {
		return;
	}

	/* 次のスキャンがあるなら */
	if (1 <= this->cl_file_number_list.get_next_file_num()) {
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

	/* 次の番号を得る */
	this->cl_file_number_list.counter_next();

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (this->next_scan_and_save_() != OK) {
		return;
	}

	/* 次のスキャンがあるなら */
	if (1 <= this->cl_file_number_list.get_next_file_num()) {
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
	if ( this->next_scan_and_save_() != OK ) {
		return;
	}

	/* 次のスキャンがあるなら */
	if (1 <= this->cl_file_number_list.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
