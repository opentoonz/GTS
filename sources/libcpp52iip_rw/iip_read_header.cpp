#include <assert.h>	/* assert() */
#include <string.h>	/* strcmp() */
#include <limits>	/* std::numeric_limits<> */

#include "ptbl_returncode.h"
#include "pri.h"

#include "image_tif_read_handle.h"
#include "tga_image_rw.h"

#ifdef _WIN32
#include "osapi_mbs_wcs.h"	// osapi::cp932_from_utf8(-)
#endif

#include "iip_read.h"

int iip_read::header( void )
{
	char	*cp_ext;
	int	i_ret;
	long	l_w, l_h, l_c, l_b;

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

	const std::string file_path(
#ifdef _WIN32
		const_cast<char *>(osapi::cp932_from_utf8(
		this->cl_name.get_cp_name()).c_str())
#else
		this->cl_name.get_cp_name()
#endif
	);

	/* TIFF画像 */
	if ( !strcmp( "tif", cp_ext )
	||   !strcmp( "TIF", cp_ext )
	) {
 try {
		image::tif::read_handle r_hdr(file_path);

		bool isexist = false;
		l_h = r_hdr.imagelength( isexist );
		l_w = r_hdr.imagewidth( isexist );
		l_c = r_hdr.samplesperpixel( isexist );
		l_b = r_hdr.bitspersample( isexist );

		this->_d_tif_dpi_x = r_hdr.xresolution( isexist );
		this->_d_tif_dpi_y = r_hdr.yresolution( isexist );

		this->_l_tif_tile_width  = r_hdr.tilewidth( isexist );
		this->_l_tif_tile_height = r_hdr.tilelength( isexist );

		this->_l_tif_compression = r_hdr.compression( isexist );
		this->_l_tif_orientation = r_hdr.orientation( isexist );
 }
 catch (std::exception& e) {
 		std::cerr << "Error : exception \"" << e.what() << "\"\n";
		return NG;
 }
 catch (...) {
 		std::cerr << "Error : other exception\n";
		return NG;
 }
	}
	/* Targa画像 */
	else if ( !strcmp( "tga", cp_ext )
	||        !strcmp( "TGA", cp_ext ) ) {
		i_ret = tga_image_read_header(
			const_cast<char *>( file_path.c_str() )
			,&l_w, &l_h, &l_c, &l_b
		);
		if (OK != i_ret) {
			pri_funct_err_bttvr(
	       "Error : tga_image_read_header(-) returns NG." );
			return NG;
		}
		l_b *= std::numeric_limits<unsigned char>::digits;
	}
	else {
		pri_funct_err_bttvr(
		"Error : not support extention<%s>.\n", cp_ext );
		return NG;
	}

	this->set_l_width(    l_w );
	this->set_l_height(   l_h );
	this->set_l_channels( l_c );

	/* チャンネル毎のセット */
	switch (l_b) {
	case std::numeric_limits<unsigned char>::digits:
		this->cl_ch_info.set_e_ch_num_type(E_CH_NUM_UCHAR);
		break;
	case std::numeric_limits<unsigned short>::digits:
		this->cl_ch_info.set_e_ch_num_type(E_CH_NUM_USHRT);
		break;
	case 1:
		this->cl_ch_info.set_e_ch_num_type(E_CH_NUM_BITBW);
		break;
	default:
		pri_funct_err_bttvr( "Error : bad l_bits<%ld>" , l_b );
		return NG;
	}

	return OK;
}
