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

#if 0
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
	/* 01. Dirパス */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_save_dir_path_ )) {
			cl_gts_master.cl_bro_level.init_level_dir(ca_scan2);
			i_level_list_redisplay_sw = ON;
		}
	/* 02 file/levelのlist表示切替(Renumberボタンの表示OFF/ONも) */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1 ,this->str_level_list_form_ )) {
	if (isdigit(ca_scan2[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_level_list_form->value( atoi(ca_scan2) );
		 i_level_list_redisplay_sw = ON;
		 /* File/Level表示によってボタンを表示/非表示する */
		 if (0 == cl_gts_gui.choice_level_list_form->value()) {
			cl_gts_gui.menite_level_shift_number->deactivate();
			cl_gts_gui.menite_level_view_rgb_full_sw->deactivate();
		 } else {
			cl_gts_gui.menite_level_shift_number->activate();
			cl_gts_gui.menite_level_view_rgb_full_sw->activate();
		 }
	}
	else {
		const Fl_Menu_Item *crnt =
		 cl_gts_gui.choice_level_list_form->find_item( ca_scan2 );
		if (crnt != nullptr) {
		 cl_gts_gui.choice_level_list_form->value( crnt );
		 i_level_list_redisplay_sw = ON;
		 /* File/Level表示によってボタンを表示/非表示する */
		 if (0 == cl_gts_gui.choice_level_list_form->value()) {
			cl_gts_gui.menite_level_shift_number->deactivate();
			cl_gts_gui.menite_level_view_rgb_full_sw->deactivate();
		 } else {
			cl_gts_gui.menite_level_shift_number->activate();
			cl_gts_gui.menite_level_view_rgb_full_sw->activate();
		 }
		}
	}
		}
	/* 03 Level名 */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_save_file_head_ )) {
			//cl_gts_master.cl_bro_level.level_filename_memory(ca_scan2);
			cl_gts_gui.strinp_level_save_file_head->value(ca_scan2);
		}
	/* 04 Level開始番号 */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_num_start_ )) {
			cl_gts_gui.valinp_level_num_start->value(
				atof(ca_scan2));
		}
	/* 05 Level終端番号 */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_num_end_ )) {
			cl_gts_gui.valinp_level_num_end->value(
				atof(ca_scan2));
		}
	/* 06 Level終端タイプ */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1 ,this->str_level_num_continue_type_)) {
	const Fl_Menu_Item* crnt =
		cl_gts_gui.choice_level_num_continue_type->find_item(ca_scan2);
	if (crnt != nullptr) {
		 cl_gts_gui.choice_level_num_continue_type->value(crnt);
		if (cl_gts_gui.choice_level_num_continue_type->value() == 0) {
			cl_gts_gui.valinp_level_num_end->show();
			cl_gts_gui.choice_level_num_endless_direction->hide();
			cl_gts_gui.selbro_fnum_list->activate();
		}
		else {
			cl_gts_gui.valinp_level_num_end->hide();
			cl_gts_gui.choice_level_num_endless_direction->show();
			cl_gts_gui.selbro_fnum_list->deactivate();
		}
	}
		}
	/* 07 Level Endless時増減方向 */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,this->str_level_num_endless_direction_)) {
	const Fl_Menu_Item *crnt =
	 cl_gts_gui.choice_level_num_endless_direction->find_item( ca_scan2 );
	if (crnt != nullptr) {
		cl_gts_gui.choice_level_num_endless_direction->value(crnt);
	}
		}

	/* 08 保存(開くときも)画像ファイル書式 */
		else if ((2 == i_ret) &&
		!strcmp(ca_scan1,this->str_level_save_image_format_)) {
	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_level_save_image_format->find_item(ca_scan2);
			if (crnt != nullptr) {
	cl_gts_gui.choice_level_save_image_format->value(crnt);
	cl_gts_master.cl_bro_level.cb_set_image_file_extension();
			}
		}

	/* 09 等倍画像表示スイッチ */
	/* 10 画像全体表示スイッチ */

	/* 11 open dirパス */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_open_dir_path_ )) {
			cl_gts_gui.filinp_level_open_dir_path->value(
				ca_scan2);
			cl_gts_gui.filinp_level_open_dir_path->position(
				strlen(ca_scan2)
			);

			i_level_list_redisplay_sw = ON;
		}
	/* xx Open Level名 */
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_level_open_file_head_ )) {
			//cl_gts_master.cl_bro_level.level_filename_memory(ca_scan2);
			cl_gts_gui.strinp_level_open_file->value(ca_scan2);
		}
	/* xx open画像ファイル書式 */
		else if ((2 == i_ret) &&
		!strcmp(ca_scan1,this->str_level_open_image_format_)) {
	const Fl_Menu_Item *crnt =
	cl_gts_gui.choice_level_open_image_format->find_item(ca_scan2);
			if (crnt != nullptr) {
	cl_gts_gui.choice_level_open_image_format->value(crnt);
			}
		}
	/* 12 RGBスキャン時、トレスを実行(し保存)するスイッチ */
		else if ((2 == i_ret) &&
		!strcmp(ca_scan1,this->str_filter_rgb_color_trace_sw_)) {
			 cl_gts_gui.chkbtn_filter_rgb_color_trace->value(
				this->_chk_ON_OFF( ca_scan2 )
			 );
		}

	/* 15 dirパス/_full dirパスのブラウジング切替えスイッチ */
	/* 16 _full等倍画像表示スイッチ */

		/*------------------------------------------------*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_area_select_ )) {
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_area_selecter->find_item( ca_scan2 );
	if (crnt != nullptr) {
		cl_gts_gui.choice_area_selecter->value( crnt );
		cl_gts_master.cb_area_selecter();
	}
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
	const Fl_Menu_Item *crnt =
	 cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(ca_scan2 );
	if (crnt != 0) {
	 cl_gts_gui.choice_area_aspect_ratio_selecter->value(crnt);
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
	if (isdigit(ca_scan2[0])) {/* For Legacy Format...Delete sameday */
	/*
		0=CW_-90 , 1=CW_0 , 2=CW_90 , 3=CW_180
		0=CW_-90はScannerにとっての正対なのでこれ以外は回転処理必要
		1=CW_0は作業者にとっての正対
	*/
		 cl_gts_gui.choice_rot90->value( atoi(ca_scan2) );
		 /* 回転値(システム設定値)をメモリする */
		 cl_gts_master.set_i_rotate_per_90(
			cl_gts_gui.choice_rot90->value()
		 );
	}
	else {
		const Fl_Menu_Item *crnt =
		 cl_gts_gui.choice_rot90->find_item( ca_scan2 );
		if (crnt != nullptr) {
		 cl_gts_gui.choice_rot90->value( crnt );
		 /* 回転値(システム設定値)をメモリする */
		 cl_gts_master.set_i_rotate_per_90(
			cl_gts_gui.choice_rot90->value()
		 );
		}
	}
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
	if (isdigit(ca_scan2[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_pixel_type->value( atoi(ca_scan2) );
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
	else {
		const Fl_Menu_Item *crnt =
		 cl_gts_gui.choice_pixel_type->find_item( ca_scan2 );
		if (crnt != nullptr) {
		 cl_gts_gui.choice_pixel_type->value( crnt );
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
	}
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
		!strcmp( ca_scan1, this->str_filter_rgb_erase_1dot_sw_ )) {
			cl_gts_gui.chkbtn_filter_rgb_erase_1dot_sw->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1, this->str_color_trace_real_time_ )) {
			/*cl_gts_gui.menite_color_trace_real_time->value(
				this->_chk_ON_OFF( ca_scan2 )
			);*/
			if (this->_chk_ON_OFF( ca_scan2 ) == 0) {
			 cl_gts_gui.menite_color_trace_real_time->clear();
			}
			else {
			 cl_gts_gui.menite_color_trace_real_time->set();
			}
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
		!strcmp( ca_scan1, this->str_file_number_frame_)) {
			/* ファイル番号リストの一番始めにやること */
			if (OFF == i_fnum_list_sw) {
			 /* ファイル番号リストの存在の有無 */
			 i_fnum_list_sw = ON;
			 /* 以前のリストをすべて削除 */
			 cl_gts_master.cl_file_number_list.remove_all();
			}

			/* 実際の画像ファイルの有無を調べて
			リストの最後に追加する */
	cl_gts_master.cl_file_number_list.append_fnum_list_with_chk_mark(
				atoi(ca_scan2));

			/* 選択状態の再現 */
			if (
			!strcmp( ca_scan3,this->str_file_number_selected_ ) ||
			!strcmp( ca_scan4,this->str_file_number_selected_ )
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
	"Warning : memory_config::_load_by_fp(-) : ignore '%s' at line %d"
				,ca_str ,ii );
			}
		}
	}

	/* frame listがない時は設定ファイルと判断してlistをクリアする */
	if (OFF == i_fnum_list_sw) {
		/* 以前のリストをすべて削除 */
		cl_gts_master.cl_file_number_list.remove_all();
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
		cl_gts_gui.filinp_level_save_dir_path->value(),
		cl_gts_gui.filinp_level_open_dir_path->value()
	);******/

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	cl_gts_master.cl_color_trace_thickness.cb_enh_01();
	cl_gts_master.cl_color_trace_thickness.cb_enh_02();
	cl_gts_master.cl_color_trace_thickness.cb_enh_03();
	cl_gts_master.cl_color_trace_thickness.cb_enh_04();
	cl_gts_master.cl_color_trace_thickness.cb_enh_05();
	cl_gts_master.cl_color_trace_thickness.cb_enh_06();

	/* LevelのCancelを可能にするためmemoryしておく */
	cl_gts_master.cl_bro_level.memory_from_gui(
		cl_gts_gui.filinp_level_save_dir_path->value()
	);

	return OK;
}
int memory_config::load( const char *cp_file_path, int i_load_trace_batch_sw )
{
	FILE *fp;
	char current_path[PTBL_PATH_MAX];

	/* ファイル名の一時記憶 */
	strncpy( current_path ,cp_file_path,PTBL_PATH_MAX );
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

	/* 画面は空白表示する指定(データは残っている) */
	cl_gts_master.cl_ogl_view.no_view_canvas();
	/* 画面クリア設定 */
	cl_gts_master.cl_ogl_view.clear_opengl(
		cl_gts_gui.opengl_view->w(),
		cl_gts_gui.opengl_view->h()
	);
	/* 画面クリア */
	cl_gts_gui.opengl_view->flush();

	/* 画像表示 */
	cl_gts_master.cb_read_and_trace_and_preview();

	return OK;
}
#endif

//----------------------------------------------------------------------

int memory_config::_chk_ON_OFF( char *cp_scan )
{
	if (!strcmp( this->str_on_, cp_scan ) ) {
		return 1;
	}
	return 0;
}

#include <iostream>
#include "igs_lex_white_space_and_double_quote.h"

namespace {

/* この関数(set_level_num_continue_type_())はgts_masterへ移設すべき */
void set_level_num_continue_type_( const std::string& str1 )
{
	const Fl_Menu_Item* crnt =
		cl_gts_gui.choice_level_num_continue_type->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }

	    cl_gts_gui.choice_level_num_continue_type->value(crnt);
	//if (cl_gts_gui.choice_level_num_continue_type->value() == 0) {
	if (cl_gts_gui.choice_level_num_continue_type->text()
	== std::string("End")) {
		cl_gts_gui.valinp_level_num_end->show();
		cl_gts_gui.choice_level_num_endless_direction->hide();
		cl_gts_gui.selbro_fnum_list->activate();
	}
	else {
		cl_gts_gui.valinp_level_num_end->hide();
		cl_gts_gui.choice_level_num_endless_direction->show();
		cl_gts_gui.selbro_fnum_list->deactivate();
	}
}
void set_level_num_endless_direction_( const std::string& str1 )
{
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_level_num_endless_direction->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }

	cl_gts_gui.choice_level_num_endless_direction->value(crnt);
}
void set_level_save_image_format_( const std::string& str1 )
{
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_level_save_image_format->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }

	cl_gts_gui.choice_level_save_image_format->value(crnt);
	cl_gts_master.cl_bro_level.cb_set_image_file_extension();
}
void set_level_open_image_format_( const std::string& str1 )
{
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_level_open_image_format->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }
	cl_gts_gui.choice_level_open_image_format->value(crnt);
}
void set_level_list_form_( const std::string& str1 )
{
#if 0
	if (isdigit(str1.c_str()[0])) {/* For Legacy Format...Delete sameday */
		cl_gts_gui.choice_level_list_form->value(
		 std::stoi(str1) // use C++11,throw exception then error
		);
	}
	else {
#endif
		const Fl_Menu_Item *crnt =
		 cl_gts_gui.choice_level_list_form->find_item(
			str1.c_str() );
		if (crnt == nullptr) { return; }
		cl_gts_gui.choice_level_list_form->value( crnt );
//	}

	/* File/Level表示によってボタンを表示/非表示する */
	if (cl_gts_gui.choice_level_list_form->text()
	== std::string("File")) {
		cl_gts_gui.menite_level_shift_number->deactivate();
		cl_gts_gui.menite_level_view_rgb_full_sw->deactivate();
	} else {
		cl_gts_gui.menite_level_shift_number->activate();
		cl_gts_gui.menite_level_view_rgb_full_sw->activate();
	}
}
void set_rotate_per_90_( const std::string& str1 )
{
	if (isdigit(str1.c_str()[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_rot90->value(
		  std::stoi(str1) // use C++11,throw exception then error
		 );
	}
	else {
	/*
		0=CW_-90 , 1=CW_0 , 2=CW_90 , 3=CW_180
		0=CW_-90はScannerにとっての正対なのでこれ以外は回転処理必要
		1=CW_0は作業者にとっての正対
	*/
		const Fl_Menu_Item *crnt =
			cl_gts_gui.choice_rot90->find_item( str1.c_str() );
		if (crnt == nullptr) { return; }

		cl_gts_gui.choice_rot90->value( crnt );
	}
	/* 回転値(システム設定値)をメモリする */
	cl_gts_master.set_i_rotate_per_90(
	 cl_gts_gui.choice_rot90->value() );
}
void set_pixel_type_( const std::string& str1 )
{
	if (isdigit(str1.c_str()[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_pixel_type->value(
		  std::stoi(str1) // use C++11,throw exception then error
		 );
	}
	else {
		const Fl_Menu_Item *crnt =
			cl_gts_gui.choice_pixel_type->find_item(
				str1.c_str() );
		if (crnt == nullptr) { return; }

		cl_gts_gui.choice_pixel_type->value( crnt );
	}
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

} // namespace

int memory_config::load_ifs_(
	std::ifstream& ifs , int load_trace_batch_sw
)
{
	int	fnum_list_sw = OFF;
	int	trace_batch_list_sw = OFF;
	int	level_list_redisplay_sw = OFF;

	std::string str;
	for (int ii = 1 ;std::getline(ifs,str) ;++ii) {/* 一行読む */
		if (str.empty()) { continue; }/* 空行は無視 */
		if ('#' == str.at(0)) { continue; }/* コメント行は無視 */
		std::vector< std::string > words; /* 単語に分割 */
		igs::lex::white_space_and_double_quote(str,words);
		if (words.size() < 2) { continue; }/* キーワードしかない */

		/* キーワードと、数値が1語以上(2<=words.size())ある */

		//---------- config ----------

		if ((2 == words.size()) &&
		(words.at(0) == this->str_config_dir_)) {
			cl_gts_master.cl_bro_config.init_config_dir(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_config_load_file_ )) {
			cl_gts_gui.strinp_config_load_file->value(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_config_save_as_file_)) {
			cl_gts_gui.strinp_config_save_as_file->value(
				words.at(1).c_str() );
		}

		//---------- level ----------

		else if ((2 == words.size()) &&
		((words.at(0)==this->str_level_save_dir_path_) ||
		 (words.at(0)==this->str_level_save_dir_path_legacy2016_))
		) {
			cl_gts_master.cl_bro_level.init_level_dir(
				words.at(1).c_str() );
			level_list_redisplay_sw = ON;
		}
		else if ((2 == words.size()) &&
		((words.at(0)==this->str_level_save_file_head_) ||
		 (words.at(0)==this->str_level_save_file_head_legacy2016_))
		) {
			cl_gts_gui.strinp_level_save_file_head->value(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_num_start_)) {
			cl_gts_gui.valinp_level_num_start->value(
			//atof(words.at(1).c_str()) // not return error
			//strtod(words.at(1).c_str()) // return error
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_num_end_ )) {
			cl_gts_gui.valinp_level_num_end->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) && (words.at(0)
		==this->str_level_num_continue_type_)) {
			set_level_num_continue_type_( words.at(1) );
		}
		else if ((2 == words.size()) && (words.at(0)
		==this->str_level_num_endless_direction_)) {
			set_level_num_endless_direction_( words.at(1) );
		}
		else if ((2 == words.size()) &&
		((words.at(0) ==this->str_level_save_image_format_) ||
		 (words.at(0) ==this->str_level_save_image_format_legacy2016_))
		) {
			set_level_save_image_format_( words.at(1) );
		}

		else if ((2 == words.size()) &&
		((words.at(0) == this->str_filter_rgb_erase_1dot_sw_) ||
		 (words.at(0) == this->str_filter_rgb_erase_1dot_sw_legacy2016_))
		) {
			cl_gts_gui.chkbtn_filter_rgb_erase_1dot_sw->value(
				(words.at(1) == this->str_on_) ?1 :0
			);
		}
		else if ((2 == words.size()) &&
		((words.at(0) == this->str_filter_rgb_color_trace_sw_) ||
		 (words.at(0) == this->str_filter_rgb_color_trace_sw_legacy2016_))
		) {
			cl_gts_gui.chkbtn_filter_rgb_color_trace->value(
				(words.at(1) == this->str_on_) ?1 :0
			);
		}

		else if ((2 == words.size()) &&
		((words.at(0) == this->str_level_open_dir_path_ ) ||
		 (words.at(0) == this->str_level_open_dir_path_legacy2016_))
		) {
			cl_gts_gui.filinp_level_open_dir_path->value(
				words.at(1).c_str() );
			cl_gts_gui.filinp_level_open_dir_path->position(
				words.at(1).size() );
			level_list_redisplay_sw = ON;
		}

		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_open_file_head_)) {
			cl_gts_gui.strinp_level_open_file->value(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) && (words.at(0)
		==this->str_level_open_image_format_)) {
			set_level_open_image_format_( words.at(1) );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_list_form_)) {
			set_level_list_form_( words.at(1) );
			level_list_redisplay_sw = ON;
		}

		//---------- area ----------

		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_select_ )) {
			const Fl_Menu_Item *crnt =
				cl_gts_gui.choice_area_selecter->find_item(
					words.at(1) );
			if (crnt != nullptr) {
			 cl_gts_gui.choice_area_selecter->value(crnt);
			 cl_gts_master.cb_area_selecter();
			}
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_x_pos_ )) {
			cl_gts_gui.valinp_area_x_pos->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_y_pos_ )) {
			cl_gts_gui.valinp_area_y_pos->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_aspect_ratio_select_)) {
			const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(
				words.at(1) );
			if (crnt != 0) {
		cl_gts_gui.choice_area_aspect_ratio_selecter->value(crnt);
		cl_gts_master.cb_area_aspect_ratio_selecter();
			}
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_x_size_)) {
			cl_gts_gui.valinp_area_x_size->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_y_size_)) {
			cl_gts_gui.valinp_area_y_size->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_x_pixel_ )) {
			cl_gts_gui.valinp_area_x_pixel->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_y_pixel_ )) {
			cl_gts_gui.valinp_area_y_pixel->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_resolution_dpi_ )) {
			cl_gts_gui.valinp_area_reso->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rotate_per_90_ )) {
			set_rotate_per_90_( words.at(1) );
		}

		//---------- scanner info. ----------

		/* スキャナー情報
			this->str_scanner_type_
			cl_gts_gui.txtout_scanner_type
			this->str_scanner_x_max_
			cl_gts_gui.valout_scanner_width_max
			this->str_scanner_y_max_
			cl_gts_gui.valout_scanner_height_max
		はTWAINドライバーから取るべきなので、
		ファイルからは設定しない
		*/

		//---------- pixel type ----------

		else if ((2 == words.size()) &&
		(words.at(0) == this->str_pixel_type_ )) {
			set_pixel_type_( words.at(1) );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_bw_threshold_ )) {
			cl_gts_gui.valinp_bw_threshold->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_bw_threshold)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_grayscale_brightness_ )) {
			cl_gts_gui.valinp_grays_brightness->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_brightness)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_grayscale_contrast_ )) {
			cl_gts_gui.valinp_grays_contrast->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_contrast)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_grayscale_gamma_ )) {
			cl_gts_gui.valinp_grays_gamma->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_gamma)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rgb_brightness_ )) {
			cl_gts_gui.valinp_rgb_brightness->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_brightness)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rgb_contrast_ )) {
			cl_gts_gui.valinp_rgb_contrast->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_contrast)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rgb_gamma_ )) {
			cl_gts_gui.valinp_rgb_gamma->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_gamma)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}

		//---------- legacy ----------

		/* color trace real time sw情報
		は固定にしたので設定しない
		this->str_color_trace_real_time_
		cl_gts_gui.menite_color_trace_real_time
		*/

		//---------- Number ----------

		else if (( (2==words.size())
			|| (3==words.size())
			|| (4==words.size())
		) && (words.at(0) == this->str_file_number_frame_)) {
			/* ファイル番号リストの一番始めにやること */
			if (OFF == fnum_list_sw) {
			 /* ファイル番号リストの存在の有無 */
			 fnum_list_sw = ON;
			 /* 以前のリストをすべて削除 */
			 cl_gts_master.cl_file_number_list.remove_all();
			}

			/* 実際の画像ファイルの有無を調べて
			リストの最後に追加する */
	cl_gts_master.cl_file_number_list.append_fnum_list_with_chk_mark(
	 std::stoi(words.at(1)) // use C++11,throw exception then error
	);

			/* 選択状態の再現 */
			if (
			 ((3<=words.size()) &&
	 		  (words.at(2) == this->str_file_number_selected_)
			 )
	 		||
			 ((4<=words.size()) &&
			  (words.at(3) == this->str_file_number_selected_)
			 )
			) {
				cl_gts_gui.selbro_fnum_list->select(
				 cl_gts_gui.selbro_fnum_list->size());
			}
		}

		/*------------------------------------------------*/

		else if ( (2 == words.size()) &&
		!strcmp( ca_scan0, this->str_trace_batch_dir_ )) {
			if (ON != load_trace_batch_sw) { continue; }

			cl_gts_master.cl_bro_trace_batch.init_trace_batch_dir(ca_scan1);
		}

		else if ( ((2==words.size()) || (3==words.size())) &&
		!strcmp( ca_scan0, this->str_trace_batch_list_)) {
			if (ON != load_trace_batch_sw) { continue; }

			/* ファイル番号リストの一番始めにやること */
			if (OFF == trace_batch_list_sw) {
				/* ファイル番号リストの存在の有無 */
				trace_batch_list_sw = ON;
				/* 以前のリストをすべて削除 */
				while (0 <
			cl_gts_gui.selbro_trace_batch_run_list->size()) {
			cl_gts_gui.selbro_trace_batch_run_list->remove(1);
				}
			}

			int i_len = strlen(ca_scan1);
			char* cp_tmp = nullptr;
			if (2 < i_len) {
				ca_scan1[i_len-1] = '\0';
				cp_tmp = &(ca_scan1[1]);
			} else {
				ca_scan1[0] = '\0';
				cp_tmp = ca_scan1;
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
			 words.size(),ca_scan0,ca_scan1,ca_scan2,ca_scan3
			 )
			) {
				pri_funct_err_bttvr(
	"Warning : memory_config::_load_by_fp(-) : ignore '%s' at line %d"
				,str ,ii );
			}
		}
	}
	ifs.close();/* ファイル閉じる */



	/* frame listがない時は設定ファイルと判断してlistをクリアする */
	if (OFF == fnum_list_sw) {
		/* 以前のリストをすべて削除 */
		cl_gts_master.cl_file_number_list.remove_all();
	}

	/* trace batch listがない時はlistをクリアする */
	if (ON == load_trace_batch_sw) {
	 if (OFF == trace_batch_list_sw) {
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
	if (ON == level_list_redisplay_sw) {
		cl_gts_master.cl_bro_level.cb_list_redisplay();
	}

	/******cl_gts_master.cl_list_level.load(
		cl_gts_gui.filinp_level_save_dir_path->value(),
		cl_gts_gui.filinp_level_open_dir_path->value()
	);******/

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	cl_gts_master.cl_color_trace_thickness.cb_enh_01();
	cl_gts_master.cl_color_trace_thickness.cb_enh_02();
	cl_gts_master.cl_color_trace_thickness.cb_enh_03();
	cl_gts_master.cl_color_trace_thickness.cb_enh_04();
	cl_gts_master.cl_color_trace_thickness.cb_enh_05();
	cl_gts_master.cl_color_trace_thickness.cb_enh_06();

	/* LevelのCancelを可能にするためmemoryしておく */
	cl_gts_master.cl_bro_level.memory_from_gui(
		cl_gts_gui.filinp_level_save_dir_path->value()
	);

	return OK;
}
int memory_config::load( const char *file_path, int load_trace_batch_sw )
{
 try {
	std::ifstream ifs( file_path );/* ファイル開く */
	ifs.exceptions(std::ios_base::failbit);/* エラー時例外送出設定 */
	this->load_ifs_(ifs ,load_trace_batch_sw); /* ファイル読む */
	ifs.close(); /* ファイル閉じる */

	this->memory_of_path = file_path; /* 正常保存ならファイル名の記憶 */
	cl_gts_master._print_window_headline(); /* ファイル名を表示する */

	/* frame number listにlevel名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
		cl_gts_master.cl_bro_level.cp_levelname()
	);

	/* level名からfileが上書きなら注意表示 */
	cl_gts_master.cl_bro_level.cb_level_name();

	/* 画面は空白表示する指定(データは残っている) */
	cl_gts_master.cl_ogl_view.no_view_canvas();
	/* 画面クリア設定 */
	cl_gts_master.cl_ogl_view.clear_opengl(
		cl_gts_gui.opengl_view->w(),
		cl_gts_gui.opengl_view->h()
	);
	/* 画面クリア */
	cl_gts_gui.opengl_view->flush();

	/* 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview();
 }
 catch (const std::ios_base::failure& e) {
	std::ostringstream ost;
	ost	<< "Error in loading \"" << file_path << "\","
		<< e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ダイオローグでユーザーに知らせる */
 }
}
