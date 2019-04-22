#ifndef image_common_plugin_h
#define image_common_plugin_h

#if defined _WIN32
# include <windows.h>
#endif
#include <string>	/* std::string */
#include <vector>

namespace image {
namespace common {
 class plugin {
 public:
	~plugin();

	void add( const std::string& utf8_file_path );

	size_t get_r_instance_size(void);
	void*  get_r_instance(size_t count);
	size_t get_w_instance_size(void);
	void*  get_w_instance(size_t count);

	void close(void);
 private:

	std::vector<std::string> utf8_file_paths_;

#if defined _WIN32
	std::vector<HMODULE> module_handles_;
#else /* unix */
	std::vector<void *> module_handles_;
#endif /* !_WIN32 */

	const char* func_name_reader_ = "get_plugin_instance_reader";
	const char* func_name_writer_ = "get_plugin_instance_writer";

	std::vector<void *> r_instance_handles_;
	std::vector<void *> w_instance_handles_;
 };
} // namespace common
} // namespace image

#endif /* !image_common_plugin_h */
