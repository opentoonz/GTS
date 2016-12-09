#ifndef memory_install_setup_h
#define memory_install_setup_h

#include <string>

class memory_install_setup {
public:
	void load( const std::string& exe_file_path );

	std::string browser_directory_path;
	std::string image_file_format;
private:
};

#endif /* !memory_install_setup_h */
