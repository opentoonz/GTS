#include <iostream>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
#include "pri.h"
#include "ids_path_level_from_files.h"
#include "ids_path_fltk_native_browse.h"
#include "cb_config.h"
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
	const std::string fpath = ids::path::fltk_native_browse_open(
		"Open Config"
		,this->dir_path_
		,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,0
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* fpathを設定し、config情報を保存する */
	this->loading_and_set_dpath_fname( fpath );
}
void cb_config::open_only_trace_parameters( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string fpath = ids::path::fltk_native_browse_open(
		"Open Config only Trace Parameters"
		,this->dir_path_
		,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,0
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.load_only_trace_parameters(
		fpath
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.load_only_trace_parameters(%s) returns NG"
			, fpath.c_str()
		);
		return;
	}
}
void cb_config::open_only_area_and_rot90( void )
{
	/* NativeブラウザーOpenで開く */
	const std::string fpath = ids::path::fltk_native_browse_open(
		"Open Config only Area and Rot90"
		,this->dir_path_
		,this->open_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,0
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

void cb_config::save_as( void )
{
	/* NativeブラウザーSaveで開く */
	std::string fpath = ids::path::fltk_native_browse_save(
		"Save As Config"
		,this->dir_path_
		,this->save_file_name_
		,std::string("Text(Config)\t*")+this->ext_
		,0
	).at(0);
	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* 拡張子がなければ追加 */
	this->add_ext_if_not_exist( fpath );

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
		fl_alert("Use \'Save As Config\'");
		return;
	}

	/* ファイルパスを得る */
	const std::string fpath( ids::path::fpath_from_dpath_fname(
		this->dir_path_ ,this->save_file_name_
	));

	/* ダイオローグを表示 */
	if (ptbl_dir_or_file_is_exist(const_cast<char *>(fpath.c_str()))) {
		/* すでに存在するなら上書き確認 */
		if (0 == fl_ask( "Overwrite \"%s\"?" ,fpath.c_str() )){
			return;
		}
	}
	else {
		/* 存在しないときは保存確認 */
		if (0 == fl_ask( "Save \"%s\"?" ,fpath.c_str() )) {
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

void cb_config::add_ext_if_not_exist( std::string&fpath )
{
	if ((fpath.size() < this->ext_.size())
	||  (fpath.substr(fpath.size()-this->ext_.size()) != this->ext_)) {
		fpath += this->ext_;
	}
}
