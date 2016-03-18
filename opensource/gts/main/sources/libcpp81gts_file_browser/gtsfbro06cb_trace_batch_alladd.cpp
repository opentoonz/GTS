#include <string.h>
#include "gtsfbro06cb_trace_batch.h"
#include "gts_gui.h"

/*
	run listに同じものがあればマーク、なければ追加し、
	select状態にする
*/
int gtsfbro06cb_trace_batch::_mark_or_add_from_list( int i_selected )
{
	int     ii;

	/* 加えるパスを設定 */
	if (OK != this->i_path_dir_file(
		cl_gts_gui.filinp_trace_batch_dir->value(),
		cl_gts_gui.selbro_trace_batch_list->text(i_selected)
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NG",
		cl_gts_gui.filinp_trace_batch_dir->value(),
		cl_gts_gui.selbro_trace_batch_list->text(i_selected)
		);
		return NG;
	}

	/* 同じパスがあるか調べる */
	for (ii=1; ii<= cl_gts_gui.selbro_trace_batch_run_list->size();
	++ii) {
		/* 同じパスがあった */
		if (!strcmp( this->cp_path(),
			cl_gts_gui.selbro_trace_batch_run_list->text(ii)
		)) {
			/* 同じパスをselect状態にする */
			cl_gts_gui.selbro_trace_batch_run_list->select(ii);
			return OK;
		}
	}

	/* 同じパスがなければ新規パスを加える */
	cl_gts_gui.selbro_trace_batch_run_list->insert(
	 cl_gts_gui.selbro_trace_batch_run_list->size()+1, this->cp_path()
	);

	/* 追加したパスをselect状態にする */
	cl_gts_gui.selbro_trace_batch_run_list->select(
	 cl_gts_gui.selbro_trace_batch_run_list->size()
	);

	return OK;
}

void gtsfbro06cb_trace_batch::cb_alladd( void )
{
	int     ii;

	/* run listすべてunselectする */
	for (ii=1; ii<= cl_gts_gui.selbro_trace_batch_run_list->size();
	++ii) {
	     cl_gts_gui.selbro_trace_batch_run_list->select( ii, 0 );
	}

	/* file listをloop */
	for (ii=2; ii<= cl_gts_gui.selbro_trace_batch_list->size(); ++ii) {
		/* run listに同じものがあればマーク、なければ追加し、
		select状態にする */
		if (OK != this->_mark_or_add_from_list(ii)) {
			pri_funct_err_bttvr(
		 "Error : this->_mark_or_add_from_list(%d) returns NG",
				ii
			);
			return;
		}
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
