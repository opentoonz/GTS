#include <FL/Fl.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "pri.h"
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

int memory_config::_save_comment_by_fp( FILE *fp )
{
	int i_ret;
	time_t tt;
	char *cp;

	tt = time(NULL);
	cp = asctime(localtime(&tt));

	/* cpは26文字とヌル文字の入った文字列へのポインター
		Example : "Fri Sep 13 00:00:00 1986\n\0"
		cpの示す文字列はstatic領域なのでfree()してはいけません
	*/

	i_ret = fprintf(fp, "# date and time : %s", cp );
	if (i_ret < 0) { return NG; }

	/*------------------------------------------------*/

	cp = ptbl_get_cp_username();
	if (NULL == cp) { cp = "unknown"; }
	i_ret = fprintf(fp, "# current user  : %s\n#\n", cp );
	if (i_ret < 0) { return NG; }

	return OK;
}

int memory_config::_save_by_fp( FILE *fp )
{
	int i_ret;

	/*------------------------------------------------*/
	/* config loadとsave saとsaveは同じdirを示す */
	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_CONFIG_DIR,
		cl_gts_gui.filinp_config_load_dir->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_CONFIG_LOAD_FILE,
		cl_gts_gui.strinp_config_load_file->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_CONFIG_SAVE_AS_FILE,
		cl_gts_gui.strinp_config_save_as_file->value() );
	if (i_ret < 0) { return NG; }

	/*------------------------------------------------*/

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_LEVEL_DIR,
		cl_gts_gui.filinp_level_dir->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %d\n",
			STR_LEVEL_LIST_FORM,
		cl_gts_gui.choice_level_list_form->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_LEVEL_FILE,
		cl_gts_gui.strinp_level_file->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_LEVEL_NUM_START,
		cl_gts_gui.valinp_level_start->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_LEVEL_NUM_END,
		cl_gts_gui.valinp_level_end->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %s\n",
			STR_LEVEL_RGB_TRACE_SAVE_SW,
			cl_gts_gui.chkbtn_level_trace_save_sw->value()?
			this->_ccp_on:this->_ccp_off );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_LEVEL_RGB_SCAN_DIR,
		cl_gts_gui.filinp_level_rgb_scan_dir->value() );
	if (i_ret < 0) { return NG; }

	/*------------------------------------------------*/

	i_ret = fprintf(fp, "%-24s %s\n",
			STR_AREA_SELECT,
		cl_gts_gui.choice_area_selecter->text()
	);
	if (i_ret < 0) { return NG; }

	/* Default(Custom)のときはエリア値を保存 */
	//if (0 == cl_gts_gui.choice_area_selecter->value()) {

	/* Presetのときも、マウスドラッグやRotateでエリア値は変化する
	のですべての値は保存し再現する2014-03-18 */

		i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_X_POS,
			cl_gts_gui.valinp_area_x_pos->value() );
		if (i_ret < 0) { return NG; }

		i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_Y_POS,
			cl_gts_gui.valinp_area_y_pos->value() );
		if (i_ret < 0) { return NG; }

		i_ret = fprintf(fp, "%-24s %s\n",
				STR_AREA_ASPECT_RATIO_SELECT,
			cl_gts_gui.choice_area_aspect_ratio_selecter->text()
		);
		if (i_ret < 0) { return NG; }

		i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_X_SIZE,
			cl_gts_gui.valinp_area_x_size->value() );
		if (i_ret < 0) { return NG; }

		i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_Y_SIZE,
			cl_gts_gui.valinp_area_y_size->value() );
		if (i_ret < 0) { return NG; }
	//}

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_X_PIXEL,
		cl_gts_gui.valinp_area_x_pixel->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_Y_PIXEL,
		cl_gts_gui.valinp_area_y_pixel->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_AREA_RESOLUTION_DPI,
		cl_gts_gui.valinp_area_reso->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %d\n",
			STR_ROTATE_PER_90,
		cl_gts_gui.choice_rot90->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_SCANNER_TYPE,
		cl_gts_gui.txtout_scanner_type->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_SCANNER_X_MAX,
		cl_gts_gui.valout_scanner_width_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_SCANNER_Y_MAX,
		cl_gts_gui.valout_scanner_height_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %d\n",
			STR_PIXEL_TYPE,
		cl_gts_gui.choice_pixel_type->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_BW_THRESHOLD,
		cl_gts_gui.valinp_bw_threshold->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_GRAYS_BRIGHTNESS,
		cl_gts_gui.valinp_grays_brightness->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_GRAYS_CONTRAST,
		cl_gts_gui.valinp_grays_contrast->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_GRAYS_GAMMA,
		cl_gts_gui.valinp_grays_gamma->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_RGB_BRIGHTNESS,
		cl_gts_gui.valinp_rgb_brightness->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_RGB_CONTRAST,
		cl_gts_gui.valinp_rgb_contrast->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n",
			STR_RGB_GAMMA,
		cl_gts_gui.valinp_rgb_gamma->value() );
	if (i_ret < 0) { return NG; }

	/*- color trace window other ----*/

	i_ret = fprintf(fp, "%-24s %s\n",
			STR_COLOR_TRACE_ERASE_1DOT,
			cl_gts_gui.chkbtn_color_trace_erase_1dot->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %s\n",
			STR_COLOR_TRACE_REAL_TIME,
			cl_gts_gui.chkbtn_color_trace_real_time->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	/*------------------------------------------------*/

	/******i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_FRAME_NUMBER_INSERT,
		cl_gts_gui.norinp_fnum_insert->value() );
	if (i_ret < 0) { return NG; }**********/

	/*------------------------------------------------*/

	return OK;
}

int memory_config::_save_fnum_by_fp( FILE *fp )
{
	int i_ret;
	int ii;

	/* リストを全てサーチ */
	for (ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		i_ret = fprintf(fp, "%s %s",
			STR_FRAME_NUMBER_LIST,
			cl_gts_gui.selbro_fnum_list->text(ii) );
		if (i_ret < 0) { return NG; }

		if ( cl_gts_gui.selbro_fnum_list->selected(ii) ) {
			i_ret = fprintf(fp, " %s\n",
				STR_FRAME_NUMBER_SELECTED );
		} else {
			i_ret = fprintf(fp, "\n");
		}
		if (i_ret < 0) { return NG; }
	}

	return OK;
}

int memory_config::_save_trace_batch_by_fp( FILE *fp )
{
	int i_ret;
	int ii;

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_TRACE_BATCH_DIR,
		cl_gts_gui.filinp_trace_batch_dir->value() );
	if (i_ret < 0) { return NG; }

	/* リストを全てサーチ */
	for (ii = 1; ii <= cl_gts_gui.selbro_trace_batch_run_list->size();
	++ii) {
		i_ret = fprintf(fp, "%s \"%s\"\n",
			STR_TRACE_BATCH_LIST,
			cl_gts_gui.selbro_trace_batch_run_list->text(ii) );
		if (i_ret < 0) { return NG; }
	}

	return OK;
}

int memory_config::save( char *cp_file_path )
{
	FILE *fp;

	/* ファイル名の一時記憶 */
	strncpy( this->_ca_current_path,cp_file_path,PTBL_PATH_MAX );
	this->_ca_current_path[PTBL_PATH_MAX-1] = '\0';

	/* ファイル開く */
	fp = fopen( this->_ca_current_path, "w" );
	if (NULL == fp) {
		pri_funct_err_bttvr(
		"fopen(%s,w) returns NULL.",this->_ca_current_path);
		return NG;
	} 
	/* ファイルに設定保存 */
	if (OK != this->_save_comment_by_fp( fp )) {
		pri_funct_err_bttvr(
	"memory_config::_save_comment_by_fp(-) returns NG.");
		return NG;
	}
	if (OK != this->_save_by_fp( fp )) {
		pri_funct_err_bttvr(
	"memory_config::_save_by_fp(-) returns NG.");
		return NG;
	}
	if (OK != this->_save_trace_src_hsv_by_fp( fp )) {
		pri_funct_err_bttvr(
	"memory_config::_save_trace_src_hsv_by_fp(-) returns NG.");
		return NG;
	}
	if (OK != this->_save_fnum_by_fp( fp )) {
		pri_funct_err_bttvr(
	"memory_config::_save_fnum_by_fp(-) returns NG.");
		return NG;
	}
	if (OK != this->_save_trace_batch_by_fp( fp )) {
		pri_funct_err_bttvr(
	"memory_config::_save_trace_batch_by_fp(-) returns NG.");
		return NG;
	}
	/* ファイル閉じる */
	if (fclose(fp)) {
		pri_funct_err_bttvr("fclose(-) returns not zero.");
		return NG;
	}

	/* 正常に設定したなら、ファイル名の記憶 */
	strcpy( this->_ca_memory_path, this->_ca_current_path );

	/* ファイル名を表示する */
	cl_gts_master._print_window_headline();

	return OK;
}
