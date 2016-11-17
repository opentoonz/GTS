#include <string.h> /* strlen() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_renumber( void )
{
	int i_list_crnt;
	const char *ccp_dir_or_level_or_file;
	size_t	t_sz;
	ST_DIR_OR_LEVEL_INFO *stp_dir_or_level;

	/* level表示でないならキャンセル */
	if (1 != cl_gts_gui.choice_level_list_form->value()) {
		return;
	}

	/* 選択項目 */
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
	t_sz = strlen(this->ccp_dir_mark());
	if (	(t_sz <= strlen(ccp_dir_or_level_or_file)) &&
		(!strncmp(	ccp_dir_or_level_or_file,
				this->ccp_dir_mark(),t_sz ))
	) {
		return;
	}

	/* Levelを選択 --> 変更を行なう */
	if (OK != this->_renumber_level_tif( i_list_crnt-1 )) {
		return;
	}

	/* Dir or File or Level再表示 */
	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return;
	}

	/* 新しいものを選択状態にする */
	stp_dir_or_level = this->stp_dir_or_level_info(i_list_crnt-1);
	if (NULL != stp_dir_or_level) {
		this->_select_new_dir_or_file_or_level(
			stp_dir_or_level->name
		);
		cl_gts_gui.valinp_level_saveopen_num_start->value(
			(double)stp_dir_or_level->i_start_num
		);
		cl_gts_gui.valinp_level_saveopen_num_end->value(
			(double)stp_dir_or_level->i_end_num
		);
	}
}
