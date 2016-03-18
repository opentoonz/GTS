#include "gtsfbro06cb_trace_batch.h"
#include "gts_gui.h"

void gtsfbro06cb_trace_batch::_cancel( void )
{
	/* パスを前回のOK時のものに戻す */
	this->change_trace_batch_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_trace_batch_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_trace_batch_list() returns NG" );
		return;
	}
}

void gtsfbro06cb_trace_batch::cb_cancel( void )
{
	this->_cancel();

	cl_gts_gui.menite_trace_batch->clear(); /* menuのcheck外す */
	cl_gts_gui.window_trace_batch->hide();  /* Window閉じる */
}
