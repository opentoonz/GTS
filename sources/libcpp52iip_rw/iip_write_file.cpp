#include <limits.h> /* CHAR_BIT */
#include <assert.h> /* assert() */
#include <string.h> /* strcmp() */
#include <iostream>	/* std::cerr */

#include "tiff.h"
#include "pri.h"

#include "image_tif_common.h"
#include "image_tif_writer.h"
#include "tga_image_rw.h"

#ifdef _WIN32
#include "osapi_mbs_wcs.h"	// osapi::cp932_from_utf8(-)
#endif

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
	||   !strcmp( "TIF", cp_ext ) ) {

		int compression_number = COMPRESSION_NONE;
		if ((0 == this->cl_ch_info.get_l_bytes())
		&&  (1 == this->cl_ch_info.get_l_bits())
		) {	/* BWの場合の圧縮 */
			compression_number = COMPRESSION_CCITTFAX4;
		}
		else {	/* その他(Grayscale,RGB)の場合の圧縮 */
			compression_number = COMPRESSION_LZW;
		}

		/* TIFFバイトオーダーをCPUに依存とする
			--> "image_tif_write_head.cpp" 内固定
		*/

#if 0
		if (OK != tif_image_write(
			this->get_vp_canvas()
			,this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
			,this->cl_ch_info.get_l_bytes()
			,this->cl_ch_info.get_l_bits()
			,this->_d_tif_dpi_x
			,this->_d_tif_dpi_y
			,this->_l_tif_compression
			,this->_l_tif_lzw_prediction_scheme
			,this->_l_tif_orientation
			,this->_l_tif_byte_swap_mode
#ifdef _WIN32
		,const_cast<char *>(osapi::cp932_from_utf8(
		 this->cl_name.get_cp_name()).c_str())
#else
		,this->cl_name.get_cp_name()
#endif
			,this->get_i_mv_sw()
			,this->get_i_pv_sw()
			,this->get_i_cv_sw()
		)) {
			pri_funct_err_bttvr(
			"Error : tif_image_write(-) returns NG." );
			return NG;
		}
#endif

 try {
		image::common::properties props;
		props.height	= this->get_l_height();
		props.width	= this->get_l_width();
		props.channels	= this->get_l_channels();
		props.bits	= this->cl_ch_info.get_l_bits();
		props.reso_unit	= image::common::resolution::inch;
		props.reso_x	= this->_d_tif_dpi_x;
		props.reso_y	= this->_d_tif_dpi_y;
		props.orie_side =
 static_cast<image::common::orientation::side>(this->_l_tif_orientation);

		const size_t image_bytes = props.height *
			image::tif::bytes_of_scanline(
				props.width , props.channels , props.bits
			);
		std::string history_str;
		image::tif::writer wtr;
		std::ostringstream error_or_warning_msg;

		const bool w_chk = wtr.error_from_properties(
			props
			, 0
			, error_or_warning_msg
		);
		if (w_chk) {
			std::cerr << error_or_warning_msg.str();
			return NG;
		}
		wtr.put_data(
			props
			, image_bytes
			, this->get_vp_canvas()
			, compression_number
			, history_str
			, file_path
		);
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
		if (OK != tga_image_write(
			this->get_vp_canvas()
			,this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
			,this->cl_ch_info.get_l_bytes()
			,this->_i_tga_rle_sw
#ifdef _WIN32
		,const_cast<char *>(osapi::cp932_from_utf8(
		 this->cl_name.get_cp_name()).c_str())
#else
		,this->cl_name.get_cp_name()
#endif
			,this->get_i_mv_sw()
			,this->get_i_pv_sw()
			,this->get_i_cv_sw()
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
