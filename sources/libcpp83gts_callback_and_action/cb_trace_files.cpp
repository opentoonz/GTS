#include <cstdio> // std::rename(-)
#include <sstream> // std::ostringstream
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
	cl_gts_gui.selbro_fnum_list->middleline(list_num);

	/* 読込：番号に対するファイルパスを得る */
	std::string fpath_open( this->get_open_path(file_num) );
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
	std::string fpath_save( this->get_save_path_(file_num) );
	if (fpath_save.empty()) {
		pri_funct_err_bttvr(
		       "Error : this->get_save_path_(%d) returns empty"
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
	if ( cl_gts_gui.chkbtn_trace_trace_sw->value() ) {
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

	/* 順送り(start <= end)の初期位置 */
	cb_number &cl_num = cl_gts_master.cl_number;
	const int list_num = cl_num.next_selected_list_num(1);

	/* チェック：番号選択がない */
	if (list_num < 1) {
		fl_alert("Select Number!");
		return NG;
	}

	/* 順送り(start <= end)の初期番号 */
	const int file_num = cl_num.file_num_from_list_num(list_num);

	/* 実行確認 */
	if (interactive_sw) {
	 const bool tsw =
		cl_gts_gui.chkbtn_trace_trace_sw->value() != 0;
	 const bool esw =
		cl_gts_gui.chkbtn_trace_erase_dot_noise_sw->value() != 0;
	 if (fl_ask(
		"%s%s\n%s\n-->\n%s\n..."
		,tsw ?"Trace" :"Not trace"
		,esw ?" and Erase Dot Noise" :""
		,this->get_open_path(file_num).c_str()
		,this->get_save_path_(file_num).c_str()
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
	const char* new_level_ptr = fl_input(
		"Enter New Level Name" ,head.c_str()
	);
	if (new_level_ptr == nullptr || head == new_level_ptr ) {
		return; /* Cancel or 同じ名前なら何もしない */
	}
	const std::string new_level(new_level_ptr);

	/* ファイル毎名前を変更する */
	for (size_t ii=0; ii<nums.size() ; ++ii) {
		std::string opa( this->get_open_path( nums.at(ii) ) );
		std::string npa( this->get_open_path_from_head_and_number_(
			new_level.c_str() ,nums.at(ii)
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
}

void cb_trace_files::cb_renumber(void)
{
	/* Openファイルのフルパスを得る */
	const std::string filepath = this->get_open_path( 1 );

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
}

//----------------------------------------------------------------------
/* ファイルブラウズ/フォルダーブラウズ */
void cb_trace_files::cb_browse_open_file( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_open(
		"Open File"
		,cl_gts_gui.filinp_trace_open_dir_path->value()
		,this->get_open_name_from_number_(
		static_cast<int>(cl_gts_gui.valinp_trace_num_start->value())
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

	/* ファイルパスから生成した部品を、GUI、その他セット */
	this->set_gui_for_open( dpath ,head ,num ,ext ,nums );

	/* 11 画像読込表示 */
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
	/* 01 チェック：ファイルヘッド(file head名)が空だとなにもしない */
	if (head.empty()) {
		fl_alert("No Head of OpenFileName");
		return;
	}

	/* 02 チェック：拡張子が対応した種類でないと何もしない */
	const int ext_num = this->ext_open.num_from_str( ext );
	if ( ext_num < 0 ) {
		fl_alert("Bad Extension\"%s\" of OpenFileName",ext.c_str());
		return;
	}

	/* 03 チェック：開く対象の番号リスト(ファイルの存在)確認 */
	if (nums.empty()) {
		fl_alert("No Numbers with OpenFileName");
		return;
	}

	/* 04 Trace Filesウインドウ Open設定 */
	cl_gts_gui.filinp_trace_open_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_trace_open_file_head->value(head.c_str());
	cl_gts_gui.strinp_trace_open_number_format->value(num.c_str());
	cl_gts_gui.choice_trace_open_image_format->value(ext_num);

	/* 05 Trace Filesウインドウ Number設定 */
	cl_gts_gui.valinp_trace_num_start->value( nums.front() );
	cl_gts_gui.valinp_trace_num_end->value( nums.back() );

	/* 06 Trace Filesウインドウ 即表示 */
	cl_gts_gui.window_window_trace_files->flush();

	/* 07 Numberウインドウ再構築 */
	this->set_number_window_( nums );
}
void cb_trace_files::cb_browse_save_folder( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_save(
		"Set Saving Folder(&File) for Trace"
		,cl_gts_gui.filinp_trace_save_dir_path->value()
		,this->get_save_name_(
		static_cast<int>(cl_gts_gui.valinp_trace_num_start->value())
		)
		,this->ext_save.get_native_filters()
		,cl_gts_gui.choice_trace_save_image_format->value()
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

	/* ファイルヘッド(Level名)が空だとなにもしない */
	if (head.empty()) {
		fl_alert("No Head of SaveFileName");
		return;
	}

	/* 拡張子が対応した種類かどうか確認 */
	if (!ext.empty()) {
	 const int ext_num = this->ext_save.num_from_str( ext );
	 if ( ext_num < 0 ) {
		fl_alert("Bad Extension\"%s\" of SaveFileName",ext.c_str());
		return;
	 }
	}

	/* Save設定 */
	cl_gts_gui.filinp_trace_save_dir_path->value(dpath.c_str());
/*
	cl_gts_gui.strinp_trace_save_file_head->value(head.c_str());
	cl_gts_gui.strinp_trace_save_number_format->value(num.c_str());
	if (!ext.empty()) {
	 const int ext_num = this->ext_save.num_from_str( ext );
	 cl_gts_gui.choice_trace_save_image_format->value(ext_num);
	}
*/
}

//----------------------------------------------------------------------
/* numberセット表示/file存在確認表示 */
void cb_trace_files::cb_set_number( void )
{
	std::string filepath( this->get_save_path_( 0 ) );

	/* 必要な情報に変える */
	std::string dpath , head , num , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		filepath ,dpath ,head ,num ,number ,ext ,nums
	);

	this->set_number_window_( nums );
}

/*  Numberウインドウ再構築 */
void cb_trace_files::set_number_window_(
	const std::vector<int>& nums
)
{
	/* Numberウインドウ List再構築
		01 リスト全消去
		02 numsからリストに表示しファイル存在なら'S'マーク付ける
		03 リスト全選択
	*/
	cl_gts_master.cl_number.remove_all();
	for (int nn : nums) {
		if (ptbl_dir_or_file_is_exist(const_cast<char*>(
			this->get_save_path_(nn).c_str()
		))) {
		 cl_gts_master.cl_number.append_with_S(nn);
		}
		else {
		 cl_gts_master.cl_number.append_without_S(nn);
		}
	}
	cl_gts_master.cl_number.select_all();

	/* Numberウインドウ Listを操作可能にする */
	cl_gts_gui.selbro_fnum_list->activate();

	/* Numberウインドウ 保存level名表示 */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
	 cl_gts_gui.strinp_trace_save_file_head->value()
	);

	/* Numberウインドウ 即表示 */
	cl_gts_gui.window_number->flush();
}

//----------------------------------------------------------------------
/* 保存する連番ファイルが存在するならファイル名の背景を黄色表示 */
void cb_trace_files::cb_check_existing_saved_file(void)
{
	bool overwrite_sw = this->is_exist_save_files_();

	if (overwrite_sw) {	/* 上書き */
		Fl_Color col = FL_YELLOW;
		cl_gts_gui.strinp_trace_save_file_head->color(col);
		cl_gts_gui.strinp_trace_save_file_head->redraw();
	} else {	/* 新規ファイル */
		Fl_Color col = FL_WHITE;
		cl_gts_gui.strinp_trace_save_file_head->color(col);
		cl_gts_gui.strinp_trace_save_file_head->redraw();
	}
}
bool cb_trace_files::is_exist_save_files_(void)
{
/* Numberの非選択含めた番号ファイルで一つでも存在するならtrueを返す */
	for (int ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		std::string filepath( this->get_save_path_(
			std::stoi( /* リストの項目に表示した番号 */
				cl_gts_gui.selbro_fnum_list->text(ii)
			)
		) );
		if (ptbl_dir_or_file_is_exist(const_cast<char*>(
			filepath.c_str()
		))) {
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
/* open file/path */
const std::string cb_trace_files::get_open_path( const int number )
{
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
	std::string filename(file_head);
	if (filename.empty()) {
	 filename += "untitled";
	}
	if (0 <= number) {
	 filename += ids::path::str_from_number(
	   number , cl_gts_gui.strinp_trace_open_number_format->value()
	 );
	}
	filename += cl_gts_gui.choice_trace_open_image_format->text() ;
	return filename;
}

const std::string cb_trace_files::get_open_path_from_head_and_number_(
	const std::string& file_head
	,const int number
)
{
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
const std::string cb_trace_files::get_save_path_( const int number )
{
	std::string filepath;
	filepath += cl_gts_gui.filinp_trace_save_dir_path->value();
	filepath += '/';
	filepath += this->get_save_name_( number );
	return filepath;
}

const std::string cb_trace_files::get_save_name_( const int number )
{
	std::string filename;
	filename += cl_gts_gui.strinp_trace_save_file_head->value();
	if (filename.empty()) {
	 filename += "untitled";
	}
	if (0 <= number) {
	 filename += ids::path::str_from_number(
	   number , cl_gts_gui.strinp_trace_save_number_format->value()
	 );
	}
	filename += cl_gts_gui.choice_trace_save_image_format->text() ;
	return filename;
}
//----------------------------------------------------------------------
void cb_trace_files::cb_choice_open_image_format( const std::string& type )
{
	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_trace_open_image_format->find_item(
		type.c_str() );
	if (crnt == nullptr) { return; }
	cl_gts_gui.choice_trace_open_image_format->value(crnt);
}
void cb_trace_files::cb_choice_save_image_format( const std::string& type )
{
	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_trace_save_image_format->find_item(
		type.c_str() );
	if (crnt == nullptr) { return; }
	cl_gts_gui.choice_trace_save_image_format->value(crnt);
}
//----------------------------------------------------------------------
