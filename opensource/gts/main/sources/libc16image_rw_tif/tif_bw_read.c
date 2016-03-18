#include <stdlib.h>	/* calloc() */
#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"

unsigned char *tif_bw_read( TIF_IMAGE_RW *tp_read, int i_reverse_sw, int i_pv_sw )
{
	tsize_t	strip_size,
		strip_count,
		image_size,
		ii,
		offset,
		return_code;
	unsigned char	*ucharp_image;
/***
	unsigned char	uchar_tmp;
	uint16	ui16_fillorder;
***/

	/* multiple strips(画像の水平方向のブロック)の大きさ
	戻り値の型はtsize_t[=int32] */
	strip_size = TIFFStripSize( tp_read->tp_tiff_head );

	/* multiple strips(画像の水平方向のブロック)の数
	戻り値の型はtstrip_t[=uint32] */
	strip_count = TIFFNumberOfStrips( tp_read->tp_tiff_head );

	/* 画像の大きさ(ほんとうはImageLength値を見るべきか？
	--> 不明(2005.01.11) */
	image_size = strip_count * strip_size;

	/* 画像のメモリ確保 */
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
			"Alloc %d bytes(strip (count %d) x (size %d))",
			image_size, strip_count,strip_size
		);
	}
	ucharp_image = (unsigned char *)calloc(
				strip_count,strip_size );
	if (NULL == ucharp_image) {
		pri_funct_err_bttvr(
			"Error : calloc(%ld,%ld) returns NULL",
			strip_count,strip_size );
		return NULL;
	}

	/* ファイルから読み込み */
	if (ON == i_pv_sw) {
		pri_funct_msg_ttvr(
			"Read(tif B/W) strip (count %d) x (size %d)",
			strip_count,strip_size
		);
	}
	offset = 0;
	for (ii = 0; ii < strip_count; ++ii){
		return_code = TIFFReadEncodedStrip(
			tp_read->tp_tiff_head, (tstrip_t)ii,
			ucharp_image + offset, strip_size
		);
		if (-1 == return_code) {
			pri_funct_err_bttvr(
	       "Error : TIFFReadEncodedStrip(,%ld/%ld,,%ld) returns -1",
				ii,strip_count,strip_size );
			free(ucharp_image);
			return NULL;
		}
		offset += return_code;
	}

	/* 原点が上のとき上下反転して、下(OpenGLは左下原点)にする */
	if (ON == i_reverse_sw) {
		if (ON == i_pv_sw) {
			pri_funct_msg_ttvr(
				"reverse up and down  w %u h %u",
				tp_read->ui32_image_width,
				tp_read->ui32_image_length
			);
		}
		tif_bw_reverse(
			tp_read->ui32_image_width,
			tp_read->ui32_image_length,
			ucharp_image );
	}

	/* ゼロを黒、1を白(PHOTOMETRIC_MINISBLACK)とする */
	if (PHOTOMETRIC_MINISWHITE == tp_read->ui16_photometric) {
		if (ON == i_pv_sw) {
			pri_funct_msg_ttvr(
				"invert black and white  size %ld",
				image_size );
		}
		tif_bw_invert(
			tp_read->ui32_image_width,
			tp_read->ui32_image_length,
			ucharp_image );
	}
#if 0
	!!!!!!!!!!!!!!!comment_out!!!!!!!!!!!!!!!

	/* ビットのベキ順を調べる */
	if (1 == TIFFGetField(
		tp_read->tp_tiff_head,TIFFTAG_FILLORDER,&ui16_fillorder
	)){
	 /* MSBが先頭にくるようにする */
	 if (FILLORDER_MSB2LSB != ui16_fillorder) {
		/* 1byte内のビットオーダーを逆にする */
		for (ii = 0L; ii < image_size; ++ii) {
			uchar_tmp = 0;
			if (ucharp_image[ii] & 128) {uchar_tmp +=   1;}
			if (ucharp_image[ii] &  64) {uchar_tmp +=   2;}
			if (ucharp_image[ii] &  32) {uchar_tmp +=   4;}
			if (ucharp_image[ii] &  16) {uchar_tmp +=   8;}
			if (ucharp_image[ii] &   8) {uchar_tmp +=  16;}
			if (ucharp_image[ii] &   4) {uchar_tmp +=  32;}
			if (ucharp_image[ii] &   2) {uchar_tmp +=  64;}
			if (ucharp_image[ii] &   1) {uchar_tmp += 128;}
			ucharp_image[ii] = uchar_tmp;
		}
	 }
	}
	!!!!!!!!!!!!!!!comment_out!!!!!!!!!!!!!!!
#endif

	return ucharp_image;
}
