#include <string.h> /* strcpy() */
#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

int gtsfbro06cb_config::i_init( void )
{
	this->init_text_buffer(); /* テキスト表示初期設定 */

	/* file名を記憶 */
	strcpy(	this->_ca_save_as_filename_memory,
		cl_gts_gui.strinp_config_save_as_file->value()
	);

	/* GUIにdir_path設定 */
	this->change_config_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_config_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_config_list() returns NG");
		return NG;
	}
	return OK;
}
