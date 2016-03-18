#include <string.h>
#include <FL/fl_ask.H>	/* fl_input(),fl_ask() */
#include "ptbl_funct.h"
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

/* 実行する(OK(0))か否(NG(-1))かを返す */
int gtsfbro06cb_level::_rename_level_tif( int i_num, char *cp_new )
{
	ST_DIR_OR_LEVEL_INFO *stp_dir_or_level;
	const char	*ccp_main_dir,
			*ccp_full_dir,
			*ccp_new;
	const char *ccp_old;
	char ca_msg[PTBL_PATH_MAX];

	/* 現状の把握 --------------------------------------*/
	stp_dir_or_level = this->stp_dir_or_level_info(i_num);
	if (NULL == stp_dir_or_level) { return NG; }

	/* それぞれのDirパス */
	ccp_main_dir = NULL;
	ccp_full_dir = NULL;
	if (0 < stp_dir_or_level->i_count) {
	 ccp_main_dir =cl_gts_gui.filinp_level_dir->value();
	}
	if (0 < stp_dir_or_level->i_not_traceing_rgb_count) {
	 ccp_full_dir =cl_gts_gui.filinp_level_rgb_scan_dir->value();
	}

	/* Dialogのメッセージ生成 */
	strcpy( ca_msg, "In\n" );
	if (	(NULL != ccp_main_dir) &&
		(NULL != ccp_full_dir) &&
		!strcmp(ccp_main_dir,ccp_full_dir)
	) {
			strcat( ca_msg, " " );
			strcat( ca_msg, ccp_main_dir );
			strcat( ca_msg, "\n" );
	} else {
		if (NULL != ccp_main_dir) {
			strcat( ca_msg, " " );
			strcat( ca_msg, ccp_main_dir );
			strcat( ca_msg, "\n" );
		}
		if ((NULL != ccp_main_dir) && (NULL != ccp_full_dir)) {
			strcat( ca_msg, "and\n" );
		}
		if (NULL != ccp_full_dir) {
			strcat( ca_msg, " " );
			strcat( ca_msg, ccp_full_dir );
			strcat( ca_msg, "\n" );
		}
	}
	strcat( ca_msg, "Rename Level\n" );
	strcat( ca_msg, " " );

	/* Dialogを使いユーザーによるDir名変更------------- */
	ccp_old = stp_dir_or_level->name;
	strcat( ca_msg, ccp_old );
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
	if (NULL != this->stp_dir_or_level_search(cp_new)) {
		if (E_DIR_OR_FILE_IS_DIR ==
		this->stp_dir_or_level_search(cp_new)->e_type) {
			snprintf( ca_msg,PTBL_PATH_MAX,
			"Can not rename.\nDirectory\n %s\nis exist",
				cp_new);
		} else {
			snprintf( ca_msg,PTBL_PATH_MAX,
			"Can not rename.\nlevel\n %s\nis exist",
				cp_new);
		}
		fl_alert(ca_msg);
		strcpy( cp_new,ccp_old );
		return NG;
	}

#if 0
	/* Dialogを使い実行確認 */
	snprintf(ca_msg,PTBL_PATH_MAX,
		"Rename Level\n %s(No,%d...%d) --> %s ok?",
		ccp_old,
		stp_dir_or_level->i_start_num,
		stp_dir_or_level->i_end_num,
		cp_new
	);
	if (0 == fl_ask(ca_msg)) {
		strcpy( cp_new,ccp_old );
		return NG; /* ユーザーによるcancel */
	}
#endif

	/* rename実行 */
	if (0 < stp_dir_or_level->i_count) {
		int ii;
		for (ii = stp_dir_or_level->i_start_num;
		ii <= stp_dir_or_level->i_end_num; ++ii) {
			if (OK != this->_rename_level_tif_main(
			ii, ccp_old, cp_new )) {
				pri_funct_err_bttvr(
			 "Error : this->_rename_level_tif_main(%d,%s,%s) returns NG",
					ii, ccp_old, cp_new
				);
				strcpy( cp_new,ccp_old );
				return OK;
				/* 途中でエラーでもlist再表示する */
			}
		}
	}
	if (0 < stp_dir_or_level->i_not_traceing_rgb_count) {
		int ii;
		for (ii = stp_dir_or_level->i_start_num;
		ii <= stp_dir_or_level->i_end_num; ++ii) {
			if (OK != this->_rename_level_tif_full(
			ii, ccp_old, cp_new )) {
				pri_funct_err_bttvr(
			 "Error : this->_rename_level_tif_full(%d,%s,%s) returns NG",
					ii, ccp_old, cp_new
				);
				strcpy( cp_new,ccp_old );
				return OK;
				/* 途中でエラーでもlist再表示する */
			}
		}
	}
	return OK;
}

int gtsfbro06cb_level::_rename_level_tif_main( int i_num, const char *ccp_old, const char *ccp_new )
{
	const char *ccp_dir;
	char ca_new[PTBL_PATH_MAX];

	ccp_dir = cl_gts_gui.filinp_level_dir->value();

	/* 新しいDirパス設定 */
	if (OK != this->i_path_cpy_dir( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
			ccp_dir
		);
		return NG;
	}
	if (OK != this->i_lpath_cat_file_by_num( ccp_new, i_num )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_by_num(%s,%d) returns NG",
			ccp_new, i_num
		);
		return NG;
	}
	strcpy( ca_new, this->cp_path() );

	/* 古いDirパス設定 */
	if (OK != this->i_path_cpy_dir( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
			ccp_dir
		);
		return NG;
	}
// pri_funct_msg_vr("%s %d ccp_old<%s>", __FILE__, __LINE__,ccp_old);
	if (OK != this->i_lpath_cat_file_by_num( ccp_old, i_num )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_by_num(%s,%d) returns NG",
			ccp_old, i_num
		);
		return NG;
	}

	/* ファイルが存在しないなら正常終了 */
	if (!ptbl_dir_or_file_is_exist( this->cp_path() )) {
		return OK;
	}

// pri_funct_msg_vr("%04d %s\n     %s",i_num,this->cp_path(),ca_new);

	/* 変更 */
	if (rename( this->cp_path(), ca_new )) {
		pri_funct_err_bttvr(
   "Error : rename(%s,%s) returns not zero",
			this->cp_path(), ca_new
		);
		return NG;
	}
	return OK;
}

int gtsfbro06cb_level::_rename_level_tif_full( int i_num, const char *ccp_old, const char *ccp_new )
{
	const char *ccp_dir;
	char ca_new[PTBL_PATH_MAX];

	ccp_dir = cl_gts_gui.filinp_level_rgb_scan_dir->value();

	/* 新しいDirパス設定 */
	if (OK != this->i_path_cpy_dir( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
			ccp_dir
		);
		return NG;
	}
	if (OK != this->i_lpath_cat_file_for_full( ccp_new, i_num )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_for_full(%s,%d) returns NG",
			ccp_new, i_num
		);
		return NG;
	}
	strcpy( ca_new, this->cp_path() );

	/* 古いDirパス設定 */
	if (OK != this->i_path_cpy_dir( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
			ccp_dir
		);
		return NG;
	}
// pri_funct_msg_vr("%s %d ccp_old<%s>", __FILE__, __LINE__,ccp_old);
	if (OK != this->i_lpath_cat_file_for_full( ccp_old, i_num )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_for_full(%s,%d) returns NG",
			ccp_old, i_num
		);
		return NG;
	}

	/* ファイルが存在しないなら正常終了 */
	if (!ptbl_dir_or_file_is_exist( this->cp_path() )) {
		return OK;
	}

// pri_funct_msg_vr("%04d %s\n     %s",i_num,this->cp_path(),ca_new);

	/* 変更 */
	if (rename( this->cp_path(), ca_new )) {
		pri_funct_err_bttvr(
   "Error : rename(%s,%s) returns not zero",
			this->cp_path(), ca_new
		);
		return NG;
	}
	return OK;
}
