#ifndef __memory_config_h__
#define __memory_config_h__

#include <stdio.h>
#include "ptbl_path_max.h"
#include "ptbl_returncode.h"

#define STR_CONFIG_DIR			"config_dir"
#define STR_CONFIG_LOAD_FILE		"config_load_file"
#define STR_CONFIG_SAVE_AS_FILE		"config_save_as_file"

#define STR_LEVEL_DIR			"level_dir"
#define STR_LEVEL_LIST_FORM		"level_list_form"
#define STR_LEVEL_FILE			"level_file"
#define STR_LEVEL_NUM_START		"level_num_start"
#define STR_LEVEL_NUM_END		"level_num_end"
#define STR_LEVEL_RGB_SCAN_DIR		"level_rgb_scan_dir"
#define STR_LEVEL_RGB_TRACE_SAVE_SW	"level_rgb_trace_save_sw"

#define STR_AREA_SELECT			"area_select"
#define STR_AREA_X_POS			"area_x_pos"
#define STR_AREA_Y_POS			"area_y_pos"
#define STR_AREA_ASPECT_RATIO_SELECT	"area_aspect_ratio_select"
#define STR_AREA_X_SIZE			"area_x_size"
#define STR_AREA_Y_SIZE			"area_y_size"
#define STR_AREA_X_PIXEL		"area_x_pixel"
#define STR_AREA_Y_PIXEL		"area_y_pixel"
#define STR_AREA_RESOLUTION_DPI		"area_resolution_dpi"
#define STR_ROTATE_PER_90		"rotate_per_90"
#define STR_SCANNER_TYPE		"scanner_type"
#define STR_SCANNER_X_MAX		"scanner_x_max"
#define STR_SCANNER_Y_MAX		"scanner_y_max"

#define STR_PIXEL_TYPE			"pixel_type"
#define STR_BW_THRESHOLD		"bw_threshold"
#define STR_GRAYS_BRIGHTNESS		"grayscale_brightness"
#define STR_GRAYS_CONTRAST		"grayscale_contrast"
#define STR_GRAYS_GAMMA			"grayscale_gamma"
#define STR_RGB_BRIGHTNESS		"rgb_brightness"
#define STR_RGB_CONTRAST		"rgb_contrast"
#define STR_RGB_GAMMA			"rgb_gamma"

#define STR_COLOR_TRACE_ERASE_1DOT	"color_trace_erase_1dot"
#define STR_COLOR_TRACE_REAL_TIME	"color_trace_real_time"

#define STR_FRAME_NUMBER_INSERT		"frame_number_insert"
#define STR_FRAME_NUMBER_LIST		"frame"
#define STR_FRAME_NUMBER_SELECTED	"selected"

#define STR_TRACE_BATCH_DIR		"trace_batch_dir"
#define STR_TRACE_BATCH_LIST		"batch"
/*					 12345678901234567890123 */

typedef enum {
	E_MEMORY_CONFIG_LOAD_MATCH = 1,
	E_MEMORY_CONFIG_LOAD_NOTHING,
	E_MEMORY_CONFIG_LOAD_ERROR,
} E_MEMORY_CONFIG_LOAD_RET;

class memory_config {
public:
	memory_config()
	{
		this->_ccp_on  = "ON";
		this->_ccp_off = "OFF";
		this->_ca_current_path[0] = '\0';
		this->_ca_memory_path[0] = '\0';
	}
	int save( char *cp_file_path );
	int load( char *cp_file_path, int i_load_trace_batch_sw=ON );

	/****char *cp_current_filepath( void ) const {
		return this->_ca_current_path; }***/
	char *cp_memory_path( void ) {
		return this->_ca_memory_path; }
private:
	const char	*_ccp_on,
			*_ccp_off;

	char	_ca_current_path[PTBL_PATH_MAX];
	char	_ca_memory_path[PTBL_PATH_MAX];

	int _save_comment_by_fp( FILE *fp );
	int _save_by_fp( FILE *fp );
	int _save_fnum_by_fp( FILE *fp );
	int _save_trace_batch_by_fp( FILE *fp );
	int _save_trace_src_hsv_by_fp( FILE *fp );

	int _chk_ON_OFF( char *cp_scan );
	int _load_by_fp( FILE *fp, int i_load_trace_batch_sw );
	E_MEMORY_CONFIG_LOAD_RET _load_trace_src_hsv_by_fp( int i_num, char *cp1, char *cp2, char *cp3, char *cp4 );
};

#endif /* !__memory_config_h__ */
