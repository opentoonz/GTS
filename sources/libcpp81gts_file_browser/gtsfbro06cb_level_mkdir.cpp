#include <string.h> /* strlen() */
#include <ctype.h>  /* isdigit(),islower(),isupper() */
#include <FL/fl_ask.H>	/* fl_input() */
#include "ptbl_funct.h"	/* ptbl_mkdir() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

int gtsfbro06cb_level::_is_valid_string( const char *ccp_name )
{
	int i_len, ii;
	i_len = strlen( ccp_name );
	for (ii = 0; ii < i_len; ++ii) {
		if (	!isdigit(ccp_name[ii]) &&
			!islower(ccp_name[ii]) &&
			!isupper(ccp_name[ii]) &&
			('-' != ccp_name[ii]) &&
			('.' != ccp_name[ii]) &&
			('_' != ccp_name[ii])
		) {
			return NG;
		}
	}
	return OK;
}

void gtsfbro06cb_level::_select_new_dir_or_file_or_level( const char *ccp_name )
{
	int i_num;
	if (0 == cl_gts_gui.choice_level_list_form->value()) {
		i_num = this->i_dir_or_file_search( ccp_name );
	} else {
		i_num = this->i_dir_or_level_search( ccp_name );
	}
	if (0 <= i_num) {
		cl_gts_gui.selbro_level_list->select(i_num+1);
		cl_gts_gui.selbro_level_list->topline(i_num+1);
	}
}

void gtsfbro06cb_level::cb_mkdir( void )
{
	const char *ccp_dir, *ccp_subdir;
	char ca_msg[PTBL_PATH_MAX];
	char ca_subdir[PTBL_PATH_MAX];

	/* Dirを得る */
	if (cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
		ccp_dir = cl_gts_gui.filinp_level_rgb_scan_dir->value();
	} else {
		ccp_dir = cl_gts_gui.filinp_level_dir->value();
	}

	/* Dialogのメッセージ生成 */
	snprintf(ca_msg,PTBL_PATH_MAX,"In\n %s\nNew directory name",
			ccp_dir);

	/* Dialogを使いユーザーによるDir名変更 */
	ccp_subdir = fl_input( ca_msg );
	if (NULL == ccp_subdir) { return; /* ユーザーによるcancel */ }

	/* 入力した名前のチェック-------------------------- */
	ca_subdir[0] = '\0';
	sscanf(ccp_subdir,"%s",ca_subdir); /* space文字をとる */
	if ('\0' == ca_subdir[0]) {
		return; /* 空文字 */
	}
	ca_subdir[PTBL_PATH_MAX-1] = '\0';

	/* 有効でない文字がある */
	if (NG == this->_is_valid_string( ca_subdir )) {
		snprintf( ca_msg,PTBL_PATH_MAX,
		"bad string.\n %s\ninclude bad character",
			ca_subdir);
		fl_alert(ca_msg);
		return;
	}

	/* 同じ名前がある */
	if (NULL != this->stp_dir_or_file_search(ca_subdir)) {
		if (E_DIR_OR_FILE_IS_DIR ==
		this->stp_dir_or_file_search(ca_subdir)->e_type) {
			snprintf( ca_msg,PTBL_PATH_MAX,
			"Can not makedir.\nDirectory\n %s\nis exist",
				ca_subdir);
		} else {
			snprintf( ca_msg,PTBL_PATH_MAX,
			"Can not makedir.\nFile\n %s\nis exist",
				ca_subdir);
		}
		fl_alert(ca_msg);
		return;
	}

	/* 新しいDirパス生成 */
	if (OK != this->i_path_dir_down(
			ccp_dir, ca_subdir
	)) {
		pri_funct_err_bttvr(
	"Error : this->i_path_dir_down(%s,%s) returns NG",
			ccp_dir, ca_subdir
		);
		return;
	}

	if (ptbl_mkdir( this->cp_path() )) {
		pri_funct_err_bttvr(
   "Error : ptbl_mkdir(%s) returns not zero",  this->cp_path() );
		return;
	}

	/* ファイルandディレクトリリスト再表示 */
	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return;
	}

	/* 新しいものを選択状態にする */
	this->_select_new_dir_or_file_or_level( ca_subdir );
}
