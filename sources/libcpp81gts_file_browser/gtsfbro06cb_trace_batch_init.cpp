#include "gtsfbro06cb_trace_batch.h"

int gtsfbro06cb_trace_batch::i_init( void )
{
	this->init_text_buffer(); /* テキスト表示初期設定 */

	/* GUIにDir path設定 */
	this->change_trace_batch_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_trace_batch_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_trace_batch_list() returns NG");
		return NG;
	}
	return OK;
}
