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

	/*---------- cl_level.ext_open/save初期値設定----------*/

	/* 画像R/Wルーチンの対応状態をセットする --> あとで修正予定 */
	this->cl_level.ext_open.set_filter( "TIFF" ,".tif" );	/* 0番目 */
	this->cl_level.ext_open.set_filter( "TGA"  ,".tga" );	/* 1番目 */

	this->cl_level.ext_save.set_filter( "TIFF" ,".tif" );	/* 0番目 */
	this->cl_level.ext_save.set_filter( "TGA"  ,".tga" );	/* 1番目 */

	/*---------- GUI(fltk)生成 ----------*/

	/***Fl::add_handler(handle_to_steel_shortcut_event);***/
	(void)cl_gts_gui.make_window();

	/*---------- GUI初期設定 ----------*/

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

	/* HLS Min-Max windowの色ベルト画像表示設定 */
//	this->make_hab_belt_image();

	/* short cut key設定 */
	this->cl_memo_short_cut_key.set_shortcut();

	/* fltk設定各種 --- ここまで */

	/* ファイル拡張子、元設定からGUI設定し、初期指定(.tga)する */
	for(int ii=0;ii<this->cl_level.ext_open.size() ;++ii) {
		   cl_gts_gui.choice_trace_open_image_format->add(
			this->cl_level.ext_open.get_fltk_filter(ii).c_str()
		);
	}
	for(int ii=0;ii<this->cl_level.ext_save.size() ;++ii) {
		   cl_gts_gui.choice_scan_save_image_format->add(
			this->cl_level.ext_save.get_fltk_filter(ii).c_str()
		);
	}
	if (0 < this->cl_level.ext_open.size()) {
	   cl_gts_gui.choice_trace_open_image_format->value(
		this->cl_level.ext_open.size() - 1/*".tga"*/ );
	}
	if (0 < this->cl_level.ext_save.size()) {
	   cl_gts_gui.choice_scan_save_image_format->value(
		this->cl_level.ext_save.size() - 1/*".tga"*/ );
	}

	/* gts guiの初期設定 Filterの初期スイッチ */
	cl_gts_gui.chkbtn_scan_trace_sw->box( FL_SHADOW_BOX );
	cl_gts_gui.chkbtn_scan_trace_sw->value( 1 );

	/* install_setupによる2次設定 */

	if (!this->cl_memo_install_setup.browser_directory_path.empty()) {
	  cl_gts_gui.filinp_trace_open_dir_path->value(
	     this->cl_memo_install_setup.browser_directory_path.c_str()
	  );
	  cl_gts_gui.filinp_scan_save_dir_path->value(
	     this->cl_memo_install_setup.browser_directory_path.c_str()
	  );
	}

	if (!this->cl_memo_install_setup.image_file_format.empty()) {
	 if (this->cl_memo_install_setup.image_file_format=="TIFF"){
	  cl_gts_gui.choice_trace_open_image_format->value(0);
	  cl_gts_gui.choice_scan_save_image_format->value(0);
	 } else if (
	     this->cl_memo_install_setup.image_file_format=="TGA") {
	  cl_gts_gui.choice_trace_open_image_format->value(1);
	  cl_gts_gui.choice_scan_save_image_format->value(1);
	 }
	}

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	this->cl_color_trace_thickness.cb_enh_01();
	this->cl_color_trace_thickness.cb_enh_02();
	this->cl_color_trace_thickness.cb_enh_03();
	this->cl_color_trace_thickness.cb_enh_04();
	this->cl_color_trace_thickness.cb_enh_05();
	this->cl_color_trace_thickness.cb_enh_06();

	/* fltk windowのうちmain画面は必ず表示する */
	/* set_non_model()は始めにshowしたwindowがメイン */
	cl_gts_gui.window_opengl->show();
	cl_gts_gui.window_opengl->wait_for_expose();
	Fl::flush();

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
	this->print_window_headline();

	/* keyのDrag and Dropをしない */
	Fl::dnd_text_ops(0);

	/*------------------------------------------------*/
	/* fltkイベントループ */

	return Fl::run();
}
