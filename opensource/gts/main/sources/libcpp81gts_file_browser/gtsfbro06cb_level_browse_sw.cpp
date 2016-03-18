#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_browse_sw( void )
{
	this->change_level_list();
	if (cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
		cl_gts_gui.filinp_level_dir->deactivate();
		cl_gts_gui.filinp_level_rgb_scan_dir->activate();
	} else {
		cl_gts_gui.filinp_level_dir->activate();
		cl_gts_gui.filinp_level_rgb_scan_dir->deactivate();
	}
}
