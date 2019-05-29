#include <iostream>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "pri.h"
#include "osapi_exist.h"
#include "gts_str_language.h" // gts_str::
#include "ids_path_level_from_files.h"
#include "ids_path_fltk_native_browse.h"
#include "cb_config.h"
#include "gts_gui.h"
#include "gts_master.h"

int cb_config::loading_and_set_dpath_fname(
	const std::string& fpath
	,const bool load_trace_batch_sw
)
{
	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.load(
		fpath ,load_trace_batch_sw
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.load(%s,%s) returns NG"
	 		, fpath.c_str()
			, load_trace_batch_sw ?"true" :"false"
		);
		return NG;
	}

	//---------- after reading ----------

	/* DirPath&OpenName記憶 */
	ids::path::from_fpath_to_dpath_fname(
		fpath
		,this->dir_path_
		,this->open_file_name_
	);

	/* 開いたconfigファイルに保存するように名前を記憶 */
	this->save_file_name_ = this->open_file_name_;

	/* 記憶した名前を表示する */
	cl_gts_master.print_window_headline();

	return OK;
}
void cb_config::open( void )
{
	/* NativeブラウザーOpenで開く */
	int filter_current=0;
	const std::string fpath = ids::path::fltk_native_browse_open(
//		"Open Config"
		gts_str::config::open
		,this->dir_path_
		,"" //,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,filter_current
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* fpathを設定し、config情報を保存する */
	this->loading_and_set_dpath_fname( fpath );
}
void cb_config::open_only_area_and_rot90( void )
{
	/* NativeブラウザーOpenで開く */
	int filter_current=0;
	const std::string fpath = ids::path::fltk_native_browse_open(
//		"Open Config only Area and Rot90"
		gts_str::config::open_only_area_and_rot90
		,this->dir_path_
		,"" //,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,filter_current
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.load_only_area_and_rot90(
		fpath
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.load_only_area_and_rot90(%s) returns NG"
			, fpath.c_str()
		);
		return;
	}
}
void cb_config::open_only_pixel_type_and_bright( void )
{
	/* NativeブラウザーOpenで開く */
	int filter_current=0;
	const std::string fpath = ids::path::fltk_native_browse_open(
//		"Open Config only Pixel Type and Bright"
		gts_str::config::open_only_pixel_type_and_bright
		,this->dir_path_
		,"" //,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,filter_current
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* config情報を保存する */
	if (OK !=
	cl_gts_master.cl_memo_config.load_only_pixel_type_and_bright(
		fpath
	)) {
		pri_funct_err_bttvr(
"Error : cl_gts_master.cl_memo_config.load_only_pixel_type_and_bright(%s) returns NG"
			, fpath.c_str()
		);
		return;
	}
}
void cb_config::open_only_trace_params( void )
{
	/* NativeブラウザーOpenで開く */
	int filter_current=0;
	const std::string fpath = ids::path::fltk_native_browse_open(
//		"Open Config only Trace Params"
		gts_str::config::open_only_trace_params
		,this->dir_path_
		,"" //,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,filter_current
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* config情報を保存する */
	if (OK !=
	cl_gts_master.cl_memo_config.load_only_trace_params(
		fpath
	)) {
		pri_funct_err_bttvr(
"Error : cl_gts_master.cl_memo_config.load_only_trace_params(%s) returns NG"
			, fpath.c_str()
		);
		return;
	}
}

void cb_config::save_as( void )
{
	/* NativeブラウザーSaveで開く */
	int filter_current=0;
	std::string fpath;
	if (this->save_as_set_scan_images_path_sw) {
		fpath = ids::path::fltk_native_browse_save(
//		"Save Config As"
		gts_str::config::save_as
		,cl_gts_gui.filinp_scan_save_dir_path->value()
		,cl_gts_gui.strinp_scan_save_file_head->value()
		,std::string("Text(Config)\t*")+this->ext_
		,filter_current
		).at(0);
	} else {
		fpath = ids::path::fltk_native_browse_save(
//		"Save Config As"
		gts_str::config::save_as
		,this->dir_path_
		,this->save_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,filter_current
		).at(0);
	}

	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* 拡張子がなければ追加 */
	bool add_ext_sw = false;
	this->add_ext_if_not_exist_( fpath ,add_ext_sw );

	/*
	2018-11-01
	Windowsのファイル保存ブラウザーは、その中では、
	上書きになる場合、上書きの確認を聞いてくる
	しかし、拡張子を書かなくてもいいようにブラウザーの外で
	拡張子を付けている場合、ブラウザー内で感知できないので、
	上書き確認は聞いてこない
	なので
	拡張子を別途付加してそのファイルが存在するなら上書き確認する
	*/
	if ( add_ext_sw && osapi::exist_utf8_mbs(fpath) ) {
		if (0 == fl_ask(
//			"Overwrite \"%s\"?"
			gts_str::config::ask_overwrite
			,fpath.c_str() )) {
			return;
		}
	}

	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.save( fpath )) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.save(%s) returns NG",
			fpath.c_str() );
		return;
	}

	/* 保存名を記憶(開いた名前は変わらない) */
	ids::path::from_fpath_to_dpath_fname(
		fpath
		,this->dir_path_
		,this->save_file_name_
	);

	/* 記憶した名前を表示する */
	cl_gts_master.print_window_headline();
}

void cb_config::save( void )
{
	/* まだconfigファイルをOpenもSaveAsもしていない */
	if ( this->dir_path_.empty() || this->save_file_name_.empty() ) {
		fl_alert(
//			"Use \'Save Config As\'"
			gts_str::config::use_save_config_as
		);
		return;
	}

	/* ファイルパスを得る */
	const std::string fpath( ids::path::fpath_from_dpath_fname(
		this->dir_path_ ,this->save_file_name_
	));

	/* ダイオローグを表示 */
	if (osapi::exist_utf8_mbs(fpath)) {
		/* すでに存在するなら上書き確認 */
		if (0 == fl_ask(
//			"Overwrite \"%s\"?"
			gts_str::config::ask_overwrite
			,fpath.c_str() )){
			return;
		}
	}
	else {
		/* 存在しないときは保存確認 */
		if (0 == fl_ask(
//			"Save \"%s\"?"
			gts_str::config::ask_save
			,fpath.c_str() )) {
			return;
		}
	}

	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.save( fpath )) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.save(%s) returns NG",
			fpath.c_str() );
		return;
	}
}

void cb_config::add_ext_if_not_exist_( std::string&fpath ,bool& add_sw )
{
	if ((fpath.size() < this->ext_.size())
	||  (fpath.substr(fpath.size()-this->ext_.size()) != this->ext_)) {
		fpath += this->ext_;
		add_sw = true;
		return;
	}
	add_sw = false;
}
