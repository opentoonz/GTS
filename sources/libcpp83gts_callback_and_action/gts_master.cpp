#include <iostream> // std::cout
#include <stdlib.h> /* getenv() */
#include <FL/x.H> /* for fl_xid() */
#include "pri.h"
#include "ids_path_level_from_files.h"
#include "gts_file_path.h"
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
{
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

	/*
		パラメータ初期設定
	*/

	/* 画像R/W書式(拡張子)の初期設定 */ 
	this->cl_scan_and_save.ext_save.set_filter("TIFF",".tif");/*0番目 */
	this->cl_scan_and_save.ext_save.set_filter( "TGA",".tga");/*1番目 */
	this->cl_trace_files.ext_open.set_filter("TIFF",".tif");/* 0番目 */
	this->cl_trace_files.ext_open.set_filter( "TGA",".tga");/* 1番目 */
	this->cl_trace_files.ext_save.set_filter("TIFF",".tif");/* 0番目 */
	this->cl_trace_files.ext_save.set_filter( "TGA",".tga");/* 1番目 */
	this->cl_image.ext_open.set_filter("TIFF",".tif");/* 0番目 */
	this->cl_image.ext_open.set_filter( "TGA",".tga");/* 1番目 */
	this->cl_image.ext_save.set_filter("TIFF",".tif");/* 0番目 */
	this->cl_image.ext_save.set_filter( "TGA",".tga");/* 1番目 */

	/*
		GUI(fltk)生成
	*/

	/***Fl::add_handler(handle_to_steel_shortcut_event);***/
	(void)cl_gts_gui.make_window();

	/*
		GUI(fltk)初期設定
	*/

	/* DPIの値をユーザー入力しキャンセルした時の値の復元用記憶 */
	this->cl_area_and_rot90.set_dpi_before_change(
		cl_gts_gui.valinp_area_reso->value()
	);

	/* 画像書式種類(拡張子)をGUIに設定 */
	for(int ii=0;ii<this->cl_scan_and_save.ext_save.size() ;++ii) {
	       cl_gts_gui.choice_scan_save_image_format->add(
			this->cl_scan_and_save.ext_save.str_from_num(ii).c_str()
		);
	}
	       cl_gts_gui.choice_scan_save_image_format->value(0);
	for(int ii=0;ii<this->cl_trace_files.ext_open.size() ;++ii) {
	       cl_gts_gui.choice_trace_open_image_format->add(
			this->cl_trace_files.ext_open.str_from_num(ii).c_str()
		);
	       cl_gts_gui.choice_trace_open_image_format->value(0);
	}
	for(int ii=0;ii<this->cl_trace_files.ext_save.size() ;++ii) {
	       cl_gts_gui.choice_trace_save_image_format->add(
			this->cl_trace_files.ext_save.str_from_num(ii).c_str()
		);
	       cl_gts_gui.choice_trace_save_image_format->value(0);
	}

	/* Save File Number Formatについての選択リスト設定 */
	const char** names =
		ids::path::get_separator_names_for_level_from_files();
	cl_gts_gui.choice_input_num_form_separator->add("Nothing");
	for (int ii=0; names[ii] != nullptr ;++ii) {
		cl_gts_gui.choice_input_num_form_separator->add(names[ii]);
	}

	/* fltk windowのうちmain画面は必ず表示する */
	/* set_non_model()は始めにshowしたwindowがメイン */
	cl_gts_gui.window_main_view->show();
	cl_gts_gui.window_main_view->wait_for_expose();
	Fl::flush();

	/* trace paramsのguiを配列で利用するための変数初期設定 */
	this->cl_trace_params.init_widget_set();
	this->cl_trace_params.init_color(); /* init_widget_set()後使用 */

	/* gts_initial_configuration.txtによる初期設定 */
	{
	const char *file_name = "gts_initial_configuration.txt";
	std::string path = gts_file_path(comm, file_name);
	if (!path.empty()) {/* ファイルあるなら設定する */
		if (OK != this->cl_memo_config.load( path.c_str() )) {
			pri_funct_err_bttvr(
	 "Error : this->cl_memo_config.load() returns NG" );
			return NG;
		}
	}
	}

	/* trace paramsのguiを配列で利用するための変数初期設定 */
	/* configで順番が決まってから0番目(赤)を指定 */
	this->cl_trace_params.cb_hue_minmax_init_editor(0);

	/* desktop.txtによる fltk window位置とサイズを復元 */
	if (OK != this->cl_memo_desktop.load()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_desktop.load() returns NG" );
		return NG;
	}

	/* Scan and SaveでSet Numberしておく */
	this->cl_scan_and_save.cb_set_number();
	this->cl_scan_and_save.cb_check_existing_saved_file();

	/*------------------------------------------------*/
	/* window TWAINのためにウインドウハンドルを設定する */

#if defined _WIN32
	cl_gts_master.cl_iip_scan.set_hw_parent(
		fl_xid( cl_gts_gui.window_main_view )
	);
#endif

	/* TWAINからタイプと最大値をとってきてメニューへ表示する */
	/* ->show();と.set_hw_parent()は先にやらなければ動作しない */
	if (OK != this->iipg_scan_get_scanner_info_()) {
		pri_funct_err_bttvr(
	 "Error : this->iipg_scan_get_scanner_info_() returns NG" );
		//return NG;
		/* エラーが起きても(Scanner接続してなくても)
		動作させる */
	}

	/* main windowのタイトル表示 */
	this->print_window_headline();

	/* keyのDrag and Dropをしない */
	Fl::dnd_text_ops(0);

	/*------------------------------------------------*/
	/* fltkイベントループ */

	return Fl::run();
}
