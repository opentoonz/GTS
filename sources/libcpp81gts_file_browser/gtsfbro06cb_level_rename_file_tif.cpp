#include <string.h>
#include <FL/fl_ask.H>	/* fl_input(),fl_ask() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

/* 実行する(OK(0))か否(NG(-1))かを返す */
int gtsfbro06cb_level::_rename_file_tif( int i_num, const char *ccp_old, char *cp_new )
{
	ST_DIR_OR_FILE_INFO *stp_dir_or_file;
	const char *ccp_dir, *ccp_new;
	char ca_msg[PTBL_PATH_MAX];
	char ca_path[PTBL_PATH_MAX];

	stp_dir_or_file = this->stp_dir_or_file_info(i_num);
	if (NULL == stp_dir_or_file) { return NG; }

	if (E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE ==
	stp_dir_or_file->e_type) {
		ccp_dir =cl_gts_gui.filinp_level_open_dir_path->value();
	} else {
		ccp_dir =cl_gts_gui.filinp_level_save_dir_path->value();
	}

	/* Dialogのメッセージ生成 */
	snprintf(ca_msg,PTBL_PATH_MAX,"In\n %s\nRename File\n %s",
			ccp_dir,ccp_old);

	/* Dialogを使いユーザーによるDir名変更 */
	ccp_new = fl_input( ca_msg, ccp_old );

	/* ユーザーによるcancel */
	if (NULL == ccp_new) {
		strcpy( cp_new,ccp_old );
		return NG;
	}

	/* 入力した名前のチェック-------------------------- */
	// cp_new[0] = '\0';
	sscanf(ccp_new,"%s",cp_new); /* space文字をとる */

	/* 空文字か変更なし */
	if (('\0' == cp_new[0]) || !strcmp( ccp_old,cp_new )) {
		strcpy( cp_new,ccp_old );
		return NG;
	}

	/* 有効でない文字がある */
	if (NG == this->_is_valid_string( cp_new )) {
		snprintf( ca_msg,PTBL_PATH_MAX,
		"bad string.\n %s\ninclude bad character",
			cp_new);
		fl_alert(ca_msg);
		strcpy( cp_new,ccp_old );
		return NG;
	}

	/* 同じ名前がある */
	if (NULL != this->stp_dir_or_file_search(cp_new)) {
		if (E_DIR_OR_FILE_IS_DIR ==
		this->stp_dir_or_file_search(cp_new)->e_type) {
			snprintf( ca_msg,PTBL_PATH_MAX,
			"Can not rename.\nDirectory\n %s\nis exist",
				cp_new);
		} else {
			snprintf( ca_msg,PTBL_PATH_MAX,
			"Can not rename.\nFile\n %s\nis exist",
				cp_new);
		}
		fl_alert(ca_msg);
		strcpy( cp_new,ccp_old );
		return NG;
	}

	/* 拡張子の確認 */
	const char *ccp_n,*ccp_o;
	ccp_o = strrchr( ccp_old, '.' );
	ccp_n = strrchr( cp_new, '.' );
	if (	(NULL != ccp_o) && /* 元もと、拡張子があって */
		(	(NULL == ccp_n) || /* 拡張子がないか... */
			strcmp(ccp_o,ccp_n) /* あるいは違う拡張子名 */
		)
	) {
		snprintf(ca_msg,PTBL_PATH_MAX,
			"Do Not change extention\n %s",
			cp_new);
		fl_alert(ca_msg);
		strcpy( cp_new,ccp_old );
		return NG;
	}
	/* 接尾語".0000.tif"の確認 */
	if (NULL == this->ccp_num4_and_ext( cp_new )) {
		snprintf(ca_msg,PTBL_PATH_MAX,
			"Do Not change number or extention\n %s",
			cp_new);
		fl_alert(ca_msg);
		strcpy( cp_new,ccp_old );
		return NG;
	}

	/* 新しいDirパス生成 */
	if (OK != this->i_path_dir_file( ccp_dir, cp_new )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NG",
			ccp_dir, cp_new
		);
		strcpy( cp_new,ccp_old );
		return NG;
	}
	strcpy( ca_path, this->cp_path() );

#if 0
	/* Dialogを使い実行確認 */
	snprintf(ca_msg,PTBL_PATH_MAX,
		"In\n %s\nRename File\n %s --> %s ok?",
		ccp_dir,ccp_old,cp_new
	);
	if (0 == fl_ask(ca_msg)) {
		strcpy( cp_new,ccp_old );
		return NG; /* ユーザーによるcancel */
	}
#endif

	/* 古いDirパス設定 */
	if (OK != this->i_path_dir_file( ccp_dir, ccp_old )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NG",
			ccp_dir, ccp_old
		);
		strcpy( cp_new,ccp_old );
		return NG;
	}

	/* 変更 */
	if (rename( this->cp_path(), ca_path )) {
		pri_funct_err_bttvr(
   "Error : rename(%s,%s) returns not zero",
			this->cp_path(), ca_path
		);
		/* rename()に失敗してもリスト再表示はする */
		strcpy( cp_new,ccp_old );
		return NG;
	}
	return OK;
}
