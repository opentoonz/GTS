#ifndef cb_level_h
#define cb_level_h

#include <vector>
#include <string>

namespace ids {
namespace path {

/* 拡張子管理 */
class extensions {
public:
	extensions();

	/* 名前と拡張子をセット */
	void set_filter(const std::string& name ,const std::string& dotex);

	/* セットした数 */
	const int size(void) { return this->dotex_.size(); }

	/* 位置から拡張子を得る */
	const std::string str_from_num( const int num );

	/* 拡張子から位置を得る */
	const int num_from_str( const std::string& ext );

	/* fltk Nativeウインドウへ渡すための拡張子フィルタ文字列 */
	const std::string get_native_filters( void );

	/* fltk Fl_Choiceに渡すための拡張子フィルタ文字列 */
	const std::string get_fltk_filter( const int num );
private:
	std::vector< std::string >	 names_
					,dotex_;
};

} // path
} // ids

class cb_level {
public:
	cb_level() {}

	ids::path::extensions ext_open;
	ids::path::extensions ext_save;

	void browse_and_set_of_open( void );
	void browse_and_set_of_save( void );

	/* numをマイナスにするとファイル名に番号が付かない */
	const std::string get_openfilename( const int num );
	const std::string get_savefilename( const int num );

	const std::string get_openfilepath( const int num );
	const std::string get_savefilepath( const int num );

	void set_level_open(
		const std::string& dpath
		,const std::string& head
		,const std::string& ext
		,const std::vector<int>& nums
	);
	void set_level_save(
		const std::string& dpath
		,const std::string& head
		,const std::string& ext
		,const std::vector<int>& nums
	);

	void set_number_and_savelevelname( void );
private:
};

#endif /* !cb_level_h */
