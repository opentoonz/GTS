#include <cstdio>	// std::rename(-)
#include <iostream>	// std::cout
#include <sstream>	// std::ostringstream
#include <iomanip>	// std::setfill(-) ,std::setw(-)
#include <FL/fl_ask.H>  // fl_alert(-) fl_input(-)
#include "pri.h"
#include "ptbl_returncode.h"
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
#include "ids_path_fltk_native_browse.h"
#include "ids_path_level_from_files.h"
#include "cb_trace_files.h"
#include "gts_gui.h"
#include "gts_master.h"

//----------------------------------------------------------------------
/* 2値化処理実行 */
int cb_trace_files::read_and_save_crnt_(
	const int file_num
	,const int list_num
)
{
	/* 表示：リストを対象項目が見える場所にスクロール */
	cl_gts_gui.selbro_number_list->middleline(list_num);

	/* 読込：番号に対するファイルパスを得る */
	std::string fpath_open(  this->get_open_path(file_num) );
	if (fpath_open.empty()) {
		pri_funct_err_bttvr(
			"Error : this->get_open_path(%d) returns nullptr"
			, file_num
		);
		return NG;
	}

	/* 読込：ファイルがあるかチェック */
	if (!ptbl_dir_or_file_is_exist(
		const_cast<char *>(fpath_open.c_str())
	)) {
		pri_funct_msg_ttvr(
	"Error : Not exist \"%s\"",fpath_open.c_str());
		return NG;
	}

	/* 読込：ファイルパスを設定 */
	if (cl_gts_master.cl_iip_read.cl_name.set_name(fpath_open.c_str())
	!= OK) {
		pri_funct_err_bttvr(
   "Error : cl_gts_master.cl_iip_read.cl_name.set_name(%s) returns NG",
			fpath_open.c_str());
		return NG;
	}

	/* 読込 */
	if (cl_gts_master.cl_iip_read.file() != OK) {
		pri_funct_err_bttvr(
   "Error : cl_gts_master.cl_iip_read.file() returns NG" );
		return NG;
	}

	/* 読込：画像はフルカラーであること */
	if (cl_gts_master.cl_iip_read.get_l_channels() < 3) {
		pri_funct_err_bttvr(
   "Error : cl_gts_master.cl_iip_read.get_l_channels() is less than 3" );
		return NG;
	}

	/* 処理：Rot90 and Effects(color Trace and Erase color dot noise) */
	if (cl_gts_master.rot_and_trace_and_enoise(
		&(cl_gts_master.cl_iip_read)
		,0	/* 画像コンバート処理のみで、回転はしない */
	) != OK) {
		return NG;
	}

	/* 保存：番号に対するファイルパスを得る */
	std::string fpath_save( this->get_save_path(file_num) );
	if (fpath_save.empty()) {
		pri_funct_err_bttvr(
		       "Error : this->get_save_path(%d) returns empty"
			, file_num
		);
		return NG;
	}

	/* 保存 */
	if (OK != cl_gts_master.iipg_save(
		&(cl_gts_master.cl_iip_trac)
		, const_cast<char *>(fpath_save.c_str())
		, cl_gts_master.cl_iip_read.get_d_tif_dpi_x()
		/* rot90実行後なので(デフォルト)0度とする */
		/* (デフォルト)なしとする、
			&(cl_gts_master.cl_iip_read)は参照しない */
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.iipg_save(-) returns NG" );
		return NG;
	}

	/* 表示：リストにマーク付いていなければ付ける */
	cl_gts_master.cl_number.add_S( list_num );

	/* 表示：リストの選択解除 */
	cl_gts_master.cl_number.unselect(list_num);

	/* 表示：画像の再表示 */
	if (cl_gts_master.redraw_image(
		&(cl_gts_master.cl_iip_read)
		, false /* crop sw */
		, false /* force view scanimage sw */
	)) {
		return NG;
	}

	/* 表示：保存するタイプで画像を表示する */
	if ( cl_gts_gui.chkbtn_trace_filter_trace_sw->value() ) {
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

	return OK;
}

int cb_trace_files::cb_start( const bool interactive_sw )
{
	if ( !cl_gts_master.cl_number.is_trace() ) {
		fl_alert("Set Number for Trace");
		return OK;
	}

	/* チェック：開くファイルのLevel名がない */
	{
	std::string name(cl_gts_gui.strinp_trace_open_file_head->value());
	if ( name.empty() ) {
		fl_alert("Need Trace Open Name!");
		return NG;
	}
	}

	/* チェック：保存ファイルのLevel名がない */
	{
	std::string name(cl_gts_gui.strinp_trace_save_file_head->value());
	if ( name.empty() ) {
		fl_alert("Need Trace Save Name!");
		return NG;
	}
	}

	/* チェック：開くファイル名がない */
	if (this->get_open_path(0).empty()) {
		fl_alert("Check Open Folder and File name!");
		return NG;
	}

	/* チェック：保存ファイル名がない */
	if (this->get_save_path(0).empty()) {
		fl_alert("Check Save Folder and File name!");
		return NG;
	}

	/* 順送り(start <= end)の初期位置 */
	cb_number &cl_num = cl_gts_master.cl_number;
	int list_num = cl_num.next_selected_list_num(1);

	/* チェック：番号選択がない */
	if (list_num < 1) {
		fl_alert("Select Number!");
		return NG;
	}

	/* 順送り(start <= end)の初期番号 */
	int file_num = cl_num.file_num_from_list_num(list_num);

	/* 実行確認 */
	if (interactive_sw) {
	 const bool tsw =
	  cl_gts_gui.chkbtn_trace_filter_trace_sw->value() != 0;
	 const bool esw =
	  cl_gts_gui.chkbtn_trace_filter_erase_dot_noise_sw->value() != 0;
	 if (fl_ask(
		"%s%s\n%s\n-->\n%s\n..."
		,tsw ?"Trace" :"Not trace"
		,esw ?" and Erase Dot Noise" :""
		,this->get_open_path(file_num).c_str()
		,this->get_save_path(file_num).c_str()
	 ) != 1) {
		return OK; // Cancel
	 }
	}

	while (1 <= list_num) {
		/* カレントの読み込みと処理と保存をして */
		if (OK != this->read_and_save_crnt_( file_num ,list_num )) {
			pri_funct_err_bttvr(
		 "Error : this->read_and_save_crnt_() returns NG" );
			return NG;
		}
		/* 次を得る */
		list_num = cl_num.next_selected_list_num( list_num + 1 );
		file_num = cl_num.file_num_from_list_num( list_num );

		Fl::check();
		const int ekey = Fl::event_key();

		/* FL_Escapeと'q'と't'は効かない */
		//if (FL_Escape == ekey) {
		//if ('q' == ekey) {
		//if ('t' == ekey) { /* Tで開始し、tで終る */

		if ('e' == ekey) {
			break;
		}
	}
	return OK;
}

//----------------------------------------------------------------------
/* rename/renumber処理実行 */
void cb_trace_files::cb_rename(void)
{
	/* Openファイルのフルパスを得る */
	const std::string filepath = this->get_open_path( 1 );
	if (filepath.empty()) {
		fl_alert( "Not set Open Folder or File name" );
		return;
	}

	/* 連番ファイルの存在チェックして必要な情報に変える */
	std::string dpath , head , num , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		filepath ,dpath ,head ,num ,number ,ext ,nums
	);
	if (head.empty() || nums.size() <= 0) {
		fl_alert( "Not exist files" );
		return;
	}
	std::ostringstream numost;
	for (auto nu : nums) {
		numost << nu;
		numost << " ";
	}

	/* ユーザーから新しい名前を得る */
	const char* new_head_ptr = fl_input(
		"Enter New Level Name" ,head.c_str()
	);
	if (new_head_ptr == nullptr || head == new_head_ptr ) {
		return; /* Cancel or 同じ名前なら何もしない */
	}
	const std::string new_head(new_head_ptr);

	/* ファイル毎名前を変更する */
	for (size_t ii=0; ii<nums.size() ; ++ii) {
		std::string opa( this->get_open_path( nums.at(ii) ) );
		std::string npa( this->get_open_path_from_head_and_number_(
			new_head.c_str() ,nums.at(ii)
		));
		/* 最初にこれでいいかユーザーに確認する */
		if (ii==0) {
			if (fl_ask(
 "Rename\nFrom\n %s\nTo\n %s\nNumber List\n %s\nOK?"
				,opa.c_str()
				,npa.c_str()
				,numost.str().c_str()
			) != 1) {
				return; // Cancel
			}
		}
		std::rename( opa.c_str() ,npa.c_str() );
	}

	/* rename成功したら、新しい名前に表示変更 */
	cl_gts_gui.strinp_trace_open_file_head->value( new_head.c_str() );
}

void cb_trace_files::cb_renumber(void)
{
	/* Openファイルのフルパスを得る */
	const std::string filepath = this->get_open_path( 1 );
	if (filepath.empty()) {
		fl_alert( "Not set Open Folder or File name" );
		return;
	}

	/* 連番ファイルの存在チェックして必要な情報に変える */
	std::string dpath , head , num , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		filepath ,dpath ,head ,num ,number ,ext ,nums
	);
	if (head.empty() || nums.size() <= 0) {
		fl_alert( "Not exist files" );
		return;
	}

	/* ユーザーから新しいStart番号を得る */
	const char* new_start_num_ptr = fl_input(
		"Enter New Start Number" ,std::to_string(nums.at(0)).c_str()
	);
	if (new_start_num_ptr == nullptr
	||  std::stoi(std::string(new_start_num_ptr))==nums.at(0)) {
		return; /* Cancel or 同じ名前なら何もしない */
	}
	const std::string new_start_num( new_start_num_ptr );

	/* 新しいStart番号との差 */
	const int diff_num = std::stoi(new_start_num) - nums.at(0);

	/* エラー数値をチェックしつつ番号を文字列に入れる */
	std::ostringstream numost;
	bool error_sw = false;
	for (auto nu : nums) {
		numost << nu + diff_num;
		numost << " ";
		if ( nu + diff_num < 0 || 9999 < nu + diff_num ) {
			error_sw = true;
		}
	}

	/* ゼロ以下数値があるとエラーメッセージダイオローグを出して終わる */
	if (error_sw) {
		std::string opa( this->get_open_path( nums.at(0) ) );
		std::string npa( this->get_open_path(
				nums.at(0) + diff_num ) );
		fl_alert(
"Error : Number need 0...9999 range\nFrom\n %s\nTo\n %s\nNumber List\n %s\n"
			,opa.c_str()
			,npa.c_str()
			,numost.str().c_str()
		);
		return;
	}

	/* ファイル毎名前を変更する */
	for (size_t ii=0; ii<nums.size() ; ++ii) {
		std::string opa( this->get_open_path( nums.at(ii) ) );
		std::string npa( this->get_open_path(
				nums.at(ii) + diff_num ) );
		/* 最初にこれでいいかユーザーに確認する */
		if (ii==0) {
			if (fl_ask(
"Renumber\nFrom\n %s\nTo\n %s\nNumber List\n %s\nOK?"
				,opa.c_str()
				,npa.c_str()
				,numost.str().c_str()
			) != 1) {
				return; // Cancel
			}
		}
		std::rename( opa.c_str() ,npa.c_str() );
	}

	/* renumber成功したら、新しいStart,End,Numberに表示変更 */
	this->cb_set_number();
	this->cb_check_existing_saved_file();
}

//----------------------------------------------------------------------
/* ファイルブラウズ/フォルダーブラウズ */
void cb_trace_files::cb_browse_open_file( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_open(
		"Open Image"
		,cl_gts_gui.filinp_trace_open_dir_path->value()
		,this->get_open_name_from_number_(
		static_cast<int>(cl_gts_gui.valout_trace_num_start->value())
		)
		,this->ext_open.get_native_filters()
		,cl_gts_gui.choice_trace_open_image_format->value()
	).at(0);

	/* Cancel */
	if (filepath.empty()) {
		return;
	}

	/* 必要な情報に変える */
	std::string dpath , head , num , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		filepath ,dpath ,head ,num ,number ,ext ,nums
	);

	/* チェック：ファイルヘッド(file head名)が空だとなにもしない */
	if (head.empty()) {
		fl_alert("No Head of OpenFileName");
		return;
	}

	/* チェック：拡張子が対応した種類でないと何もしない */
	const int ext_num = this->ext_open.num_from_str( ext );
	if ( ext_num < 0 ) {
		fl_alert("Bad Extension\"%s\" of OpenFileName",ext.c_str());
		return;
	}

	/* チェック：開く対象の番号リスト(ファイルの存在)確認 */
	if (nums.empty()) {
		fl_alert("No Numbers with OpenFileName");
		return;
	}

	/* Scanの番号であることを表示して示す */
	cl_gts_master.cl_number.set_type_to_trace();

	/* ファイルパスから生成した部品を、GUI、その他セット */
	this->set_gui_for_open( dpath ,head ,num ,ext ,nums );

	/* 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview();
}
void cb_trace_files::set_gui_for_open(
	const std::string& dpath
	,const std::string& head
	,const std::string& num
	,const std::string& ext
	,const std::vector<int>& nums
)
{
	/* Trace Filesウインドウ Open設定 */
	cl_gts_gui.filinp_trace_open_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_trace_open_file_head->value(head.c_str());
	cl_gts_gui.strinp_trace_open_number_format->value(num.c_str());
	int ext_num = this->ext_open.num_from_str(ext);
	if (ext_num < 0) { ext_num = 0; }
	cl_gts_gui.choice_trace_open_image_format->value(ext_num);

	/* Trace Filesウインドウ Number設定 */
	cl_gts_gui.valout_trace_num_start->value( nums.front() );
	cl_gts_gui.valout_trace_num_end->value( nums.back() );

	/* Trace Filesウインドウ 即表示 */
	cl_gts_gui.window_trace_files->flush();

	/* Numberウインドウ Listを操作可能にする */
	cl_gts_gui.selbro_number_list->activate();

	/* Numberウインドウ再構築 */
	cl_gts_master.cl_number.reset_by_number_list( nums );
}
void cb_trace_files::cb_browse_save_folder( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_save(
		"Set Saving Folder for Trace"
		,cl_gts_gui.filinp_trace_save_dir_path->value()

		,this->get_save_name_(
		static_cast<int>(cl_gts_gui.valout_trace_num_start->value())
	 	) + "_" /* 保存を聞いてこないよう存在しない名前にする */

		,this->ext_save.get_native_filters()
		,cl_gts_gui.choice_trace_save_image_format->value()
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
	cl_gts_gui.filinp_trace_save_dir_path->value(dpath.c_str());
}

//----------------------------------------------------------------------
/* numberセット表示/file存在確認表示 */
void cb_trace_files::cb_set_number( void )
{
	/* Traceの番号であることを表示して示す */
	cl_gts_master.cl_number.set_type_to_trace();

	/* 必要な情報に変える */
	std::string filepath( this->get_open_path( 0 ) );
	std::string dpath , head , num , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		filepath ,dpath ,head ,num ,number ,ext ,nums
	);
	if (head.empty() || nums.empty() || nums.size() <= 0) {
		fl_alert( "Not exist file about \'%s\'" ,filepath.c_str() );
		return;
	}

	/* Trace Filesウインドウ Number設定 */
	cl_gts_gui.valout_trace_num_start->value( nums.front() );
	cl_gts_gui.valout_trace_num_end->value( nums.back() );

	/* Trace Filesウインドウ 即表示 */
	cl_gts_gui.window_trace_files->flush();

	/* Numberウインドウ Listを操作可能にする */
	cl_gts_gui.selbro_number_list->activate();

	/* Numberウインドウ再構築 */
	cl_gts_master.cl_number.reset_by_number_list( nums );
}

//----------------------------------------------------------------------
/* 保存する連番ファイルが存在するならファイル名の背景を黄色表示 */
void cb_trace_files::cb_check_existing_saved_file(void)
{
	if ( !cl_gts_master.cl_number.is_trace() ) {
		return;
	}
	this->check_existing_saved_file();
}
void cb_trace_files::check_existing_saved_file(void)
{
	Fl_Color col = 0;
	if ( this->is_exist_save_files_() ) {	/* 上書き */
		col = FL_YELLOW;
	} else {	/* 新規ファイル */
		col = FL_WHITE;
	}
	cl_gts_gui.filinp_trace_save_dir_path->color(col);
	cl_gts_gui.filinp_trace_save_dir_path->redraw();
	cl_gts_gui.strinp_trace_save_file_head->color(col);
	cl_gts_gui.strinp_trace_save_file_head->redraw();
	//cl_gts_gui.strinp_trace_save_number_format->color(col);
	//cl_gts_gui.strinp_trace_save_number_format->redraw();
	cl_gts_gui.output_trace_save_number_format->color(col);
	cl_gts_gui.output_trace_save_number_format->redraw();
	cl_gts_gui.choice_trace_save_image_format->color(col);
	cl_gts_gui.choice_trace_save_image_format->redraw();
}
bool cb_trace_files::is_exist_save_files_(void)
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
		if (   !filepath.empty()
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
/* open file/path */
const std::string cb_trace_files::get_open_path( const int number )
{
	/* Folder & File名が設定していないと空を返す */
	if (cl_gts_gui.filinp_trace_open_dir_path->value() == nullptr
	||  this->get_open_name_from_number_( number ).empty()) {
		return std::string();
	}

	std::string filepath;
	filepath += cl_gts_gui.filinp_trace_open_dir_path->value();
	filepath += '/';
	filepath += this->get_open_name_from_number_( number );
	return filepath;
}
const std::string cb_trace_files::get_open_name_from_number_( const int number )
{
	return this->get_open_name_from_head_and_number_( 
		cl_gts_gui.strinp_trace_open_file_head->value() ,number );
}
const std::string cb_trace_files::get_open_name_from_head_and_number_(
	const std::string& file_head
	,const int number
)
{
	/* 名(head,num_form,ext)が設定していないと空を返す */
	if (file_head.empty()
	|| (0 <= number
	&& cl_gts_gui.strinp_trace_open_number_format->value() == nullptr)
	|| cl_gts_gui.choice_trace_open_image_format->text() == nullptr) {
		return std::string();
	}

	std::string filename(file_head);
	if (0 <= number) {
	 filename += ids::path::str_from_number(
	   number , cl_gts_gui.strinp_trace_open_number_format->value()
	 );
	}
	filename += cl_gts_gui.choice_trace_open_image_format->text();
	return filename;
}

const std::string cb_trace_files::get_open_path_from_head_and_number_(
	const std::string& file_head
	,const int number
)
{
	/* Folder & File名が設定していないと空を返す */
	if (cl_gts_gui.filinp_trace_open_dir_path->value() == nullptr
	||  this->get_open_name_from_head_and_number_(
	file_head,number).empty()) {
		return std::string();
	}

	std::string filepath;
	filepath += cl_gts_gui.filinp_trace_open_dir_path->value();
	filepath += '/';
	filepath += this->get_open_name_from_head_and_number_(
		file_head ,number
	);
	return filepath;
}

//----------------------------------------------------------------------
/* save file/path */
const std::string cb_trace_files::get_save_path( const int number )
{
	/* Folder & File名が設定していないと空を返す */
	if (cl_gts_gui.filinp_trace_save_dir_path->value() == nullptr
	|| this->get_save_name_( number ).empty()) {
		return std::string();
	}

	std::string filepath;
	filepath += cl_gts_gui.filinp_trace_save_dir_path->value();
	filepath += '/';
	filepath += this->get_save_name_( number );
	return filepath;
}

const std::string cb_trace_files::get_save_name_( const int number )
{
	/* 名(head,num_form,ext)が設定していないと空を返す */
	if (cl_gts_gui.strinp_trace_save_file_head->value() == nullptr
	||  (0 <= number
	&&  cl_gts_gui.output_trace_save_number_format->value() == nullptr)
	||  cl_gts_gui.choice_trace_save_image_format->text() == nullptr) {
		return std::string();
	}

	std::string filename;
	filename += cl_gts_gui.strinp_trace_save_file_head->value();
	if (0 <= number) {
	 filename += ids::path::str_from_number(
		number
		, cl_gts_gui.output_trace_save_number_format->value()
	 );
	}
	filename += cl_gts_gui.choice_trace_save_image_format->text();
	return filename;
}
//----------------------------------------------------------------------
std::string cb_trace_files::get_open_ext_for_legacy_(const std::string& type)
{
	if (type.size() == 4) { return type; }
	for (int ii=0;ii<this->ext_open.size() ;++ii)  {
		if (	 this->ext_open.get_fltk_filter( ii ) == type) {
		return	 this->ext_open.str_from_num( ii );
		}
	}
	return type;
}
std::string cb_trace_files::get_save_ext_for_legacy_(const std::string& type)
{
	if (type.size() == 4) { return type; }
	for (int ii=0;ii<this->ext_save.size() ;++ii)  {
		if (	 this->ext_save.get_fltk_filter( ii ) == type) {
		 return	 this->ext_save.str_from_num( ii );
		}
	}
	return type;
}

void cb_trace_files::cb_choice_open_image_format( const std::string& type )
{
	std::string typestr( this->get_open_ext_for_legacy_(type) );

	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_trace_open_image_format->find_item(
		typestr.c_str() );
	if (crnt == nullptr) { return; }
	cl_gts_gui.choice_trace_open_image_format->value(crnt);
}
void cb_trace_files::cb_choice_save_image_format( const std::string& type )
{
	std::string typestr( this->get_save_ext_for_legacy_(type) );

	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_trace_save_image_format->find_item(
		typestr.c_str() );
	if (crnt == nullptr) { return; }
	cl_gts_gui.choice_trace_save_image_format->value(crnt);
}
//----------------------------------------------------------------------
void cb_trace_files::cb_switch_trace_filter_erase_dot_noise( const bool sw )
{
	if (sw) {
 cl_gts_gui.chkbtn_trace_filter_erase_dot_noise_sw->box(FL_SHADOW_BOX);
 cl_gts_gui.chkbtn_trace_filter_erase_dot_noise_sw->value(1);//ON
	}
	else {
 cl_gts_gui.chkbtn_trace_filter_erase_dot_noise_sw->box(FL_FLAT_BOX);
 cl_gts_gui.chkbtn_trace_filter_erase_dot_noise_sw->value(0);//OFF
	}
}
