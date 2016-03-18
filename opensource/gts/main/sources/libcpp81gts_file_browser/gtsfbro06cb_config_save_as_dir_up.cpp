#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

/* ディレクトリを上がる */
void gtsfbro06cb_config::cb_save_as_dir_up( void )
{
	const char *ccp_dir;

	ccp_dir = cl_gts_gui.filinp_config_save_as_dir->value();

	if (OK != this->i_path_dir_up( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_up(%s) returns NG",ccp_dir);
		return;
	}

	this->change_config_dir();

	if (OK != this->change_config_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_config_list() returns NG");
		return;
	}
}
