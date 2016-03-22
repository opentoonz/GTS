#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::_load_cancel( void )
{
	/* ファイル名の項目をクリアする */
	cl_gts_gui.strinp_config_load_file->value(NULL);

	/* パスを前回のOK時のものに戻す */
	this->change_config_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_config_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_config_list() returns NG");
	 	return;
	}
}
void gtsfbro06cb_config::cb_load_cancel( void )
{
	this->_load_cancel();

	cl_gts_gui.menite_config_load->clear(); /* menuのcheck消す */
	cl_gts_gui.window_config_load->hide();  /* Window閉じる */
}
