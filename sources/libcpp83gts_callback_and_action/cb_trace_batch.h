#ifndef cb_trace_batch_h
#define cb_trace_batch_h

#include <vector>
#include <string>

class cb_trace_batch {
public:
	cb_trace_batch() {}

	/* リストの選択したものをtrace batch処理実行 */
	void cb_run( void );
	void cb_add_or_select( void );
	void cb_upper( void );
	void cb_lower( void );
	void cb_delete( void );

	void set_dir_path(const std::string&ss) {
	   this->dir_path_ = ss; }
private:
	std::string	dir_path_;
};

#endif /* !cb_trace_batch_h */
