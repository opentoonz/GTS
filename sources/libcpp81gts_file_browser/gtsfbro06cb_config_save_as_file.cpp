#include <cstring>
#include <string>
#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::cb_save_as_file( void )
{
	std::string name(
		cl_gts_gui.strinp_config_save_as_file->value()
	);

	/* 入力ファイル名に拡張子を付加する */
	// ccp_text_file_ext is ".txt"
	const unsigned ext_sz = strlen( this->ccp_text_file_ext() );
	if (ext_sz < name.size()) {
		if (name.substr(
			name.size() - ext_sz ,ext_sz
		) == this->ccp_text_file_ext()) {
			name.erase( name.size() - ext_sz );
		}
	}
	name += this->ccp_text_file_ext();

	bool overwrite_sw = false;
	for (int ii = 0; ii < this->i_dir_or_file_used(); ++ii) {
		/* File List */
		if ((E_DIR_OR_FILE_IS_TEXT ==
		this->stp_dir_or_file()[ii].e_type) ||
		    (E_DIR_OR_FILE_IS_DIR ==
		this->stp_dir_or_file()[ii].e_type)) {
			if (name == this->stp_dir_or_file()[ii].cp_name) {
				overwrite_sw = true;
			}
		}
	}

	if (overwrite_sw) {	/* 上書き */
		Fl_Color col = FL_YELLOW;
		//Fl_Color col = (Fl_Color)92;
		//Fl_Color col = (Fl_Color)213;/* satsuei list check近色 */
		cl_gts_gui.strinp_config_save_as_file->color(col);
		cl_gts_gui.strinp_config_save_as_file->redraw();
	} else {	/* 新規ファイル */
		Fl_Color col = FL_WHITE;
		cl_gts_gui.strinp_config_save_as_file->color(col);
		cl_gts_gui.strinp_config_save_as_file->redraw();
	}
}
