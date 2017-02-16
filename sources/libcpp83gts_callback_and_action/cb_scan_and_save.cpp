#include <cstdio>	// std::rename(-)
#include <utility>	// std::swap(-)
#include <iostream>	// std::cout
#include <sstream>	// std::ostringstream
#include <iomanip>	// std::setfill(-) ,std::setw(-)
#include <FL/fl_ask.H>  // fl_alert(-) fl_input(-)
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
#include "ptbl_returncode.h"
#include "pri.h"
#include "ids_path_fltk_native_browse.h"
#include "ids_path_level_from_files.h"
#include "cb_scan_and_save.h"
#include "gts_gui.h"
#include "gts_master.h"

//------------------------------------------------------------
/* スキャン＆保存実行 */
void cb_scan_and_save::cb_start( void )
{
	if ( !cl_gts_master.cl_number.is_scan() ) {
		fl_alert("Set Number for Scan");
		return;
	}

	/* 先頭を得る */
	cl_gts_master.cl_number.counter_start(
		cl_gts_gui.choice_scan_num_continue_type->value()
	);

	/* チェック：保存ファイルのLevel名がない */
	{
	std::string name(cl_gts_gui.strinp_scan_save_file_head->value());
	if ( name.empty() ) {
		fl_alert("Need Scan Save Name!");
		return;
	}
	}

	/* 番号選択がない/設定できない */
	if (cl_gts_master.cl_number.get_crnt_file_num() < 1) {
		if (cl_gts_gui.choice_scan_num_continue_type->value()
		== cl_gts_master.cl_number.get_end_type_value()
		) {	/* End type */
			fl_alert("Select Number!");
		}
		else {	/* Endless type */
			fl_alert("Bad Number in Start!");
		}
		return;
	}

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	this->prev_scan_action_is_ = this->next_scan_and_save_();
	if (this->prev_scan_action_is_ != OK) { // NG or CANCEL
		return; /* 始めにエラーやキャンセルしたら次はしない */
	}

	/* 次のスキャンがあるなら */
	if (1 <= cl_gts_master.cl_number.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
 cl_gts_master.cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
void cb_scan_and_save::cb_next( void )
{
	/* windowを消す */
	cl_gts_gui.window_next_scan->hide();

	/* 次の番号を得る。ただし以前CANCELであったら以前のまま */
	cl_gts_master.cl_number.counter_next(
		cl_gts_gui.choice_scan_num_continue_type->value()
	);

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	this->prev_scan_action_is_ = this->next_scan_and_save_();
	if (this->prev_scan_action_is_ == NG) {
		return;
	}
	/* キャンセルであっても次を... */
	if (this->prev_scan_action_is_ == CANCEL) {
		cl_gts_master.cl_number.counter_cancel_one_step();
	}

	/* 次のスキャンがあるなら */
	if (1 <= cl_gts_master.cl_number.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
 cl_gts_master.cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
void cb_scan_and_save::cb_rescan( void )
{
	/* windowを消す */
	cl_gts_gui.window_next_scan->hide();

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	this->prev_scan_action_is_ = this->next_scan_and_save_();
	if ( this->prev_scan_action_is_ == NG ) {
		return;
	}
	/* キャンセルであっても次を... */

	/* 次のスキャンがあるなら */
	if (1 <= cl_gts_master.cl_number.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
 cl_gts_master.cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
int cb_scan_and_save::next_scan_and_save_( void )
{
	/* 01 次(始め)の位置を得る */
	int crnt_list_num = cl_gts_master.cl_number.get_crnt_list_num();
	int crnt_file_num = cl_gts_master.cl_number.get_crnt_file_num();
	int next_file_num = cl_gts_master.cl_number.get_next_file_num();
	if (crnt_list_num< 1 || crnt_file_num< 1) {
		pri_funct_err_bttvr(
   "Error : crnt_list_num=%d or crnt_file_num=%d"
			,crnt_list_num ,crnt_file_num );
		return NG;
	}

	/* 02 保存するファイルパスを得る
		DirPath/Level.Number.Ext-->例:"C:/users/public/A.0001.tif"
	*/
	std::string fpath_save( this->get_save_path(crnt_file_num) );
	if (fpath_save.empty()) {
		pri_funct_err_bttvr(
			"Error : this->get_save_path(%d) returns empty"
			, crnt_file_num );
		return NG;
	}

	/* 03 フレーム番号(crnt_list_num)を表示するようリストをスクロール */
	cl_gts_gui.selbro_number_list->middleline(crnt_list_num);

	/* 04 スキャンを実行 */
	int return_code=NG;
	iip_canvas* clp_scan = cl_gts_master.iipg_scan( return_code );
	if (return_code == NG) {
		pri_funct_err_bttvr(
		      "Error : cl_gts_master.iipg_scan() returns NG" );
		return NG;
	}
	if (return_code == CANCEL) {
		return CANCEL;
	}
	if (nullptr == clp_scan) {
		pri_funct_err_bttvr(
		      "Error : cl_gts_master.iipg_scan() returns nullptr" );
		return NG;
	}

	/* 05 回転、2値化、ドットノイズ消去　処理 */
	if (cl_gts_master.rot_and_trace_and_enoise(
		clp_scan ,cl_gts_gui.choice_rot90->value()
	) != OK) {
		return NG;
	}

	/* 06 画像を保存する
		BW/Grayscale/RGB/RGBTraceのどれか
	*/
	if (OK != cl_gts_master.iipg_save(
		&(cl_gts_master.cl_iip_edot)/* Effectの最後Node画像を保存 */
		, const_cast<char *>(fpath_save.c_str())
		, cl_gts_gui.valinp_area_reso->value()
		/* 回転値後を正対として角度ゼロ(default)として保存する */
	) ) {
		pri_funct_err_bttvr(
	 "Error : this->iipg_save(-) returns NG" );
		return NG;
	}

	/* 07 リストに保存済マーク付け "0000" --> "0000 S" */
	cl_gts_master.cl_number.add_S(crnt_list_num);

	/* 08 リストの選択解除 */
	cl_gts_master.cl_number.unselect(crnt_list_num);

	/* 09 画像表示 */
	if (cl_gts_master.redraw_image( clp_scan ,false ,false ) != OK) {
		return NG;
	}

	/* 10 保存するタイプで画像を表示する */
	if ( cl_gts_gui.chkbtn_scan_filter_trace_sw->value() ) {
		/* TracenImage画像のみ表示 */
		cl_gts_master.cb_change_wview_sub();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_sub->setonly();
	}
	else {
		/* ScanImage(メイン)画像のみ表示 */
		cl_gts_master.cb_change_wview_main();

		/* 画像表示状態をメニューに設定 */
		cl_gts_gui.menite_wview_main->setonly();
	}

	/* 11 切抜きはしないのでOFFにしておく */
	cl_gts_master.cl_ogl_view.set_crop_disp_sw(OFF);

	/* 12 次のフレーム番号があるなら、
	次の処理を促すwindowの設定をしておく */
	if (0 < cl_gts_master.cl_number.get_next_file_num()) {
		char	ca8_but[8];
		(void)sprintf( ca8_but ,"%d" ,crnt_file_num );
		cl_gts_gui.norout_crnt_scan_number->value(ca8_but);

		(void)sprintf( ca8_but ,"%d" ,next_file_num );
		cl_gts_gui.norout_next_scan_number->value(ca8_but);

		cl_gts_gui.norout_crnt_scan_level->value(
		 cl_gts_gui.strinp_scan_save_file_head->value()
		);
	}

	return OK;
}

//------------------------------------------------------------
/* ファイルブラウズ/フォルダーブラウズ */
void cb_scan_and_save::cb_browse_save_folder( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_save(
		"Set Saving Folder for Scan"
		,cl_gts_gui.filinp_scan_save_dir_path->value()

	 	,this->get_save_name_(
		 static_cast<int>(cl_gts_gui.valinp_scan_num_start->value())
	 	) + "_" /* 保存を聞いてこないよう存在しない名前にする */

		,this->ext_save.get_native_filters()
		,cl_gts_gui.choice_scan_save_image_format->value()
	).at(0);

	/* Cancel */
	if (filepath.empty()) {
		return;
	}

	/* Save設定 */
	std::string dpath ,fname;
	ids::path::from_fpath_to_dpath_fname(
		filepath ,dpath ,fname
	);
	cl_gts_gui.filinp_scan_save_dir_path->value(dpath.c_str());
}

//------------------------------------------------------------
/* numberセット表示/file存在確認表示 */
void cb_scan_and_save::cb_set_number( void )
{
	/* Scanの番号であることを表示して示す */
	cl_gts_master.cl_number.set_type_to_scan();

	/* 番号範囲(start ,end)を得る */
	int num_s = -1;
	int num_e = -1;
	if (cl_gts_gui.choice_scan_num_continue_type->value()
	== cl_gts_master.cl_number.get_endless_type_value()) {
 num_s = static_cast<int>(cl_gts_gui.valinp_scan_num_start->value());
 num_e = num_s;
	}
	else {
 num_s = static_cast<int>(cl_gts_gui.valinp_scan_num_start->value());
 num_e = static_cast<int>(cl_gts_gui.valinp_scan_num_end->value());
		if (num_e < num_s) {
			std::swap( num_s ,num_e );
		}
	}

	/* End/EndlessによるNumberリストのdeactivate/activete */
	this->cb_change_num_continue_type(
	 cl_gts_gui.choice_scan_num_continue_type->text()
	);

	/* Numberウインドウ再構築 */
	cl_gts_master.cl_number.reset_from_start_to_end( num_s ,num_e );
}

//------------------------------------------------------------
/* 保存する連番ファイルが存在するならファイル名の背景を黄色表示 */
void cb_scan_and_save::cb_check_existing_saved_file(void)
{
	if ( !cl_gts_master.cl_number.is_scan() ) {
		return;
	}
	this->check_existing_saved_file();
}
void cb_scan_and_save::check_existing_saved_file(void)
{
	Fl_Color col = 0;
	if ( this->is_exist_save_files_() ) {	/* 上書き */
		col = FL_YELLOW;
	} else {	/* 新規ファイル */
		col = FL_WHITE;
	}
	cl_gts_gui.filinp_scan_save_dir_path->color(col);
	cl_gts_gui.filinp_scan_save_dir_path->redraw();
	cl_gts_gui.strinp_scan_save_file_head->color(col);
	cl_gts_gui.strinp_scan_save_file_head->redraw();
	cl_gts_gui.output_scan_save_number_format->color(col);
	cl_gts_gui.output_scan_save_number_format->redraw();
	cl_gts_gui.choice_scan_save_image_format->color(col);
	cl_gts_gui.choice_scan_save_image_format->redraw();
}
bool cb_scan_and_save::is_exist_save_files_(void)
{
/* Numberの非選択含めた番号ファイルで一つでも存在するならtrueを返す */
	bool sw=false;
	for (int ii = 1; ii <= cl_gts_gui.selbro_number_list->size(); ++ii) {
		/* リストの項目に表示した番号 */
		const int file_num = std::stoi(
			cl_gts_gui.selbro_number_list->text(ii)
		);
		/* 番号によるファイルパス */
		std::string filepath( this->get_save_path( file_num ) );
		/* ファイルの存在の表示チェック */
		if (	!filepath.empty()
		&& ptbl_dir_or_file_is_exist(const_cast<char*>(
			filepath.c_str()
		))) {
		 sw = true;
		 cl_gts_master.cl_number.replace_with_S( file_num ,ii );
		}
		else {
		 cl_gts_master.cl_number.replace_without_S( file_num ,ii );
		}
	}
	return sw;
}

//----------------------------------------------------------------------
/* save file/path */
const std::string cb_scan_and_save::get_save_path( const int number )
{
	/* Folder & File名が設定していないと空を返す */
	if (cl_gts_gui.filinp_scan_save_dir_path->value() == nullptr
	||  this->get_save_name_(number).empty()) {
		return std::string();
	}

	std::string filepath;
	filepath += cl_gts_gui.filinp_scan_save_dir_path->value();
	filepath += '/';
	filepath += this->get_save_name_( number );
	return filepath;
}
const std::string cb_scan_and_save::get_save_name_( const int number )
{
	/* 名(head,num_form,ext)が設定していないと空を返す */
	if (cl_gts_gui.strinp_scan_save_file_head->value() == nullptr
	||  (0<=number
	&&  cl_gts_gui.output_scan_save_number_format->value() == nullptr)
	||  cl_gts_gui.choice_scan_save_image_format->text() == nullptr) {
		return std::string();
	}

	std::string filename;
	filename += cl_gts_gui.strinp_scan_save_file_head->value();
	if (0 <= number) {
	 filename += ids::path::str_from_number(
		number
		, cl_gts_gui.output_scan_save_number_format->value()
	 );
	}
	filename += cl_gts_gui.choice_scan_save_image_format->text();
	return filename;
}

//----------------------------------------------------------------------
void cb_scan_and_save::cb_choice_and_num_continue_type(const std::string& type)
{
	const Fl_Menu_Item* crnt =
	cl_gts_gui.choice_scan_num_continue_type->find_item( type.c_str() );
	if (crnt == nullptr) { return; }

	/* End/Endless表示のChoice切替 */
	cl_gts_gui.choice_scan_num_continue_type->value(crnt);

	/* End/Endless表示のChoice以外の切替 */
	this->cb_change_num_continue_type( type );
}
void cb_scan_and_save::cb_change_num_continue_type(const std::string& type)
{
	if (std::string("End") == type) {
		cl_gts_gui.valinp_scan_num_end->show();
		cl_gts_gui.choice_scan_num_endless_direction->hide();
		cl_gts_gui.selbro_number_list->activate();
	} else
	if (std::string("Endless") == type) {
		cl_gts_gui.valinp_scan_num_end->hide();
		cl_gts_gui.choice_scan_num_endless_direction->show();
		cl_gts_gui.selbro_number_list->deactivate();
	}
}

void cb_scan_and_save::cb_choice_num_endless_direction( const std::string& type )
{
	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_scan_num_endless_direction->find_item(
		type.c_str() );
	if (crnt == nullptr) { return; }

	cl_gts_gui.choice_scan_num_endless_direction->value(crnt);
}

std::string cb_scan_and_save::get_save_ext_for_legacy_(const std::string& type)
{
	if (type.size() == 4) { return type; }
	for (int ii=0;ii<this->ext_save.size() ;++ii)  {
		if (	 this->ext_save.get_fltk_filter( ii ) == type) {
		 return	 this->ext_save.str_from_num( ii );
		}
	}
	return type;
}
void cb_scan_and_save::cb_choice_save_image_format( const std::string& type )
{
	std::string typestr( this->get_save_ext_for_legacy_(type) );

	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_scan_save_image_format->find_item(
		typestr.c_str() );
	if (crnt == nullptr) { return; }

	cl_gts_gui.choice_scan_save_image_format->value(crnt);
}

void cb_scan_and_save::cb_switch_scan_filter_trace( const bool sw )
{
	if (sw) {
		cl_gts_gui.chkbtn_scan_filter_trace_sw->box(FL_SHADOW_BOX);
		cl_gts_gui.chkbtn_scan_filter_trace_sw->value(1);//ON
	}
	else {
		cl_gts_gui.chkbtn_scan_filter_trace_sw->box(FL_FLAT_BOX);
		cl_gts_gui.chkbtn_scan_filter_trace_sw->value(0);//OFF
	}
}

void cb_scan_and_save::cb_switch_scan_filter_erase_dot_noise( const bool sw )
{
	if (sw) {
 cl_gts_gui.chkbtn_scan_filter_erase_dot_noise_sw->box(FL_SHADOW_BOX);
 cl_gts_gui.chkbtn_scan_filter_erase_dot_noise_sw->value(1);//ON
	}
	else {
 cl_gts_gui.chkbtn_scan_filter_erase_dot_noise_sw->box(FL_FLAT_BOX);
 cl_gts_gui.chkbtn_scan_filter_erase_dot_noise_sw->value(0);//OFF
	}
}

