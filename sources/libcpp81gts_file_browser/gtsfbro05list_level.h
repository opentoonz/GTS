#ifndef __gtsfbro05list_level_h__
#define __gtsfbro05list_level_h__

#include <string>
#include <FL/Fl_Text_Buffer.H>
#include "gtsfbro04path_level.h"

/* 1dir複数files毎 */
typedef struct st_dir_or_level_info {
	//char	*cp_name;
	char	name[PTBL_PATH_MAX];
	E_DIR_OR_FILE_TYPE e_type;
	int	i_start_num;
	int	i_end_num;
	int	i_count;
	int	i_not_traceing_rgb_count;
} ST_DIR_OR_LEVEL_INFO;

class gtsfbro05list_level : public gtsfbro04path_level {
public:
	gtsfbro05list_level()
	{

		this->_tpp_dirent_sub_list = NULL;
		this->_i_dirent_sub_list_count = 0;

		this->_stp_dir_or_level = NULL;
		this->_i_dir_or_level_alloc = 0;
		this->_i_dir_or_level_used = 0;
	}
	~gtsfbro05list_level()
	{
		this->_end();
	}
	void init_level_dir( const char *ccp_dir );

protected:
	void init_text_buffer( void );
	void text_clear( void );
	void text_add( const char *ccp_text );

	int change_level_list( void );
	void change_level_dir( const char *ccp_dir = NULL );

	char *cp_dir_or_level_name( int num ) const;

	int i_dir_or_level_start( int num ) const;
	int i_dir_or_level_end( int num ) const;
	ST_DIR_OR_LEVEL_INFO *stp_dir_or_level_info( int num ) const;
	ST_DIR_OR_LEVEL_INFO *stp_dir_or_level_search( const char *ccp_name ) const;
	int i_dir_or_level_search( const char *ccp_name ) const;

private:
	dirent	**_tpp_dirent_sub_list;
	int	_i_dirent_sub_list_count;

	ST_DIR_OR_LEVEL_INFO	*_stp_dir_or_level;
	int _i_dir_or_level_alloc;
	int _i_dir_or_level_used;

	Fl_Text_Buffer _cl_fl_text_buffer;

	void _mem_free_level( void );
	int _mem_alloc_level(
	 const char *ccp_gui_main_dir, const char *ccp_gui_sub_dir );
	int _make_dir_or_file_level(
	 const char *ccp_gui_main_dir, const char *ccp_gui_sub_dir );
	void _end( void );
	void _draw_dir_or_file_list( void );

	void add_same_dir_or_level_(
		const int file_start, const int level_tgt
		,const std::string&name
	);
	void _make_dir_or_level( void );
	void _draw_dir_or_level_list( void );
};

#endif /* !__gtsfbro05list_level_h__ */
