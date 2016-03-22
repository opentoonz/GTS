#include "ptbl_returncode.h"
#include "pri.h"
#include "tga.h"

static int _tga_read_scanline_uncompressed( TGA_READ *tp_read, void *vp_buf )
{
	BREAD	*tp_bread;
	TGA_FILE_HEADER	*tp_header;
	long	l_size;
	unsigned char	*ucp_;
	unsigned long	ul_val;
	unsigned long	ul_r, ul_g, ul_b, ul_a;
	unsigned char	uchar_tmp;
	unsigned short	ushort_tmp;

	tp_bread = &(tp_read->t_bread);
	tp_header = &(tp_read->t_tga_file_header);
	l_size	= (long)(tp_header->s_xsize);

	/* フルカラーモードで読み込む */
	if (tp_header->s_mapsize <= 1) {
		switch (tp_header->uc_pixsize) {
		case 32:
			ucp_ = (unsigned char *)vp_buf;
			while ((long)0 < l_size--) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_b");
					return NG;
				}
				ul_b = (unsigned long)uchar_tmp;
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_g");
					return NG;
				}
				ul_g = (unsigned long)uchar_tmp;
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_r");
					return NG;
				}
				ul_r = (unsigned long)uchar_tmp;
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_a");
					return NG;
				}
				ul_a = (unsigned long)uchar_tmp;
				*ucp_++ = (unsigned char)(ul_r & 0xff);
				*ucp_++ = (unsigned char)(ul_g & 0xff);
				*ucp_++ = (unsigned char)(ul_b & 0xff);
				*ucp_++ = (unsigned char)(ul_a & 0xff);
			}
			break;
		case 24:
			ucp_ = (unsigned char *)vp_buf;
			while ((long)0 < l_size--) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_b");
					return NG;
				}
				ul_b = (unsigned long)uchar_tmp;
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_g");
					return NG;
				}
				ul_g = (unsigned long)uchar_tmp;
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_r");
					return NG;
				}
				ul_r = (unsigned long)uchar_tmp;
				*ucp_++ = (unsigned char)(ul_r & 0xff);
				*ucp_++ = (unsigned char)(ul_g & 0xff);
				*ucp_++ = (unsigned char)(ul_b & 0xff);
			}
			break;
		case 16:
		case 15:
			ucp_ = (unsigned char *)vp_buf;
			while ((long)0 < l_size--) {
				if (OK != bread_ui16(
				tp_bread,(uint8_t *)&(ushort_tmp) )) {
					_r_ui8err("ul_val");
					return NG;
				}
				ul_val = (unsigned long)ushort_tmp;
				*ucp_++ = (unsigned char)(((ul_val>>10)&0x1f)* 0xff / 0x1f);
				*ucp_++ = (unsigned char)(((ul_val>> 5)&0x1f)* 0xff / 0x1f);
				*ucp_++ = (unsigned char)(((ul_val    )&0x1f)* 0xff / 0x1f);
			}
			break;
		case 8:
			ucp_ = (unsigned char *)vp_buf;
			while ((long)0 < l_size--) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_val");
					return NG;
				}
				ul_val = (unsigned long)uchar_tmp;
				*ucp_++ = (unsigned char)ul_val;
			}
			break;
		default:
			pri_funct_err_bttvr(
		"Error : Can't handle this format type's targa." );
			return NG;
			break;
		}
	/* カラーテーブルモードで読み込む */
	} else {
		switch (tp_header->uc_pixsize) {
		case 8:
			ucp_ = (unsigned char *)vp_buf;
			while ((long)0 < l_size--) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_val");
					return NG;
				}
				ul_val = (unsigned long)uchar_tmp;
				*ucp_++ = (unsigned char)ul_val;
			}
			break;
		default:
			pri_funct_err_bttvr(
 "Error : Can't handle this format targa type mapsize<%d> pixsize<%d>.",
				tp_header->s_mapsize,
				tp_header->uc_pixsize);
			return NG;
			break;
		}
	}
	return OK;
}

static int _tga_read_scanline_runlength( TGA_READ *tp_read, void *vp_buf )
{
	BREAD	*tp_bread;
	TGA_FILE_HEADER	*tp_header;

	long	l_value;
	long	l_cntr;
	unsigned long	ul_val;
	long	l_bpp = 0;
	long	l_buffer_bytes;
	unsigned char	*ucp_;
	unsigned char	uchar_tmp;

	static int i_in_raw_packet_sw = OFF;/* flags processing state for RLE data */
	static int i_in_rle_packet_sw = OFF;/* flags processing state for RLE data */
	static long l_packet_size = 0L;/* records current RLE packet size in bytes */
		/* l_packet_sizeの最大値は、128、l_bppの最大は、4。128*4=512 */
	static unsigned long	ul_r,ul_g,ul_b,ul_a;

	tp_bread = &(tp_read->t_bread);
	tp_header = &(tp_read->t_tga_file_header);

	/* 1pixel当りのバイト数 */
	switch (tp_header->uc_pixsize) {
	case 32: l_bpp = (long)4; break;
	case 24: l_bpp = (long)3; break;
	case 16:
	case 15: l_bpp = (long)2; break;
	case 8:  l_bpp = (long)1; break;
	}

	/* バッファのサイズ */
	l_buffer_bytes = (long)(tp_header->s_xsize) * l_bpp;

	/* メモリのポインター */
	ucp_ = (unsigned char *)vp_buf;

	/* ダンプデータとしての数の分読むためのループ */
	while (0 < l_buffer_bytes) {
	 /* RunLength圧縮データの解凍 */
	 if ( ON == i_in_rle_packet_sw ) {
		/* 取り込んだ大きさが、受け取るバッファに入りきらないとき */
		if ( l_buffer_bytes < l_packet_size * l_bpp ) {
			l_value = l_buffer_bytes/l_bpp;/* 残りのバッファのpixel数 */
			l_packet_size -= l_value;
			l_buffer_bytes = (long)0;
		}
		/* 残りデータの処理を終了 */
		else {
			l_buffer_bytes -= l_packet_size * l_bpp;
			l_value = l_packet_size;
			l_packet_size = (long)0;
			i_in_rle_packet_sw = OFF;
		}
		/* 読んだデータを、
			指定pixel数(l_value)受け取るバッファに敷き詰める */
		while ( (long)0 < l_value ) {
			if ((long)2 == l_bpp) {
			 ul_val = ((ul_b & 0xff) << 8) & (ul_g&0xff);
			 *ucp_++ = (unsigned char)(((ul_val >> 10) & 0x1f) * 0xff / 0x1f);
			 *ucp_++ = (unsigned char)(((ul_val >>  5) & 0x1f) * 0xff / 0x1f);
			 *ucp_++ = (unsigned char)(((ul_val      ) & 0x1f) * 0xff / 0x1f);
			} else {
						 *ucp_++ = (unsigned char)(ul_b & 0xff);
			if ( (long)1 < l_bpp ) { *ucp_++ = (unsigned char)(ul_g & 0xff); }
			if ( (long)2 < l_bpp ) { *ucp_++ = (unsigned char)(ul_r & 0xff); }
			if ( (long)3 < l_bpp ) { *ucp_++ = (unsigned char)(ul_a & 0xff); }
			}
			--l_value;
		}
	 }
	 else if ( ON == i_in_raw_packet_sw ) {
		if ( l_buffer_bytes < l_packet_size * l_bpp ) {
			l_value = l_buffer_bytes;
			l_packet_size -= l_buffer_bytes / l_bpp;
			l_buffer_bytes = (long)0;
		}
		else {
			l_value = l_packet_size * l_bpp;/* calculate byte count */
			l_buffer_bytes -= l_value;
			i_in_raw_packet_sw = OFF;
		}
		for ( l_cntr = (long)0; l_cntr < l_value/l_bpp; ++l_cntr ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_b");
					return NG;
				}
				ul_b = (unsigned long)uchar_tmp;
			if ( (long)1 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_g");
					return NG;
				}
				ul_g = (unsigned long)uchar_tmp;
			}
			if ( (long)2 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_r");
					return NG;
				}
				ul_r = (unsigned long)uchar_tmp;
			}
			if ( (long)3 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_a");
					return NG;
				}
				ul_a = (unsigned long)uchar_tmp;
			}
			if ((long)2 == l_bpp) {
			 ul_val = ((ul_b & 0xff) << 8) & (ul_g&0xff);
			 *ucp_++ = (unsigned char)(((ul_val >> 10) & 0x1f) * 0xff / 0x1f);
			 *ucp_++ = (unsigned char)(((ul_val >>  5) & 0x1f) * 0xff / 0x1f);
			 *ucp_++ = (unsigned char)(((ul_val      ) & 0x1f) * 0xff / 0x1f);
			} else {
			 			 *ucp_++ = (unsigned char)(ul_r & 0xff);
			 if ( (long)1 < l_bpp ) { *ucp_++ = (unsigned char)(ul_g & 0xff); }
			 if ( (long)2 < l_bpp ) { *ucp_++ = (unsigned char)(ul_b & 0xff); }
			 if ( (long)3 < l_bpp ) { *ucp_++ = (unsigned char)(ul_a & 0xff); }
			}
		}
	 }
	 else {
		/* 解析の始めのデータを読む */
		if (OK != bread_ui8( tp_bread, (uint8_t *)&(uchar_tmp) )) {
			_r_ui8err("ul_a");
			return NG;
		}
		ul_val = (unsigned long)uchar_tmp;
		l_packet_size = (long)ul_val;

		/* RunLength圧縮データ (charマイナス(0x80ビットが立っている)) */
		if ( l_packet_size & 0x80 ) {
			l_packet_size &= (long)0x7f;
			++l_packet_size;

			/* 取り込んだ大きさが、受け取るバッファに入りきらないとき */
			if ( l_buffer_bytes < (l_packet_size * l_bpp) ) {
				/* 残りのバッファのpixel数 */
				l_value = l_buffer_bytes / l_bpp;

				/* ループの次のループの時のための記録 */
				l_packet_size -= l_value; /*処理した数を引く */
				i_in_rle_packet_sw = ON;

				/* カウンターをゼロにする */
				l_buffer_bytes = (long)0;
			}
			else {
				l_value = l_packet_size;/* 同じ色であるpixel数 */
				l_buffer_bytes -= l_packet_size * l_bpp;
			}
			/* 1pixel分読む */
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_b");
					return NG;
				}
				ul_b = (unsigned long)uchar_tmp;
			if ( (long)1 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_g");
					return NG;
				}
				ul_g = (unsigned long)uchar_tmp;
			}
			if ( (long)2 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_r");
					return NG;
				}
				ul_r = (unsigned long)uchar_tmp;
			}
			if ( (long)3 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_a");
					return NG;
				}
				ul_a = (unsigned long)uchar_tmp;
			}
			/* 読んだデータを、
				指定pixel数(l_value)受け取るバッファに敷き詰める */
			while ( (long)0 < l_value ) {
			 if ((long)2 == l_bpp) {
			  ul_val = ((ul_b & 0xff) << 8) & (ul_g&0xff);
			  *ucp_++ = (unsigned char)(((ul_val >> 10) & 0x1f) * 0xff / 0x1f);
			  *ucp_++ = (unsigned char)(((ul_val >>  5) & 0x1f) * 0xff / 0x1f);
			  *ucp_++ = (unsigned char)(((ul_val      ) & 0x1f) * 0xff / 0x1f);
			 } else {
						   *ucp_++ = (unsigned char)(ul_r & 0xff);
			  if ( (long)1 < l_bpp ) { *ucp_++ = (unsigned char)(ul_g & 0xff); }
			  if ( (long)2 < l_bpp ) { *ucp_++ = (unsigned char)(ul_b & 0xff); }
			  if ( (long)3 < l_bpp ) { *ucp_++ = (unsigned char)(ul_a & 0xff); }
			 }
				--l_value;
			}
		}
		/* Raw非圧縮データ (charマイナス(0x80ビットが立っていない)) */
		else {
			++l_packet_size;

			/* 取り込んだ大きさが、受け取るバッファに入りきらないとき */
			if ( l_buffer_bytes < (l_packet_size * l_bpp) ) {
				/* 残りのバッファ数を、受け取る大きさとする */
				l_value = l_buffer_bytes;

				/* ループの次のループの時のための記録 */
				/* 入りきらない数とする */
				l_packet_size -= l_buffer_bytes / l_bpp;

				i_in_raw_packet_sw = ON; /* 処理動作のモード */

				l_buffer_bytes = (long)0;/* カウンターをゼロにする */
			}
			else {
				/* 取り込んだ(受け取る)大きさ */
				l_value = l_bpp * l_packet_size;

				/* 取り込んだ数だけカウンターを減らす */
				l_buffer_bytes -= l_value;
			}
			/* Raw非圧縮データ部分を、読み込み、バッファに受け取る */
			for ( l_cntr = (long)0; l_cntr < l_value/l_bpp; ++l_cntr ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_b");
					return NG;
				}
				ul_b = (unsigned long)uchar_tmp;
			 if ( (long)1 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_g");
					return NG;
				}
				ul_g = (unsigned long)uchar_tmp;
			 }
			 if ( (long)2 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_r");
					return NG;
				}
				ul_r = (unsigned long)uchar_tmp;
			 }
			 if ( (long)3 < l_bpp ) {
				if (OK != bread_ui8(
				tp_bread, (uint8_t *)&(uchar_tmp) )) {
					_r_ui8err("ul_a");
					return NG;
				}
				ul_a = (unsigned long)uchar_tmp;
			 }
			 if ((long)2 == l_bpp) {
			  ul_val = ((ul_b & 0xff) << 8) & (ul_g&0xff);
			  *ucp_++ = (unsigned char)(((ul_val >> 10) & 0x1f) * 0xff / 0x1f);
			  *ucp_++ = (unsigned char)(((ul_val >>  5) & 0x1f) * 0xff / 0x1f);
			  *ucp_++ = (unsigned char)(((ul_val      ) & 0x1f) * 0xff / 0x1f);
			 } else {
						   *ucp_++ = (unsigned char)(ul_r & 0xff);
			  if ( (long)1 < l_bpp ) { *ucp_++ = (unsigned char)(ul_g & 0xff); }
			  if ( (long)2 < l_bpp ) { *ucp_++ = (unsigned char)(ul_b & 0xff); }
			  if ( (long)3 < l_bpp ) { *ucp_++ = (unsigned char)(ul_a & 0xff); }
			 }
			}
		}
	 }
	}
	return OK;
}

int tga_read_scanline( TGA_READ *tp_read, int yy, void *vp_scanline )
{
	/*** さまざまチェック ***/

	if (NULL == tp_read) {
		pri_funct_err_bttvr(
			"Error : bad argument, tp_read is NULL." );
		return NG;
	}
	if (NULL == vp_scanline) {
		pri_funct_err_bttvr(
			"Error : bad argument, vp_scanline is NULL." );
		return NG;
	}

	/* オープン済みかどうかをチェック */
	if (NULL == (tp_read->t_bread._fp)) {
		pri_funct_err_bttvr(
			"Error : tp_read->t_bread._fp is NULL." );
		return NG;
	}

	/* yy */ /* の位置チェック */
	if (yy < 0
	||  (tp_read->t_tga_file_header.s_ysize) <= yy) {
		pri_funct_err_bttvr(
		"Error : bad argument, yy<%ld> is out of range.\n",
			yy );
		return NG;
	}

	/*** ファイル読み込み  ***/

	switch (tp_read->t_tga_file_header.uc_imgtyp) {
	case  0: /* no image data included */
		break;
	case  1: /* uncompressed, color_mapped image */
	case  2: /* uncompressed, true_color image */
	case  3: /* uncompressed, black and white image */
		if(OK != _tga_read_scanline_uncompressed(
			tp_read, vp_scanline
		)) {
			pri_funct_err_bttvr(
		"Error : _tga_read_scanline_uncompressed(-) returns NG." );
			return NG;
		}
		break;
	case  9: /* run_length encoded color_mapped image */
	case 10: /* run_length encoded true_color image */
	case 11: /* run_length encoded black and white image */
		if(OK != _tga_read_scanline_runlength(
			tp_read, vp_scanline
		)) {
			pri_funct_err_bttvr(
		"Error : _tga_read_scanline_runlength(-) returns NG." );
			return NG;
		}
		break;
	default:
		pri_funct_err_bttvr(
		"Error : Can't handle this targa uc_imgtyp<%d>.",
			tp_read->t_tga_file_header.uc_imgtyp);
		return NG;
	}
	return OK;
}
