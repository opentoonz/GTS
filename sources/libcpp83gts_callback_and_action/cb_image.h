#ifndef cb_image_h
#define cb_image_h

#include <string>
#include "ids_path_extensions.h"

class cb_image {
public:
	cb_image()
		:ext_open_filter_current_(0)
		,ext_save_filter_current_(0)
		,save_as_set_scan_images_path_sw(false)
	{}

	ids::path::extensions ext_open;
	ids::path::extensions ext_save;

	void open(void);
	void save_as(void);
	bool save_as_set_scan_images_path_sw;

	void set_dir_path(const std::string&ss) {
	   this->dir_path_ = ss; }
	void set_open_file_name(const std::string&ss) {
	   this->open_file_name_ = ss; }
	void set_save_file_name(const std::string&ss) {
	   this->save_file_name_ = ss; }
	void set_open_image_format( const std::string& ext ) {
		this->ext_open_filter_current_ =
		this->ext_open.num_from_str(ext);
		if (this->ext_open_filter_current_ < 0) {
		    this->ext_open_filter_current_ = 0;
		}
	}
	void set_save_image_format( const std::string& ext ) {
		this->ext_save_filter_current_ =
		this->ext_save.num_from_str(ext);
		if (this->ext_save_filter_current_ < 0) {
		    this->ext_save_filter_current_ = 0;
		}
	}

	const std::string get_dir_path(void) {
	   return this->dir_path_;}
	const std::string get_open_file_name(void) {
	   return this->open_file_name_;}
	const std::string get_save_file_name(void) {
	   return this->save_file_name_;}
	const std::string get_open_image_format(void) { return
		this->ext_open.str_from_num(
		this->ext_open_filter_current_ );
	}
	const std::string get_save_image_format(void) { return
		this->ext_save.str_from_num(
		this->ext_save_filter_current_ );
	}

private:
	std::string	dir_path_
			,open_file_name_ /* Openの時のみ設定する */
			,save_file_name_;/* Open/Save両方で設定する */
	int ext_open_filter_current_;
	int ext_save_filter_current_;

	bool ext_save_is_exist_( std::string& fpath );
};

#endif /* !cb_image_h */
