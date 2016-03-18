#include <stdio.h> /* for snprintf() */
#include "gtsfbro03list_gui.h"

void gtsfbro03list_gui::remove_gui_list( Fl_Browser *flp_selbro )
{
	while (0 < flp_selbro->size()) { flp_selbro->remove(1); }
}

void gtsfbro03list_gui::draw_gui_list( Fl_Browser *flp_selbro )
{
	int	ii;
	char	ca_buf[PTBL_PATH_MAX];

	for (ii = 0; ii < this->i_dir_or_file_used(); ++ii) {
		/* Dir List */
		if (E_DIR_OR_FILE_IS_DIR ==
		this->stp_dir_or_file()[ii].e_type) {
			snprintf( ca_buf, PTBL_PATH_MAX, "%s%s",
				this->ccp_dir_mark(),
				this->stp_dir_or_file()[ii].cp_name
			);
		}
		/* File List */
		else {
			snprintf( ca_buf, PTBL_PATH_MAX, "%s",
				this->stp_dir_or_file()[ii].cp_name
			);
		}
		flp_selbro->insert(flp_selbro->size()+1,ca_buf);
	}
	if (0 < this->i_dir_or_file_used()) {
		/* 表示を１行目からに戻す */
		flp_selbro->topline(1);
	}
}
