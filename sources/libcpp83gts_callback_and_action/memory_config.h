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
	static const char* str_on_;
	static const char* str_off_;

	static const char* str_config_dir_;
	static const char* str_config_load_file_;
	static const char* str_config_save_as_file_;

	static const char* str_level_dir_;
	static const char* str_level_list_form_;
	static const char* str_level_file_;
	static const char* str_level_num_start_;
	static const char* str_level_num_end_;
	static const char* str_level_rgb_scan_dir_;
	static const char* str_level_rgb_trace_save_sw_;
	static const char* str_level_rgb_full_save_sw_;
	static const char* str_level_rgb_with_full_sw_;
	static const char* str_level_image_file_format_;

	static const char* str_area_select_;
	static const char* str_area_x_pos_;
	static const char* str_area_y_pos_;
	static const char* str_area_aspect_ratio_select_;
	static const char* str_area_x_size_;
	static const char* str_area_y_size_;
	static const char* str_area_x_pixel_;
	static const char* str_area_y_pixel_;
	static const char* str_area_resolution_dpi_;
	static const char* str_rotate_per_90_;
	static const char* str_scanner_type_;
	static const char* str_scanner_x_max_;
	static const char* str_scanner_y_max_;

	static const char* str_pixel_type_;
	static const char* str_bw_threshold_;
	static const char* str_grayscale_brightness_;
	static const char* str_grayscale_contrast_;
	static const char* str_grayscale_gamma_;
	static const char* str_rgb_brightness_;
	static const char* str_rgb_contrast_;
	static const char* str_rgb_gamma_;

	static const char* str_color_trace_erase_1dot_;
	static const char* str_color_trace_real_time_;
	static const char* str_frame_number_insert_;
	static const char* str_frame_number_list_;
	static const char* str_frame_number_selected_;

	static const char* str_trace_batch_dir_;
	static const char* str_trace_batch_list_;

	static const char* str_color_trace_01_chk_;
	static const char* str_color_trace_01_src_hh_min_;
	static const char* str_color_trace_01_src_hh_max_;
	static const char* str_color_trace_01_src_aa_min_;
	static const char* str_color_trace_01_src_aa_max_;
	static const char* str_color_trace_01_src_bb_min_;
	static const char* str_color_trace_01_src_bb_max_;
	static const char* str_color_trace_01_tgt_rgb_;

	static const char* str_color_trace_02_chk_;
	static const char* str_color_trace_02_src_hh_min_;
	static const char* str_color_trace_02_src_hh_max_;
	static const char* str_color_trace_02_src_aa_min_;
	static const char* str_color_trace_02_src_aa_max_;
	static const char* str_color_trace_02_src_bb_min_;
	static const char* str_color_trace_02_src_bb_max_;
	static const char* str_color_trace_02_tgt_rgb_;

	static const char* str_color_trace_03_chk_;
	static const char* str_color_trace_03_src_hh_min_;
	static const char* str_color_trace_03_src_hh_max_;
	static const char* str_color_trace_03_src_aa_min_;
	static const char* str_color_trace_03_src_aa_max_;
	static const char* str_color_trace_03_src_bb_min_;
	static const char* str_color_trace_03_src_bb_max_;
	static const char* str_color_trace_03_tgt_rgb_;

	static const char* str_color_trace_04_chk_;
	static const char* str_color_trace_04_src_hh_min_;
	static const char* str_color_trace_04_src_hh_max_;
	static const char* str_color_trace_04_src_aa_min_;
	static const char* str_color_trace_04_src_aa_max_;
	static const char* str_color_trace_04_src_bb_min_;
	static const char* str_color_trace_04_src_bb_max_;
	static const char* str_color_trace_04_tgt_rgb_;

	static const char* str_color_trace_05_chk_;
	static const char* str_color_trace_05_src_hh_min_;
	static const char* str_color_trace_05_src_hh_max_;
	static const char* str_color_trace_05_src_aa_min_;
	static const char* str_color_trace_05_src_aa_max_;
	static const char* str_color_trace_05_src_bb_min_;
	static const char* str_color_trace_05_src_bb_max_;
	static const char* str_color_trace_05_tgt_rgb_;

	static const char* str_color_trace_06_chk_;
	static const char* str_color_trace_06_src_hh_min_;
	static const char* str_color_trace_06_src_hh_max_;
	static const char* str_color_trace_06_src_aa_min_;
	static const char* str_color_trace_06_src_aa_max_;
	static const char* str_color_trace_06_src_bb_min_;
	static const char* str_color_trace_06_src_bb_max_;
	static const char* str_color_trace_06_tgt_rgb_;

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
