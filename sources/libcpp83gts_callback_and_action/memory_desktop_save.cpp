#include <stdio.h>
// #include <stdlib.h>	/* getenv() */
#include <string>
#include <string.h>
#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "pri.h"
#include "memory_desktop.h"
#include "memory_config.h"
#include "gts_gui.h"

int memory_desktop::_save_by_fp( FILE *fp )
{
	int i_ret;
	const char	*ccp_show = STR_WINDOW_SHOW,
			*ccp_hide = STR_WINDOW_HIDE;

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n",
		STR_WINDOW_OPENGL,
		cl_gts_gui.window_opengl->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_opengl->x(),
		cl_gts_gui.window_opengl->y(),
		cl_gts_gui.window_opengl->w(),
		cl_gts_gui.window_opengl->h() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n",
		STR_WINDOW_CONFIG_LOAD,
		cl_gts_gui.window_config_load->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_config_load->x(),
		cl_gts_gui.window_config_load->y(),
		cl_gts_gui.window_config_load->w(),
		cl_gts_gui.window_config_load->h() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n",
	 STR_WINDOW_CONFIG_SAVE_AS,
	 cl_gts_gui.window_config_save_as->visible()?ccp_show:ccp_hide,
	 cl_gts_gui.window_config_save_as->x(),
	 cl_gts_gui.window_config_save_as->y(),
	 cl_gts_gui.window_config_save_as->w(),
	 cl_gts_gui.window_config_save_as->h() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n",
		STR_WINDOW_LEVEL,
		cl_gts_gui.window_level->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_level->x(),
		cl_gts_gui.window_level->y(),
		cl_gts_gui.window_level->w(),
		cl_gts_gui.window_level->h() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n",
	 STR_WINDOW_CROP_AREA_AND_ROT90,
	 cl_gts_gui.window_crop_area_and_rot90->visible()?ccp_show:ccp_hide,
	 cl_gts_gui.window_crop_area_and_rot90->x(),
	 cl_gts_gui.window_crop_area_and_rot90->y() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n",
	 STR_WINDOW_PIXEL_TYPE_AND_BRIGHT,
	cl_gts_gui.window_pixel_type_and_bright->visible()?ccp_show:ccp_hide,
	 cl_gts_gui.window_pixel_type_and_bright->x(),
	 cl_gts_gui.window_pixel_type_and_bright->y() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n",
		STR_WINDOW_COLOR_TRACE,
		cl_gts_gui.window_color_trace->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_color_trace->x(),
		cl_gts_gui.window_color_trace->y() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n",
		STR_WINDOW_EDIT_COLOR,
		cl_gts_gui.window_edit_color->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_edit_color->x(),
		cl_gts_gui.window_edit_color->y() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n",
		STR_WINDOW_EDIT_HAB_MIN_MAX,
	 cl_gts_gui.window_hab_histogram->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_hab_histogram->x(),
		cl_gts_gui.window_hab_histogram->y() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n",
		STR_WINDOW_FNUM_LIST,
		cl_gts_gui.window_fnum_list->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_fnum_list->x(),
		cl_gts_gui.window_fnum_list->y(),
		cl_gts_gui.window_fnum_list->w(),
		cl_gts_gui.window_fnum_list->h() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n",
		STR_WINDOW_TRACE_BATCH,
		cl_gts_gui.window_trace_batch->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_trace_batch->x(),
		cl_gts_gui.window_trace_batch->y(),
		cl_gts_gui.window_trace_batch->w(),
		cl_gts_gui.window_trace_batch->h() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n",
		STR_WINDOW_NEXT_SCAN,
		cl_gts_gui.window_next_scan->visible()?ccp_show:ccp_hide,
		cl_gts_gui.window_next_scan->x(),
		cl_gts_gui.window_next_scan->y() );
	if (i_ret < 0) { return NG; }

	return OK;
}
int memory_desktop::_save_startup_path_by_fp( FILE *fp )
{
	int i_ret;

	i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_CONFIG_DIR,
		cl_gts_gui.filinp_config_load_dir->value() );
	if (i_ret < 0) { return NG; }

	/******i_ret = fprintf(fp, "%-24s \"%s\"\n",
			STR_CONFIG_FILE,
		cl_gts_gui.strinp_config_load_file->value() );
	if (i_ret < 0) { return NG; }******/

	return OK;
}

int memory_desktop::_save_by_fname( const char *cp_fname )
{
	FILE *fp;

	fp = fopen( cp_fname, "w" );
	if (NULL == fp) {
		pri_funct_err_bttvr(
		"fopen(%s,w) returns NULL.",cp_fname);
		return NG;
	} 

	if (OK != this->_save_by_fp( fp )) {
		pri_funct_err_bttvr(
		 "this->_save_by_fp(-) returns NG.");
		return NG;
	}
	if (OK != this->_save_startup_path_by_fp( fp )) {
		pri_funct_err_bttvr(
		 "this->_save_startup_path_by_fp(-) returns NG.");
		return NG;
	}
	if (fclose(fp)) {
		pri_funct_err_bttvr("fclose(-) returns not zero.");
		return NG;
	}
	return OK;
}

int memory_desktop::save( void )
{
#if 0//-----------------------------------------------------------
	int	i_len;
	char ca_home[FILENAME_MAX];

	// char *cp_home;
	// cp_home = getenv( "HOME" );
	/* 環境変数がない */
	/******if (NULL == cp_home) {
		pri_funct_err_bttvr("getenv(HOME) returns NULL.");
		return NG;
	}******/

	std::string dir_path;
	igs::resource::get_user_home(dir_path);
	if (dir_path.empty()) {
		pri_funct_err_bttvr(
		"igs::resource::get_user_home(-) can not get dir");
		return NG;
	}
	const char *cp_home = dir_path.c_str();

	i_len = strlen( cp_home );
	i_len += strlen( ptbl_get_cp_path_separeter() );
	i_len += strlen( STR_DESKTOP_FILENAME );
	if (FILENAME_MAX <= i_len) {
		pri_funct_err_bttvr(
		"over FILENAME_MAX<%d>.", FILENAME_MAX);
		return NG;
	}

	(void)strcpy( ca_home, cp_home );
	(void)strcat( ca_home, ptbl_get_cp_path_separeter() );
	(void)strcat( ca_home, STR_DESKTOP_FILENAME );
#endif//----------------------------------------------------------
	if (this->set_desktop_file_path_() != OK) {
		pri_funct_err_bttvr(
		 "set_desktop_file_path_(-) can not set dir");
		return NG;
	}

	if (OK != this->_save_by_fname(this->desktop_file_path_.c_str())) {
		pri_funct_err_bttvr(
		"memory_desktop::_save_by_fname(-) returns NG.");
		return NG;
	}

	return OK;
}
