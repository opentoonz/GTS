#include <string.h>
#include <FL/fl_ask.H>	/* fl_input(),fl_ask() */
#include "ptbl_funct.h"
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

/* 実行する(OK(0))か否(NG(-1))かを返す */
int gtsfbro06cb_level::_renumber_level_tif( int i_num )
{
	ST_DIR_OR_LEVEL_INFO *stp_dir_or_level;
	const char	*ccp_main_dir,
			*ccp_full_dir,
			*ccp_new,
			*ccp_file;
	int i_new, ii;
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
	ccp_file = stp_dir_or_level->name;

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
	strcat( ca_msg, "Renumber Level\n");
	if (stp_dir_or_level->i_start_num<stp_dir_or_level->i_end_num) {
		sprintf( &(ca_msg[strlen(ca_msg)]),
			" %s.%04d%s...%s.%04d%s\n",
			ccp_file,
			stp_dir_or_level->i_start_num,
			this->get_imagefile_extension(),
			ccp_file,
			stp_dir_or_level->i_end_num,
			this->get_imagefile_extension()
		);
	} else {
		sprintf( &(ca_msg[strlen(ca_msg)]),
			" %s.%04d%s\n",
			ccp_file,
			stp_dir_or_level->i_start_num,
			this->get_imagefile_extension()
		);
	}
	strcat( ca_msg, "Input plus or minus number\n");

	/* Dialogを使いユーザーによるDir名変更------------- */
	ccp_new = fl_input( ca_msg, "0" );
	if (NULL == ccp_new) { return NG; } /* ユーザーによるcancel */

	/* 入力した名前のチェック-------------------------- */
	i_new = 0;
	sscanf(ccp_new,"%d",&i_new); /* space文字をとる */

	/* 空文字かゼロ値 */
	if (0 == i_new) {
		return NG;
	}

	/* 値が小さすぎ */
	if ((stp_dir_or_level->i_start_num + i_new) < 1) {
		snprintf( ca_msg,PTBL_PATH_MAX,
		"Can not renumber.\nNumber\n %d\nis too small",
				i_new);
		fl_alert(ca_msg);
		return NG;
	}

	/* 値が大きすぎ */
	if (9999 < (stp_dir_or_level->i_end_num + i_new)) {
		snprintf( ca_msg,PTBL_PATH_MAX,
		"Can not renumber.\nNumber\n %d\nis too big",
				i_new);
		fl_alert(ca_msg);
		return NG;
	}

#if 0
	/* Dialogを使い実行確認 */
	snprintf(ca_msg,PTBL_PATH_MAX,
		"Renumber Level\n (%s)  No, %d...%d --> %d...%d ok?",
		ccp_file,
		stp_dir_or_level->i_start_num,
		stp_dir_or_level->i_end_num,
		stp_dir_or_level->i_start_num + i_new,
		stp_dir_or_level->i_end_num + i_new
	);
	if (0 == fl_ask(ca_msg)) {
		return NG; /* ユーザーによるcancel */
	}
#endif

	/* renumber実行 */
	if (0 < i_new) { /* プラスのときは大きい番号から実行 */
	 if (0 < stp_dir_or_level->i_count) {
	  for (ii = stp_dir_or_level->i_end_num;
	  stp_dir_or_level->i_start_num <= ii; --ii) {
		if (OK != this->_renumber_level_tif_main(
		ccp_file,ii,ii+i_new )) {
			pri_funct_err_bttvr(
		 "Error : this->_renumber_level_tif_main(%s,%d,%d) returns NG",
				ccp_file,ii,ii+i_new
			);
			return OK;
		}
	  }
	 }
	 if (0 < stp_dir_or_level->i_not_traceing_rgb_count) {
	  for (ii = stp_dir_or_level->i_end_num;
	  stp_dir_or_level->i_start_num <= ii; --ii) {
		if (OK != this->_renumber_level_tif_full(
		ccp_file, ii,ii+i_new )) {
			pri_funct_err_bttvr(
		 "Error : this->_renumber_level_tif_full(%s,%d,%d) returns NG",
				ccp_file,ii,ii+i_new
			);
			return OK;
		}
	  }
	 }
	} else { /* マイナスのときは小さい番号から実行 */
	 if (0 < stp_dir_or_level->i_count) {
	  for (ii = stp_dir_or_level->i_start_num;
	  ii <= stp_dir_or_level->i_end_num; ++ii) {
		if (OK != this->_renumber_level_tif_main(
		ccp_file,ii,ii+i_new )) {
			pri_funct_err_bttvr(
		 "Error : this->_renumber_level_tif_main(%s,%d,%d) returns NG",
				ccp_file,ii,ii+i_new
			);
			return OK;
		}
	  }
	 }
	 if (0 < stp_dir_or_level->i_not_traceing_rgb_count) {
	  for (ii = stp_dir_or_level->i_start_num;
	  ii <= stp_dir_or_level->i_end_num; ++ii) {
		if (OK != this->_renumber_level_tif_full(
		ccp_file, ii,ii+i_new )) {
			pri_funct_err_bttvr(
		 "Error : this->_renumber_level_tif_full(%s,%d,%d) returns NG",
				ccp_file,ii,ii+i_new
			);
			return OK;
		}
	  }
	 }
	}
	return OK;
}

int gtsfbro06cb_level::_renumber_level_tif_main( const char *ccp_file, int i_old, int i_new )
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
	if (OK != this->i_lpath_cat_file_by_num( ccp_file, i_new )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_by_num(%s,%d) returns NG",
			ccp_file, i_new
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
	if (OK != this->i_lpath_cat_file_by_num( ccp_file, i_old )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_by_num(%s,%s) returns NG",
			ccp_file, i_old
		);
		return NG;
	}

	/* ファイルが存在しないなら正常終了 */
	if (!ptbl_dir_or_file_is_exist( this->cp_path() )) {
		return OK;
	}

	/* 変更 */
	if (rename( this->cp_path(), ca_new )) {
		pri_funct_err_bttvr(
   "Error : renumber(%s,%s) returns not zero",
			this->cp_path(), ca_new
		);
		return NG;
	}
	return OK;
}

int gtsfbro06cb_level::_renumber_level_tif_full( const char *ccp_file, int i_old, int i_new )
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
	if (OK != this->i_lpath_cat_file_for_full( ccp_file, i_new )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_for_full(%s,%d) returns NG",
			ccp_file, i_new
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
	if (OK != this->i_lpath_cat_file_for_full( ccp_file, i_old )) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_for_full(%s,%s) returns NG",
			ccp_file, i_old
		);
		return NG;
	}

	/* ファイルが存在しないなら正常終了 */
	if (!ptbl_dir_or_file_is_exist( this->cp_path() )) {
		return OK;
	}

	/* 変更 */
	if (rename( this->cp_path(), ca_new )) {
		pri_funct_err_bttvr(
   "Error : renumber(%s,%s) returns not zero",
			this->cp_path(), ca_new
		);
		return NG;
	}
	return OK;
}
