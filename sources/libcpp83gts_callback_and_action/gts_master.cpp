#include <iostream> // std::cout
#include <stdlib.h> /* getenv() */
#include <FL/x.H> /* for fl_xid() */
#include "pri.h"
#include "ids_path_level_from_files.h"
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

	/* 2値化のための初期設定 --> あとでrefactoring必要 */
	this->cl_calc_trace_hsv.setup_default_area_param();

	/*
		GUI(fltk)生成
	*/

	/***Fl::add_handler(handle_to_steel_shortcut_event);***/
	(void)cl_gts_gui.make_window();

	/*
		GUI(fltk)初期設定
	*/

	/* color trace enhancement */
	this->cl_color_trace_enhancement.src_init_histogram_window();

	/* DPIの値をユーザー入力しキャンセルした時の値の復元用記憶 */
	this->cl_area_and_rot90.set_dpi_before_change(
		cl_gts_gui.valinp_area_reso->value()
	);

	/* short cut key設定 */
	this->cl_memo_short_cut_key.set_shortcut();

	/* 画像書式種類(拡張子)をGUIに設定 */
	for(int ii=0;ii<this->cl_scan_and_save.ext_save.size() ;++ii) {
	       cl_gts_gui.choice_scan_save_image_format->add(
			this->cl_scan_and_save.ext_save.str_from_num(ii).c_str()
		);
	}
	for(int ii=0;ii<this->cl_trace_files.ext_open.size() ;++ii) {
	       cl_gts_gui.choice_trace_open_image_format->add(
			this->cl_trace_files.ext_open.str_from_num(ii).c_str()
		);
	}
	for(int ii=0;ii<this->cl_trace_files.ext_save.size() ;++ii) {
	       cl_gts_gui.choice_trace_save_image_format->add(
			this->cl_trace_files.ext_save.str_from_num(ii).c_str()
		);
	}

	/* Save File Number Formatについての選択リスト設定 */
	const char** names =
		ids::path::get_separator_names_for_level_from_files();
	cl_gts_gui.choice_input_num_form_separator->add("Nothing");
	for (int ii=0; names[ii] != nullptr ;++ii) {
		cl_gts_gui.choice_input_num_form_separator->add(names[ii]);
	}

#if 0
	/* gts_install_setup.txtによる初期設定01 : 各ブラウザーのフォルダ */
	if (!this->cl_memo_install_setup.browser_top_folder.empty()) {
		std::string dpath(
	     this->cl_memo_install_setup.browser_top_folder
		);
		cl_gts_gui.filinp_scan_save_dir_path->value( dpath.c_str());
		cl_gts_gui.filinp_trace_open_dir_path->value(dpath.c_str());
		cl_gts_gui.filinp_trace_save_dir_path->value(dpath.c_str());
		cl_gts_master.cl_trace_batch.set_dir_path(   dpath.c_str());
		cl_gts_master.cl_config.set_dir_path(        dpath.c_str());
	}

	/* gts_install_setup.txtによる初期設定02 : 画像番号書式設定 */
	if (!this->cl_memo_install_setup.save_number_format.empty()) {
		std::string fmt(
	     this->cl_memo_install_setup.save_number_format
		);
	 cl_gts_gui.output_scan_save_number_format->value(  fmt.c_str() );
	 cl_gts_gui.output_trace_save_number_format->value( fmt.c_str() );
	}

	/* gts_install_setup.txtによる初期設定03 : 画像書式 */
	if (!this->cl_memo_install_setup.image_file_format.empty()) {
		const std::string fform(
	     this->cl_memo_install_setup.image_file_format
		);
		if (fform == "TIFF"){
			cl_gts_gui.choice_scan_save_image_format->value(0);
			cl_gts_gui.choice_trace_open_image_format->value(0);
			cl_gts_gui.choice_trace_save_image_format->value(0);

			cl_gts_gui.choice_scan_save_image_format->redraw();
			cl_gts_gui.choice_trace_open_image_format->redraw();
			cl_gts_gui.choice_trace_save_image_format->redraw();
		} else if (fform == "TGA") {
			cl_gts_gui.choice_scan_save_image_format->value(1);
			cl_gts_gui.choice_trace_open_image_format->value(1);
			cl_gts_gui.choice_trace_save_image_format->value(1);

			cl_gts_gui.choice_scan_save_image_format->redraw();
			cl_gts_gui.choice_trace_open_image_format->redraw();
			cl_gts_gui.choice_trace_save_image_format->redraw();
		}
	}
	/* gts_install_setup.txtによる初期設定04 : DPI */
	if (!this->cl_memo_install_setup.area_resolution_dpi.empty()) {
		const double dpi = std::stod(
			this->cl_memo_install_setup.area_resolution_dpi);
		cl_gts_gui.valinp_area_reso->value(dpi);
	}

	/* gts_install_setup.txtによる初期設定05 : 回転値 */
	if (!this->cl_memo_install_setup.area_rotate_per_90.empty()) {
		const int idx = cl_gts_gui.choice_rot90->find_index(
		 this->cl_memo_install_setup.area_rotate_per_90.c_str()
		);
		if (0 <= idx) {
			cl_gts_gui.choice_rot90->value(idx);
			this->cl_area_and_rot90.set_previous_choice_rot90(
						  cl_gts_gui.choice_rot90->value()
			);
		}
	}
	/* gts_install_setup.txtによる初期設定06 : Pixel Type */
	if (!this->cl_memo_install_setup.pixel_type.empty()) {
		this->cb_choice_pixel_type_title( 
			this->cl_memo_install_setup.pixel_type
		);
		this->cb_choice_pixel_type_menu();
	}
	/* gts_install_setup.txtによる初期設定07 : 連番の連続方法 */
	if (!this->cl_memo_install_setup.scan_num_endless_direction.empty()) {
	 this->cl_scan_and_save.cb_choice_and_num_continue_type(
	  this->cl_memo_install_setup.scan_num_endless_direction
	 );
	}
#endif

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	this->cl_color_trace_thickness.cb_enh_01();
	this->cl_color_trace_thickness.cb_enh_02();
	this->cl_color_trace_thickness.cb_enh_03();
	this->cl_color_trace_thickness.cb_enh_04();
	this->cl_color_trace_thickness.cb_enh_05();
	this->cl_color_trace_thickness.cb_enh_06();

	/* fltk windowのうちmain画面は必ず表示する */
	/* set_non_model()は始めにshowしたwindowがメイン */
	cl_gts_gui.window_main_view->show();
	cl_gts_gui.window_main_view->wait_for_expose();
	Fl::flush();

	/* scan_area.txtによるscan area位置とサイズを読んで設定 */
	/*if (OK != this->cl_memo_scan_area.load( comm )) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_scan_area.load() returns NG" );
		return NG;
	}*/

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
