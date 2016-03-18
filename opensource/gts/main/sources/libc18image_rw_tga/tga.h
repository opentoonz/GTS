#ifndef __tga_h__
#define __tga_h__

#include <stdio.h>

#include "bread.h"
#include "bwrite.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 2000.04.19
	original Truevision TGA(tm) file structure
	field 1 : 1 bytes
		numbers of characters in ID field
	field 2 : 1 bytes
		color map type
	field 3 : 1 bytes
		image type code
		 0	no image data included
		 1	uncompressed, color_mapped image
		 2	uncompressed, true_color image	
		 3	uncompressed, black and white image
		 9	run_length encoded color_mapped image
		10	run_length encoded true_color image
		11	run_length encoded black and white image
	field 4 : 5 bytes
		color map specification
		field 4.1 : 2 bytes : color map origin
		field 4.2 : 2 bytes : color map length
		field 4.3 : 1 bytes : color map entry size
	field 5 : 10 bytes
		image specification
		field 5.1 : 2 bytes : x origin of image
		field 5.2 : 2 bytes : y origin of image
		field 5.3 : 2 bytes : width of image
		field 5.4 : 2 bytes : height of image
		field 5.5 : 1 bytes : image pixel size
		field 5.6 : 1 bytes : image descriptor bytes
	field 6 : length specified by field 1
		image of field
	field 7 : bit width specified by field 4.3 and
			number of color map entries specified in field 4.2
		color map data
	field 8 : width and height specified in field 5.3 and 5.4
		image data field
*/

/* ファイルヘッダー */
typedef struct _tga_file_header {
	unsigned char	uc_numid;
	unsigned char	uc_maptyp;
	unsigned char	uc_imgtyp;
	short	s_maporig;
	short	s_mapsize;
	unsigned char	uc_mapbits;
	short	s_xorig;
	short	s_yorig;
	short	s_xsize;
	short	s_ysize;
	unsigned char	uc_pixsize;
	unsigned char	uc_imgdes;
} TGA_FILE_HEADER;

/* 読み込みヘッダ */
typedef struct tga_read_{
	BREAD		t_bread;
	TGA_FILE_HEADER	t_tga_file_header;
} TGA_READ;

/* 書き出しヘッダ */
typedef struct tga_write_ {
	BWRITE		t_bwrite;
	TGA_FILE_HEADER	t_tga_file_header;
} TGA_WRITE;

/* 画像読み込みエラー表示define */
#define _r_ui8err(cp)  pri_funct_err_bttvr("Error : bread_ui8(,%s) returns NG.",cp)
#define _r_ui16err(cp) pri_funct_err_bttvr("Error : bread_ui16(,%s) returns NG.",cp)

/* 画像書き出しエラー表示define */
#define _w_ui8err(cp)  pri_funct_err_bttvr("Error : bwrite_ui8(%s,) returns NG.",cp)
#define _w_ui16err(cp) pri_funct_err_bttvr("Error : bwrite_ui16(%s,) returns NG.",cp)

/* 初期化関数 */
extern void tga_init_file_header( TGA_FILE_HEADER *tp_tga_head );

/* 読み込み関数群 */
extern int tga_read_close( TGA_READ *tp_read );
extern void tga_read_init( TGA_READ *tp_read );
extern int tga_read_open( char *cp_fname, TGA_READ *tp_read );
extern int tga_read_scanline( TGA_READ *tp_read, int yy, void *vp_scanline );

/* 書き出し関数群 */
extern int tga_write_close( TGA_WRITE *tp_write );
extern void tga_write_init( TGA_WRITE *tp_write );
extern int tga_write_open( char *cp_fname, TGA_WRITE *tp_write );
extern int tga_write_scanline( long yy, void *vp_scanline, TGA_WRITE *tp_write );
extern int tga_write_setup_header( short s_width, short s_height, short s_samples, short s_bytes, int i_rle_sw, TGA_FILE_HEADER *tp_header );

#ifdef __cplusplus
}
#endif
#endif /* !__tga_h__ */
