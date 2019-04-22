#ifndef cb_config_h
#define cb_config_h

#include <string>

class cb_config {
public:
	cb_config()
		:ext_(".txt")
		,save_as_set_scan_images_path_sw(false)
	{}

	int loading_and_set_dpath_fname(
		const std::string& fpath
		,const bool load_trace_batch_sw=true
	);
	void open(void);
	void open_only_trace_parameters( void );
	void open_only_area_and_rot90( void );
	void open_only_pixel_type_and_bright( void );
	void open_only_trace_params( void );

	void save_as(void);
	bool save_as_set_scan_images_path_sw;

	void save(void);

	void set_dir_path(const std::string&ss) {
	   this->dir_path_ = ss; }
	void set_open_file_name(const std::string&ss) {
	   this->open_file_name_ = ss; }
	void set_save_file_name(const std::string&ss) {
	   this->save_file_name_ = ss; }

	std::string get_dir_path(void) {
	   return this->dir_path_;}
	std::string get_open_file_name(void) {
	   return this->open_file_name_;}
	std::string get_save_file_name(void) {
	   return this->save_file_name_;}

private:
	std::string	dir_path_
			,open_file_name_ /* Openの時のみ設定する */
			,save_file_name_;/* Open/Save両方で設定する */
	const std::string ext_;

	/*	bool add_ext_if_not_exist_( std::string&fpath );
		だと、VirusTotalのチェックで引っかかる 2019-04-15
	*/
	void add_ext_if_not_exist_( std::string&fpath ,bool& add_sw );
};

#endif /* !cb_config_h */
