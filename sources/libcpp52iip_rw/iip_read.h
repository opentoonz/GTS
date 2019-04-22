#ifndef __iip_read_h__
#define __iip_read_h__

#include "name_strings.h"
#include "iip_canvas.h"

class iip_read : public iip_canvas {
public:
	iip_read(void)
		:_d_tif_dpi_x(0)
		,_d_tif_dpi_y(0)
		,_l_tif_tile_width(0)
		,_l_tif_tile_height(0)
		,_l_tif_compression(0)
		,_l_tif_orientation(0)
	{
		this->set_ccp_object_name_of_mv("iip_read");
	}
	~iip_read(void) {}

	/* 名前を格納する(以前のメモリを解放、メモリ確保、記録) */
	name_strings	cl_name;

	/* 画像ファイルの情報のみ読み込み、設定する */
	int header( void );

	/* 画像カンバスを生成し、ファイルから画像を読み込む */
	int file( void );

	double get_d_tif_dpi_x( void ) {
     return this->_d_tif_dpi_x; }
	double get_d_tif_dpi_y( void ) {
     return this->_d_tif_dpi_y; }

	long get_l_tif_tile_width( void ) {
   return this->_l_tif_tile_width; }
	long get_l_tif_tile_height( void ) {
   return this->_l_tif_tile_height; }

	long get_l_tif_compression( void ) {
   return this->_l_tif_compression; }

	long get_l_tif_orientation( void ) {
   return this->_l_tif_orientation; }

private:
	/* TIFF画像を呼んだ時のみ保持する情報 */
	double	_d_tif_dpi_x,
		_d_tif_dpi_y;
	long	_l_tif_tile_width,
		_l_tif_tile_height,
		_l_tif_compression,
		_l_tif_orientation;
};
#endif /* !__iip_read_h__ */
