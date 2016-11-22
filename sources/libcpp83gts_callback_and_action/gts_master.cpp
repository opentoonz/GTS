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
	/* GUIのsaveで指定した順に拡張子リストを作る */
	for (int ii=0 ;ii<cl_gts_gui.choice_level_save_image_format->size()
	;++ii) {
		const char* tx =
			cl_gts_gui.choice_level_save_image_format->text(ii);
		if      (std::string(tx) == "TGA(*.tga)") {
			this->cl_bro_level.add_imagefile_extension(".tga");
		}
		else if (std::string(tx) == "TIFF(*.tif)") {
			this->cl_bro_level.add_imagefile_extension(".tif");
		}
	}

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
	/* GUI(fltk)生成 */

	/***Fl::add_handler(handle_to_steel_shortcut_event);***/
	(void)cl_gts_gui.make_window();

	/*------------------------------------------------*/
	/* GUI設定 */

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

	/* カレントのファイル拡張子(tif/tga)、元設定からGUI設定する*/
	cl_gts_gui.choice_level_save_image_format->value(
 this->cl_bro_level.get_current_save_imagefile_extension()
	);
	cl_gts_gui.choice_level_open_image_format->value(
 this->cl_bro_level.get_current_open_imagefile_extension()
	);
	//ct_gts_master.cl_bro_level.cb_set_save_image_file_extension();

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
	this->_print_window_headline();

	/* keyのDrag and Dropをしない */
	Fl::dnd_text_ops(0);

	/*------------------------------------------------*/
	/* fltkイベントループ */

	return Fl::run();
}
