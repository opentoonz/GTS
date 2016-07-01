#include <FL/Fl.H>
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/* color trace enhancement windowから、
番号指定してedit color windowを開く時 */
void  gts_master::cb_color_trace_tgt_open_01( void )
{ this->cl_color_trace_enhancement.tgt_open_edit_color(
			E_COLOR_TRACE_HAB_01 );
}
void  gts_master::cb_color_trace_tgt_open_02( void )
{ this->cl_color_trace_enhancement.tgt_open_edit_color(
			E_COLOR_TRACE_HAB_02 );
}
void  gts_master::cb_color_trace_tgt_open_03( void )
{ this->cl_color_trace_enhancement.tgt_open_edit_color(
			E_COLOR_TRACE_HAB_03 );
}
void  gts_master::cb_color_trace_tgt_open_04( void )
{ this->cl_color_trace_enhancement.tgt_open_edit_color(
			E_COLOR_TRACE_HAB_04 );
}
void  gts_master::cb_color_trace_tgt_open_05( void )
{ this->cl_color_trace_enhancement.tgt_open_edit_color(
			E_COLOR_TRACE_HAB_05 );
}
void  gts_master::cb_color_trace_tgt_open_06( void )
{ this->cl_color_trace_enhancement.tgt_open_edit_color(
			E_COLOR_TRACE_HAB_06 );
}

