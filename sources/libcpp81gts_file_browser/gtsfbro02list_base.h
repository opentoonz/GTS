#ifndef __gtsfbro02list_base_h__
#define __gtsfbro02list_base_h__

typedef enum {
	E_DIR_OR_FILE_IS_PIRIOD = 1,
	E_DIR_OR_FILE_IS_DIR,
	E_DIR_OR_FILE_IS_TEXT,
	E_DIR_OR_FILE_IS_NUM_IMAGE,
	E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE,
	E_DIR_OR_FILE_IS_OTHER,  /* 他の種類のdir or file */
	E_DIR_OR_FILE_IS_NOTHING /* 何にも該当しない */
} E_DIR_OR_FILE_TYPE;

/* 1dir1file毎 */
typedef struct st_dir_or_file_info {
	char	*cp_name;
	E_DIR_OR_FILE_TYPE	e_type;
	int	is_chk;
} ST_DIR_OR_FILE_INFO;

#include <FL/filename.H>	/* dirent */
#include "gtsfbro01path_base.h"

class gtsfbro02list_base : public gtsfbro01path_base {
public:
	gtsfbro02list_base() :
		/* 静的でないconstメンバ変数の初期化 */
		_ccp_text_file_ext(".txt"),
		/*** _ccp_image_file_ext(".tif"), ***/
		_ccp_dir_mark("<Dir>   "),
		_ccp_mark_not_tracing_rgb("_full")
	{
		this->_tpp_dirent_list = NULL;
		this->_i_dirent_list_count = 0;
		this->_stp_dir_or_file = NULL;
		this->_i_dir_or_file_used = 0;
	}
	~gtsfbro02list_base()
	{
		this->mem_free();
	}
protected:
	const char *ccp_text_file_ext( void ) const
	{ return this->_ccp_text_file_ext; }
	/*** const char *ccp_image_file_ext( void ) const
	{ return this->_ccp_image_file_ext; } ***/
	const char *ccp_dir_mark( void ) const
	{ return this->_ccp_dir_mark; }
	const char *ccp_mark_not_tracing_rgb( void ) const
	{ return this->_ccp_mark_not_tracing_rgb; }

	int		i_dirent_list_count( void ) const
	{ return this->_i_dirent_list_count; }
	ST_DIR_OR_FILE_INFO *stp_dir_or_file( void ) const
	{ return      this->_stp_dir_or_file; }
	int		i_dir_or_file_used( void ) const
	{ return this->_i_dir_or_file_used; }
	void   incr_i_dir_or_file_used( void )
	{ ++ this->_i_dir_or_file_used; }

	E_DIR_OR_FILE_TYPE e_dir_or_file_type( char *cp_fname );
	void mem_free( void );
	int mem_alloc( int i_additional_alloc );
	void make_dir_or_file( E_DIR_OR_FILE_TYPE e_1st_type, E_DIR_OR_FILE_TYPE e_2nd_type );

	ST_DIR_OR_FILE_INFO *stp_dir_or_file_info( int num ) const;
	ST_DIR_OR_FILE_INFO *stp_dir_or_file_search( const char *ccp_name ) const;
	int i_dir_or_file_search( const char *ccp_name ) const;

	void debug_print_dirent_(
		const char *title ,int count ,dirent **list
	);
	void debug_print_dirent( const char *title );
	void debug_print_dir_or_file( const char *title );

private:
	const char *_ccp_text_file_ext;
	/*** const char *_ccp_image_file_ext; ***/
	const char *_ccp_dir_mark;
	const char *_ccp_mark_not_tracing_rgb;

	dirent **_tpp_dirent_list;
	int _i_dirent_list_count;
	ST_DIR_OR_FILE_INFO *_stp_dir_or_file;
	int _i_dir_or_file_used;
};

#endif /* !__gtsfbro02list_base_h__ */
