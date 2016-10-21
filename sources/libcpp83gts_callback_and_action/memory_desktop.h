#ifndef memory_desktop_h
#define memory_desktop_h

#include <string>

class memory_desktop {
public:
	memory_desktop()
	:str_desktop_filename_( ".GTS-desktop" )
	,str_desktop_filename2_( "_gts-desktop.txt" )

	,str_show_(
	    "show" )
	,str_hide_(
	    "hide" )

	,str_config_dir_(
	    "config_dir" )

	,str_window_opengl_(
	    "window_main" )
	,str_window_next_scan_(
	    "window_next_scan" )

	,str_window_level_(
	    "window_level" )
	,str_window_level_browse_(
	    "window_level_browse" )
	,str_window_config_load_(
	    "window_config_load" )
	,str_window_config_save_as_(
	    "window_config_save_as" )

	,str_window_crop_area_and_rot90_(
	    "window_crop_area_and_rot90" )
	,str_window_pixel_type_and_bright_(
	    "window_pixel_type_and_bright" )
	,str_window_color_trace_(
	    "window_color_trace" )
	,str_window_fnum_list_(
	    "window_fnum_list" )
	,str_window_trace_batch_(
	    "window_trace_batch" )
	,str_window_thickness_(
	    "window_thickness" )
	,str_window_edit_color_(
	    "window_edit_color" )
	,str_window_edit_hab_min_max_(
	    "window_edit_hab_min_max" )
# ifndef _WIN32
	,str_desktop_dir_( ".GTS" )
	,str_sane_device_name_(
	    "sane_device_name" )
# endif
	{
	}

	int save( void );
	int load( void );

# ifndef _WIN32
	const char* get_install_and_scan_area_and_desktop_dir( void )
	{
		return this->str_desktop_dir_;
	}
# endif

private:
	const char* str_desktop_filename_;
	const char* str_desktop_filename2_;

	const char* str_show_;
	const char* str_hide_;

	const char* str_config_dir_;

	const char* str_window_opengl_;
	const char* str_window_next_scan_;

	const char* str_window_level_;
	const char* str_window_level_browse_;
	const char* str_window_config_load_;
	const char* str_window_config_save_as_;

	const char* str_window_crop_area_and_rot90_;
	const char* str_window_pixel_type_and_bright_;
	const char* str_window_color_trace_;
	const char* str_window_fnum_list_;
	const char* str_window_trace_batch_;
	const char* str_window_thickness_;
	const char* str_window_edit_color_;
	const char* str_window_edit_hab_min_max_;
# ifndef _WIN32
	const char* str_desktop_dir_;
	const char* str_sane_device_name_;
# endif

	int _load_by_fp( FILE *fp );
	int _load_by_fname( char *cp_fname );

	int _save_by_fp( FILE *fp );
	int _save_by_fname( const char *cp_fname );
	int _save_startup_path_by_fp( FILE *fp );

	int set_desktop_file_path_( void );
	std::string user_home_;
	std::string desktop_file_path_;
};

#endif /* !memory_desktop_h */
