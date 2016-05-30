#include <stdlib.h> /* calloc(),free() */
#include <string.h>
#include <ctype.h> /* isdigit() */
#include <FL/filename.H> /* fl_filename_isdir() */
#include "gtsfbro02list_base.h"

ST_DIR_OR_FILE_INFO *gtsfbro02list_base::stp_dir_or_file_search( const char *ccp_name ) const
{
	int	ii;
	for (ii = 0; ii < this->_i_dir_or_file_used; ++ii) {
		if (!strcmp(
			this->_stp_dir_or_file[ii].cp_name,ccp_name
		)) {
			return &(this->_stp_dir_or_file[ii]);
		}
	}
	return NULL;
}
int gtsfbro02list_base::i_dir_or_file_search( const char *ccp_name ) const
{
	int	ii;
	for (ii = 0; ii < this->_i_dir_or_file_used; ++ii) {
		if (!strcmp(
			this->_stp_dir_or_file[ii].cp_name,ccp_name
		)) {
			return ii;
		}
	}
	return -1;
}

ST_DIR_OR_FILE_INFO *gtsfbro02list_base::stp_dir_or_file_info( int num ) const
{
	return (num < this->_i_dir_or_file_used)?
		&(this->_stp_dir_or_file[num]) :NULL;
}

/* -------------------------------------------------------- */
/* dirpathは"int i_path_cpy_dir(const char *ccp)"で設定してあること */
/* MS-Windowsでのfl_filename_list()は
	ディレクトリの場合の名前の最後が'/'で終るので、
	削除する
*/
E_DIR_OR_FILE_TYPE gtsfbro02list_base::e_dir_or_file_type( char *cp_file )
{
	size_t	t_len;

	/* ピリオドで始まるFile or Directory名(表示しない) -----------
		カレントディレクトリ	"./"
		上のディレクトリ	"../"
		隠しファイル		".*"
	*/
	if ('.' == cp_file[0])
	{ return E_DIR_OR_FILE_IS_PIRIOD; }

	/* ディレクトリ ----------------------------------------------
		MS-Windows
			fl_filename_list()による名前の最後が'/'で終る
		Linux
			fl_filename_isdir(this->cp_path() + cp_file)
			でチェックしパスはリセット
	*/
	t_len = strlen(cp_file);
#if defined _WIN32
	/* MS-Windowsでのfl_filename_list()は
	ディレクトリの場合の名前の最後が'/'で終る */
	if ( (0 < t_len) && ('/'  == cp_file[t_len-1]) ) {
		cp_file[t_len-1] = '\0'; /* 最後の'/'を削除 */
		return E_DIR_OR_FILE_IS_DIR;
	}
#else
	if (OK == this->i_path_cat_part( cp_file )) {
		if (fl_filename_isdir(this->cp_path())) {
			this->v_path_dir_part_cutting();
			return E_DIR_OR_FILE_IS_DIR;
		}
		this->v_path_dir_part_cutting();
	}
#endif

	/* 拡張子がthis->ccp_text_file_ext()(=".txt)であるファイル ---
		43210987654321
		scanner001.txt
	*/
	if (	(4 <= t_len) &&
		(0 == strcmp(	this->ccp_text_file_ext(),
				&(cp_file[t_len-4]) ))
	) {
		return E_DIR_OR_FILE_IS_TEXT;
	}

	/* 拡張子がthis->get_imagefile_extension()(=".tif")であり ---------
		かつ
	   番号がある(".0000")
		A.0001.tif" or "A_full.0001.tif" or ...
	*/
	if (NULL != this->ccp_num4_and_ext(cp_file)) {
		size_t t_full_sz;

		/* "_full"が決まった位置にある
			A_full.0001.tif ...

			A		--> 1
			 _full		--> t_full_sz
			      .0001.tif --> 9
					    1+t_full_sz+9(最小の文字数)
		*/
		t_full_sz = strlen( this->ccp_mark_not_tracing_rgb() );
		if (	((1+t_full_sz+9) <= t_len) &&
			!strncmp(
				this->ccp_mark_not_tracing_rgb(),
				cp_file+(t_len-t_full_sz-9),
				t_full_sz
			)
		) {
			return E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE;
		}
		/* "_full"が付いてない
			A.0001.tif ...
		*/
		return E_DIR_OR_FILE_IS_NUM_IMAGE;
	}

	return E_DIR_OR_FILE_IS_OTHER;
}

void gtsfbro02list_base::mem_free( void )
{
	int	ii;

	if (NULL !=  this->_stp_dir_or_file) {
		free(this->_stp_dir_or_file);
		     this->_stp_dir_or_file = NULL;
		this->_i_dir_or_file_used = 0;
	}
	if (NULL !=		this->_tpp_dirent_list) {
		for (ii =	  this->_i_dirent_list_count; 0<ii;) {
			free(	this->_tpp_dirent_list[--ii]);
		}
		free(		this->_tpp_dirent_list);
				this->_tpp_dirent_list = NULL;
				  this->_i_dirent_list_count = 0;
	}
}

/* dirpathは"int i_path_cpy_dir(const char *ccp)"で設定してあること */
int gtsfbro02list_base::mem_alloc( int i_additional_alloc )
{
	int i_nmemb;

	/* ゾンビメモリを作らないための安全策 */
	this->mem_free();

	/* dir listの作成 */
	/* Windowsでは
		this->cp_path()のパスの最後にスラッシュ'/'が必要
		各リストは../が始めに来て、./が２番目に来る
		リストのDir名には"/"が付く
	*/
	this->_i_dirent_list_count = fl_filename_list( this->cp_path(),
	&(this->_tpp_dirent_list) );
	if (this->_i_dirent_list_count <= 0) {
		pri_funct_err_bttvr(
			"Error : fl_filename_list(%s,) returns %d",
			this->cp_path(),
			this->_i_dirent_list_count
		);
		this->_tpp_dirent_list = NULL;
		this->_i_dirent_list_count = 0;
		return NG;
	}

	/* リストメモリ確保 (Up Dir分一つ多く) */
	i_nmemb = this->_i_dirent_list_count + i_additional_alloc + 1;
	if (0 < i_nmemb) {
		this->_stp_dir_or_file = (ST_DIR_OR_FILE_INFO *)calloc(
			i_nmemb, sizeof(ST_DIR_OR_FILE_INFO)
		);
		// this->_i_dir_or_file_used = 0;
		if (NULL == this->_stp_dir_or_file) {
			pri_funct_err_bttvr(
				"Error : calloc(%d,%d) returns NULL",
			i_nmemb, sizeof(ST_DIR_OR_FILE_INFO)
			);
			return NG;
		}
	}
	return OK;
}

/*
 e_1st_type is E_DIR_OR_FILE_IS_DIR or E_DIR_OR_FILE_IS_NOTHING
 e_2nd_type is E_DIR_OR_FILE_IS_NUM_IMAGE or E_DIR_OR_FILE_IS_TEXT
 dirpathは"int i_path_cpy_dir(const char *ccp)"で設定してあること
*/
void gtsfbro02list_base::make_dir_or_file( E_DIR_OR_FILE_TYPE e_1st_type, E_DIR_OR_FILE_TYPE e_2nd_type )
{
	ST_DIR_OR_FILE_INFO *stp_fil;
	int ii;
	char *cp_name;
	E_DIR_OR_FILE_TYPE e_type;

	if (NULL == this->_stp_dir_or_file) { return; }

	/* Up Dir これは先頭に必ずいれる */
	// this->_i_dir_or_file_used = 0;
	stp_fil = this->_stp_dir_or_file;
	stp_fil->cp_name = "..";
	stp_fil->e_type = E_DIR_OR_FILE_IS_DIR;
	stp_fil->is_chk = OFF; /* 初期化 */
	++ this->_i_dir_or_file_used;
	++ stp_fil;

	/* dir or fileのチェックをしながら、listを作る */
	for (ii = 0; ii < this->_i_dirent_list_count; ++ii) {
		cp_name = this->_tpp_dirent_list[ii]->d_name;

		/* this->cp_path()内のd_nameファイルの種別を得る */
		e_type = this->e_dir_or_file_type( cp_name );

		if (	(e_1st_type == e_type) ||
			(e_2nd_type  == e_type)
		) {
			stp_fil->cp_name = cp_name;
			stp_fil->e_type = e_type;
			stp_fil->is_chk = OFF; /* 初期化 */
			++ this->_i_dir_or_file_used;
			++ stp_fil;
		}
	}
}
// add 2013-10-07
#include <iostream>
void gtsfbro02list_base::debug_print_dirent_(
	const char *title ,int count ,dirent **list
) {
  	std::cout << "--- dir_list --- " << title << " ---" << std::endl;
	for (int ii= 0; ii < count; ++ii) {
  		std::cout << ii+1 << "/" << count
			<< " name=\"" << list[ii]->d_name << "\""
			<< std::endl;
	}
}
void gtsfbro02list_base::debug_print_dirent( const char *title ) {
	this->debug_print_dirent_(
		title ,this->_i_dirent_list_count ,this->_tpp_dirent_list );
}
void gtsfbro02list_base::debug_print_dir_or_file( const char *title ) {
	std::cout << "=== dir_or_file === " << title << " ===" << std::endl;
	for (int ii= 0; ii < this->_i_dir_or_file_used; ++ii) {
  		std::cout << ii+1 << "/" << this->_i_dir_or_file_used
		<< " type="   << this->_stp_dir_or_file[ii].e_type
		<< " name=\"" << this->_stp_dir_or_file[ii].cp_name << "\""
		<< std::endl;
	}
}
