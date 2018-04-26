#include <assert.h> /* assert() */
#include <string.h> /* strcmp() */

#include "ptbl_returncode.h"
#include "pri.h"

#include "tif_image_rw.h"
#include "tga_image_rw.h"

#ifdef _WIN32
#include "osapi_mbs_wcs.h"	// osapi::cp932_from_utf8(-)
#endif

#include "iip_read.h"

int iip_read::file( void )
{
	char	*cp_ext;
	void	*vp_canvas;
	long	l_w, l_h, l_c, l_b;
	long	l_tif_bits_per_sample = 0;

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
	||        !strcmp( "tzi", cp_ext )
	||        !strcmp( "TIF", cp_ext ) ) {
		vp_canvas = tif_image_read(
#ifdef _WIN32
		const_cast<char *>(osapi::cp932_from_utf8(
		this->cl_name.get_cp_name()).c_str())
#else
		this->cl_name.get_cp_name()
#endif
		,&l_w, &l_h, &l_c, &l_b
		,&(l_tif_bits_per_sample)
		,&(this->_d_tif_dpi_x)
		,&(this->_d_tif_dpi_y)
		,&(this->_l_tif_tile_width)
		,&(this->_l_tif_tile_height)
		,&(this->_l_tif_compression)
		,&(this->_l_tif_orientation)
		,this->get_i_mv_sw()
		,this->get_i_pv_sw()
		,this->get_i_cv_sw()
		);
		if (NULL == vp_canvas) {
			pri_funct_err_bttvr(
			"Error : tif_image_read(-) returns NULL." );
			return NG;
		}

	}
	/* Targa画像 */
	else if ( !strcmp( "tga", cp_ext )
	||        !strcmp( "TGA", cp_ext ) ) {
		vp_canvas = tga_image_read(
#ifdef _WIN32
		const_cast<char *>(osapi::cp932_from_utf8(
		this->cl_name.get_cp_name()).c_str())
#else
		this->cl_name.get_cp_name()
#endif
		,&l_w, &l_h, &l_c, &l_b
		,this->get_i_mv_sw()
		,this->get_i_pv_sw()
		,this->get_i_cv_sw()
		);
		if (NULL == vp_canvas) {
			pri_funct_err_bttvr(
			"Error : tga_image_read(-) returns NULL." );
			return NG;
		}
	}
	else {
		pri_funct_err_bttvr(
		"Error : not support extention<%s>.\n", cp_ext );
		return NG;
	}

	this->set_vp_independence_canvas( vp_canvas );
	this->set_l_width(    l_w );
	this->set_l_height(   l_h );
	this->set_l_channels( l_c );

	/* チャンネル毎のセット */
	switch (l_b) {
	case sizeof(unsigned char):
		this->cl_ch_info.set_e_ch_num_type(E_CH_NUM_UCHAR);
		break;
	case sizeof(unsigned short):
		this->cl_ch_info.set_e_ch_num_type(E_CH_NUM_USHRT);
		break;
	case 0:
		if (1L == l_tif_bits_per_sample) {
		 this->cl_ch_info.set_e_ch_num_type(E_CH_NUM_BITBW);
		} else {
		 pri_funct_err_bttvr(
			"Error : bad l_bytes<%ld> and bits<%ld>",
			l_b, l_tif_bits_per_sample );
		 return NG;
		}
		break;
	default:
		pri_funct_err_bttvr( "Error : bad l_bytes<%ld>", l_b );
		return NG;
	}

	return OK;
}
