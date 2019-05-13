#ifndef cb_scan_and_save_h
#define cb_scan_and_save_h

#include <vector>
#include <string>
#include "ptbl_returncode.h"
#include "ids_path_extensions.h"

class cb_scan_and_save {
public:
	cb_scan_and_save()
	:during_the_scan_is_(false)
	{}

	ids::path::extensions ext_save;

	void cb_start( void );	/* 連番始めの番号から実行開始	*/
	void cb_next( void );	/* 次の番号を実行		*/
	void cb_rescan( void );	/* 同じ番号で再実行		*/
	void cb_save( const bool change_adjustable_sw=false );
				/* 各フレーム毎に保存 */
			/* 各フレーム毎に画像調整したときは引数をtrueに */
	void cb_cancel( void );

	void cb_browse_save_folder( void );
	void cb_set_number( void );
	void cb_check_existing_saved_file( void ); /* Scan typeの時動作 */
	void check_existing_saved_file(void);

	//----------

	const std::string get_save_path( const int number );

	/* numをマイナスにするとファイル名に番号が付かない */
	const std::string get_save_name( const int number );

	//---------- fltk GUI access ----------

	/* End/Endless表示のChoice含めた切替 */
	void cb_choice_and_num_continue_type(const int type);

	/* End/Endless表示のChoice以外の切替 */
	void cb_change_num_continue_type( const int type );

	/* Endlessの方向選択の表示切替 */
	void cb_choice_num_endless_direction( const std::string& type );

	/* 保存するファイル拡張子設定 */
	void cb_choice_save_image_format( const std::string& type );

	/* スイッチの協調ON/OFF */
	void cb_switch_scan_filter_trace( const bool sw );
	void cb_switch_scan_filter_erase_dot_noise( const bool sw );

	/* GUI上の拡張子選択リストの変更
		RGB:.tga,.tif
		Grayscale:(.tga将来追加する),).tif
		BW:.tif
	*/
	void set_gui_ext_list(void);
private:
	bool during_the_scan_is_;

	//int next_scan_and_save_( void );
	bool is_exist_save_files_( void );
	std::string get_save_ext_for_legacy_(const std::string& type);

	const char* cb_start_check_( void );
	std::string cb_scan_fx_display_( int& return_code );
	std::string cb_save_( void );
	void cb_set_next_window_( void );
	void cb_set_next_window_non_modal_( void );
};

#endif /* !cb_scan_and_save_h */
