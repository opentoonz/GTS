#include "tiff.h"
#include "iip_write.h"

#if 0
/* .tif画像の圧縮方法 */
void iip_write::set_tif_compression_none( void ) {
	   this->_l_tif_compression =
	tif_write_get_i_compression_none();
}
void iip_write::set_tif_compression_lzw( void ) {
	   this->_l_tif_compression =
	tif_write_get_i_compression_lzw();
}
void iip_write::set_tif_compression_packbits( void ) {
	   this->_l_tif_compression =
	tif_write_get_i_compression_packbits();
}
void iip_write::set_tif_compression_faxg4( void ) {
	   this->_l_tif_compression =
	tif_write_get_i_compression_faxg4(); /* COMPRESSION_CCITTFAX4 */
}

/* .tif画像の圧縮方法がLZWの時の詳細 */
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
void iip_write::set_tif_compression_lzw_no_prediction_scheme( void ) {
			  this->_l_tif_lzw_prediction_scheme = 1; }
void iip_write::set_tif_compression_lzw_prediction_scheme( void ) {
		       this->_l_tif_lzw_prediction_scheme = 2; }

/* .tif画像のCPUバイトオーダー */
void iip_write::set_tif_byte_order_depend_cpu( void ) {
	   this->_l_tif_byte_swap_mode = 0L;
}
void iip_write::set_tif_byte_order_little_endian( void ) {
	   this->_l_tif_byte_swap_mode = 'l';
}
void iip_write::set_tif_byte_order_big_endian( void ) {
	   this->_l_tif_byte_swap_mode = 'b';
}
#endif

/* .tif画像の方向 */
void iip_write::set_l_tif_orientation_rot0( void ) {
	     this->_l_tif_orientation =
	  //tif_write_get_i_orientation_rot0();
	  ORIENTATION_TOPLEFT;
}
void iip_write::set_l_tif_orientation_rot90( void ) {
	     this->_l_tif_orientation =
	  //tif_write_get_i_orientation_rot90();
	  ORIENTATION_LEFTBOT; /* ???RIGHTTOP??? */
}
void iip_write::set_l_tif_orientation_rot180( void ) {
	     this->_l_tif_orientation =
	  //tif_write_get_i_orientation_rot180();
	  ORIENTATION_BOTRIGHT;
}
void iip_write::set_l_tif_orientation_rot270( void ) {
	     this->_l_tif_orientation =
	  //tif_write_get_i_orientation_rot270();
	  ORIENTATION_RIGHTTOP; /* ???LEFTBOT??? */
}

/* モノクロ２階調専用の設定(左下原点のまま保存するため) */
void iip_write::set_l_tif_orientation_botleft_rot0( void ) {
	     this->_l_tif_orientation =
	  //tif_write_get_i_orientation_botleft_rot0();
	  ORIENTATION_BOTLEFT;
}
