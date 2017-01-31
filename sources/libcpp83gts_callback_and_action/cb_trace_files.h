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

	int cb_start( const bool interactive_sw=true ); /* 二値化処理実行 */
	void cb_rename(void);	/* open_pathで連番Fileの名前変更  */
	void cb_renumber(void);	/* open_pathで連番Fileの番号Shift */

	void cb_browse_open_file(void);  /* ブラウザでファイル選択し設定 */
	void set_gui_for_open( /* 画像情報をGUIにセットし画像を表示 */
		const std::string& dpath
		,const std::string& head
		,const std::string& num
		,const std::string& ext
		,const std::vector<int>& nums
	);
	void cb_browse_save_folder(void);/* ブラウザでフォルダ選択し設定 */

	void cb_set_number( void );

	void cb_check_existing_saved_file(void); /* Trace Typeの時動作 */
	void check_existing_saved_file(void);

	/* 開くファイル拡張子設定 */
	void cb_choice_open_image_format( const std::string& type );

	/* 保存するファイル拡張子設定 */
	void cb_choice_save_image_format( const std::string& type );

	//----------

	/* numマイナスでファイル名に番号付かない */
	const std::string get_open_path( const int num );
	const std::string get_save_path( const int num );

	void cb_switch_trace_filter_erase_dot_noise( const bool sw );

private:
	int read_and_save_crnt_(
		const int crnt_file_num
		,const int crnt_list_num
	);

	void set_number_window_( const std::vector<int>& nums );

	bool is_exist_save_files_(void);

	const std::string get_open_name_from_number_( const int num );
	const std::string get_open_name_from_head_and_number_(
		const std::string& file_head
		,const int number
	);

	const std::string get_open_path_from_head_and_number_(
		const std::string& file_head
		,const int number
	);
	const std::string get_save_name_( const int num );
	std::string get_open_ext_for_legacy_(const std::string& type);
	std::string get_save_ext_for_legacy_(const std::string& type);
};

#endif /* !cb_trace_files_h */
