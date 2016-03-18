#include "ptbl_returncode.h"
#include "pri.h"
#include "tga.h"

static unsigned long _tga_write_get_pixel( unsigned char *ucp_will_encode, long l_samples_per_pixel )
{
	unsigned long	pixel;

	pixel = (unsigned long)*ucp_will_encode++;
	while ( (long)1 < l_samples_per_pixel-- ) {
		pixel <<= 8;
		pixel |= (unsigned long)*ucp_will_encode++;
	}
	return pixel;
}

static long _tga_write_count_diff_pixels( unsigned char *ucp_will_encode, int l_samples_per_pixel, long l_pixel_count )
{
	unsigned long	ul_pixel;
	unsigned long	ul_next_pixel = 0;
	long	l_count;

	l_count = 0;

	/* バッファの数があとpixel１個分ならば */
	if ( (long)1 == l_pixel_count ) return l_pixel_count;

	/* バッファの中から、最初の1pixel分を抜き取る */
	ul_pixel = _tga_write_get_pixel( ucp_will_encode, l_samples_per_pixel );

	/* バッファを見ていく */
	while ( (long)1 < l_pixel_count ) {
		/* 次のポインター */
		ucp_will_encode += l_samples_per_pixel;

		/* バッファの中から、次の1pixel分を抜き取る */
		ul_next_pixel = _tga_write_get_pixel(
			ucp_will_encode, l_samples_per_pixel );

		/* 次のpixelが同じならループから抜ける */
		if ( ul_next_pixel == ul_pixel ) break;

		ul_pixel = ul_next_pixel;
		++l_count;
		--l_pixel_count;
	}
	/* 次の数値(ul_next_pixel)は個数としては入らない */
	if ( ul_next_pixel == ul_pixel ) return l_count;

	/* ループが最後までいった場合、
		次の数値(ul_next_pixel)も、違う数値列に入れる */
	return l_count+1;
}
static long _tga_write_count_save_pixels( unsigned char *ucp_will_encode, int l_samples_per_pixel, long l_pixel_count )
{
	unsigned long	ul_pixel;
	unsigned long	ul_next_pixel;
	long	l_count;

	l_count = 1;

	/* バッファの中から、最初の1pixel分を抜き取る */
	ul_pixel = _tga_write_get_pixel( ucp_will_encode, l_samples_per_pixel );

	l_pixel_count--;

	/* バッファを見ていく */
	while ( (long)0 < l_pixel_count ) {
		/* 次のポインター */
		ucp_will_encode += l_samples_per_pixel;

		/* バッファの中から、次の1pixel分を抜き取る */
		ul_next_pixel = _tga_write_get_pixel(
					ucp_will_encode, l_samples_per_pixel );

		/* 次のpixelと違うならループから抜ける */
		if ( ul_next_pixel != ul_pixel ) break;

		++l_count;
		--l_pixel_count;
	}
	/* 全く続かないとき1を戻す */
	return l_count;
}

/* 処理したbytes数を返す */
static long _tga_write_rle_ncode_row( long l_pixels_per_buf, long l_samples_per_pixel, unsigned char *ucp_will_encode, BWRITE *tp_bwrite )
{
	long	l_diff_count;	/* pixel count until two identical */
	long	l_same_count;	/* number of identical adjacent pixels */
	long	l_bytes_encoded;	/* count of number of bytes encoded */
	unsigned char	uc_r,uc_g,uc_b, uc_a;
	unsigned char	uchar_tmp;

	l_bytes_encoded = 0;
	while ( (long)0 < l_pixels_per_buf ) {
		l_diff_count = _tga_write_count_diff_pixels(
			ucp_will_encode, l_samples_per_pixel, l_pixels_per_buf );
		l_same_count = _tga_write_count_save_pixels(
			ucp_will_encode, l_samples_per_pixel, l_pixels_per_buf );
		if ( (long)128 < l_diff_count ) l_diff_count = 128;
		if ( (long)128 < l_same_count ) l_same_count = 128;
		if ( (long)0 < l_diff_count ) {
			/* 頭のコード(RAW packet) */
			uchar_tmp = (unsigned char)(l_diff_count - (long)1);
			if (OK != bwrite_ui8(
			(uint8_t *)&(uchar_tmp), tp_bwrite )) {
				_w_ui8err("l_diff_count-1");
				return NG;
			}

			l_pixels_per_buf -= l_diff_count;

			l_bytes_encoded += (l_diff_count * l_samples_per_pixel) + 1;

			/* データ列をセット */
			while ( (long)0 < l_diff_count ) {
			 uc_r = *ucp_will_encode++;
			 if ( l_samples_per_pixel > 1 ) uc_g = *ucp_will_encode++;
			 if ( l_samples_per_pixel > 2 ) uc_b = *ucp_will_encode++;
			 if ( l_samples_per_pixel > 3 ) uc_a = *ucp_will_encode++;

			 if (OK != bwrite_ui8(
			 (uint8_t *)&(uc_b), tp_bwrite )) {
			   _w_ui8err("uc_b"); return NG; }
			 if ( l_samples_per_pixel > 1 ) {
				if (OK != bwrite_ui8(
				(uint8_t *)&(uc_g), tp_bwrite )) {
				  _w_ui8err("uc_g"); return NG; }
			 }
			 if ( l_samples_per_pixel > 2 ) {
				if (OK != bwrite_ui8(
				(uint8_t *)&(uc_r), tp_bwrite )) {
				  _w_ui8err("uc_r"); return NG; }
			 }
			 if ( l_samples_per_pixel > 3 ) {
				if (OK != bwrite_ui8(
				(uint8_t *)&(uc_a), tp_bwrite )) {
				  _w_ui8err("uc_a"); return NG; }
			 }
			 --l_diff_count;
			}
		}
		if ( (long)1 < l_same_count ) {
			/* 頭のコード(RLE packet) */
			uchar_tmp = (unsigned char)((l_same_count - (long)1) | 0x80);
			if (OK != bwrite_ui8(
			(uint8_t *)&(uchar_tmp), tp_bwrite)) {
				_w_ui8err("l_same_count-1");
				return NG;
			}

			l_pixels_per_buf -= l_same_count;

			l_bytes_encoded += l_samples_per_pixel + 1;

			ucp_will_encode += (l_same_count - 1) * l_samples_per_pixel;

			/* データ列をセット */
			uc_r = *ucp_will_encode++;
			if ((long)1 < l_samples_per_pixel) uc_g = *ucp_will_encode++;
			if ((long)2 < l_samples_per_pixel) uc_b = *ucp_will_encode++;
			if ((long)3 < l_samples_per_pixel) uc_a = *ucp_will_encode++;

			if (OK != bwrite_ui8(
			(uint8_t *)&(uc_b), tp_bwrite )) {
			  _w_ui8err("uc_b"); return NG; }
			if ( l_samples_per_pixel > 1 ) {
			 if (OK != bwrite_ui8(
			 (uint8_t *)&(uc_g), tp_bwrite )) {
			   _w_ui8err("uc_g"); return NG; }
			}
			if ( l_samples_per_pixel > 2 ) {
			 if (OK != bwrite_ui8(
			 (uint8_t *)&(uc_r), tp_bwrite )) {
			   _w_ui8err("uc_r"); return NG; }
			}
			if ( l_samples_per_pixel > 3 ) {
			 if (OK != bwrite_ui8(
			 (uint8_t *)&(uc_a), tp_bwrite )) {
			   _w_ui8err("uc_a"); return NG; }
			}
		}
	}
	return OK;
}

int tga_write_scanline( long yy, void *vp_scanline, TGA_WRITE *tp_write )
{
	unsigned char	*ucp_tmp;
	long	l_width,
		l_samples_per_pixel,
		ii;
	unsigned char	uc_r, uc_g, uc_b, uc_a;

	/*** さまざまチェック ***/

	if (NULL == tp_write) {
		pri_funct_err_bttvr(
			"Error : bad argument, tp_write is NULL." );
		return NG;
	}
	if (NULL == vp_scanline) {
		pri_funct_err_bttvr(
			"Error : bad argument, vp_scanline is NULL." );
		return NG;
	}

	/* オープン済みかどうかをチェック */
	if (NULL == (tp_write->t_bwrite._fp)) {
		pri_funct_err_bttvr(
		"Error : Not opened yet, at tga_write_scanline(-)." );
		return NG;
	}

	/* yy */ /* の位置チェック */
	if (yy < 0L
	||  (long)(tp_write->t_tga_file_header.s_ysize) <= yy) {
		pri_funct_err_bttvr(
			"Error : yy<%ld> is out of range.", yy );
		return NG;
	}

	/* データの移し変え */

	ucp_tmp = (unsigned char *)vp_scanline;
	l_width = (long)(tp_write->t_tga_file_header.s_xsize);
	l_samples_per_pixel = (long)(tp_write->t_tga_file_header.uc_pixsize/8);

	if (10L == (long)tp_write->t_tga_file_header.uc_imgtyp) {
		if (OK != _tga_write_rle_ncode_row(
		l_width, l_samples_per_pixel, ucp_tmp, &(tp_write->t_bwrite) )) {
			pri_funct_err_bttvr(
		 "Error : _tga_write_rle_ncode_row(%ld,%ld,,) returns NG.",
				l_width, l_samples_per_pixel );
			(void)fflush( stderr );
			return NG;
		}
	}
	else {
	 for( ii = 0 ; ii < l_width; ++ii ){
						   uc_r = *ucp_tmp++;
		if ((long)1 < l_samples_per_pixel) uc_g = *ucp_tmp++;
		if ((long)2 < l_samples_per_pixel) uc_b = *ucp_tmp++;
		if ((long)3 < l_samples_per_pixel) uc_a = *ucp_tmp++;

		if (OK != bwrite_ui8(
		(uint8_t *)&(uc_b),&(tp_write->t_bwrite) )) {
		  _w_ui8err("uc_b"); return NG; }
		if ( 1L < l_samples_per_pixel ) {
		 if (OK != bwrite_ui8(
		 (uint8_t *)&(uc_g),&(tp_write->t_bwrite) )) {
		   _w_ui8err("uc_g"); return NG; }
		}
		if ( 2L < l_samples_per_pixel ) {
		 if (OK != bwrite_ui8(
		 (uint8_t *)&(uc_r),&(tp_write->t_bwrite) )) {
		   _w_ui8err("uc_r"); return NG; }
		}
		if ( 3L < l_samples_per_pixel ) {
		 if (OK != bwrite_ui8(
		 (uint8_t *)&(uc_a),&(tp_write->t_bwrite) )) {
		   _w_ui8err("uc_a"); return NG; }
		}
	 }
	}
	return OK;
}
