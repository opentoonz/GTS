#include <string.h>
#include <FL/fl_ask.H>
#include <FL/filename.H>
#include "gtsfbro06cb_config.h"
#include "gts_gui.h"

void gtsfbro06cb_config::cb_load_list( void )
{
	size_t	t_sz;
	char *cp_dir_or_file;
	int i_dir_sw = OFF;
	const char *ccp_dir;
	char ca_msg[PTBL_PATH_MAX];

	/* list下をクリック等で、選択していない */
	if (cl_gts_gui.selbro_config_load_list->value() <= 0) {
		return; /* 何もせず正常終了 */
	}

	/* 選択したディレクトリあるいはファイル名 */
	cp_dir_or_file = (char *)(
		cl_gts_gui.selbro_config_load_list->text(
		cl_gts_gui.selbro_config_load_list->value()
		)
	);
	if (NULL == cp_dir_or_file) {
		pri_funct_err_bttvr(
       "Error : cl_gts_gui.selbro_config_load_list->text(%d) returns NULL",
		cl_gts_gui.selbro_config_load_list->value() );
		return;
	}

	/* 始めのコメント文字
		      this->ccp_dir_mark() is "<Dir>   "
	を外す */
	t_sz = strlen(this->ccp_dir_mark());
	if (	(t_sz <= strlen(cp_dir_or_file)) &&
		(!strncmp(	cp_dir_or_file,
		      this->ccp_dir_mark(),t_sz
		))
	) {
		cp_dir_or_file = &(cp_dir_or_file[t_sz]);
		i_dir_sw = ON;
	}

	ccp_dir = cl_gts_gui.filinp_config_load_dir->value();

	/* ディレクトリを上がる */
	if (!strcmp( cp_dir_or_file, ".." )) {
		if (OK != this->i_path_dir_up( ccp_dir )) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_dir_up(%s) returns NG",ccp_dir);
			return;
		}
		this->change_config_dir();
		if (OK != this->change_config_list()) {
			pri_funct_err_bttvr(
		 "Error : this->change_config_list() returns NG"
				);
			return;
		}
		return;
	}

	/* dirが存在しない(nullパス("")は有効とする)
	なら、Dialog表示して注意する */
	if (	(NULL == ccp_dir) ||
		(	('\0' != ccp_dir[0]) &&
			!fl_filename_isdir( ccp_dir )
		)
	) {
		pri_funct_err_bttvr(
			"Error : dir path(%s) is not exist", ccp_dir );
		if (NULL == ccp_dir) {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"Dir path\nis not exist!");
		} else {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"Dir\n %s\nis not exist!",ccp_dir);
		}
		fl_alert(ca_msg);
		return;
	}

	/* ディレクトリを下る */
	if (ON == i_dir_sw) {
		if (OK != this->i_path_dir_down(
			ccp_dir,
			cp_dir_or_file
		)) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_dir_down(%s,%s) returns NG",
			ccp_dir,
			cp_dir_or_file);
			return;
		}
		this->change_config_dir();
		if (OK != this->change_config_list()) {
			pri_funct_err_bttvr(
		 "Error : this->change_config_list() returns NG");
			return;
		}
		return;
	}

	/* ディレクトリでなければファイルである */
	/* ファイル名をGUIに表示する */
	cl_gts_gui.strinp_config_load_file->value(cp_dir_or_file);

	/* textファイルを、表示する */
	this->view_text_for_load();
}
