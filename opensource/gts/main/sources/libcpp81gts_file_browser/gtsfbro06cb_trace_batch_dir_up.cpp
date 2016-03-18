#include "gtsfbro06cb_trace_batch.h"
#include "gts_gui.h"

/* ディレクトリを上がる */
void gtsfbro06cb_trace_batch::cb_dir_up( void )
{
	const char *ccp_dir;

	ccp_dir = cl_gts_gui.filinp_trace_batch_dir->value();

	if (OK != this->i_path_dir_up( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_up(%s) returns NG",ccp_dir);
		return;
	}

	this->change_trace_batch_dir();

	if (OK != this->change_trace_batch_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_trace_batch_list() returns NG" );
		return;
	}
}
