#include <stdlib.h>	/* free() */
#include <ctype.h>	/* isdigit() */
#include <string.h>	/* strcmp() */
#include <FL/fl_ask.H>
#include <FL/filename.H> /* fl_filename_list() */
#include "gtsfbro05list_level.h"
#include "gts_gui.h"


void gtsfbro05list_level::init_text_buffer( void )
{
	cl_gts_gui.txtdis_level_info->buffer(
		&(this->_cl_fl_text_buffer) );
}
void gtsfbro05list_level::text_clear( void )
{
	this->_cl_fl_text_buffer.remove(
	0, this->_cl_fl_text_buffer.length() );
}
void gtsfbro05list_level::text_add( const char *ccp_text )
{
	this->_cl_fl_text_buffer.append( ccp_text );
}

/*--------------------------------------------------------*/

char *gtsfbro05list_level::cp_dir_or_level_name( int num ) const
{
	return (num < this->_i_dir_or_level_used)?
		this->_stp_dir_or_level[num].name :NULL;
}
int gtsfbro05list_level::i_dir_or_level_start( int num ) const
{
	return (num < this->_i_dir_or_level_used)?
		this->_stp_dir_or_level[num].i_start_num :0;
}
int gtsfbro05list_level::i_dir_or_level_end( int num ) const
{
	return (num < this->_i_dir_or_level_used)?
		this->_stp_dir_or_level[num].i_end_num :0;
}

ST_DIR_OR_LEVEL_INFO *gtsfbro05list_level::stp_dir_or_level_info( int num ) const
{
	return (num < this->_i_dir_or_level_used)?
		&(this->_stp_dir_or_level[num]) :NULL;
}
ST_DIR_OR_LEVEL_INFO *gtsfbro05list_level::stp_dir_or_level_search( const char *ccp_name ) const
{
	int	ii;
	for (ii = 0; ii < this->_i_dir_or_level_used; ++ii) {
		if (!strcmp(
			//this->_stp_dir_or_level[ii].cp_name
			this->_stp_dir_or_level[ii].name
			,ccp_name
		)) {
			return &(this->_stp_dir_or_level[ii]);
		}
	}
	return NULL;
}
int gtsfbro05list_level::i_dir_or_level_search( const char *ccp_name ) const
{
	int	ii;
	for (ii = 0; ii < this->_i_dir_or_level_used; ++ii) {
		if (!strcmp(
			//this->_stp_dir_or_level[ii].cp_name,ccp_name
			this->_stp_dir_or_level[ii].name
			,ccp_name
		)) {
			return ii;
		}
	}
	return -1;
}

/*--------------------------------------------------------*/

void gtsfbro05list_level::_mem_free_level( void )
{
	int	ii;

	/* alloc No,3  3:連番用メモリ確保(Up Dir分一つ多く) */
	if (NULL !=  this->_stp_dir_or_level) {
		free(this->_stp_dir_or_level);
		     this->_stp_dir_or_level = NULL;
		this->_i_dir_or_level_alloc = 0;
		this->_i_dir_or_level_used = 0;
	}

	/* alloc No,2  main_dirのlist作成とdir_or_fileメモリの確保 */
	this->mem_free();

	/* alloc No,1  sub_dirのlist作成 */
	if (NULL !=		this->_tpp_dirent_sub_list) {
		for (ii =	  this->_i_dirent_sub_list_count;0<ii;){
			free(	this->_tpp_dirent_sub_list[--ii]);
		}
		free(		this->_tpp_dirent_sub_list);
				this->_tpp_dirent_sub_list = NULL;
				  this->_i_dirent_sub_list_count = 0;
	}
}

int gtsfbro05list_level::_mem_alloc_level( const char *ccp_gui_main_dir, const char *ccp_gui_sub_dir )
{
	/* alloc No,1  sub_dirのlist作成 */
	if (
		/* sub_dirに文字列があり... */
		(NULL != ccp_gui_sub_dir) &&
		('\0' != ccp_gui_sub_dir[0])
		/* sub_dirがmain_dirと同じ場所でも見る */
	) {
		if (OK != this->i_path_cpy_dir( ccp_gui_sub_dir )) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_cpy_dir(%s) returns NG",
				ccp_gui_sub_dir );
			return NG;
		}
		this->_i_dirent_sub_list_count = fl_filename_list(
			this->cp_path(), &(this->_tpp_dirent_sub_list));
		if (this->_i_dirent_sub_list_count <= 0) {
			pri_funct_err_bttvr(
		 "Error : fl_filename_list(%s,) returns %d",
				this->cp_path(),
				this->_i_dirent_sub_list_count
			);
			this->_tpp_dirent_sub_list = NULL;
			this->_i_dirent_sub_list_count = 0;
			return NG;
		}
	}

 // this->debug_print_dirent_( "filelist_sub" ,this->_i_dirent_sub_list_count ,this->_tpp_dirent_sub_list );

	/* alloc No,2  main_dirのlist作成とdir_or_fileメモリの確保 */
	if (OK != this->i_path_cpy_dir( ccp_gui_main_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
			ccp_gui_main_dir );
		return NG;
	}
	if (OK != this->mem_alloc( this->_i_dirent_sub_list_count )) {
		pri_funct_err_bttvr(
	 "Error : this->mem_alloc(%d) returns NG",
			this->_i_dirent_sub_list_count );
		return NG;
	}

 // this->debug_print_dirent( "filelist_main" );

	/* alloc No,3  3:連番用メモリ確保(Up Dir分一つ多く) */
	this->_i_dir_or_level_alloc = this->i_dirent_list_count()+
				 this->_i_dirent_sub_list_count + 1;
	if (0 < this->_i_dir_or_level_alloc) {
		this->_stp_dir_or_level =(ST_DIR_OR_LEVEL_INFO *)calloc(
			this->_i_dir_or_level_alloc,
			sizeof(ST_DIR_OR_LEVEL_INFO)
		);
		if (NULL == this->_stp_dir_or_level) {
			pri_funct_err_bttvr(
				"Error : calloc(%d,%d) returns NULL",
			this->_i_dir_or_level_alloc,
			sizeof(ST_DIR_OR_LEVEL_INFO)
			);
			this->_i_dir_or_level_alloc = 0;
			return NG;
		}
	}
	return OK;
}

int gtsfbro05list_level::_make_dir_or_file_level( const char *ccp_gui_main_dir, const char *ccp_gui_sub_dir )
{
	ST_DIR_OR_FILE_INFO *stp_fil;
	int ii;
	char *cp_name;
	E_DIR_OR_FILE_TYPE e_type, e_1st_main_type, e_1st_sub_type;

	if (OK != this->i_path_cpy_dir( ccp_gui_main_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG",
			ccp_gui_main_dir );
		return NG;
	}

	if (0 == cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
		e_1st_main_type = E_DIR_OR_FILE_IS_DIR;
		e_1st_sub_type = E_DIR_OR_FILE_IS_NOTHING;
	} else {
		e_1st_main_type = E_DIR_OR_FILE_IS_NOTHING;
		e_1st_sub_type = E_DIR_OR_FILE_IS_DIR;
	}

	this->make_dir_or_file(
		e_1st_main_type,
		E_DIR_OR_FILE_IS_NUM_IMAGE );

 // this->debug_print_dir_or_file( "list_main" );

	if (
		/* sub_dirに文字列がある */
		(NULL != ccp_gui_sub_dir) &&
		('\0' != ccp_gui_sub_dir[0])
		/* sub_dirがmain_dirと同じ場所でも見る */
	) {
		if (OK != this->i_path_cpy_dir( ccp_gui_sub_dir )) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_cpy_dir(%s) returns NG",
				ccp_gui_sub_dir );
			return NG;
		}
		stp_fil = this->stp_dir_or_file();
		stp_fil += this->i_dir_or_file_used();
		for (ii= 0; ii < this->_i_dirent_sub_list_count; ++ii) {
			cp_name =this->_tpp_dirent_sub_list[ii]->d_name;
			e_type = this->e_dir_or_file_type( cp_name );

			if (
			(e_1st_sub_type == e_type) ||
			(E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE
			== e_type)
			) {
				stp_fil->cp_name = cp_name;
				stp_fil->e_type = e_type;
				stp_fil->is_chk = OFF; /* 初期化 */
				this->incr_i_dir_or_file_used();
				++stp_fil;
			}
		}
	}
 // this->debug_print_dir_or_file( "list_main_with_sub" );
	return OK;
}

void gtsfbro05list_level::_end( void )
{
	this->remove_gui_list( cl_gts_gui.selbro_level_list );
	this->_mem_free_level();
}

/*--------------------------------------------------------*/

int gtsfbro05list_level::change_level_list( void )
{
	const char *ccp_gui_main_dir;
	const char *ccp_gui_sub_dir;
	const char *ccp_dir;
	char ca_msg[PTBL_PATH_MAX];

	ccp_gui_main_dir= cl_gts_gui.filinp_level_dir->value();
	ccp_gui_sub_dir = cl_gts_gui.filinp_level_rgb_scan_dir->value();

	if (0 == cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
		ccp_dir = ccp_gui_main_dir;;
	} else {
		ccp_dir = ccp_gui_sub_dir;;
	}

	/* dirが存在しない(nullパス("")は有効とする)
	ときはlist更新せず、Dialog表示して注意する */
	if (	(NULL == ccp_dir) ||
		(	('\0' != ccp_dir[0]) &&
			!fl_filename_isdir( ccp_dir )
		)
	) {
		pri_funct_err_bttvr(
			"Error : dir path(%s) is not exist",
			ccp_dir );
		if (NULL == ccp_dir) {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"Dir path\n is not exist!");
		} else {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"%s\n is not exist!",ccp_dir);
		}
		fl_alert(ca_msg);
		return OK;
	}

	/* テキスト情報を消す */
	this->text_clear();

	/* 画像を非表示する */
	cl_gts_gui.box_level_image->hide();
	cl_gts_gui.box_level_x1view->hide();

	/* リストメモリの消去 */
	this->_end();

	/* リストメモリの確保 */
	if (OK != this->_mem_alloc_level(
		ccp_gui_main_dir,ccp_gui_sub_dir
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_mem_alloc_level(%s,%s) returns NG",
		ccp_gui_main_dir,ccp_gui_sub_dir );
		return NG;
	}

	/* Fileリストデータの作成 */
	if (OK != this->_make_dir_or_file_level(
		ccp_gui_main_dir,ccp_gui_sub_dir
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_make_dir_or_file_level(%s,%s) returns NG",
		ccp_gui_main_dir,ccp_gui_sub_dir );
		return NG;
	}

	if (0 == cl_gts_gui.choice_level_list_form->value()) {
		/* Levelリストデータの作成 */
		/* add 2013-09-24 表示のあと!、Level名との照会のため生成*/
		this->_make_dir_or_level();

 // this->debug_print_dir_or_file( "File.tif" );

		/* "File.tif"リストの表示 */
		this->draw_gui_list( cl_gts_gui.selbro_level_list );

	} else {
		/* Levelリストデータの作成 */
		this->_make_dir_or_level();

 // this->debug_print_dir_or_file( "Level.tif" );

		/* "Level.tif"リストの表示 */
		this->_draw_dir_or_level_list();
	}

	return OK;
}

/* levelディレクトリのlistクリックによる移動、あるいはmkdirで使う */
void gtsfbro05list_level::change_level_dir( const char *ccp_dir )
{
	char *cp_gui_dir;

	if (NULL == ccp_dir) {
		cp_gui_dir = this->cp_path();
	} else {
		cp_gui_dir = (char *)ccp_dir;
	}

	if (0 == cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
	 cl_gts_gui.filinp_level_dir->value(cp_gui_dir);
	 cl_gts_gui.filinp_level_dir->position(strlen(cp_gui_dir));
	}
	cl_gts_gui.filinp_level_rgb_scan_dir->value(cp_gui_dir);
	cl_gts_gui.filinp_level_rgb_scan_dir->position(
		strlen(cp_gui_dir)
	);
}

/* configディレクトリのconfigファイル読み込みによる設定で使う... */
void gtsfbro05list_level::init_level_dir( const char *ccp_dir )
{
	cl_gts_gui.filinp_level_dir->value(ccp_dir);
	cl_gts_gui.filinp_level_dir->position(strlen(ccp_dir));
	this->v_path_memory(ccp_dir);
}
