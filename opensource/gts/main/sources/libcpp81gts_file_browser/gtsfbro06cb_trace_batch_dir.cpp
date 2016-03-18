#include <FL/filename.H> /* fl_filename_isdir() */
#include "gtsfbro06cb_trace_batch.h"
#include "gts_gui.h"

void gtsfbro06cb_trace_batch::cb_dir( void )
{
	const char *ccp_path;

	ccp_path = cl_gts_gui.filinp_trace_batch_dir->value();

	/* pathがない(NULL or 空文字)か、実在のdirを示したら... */
	if (	(NULL == ccp_path) ||
		('\0' == ccp_path[0]) ||
		fl_filename_isdir(ccp_path)
	) {
		/* trace batchのdir listを再表示する */
		if (OK != this->change_trace_batch_list()) {
			pri_funct_err_bttvr(
		 "Error : this->change_trace_batch_list() returns NG"
			);
			return;
		}
	}
}
