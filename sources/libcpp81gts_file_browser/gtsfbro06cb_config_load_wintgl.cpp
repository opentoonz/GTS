#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::cb_load_wintgl( void )
{
	if (    cl_gts_gui.menite_config_load->value()) {
		cl_gts_gui.window_config_load->show();
	} else {
		this->_load_cancel();
		cl_gts_gui.window_config_load->hide();
	}
}
