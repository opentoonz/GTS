#include <FL/filename.H>	/* fl_filename_isdir() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_rgb_scan_dir( void )
{
	if (fl_filename_isdir(
		cl_gts_gui.filinp_level_open_dir_path->value()
	)) {
		this->change_level_list();
	}
}
