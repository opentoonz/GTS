#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

/*
BW画,Grayscale画,RGBTrace画(結果画像)
で使用するノーマルな名前(/dir_crnt_path/A.0001.tif)
*/
char *gtsfbro06cb_level::cp_filepath( int i_number )
{
	if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_level_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG.",
		cl_gts_gui.filinp_level_dir->value()
		);
		return NULL;
	}
	if (OK != this->i_lpath_cat_file_by_num(
		cl_gts_gui.strinp_level_file->value(), i_number,ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_by_num(%s,%d,%d) returns NG.",
		cl_gts_gui.strinp_level_file->value(), i_number,ON
		);
		return NULL;
	}
	return this->cp_path();
}
/*
RGBScan画(中間画像)
の専用の名前(/dir_full_path/A_full.0001.tif)
*/
char *gtsfbro06cb_level::cp_filepath_full( int i_number )
{
	if (OK != this->i_path_cpy_dir(
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG.",
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
		);
		return NULL;
	}
	if (OK != this->i_lpath_cat_file_for_full(
		cl_gts_gui.strinp_level_file->value(), i_number,ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_for_full(%s,%d,%d) returns NG.",
		cl_gts_gui.strinp_level_file->value(), i_number,ON
		);
		return NULL;
	}
	return this->cp_path();
}

/*
level名
levelブラウザーのlevel名の項目からとって来る
*/
char *gtsfbro06cb_level::cp_levelname( void )
{
	if (OK != this->i_lpath_cpy_head_means_level(
		cl_gts_gui.strinp_level_file->value(),ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_lpath_cpy_head_means_level(%s,%d) returns NG",
		cl_gts_gui.strinp_level_file->value(),ON
		);
		return NULL;
	}

	return this->cp_path();
}
