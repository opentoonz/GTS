#include <string.h>
#include "gtsfbro06cb_trace_batch.h"
#include "gts_gui.h"

void gtsfbro06cb_trace_batch::cb_add( void )
{
	int     ii, i_selected;

	/* 選択した番号を得る */
	i_selected = this->get_i_1st_selected();
	if (i_selected < 0) {
		return; /* 選択されていない --> 正常終了 */
	}

	/* run listすべてunselectする */
	for (ii=1; ii<= cl_gts_gui.selbro_trace_batch_run_list->size();
	++ii) {
		cl_gts_gui.selbro_trace_batch_run_list->select( ii, 0 );
	}

	/* run listに同じものがあればマーク、なければ追加し、
	select状態にする */
	if (OK != this->_mark_or_add_from_list(i_selected)) {
		pri_funct_err_bttvr(
	 "Error : this->_mark_or_add_from_list(%d) returns NG",
			i_selected
		);
		return;
	}

	/* 現在ディレクトリを次のCancel用にメモリする */
	if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_trace_batch_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
		cl_gts_gui.filinp_trace_batch_dir->value()
		);
		return;
	}
	this->v_path_memory();
}
