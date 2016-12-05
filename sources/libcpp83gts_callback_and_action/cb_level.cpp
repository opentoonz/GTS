/*
#include <cstdlib>	// atoi()
#include <cctype>	// isdigit()
#include <cassert>	// assert()
#include <cstring>
#include <sstream>	// std::ostringstream
#include <iomanip>	// std::setw()
#include "ptbl_funct.h"
#include "gts_master.h"
*/
#include "ids_path_fltk_native_browse.h"
#include "ids_path_level_from_files.h"
#include "gts_gui.h"
#include "cb_level.h"

#if 0 /* 開発中2016-12-05 */
void cb_level::set_level_open(
	const std::string& dpath
	,const std::string& head
	,const std::string& num
	,const int number
	,const std::string& ext
	,const std::vector<int>& nums
)
{
	/* 拡張子が対応外エラー */
	if (ext != ".tga" && ext != ".tif") {
		return;
	}
	/* ファイル名に番号がないエラー */
	if (nums.empty()) {
		return "Error : Need Number in Filename";
	}
	/* Levelウインドウに設定 */
	cl_gts_gui.filinp_level_save_dir_path->value(dpath.c_str());
	cl_gts_gui.filinp_level_open_dir_path->value(dpath.c_str());
	cl_gts_gui.strinp_level_save_file_head->value(head.c_str());
	cl_gts_gui.strinp_level_open_file_head->value(head.c_str());
	cl_gts_gui.valinp_level_num_start->value( nums.front() );
	cl_gts_gui.valinp_level_num_end->value( nums.back() );
	if ( ext == ".tif" ) {
	 cl_gts_gui.choice_level_save_image_format->value(0);
	 cl_gts_gui.choice_level_open_image_format->value(0);
	} else
	if ( ext == ".tga" ) {
	 cl_gts_gui.choice_level_save_image_format->value(1);
	 cl_gts_gui.choice_level_open_image_format->value(1);
	}
	/* Levelウインドウに設定 : Start...End範囲指定タイプ */
	cl_gts_gui.valinp_level_num_end->show();
	cl_gts_gui.choice_level_num_endless_direction->hide();
	cl_gts_gui.selbro_fnum_list->activate();
	cl_gts_gui.choice_level_num_continue_type->value(0/*End*/);

	/* Numberリスト再構築。
	ファイル存在マーク付けて選択状態にする */
	cl_gts_master.cl_file_number_list.remake_with_exist_mark_and_select(
		nums ,nums.front() ,nums.back()
	);

	/* Number上部に保存level名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
	 cl_gts_gui.strinp_level_save_file_head->value()
	);

	/* メインウインドウバーに(level名更新)表示 */
	cl_gts_master.print_window_headline();

	/* 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview();
}
#endif

void cb_level::browse_open( void )
{
/* 開発中2017-12-05
	std::vector< std::string > ext_names{ "TIFF" ,"TGA" }
				,ext_dotex{ ".tif" ,".tgs" };
*/

	/* LevelウインドウメニューからFileNameを得る */
	std::string filename;
	filename += cl_gts_gui.strinp_level_open_file_head->value();
	if (0 <= cl_gts_gui.valinp_level_num_start->value()) {
		filename += ids::path::str_from_number(
		static_cast<int>(cl_gts_gui.valinp_level_num_start->value())
		);
	}
	switch (cl_gts_gui.choice_level_open_image_format->value()) {
	case 0: filename += ".tif"; break;
	case 1: filename += ".tga"; break;
	}

	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_open(
		cl_gts_gui.filinp_level_open_dir_path->value()
		,filename
		,"TIFF\t(*.tif)\n" "TGA\t(*.tga)"
		,cl_gts_gui.choice_level_open_image_format->value()
	);

	/* 必要な情報に変える */
	std::string dpath , head , num , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		filepath ,dpath ,head ,num ,number ,ext ,nums
	);

	/* ファイルパスから生成した部品を、GUI、その他セット */
/* 開発中2017-12-05
	this->set_level_open(
		dpath ,head ,num ,number ,ext ,nums
	);
*/
}

void cb_level::browse_save( void )
{
	/* LevelウインドウメニューからFileNameを得る */
	std::string filename;
	filename += cl_gts_gui.strinp_level_save_file_head->value();
	if (0 <= cl_gts_gui.valinp_level_num_start->value()) {
		filename += ids::path::str_from_number(
		static_cast<int>(cl_gts_gui.valinp_level_num_start->value())
		);
	}
	switch (cl_gts_gui.choice_level_save_image_format->value()) {
	case 0: filename += ".tif"; break;
	case 1: filename += ".tga"; break;
	}

	/* NativeブラウザーOpenで開く */
	const std::string filepath = ids::path::fltk_native_browse_save(
		cl_gts_gui.filinp_level_save_dir_path->value()
		,filename
		,"TIFF\t(*.tif)\n" "TGA\t(*.tga)"
		,cl_gts_gui.choice_level_save_image_format->value()
	);
}
