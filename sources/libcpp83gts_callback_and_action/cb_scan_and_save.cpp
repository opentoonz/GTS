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

const char* cb_scan_and_save::cb_start_check_( void )
{
	/* 01 チェック：スキャンモードであること */
	if ( !cl_gts_master.cl_number.is_scan() ) {
		return "Set Number for Scan";
	}

	/* 02 チェック：保存ファイルのLevel名があること */
	std::string name(cl_gts_gui.strinp_scan_save_file_head->value());
	if ( name.empty() ) {
		return "Need Scan Save Name!";
	}

	/* 03 値セット：選択リストから先頭を得る */
	cl_gts_master.cl_number.counter_start(
		cl_gts_gui.choice_scan_num_continue_type->value()
	);

	/* 04 チェック：番号リストの選択からカレントを得る */
	if (cl_gts_master.cl_number.get_crnt_file_num() < 1) {
		if (cl_gts_gui.choice_scan_num_continue_type->value()
		== cl_gts_master.cl_number.get_end_type_value()
		) {	/* End type */
		return "Select Number!";
		}
		else {	/* Endless type */
		return "Bad Number in Start!";
		}
	}
	return "";
}

std::string cb_scan_and_save::cb_scan_fx_display_( int& return_code )
{
	/* 01 チェック：スキャンする番号を得る */
	if (cl_gts_master.cl_number.get_crnt_list_num() < 1
	||  cl_gts_master.cl_number.get_crnt_file_num() < 1) {
		std::ostringstream ost;
		ost	<< "Bad Number(crnt_list_num="
			<< cl_gts_master.cl_number.get_crnt_list_num()
			<< ",crnt_file_num="
			<< cl_gts_master.cl_number.get_crnt_file_num()
			<< ")"
		;
		return_code = NG;
		return ost.str();
	}

	/* 02 表示：スキャンするフレーム番号位置にリストをスクロール */
	cl_gts_gui.selbro_number_list->middleline(
		cl_gts_master.cl_number.get_crnt_list_num()
	);

	/* 03 スキャン：実行 */
	iip_canvas* clp_scan_err = cl_gts_master.iipg_scan( return_code );
	if (return_code == NG) {
		return_code = NG;
		return std::string("Can not Scan(NG)");
	}

	/* 04 スキャン：ユーザーからキャンセル指示があればここまで */
	if (return_code == CANCEL) {
		return_code = CANCEL;
		return std::string();
	}

	/* 05 スキャン：return_codeチェックのあとにエラーチェックする */
	if (nullptr == clp_scan_err) {
		return_code = NG;
		return std::string("Can not Scan(nullptr)");
	}

	//------------------------------

	/* 06 画像処理：回転、2値化、ドットノイズ消去 */
/*
	if (cl_gts_master.rot_and_trace_and_enoise(
		cl_gts_master.cl_iip_scan.get_clp_canvas()
		,cl_gts_gui.choice_rot90->value()
	) != OK) {
		return_code = NG;
		return std::string("Can not Fx");
	}
*/

	//------------------------------

	/* 07 表示：Crop以外の画像をスキャンし表示をする場合 */
	cl_gts_master.cl_area_and_rot90.reset_dpi_to_zero_by_scan_or_preview();

	/* 08 表示：Crop(切抜き)はしないのでOFFにしておく */
	cl_gts_master.cl_ogl_view.set_crop_disp_sw(OFF);

	/* 09 表示：画像 */
	if (cl_gts_master.redraw_image(
		cl_gts_master.cl_iip_scan.get_clp_canvas()
		,false ,false ) != OK) {
		return_code = NG;
		return std::string("Can not Redraw");
	}

	/* 10 表示：保存するタイプで画像を表示する */
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

	return_code = OK;
}

std::string cb_scan_and_save::cb_save_( void )
{
	/* 01 保存するファイルパスを得る
	DirPath/Level.Number.Ext-->例:"C:/users/public/A.0001.tif" */
	std::string fpath_save( this->get_save_path(
		cl_gts_master.cl_number.get_crnt_file_num()
	) );
	if (fpath_save.empty()) {
		std::ostringstream ost;
		ost	<< "Can not get save_file_path at current_number("
			<< cl_gts_master.cl_number.get_crnt_file_num()
			<< ")"
			;
		return ost.str();
	}

	/* 02 画像を保存する BW/Grayscale/RGB/RGBTraceのどれか */
	if (OK != cl_gts_master.iipg_save(
		&(cl_gts_master.cl_iip_edot)/* Effectの最後Node画像を保存 */
		, const_cast<char *>(fpath_save.c_str())
		, cl_gts_gui.valinp_area_reso->value()
		/* 回転値後を正対として角度ゼロ(default)として保存する */
	) ) {
		std::ostringstream ost;
		ost	<< "Can not Save file("
			<< fpath_save
			<< ")"
			;
		return ost.str();
	}

	/* 03 リストに保存済マーク付け "0000" --> "0000 S" */
	cl_gts_master.cl_number.add_S(
	 cl_gts_master.cl_number.get_crnt_list_num()
	);

	/* 04 リストの選択解除 */
	cl_gts_master.cl_number.unselect(
	 cl_gts_master.cl_number.get_crnt_list_num()
	);

	return std::string();
}

void cb_scan_and_save::cb_set_next_window_( void )
{
	if (cl_gts_master.cl_number.get_next_file_num() <= 0) {
		return;
	}
 {
	std::ostringstream ost;
	ost << cl_gts_master.cl_number.get_crnt_file_num();
	std::string str(ost.str());
	cl_gts_gui.norout_crnt_scan_number->value( str.c_str() );
 }
 {
	std::ostringstream ost;
	ost << cl_gts_master.cl_number.get_next_file_num();
	std::string str(ost.str());
	cl_gts_gui.norout_next_scan_number->value( str.c_str() );
 }
	cl_gts_gui.norout_crnt_scan_level->value(
		cl_gts_gui.strinp_scan_save_file_head->value()
	);
}
void cb_scan_and_save::cb_set_next_window_non_modal_( void )
{
	std::string fpath_save( this->get_save_path(
		cl_gts_master.cl_number.get_crnt_file_num()
	) );
	cl_gts_gui.norout_next_save_non_modal->value( fpath_save.c_str() );
	cl_gts_gui.norout_next_save_non_modal->position(
	cl_gts_gui.norout_next_save_non_modal->size()
	);
}

//-----------------------------

void cb_scan_and_save::cb_start( void )
{
	/* ショートカット動作で連続してキーインしたときの誤動作防止 */
	if ( this->during_the_scan_is_ == true ) { return; }
	this->during_the_scan_is_ = true;

	/* 連番処理のパラメータチェックと、連番の始めの番号をセット */
	{
	std::string err_msg( this->cb_start_check_() );
	if ( !err_msg.empty() ) {
		this->during_the_scan_is_ = false;
		fl_alert( err_msg.c_str() ); return;
	}
	}

 {
	/* スキャンしエフェクト処理し表示をする */
	int return_code = NG;
	std::string err_msg( this->cb_scan_fx_display_( return_code ) );

	/* start時のユーザーキャンセルは動作終了する */
	if (return_code == CANCEL) {
		this->during_the_scan_is_ = false;
		return;
	}

	/* NGの時は動作終了する */
	if (return_code == NG) {
		this->during_the_scan_is_ = false;
		fl_alert( err_msg.c_str() ); return;
	}
 }

	/* 調整しないで次番号を処理する */
	if (cl_gts_gui.chkbtn_scan_adjustable_per_frame_sw->value() == 0) {
		/* 保存処理 */
		this->cb_save();
	}
	/* 調整してから次番号を処理する */
	else {
		/* ファイル保存を促すwindowの設定をしておく */
		this->cb_set_next_window_non_modal_();

		/* 今の画像を保存を促すウインドウを表示する */
		Fl::focus( cl_gts_gui.button_next_save_non_modal );
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_next_scan_non_modal->show();
	}
}
void cb_scan_and_save::cb_next( void )
{
	/* ショートカット動作のとき、連続してキーインしたときの誤動作防止 */
	if ( this->during_the_scan_is_ == true ) { return; }
	this->during_the_scan_is_ = true;

	/* nextウインドウを消す */
	cl_gts_gui.window_next_scan_non_modal->position(
	cl_gts_gui.window_next_scan->x(),
	cl_gts_gui.window_next_scan->y()
	);
	cl_gts_gui.window_next_scan->hide();

	/* 次の番号をセット */
	cl_gts_master.cl_number.counter_next(
		cl_gts_gui.choice_scan_num_continue_type->value()
	);

	/* スキャンしエフェクト処理し表示をする */
	int return_code = NG;
	std::string err_msg = this->cb_scan_fx_display_( return_code );

	/* next時のユーザーキャンセルはフレーム戻して次フレームスキャンへ */
	if (return_code == CANCEL) {
		cl_gts_master.cl_number.counter_cancel_one_step();
		this->during_the_scan_is_ = false;
		Fl::focus( cl_gts_gui.button_rescan );
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_next_scan->show();
		return;
	}

	/* NGの時は動作終了する */
	if (return_code == NG) {
		this->during_the_scan_is_ = false;
		fl_alert( err_msg.c_str() ); return;
	}

	/* 調整しないで次番号を処理する */
	if (cl_gts_gui.chkbtn_scan_adjustable_per_frame_sw->value() == 0) {
		/* 保存処理 */
		this->cb_save();
	}
	/* 調整してから次番号を処理する */
	else {
		/* ファイル保存を促すwindowの設定をしておく */
		this->cb_set_next_window_non_modal_();

		/* 今の画像を保存を促すウインドウを表示する */
		Fl::focus( cl_gts_gui.button_next_save_non_modal );
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_next_scan_non_modal->show();
	}
}
void cb_scan_and_save::cb_rescan( void )
{
	/* ショートカット動作のとき、連続してキーインしたときの誤動作防止 */
	if ( this->during_the_scan_is_ == true ) { return; }
	this->during_the_scan_is_ = true;

	/* nextウインドウを消す */
	cl_gts_gui.window_next_scan_non_modal->position(
	cl_gts_gui.window_next_scan->x(),
	cl_gts_gui.window_next_scan->y()
	);
	cl_gts_gui.window_next_scan->hide();

	/* スキャンしエフェクト処理し表示をする */
	int return_code = NG;
	std::string err_msg = this->cb_scan_fx_display_( return_code );

	/* next時のユーザーキャンセルはフレーム戻して次フレームスキャンへ */
	if (return_code == CANCEL) {
		cl_gts_master.cl_number.counter_cancel_one_step();
		this->during_the_scan_is_ = false;
		Fl::focus( cl_gts_gui.button_rescan );
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_next_scan->show();
		return;
	}

	/* NGの時は動作終了する */
	if (return_code == NG) {
		this->during_the_scan_is_ = false;
		fl_alert( err_msg.c_str() ); return;
	}

	/* 調整しないで次番号を処理する */
	if (cl_gts_gui.chkbtn_scan_adjustable_per_frame_sw->value() == 0) {
		/* 保存処理 */
		this->cb_save();
	}
	/* 調整してから次番号を処理する */
	else {
		/* ファイル保存を促すwindowの設定をしておく */
		this->cb_set_next_window_non_modal_();

		/* 今の画像を保存を促すウインドウを表示する */
		Fl::focus( cl_gts_gui.button_next_save_non_modal );
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_next_scan_non_modal->show();
	}
}
void cb_scan_and_save::cb_save( void )
{
	/* nextウインドウを消す */
	cl_gts_gui.window_next_scan->position(
	cl_gts_gui.window_next_scan_non_modal->x(),
	cl_gts_gui.window_next_scan_non_modal->y()
	);
	cl_gts_gui.window_next_scan_non_modal->hide();

	/* 06 画像処理：回転、2値化、ドットノイズ消去 */
	if (cl_gts_master.rot_and_trace_and_enoise(
		cl_gts_master.cl_iip_scan.get_clp_canvas()
		,cl_gts_gui.choice_rot90->value()
	) != OK) {
		fl_alert("Can not Fx");
		return;
	}

	/* ファイル保存する */
	std::string err_msg = this->cb_save_();
	if ( !err_msg.empty() ) {
		this->during_the_scan_is_ = false;
		fl_alert( err_msg.c_str() );
		/* エラー情報を出して次のフレーム処理に行くことにしとく */
	}

	/* ショートカット動作で連続してキーインしたときの誤動作防止 */
	this->during_the_scan_is_ = false;

	/* 次のフレーム番号あるなら、次処理を促すwindowの設定をしておく */
	this->cb_set_next_window_();

	/* 次のスキャンを促すウインドウを表示する */
	if (1 <= cl_gts_master.cl_number.get_next_file_num()) {
		Fl::focus( cl_gts_gui.button_rescan );
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_next_scan->show();
	}
}

//------------------------------------------------------------
/* ファイルブラウズ/フォルダーブラウズ */
void cb_scan_and_save::cb_browse_save_folder( void )
{
	/* Nativeフォルダーブラウザー開く */
	const std::string filepath =ids::path::fltk_native_browse_directory(
		"Set Saving Folder for Scan"
		,cl_gts_gui.filinp_scan_save_dir_path->value()
	).at(0);

	/* Cancel */
	if (filepath.empty()) {
		return;
	}

	cl_gts_gui.filinp_scan_save_dir_path->value(filepath.c_str());
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
	||  this->get_save_name(number).empty()) {
		return std::string();
	}

	std::string filepath;
	filepath += cl_gts_gui.filinp_scan_save_dir_path->value();
	filepath += '/';
	filepath += this->get_save_name( number );
	return filepath;
}
const std::string cb_scan_and_save::get_save_name( const int number )
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

