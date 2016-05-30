#include <stdlib.h> /* getenv() */
#include <FL/x.H> /* for fl_xid() */
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

gts_master::gts_master(
	const char *const app_name
	,const char *const rele_num
	,const char *const rele_date
):
	_i_mv_sw(OFF)
	,_i_pv_sw(OFF)
	,_i_cv_sw(OFF)
	,_cp_release_name(app_name)
	,_cp_release_date(rele_date)
	,_cp_release_number(rele_num)
	,_i_enable_act_menu_sw(ON)
	,_i_enable_act_key_event_sw(OFF)
	/* メニューの初期設定値に合わせる、また、
	cb_config_load_ok(),cb_level_ok()の時も
	んだ設定に合わせること */
	,_i_rotate_per_90(0)
{
	this->cl_bro_level.add_imagefile_extension( ".tif" );
	this->cl_bro_level.add_imagefile_extension( ".tga" );
	this->cl_bro_config.add_imagefile_extension( ".txt" );/* 未使用2016-5-18 */
	this->cl_bro_trace_batch.add_imagefile_extension( ".txt" );/* 未使用2016-5-18 */
}

int  gts_master::i_mv_sw( void ) const
{  return this->_i_mv_sw; }
void gts_master::i_mv_sw( int sw ) {
	  this->_i_mv_sw = sw;
	this->cl_iip_scan.set_i_mv_sw( sw );
	this->cl_iip_read.set_i_mv_sw( sw );
	this->cl_iip_ro90.set_i_mv_sw( sw );
	this->cl_iip_trac.set_i_mv_sw( sw );
	this->cl_iip_edot.set_i_mv_sw( sw );
	this->cl_ogl_view.set_i_mv_sw( sw );
	this->cl_iip_writ.set_i_mv_sw( sw );
}
int  gts_master::i_pv_sw( void ) const
{  return this->_i_pv_sw; }
void gts_master::i_pv_sw( int sw ) {
	  this->_i_pv_sw = sw;
	this->cl_iip_scan.set_i_pv_sw( sw );
	this->cl_iip_read.set_i_pv_sw( sw );
	this->cl_iip_ro90.set_i_pv_sw( sw );
	this->cl_iip_trac.set_i_pv_sw( sw );
	this->cl_iip_edot.set_i_pv_sw( sw );
	this->cl_ogl_view.set_i_pv_sw( sw );
	this->cl_iip_writ.set_i_pv_sw( sw );
}
int  gts_master::i_cv_sw( void ) const
{  return this->_i_cv_sw; }
void gts_master::i_cv_sw( int sw ) {
	  this->_i_cv_sw = sw;
	this->cl_iip_scan.set_i_cv_sw( sw );
	this->cl_iip_read.set_i_cv_sw( sw );
	this->cl_iip_ro90.set_i_cv_sw( sw );
	this->cl_iip_trac.set_i_cv_sw( sw );
	this->cl_iip_edot.set_i_cv_sw( sw );
	this->cl_ogl_view.set_i_cv_sw( sw );
	this->cl_iip_writ.set_i_cv_sw( sw );
}

const char *const gts_master::cp_release_name( void ) const
{   return this->_cp_release_name; }

const char *const gts_master::cp_release_date( void ) const
{   return this->_cp_release_date; }

const char *const gts_master::cp_release_number( void ) const
{   return this->_cp_release_number; }

// this is used to stop Esc from exiting the program:
/***static int handle_to_steel_shortcut_event(int e) {
	if (e == FL_KEYDOWN) {
		pri_funct_msg_ttvr(
			"FL_KEYDOWN ley<%d> text<%s> len<%d>",
			Fl::event_key(),
			Fl::event_text(),
			Fl::event_length() );
	} else
	if (e == FL_KEYUP) {
		pri_funct_msg_ttvr(
			"FL_KEYUP ley<%d> text<%s> len<%d>",
			Fl::event_key(),
			Fl::event_text(),
			Fl::event_length() );
	} else
	if (e == FL_SHORTCUT) {
		pri_funct_msg_ttvr(
			"FL_SHORTCUT ley<%d> text<%s> len<%d>",
			Fl::event_key(),
			Fl::event_text(),
			Fl::event_length() );
	}

	return (e == FL_SHORTCUT); // eat all keystrokes
}***/

int gts_master::exec( const char *comm )
{
	if (ON == this->i_mv_sw()) {
		pri_funct_msg_ttvr( "gts_master::exec()" );
	}

	/*------------------------------------------------*/
	// Fl::set_font(FL_HELVETICA, "Kochi Gothic");
	/*
		Windows版のブラウザー上、日本語で、
		フォルダーを表示移動可能となる(日本語入力はできない)
		現在は対応しない(2009-07-13)
		詳細はhistory.txtへ
	*/

	/*------------------------------------------------*/
	/* GUI生成                                        */

	/***Fl::add_handler(handle_to_steel_shortcut_event);***/

	/* fltk window and gui生成 */ 
	(void)cl_gts_gui.make_window();

	/*------------------------------------------------*/
	/* GUI設定                                        */

	/* color trace enhancement */
	this->cl_color_trace_enhancement.src_init_histogram_window();

	/* システム初期ディレクトリを設定 */
#if defined _WIN32
	/************** this->change_level_dir("C:/"); *************/
#endif

	/* 回転値(システム設定値)をメモリする */
	this->_i_rotate_per_90 = cl_gts_gui.choice_rot90->value();

	/* fltk windowのうちwindow_next_scan画面は必ず中央表示する */
	//cl_gts_gui.window_next_scan->position(390,362);

	/* fltk設定各種 --- ここから */
	cl_gts_gui.scrbar_bw_threshold->linesize(1);

	((Fl_Valuator *)cl_gts_gui.scrbar_bw_threshold)->value(
			cl_gts_gui.valinp_bw_threshold->value()
	);

	cl_gts_gui.scrbar_grays_brightness->linesize(1);
	cl_gts_gui.scrbar_grays_contrast->linesize(1);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_brightness)->value(
			cl_gts_gui.valinp_grays_brightness->value() );
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_contrast)->value(
			cl_gts_gui.valinp_grays_contrast->value() );
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_gamma)->value(
			cl_gts_gui.valinp_grays_gamma->value() );

	cl_gts_gui.scrbar_rgb_brightness->linesize(1);
	cl_gts_gui.scrbar_rgb_contrast->linesize(1);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_brightness)->value(
			cl_gts_gui.valinp_rgb_brightness->value() );
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_contrast)->value(
			cl_gts_gui.valinp_rgb_contrast->value() );
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_gamma)->value(
			cl_gts_gui.valinp_rgb_gamma->value() );

	cl_gts_gui.scrbar_color_trace_01_src_hh_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_01_src_hh_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_01_src_aa_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_01_src_aa_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_01_src_bb_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_01_src_bb_max->linesize(1);
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_min)->value(
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_max)->value(
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_min)->value(
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_max)->value(
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_min)->value(
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_max)->value(
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value());

	cl_gts_gui.scrbar_color_trace_02_src_hh_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_02_src_hh_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_02_src_aa_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_02_src_aa_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_02_src_bb_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_02_src_bb_max->linesize(1);
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_min)->value(
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_max)->value(
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_min)->value(
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_max)->value(
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_min)->value(
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_max)->value(
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value());

	cl_gts_gui.scrbar_color_trace_03_src_hh_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_03_src_hh_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_03_src_aa_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_03_src_aa_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_03_src_bb_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_03_src_bb_max->linesize(1);
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_min)->value(
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_max)->value(
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_min)->value(
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_max)->value(
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_min)->value(
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_max)->value(
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value());

	cl_gts_gui.scrbar_color_trace_04_src_hh_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_04_src_hh_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_04_src_aa_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_04_src_aa_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_04_src_bb_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_04_src_bb_max->linesize(1);
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_min)->value(
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_max)->value(
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_min)->value(
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_max)->value(
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_min)->value(
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_max)->value(
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value());

	cl_gts_gui.scrbar_color_trace_05_src_hh_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_05_src_hh_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_05_src_aa_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_05_src_aa_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_05_src_bb_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_05_src_bb_max->linesize(1);
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_min)->value(
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_max)->value(
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_min)->value(
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_max)->value(
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_min)->value(
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_max)->value(
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value());

	cl_gts_gui.scrbar_color_trace_06_src_hh_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_06_src_hh_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_06_src_aa_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_06_src_aa_max->linesize(1);
	cl_gts_gui.scrbar_color_trace_06_src_bb_min->linesize(1);
	cl_gts_gui.scrbar_color_trace_06_src_bb_max->linesize(1);
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_min)->value(
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_max)->value(
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_min)->value(
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_max)->value(
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_min)->value(
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value());
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_max)->value(
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value());

	cl_gts_gui.scrbar_edit_color_red->linesize(1);
	cl_gts_gui.scrbar_edit_color_gre->linesize(1);
	cl_gts_gui.scrbar_edit_color_blu->linesize(1);
	/******((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_red)->value(
			cl_gts_gui.valinp_edit_color_red->value());
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_gre)->value(
			cl_gts_gui.valinp_edit_color_gre->value());
	((Fl_Valuator *)cl_gts_gui.scrbar_edit_color_blu)->value(
			cl_gts_gui.valinp_edit_color_blu->value());*****/

	/* 6番目のtgt色を黒に初期化する */
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
		E_COLOR_TRACE_HAB_06, 0,0,0
	);

	cl_gts_gui.valinp_area_x_pos->value(0.0);
	cl_gts_gui.valinp_area_y_pos->value(0.0);
	cl_gts_gui.valinp_area_x_size->value(0.0);
	cl_gts_gui.valinp_area_y_size->value(0.0);
	cl_gts_gui.valinp_area_x_pixel->value(0.0);
	cl_gts_gui.valinp_area_y_pixel->value(0.0);
	cl_gts_gui.valinp_area_reso->value(50);

	/* Sub windowの設定
	Redhat9ではfluidでセットすれば正常だが
	WindowsXpでは正常にはうごかない */
// #if !defined _WIN32
	//cl_gts_gui.window_opengl->set_non_modal();

	/***cl_gts_gui.window_level->set_non_modal();
	cl_gts_gui.window_config_load->set_non_modal();
	cl_gts_gui.window_config_save_as->set_non_modal();
	cl_gts_gui.window_crop_area_and_rot90->set_non_modal();
	cl_gts_gui.window_pixel_type_and_bright->set_non_modal();
	cl_gts_gui.window_color_trace->set_non_modal();
	cl_gts_gui.window_edit_color->set_non_modal();
	cl_gts_gui.window_fnum_list->set_non_modal();
	cl_gts_gui.window_trace_batch->set_non_modal();***/

	//cl_gts_gui.window_next_scan->set_non_modal();
// #endif

	/* HLS Min-Max windowの色ベルト画像表示設定 */
	this->make_hab_belt_image();

	/* short cut key設定 */
	this->cl_memo_short_cut_key.set_shortcut();

	/* fltk設定各種 --- ここまで */

	/* levelシステム初期ディレクトリを設定 */
	/* text viewのバッファー設定 */
	if (OK != this->cl_bro_config.i_init()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_config.i_init() returns NG");
		return NG;
	}
	if (OK != this->cl_bro_level.i_init()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_init() returns NG");
		return NG;
	}
	if (OK != this->cl_bro_trace_batch.i_init()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_trace_batch.i_init() returns NG");
		return NG;
	}

	/* image file format TIFF/TGA */
	cl_gts_gui.choice_level_image_file_format->value(
	 this->cl_bro_level.get_current_imagefile_extension()
	);
	//ct_gts_master.cl_bro_level.cb_set_image_file_extension();

	/* fltk windowのうちmain画面は必ず表示する */
	/* set_non_model()は始めにshowしたwindowがメイン */
	cl_gts_gui.window_opengl->show();

	/* fltk window位置とサイズを復元 */
	if (OK != this->cl_memo_desktop.load()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_desktop.load() returns NG" );
		return NG;
	}
	/* テキスト指定したscan area位置とサイズを読んで設定 */
	if (OK != this->cl_memo_scan_area.load( comm )) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_scan_area.load() returns NG" );
		return NG;
	}

	/*------------------------------------------------*/
	/* window TWAINのためにウインドウハンドルを設定する */

#if defined _WIN32
	cl_gts_master.cl_iip_scan.set_hw_parent(
		fl_xid( cl_gts_gui.window_opengl )
	);
#endif

	/* TWAINからタイプと最大値をとってきてメニューへ表示する */
	/* ->show();と.set_hw_parent()は先にやらなければ動作しない */
	if (OK != this->_iipg_scan_get_scanner_info()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_scan_get_scanner_info() returns NG" );
		//return NG;
		/* エラーが起きても(Scanner接続してなくても)
		動作させる */
	}

	/* main windowのタイトル表示 */
	this->_print_window_headline();

	/* keyのDrag and Dropをしない */
	Fl::dnd_text_ops(0);

	/*------------------------------------------------*/

	/* fltkイベントループ */
	return Fl::run();
}
