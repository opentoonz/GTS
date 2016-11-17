#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_browse_sw( void )
{
	this->change_level_list();
	if (cl_gts_gui.togbut_level_open_browse->value()) {
		cl_gts_gui.filinp_level_save_dir_path->deactivate();
		cl_gts_gui.filinp_level_open_dir_path->activate();
	} else {
		cl_gts_gui.filinp_level_save_dir_path->activate();
		cl_gts_gui.filinp_level_open_dir_path->deactivate();
	}
}
