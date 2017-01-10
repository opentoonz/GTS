#include <stdio.h>
#include <string>
#include <string.h>
#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "pri.h"
#include "memory_desktop.h"
#include "gts_gui.h"
#include "gts_master.h"

int memory_desktop::_save_by_fp( FILE *fp )
{
	int i_ret;
	const char	*ccp_show = this->str_show_,
			*ccp_hide = this->str_hide_;

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n"
	, this->str_window_opengl_
	, cl_gts_gui.window_opengl->visible()?ccp_show:ccp_hide
	, cl_gts_gui.window_opengl->x()
	, cl_gts_gui.window_opengl->y()
	, cl_gts_gui.window_opengl->w()
	, cl_gts_gui.window_opengl->h()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_next_scan_
	, cl_gts_gui.window_next_scan->visible()?ccp_show:ccp_hide
	, cl_gts_gui.window_next_scan->x()
	, cl_gts_gui.window_next_scan->y()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_level_
	, cl_gts_gui.menite_level->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_level_set->x()
	, cl_gts_gui.window_level_set->y()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_crop_area_and_rot90_
	, cl_gts_gui.menite_crop_area_and_rot90->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_crop_area_and_rot90->x()
	, cl_gts_gui.window_crop_area_and_rot90->y()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_pixel_type_and_bright_
	, cl_gts_gui.menite_pixel_type_and_bright->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_pixel_type_and_bright->x()
	, cl_gts_gui.window_pixel_type_and_bright->y()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_color_trace_
	, cl_gts_gui.menite_color_trace->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_color_trace->x()
	, cl_gts_gui.window_color_trace->y()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n"
	, this->str_window_fnum_list_
	, cl_gts_gui.menite_fnum_list->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_fnum_list->x()
	, cl_gts_gui.window_fnum_list->y()
	, cl_gts_gui.window_fnum_list->w()
	, cl_gts_gui.window_fnum_list->h()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n"
	, this->str_window_trace_batch_
	, cl_gts_gui.menite_trace_batch->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_trace_batch_job->x()
	, cl_gts_gui.window_trace_batch_job->y()
	, cl_gts_gui.window_trace_batch_job->w()
	, cl_gts_gui.window_trace_batch_job->h()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d %d %d\n"
	, this->str_window_thickness_
	, cl_gts_gui.menite_thickness->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_thickness->x()
	, cl_gts_gui.window_thickness->y()
	, cl_gts_gui.window_thickness->w()
	, cl_gts_gui.window_thickness->h()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_edit_color_
	, cl_gts_gui.menite_edit_color->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_edit_color->x()
	, cl_gts_gui.window_edit_color->y()
	);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-28s %s %d %d\n"
	, this->str_window_edit_hab_min_max_
	, cl_gts_gui.menite_edit_hsv_min_max->value()?ccp_show:ccp_hide
	, cl_gts_gui.window_hab_histogram->x()
	, cl_gts_gui.window_hab_histogram->y()
	);
	if (i_ret < 0) { return NG; }

# ifndef _WIN32
    if(cl_gts_master.cl_iip_scan.device_name()) {
        i_ret = fprintf(fp, "%-24s \"%s\"\n"
	, this->str_sane_device_name_
	, cl_gts_master.cl_iip_scan.device_name()
	);
        if(i_ret < 0) {
            return NG;
        }
    }
# endif

	return OK;
}
int memory_desktop::_save_startup_path_by_fp( FILE *fp )
{
	int i_ret;

	i_ret = fprintf(fp, "%-24s \"%s\"\n"
		,this->str_config_dir_
		,cl_gts_master.cl_config.get_dir_path().c_str()
	);
	if (i_ret < 0) { return NG; }

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
