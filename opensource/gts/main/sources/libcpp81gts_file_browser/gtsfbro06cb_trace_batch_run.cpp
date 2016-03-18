#include "gtsfbro06cb_trace_batch.h"
#if !defined GTS_DEBUG
# include "gts_master.h"
#endif
#include "gts_gui.h"

void gtsfbro06cb_trace_batch::_trace_a_level( char *cp_path )
{
#if !defined GTS_DEBUG
	/* 読み込み設定する、このときtrace batch情報のみ設定しない */
	if (OK != cl_gts_master.cl_memo_config.load( cp_path, OFF )) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_memo_config.load(%s,OFF) returns NG",
			cp_path );
		return;
	}

	/* 全画面をredraw */
	Fl::check();

	/* trace実行 */
	cl_gts_master.cb_read_and_save_start();
#endif
}

void gtsfbro06cb_trace_batch::cb_run( void )
{
	int     ii;

	/* 全て選択する */
	for (ii=1; ii<= cl_gts_gui.selbro_trace_batch_run_list->size();
	++ii) {
		cl_gts_gui.selbro_trace_batch_run_list->select(ii);
	}

	/* 実行loop */
	for (ii=1; ii<= cl_gts_gui.selbro_trace_batch_run_list->size();
	++ii) {
		/* 1 level trace実行 */
		this->_trace_a_level(
		(char *)cl_gts_gui.selbro_trace_batch_run_list->text(ii)
		);

		/* 実行後選択解除 */
		cl_gts_gui.selbro_trace_batch_run_list->select(ii,0);
	}
}

void gtsfbro06cb_trace_batch::cb_close( void )
{
	/* 現在ディレクトリをメモリする */
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

	/* 正常終了したら閉じる */
	cl_gts_gui.menite_trace_batch->clear(); /* menuのcheck外す */
	cl_gts_gui.window_trace_batch->hide();  /* Window 閉じる */
}
