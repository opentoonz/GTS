#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_wintgl( void )
{
	this->cb_x1view_wintgl();
	if (	cl_gts_gui.menite_level->value()) {
		cl_gts_gui.window_level_set->show();
	} else {
		this->_cancel();
		cl_gts_gui.window_level_set->hide();
	}
}
