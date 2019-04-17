//#include "tif_image_rw.h"
#include "iip_read.h"

/* .tif画像の圧縮方法 */
/*void iip_read::_set_tif_compression( void ) {
	   this->_l_tif_compression =
	tif_write_get_i_compression_lzw();
}*/

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

/* .tif画像の方向 */
/*void iip_read::_set_tif_orientation( void ) {
	     this->_l_tif_orientation =
	  tif_write_get_i_orientation_rot0();
}*/
