#ifndef __memory_desktop_h__
#define __memory_desktop_h__

#define STR_CONFIG_DIR			"config_dir"

#define STR_WINDOW_OPENGL		 "window_main"

#define STR_WINDOW_CONFIG_LOAD		 "window_config_load"
#define STR_WINDOW_CONFIG_SAVE_AS	 "window_config_save_as"
#define STR_WINDOW_TRACE_BATCH		 "window_trace_batch"
#define STR_WINDOW_LEVEL		 "window_level"

#define STR_WINDOW_CROP_AREA_AND_ROT90	 "window_crop_area_and_rot90"
#define STR_WINDOW_PIXEL_TYPE_AND_BRIGHT "window_pixel_type_and_bright"
#define STR_WINDOW_COLOR_TRACE		 "window_color_trace"
#define STR_WINDOW_EDIT_COLOR		 "window_edit_color"
#define STR_WINDOW_EDIT_HAB_MIN_MAX	 "window_edit_hab_min_max"
#define STR_WINDOW_FNUM_LIST		 "window_fnum_list"

#define STR_WINDOW_NEXT_SCAN		 "window_next_scan"

# ifndef _WIN32
#  define STR_SANE_DEVICE_NAME		 "sane_device_name"
# endif

/*                                        1234567890123456789012345678 */

#define STR_WINDOW_SHOW	"show"
#define STR_WINDOW_HIDE	"hide"

#define STR_DESKTOP_FILENAME	".GTS-desktop"
#define STR_DESKTOP_FILENAME2	"_gts-desktop.txt"
#define STR_DESKTOP_DIR	".GTS"

#include <string>

class memory_desktop {
public:
	int save( void );
	int load( void );
private:
	int _load_by_fp( FILE *fp );
	int _load_by_fname( char *cp_fname );

	int _save_by_fp( FILE *fp );
	int _save_by_fname( const char *cp_fname );
	int _save_startup_path_by_fp( FILE *fp );

	int set_desktop_file_path_( void );
	std::string user_home_;
	std::string desktop_file_path_;
};

void getenv_(const char *name, std::string& dest);
int get_user_home_(std::string& user_home);
std::string gts_file_path(const char *comm, const char *file_name);

#endif /* !__memory_desktop_h__ */
