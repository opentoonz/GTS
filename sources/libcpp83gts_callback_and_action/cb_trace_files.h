#ifndef cb_trace_files_h
#define cb_trace_files_h

#include <vector>
#include <string>
#include "ids_path_extensions.h"

class cb_trace_files {
public:
	cb_trace_files() {}

	ids::path::extensions ext_open;
	ids::path::extensions ext_save;

	//----------

	int cb_start( const bool interactive_sw=true );
	void cb_browse_for_open( void );

	void cb_set_number( void );
	void cb_check_existing_saved_file(void);

	void browse_and_set_of_save( void );

	//----------

	/* numをマイナスにするとファイル名に番号が付かない */
	const std::string get_open_path( const int num );

	void set_gui_for_open( /* 画像情報をGUIにセットし画像を表示 */
		const std::string& dpath
		,const std::string& head
		,const std::string& num
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


	void dialog_rename_at_open(void);  /* (open)連番Fileの名前変更  */
	void dialog_renumber_at_open(void);/* (open)連番Fileの番号Shift */

private:
	int read_and_save_crnt_( void );

	bool is_exist_save_files_(void);

	const std::string get_open_name_from_head_and_number_(
		const std::string& file_head
		,const int number
	);
	const std::string get_open_name_from_number_( const int num );

	const std::string get_open_path_from_head_and_number_(
		const std::string& file_head
		,const int number
	);
	const std::string get_save_name_( const int num );
	const std::string get_save_path_( const int num );

	void set_number_window_for_open_(
		const std::vector<int>& nums
	);
};

#endif /* !cb_trace_files_h */
