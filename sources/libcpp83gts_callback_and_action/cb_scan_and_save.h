#ifndef cb_scan_and_save_h
#define cb_scan_and_save_h

#include <vector>
#include <string>
#include "ptbl_returncode.h"
#include "ids_path_extensions.h"

class cb_scan_and_save {
public:
	cb_scan_and_save()
	:prev_scan_action_is_(OK)
	{}

	ids::path::extensions ext_save;

	void cb_start( void );	/* ScanとSave処理実行 */
	void cb_next( void );	/* 次の処理実行 */
	void cb_rescan( void );	/* 同じ番号で再処理 */
	void cb_browse_save_folder( void );
	void cb_set_number( void );
	void cb_check_existing_saved_file( void ); /* Scan typeの時動作 */
	void check_existing_saved_file(void);

	//----------

	const std::string get_save_path( const int number );

	//---------- fltk GUI access ----------

	/* End/Endless表示のChoice含めた切替 */
	void cb_choice_and_num_continue_type(const std::string& type);

	/* End/Endless表示のChoice以外の切替 */
	void cb_change_num_continue_type( const std::string& type );

	/* Endlessの方向選択の表示切替 */
	void cb_choice_num_endless_direction( const std::string& type );

	/* 保存するファイル拡張子設定 */
	void cb_choice_save_image_format( const std::string& type );

	/* スイッチの協調ON/OFF */
	void cb_switch_scan_filter_trace( const bool sw );
	void cb_switch_scan_filter_erase_dot_noise( const bool sw );

private:
	int prev_scan_action_is_;

	int next_scan_and_save_( void );

	bool is_exist_save_files_( void );

	/* numをマイナスにするとファイル名に番号が付かない */
	const std::string get_save_name_( const int number );

	std::string get_save_ext_for_legacy_(const std::string& type);
};

#endif /* !cb_scan_and_save_h */
