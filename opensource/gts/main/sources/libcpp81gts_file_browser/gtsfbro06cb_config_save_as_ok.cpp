#include <FL/fl_ask.H>
#include "ptbl_funct.h"
#include "gtsfbro06cb_config.h"
#if !defined GTS_DEBUG
# include "gts_master.h"
#endif
#include "gts_gui.h"

void gtsfbro06cb_config::cb_save_as_ok( void )
{
	/* configファイルへのパス名を設定 */
	if (OK != this->i_path_dir_file(
		cl_gts_gui.filinp_config_save_as_dir->value(),
		cl_gts_gui.strinp_config_save_as_file->value(),
		this->ccp_text_file_ext()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s,%s) returns NULL",
		cl_gts_gui.filinp_config_save_as_dir->value(),
		cl_gts_gui.strinp_config_save_as_file->value(),
		this->ccp_text_file_ext()
		);
		return;
	}

	/* すでに存在するなら上書き確認のダイオローグを表示 */
	if (ptbl_dir_or_file_is_exist( this->cp_path() )) {
		if (0 == fl_ask("Overwrite<%s>?",this->cp_path())) {
			return;
		}
	}

	/* 存在しないときは保存確認のダイオローグを表示 */
	/****else {
		if (0 == fl_ask("Save<%s>?",this->cp_path())) {
			return;
		}
	}****/

#if !defined GTS_DEBUG
	/* config情報を保存する */
	if (OK != cl_gts_master.cl_memo_config.save(this->cp_path())) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.save(%s) returns NG",
			this->cp_path() );
		return;
	}
#endif

	/* Config Save As listの更新 */
	if (OK != this->change_config_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_config_list() returns NG");
		return;
	}

	/* 現在ディレクトリを次のCancel用にメモリする */
	if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_config_save_as_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
		cl_gts_gui.filinp_config_save_as_dir->value() );
		return;
	}
	this->v_path_memory();

	/* ファイル名を次のCancel用にメモリする */
	this->_save_as_filename_memory(
		cl_gts_gui.strinp_config_save_as_file->value()
	);

	cl_gts_gui.menite_config_save_as->clear(); /* menuのcheck外す */
	cl_gts_gui.window_config_save_as->hide();  /* Window 閉じる */
}
