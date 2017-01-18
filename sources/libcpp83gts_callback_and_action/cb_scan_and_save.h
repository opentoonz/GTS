#ifndef cb_scan_and_save_h
#define cb_scan_and_save_h

#include <vector>
#include <string>

class cb_scan_and_save {
public:
	cb_scan_and_save() {}

	ids::path::extensions ext_save;

	void cb_start( void );	/* ScanとSave処理実行 */
	void cb_next( void );	/* 次の処理実行 */
	void cb_rescan( void );	/* 同じ番号で再処理 */

	void cb_browse_save_folder( void );

	/* numをマイナスにするとファイル名に番号が付かない */
	const std::string get_openfilename( const int num );
	const std::string get_openfilepath( const int num );

	const std::string get_save_path_( const int num );
	const std::string get_save_name_( const int num );

	void set_level_open(
		const std::string& dpath
		,const std::string& head
		,const std::string& ext
		,const std::vector<int>& nums
	);

	void set_number_and_savelevelname( void );

	void cb_check_existing_saved_file(void);

	void dialog_rename_at_open(void);  /* (open)連番Fileの名前変更  */
	void dialog_renumber_at_open(void);/* (open)連番Fileの番号Shift */

private:
	int next_scan_and_save_( void );

	bool is_exist_save_files_(void);
	const std::string openfilename_from_level_num_(
		const std::string& open_level ,const int num );
	const std::string openfilepath_from_level_num_(
		const std::string& open_level ,const int num );
};

#endif /* !cb_scan_and_save_h */
