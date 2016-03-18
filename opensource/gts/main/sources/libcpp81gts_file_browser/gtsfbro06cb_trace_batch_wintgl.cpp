#include "gtsfbro06cb_trace_batch.h"
#include "gts_gui.h"

void gtsfbro06cb_trace_batch::cb_wintgl( void )
{
	if (	cl_gts_gui.menite_trace_batch->value()) {
		cl_gts_gui.window_trace_batch->show();
	} else {
		this->_cancel();
		cl_gts_gui.window_trace_batch->hide();
	}
}
