#include <limits.h> /* CHAR_BIT */
#include <assert.h> /* assert() */
#include <string.h> /* strcmp() */

#include "pri.h"

#include "tif_image_rw.h"
#include "tga_image_rw.h"

#include "iip_write.h"

int iip_write::file( void )
{
	char	*cp_ext;

	/* ファイルパスの設定はしておかなければならない */
	assert( NULL != this->cl_name.get_cp_name() );

	/* 拡張子を得る */
	cp_ext = strrchr( this->cl_name.get_cp_name(), (int)'.' );
	if (NULL == cp_ext) {
		pri_funct_err_bttvr(
			"Error : %s has not extention.",
			this->cl_name.get_cp_name() );
		return NG;
	}

	/* ".rgb" --> "rgb" */
	++cp_ext;

	/* TIFF画像 */
	if ( !strcmp( "tif", cp_ext )
	||        !strcmp( "TIF", cp_ext ) ) {
		if (OK != tif_image_write(
			this->get_vp_canvas(),
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			this->cl_ch_info.get_l_bytes(),
			this->cl_ch_info.get_l_bits(),
			this->_d_tif_dpi_x,
			this->_d_tif_dpi_y,
			this->_l_tif_compression,
			this->_l_tif_lzw_prediction_scheme,
			this->_l_tif_orientation,
			this->_l_tif_byte_swap_mode,
			this->cl_name.get_cp_name(),
			this->get_i_mv_sw(),
			this->get_i_pv_sw(),
			this->get_i_cv_sw()
		)) {
			pri_funct_err_bttvr(
			"Error : tif_image_write(-) returns NG." );
			return NG;
		}
	}
	/* Targa画像 */
	else if ( !strcmp( "tga", cp_ext )
	||        !strcmp( "TGA", cp_ext ) ) {
		if (OK != tga_image_write(
			this->get_vp_canvas(),
			this->get_l_width(),
			this->get_l_height(),
			this->get_l_channels(),
			this->cl_ch_info.get_l_bytes(),
			this->_i_tga_rle_sw,
			this->cl_name.get_cp_name(),
			this->get_i_mv_sw(),
			this->get_i_pv_sw(),
			this->get_i_cv_sw()
		)) {
			pri_funct_err_bttvr(
			"Error : tga_image_write(-) returns NG." );
			return NG;
		}
	}
	else {
		pri_funct_err_bttvr(
		"Error : not support extention<%s>.", cp_ext );
		return NG;
	}

	return OK;
}
