#include <ctype.h>	/* for isdigit() */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>	/* atoi() */
#include "pri.h"
#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

int memory_config::_chk_ON_OFF( char *cp_scan )
{
	if (!strcmp( this->str_on_, cp_scan ) ) {
		return 1;
	}
	return 0;
}

#include <iostream>

#include "igs_lex_white_space_and_double_quote.h"
int memory_config::_load_by_fp( FILE *fp, int i_load_trace_batch_sw )
{
	int	ii,
		i_ret;
	int	i_fnum_list_sw = OFF;
	int	i_trace_batch_list_sw = OFF;
	int	i_level_list_redisplay_sw = OFF;
	int	i_len;
	char	*cp_tmp;
	char	ca_str[1024],
		ca_scan1[1024],
		ca_scan2[1024],
		ca_scan3[1024],
		ca_scan4[1024];

	for (ii = 1; NULL != fgets(ca_str, 132, fp); ++ii) {

// std::cout << "fgets[" << ca_str << "]" << std::endl;

		ca_scan1[0] = '\0';
		ca_scan2[0] = '\0';
		ca_scan3[0] = '\0';
		ca_scan4[0] = '\0';

		std::vector< std::string > words;
		igs::lex::white_space_and_double_quote(ca_str,words);
		i_ret = words.size();
		if (1 <= i_ret) {
			strncpy(ca_scan1,words.at(0).c_str(),1024);
std::cout << "\"" << words.at(0) << "\"";
		}
		if (2 <= i_ret) {
			strncpy(ca_scan2,words.at(1).c_str(),1024);
std::cout << " \"" << words.at(1) << "\"";
		}
		if (3 <= i_ret) {
			strncpy(ca_scan3,words.at(2).c_str(),1024);
std::cout << " \"" << words.at(2) << "\"";
		}
		if (4 <= i_ret) {
			strncpy(ca_scan4,words.at(3).c_str(),1024);
std::cout << " \"" << words.at(3) << "\"";
		}
std::cout << std::endl;
		ca_scan1[1024-1] = '\0';
		ca_scan2[1024-1] = '\0';
		ca_scan3[1024-1] = '\0';
		ca_scan4[1024-1] = '\0';

		if (i_ret < 1) {
			/* 空行(\n)、あるいはエラーで、
			sscanfが何もセットしなかった */
			continue;
		}
		else if ('#' == ca_scan1[0]) {
			/* コメント行である */
			continue;
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_dir_ )) {
			cl_gts_master.cl_bro_level.init_level_dir(ca_scan2);
			i_level_list_redisplay_sw = ON;
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_file_ )) {
			cl_gts_master.cl_bro_level.level_filename_memory(ca_scan2);
			cl_gts_gui.strinp_level_file->value(ca_scan2);
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_list_form_ )) {
			cl_gts_gui.choice_level_list_form->value(
				atoi(ca_scan2));

			i_level_list_redisplay_sw = ON;

		 /* File/Level表示によってボタンを表示/非表示する */
		 if (0 == cl_gts_gui.choice_level_list_form->value()) {
			cl_gts_gui.button_level_shift_number->hide();
			cl_gts_gui.ligbut_level_info_rgb_sub_sw->hide();
		 } else {
			cl_gts_gui.button_level_shift_number->show();
			cl_gts_gui.ligbut_level_info_rgb_sub_sw->show();
		 }
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_num_start_ )) {
			cl_gts_gui.valinp_level_start->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_num_end_ )) {
			cl_gts_gui.valinp_level_end->value(
				atof(ca_scan2));
		}

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_rgb_scan_dir_ )) {
			cl_gts_gui.filinp_level_rgb_scan_dir->value(
				ca_scan2);
			cl_gts_gui.filinp_level_rgb_scan_dir->position(
				strlen(ca_scan2)
			);

			i_level_list_redisplay_sw = ON;
		}
		else if ((2 == i_ret) &&
		!strcmp(ca_scan1,this->str_level_rgb_trace_save_sw_)) {
			cl_gts_gui.chkbtn_level_trace_save_sw->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
		}
		else if ((2 == i_ret) &&
		!strcmp(ca_scan1,this->str_level_image_file_format_)) {
			const int idx =
	cl_gts_gui.choice_level_image_file_format->find_index(ca_scan2);
			if (idx != -1) {
 cl_gts_gui.choice_level_image_file_format->value(idx);
 /* 必ずchoice_level_image_file_format->value(idx)の後で実行すること */
 cl_gts_master.cl_bro_level.cb_set_image_file_extension();
			}
		}

		/*------------------------------------------------*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_select_ )) {
		 cl_gts_gui.choice_area_selecter->value(
		  cl_gts_gui.choice_area_selecter->find_item(ca_scan2)
		 );
		 cl_gts_master.cb_area_selecter();
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_x_pos_ )) {
		 cl_gts_gui.valinp_area_x_pos->value(atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_y_pos_ )) {
		 cl_gts_gui.valinp_area_y_pos->value(atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_aspect_ratio_select_ )) {
		 const Fl_Menu_Item *item =
		  cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(
		   ca_scan2);
std::cout
<< "cl_gts_gui.choice_area_aspect_ratio_selecter->find_item("
<< ca_scan2
<<")="
<< item
<< std::endl;
		 if (item != 0) {
		  cl_gts_gui.choice_area_aspect_ratio_selecter->value(item);
		  cl_gts_master.cb_area_aspect_ratio_selecter();
		 }
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_x_size_ )) {
		 cl_gts_gui.valinp_area_x_size->value(atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_y_size_ )) {
		 cl_gts_gui.valinp_area_y_size->value(atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_x_pixel_ )) {
			cl_gts_gui.valinp_area_x_pixel->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_y_pixel_ )) {
			cl_gts_gui.valinp_area_y_pixel->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_resolution_dpi_ )) {
			cl_gts_gui.valinp_area_reso->value(atof(ca_scan2));
		}

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_rotate_per_90_ )) {
			cl_gts_gui.choice_rot90->value(atoi(ca_scan2));

			/* 回転値(システム設定値)をメモリする */
			cl_gts_master.set_i_rotate_per_90(
				cl_gts_gui.choice_rot90->value() );
		}

		else if (!strcmp( ca_scan1, this->str_scanner_type_ )) {
			/* 空白ある文字列を考慮 */
			cl_gts_gui.txtout_scanner_type->value(ca_scan2);
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_scanner_x_max_ )) {
			cl_gts_gui.valout_scanner_width_max->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_scanner_y_max_ )) {
			cl_gts_gui.valout_scanner_height_max->value(
				atof(ca_scan2));
		}

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_pixel_type_ )) {
			cl_gts_gui.choice_pixel_type->value(
				atoi(ca_scan2));
			switch (cl_gts_gui.choice_pixel_type->value()) {
			case 0:
				cl_gts_gui.group_bw->show();
				cl_gts_gui.group_grays->hide();
				cl_gts_gui.group_rgb->hide();
				break;
			case 1:
				cl_gts_gui.group_bw->hide();
				cl_gts_gui.group_grays->show();
				cl_gts_gui.group_rgb->hide();
				break;
			case 2:
				cl_gts_gui.group_bw->hide();
				cl_gts_gui.group_grays->hide();
				cl_gts_gui.group_rgb->show();
				break;
			};
		}

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_bw_threshold_ )) {
			cl_gts_gui.valinp_bw_threshold->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_bw_threshold)->value(
				atof(ca_scan2));
		}

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_grayscale_brightness_ )) {
			cl_gts_gui.valinp_grays_brightness->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_brightness)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_grayscale_contrast_ )) {
			cl_gts_gui.valinp_grays_contrast->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_contrast)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_grayscale_gamma_ )) {
			cl_gts_gui.valinp_grays_gamma->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_gamma)->value(
				atof(ca_scan2));
		}

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_rgb_brightness_ )) {
			cl_gts_gui.valinp_rgb_brightness->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_brightness)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_rgb_contrast_ )) {
			cl_gts_gui.valinp_rgb_contrast->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_contrast)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_rgb_gamma_ )) {
			cl_gts_gui.valinp_rgb_gamma->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_gamma)->value(
				atof(ca_scan2));
		}

		/*-- other ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_color_trace_erase_1dot_ )) {
			 cl_gts_gui.chkbtn_color_trace_erase_1dot->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_color_trace_real_time_ )) {
			 cl_gts_gui.chkbtn_color_trace_real_time->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
		}

		/*------------------------------------------------*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_config_dir_ )) {
			cl_gts_master.cl_bro_config.init_config_dir(
				ca_scan2);
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_config_load_file_ )) {
			cl_gts_gui.strinp_config_load_file->value(
				ca_scan2);
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_config_save_as_file_ )) {
			cl_gts_gui.strinp_config_save_as_file->value(
				ca_scan2);
		}

		/*------------------------------------------------*/

		else if (((2==i_ret) || (3==i_ret) || (4==i_ret)) &&
		!strcmp( ca_scan1, this->str_frame_number_list_)) {
			/* ファイル番号リストの一番始めにやること */
			if (OFF == i_fnum_list_sw) {
			 /* ファイル番号リストの存在の有無 */
			 i_fnum_list_sw = ON;
			 /* 以前のリストをすべて削除 */
			 cl_gts_master.cl_list_access.remove_all();
			}

			/* 実際の画像ファイルの有無を調べて
			リストの最後に追加する */
	cl_gts_master.cl_image_mark_access.append_fnum_list_with_chk_mark(
				atoi(ca_scan2));

			/* 選択状態の再現 */
			if (
			!strcmp( ca_scan3,this->str_frame_number_selected_ ) ||
			!strcmp( ca_scan4,this->str_frame_number_selected_ )
			) {
				cl_gts_gui.selbro_fnum_list->select(
				 cl_gts_gui.selbro_fnum_list->size());
			}
		}

		/*------------------------------------------------*/

		else if ( (2 == i_ret) &&
		!strcmp( ca_scan1, this->str_trace_batch_dir_ )) {
			if (ON != i_load_trace_batch_sw) { continue; }

			cl_gts_master.cl_bro_trace_batch.init_trace_batch_dir(ca_scan2);
		}

		else if ( ((2==i_ret) || (3==i_ret)) &&
		!strcmp( ca_scan1, this->str_trace_batch_list_)) {
			if (ON != i_load_trace_batch_sw) { continue; }

			/* ファイル番号リストの一番始めにやること */
			if (OFF == i_trace_batch_list_sw) {
				/* ファイル番号リストの存在の有無 */
				i_trace_batch_list_sw = ON;
				/* 以前のリストをすべて削除 */
				while (0 <
			cl_gts_gui.selbro_trace_batch_run_list->size()) {
			cl_gts_gui.selbro_trace_batch_run_list->remove(1);
				}
			}

			i_len = strlen(ca_scan2);
			if (2 < i_len) {
				ca_scan2[i_len-1] = '\0';
				cp_tmp = &(ca_scan2[1]);
			} else {
				ca_scan2[0] = '\0';
				cp_tmp = ca_scan2;
			}

			/* リストの最後に追加する */
			cl_gts_gui.selbro_trace_batch_run_list->insert(
			cl_gts_gui.selbro_trace_batch_run_list->size()+1,
				cp_tmp
			);
		}

		/*------------------------------------------------*/

		else {
			if (E_MEMORY_CONFIG_LOAD_MATCH !=
			 this->_load_trace_src_hsv_by_fp(
			 i_ret,ca_scan1,ca_scan2,ca_scan3,ca_scan4
			 )
			) {
				pri_funct_err_bttvr(
			"Warning : ignore bad line '%s' at number %d",
					ca_str, ii );
			}
		}
	}

	/* frame listがない時は設定ファイルと判断してlistをクリアする */
	if (OFF == i_fnum_list_sw) {
		/* 以前のリストをすべて削除 */
		cl_gts_master.cl_list_access.remove_all();
	}

	/* trace batch listがない時はlistをクリアする */
	if (ON == i_load_trace_batch_sw) {
	 if (OFF == i_trace_batch_list_sw) {
		/* 以前のリストをすべて削除 */
		while (0 <
		cl_gts_gui.selbro_trace_batch_run_list->size()) {
		 cl_gts_gui.selbro_trace_batch_run_list->remove(1);
		}
	 }
	}

	/* frame number insert項目をゼロクリアする */
	cl_gts_gui.norinp_fnum_insert->value(NULL);

	/* Level/Fileリストを再表示する */
	if (ON == i_level_list_redisplay_sw) {
		cl_gts_master.cl_bro_level.cb_list_redisplay();
	}

	/******cl_gts_master.cl_list_level.load(
		cl_gts_gui.filinp_level_dir->value(),
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	);******/

	return OK;
}
int memory_config::load( const char *cp_file_path, int i_load_trace_batch_sw )
{
	FILE *fp;
	char current_path[PTBL_PATH_MAX];

	/* ファイル名の一時記憶 */
	strncpy( current_path,cp_file_path,PTBL_PATH_MAX );
	current_path[PTBL_PATH_MAX-1] = '\0';

	/* ファイル開く */
	fp = fopen( current_path, "r" );
	if (NULL == fp) {
		pri_funct_err_bttvr(
		"fopen(%s,r) returns NULL.",current_path);
		return NG;
	} 

	/* ファイル呼んで設定 */
	if (OK != this->_load_by_fp( fp, i_load_trace_batch_sw )) {
		pri_funct_err_bttvr(
		"memory_config::_load_by_fp(-) returns NG.");
		return NG;
	}

	/* ファイル閉じる */
	if (fclose(fp)) {
		pri_funct_err_bttvr("fclose(-) returns not zero.");
		return NG;
	}

	/* 正常に設定したなら、ファイル名の記憶 */
	this->memory_of_path = current_path;

	/* ファイル名を表示する */
	cl_gts_master._print_window_headline();

	/* frame number listにlevel名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
		cl_gts_master.cl_bro_level.cp_levelname()
	);

	/* add 2013-09-25 level名からfileが上書きなら注意表示 */
	cl_gts_master.cl_bro_level.cb_level_name();

	/* 表示を切る(データは残っている) */
	cl_gts_master.cl_ogl_view.no_view_canvas();

	/* 画面クリア */
	cl_gts_master.cl_ogl_view.clear_opengl(
		cl_gts_gui.opengl_view->w(),
		cl_gts_gui.opengl_view->h()
	);

	return OK;
}
