#include <string.h>	/* strlen() */
#include <FL/filename.H>	/* fl_filename_isdir() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_dir( void )
{
	const char *ccp_dir;

	ccp_dir = cl_gts_gui.filinp_level_save_dir->value();
	if (
		(NULL == ccp_dir) ||
		('\0' == ccp_dir[0]) ||
		fl_filename_isdir(ccp_dir)
	) {
		cl_gts_gui.filinp_level_open_dir->value(ccp_dir);
		cl_gts_gui.filinp_level_open_dir->position(
			strlen(ccp_dir)
		);
		this->change_level_list();
	}
}
