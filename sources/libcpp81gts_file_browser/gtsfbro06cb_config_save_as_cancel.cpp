#include <string.h>	/* strncpy(-) */
#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::_save_as_filename_memory( const char *ccp_fname )
{
	/* strncpy()は、
	最初のnバイトの中にNULL文字が無ければ、
	コピーの結果としてできる文字列は
	NULLで終端していないものになる。
	*/
	strncpy(this->_ca_save_as_filename_memory,
		ccp_fname,PTBL_PATH_MAX);
	this->_ca_save_as_filename_memory[PTBL_PATH_MAX-1] = '\0';
}

void gtsfbro06cb_config::_save_as_cancel( void )
{
	/* OK時のファイル名に戻す */
	cl_gts_gui.strinp_config_save_as_file->value(
		this->_ca_save_as_filename_memory
	);

	/* パスを前回のOK時のものに戻す */
	this->change_config_dir(this->cp_memory());

	/* GUIにlist表示 */
	if (OK != this->change_config_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_config_list() returns NG" );
		return;
	}
}
void gtsfbro06cb_config::cb_save_as_cancel( void )
{
	this->_save_as_cancel();

	cl_gts_gui.menite_config_save_as->clear(); /* menuのcheck消す */
	cl_gts_gui.window_config_save_as->hide();  /* Window閉じる */
}
