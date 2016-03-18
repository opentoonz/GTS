#include <string.h> /* strlen() */
#include <FL/filename.H> /* fl_filename_isdir() */
#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::cb_save_as_dir( void )
{
	const char *ccp_path;

	ccp_path = cl_gts_gui.filinp_config_save_as_dir->value();

	/* pathがない(NULL or 空文字)か、実在のdirを示したら... */
	if (	(NULL == ccp_path) ||
		('\0' == ccp_path[0]) ||
		fl_filename_isdir(ccp_path)
	) {
		/* save asのdirも同じpathにする */
		cl_gts_gui.filinp_config_load_dir->value(ccp_path);
		cl_gts_gui.filinp_config_load_dir->position(
			strlen(ccp_path)
		);

		/* loadとsave as両方のdir listを再表示する */
		if (OK != this->change_config_list()) {
			pri_funct_err_bttvr(
		 "Error : this->change_config_list() returns NG");
			return;
		}
	}
}
