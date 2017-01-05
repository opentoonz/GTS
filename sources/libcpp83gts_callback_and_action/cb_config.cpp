//#include <assert.h>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
//#include "pri.h"
#include "ids_path_level_from_files.h"
#include "ids_path_fltk_native_browse.h"
#include "cb_config.h"
#include "gts_master.h"

void cb_config::loading_and_set_dpath_fname( const std::string& fpath )
{
	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.load( fpath.c_str() )) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.load(%s) returns NG",
			fpath.c_str() );
		return;
	}

	/* DirPath&OpenName記憶 */
	ids::path::from_fpath_to_dpath_fname(
		fpath
		,this->dir_path_
		,this->open_file_name_
	);
}
void cb_config::open( void )
{
	/* DirctoryPathとFileNameを得る */
	if (	this->dir_path_.empty() ) {
		this->dir_path_ = ".";
	}
	if (	this->open_file_name_.empty() ) {
		this->open_file_name_ = "untitled";
		this->open_file_name_ += this->ext_;
	}

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

void cb_config::save_as( void )
{
	/* DirctoryPathとFileNameを得る */
	if (	this->dir_path_.empty() ) {
		this->dir_path_ = ".";
	}
	if (	this->save_file_name_.empty() ) {
		this->save_file_name_ = "untitled";
		this->save_file_name_ += this->ext_;
	}

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
	if (OK != cl_gts_master.cl_memo_config.save( fpath.c_str() )) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.save(%s) returns NG",
			fpath.c_str() );
		return;
	}

	/* DirPath&SaveName記憶 */
	ids::path::from_fpath_to_dpath_fname(
		fpath
		,this->dir_path_
		,this->save_file_name_
	);
}

void cb_config::save( void )
{
	/* まだconfigファイルをOpenもSaveAsもしていないとき */
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
	if (OK != cl_gts_master.cl_memo_config.save( fpath.c_str() )) {
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
