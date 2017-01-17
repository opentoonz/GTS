#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

int gts_master::next_scan_and_save_( void )
{
	/* 01 次(始め)の位置を得る */
	int crnt_list_num = this->cl_file_number_list.get_crnt_list_num();
	int crnt_file_num = this->cl_file_number_list.get_crnt_file_num();
	int next_file_num = this->cl_file_number_list.get_next_file_num();
	if (crnt_list_num< 1 || crnt_file_num< 1) {
		pri_funct_err_bttvr(
   "Error : crnt_list_num=%d or crnt_file_num=%d"
			,crnt_list_num ,crnt_file_num );
		return NG;
	}

	/* 02 保存するファイルパスを得る
		DirPath/Level.Number.Ext-->例:"C:/users/public/A.0001.tif"
	*/
	std::string fpath_save(
		this->cl_level.get_savefilepath(crnt_file_num)
	);
	if (fpath_save.empty()) {
		pri_funct_err_bttvr(
	"Error : this->cl_level.get_savefilepath(%d) returns empty"
			, crnt_file_num );
		return NG;
	}

	/* 03 フレーム番号(crnt_list_num)を表示するようリストをスクロール */
	cl_gts_gui.selbro_fnum_list->middleline(crnt_list_num);

	/* 04 スキャンを実行 */
	iip_canvas* clp_scan = this->_iipg_scan();
	if (nullptr == clp_scan) {
		pri_funct_err_bttvr(
		      "Error : this->_iipg_scan() returns nullptr" );
// std::string str("Error in scaning at next!";
// fl_alert(str.c_str());
		return NG;
	}

	/* 05 回転、2値化、ドットノイズ消去　処理 */
	if (this->rot_and_trace_and_enoise_(
		clp_scan ,cl_gts_gui.choice_rot90->value()
	) != OK) {
		return NG;
	}

	/* 06 画像を保存する
		BW/Grayscale/RGB/RGBTraceのどれか
	*/
	if (OK != this->_iipg_save(
		&(cl_gts_master.cl_iip_edot)/* Effectの最後Node画像を保存 */
		, const_cast<char *>(fpath_save.c_str())
		, cl_gts_gui.valinp_area_reso->value()
		/* 回転値後を正対として角度ゼロ(default)として保存する */
	) ) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_save(-) returns NG" );
		return NG;
	}

	/* 07 リストに保存済マーク付け "0000" --> "0000 S" */
	this->cl_file_number_list.add_S(crnt_list_num);

	/* 08 リストの選択解除 */
	this->cl_file_number_list.unselect(crnt_list_num);

	/* 09 画像表示 */
	if (this->redraw_image_( clp_scan ,false ,false ) != OK) {
		return NG;
	}

	/* 10 保存するタイプで画像を表示する */
	if ( cl_gts_gui.chkbtn_scan_trace_sw->value() ) {
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
	this->cl_ogl_view.set_crop_disp_sw(OFF);

	/* 12 次のフレーム番号があるなら、
	次の処理を促すwindowの設定をしておく */
	if (0 < this->cl_file_number_list.get_next_file_num()) {
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

/*--------------------------------------------------------*/

void gts_master::cb_scan_and_save_start( void )
{
	/* 先頭を得る */
	this->cl_file_number_list.counter_start(
		cl_gts_gui.choice_scan_num_continue_type->value()
	);

	/* 保存ファイルのLevel名がない */
	{
	std::string name(cl_gts_gui.strinp_scan_save_file_head->value());
	if ( name.empty() ) {
		fl_alert("Need Save Level Name!");
		return;
	}
	}

	/* 最初に番号が選択がない */
	/* 最初に番号が選択がない/設定できない */
	if (this->cl_file_number_list.get_crnt_file_num() < 1) {
		if (cl_gts_gui.choice_scan_num_continue_type->value()
		== cl_gts_master.cl_file_number_list.get_end_type_value()
		) {/*End*/
			fl_alert("Select number!");
		}
		else {/* Endless */
			fl_alert("Bad number in Start!");
		}
		return;
	}

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (this->next_scan_and_save_() != OK) {
		return;
	}

	/* 次のスキャンがあるなら */
	if (1 <= this->cl_file_number_list.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}
void gts_master::cb_scan_and_save_next( void )
{
	/* windowを消す */
	cl_gts_gui.window_next_scan->hide();

	/* 次の番号を得る */
	this->cl_file_number_list.counter_next(
		cl_gts_gui.choice_scan_num_continue_type->value()
	);

	/* カレントのスキャンと保存をして、次があるなら準備もする */
	if (this->next_scan_and_save_() != OK) {
		return;
	}

	/* 次のスキャンがあるなら */
	if (1 <= this->cl_file_number_list.get_next_file_num()) {
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
	if ( this->next_scan_and_save_() != OK ) {
		return;
	}

	/* 次のスキャンがあるなら */
	if (1 <= this->cl_file_number_list.get_next_file_num()) {
		/* Spaceに関しては常にここでfocus設定が必要2014-02-03 */
	this->cl_memo_short_cut_key.set_space_key_focus_in_next_scan();

		/* 次をどうするかwindowを表示して指示を仰ぐ */
		cl_gts_gui.window_next_scan->show();
	}
}

//------------------------------------------------------------

#include <algorithm> // std::find(-)
#include <cstdio> // std::rename(-)
#include <utility> // std::swap(-)
#include <sstream> // std::ostringstream
#include <FL/fl_ask.H>  // fl_alert(-) fl_input(-)
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
#include "ids_path_fltk_native_browse.h"
#include "ids_path_level_from_files.h"
#include "cb_level.h"
#include "gts_gui.h"
#include "gts_master.h"

//---------- extensions ----------
ids::path::extensions::extensions()
{}
const std::string ids::path::extensions::str_from_num( const int num )
{
	if (static_cast<int>(this->dotex_.size()) <= num) {
		return std::string();
	}

	return this->dotex_.at(num);
}
const int ids::path::extensions::num_from_str( const std::string& ext )
{
	auto it = std::find(this->dotex_.begin() ,this->dotex_.end() ,ext);
	if ( it == this->dotex_.end() ) {
		return -1;
	}
	return static_cast<int>(std::distance(this->dotex_.begin(), it));
}
void ids::path::extensions::set_filter(
	const std::string& name ,const std::string& dotex
)
{
	this->names_.push_back( name );
	this->dotex_.push_back( dotex );
}
const std::string ids::path::extensions::get_native_filters( void )
{
	std::string str;

	/* Exsamples
		"Text\t*.txt\n"
		"C Files\t*.{cxx,h,c}"
	*/
	for (int ii=0 ;ii<static_cast<int>(this->dotex_.size()) ;++ii) {
		str += this->names_.at(ii);
		str += "\t*";
		str += this->dotex_.at(ii);
		str += "\n";
	}
	/* 拡張子が2個以上のときは全部をまとめたFilterも追加しとく */
	if (2 <= this->dotex_.size()) {
		str += "Image Files\t*.{";
		for(int ii=0;ii<static_cast<int>(this->dotex_.size());++ii){
			if (0 < ii) {
				str += ',';
			}
			if (this->dotex_.at(ii).at(0) == '.') {
				str += this->dotex_.at(ii).substr(1);
			}
			else {
				str += this->dotex_.at(ii);
			}
		}
		str += "}";
	}
	return str;
}
const std::string ids::path::extensions::get_fltk_filter( const int num )
{
	std::string str;
	if (num < 0 || static_cast<int>(this->dotex_.size()) <= num) {
		return str;
	}
	str += this->names_.at(num);
	str += "(*";
	str += this->dotex_.at(num);
	str += ")";
	return str;
}
//---------- extensions ----------

void cb_level::set_level_open(
	const std::string& dpath
	,const std::string& head
	,const std::string& ext
	,const std::vector<int>& nums
)
{
	/* ファイルヘッド(Level名)が空だとなにもしない */
	if (head.empty()) {
		fl_alert("No Head of OpenFileName");
		return;
	}

	/* 01 拡張子が対応した種類でないと何もしない */
	const int ext_num = this->ext_open.num_from_str( ext );
	if ( ext_num < 0 ) {
		fl_alert("Bad Extension\"%s\" of OpenFileName",ext.c_str());
		return;
	}

	/* 02 開く対象の番号リスト(ファイルの存在)確認 */
	if (nums.empty()) {
		fl_alert("No Numbers with OpenFileName");
		return;
	}

	/* 03 Levelウインドウ Open設定 */
	cl_gts_gui.filinp_trace_open_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_trace_open_file_head->value(head.c_str());
	cl_gts_gui.choice_trace_open_image_format->value(ext_num);

	/* 04 Levelウインドウ Number設定 */
	cl_gts_gui.valinp_scan_num_start->value( nums.front() );
	cl_gts_gui.valinp_scan_num_end->value( nums.back() );
	cl_gts_gui.valinp_scan_num_end->show();
	cl_gts_gui.choice_scan_num_continue_type->value(0/*End*/);
	cl_gts_gui.choice_scan_num_endless_direction->hide();

	/* 即表示 */
	cl_gts_gui.window_window_scan_and_save->flush();

	/* 05 Numberウインドウ List再構築
	ファイル存在マーク付けて選択状態にする
	--> 存在するファイルの番号(nums)のみリストに表示する */
	cl_gts_master.cl_file_number_list.remove_all();
	for (int num : nums) {
		if (ptbl_dir_or_file_is_exist(const_cast<char*>(
			this->get_savefilepath(num).c_str()
		))) {
		 cl_gts_master.cl_file_number_list.append_with_S(num);
		}
		else {
		 cl_gts_master.cl_file_number_list.append_without_S(num);
		}
	}
	cl_gts_master.cl_file_number_list.select_all();


	/* 06 Numberウインドウ List表示設定 */
	cl_gts_gui.selbro_fnum_list->activate();

	/* 07 Numberウインドウ 保存level名表示 */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
	 cl_gts_gui.strinp_scan_save_file_head->value()
	);

	/* 即表示 */
	cl_gts_gui.window_number->flush();

	/* 08 Mainウインドウ バーにlevel名表示 */
	//cl_gts_master.print_window_headline();

	/* 09 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview();
}
void cb_level::set_level_save(
	const std::string& dpath
	,const std::string& head
	,const std::string& ext
	,const std::vector<int>& nums
)
{
	/* ファイルヘッド(Level名)が空だとなにもしない */
	if (head.empty()) {
		fl_alert("No Head of SaveFileName");
		return;
	}

	/* 01 拡張子が対応した種類かどうか確認 */
	if (!ext.empty()) {
	 const int ext_num = this->ext_save.num_from_str( ext );
	 if ( ext_num < 0 ) {
		fl_alert("Bad Extension\"%s\" of SaveFileName",ext.c_str());
		return;
	 }
	}

	/* 02 保存する範囲num_start,num_end
	マイナスの場合番号指定はない */

	/* 03 Levelウインドウ Save設定 */
	cl_gts_gui.filinp_scan_save_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_scan_save_file_head->value(head.c_str());
	if (!ext.empty()) {
	 const int ext_num = this->ext_save.num_from_str( ext );
	 cl_gts_gui.choice_scan_save_image_format->value(ext_num);
	}

	/* 04 Levelウインドウ Number設定
	指定あれば設定する、なければ既にある数値を使う */
	if (!nums.empty()) {
	 cl_gts_gui.valinp_scan_num_start->value( nums.front() );
	 cl_gts_gui.valinp_scan_num_end->value(   nums.back() );
	}

	/* 05 NumberウインドウList再構 & Level名表示 */
	this->set_number_and_savelevelname();
}

const std::string cb_level::openfilename_from_level_num_(
	const std::string& open_level
	,const int num
)
{
	std::string filename(open_level);
	if (filename.empty()) {
	 filename += "untitled";
	}
	if (0 <= num) {
	 filename += ids::path::str_from_number( num );
	}
	filename += this->ext_open.str_from_num(
		cl_gts_gui.choice_trace_open_image_format->value()
	);
	return filename;
}
const std::string cb_level::openfilepath_from_level_num_(
	const std::string& open_level
	,const int num
)
{
	std::string filepath;
	filepath += cl_gts_gui.filinp_trace_open_dir_path->value();
	filepath += '/';
	filepath += this->openfilename_from_level_num_( open_level ,num );
	return filepath;
}
const std::string cb_level::get_openfilename( const int num )
{
	return this->openfilename_from_level_num_( 
		cl_gts_gui.strinp_trace_open_file_head->value() ,num );
}

const std::string cb_level::get_savefilename( const int num )
{
	std::string filename;
	filename += cl_gts_gui.strinp_scan_save_file_head->value();
	if (filename.empty()) {
	 filename += "untitled";
	}
	if (0 <= num) {
	 filename += ids::path::str_from_number( num );
	}
	filename += this->ext_save.str_from_num(
		cl_gts_gui.choice_scan_save_image_format->value()
	);
	return filename;
}

const std::string cb_level::get_openfilepath( const int num )
{
	std::string filepath;
	filepath += cl_gts_gui.filinp_trace_open_dir_path->value();
	filepath += '/';
	filepath += this->get_openfilename( num );
	return filepath;
}
const std::string cb_level::get_savefilepath( const int num )
{
	std::string filepath;
	filepath += cl_gts_gui.filinp_scan_save_dir_path->value();
	filepath += '/';
	filepath += this->get_savefilename( num );
	return filepath;
}

void cb_level::browse_and_set_of_open( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_open(
		"Open Level"
		,cl_gts_gui.filinp_trace_open_dir_path->value()
		,this->get_openfilename(
		static_cast<int>(cl_gts_gui.valinp_scan_num_start->value())
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
	this->set_level_open( dpath ,head ,ext ,nums );
}

void cb_level::browse_and_set_of_save( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_save(
		"Set Saving Level"
		,cl_gts_gui.filinp_scan_save_dir_path->value()
		,this->get_savefilename(
		static_cast<int>(cl_gts_gui.valinp_scan_num_start->value())
		)
		,this->ext_save.get_native_filters()
		,cl_gts_gui.choice_scan_save_image_format->value()
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
	this->set_level_save( dpath ,head ,ext ,nums );
}

void cb_level::set_number_and_savelevelname( void )
{
	/* Numberウインドウ List再構築
	ファイル存在マーク付けて選択状態にする
	--> 番号範囲(num_start,num_end)をリストに */
	std::string cont(cl_gts_gui.choice_scan_num_continue_type->text());
	int num_s = -1;
	int num_e = -1;
	if (cont == "Endless") {
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

	cl_gts_master.cl_file_number_list.remove_all();
	for (int num =num_s ;num <= num_e ; ++num) {
		if (ptbl_dir_or_file_is_exist(const_cast<char*>(
			this->get_savefilepath(num).c_str()
		))) {
		 cl_gts_master.cl_file_number_list.append_with_S(num);
		}
		else {
		 cl_gts_master.cl_file_number_list.append_without_S(num);
		}
	}
	cl_gts_master.cl_file_number_list.select_all();

	/* Numberウインドウ List表示設定は現状維持 */

	/* Numberウインドウ 保存level名表示 */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
	 cl_gts_gui.strinp_scan_save_file_head->value()
	);

	/* Mainウインドウ バーにlevel名表示 */
	//cl_gts_master.print_window_headline();

	/* 画像読込表示はしない */
}

/* Numberの非選択含めた番号ファイルで一つでも存在するならtrueを返す */
bool cb_level::is_exist_save_files_(void)
{
	for (int ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		std::string filepath( this->get_savefilepath(
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

void cb_level::check_save_level_by_existing_file(void)
{
	bool overwrite_sw = this->is_exist_save_files_();

	if (overwrite_sw) {	/* 上書き */
		Fl_Color col = FL_YELLOW;
		cl_gts_gui.strinp_scan_save_file_head->color(col);
		cl_gts_gui.strinp_scan_save_file_head->redraw();
	} else {	/* 新規ファイル */
		Fl_Color col = FL_WHITE;
		cl_gts_gui.strinp_scan_save_file_head->color(col);
		cl_gts_gui.strinp_scan_save_file_head->redraw();
	}
}

/* (openの)連番ファイルの名前変更 */
void cb_level::dialog_rename_at_open(void)
{
	/* Openファイルのフルパスを得る */
	const std::string filepath = this->get_openfilepath( 1 );

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
		std::string opa( this->get_openfilepath( nums.at(ii) ) );
		std::string npa( this->openfilepath_from_level_num_(
				new_level.c_str()
				,nums.at(ii) ));
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

/* (openの)連番ファイルの番号のシフト */
void cb_level::dialog_renumber_at_open(void)
{
	/* Openファイルのフルパスを得る */
	const std::string filepath = this->get_openfilepath( 1 );

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
		std::string opa( this->get_openfilepath( nums.at(0) ) );
		std::string npa( this->get_openfilepath(
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
		std::string opa( this->get_openfilepath( nums.at(ii) ) );
		std::string npa( this->get_openfilepath(
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

/* openのtabに表示を切替 */
void cb_level::display_tab_to_level_open( void )
{
	cl_gts_gui.tabs_level_action->value( cl_gts_gui.group_level_open );
}

