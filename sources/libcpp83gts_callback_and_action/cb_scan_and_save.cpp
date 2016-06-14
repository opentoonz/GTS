#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/*--------------------------------------------------------*/
static int _i_rgb_trace_save_sw;

int gts_master::_scan_and_save( int i_file_num, int i_list_num )
{
	char *cp_path;
	iip_canvas *clp_scan;

	/*------------------------------------------------*/

	/* リストのセンタースクロール */
	cl_gts_gui.selbro_fnum_list->middleline(i_list_num);

	/*------------------------------------------------*/

	/* スキャンを実行 */
	clp_scan = this->_iipg_scan();
	if (NULL == clp_scan) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_scan() returns NULL" );
		return NG;
	}

	/* 回転処理を実行 */
	if (OK != this->_iipg_rot90(
		clp_scan,
		cl_gts_gui.choice_rot90->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return NG;
	}

	/*------------------------------------------------*/

	/* 保存する(番号に対する)ファイルパスを得る */
	if (3L <= this->cl_iip_ro90.get_l_channels()) {
		/* RGB画像のときは専用の名前(A_full.0001.tif)で保存 */
		/* 読み込み(番号に対する)ファイルパスを得る */

		/**********if (OK != this->cl_bro_level.i_path_cpy_dir(
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
		cp_path = this->cl_bro_level.cp_path();**********/

		cp_path = this->cl_bro_level.cp_filepath_full(
			i_file_num);
		if (NULL == cp_path) {
			pri_funct_err_bttvr(
		 "Error : this->cl_bro_level.cp_filepath_full(%d) returns NULL.",
			i_file_num
			);
			return NG;
		}
	} else {
		/* BW,Grayscaleはノーマルな名前(A.0001.tif)で保存 */
		/***********if (OK != this->cl_bro_level.i_path_cpy_dir(
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
		cp_path = this->cl_bro_level.cp_path();**********/

		cp_path = this->cl_bro_level.cp_filepath( i_file_num );
		if (NULL == cp_path) {
			pri_funct_err_bttvr(
		 "Error : this->cl_bro_level.cp_filepath(%d) returns NULL.",
			i_file_num
			);
			return NG;
		}
	}

	/* スキャン画像保存(BW,GrayscaleあるいはRGBでSWが入っている場合) */
	if ((this->cl_iip_ro90.get_l_channels() < 3L) ||//BW or Grayscale
	    (this->cl_iip_ro90.get_l_channels() == 3L &&//RGB & SW is ON
	     cl_gts_gui.chkbtn_level_rgb_full_save_sw->value() ==1
	    )
	) {
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
	}

	/*------------------------------------------------*/

	/* リストにマーク付け */
	if (OK != this->cl_list_access.marking_src(i_list_num)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.marking_src(%d) returns NG",
			i_list_num
		);
		return NG;
	}

	/*------------------------------------------------*/

	/* RGBフルカラーでないか、トレス画像保存でなければここで終了 */
	if (	(this->cl_iip_ro90.get_l_channels() < 3L) ||
		(1 != _i_rgb_trace_save_sw)
	) {
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

	/*------------------------------------------------*/

	/* 画像処理を実行 */
	if (OK != this->_iipg_color_trace_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_color_trace_setup() returns NG" );
		return NG;
	}
	this->_iipg_color_trace_exec();

	/*------------------------------------------------*/

	/* Trace保存する(番号に対する)ファイルパスを得る */
	/**********if (OK != this->cl_bro_level.i_path_cpy_dir(
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
	cp_path = this->cl_bro_level.cp_path();*********/

	cp_path = this->cl_bro_level.cp_filepath( i_file_num );
	if (NULL == cp_path) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns NULL.",
		i_file_num
		);
		return NG;
	}

	/* Trace画像を保存する */
	if (OK != this->_iipg_save(
		&(cl_gts_master.cl_iip_trac),
		cp_path,
		cl_gts_gui.valinp_area_reso->value()
		/* rot90実行後なので(デフォルト)0度とする */
	) ) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_save(-) returns NG" );
		return NG;
	}

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

	/*------------------------------------------------*/

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

void gts_master::_set_window_next_scan( int i_file_prev, int i_file_next )
{
	char	ca8_but[8];

	(void)sprintf( ca8_but, "%d", i_file_prev );
	cl_gts_gui.norout_crnt_scan_number->value(ca8_but);

	(void)sprintf( ca8_but, "%d", i_file_next );
	cl_gts_gui.norout_next_scan_number->value(ca8_but);

	cl_gts_gui.norout_crnt_scan_level->value(
		this->cl_bro_level.cp_levelname()
	);
}

/* 必ず、カレントの番号は有効の状態で、このmethodを呼ぶ */
int gts_master::_scan_and_save_crnt( void )
{
	if (OK != this->cl_list_access.set_next_number()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.set_next_number() returns NG");
		return NG;
	}

	/* スキャンと保存を実行する */
	if (OK != this->_scan_and_save(
		this->cl_list_access.get_i_crnt_file_num(),
		this->cl_list_access.get_i_crnt_list_num()
	)) {
		/* 次のスキャン番号をキャンセルしてエラーリターン */
		this->cl_list_access.reset_next_number();

		pri_funct_err_bttvr(
	 "Error : this->_scan_and_save(%d,%d) returns NG",
		this->cl_list_access.get_i_crnt_file_num(),
		this->cl_list_access.get_i_crnt_list_num()
		);

//std::string str("Critical Error!\nSave Config and Restart!");
//fl_alert(str.c_str());

		return NG;
	}

	/* 切抜きはしないのでOFFにしておく */
	this->cl_ogl_view.crop_area(OFF);

	/* 次のフレーム番号があるなら、
	次の処理を促すwindowの設定をしておく */
	if (0 < this->cl_list_access.get_i_next_file_num()) {
		this->_set_window_next_scan(
		this->cl_list_access.get_i_crnt_file_num(),
		this->cl_list_access.get_i_next_file_num()
		);
	}

	return OK;
}

void gts_master::_cb_scan_and_save_start( void )
{
	/* 01 選択されたフレームの先頭の順番を得る */
	const int i_crnt_list_num = this->cl_list_access.set_first_number();

	/* 02 ゼロは選択されていない */
	if (0 == i_crnt_list_num) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.set_first_number() returns zero"
		);
fl_alert("Select number!");
		return;
	}

	/* 03 マイナスは選択されているのにフレーム番号名がない */
	else if (i_crnt_list_num < 0) {
		pri_funct_err_bttvr(
	 "Error : this->cl_list_access.set_first_number() returns minus"
		);
fl_alert("No frame number.");
		return;
	}
	/* プラスはリストを選んだ */

	/* 保存dir,filehead,extが得られるか確認 */

	/*************if (OK != this->cl_bro_level.i_path_cpy_dir(
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
	}****************/
	// cp_path = this->cl_bro_level.cp_path();

	/* 04 levelの名前を得る */
	if (NULL == this->cl_bro_level.cp_filepath(
		this->cl_list_access.get_i_crnt_file_num()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.cp_filepath(%d) returns NULL.",
		this->cl_list_access.get_i_crnt_file_num()
		);
fl_alert("Input level name!");
		return;
	}

	/* 05 カレントのスキャンと保存をして、次があるなら準備もする */
	if (0 < this->cl_list_access.get_i_crnt_file_num()) {
	 /* この中でnext_file_numセットしている */
	 if (OK != this->_scan_and_save_crnt()) {
		pri_funct_err_bttvr(
	  "Error : this->_scan_and_save_crnt() returns NG" );

// std::string str("Error of scaning!\nSave Config and Restart!";
// fl_alert(str.c_str());

		return;
	 }
	}

	/* 06 次のスキャンがあるなら */
	if (0 < this->cl_list_access.get_i_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}

/*--------------------------------------------------------*/

void gts_master::cb_scan_and_save_start( void )
{
	_i_rgb_trace_save_sw =
		cl_gts_gui.chkbtn_level_rgb_trace_save_sw->value();
	this->_cb_scan_and_save_start();
}
void gts_master::cb_scan_and_trace_and_save_start( void )
{
	/* rgbのときだけ動作する */
	/******if (2 == cl_gts_gui.choice_pixel_type->value()) {
		_i_rgb_trace_save_sw = 1;
		this->_cb_scan_and_save_start();
	}******/

	/* 強制的にrgbモードにして実行する */
	cl_gts_gui.choice_pixel_type->value(2);

	_i_rgb_trace_save_sw = 1;
	this->_cb_scan_and_save_start();
}
void gts_master::cb_scan_and_save_next( void )
{
	/* windowを消す */
	cl_gts_gui.window_next_scan->hide();

	/* 次の番号をカレントにする */
	this->cl_list_access.set_next_to_crnt_number();

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (0 < this->cl_list_access.get_i_crnt_file_num()) {
	 if (OK != this->_scan_and_save_crnt()) {
		/*
		ここでエラーになると次の番号がカレントに
		なってしまうので元に戻す
	this->cl_list_access.set_next_to_crnt_number();
		と対で使うこと
		*/
		this->cl_list_access.reset_next_to_crnt_number();

		pri_funct_err_bttvr(
	  "Error : this->_scan_and_save_crnt() returns NG" );
		return;
	 }
	}
	/* 次のスキャンがあるなら */
	if (0 < this->cl_list_access.get_i_next_file_num()) {
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
	if (0 < this->cl_list_access.get_i_crnt_file_num()) {
	 if (OK != this->_scan_and_save_crnt()) {
		pri_funct_err_bttvr(
	  "Error : this->_scan_and_save_crnt() returns NG" );
		return;
	 }
	}
	/* 次のスキャンがあるなら */
	if (0 < this->cl_list_access.get_i_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
