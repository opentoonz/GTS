#include <string.h>
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_rename( void )
{
	int i_list_crnt;
	const char *ccp_dir_or_level_or_file;
	size_t	t_sz;
	char ca_new[PTBL_PATH_MAX];

	i_list_crnt = cl_gts_gui.selbro_level_list->value();

	/* 選択していない(list下をクリック)なら... */
	if (i_list_crnt <= 0) { return; /* ...何もせず正常終了 */ }

	/* 選択したDir or File or Level名 */
	ccp_dir_or_level_or_file = (char *)(
		cl_gts_gui.selbro_level_list->text( i_list_crnt )
	);
	if (NULL == ccp_dir_or_level_or_file) {
		pri_funct_err_bttvr(
       "Error : cl_gts_gui.selbro_level_list->text(%d) returns NULL",
		i_list_crnt
		);
		return;
	}

	/* Dirを選択 */
	ca_new[0] = '\0';
	t_sz = strlen(this->ccp_dir_mark());
	if (	(t_sz <= strlen(ccp_dir_or_level_or_file)) &&
		(!strncmp(	ccp_dir_or_level_or_file,
				this->ccp_dir_mark(),t_sz ))
	) {
		/* Dirを示す文字列を外す
			this->ccp_dir_mark() is "<Dir>   " */
		ccp_dir_or_level_or_file =
			&(ccp_dir_or_level_or_file[t_sz]);

		/* Dirを上がる項目... */
		if (!strcmp( ccp_dir_or_level_or_file, ".." )) {
			return; /* ...何もせず正常終了 */
		}
		/* Dir名の変更を行なう */
		if (OK != this->_rename_dir(
		ccp_dir_or_level_or_file,ca_new )) {
			return;
		}
	}
	/* Levelを選択 --> 変更を行なう */
	else if (cl_gts_gui.choice_level_list_form->value()) {
		if (OK != this->_rename_level_tif(
		i_list_crnt-1,ca_new )) {
			return;
		}
	}
	/* Fileを選択 --> 変更を行なう */
	else {
		if (OK != this->_rename_file_tif(
		i_list_crnt-1, ccp_dir_or_level_or_file,ca_new)) {
			return;
		}
	}

	/* Dir or File or Level再表示 */
	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return;
	}
// pri_funct_msg_vr( "%s %d: selected<%s>",__FILE__,__LINE__,ca_new);

	/* 新しいものを選択状態にする */
	this->_select_new_dir_or_file_or_level( ca_new );
}
