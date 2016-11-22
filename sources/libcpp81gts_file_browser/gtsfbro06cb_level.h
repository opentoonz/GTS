#ifndef gtsfbro06cb_level_h
#define gtsfbro06cb_level_h

#include <vector>
#include <string>
#include <time.h>	/* for time_t */
#include "gtsfbro05list_level.h"

class gtsfbro06cb_level : public gtsfbro05list_level {
public:
	gtsfbro06cb_level()
	:saveopen_start_(0.)
	,saveopen_end_(0.)
	{
	}
	/* GUIの状態を記憶する */
	void memory_from_gui( const char* level_dir_path );

	/* 記憶からGUI復元 */
	void memory_to_gui( void );

	int i_init( void );

	void cb_dir( void );
	void cb_dir_up( void );
	void cb_list( void );
	void cb_ok( void );
	void cb_cancel( void );
	void cb_wintgl( void );
	void cb_list_redisplay( void );
	void cb_mkdir( void );
	void cb_rename( void );
	void cb_renumber( void );
	void cb_rgb_scan_dir( void );
	void cb_info_redisplay( void );
	void cb_browse_sw( void );
	void cb_file_or_level( void );

	void cb_level_name( void ); /* add 2013-09-24 */

	void cb_x1view_cancel( void );
	void cb_x1view_wintgl( void );

	char *cp_filepath( int i_number );
	char *cp_filepath_full( int i_number );
	char *filepath_full( int i_number );
	const std::string filepath_open( const int number );

	char *cp_levelname( void );

	void cb_set_save_image_file_extension( void );
	void cb_set_open_image_file_extension( void );

	void level_set(
		const std::vector<int>& num_list
		, const int start_num , const int end_num
	);

protected:
private:
	void _cancel( void );

	int _info_datetimereturn( const time_t *tp_time );
	int _info_image_by_dir_and_file(
		const char *ccp_dir, const char *ccp_file );
	int _info_image_by_dir_and_num(
		const char *ccp_file_for_head, int i_num );

	/* 画像情報を表示する(メンバ関数のオーバーロード(多重定義)) */
	int _list_image_info(
		ST_DIR_OR_FILE_INFO *stp_dir_or_file_info );
	int _list_image_info(
		ST_DIR_OR_LEVEL_INFO *stp_dir_or_level_info );

	int _image_by_dir_and_file(
		const char *ccp_dir, const char *ccp_file );

	int _rename_dir( const char *ccp_subdir, char *cp_new );
	int _rename_file_tif( int i_num, const char *ccp_old, char *cp_new );
	int _rename_level_tif( int i_num, char *cp_new );
	int _rename_level_tif_main(
		int i_num, const char *ccp_old, const char *ccp_new );
	int _rename_level_tif_full(
		int i_num, const char *ccp_old, const char *ccp_new );

	int _renumber_level_tif( int i_num );
	int _renumber_level_tif_main(
		const char *ccp_file, int i_old, int i_new );
	int _renumber_level_tif_full(
		const char *ccp_file, int i_old, int i_new );

	void _select_new_dir_or_file_or_level( const char *ccp_name );
	int _is_valid_string( const char *ccp_name );

	//----------

	/* save_dir_path_はthis->cp_memory() */
	std::string save_file_head_;
	double saveopen_start_;	/* 整数利用だがFl_Inputがdoubleなので */
	double saveopen_end_;	/* 整数利用だがFl_Inputがdoubleなので */
	std::string saveopen_continue_type_;
	std::string save_image_format_;

	std::string open_dir_path_;
	std::string open_file_head_;
	std::string open_image_format_;
};

#endif /* !gtsfbro06cb_level_h */
