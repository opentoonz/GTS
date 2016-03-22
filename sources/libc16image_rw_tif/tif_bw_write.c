#include <limits.h> /* CHAR_BIT */
#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"
#include "tif_stat.h"
#include "tif_image_rw.h"

/* モノクロ２階調保存 */
int tif_bw_write( long l_width, long l_height, void *vp_image, TIF_IMAGE_RW *tp_write, int i_pv_sw )
{
	int	i_ret = OK;
	long	l_w_bytes;

	/* 白黒反転して...
	photoshop 8.0.1で白黒２値化画像を保存すると、
	ゼロを白、1を黒(PHOTOMETRIC_MINISWHITE)となっている。
	それにあわせる
	*/
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
			"invert black and white x %ld y %ld",
			l_width, l_height );
	}
	tif_bw_invert( l_width, l_height, (unsigned char *)vp_image );

	/*
	メモリ画像は      左下原点(OpenGL座標)、
	TIFF画像ファイルは左上原点(画像ファイル座標)、
	なので、_tif_image_write_body()で保存時
	上下逆さにしている。
	よって、モノクロ２階調の保存時も、
	上下さかさにしてから保存する。

	なお、
		l_orientation
	の値をファイル保存時の正対
	(読み込み時(あるいはスキャン時)の原点位置)
	となるよう与えること
	*/

	/* ...上下反転してから... */
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
			"Reverse up and down w %ld h %ld",
			l_width, l_height );
	}
	tif_bw_reverse( l_width, l_height, (unsigned char *)vp_image );

	/* ...モノクロ２階調TIFF保存して... */
	l_w_bytes = l_width/CHAR_BIT + ((l_width%CHAR_BIT)?1:0);
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
		"Save by TIFFWriteEncodedStrip(-) w_bytes %ld, h %ld)",
			l_w_bytes, l_height );
	}
	if (-1 == TIFFWriteEncodedStrip( tp_write->tp_tiff_head,
	0, vp_image, l_w_bytes * l_height)) {
		pri_funct_err_bttvr(
		"Error : TIFFWriteEncodedStrip() returns 0." );
		i_ret = NG;
	}

	/* ...上下反転を戻し... */
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
			"Reverse up and down again w %ld h %ld",
			l_width, l_height );
	}
	tif_bw_reverse( l_width, l_height, (unsigned char *)vp_image );

	/* ...白黒反転を戻す */
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
			"invert black and white again x %ld y %ld",
			l_width, l_height );
	}
	tif_bw_invert( l_width, l_height, (unsigned char *)vp_image );

	return i_ret;
}
