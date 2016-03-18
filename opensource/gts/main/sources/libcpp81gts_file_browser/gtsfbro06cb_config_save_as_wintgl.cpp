#include <FL/fl_ask.H>
#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::cb_save_as_wintgl( void )
{
	if (	cl_gts_gui.menite_config_save_as->value()) {
		cl_gts_gui.window_config_save_as->show();
	} else {
		this->_save_as_cancel();
		cl_gts_gui.window_config_save_as->hide();
	}
}
