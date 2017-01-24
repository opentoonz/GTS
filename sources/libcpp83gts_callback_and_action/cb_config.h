#ifndef cb_config_h
#define cb_config_h

#include <string>

class cb_config {
public:
	cb_config()
		:ext_(".txt")
	{}

	int loading_and_set_dpath_fname(
		const std::string& fpath
		,const bool load_trace_batch_sw=true
	);
	void open(void);
	void save_as(void);
	void save(void);

	void add_ext_if_not_exist( std::string&fpath );

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
};

#endif /* !cb_config_h */
