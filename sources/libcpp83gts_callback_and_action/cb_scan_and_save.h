#ifndef cb_level_h
#define cb_level_h

#include <vector>
#include <string>

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

	void check_save_level_by_existing_file(void);

	void dialog_rename_at_open(void);  /* (open)連番Fileの名前変更  */
	void dialog_renumber_at_open(void);/* (open)連番Fileの番号Shift */

	void display_tab_to_level_open( void ); /* openのtabに表示を切替 */

private:
	bool is_exist_save_files_(void);
	const std::string openfilename_from_level_num_(
		const std::string& open_level ,const int num );
	const std::string openfilepath_from_level_num_(
		const std::string& open_level ,const int num );
};

#endif /* !cb_level_h */
