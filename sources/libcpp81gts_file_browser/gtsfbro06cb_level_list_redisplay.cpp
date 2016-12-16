#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_list_redisplay( void )
{
	/* 現在ディレクトリの... */
	/******if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_level_save_dir_path->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
		cl_gts_gui.filinp_level_save_dir_path->value()
		);
		return;
	}******/
	/* リストを再表示 */
	this->change_level_list();
}
