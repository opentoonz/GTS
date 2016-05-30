#include "gtsfbro04path_level.h"

/*--------------------------------------------------------*/

int gtsfbro04path_level::i_lpath_cat_file_by_num( const char *ccp_file, int i_num, int i_file_head_cut_sw )
{
	if ( (NULL == ccp_file) || ('\0' == ccp_file[0]) ) {
		pri_funct_err_bttvr("Error : ccp_file is nothing.");
		return NG;
	}

	if (OK != this->i_path_cat_head(ccp_file,i_file_head_cut_sw)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_head(%s,%d) returns NULL.",
	 		ccp_file,i_file_head_cut_sw );
		return NG;
	}

	if (OK != this->i_path_cat_pad4( i_num )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_pad4(%d) returns NULL.",
			i_num
		);
		return NG;
	}

	if (OK != this->i_path_cat_part( this->get_imagefile_extension() )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_part(%s) returns NULL.",
			this->get_imagefile_extension()
		);
		return NG;
	}

	return OK;
}

int gtsfbro04path_level::i_lpath_cat_file_for_full( const char *ccp_file, int i_num, int i_file_head_cut_sw )
{
	if ( (NULL == ccp_file) || ('\0' == ccp_file[0]) ) {
		pri_funct_err_bttvr("Error : ccp_file is nothing.");
		return NG;
	}

	if (OK != this->i_path_cat_head(ccp_file,i_file_head_cut_sw)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_head(%s,%d) returns NULL.",
	 		ccp_file,i_file_head_cut_sw );
		return NG;
	}

	if (OK != this->i_path_cat_part(
			this->ccp_mark_not_tracing_rgb()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_part(%s) returns NULL.",
			this->ccp_mark_not_tracing_rgb()
		);
		return NG;
	}

	if (OK != this->i_path_cat_pad4( i_num )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_pad4(%d) returns NULL.",
			i_num
		);
		return NG;
	}

	if (OK != this->i_path_cat_part( this->get_imagefile_extension() )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_part(%s) returns NULL.",
			this->get_imagefile_extension()
		);
		return NG;
	}


	return OK;
}

/* ファイル名からその頭名を、ドーンと置く
	level名をWindowのtitleへ表示するのに使う
*/
int gtsfbro04path_level::i_lpath_cpy_head_means_level( const char *ccp_file, int i_file_head_cut_sw )
{
	/* このクラスのinstanceメモリを使う */
	/* コピーなので初期化しとく */
	this->v_path_dir_part_zero();
	this->v_path_dir_part_cutting();

	return this->i_path_cat_head( ccp_file, i_file_head_cut_sw );
}
