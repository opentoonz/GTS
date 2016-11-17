#include <string.h>
#include <FL/fl_ask.H>
#include <FL/filename.H>
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_list( void )
{
	char *cp_dir_or_file;
	int i_dir_sw = OFF;
	size_t	t_sz;
	int	i_list_num;
	const char *ccp_crnt_dir;
	char ca_msg[PTBL_PATH_MAX];

	/* list下をクリック等で、選択していない */
	if (cl_gts_gui.selbro_level_list->value() <= 0) {
		return; /* 何もせず正常終了 */
	}

	/* 選択したディレクトリあるいはファイル名 */
	cp_dir_or_file = (char *)(
		cl_gts_gui.selbro_level_list->text(
		cl_gts_gui.selbro_level_list->value()
		)
	);
	if (NULL == cp_dir_or_file) {
		pri_funct_err_bttvr(
       "Error : cl_gts_gui.selbro_level_list->text(%d) returns NULL",
		cl_gts_gui.selbro_level_list->value()
		);
		return;
	}

	/* 始めのコメント文字がディレクトリを示す文字列であれば
		this->ccp_dir_mark()"<Dir>   "
	それを外す */
	t_sz = strlen(this->ccp_dir_mark());
	if (	(t_sz <= strlen(cp_dir_or_file)) &&
		(!strncmp(	cp_dir_or_file,
		      this->ccp_dir_mark(),t_sz
		))
	) {
		cp_dir_or_file = &(cp_dir_or_file[t_sz]);
		i_dir_sw = ON;
	}

	if (0 == cl_gts_gui.togbut_level_open_browse->value()) {
	 ccp_crnt_dir = cl_gts_gui.filinp_level_save_dir_path->value();
	} else {
	 ccp_crnt_dir = cl_gts_gui.filinp_level_open_dir_path->value();
	}

	/* ディレクトリを上がる */
	if (!strcmp( cp_dir_or_file, ".." )) {
		if (OK != this->i_path_dir_up( ccp_crnt_dir )) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_dir_up(%s) returns NG",
			ccp_crnt_dir
			);
			return;
		}
		this->change_level_dir();
		if (OK != this->change_level_list() ) {
			pri_funct_err_bttvr(
		 "Error : this->change_level_list() returns NG");
			return;
		}
		/* listの中にlevelと同じ名があるなら上書き注意表示 */
		this->cb_level_name();

		return;
	}

	/* dirが存在しない(nullパス("")は有効とする)
	なら、Dialog表示して注意する */
	if (	(NULL == ccp_crnt_dir) ||
		(	('\0' != ccp_crnt_dir[0]) &&
			!fl_filename_isdir(ccp_crnt_dir)
		)
	) {
		pri_funct_err_bttvr(
			"Error : dir path(%s) is not exist",
			ccp_crnt_dir );
		if (NULL == ccp_crnt_dir) {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"Dir path\nis not exist!");
		} else {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"Dir\n %s\nis not exist!",ccp_crnt_dir);
		}
		/* listの中にlevelと同じ名があるなら上書き注意表示 */
		this->cb_level_name();

		fl_alert(ca_msg);
		return;
	}

	/* ディレクトリを下る */
	if (ON == i_dir_sw) {
		/* Control keyが押されているときは
		ディレクトリを降りず選択のみする */
		if (Fl::event_ctrl()) {/* Control key is pressed */
			return;
		}

		/* 下るディレクトリパスを設定する(内部保持) */
		if (OK != this->i_path_dir_down(
			ccp_crnt_dir,
			cp_dir_or_file
		)) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_dir_down(%s,%s) returns NG",
			ccp_crnt_dir,
			cp_dir_or_file);
			return;
		}

		/* 設定したディレクトリにパス表示を変更 */
		this->change_level_dir();

		/* 設定したディレクトリにリスト表示を変更 */
		if (OK != this->change_level_list() ) {
			pri_funct_err_bttvr(
		 "Error : this->change_level_list() returns NG");
			return;
		}

		/* listの中にlevelと同じ名があるなら上書き注意表示 */
		this->cb_level_name();

		return;
	}

	/* ディレクトリでなければファイルである */
	i_list_num = cl_gts_gui.selbro_level_list->value() - 1;
	if (0 == cl_gts_gui.choice_level_list_form->value()) {/* File表記 */
		cl_gts_gui.strinp_level_save_file_head->value(cp_dir_or_file);

		/* 画像情報を表示する */
		if (OK != this->_list_image_info(
			this->stp_dir_or_file_info(i_list_num)
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_list_image_info(files-%d) returns NG",
			i_list_num
			);
			return;
		}
	}
	/* Level表記のとき */
	else {
		cl_gts_gui.strinp_level_save_file_head->value(
			this->cp_dir_or_level_name( i_list_num )
		);
		cl_gts_gui.valinp_level_saveopen_num_start->value(
			this->i_dir_or_level_start(i_list_num)
		);
		cl_gts_gui.valinp_level_saveopen_num_end->value(
			this->i_dir_or_level_end(i_list_num)
		);
		/* End/EndressをEndに設定 */
		cl_gts_gui.choice_level_save_num_continue_type->value(0);
		cl_gts_gui.valinp_level_saveopen_num_end->show();
		cl_gts_gui.choice_level_save_num_endless_direction->hide();
		cl_gts_gui.selbro_fnum_list->activate();

		/* levelと画像情報を表示する */
		if (OK != this->_list_image_info(
			this->stp_dir_or_level_info(i_list_num)
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_list_image_info(level-%d) returns NG",
			i_list_num
			);
			return;
		}
	}
	/* listの中にlevelと同じ名があるなら上書き注意表示 */
	this->cb_level_name();
}
