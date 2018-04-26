#include <stdio.h>
#include <stdlib.h>	/* calloc() */
#include "ptbl_returncode.h"
#include "pri.h"
#include "tif.h"

static int _tif_read_head( TIF_IMAGE_RW *tp_read )
{
	/* compressionモード */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_COMPRESSION,
	&(tp_read->ui16_compression) );

	/* 原点位置モード */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_ORIENTATION,
	&(tp_read->ui16_orientation) );

	/* 幅 */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_IMAGEWIDTH,
	&(tp_read->ui32_image_width) );

	/* 高さ */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_IMAGELENGTH,
	&(tp_read->ui32_image_length) );

	/* 画像種類 */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_PHOTOMETRIC,
	&(tp_read->ui16_photometric) );

	/* １サンプルあたりのビット数(B/Wなら1,RGBなら8) */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_BITSPERSAMPLE,
	&(tp_read->ui16_bits_per_sample) );

	/* １ピクセルが何サンプル(channels)(RGBなら3) */
	TIFFGetField/*Defaulted*/( tp_read->tp_tiff_head,
		TIFFTAG_SAMPLESPERPIXEL,
	&(tp_read->ui16_samples_per_pixel) );

	/* PLANARCONFIG_CONTIG(単一面画像)/
	   PLANARCONFIG_SEPARATE(分割面画像)
	*/
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_PLANARCONFIG,
	&(tp_read->ui16_planar_configuration) );

	/* dpi */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_XRESOLUTION, &(tp_read->f_dpi_x) );
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_YRESOLUTION, &(tp_read->f_dpi_y) );

	/* タイル幅 */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_TILEWIDTH,
	&(tp_read->ui32_tile_width));

	/* タイル高さ */
	TIFFGetField( tp_read->tp_tiff_head,
		TIFFTAG_TILELENGTH,
	&(tp_read->ui32_tile_length));

	/* タイルフォーマットか否か */
	tp_read->i_tile_sw = TIFFIsTiled( tp_read->tp_tiff_head );

	return OK;
}

static int _tif_read_check_header( TIF_IMAGE_RW *tp_read )
{
	/* ヘッダー情報をチェック */

	/* 原点位置モード */
	switch (tp_read->ui16_orientation) {
	case ORIENTATION_TOPLEFT:
	case ORIENTATION_TOPRIGHT:
	case ORIENTATION_LEFTTOP:
	case ORIENTATION_RIGHTTOP:
	case ORIENTATION_BOTRIGHT:
	case ORIENTATION_BOTLEFT:
	case ORIENTATION_RIGHTBOT:
	case ORIENTATION_LEFTBOT:
	case 0: /* zero is made in photoshop does it? */
		break;
	default:
/***		pri_funct_msg_ttvr(
	"Warning : bad orientation<%u>, made in photoshop does it?.",
			(tp_read->ui16_orientation) );***/
		break;
	}

	/* 単一面画像／分割面画像モード */
	switch (tp_read->ui16_planar_configuration) {
	case PLANARCONFIG_CONTIG:	break;
	case PLANARCONFIG_SEPARATE:	break;
	default:
		pri_funct_err_bttvr(
		"Error : bad planarconfig<%u>, Must be <%d>or<%d>.",
			tp_read->ui16_planar_configuration,
			PLANARCONFIG_CONTIG,
			PLANARCONFIG_SEPARATE );
		return NG;
	}

	/* 画像パラメータチェック
		tp_read->ui16_samples_per_pixel
		tp_read->ui16_bits_per_sample
	*/
	switch (tp_read->ui16_photometric) {
	/* photometricが単チャンネルの場合 */
	case PHOTOMETRIC_MINISWHITE:
	case PHOTOMETRIC_MINISBLACK:
	case PHOTOMETRIC_PALETTE:
		/* サンプル数は一つでなければならない */
		if ( 1 != (tp_read->ui16_samples_per_pixel) ) {
			pri_funct_err_bttvr(
 "Error : bad ui16_samples_per_pixel<%u> in ui16_photometric<%u>.",
				(tp_read->ui16_samples_per_pixel),
				(tp_read->ui16_photometric) );
			return NG;
		}
		/* ビット数(1サンプルあたり)が、1,8,16(,32)のどれかで
		なければならない */
		if (
		    ( (long)1 != (long)(tp_read->ui16_bits_per_sample) )
		&&  ( (long)8 != (long)(tp_read->ui16_bits_per_sample) )
		&&  ((long)16 != (long)(tp_read->ui16_bits_per_sample) )
		) {
			pri_funct_err_bttvr(
	"Error : bad ui16_bits_per_sample<%u> in ui16_photometric<%u>.",
				(tp_read->ui16_bits_per_sample),
				(tp_read->ui16_photometric) );
			return NG;
		}
		break;

	/* photometricが複数チャンネル(フルカラー)の場合 */
	case PHOTOMETRIC_RGB:
		/* サンプル数が、3(RGB)か4(RGBA)でなければならない */
		if (
		    ((long)3 != (long)(tp_read->ui16_samples_per_pixel))
		&&  ((long)4 != (long)(tp_read->ui16_samples_per_pixel))
		) {
			pri_funct_err_bttvr(
	"Error : bad samples_per_pixel<%u> in ui16_photometric<%u>.",
				(tp_read->ui16_samples_per_pixel),
				(tp_read->ui16_photometric) );
			return NG;
		}
		/* ビット数(1サンプルあたり)が、8,16のどれかで
		なければならない */
		if (
		    ( (long)8 != (long)(tp_read->ui16_bits_per_sample) )
		&&  ((long)16 != (long)(tp_read->ui16_bits_per_sample) )
		) {
			pri_funct_err_bttvr(
	"Error : bad ui16_bits_per_sample<%u> in ui16_photometric<%u>.",
				(tp_read->ui16_bits_per_sample),
				(tp_read->ui16_photometric) );
			return NG;
		}

		break;
	default:
		pri_funct_err_bttvr(
			"Error : bad ui16_photometric<%u>.",
			(tp_read->ui16_photometric) );
		return NG;
	}

	return OK;
}

/*
開くことのできるTIFFファイルの種類
	画像種類	samples	bits
	---------------+-------+----
	B/W		1	1
	grayscale	1	8/16
	RGB		3/4	8/16
	RGBA		3/4	8/16
	---------------+-------+----

タイル情報の値
	タイルフォーマットのとき
		lp_tile_width,lp_tile_heightが有効
	スキャンラインフォーマットのとき
		lp_tile_width,lp_tile_heightはゼロ
*/
int tif_read_open( char *cp_fname, TIF_IMAGE_RW *tp_read ) 
{
	/* ヘッダーチェック */
	if (NULL != tp_read->tp_tiff_head) {
		pri_funct_err_bttvr(
		"Error : already opened, at tif_read_open(-)." );
		return NG;
	}

	/* ファイルオープン */
	tp_read->tp_tiff_head = TIFFOpen( cp_fname , "r" );
	if (NULL == tp_read->tp_tiff_head) {
		pri_funct_err_bttvr(
		"Error : TIFFOpen(%s,) returns NULL\n", cp_fname);
		return NG;
	}

	/* ヘッダー情報を得る */
	if (OK != _tif_read_head( tp_read )) {
		pri_funct_err_bttvr(
		"Error : _tif_read_head(-) returns NG." );
		return NG;
	}

	/* ヘッダー情報をチェック */
	if (OK != _tif_read_check_header( tp_read )) {
		pri_funct_err_bttvr(
		"Error : _tif_read_check_header(-) returns NG." );
		return NG;
	}

	/* タイルフォーマットならタイル用一時バッファをとる */
	if (0 != tp_read->i_tile_sw) {
		tp_read->vp_tile = calloc(
			(long)tp_read->ui32_tile_width *
			(long)tp_read->ui32_tile_length *
			(long)tp_read->ui16_samples_per_pixel,
			(long)(tp_read->ui16_bits_per_sample / 8L) );
		if (NULL == tp_read->vp_tile) {
			pri_funct_err_bttvr(
		"Error : calloc(%u x %u x %u,%u) returns NULL.",
				tp_read->ui32_tile_width,
				tp_read->ui32_tile_length,
				tp_read->ui16_samples_per_pixel,
				tp_read->ui16_bits_per_sample / 8);
			return NG;
		}
	}

	return OK;
}
