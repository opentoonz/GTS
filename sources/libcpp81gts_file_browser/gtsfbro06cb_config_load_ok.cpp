#include <iostream> // std::cout
#include "gtsfbro06cb_config.h"
#if !defined GTS_DEBUG
# include "gts_master.h"
#endif
#include "gts_gui.h"

void gtsfbro06cb_config::cb_load_ok( void )
{
	/* configファイルへのパス名を設定 */
	if (OK != this->i_path_dir_file(
		cl_gts_gui.filinp_config_load_dir->value(),
		cl_gts_gui.strinp_config_load_file->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NG",
		cl_gts_gui.filinp_config_load_dir->value(),
		cl_gts_gui.strinp_config_load_file->value()
		);
		return;
	}

#if !defined GTS_DEBUG
	/* 読み込み設定する */
	if (OK != cl_gts_master.cl_memo_config.load(this->cp_path())) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.load(%s) returns NG",
			this->cp_path() );
		return;
	}
#endif

	/* 現在ディレクトリを次のCancel用にメモリする */
	if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_config_load_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
		cl_gts_gui.filinp_config_load_dir->value()
		);
		return;
	}
	this->v_path_memory();

	/* ファイル名の項目をクリアする */
	//cl_gts_gui.strinp_config_load_file->value(NULL);

	cl_gts_gui.menite_config_load->clear(); /* menuのcheck外す */
	cl_gts_gui.window_config_load->hide();  /* Window 閉じる */
}
