#ifndef memory_config_h
#define memory_config_h

#include <stdio.h>
#include <string>
#include "ptbl_path_max.h"
#include "ptbl_returncode.h"

typedef enum {
	E_MEMORY_CONFIG_LOAD_MATCH = 1,
	E_MEMORY_CONFIG_LOAD_NOTHING,
	E_MEMORY_CONFIG_LOAD_ERROR,
} E_MEMORY_CONFIG_LOAD_RET;

class memory_config {
public:
	memory_config()
	{
	}
	int save( const char *cp_file_path );
	int load( const char *cp_file_path, int i_load_trace_batch_sw=ON );

	std::string memory_of_path;
private:
	const char* str_on_  ="ON";
	const char* str_off_ ="OFF";
	
	const char* str_config_dir_
		      ="config_dir";
	const char* str_config_load_file_
		      ="config_load_file";
	const char* str_config_save_as_file_
		      ="config_save_as_file";
	
	const char* str_level_dir_
		      ="level_dir";
	const char* str_level_list_form_
		      ="level_list_form";
	const char* str_level_file_
		      ="level_file";
	const char* str_level_num_start_
		      ="level_num_start";
	const char* str_level_num_end_
		      ="level_num_end";
	const char* str_level_rgb_scan_dir_
		      ="level_rgb_scan_dir";
	const char* str_level_rgb_trace_save_sw_
		      ="level_rgb_trace_save_sw";
	const char* str_level_rgb_full_save_sw_
		      ="level_rgb_full_save_sw";
	const char* str_level_rgb_with_full_sw_
		      ="level_rgb_with_full_sw";
	const char* str_level_image_file_format_
		      ="level_image_file_format";
	
	const char* str_area_select_
		      ="area_select";
	const char* str_area_x_pos_
		      ="area_x_pos";
	const char* str_area_y_pos_
		      ="area_y_pos";
	const char* str_area_aspect_ratio_select_
		      ="area_aspect_ratio_select";
	const char* str_area_x_size_
		      ="area_x_size";
	const char* str_area_y_size_
		      ="area_y_size";
	const char* str_area_x_pixel_
		      ="area_x_pixel";
	const char* str_area_y_pixel_
		      ="area_y_pixel";
	const char* str_area_resolution_dpi_
		      ="area_resolution_dpi";
	const char* str_rotate_per_90_
		      ="rotate_per_90";
	const char* str_scanner_type_
		      ="scanner_type";
	const char* str_scanner_x_max_
		      ="scanner_x_max";
	const char* str_scanner_y_max_
		      ="scanner_y_max";
	
	const char* str_pixel_type_
		      ="pixel_type";
	const char* str_bw_threshold_
		      ="bw_threshold";
	const char* str_grayscale_brightness_
		      ="grayscale_brightness";
	const char* str_grayscale_contrast_
		      ="grayscale_contrast";
	const char* str_grayscale_gamma_
		      ="grayscale_gamma";
	const char* str_rgb_brightness_
		      ="rgb_brightness";
	const char* str_rgb_contrast_
		      ="rgb_contrast";
	const char* str_rgb_gamma_
		      ="rgb_gamma";
	
	const char* str_color_trace_erase_1dot_
		      ="color_trace_erase_1dot";
	const char* str_color_trace_real_time_
		      ="color_trace_real_time";
	const char* str_frame_number_insert_
		      ="frame_number_insert";
	const char* str_frame_number_list_
		      ="frame";
	const char* str_frame_number_selected_
		      ="selected";
	
	const char* str_trace_batch_dir_
		      ="trace_batch_dir";
	const char* str_trace_batch_list_
		      ="batch";
	
	const char* str_color_trace_01_chk_
		      ="color_trace_01_chk";
	const char* str_color_trace_01_src_hh_min_
		      ="color_trace_01_src_hue_min";
	const char* str_color_trace_01_src_hh_max_
		      ="color_trace_01_src_hue_max";
	const char* str_color_trace_01_src_aa_min_
		      ="color_trace_01_src_sat_min";
	const char* str_color_trace_01_src_aa_max_
		      ="color_trace_01_src_sat_max";
	const char* str_color_trace_01_src_bb_min_
		      ="color_trace_01_src_val_min";
	const char* str_color_trace_01_src_bb_max_
		      ="color_trace_01_src_val_max";
	const char* str_color_trace_01_tgt_rgb_
		      ="color_trace_01_tgt_rgb";
	
	const char* str_color_trace_02_chk_
		      ="color_trace_02_chk";
	const char* str_color_trace_02_src_hh_min_
		      ="color_trace_02_src_hue_min";
	const char* str_color_trace_02_src_hh_max_
		      ="color_trace_02_src_hue_max";
	const char* str_color_trace_02_src_aa_min_
		      ="color_trace_02_src_sat_min";
	const char* str_color_trace_02_src_aa_max_
		      ="color_trace_02_src_sat_max";
	const char* str_color_trace_02_src_bb_min_
		      ="color_trace_02_src_val_min";
	const char* str_color_trace_02_src_bb_max_
		      ="color_trace_02_src_val_max";
	const char* str_color_trace_02_tgt_rgb_
		      ="color_trace_02_tgt_rgb";
	
	const char* str_color_trace_03_chk_
		      ="color_trace_03_chk";
	const char* str_color_trace_03_src_hh_min_
		      ="color_trace_03_src_hue_min";
	const char* str_color_trace_03_src_hh_max_
		      ="color_trace_03_src_hue_max";
	const char* str_color_trace_03_src_aa_min_
		      ="color_trace_03_src_sat_min";
	const char* str_color_trace_03_src_aa_max_
		      ="color_trace_03_src_sat_max";
	const char* str_color_trace_03_src_bb_min_
		      ="color_trace_03_src_val_min";
	const char* str_color_trace_03_src_bb_max_
		      ="color_trace_03_src_val_max";
	const char* str_color_trace_03_tgt_rgb_
		      ="color_trace_03_tgt_rgb";
	
	const char* str_color_trace_04_chk_
		      ="color_trace_04_chk";
	const char* str_color_trace_04_src_hh_min_
		      ="color_trace_04_src_hue_min";
	const char* str_color_trace_04_src_hh_max_
		      ="color_trace_04_src_hue_max";
	const char* str_color_trace_04_src_aa_min_
		      ="color_trace_04_src_sat_min";
	const char* str_color_trace_04_src_aa_max_
		      ="color_trace_04_src_sat_max";
	const char* str_color_trace_04_src_bb_min_
		      ="color_trace_04_src_val_min";
	const char* str_color_trace_04_src_bb_max_
		      ="color_trace_04_src_val_max";
	const char* str_color_trace_04_tgt_rgb_
		      ="color_trace_04_tgt_rgb";
	
	const char* str_color_trace_05_chk_
		      ="color_trace_05_chk";
	const char* str_color_trace_05_src_hh_min_
		      ="color_trace_05_src_hue_min";
	const char* str_color_trace_05_src_hh_max_
		      ="color_trace_05_src_hue_max";
	const char* str_color_trace_05_src_aa_min_
		      ="color_trace_05_src_sat_min";
	const char* str_color_trace_05_src_aa_max_
		      ="color_trace_05_src_sat_max";
	const char* str_color_trace_05_src_bb_min_
		      ="color_trace_05_src_val_min";
	const char* str_color_trace_05_src_bb_max_
		      ="color_trace_05_src_val_max";
	const char* str_color_trace_05_tgt_rgb_
		      ="color_trace_05_tgt_rgb";
	
	const char* str_color_trace_06_chk_
		      ="color_trace_06_chk";
	const char* str_color_trace_06_src_hh_min_
		      ="color_trace_06_src_hue_min";
	const char* str_color_trace_06_src_hh_max_
		      ="color_trace_06_src_hue_max";
	const char* str_color_trace_06_src_aa_min_
		      ="color_trace_06_src_sat_min";
	const char* str_color_trace_06_src_aa_max_
		      ="color_trace_06_src_sat_max";
	const char* str_color_trace_06_src_bb_min_
		      ="color_trace_06_src_val_min";
	const char* str_color_trace_06_src_bb_max_
		      ="color_trace_06_src_val_max";
	const char* str_color_trace_06_tgt_rgb_
		      ="color_trace_06_tgt_rgb";

	//-------------------------------------

	int _save_comment_by_fp( FILE *fp );
	int _save_config_by_fp( FILE *fp );
	int _save_level_by_fp( FILE *fp );
	int _save_area_by_fp( FILE *fp );
	int _save_pixel_type_by_fp( FILE *fp );
	int _save_trace_by_fp( FILE *fp );
	int _save_fnum_by_fp( FILE *fp );
	int _save_trace_batch_by_fp( FILE *fp );
	int _save_trace_src_hsv_by_fp( FILE *fp );

	int _chk_ON_OFF( char *cp_scan );
	int _load_by_fp( FILE *fp, int i_load_trace_batch_sw );
	E_MEMORY_CONFIG_LOAD_RET _load_trace_src_hsv_by_fp( int i_num, char *cp1, char *cp2, char *cp3, char *cp4 );
};

#endif /* !memory_config_h */
