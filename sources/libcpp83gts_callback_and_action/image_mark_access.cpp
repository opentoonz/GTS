#include <assert.h>	/* assert() */
#include <string.h>
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

/* ファイルパスに対応するファイルのヘッダー情報を得る */
int image_mark_access::_get_file_header_from_path( char *cp_file, iip_read *clp_read )
{
	assert(NULL != cp_file);
	assert(NULL != clp_read);

	/* ファイルが存在しなければ、なにもせず、OKで終る */
	if (!ptbl_dir_or_file_is_exist(cp_file)) {
		return OK;
	}

	/* ファイル名をセットして... */
	if (OK != clp_read->cl_name.set_name(cp_file)) {
		pri_funct_err_bttvr(
 	 "Error : clp_read->cl_name.set_name(%s) returns NG",
			cp_file);
		return NG;
	}
	/* ファイルヘッダー情報を得る */
	if (OK != clp_read->header()) {
		pri_funct_err_bttvr(
 	 "Error : clp_read->header() returns NG");
		return NG;
	}
	return OK;
}

/* ファイル番号に対応する、ファイルのヘッダー情報を得る */
int image_mark_access::_get_file_header_from_num( int i_num, iip_read *clp_read )
{
	char	*cp_path;

	/* ファイル番号に対応するファイルパスを得る */
	/***********if (OK != cl_gts_master.cl_bro_level.i_path_cpy_dir(
		cl_gts_gui.filinp_level_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.i_path_cpy_dir(%s) returns NULL.",
		cl_gts_gui.filinp_level_dir->value()
		);
		return NG;
	}
	if (OK != cl_gts_master.cl_bro_level.i_lpath_cat_file_by_num(
		cl_gts_gui.strinp_level_file->value(),
		i_num,ON
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.i_lpath_cat_file_by_num(%s,%d,%d) returns NULL.",
		cl_gts_gui.strinp_level_file->value(),
		i_num,ON
		);
		return NG;
	}
	cp_path = cl_gts_master.cl_bro_level.cp_path();************/

	cp_path = cl_gts_master.cl_bro_level.cp_filepath(i_num);
	if (NULL == cp_path) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.cp_filepath(%d) returns NULL.",
		i_num
		);
		return NG;
	}

	/* ファイルの情報を取る */
	if (OK != this->_get_file_header_from_path(cp_path, clp_read)) {
		pri_funct_err_bttvr(
 	 "Error : this->_get_file_header_from_path(%s,) returns NG",
			cp_path);
		return NG;
	}
	return OK;
}

/* ファイル番号に対応する、ファイルのヘッダー情報を得る */
int image_mark_access::_get_rgbscan_header_from_num( int i_num, iip_read *clp_read )
{
	char	*cp_path;

	/* rgb scanファイル番号に対応するファイルパスを得る */
	/**********if (OK != cl_gts_master.cl_bro_level.i_path_cpy_dir(
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.i_path_cpy_dir(%s) returns NULL.",
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
		);
		return NG;
	}
	if (OK != cl_gts_master.cl_bro_level.i_lpath_cat_file_for_full(
		cl_gts_gui.strinp_level_file->value(),
		i_num,ON
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.i_lpath_cat_file_for_full(%s,%d,%d) returns NULL.",
		cl_gts_gui.strinp_level_file->value(),
		i_num,ON
		);
		return NG;
	}
	cp_path = cl_gts_master.cl_bro_level.cp_path();**************/

	cp_path = cl_gts_master.cl_bro_level.cp_filepath_full(i_num);
	if (NULL == cp_path) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.cp_filepath_full(%d) returns NULL.",
		i_num
		);
		return NG;
	}
	/* rgb scanファイルの情報を取る */
	if (OK != this->_get_file_header_from_path(cp_path, clp_read)) {
		pri_funct_err_bttvr(
 	 "Error : this->_get_file_header_from_path(%s,) returns NG",
			cp_path);
		return NG;
	}
	return OK;
}

/*--------------------------------------------------------*/

/* ファイルの存在マークを文字列で返す
	マークは、"0001 ST"の、ST部分で、画像の種類毎扱いが違う
	rgbのとき
		S -> Scanファイル("A_full.0001.tif"等)
		T -> Traceファイル("A.0001.tif"等)
	grayscaleのとき
		S -> scanファイル("A.0001.tif")
		T -> 存在しない
	BWのとき
		S -> scanファイル("A.0001.tif")
		T -> 存在しない
*/
char *image_mark_access::get_cp_mark_with_checked( int i_file_num )
{
	iip_read	cl_read_target,
			cl_read_rgbscan;
	char	*cp_s = "S",
		*cp_t = "T",
		*cp_st = "ST";

	/* ファイル番号に対応するファイルヘッダー情報を得る */
	if (OK != this->_get_file_header_from_num(
	i_file_num, &cl_read_target )) {
		pri_funct_err_bttvr(
	 "Error : this->_get_file_header_from_num(-) returns NG" );
		return NULL;
	}

	/* ファイル番号に対応するrgb scanファイルヘッダー情報を得る */
	if (OK != this->_get_rgbscan_header_from_num(
	i_file_num, &cl_read_rgbscan )) {
		pri_funct_err_bttvr(
	 "Error : this->_get_rgbscan_header_from_num(-) returns NG" );
		return NULL;
	}

	/* モノクロ２値画像 */
	if (E_CH_NUM_BITBW ==
	cl_read_target.cl_ch_info.get_e_ch_num_type()) { return cp_s; }

	/* GrayScale画像 */
	else if (1L == cl_read_target.get_l_channels()) { return cp_s; }

	/* RGB Scan and Trace画像 */
	else if ((3L <= cl_read_target.get_l_channels()) &&
		 (3L <= cl_read_rgbscan.get_l_channels())) {return cp_st;}
	/* RGB Scan画像 */
	else if (3L <= cl_read_rgbscan.get_l_channels()) { return cp_s; }
	/* RGB Trace画像 */
	else if (3L <= cl_read_target.get_l_channels()) { return cp_t; }

	/* ファイルがない */
	else if ((0L == cl_read_target.get_l_channels()) &&
		 (0L == cl_read_rgbscan.get_l_channels())) {return NULL;}

	pri_funct_err_bttvr( "Error : bad file type" );
	return NULL;
}

/*--------------------------------------------------------*/

/* ファイル番号を追加し、同時にファイル存在の確認をしてマークする */
void image_mark_access::append_fnum_list_with_chk_mark( int i_file_num )
{
	char *cp_tmp, ca8_tmp[8];

	(void)sprintf(ca8_tmp, "%04d", i_file_num );

	cp_tmp = this->get_cp_mark_with_checked(i_file_num);
	/* ファイルチェックでエラーが起きたとしても実行を続ける */
	if (NULL != cp_tmp) {
		(void)strcat(ca8_tmp, " " );
		(void)strcat(ca8_tmp, cp_tmp );
	}

	cl_gts_gui.selbro_fnum_list->insert(
		cl_gts_gui.selbro_fnum_list->size()+1,
		ca8_tmp
	);

	// GUI Scroll
	cl_gts_gui.selbro_fnum_list->middleline(
		cl_gts_gui.selbro_fnum_list->size()
	);
}

/* 指定のファイル番号の範囲で、リストを設定し
同時にファイル存在の確認をしてマークする */
void image_mark_access::make_fnum_list_with_chk_mark( int i_start, int i_end )
{
	int	ii;
	/* ファイルの存在をチェックしながらリストを設定 */
	for (ii = i_start; ii <= i_end; ++ii) { 
		this->append_fnum_list_with_chk_mark( ii );
	}
}

