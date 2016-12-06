#include <algorithm> // std::find(-)
#include "ids_path_fltk_native_browse.h"
#include "ids_path_level_from_files.h"
#include "cb_level.h"
#include "gts_gui.h"
#include "gts_master.h"

ids::path::extensions::extensions()
	:names_({ "TIFF" ,"Targa" })
	,dotex_({ ".tif" ,".tga" })
{}
const std::string ids::path::extensions::str_from_num( const int num )
{
	if (static_cast<int>(this->count_::size) <= num) {
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
/*
	for (int ii=0 ;ii<this->dotex_.size() ;++ii) {
		if (this->dotex_.at(ii) == ext) {
			return ii;
		}
	}
*/
	return -1;
}
const std::string ids::path::extensions::get_native_filter( void )
{
	std::string str;

	for (int ii=0 ;ii<static_cast<int>(this->count_::size) ;++ii) {
		str += this->names_.at(ii);
		str += "\t*";
		str += this->dotex_.at(ii);
		str += "\n";
	}
	return str;
}

void cb_level::set_level_open(
	ids::path::extensions& et
	,const std::string& dpath
	,const std::string& head
	,const std::string& ext
	,const std::vector<int>& nums
)
{
	/* ファイルヘッド(Level名)が空だとなにもしない */
	if (head.empty()) {
		return;
	}

	/* 01 拡張子が対応した種類でないと何もしない */
	const int ext_num = et.num_from_str( ext );
	if ( ext_num < 0 ) {
		return;
	}

	/* 02 開く対象の番号リスト(ファイルの存在)確認 */
	if (nums.empty()) {
		return;
	}

	/* 03 Levelウインドウ Open設定 */
	cl_gts_gui.filinp_level_open_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_level_open_file_head->value(head.c_str());
	cl_gts_gui.choice_level_open_image_format->value(ext_num);

	/* 04 Levelウインドウ Number設定 */
	cl_gts_gui.valinp_level_num_start->value( nums.front() );
	cl_gts_gui.valinp_level_num_end->value( nums.back() );
	cl_gts_gui.valinp_level_num_end->show();
	cl_gts_gui.choice_level_num_endless_direction->hide();
	cl_gts_gui.choice_level_num_continue_type->value(0/*End*/);

	/* 再表示 */
	cl_gts_gui.window_level_set->redraw();

	/* 05 Numberウインドウ List再構築
	ファイル存在マーク付けて選択状態にする
	存在するファイルの番号(nums)のみリストに */
	cl_gts_master.cl_file_number_list.remake_with_exist_mark_and_select(
		nums ,nums.front() ,nums.back()
	);

	/* 06 Numberウインドウ List表示設定 */
	cl_gts_gui.selbro_fnum_list->activate();

	/* 07 Numberウインドウ 保存level名表示 */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
	 cl_gts_gui.strinp_level_save_file_head->value()
	);

	/* 再表示 */
	cl_gts_gui.window_fnum_list->redraw();

	/* 08 Mainウインドウ バーにlevel名表示 */
	cl_gts_master.print_window_headline();

	/* 09 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview();
}
void cb_level::set_level_save(
	ids::path::extensions& et
	,const std::string& dpath
	,const std::string& head
	,const std::string& ext
	,const std::vector<int>& nums
)
{
	/* ファイルヘッド(Level名)が空だとなにもしない */
	if (head.empty()) {
		return;
	}

	/* 01 拡張子が対応した種類かどうか確認 */
	if (!ext.empty()) {
	 const int ext_num = et.num_from_str( ext );
	 if ( ext_num < 0 ) {
		return;
	 }
	}

	/* 02 保存する範囲num_start,num_end
	マイナスの場合番号指定はない */

	/* 03 Levelウインドウ Save設定 */
	cl_gts_gui.filinp_level_save_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_level_save_file_head->value(head.c_str());
	if (!ext.empty()) {
	 const int ext_num = et.num_from_str( ext );
	 cl_gts_gui.choice_level_save_image_format->value(ext_num);
	}

	/* 04 Levelウインドウ Number設定
	指定あれば設定する、なければ既にある数値を使う */
	if (!nums.empty()) {
	 cl_gts_gui.valinp_level_num_start->value( nums.front() );
	 cl_gts_gui.valinp_level_num_end->value(   nums.back() );
	}

	/* 05 Numberウインドウ List再構築
	ファイル存在マーク付けて選択状態にする
	番号範囲(num_start,num_end)をリストに */
	std::vector<int> nums_dummy;
	cl_gts_master.cl_file_number_list.remake_with_exist_mark_and_select(
		nums_dummy
		,static_cast<int>(cl_gts_gui.valinp_level_num_start->value())
		,static_cast<int>(cl_gts_gui.valinp_level_num_end->value())
	);

	/* 06 Numberウインドウ List表示設定は現状維持 */

	/* 07 Numberウインドウ 保存level名表示 */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
	 cl_gts_gui.strinp_level_save_file_head->value()
	);

	/* 08 Mainウインドウ バーにlevel名表示 */
	cl_gts_master.print_window_headline();

	/* 09 画像読込表示はしない */
}

void cb_level::browse_open( void )
{
	ids::path::extensions et;

	/* LevelウインドウメニューからFileNameを得る */
	std::string filename;
	filename += cl_gts_gui.strinp_level_open_file_head->value();
	if (filename.empty()) {
	 filename += "untitled";
	}
	if (0 <= cl_gts_gui.valinp_level_num_start->value()) {
	 filename += ids::path::str_from_number(
		static_cast<int>(cl_gts_gui.valinp_level_num_start->value())
	 );
	}
	filename += et.str_from_num(
		cl_gts_gui.choice_level_open_image_format->value()
	);

	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_open(
		cl_gts_gui.filinp_level_open_dir_path->value()
		,filename
		,et.get_native_filter()
		,cl_gts_gui.choice_level_open_image_format->value()
	);

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
	this->set_level_open( et ,dpath ,head ,ext ,nums );
}

void cb_level::browse_save( void )
{
	ids::path::extensions et;

	/* LevelウインドウメニューからFileNameを得る */
	std::string filename;
	filename += cl_gts_gui.strinp_level_save_file_head->value();
	if (filename.empty()) {
	 filename += "untitled";
	}
	if (0 <= cl_gts_gui.valinp_level_num_start->value()) {
	 filename += ids::path::str_from_number(
		static_cast<int>(cl_gts_gui.valinp_level_num_start->value())
	 );
	}
	filename += et.str_from_num(
		cl_gts_gui.choice_level_save_image_format->value()
	);

	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_save(
		cl_gts_gui.filinp_level_save_dir_path->value()
		,filename
		,et.get_native_filter()
		,cl_gts_gui.choice_level_save_image_format->value()
	);

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
	this->set_level_save( et ,dpath ,head ,ext ,nums );
}
