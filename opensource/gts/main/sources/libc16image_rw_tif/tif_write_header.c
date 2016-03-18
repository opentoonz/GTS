#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"
#include "tif_image_rw.h"

/*
開くことのできるTIFFファイルの種類
	画像種類	samples	bits
	---------------+-------+----
	B/W		1	1
	grayscale	1	8/16
	RGB		3/4	8/16
	RGBA		3/4	8/16
	---------------+-------+----
*/
/* i_tiff_lzw_prediction_scheme is 1 or 2 (default is 1) */

int tif_write_header( uint32_t ui32_width, uint32_t ui32_height, uint16_t ui16_samples, uint16_t ui16_bits, float f_dpi_x, float f_dpi_y, int i_how_to_compression, int i_lzw_prediction_scheme, uint16_t ui16_orient, TIF_IMAGE_RW *tp_write )
{
	uint32 rowsperstrip = (uint32)-1;

	/* 値のチェック */
	if (ui32_width < 1) {
		pri_funct_err_bttvr(
			"Error : bad ui32_width<%d>.", ui32_width );
		return NG;
	}
	if (ui32_height < 1) {
		pri_funct_err_bttvr(
			"Error : bad ui32_height<%d>.", ui32_height );
		return NG;
	}
	if ((1 != ui16_samples)
	&&  (3 != ui16_samples)
	&&  (4 != ui16_samples)) {
		pri_funct_err_bttvr(
			"Error : bad ui16_samples<%ld>.", ui16_samples);
		return NG;
	}
	if ((1 != ui16_bits)
	&&  (8 != ui16_bits)
	&&  (16 != ui16_bits)) {
		pri_funct_err_bttvr(
			"Error : bad ui16_bits<%ld>.", ui16_bits );
		return NG;
	}
	if (i_how_to_compression < COMPRESSION_NONE) {
		pri_funct_err_bttvr(
			"Error : bad i_how_to_compression<%d>.",
			i_how_to_compression );
		return NG;
	}

	tp_write->ui32_image_width = ui32_width;
	tp_write->ui32_image_length = ui32_height;
	tp_write->ui16_compression = (uint16_t)i_how_to_compression;

	/* モノクロ２階調(Fax G4)
	photoshop 8.0.1で白黒２値化画像を保存すると、
	ゼロを白、1を黒(PHOTOMETRIC_MINISWHITE)となっている。
	それにあわせる
	*/
	if (1 == ui16_bits) {
	 tp_write->ui16_photometric = PHOTOMETRIC_MINISWHITE;
	}
	/* Grayscale */
	else if (1 == ui16_samples) {
	 tp_write->ui16_photometric = PHOTOMETRIC_MINISBLACK;
	}
	/* フルカラー(RGB, RGBA)画像 */
	else {
	 tp_write->ui16_photometric = PHOTOMETRIC_RGB;
	}

	tp_write->ui16_bits_per_sample = ui16_bits;
	tp_write->ui16_samples_per_pixel = ui16_samples;
	tp_write->ui16_planar_configuration = PLANARCONFIG_CONTIG;
	tp_write->f_dpi_x = f_dpi_x;
	tp_write->f_dpi_y = f_dpi_y;
	tp_write->ui16_orientation = ui16_orient;

	/**********************************************************/

	/* 固定ヘッダー値設定 */
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_IMAGEWIDTH,
				      tp_write->ui32_image_width );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_IMAGELENGTH,
				      tp_write->ui32_image_length );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_PLANARCONFIG,
				tp_write->ui16_planar_configuration);

	/* 1996/Oct/23
		photoshop の表示では、
			ORIENTATION_BOTLEFT にすると反転して表示する
		photoshop は、
			ORIENTATION_TOPLEFT しか
		受け付けないようだ。
	*/

	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_ORIENTATION,
				       tp_write->ui16_orientation );

	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_PHOTOMETRIC,
				       tp_write->ui16_photometric );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_SAMPLESPERPIXEL,
				     tp_write->ui16_samples_per_pixel );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_BITSPERSAMPLE,
				     tp_write->ui16_bits_per_sample );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_XRESOLUTION,
						tp_write->f_dpi_x );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_YRESOLUTION,
						tp_write->f_dpi_y );
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_RESOLUTIONUNIT,
						RESUNIT_INCH );

	/* i_how_to_compression is
		COMPRESSION_NONE/COMPRESSION_LZW/COMPRESSION_PACKBITS...
	*/
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_COMPRESSION,
				       tp_write->ui16_compression );

	/* LZW圧縮のとき予測動作を実行して圧縮効率をあげます */
	if (COMPRESSION_LZW == i_how_to_compression) {
		/*
		(注意)2004.09.14.tue
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
		/* prediction scheme w/ LZW */
		TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_PREDICTOR,
					i_lzw_prediction_scheme );
	}

	/* Fax G4 */
	/***if (1 == ui16_bits) {
		TIFFSetField( tp_write->tp_tiff_head,
			TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
	}***/

	if (1 == ui16_bits) {
		TIFFSetField( tp_write->tp_tiff_head,
			TIFFTAG_ROWSPERSTRIP,
			tp_write->ui32_image_length );
	}
	else {
		/*
		これがないと、
		正常終了するのに、読めないファイルになる
		(2000.04.05)
		*/
		TIFFSetField( tp_write->tp_tiff_head,
			TIFFTAG_ROWSPERSTRIP,
			TIFFDefaultStripSize(
				tp_write->tp_tiff_head, rowsperstrip
			)
		);
	}

/*TIFFSetField( tp_write->tp_tiff_head,TIFFTAG_ROWSPERSTRIP, ui32_height);*/

/* Example about imginfo : Page Size (x,y,z,c):    256, ?, 1, 3
	TIFFSetField( tp_write->tp_tiff_head, TIFFTAG_SUBFILETYPE, 0);
 For same to photoshop_v3.0.1(IRIX) */

	return OK;
}
