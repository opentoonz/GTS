#include <assert.h>	/* assert() */
#include <string.h>	/* strcmp() */
#include <iostream>	/* std::cerr */
#include <limits>	/* std::numeric_limits<> */

#include "ptbl_returncode.h"
#include "pri.h"

#include "tga_image_rw.h"
#include "image_tif_read_handle.h"
#include "image_tif_reader.h"

#ifdef _WIN32
#include "osapi_mbs_wcs.h"	// osapi::cp932_from_utf8(-)
#endif

#include "iip_read.h"

int iip_read::file( void )
{
	char	*cp_ext;
	void	*vp_canvas;
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
	||   !strcmp( "tzi", cp_ext )
	||   !strcmp( "TIF", cp_ext ) ) {

 try {
		image::tif::reader rdr;

		/* メモリ確保 */
		size_t image_bytes=0;
		size_t history_bytes=0;
		rdr.get_size( file_path ,image_bytes ,history_bytes );
		//std::vector<uint8_t> image(image_bytes);
		vp_canvas = calloc( image_bytes ,1 );
		if (vp_canvas == nullptr) {
 			std::cerr << "Error : calloc("
				<< image_bytes << ",1) returns nullptr\n";
			return NG;
		}

		/* 画像読込 */
		image::common::properties props;
		std::string history_str;
		static bool break_sw=false;
		rdr.get_data(
			file_path
			, props
			, image_bytes
			//, image.data()
			, vp_canvas
			, history_str
			, break_sw /* 中断Switch。外からtureで中断 */
			, 0 /* 分割読込の個々サイズ(tif以外で使用する) */
		);

		/* パラメータセット */
		l_h = props.height;
		l_w = props.width;
		l_c = props.channels;
		l_b = props.bits;
		this->_d_tif_dpi_x = props.reso_x;
		this->_d_tif_dpi_y = props.reso_y;
		this->_l_tif_tile_width = 0;	/* 不用 */
		this->_l_tif_tile_height = 0;	/* 不用 */
		bool isexist = false;
		image::tif::read_handle r_hdr(file_path);
		this->_l_tif_compression = r_hdr.compression(isexist);
		this->_l_tif_orientation = props.orie_side;

		//std::ofstream ofs( "tmp.raw" ,std::ios_base::binary );
		//ofs.write( (char *)(image.data()) ,image.size() );
		//ofs.close();
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
		vp_canvas = tga_image_read(
			const_cast<char *>( file_path.c_str() )
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
		l_b *= std::numeric_limits<unsigned char>::digits;
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
