#ifndef memory_install_setup_h
#define memory_install_setup_h

#include <string>

class memory_install_setup {
public:
	void load( const std::string& exe_file_path );

	std::string browser_top_folder;
	std::string save_number_format;
	std::string image_file_format;
	std::string area_resolution_dpi;
	std::string area_rotate_per_90;
	std::string pixel_type;
	std::string scan_num_endless_direction;
private:
};

#endif /* !memory_install_setup_h */
