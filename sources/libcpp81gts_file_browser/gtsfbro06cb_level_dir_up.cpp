#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_dir_up( void )
{
	const char *ccp_crnt_dir;

	if (0 == cl_gts_gui.togbut_level_open_browse->value()) {
	 ccp_crnt_dir = cl_gts_gui.filinp_level_save_dir->value();
	} else {
	 ccp_crnt_dir = cl_gts_gui.filinp_level_open_dir->value();
	}

	if (OK != this->i_path_dir_up( ccp_crnt_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_up(%s) returns NG",ccp_crnt_dir);
		return;
	}

	this->change_level_dir();

	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return;
	}
}
