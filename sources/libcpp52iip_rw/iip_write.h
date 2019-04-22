#ifndef __iip_write_h__
#define __iip_write_h__

#include "ptbl_returncode.h"
#include "iip_canvas.h"
#include "name_strings.h"
#include "iip_read.h"

class iip_write : public iip_canvas {
public:
	iip_write(void)
	:_i_tga_rle_sw(ON)
	{
		this->set_ccp_object_name_of_mv("iip_write");
		this->_d_tif_dpi_x = 0.0;
		this->_d_tif_dpi_y = 0.0;
		//this->set_tif_compression_lzw();
		//this->set_tif_compression_lzw_no_prediction_scheme();
		//this->set_tif_byte_order_big_endian();
		this->set_l_tif_orientation_rot0();
	}
	~iip_write(void)
	{
		this->_d_tif_dpi_x = 0.0;
		this->_d_tif_dpi_y = 0.0;
		//this->set_tif_compression_lzw();
		//this->set_tif_compression_lzw_no_prediction_scheme();
		//this->set_tif_byte_order_big_endian();
		this->set_l_tif_orientation_rot0();
	}

	/* 名前を格納する(以前のメモリを解放、メモリ確保、記録) */
	name_strings	cl_name;

	/* iip_readオブジェクトから画像ファイルの各種情報を引継ぐ */
	void set_file_attrbute_from_read( iip_read *clp_read );

	/* キャンバス画像をファイルに書き出す */
	int file( void );

	/* 画像ファイルの各種情報 */

	void set_d_tif_dpi_x( double dd ) {
	  this->_d_tif_dpi_x = dd; }
	void set_d_tif_dpi_y( double dd ) {
	  this->_d_tif_dpi_y = dd; }

#if 0
	void set_tif_compression_none( void );
	void set_tif_compression_lzw( void );
	void set_tif_compression_packbits( void );
	void set_tif_compression_faxg4( void );

	/* (注意)2004.09.14.tue
		TIFF RGB各16btis sampling画像のとき
	---------------+---------------+---------------
	lzw
	prediction
	scheme		1		2
	---------------+---------------+---------------
	症状		中間色	一部黒	中間色	一部黒
	---------------+-------+-------+-------+-------
	libtiff-v3.5.7	正常	正常	正常	でる
	libtiff-v3.6.0	?
	libtiff-v3.6.1	でない	正常	でない	でる
	---------------+-------+-------+-------+-------
	"lzw_prediction_scheme = 2;"は16bits画像で使えない。
	*/
	void set_tif_compression_lzw_no_prediction_scheme( void );
	void set_tif_compression_lzw_prediction_scheme( void );

	void set_tif_byte_order_depend_cpu( void );
	void set_tif_byte_order_little_endian( void );
	void set_tif_byte_order_big_endian( void );
#endif

	void set_l_tif_orientation_rot0( void );
	void set_l_tif_orientation_rot90( void );
	void set_l_tif_orientation_rot180( void );
	void set_l_tif_orientation_rot270( void );

	void set_l_tif_orientation_botleft_rot0( void );

private:
	double	_d_tif_dpi_x,
		_d_tif_dpi_y;
	long	_l_tif_compression,
		_l_tif_lzw_prediction_scheme,
		_l_tif_byte_swap_mode,
		_l_tif_orientation;
	int	_i_tga_rle_sw;
};

#endif /* !__iip_write_h__ */
