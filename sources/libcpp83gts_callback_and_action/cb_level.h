#ifndef cb_level_h
#define cb_level_h

#include <vector>
#include <string>

namespace ids {
namespace path {

class extensions {
public:
	extensions();
	const std::string str_from_num( const int num );
	const int num_from_str( const std::string& ext );
	const std::string get_native_filter( void );

private:
	enum struct count_ { tif ,tga ,size };
	std::vector< std::string >	 names_
					,dotex_;
};

} // path
} // ids

class cb_level {
public:
	cb_level() {}

	void browse_open( void );
	void browse_save( void );

	void set_level_open(
		ids::path::extensions& et
		,const std::string& dpath
		,const std::string& head
		,const std::string& ext
		,const std::vector<int>& nums
	);
	void set_level_save(
		ids::path::extensions& et
		,const std::string& dpath
		,const std::string& head
		,const std::string& ext
		,const std::vector<int>& nums
	);
private:
};

#endif /* !cb_level_h */
