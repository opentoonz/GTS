#include "tiffio.h"
#include <limits.h>	// CHAR_BIT
#include <iostream>
namespace {
 int write_tif_(
	const int height
	,const int width
	,const int channels
	,const int bits
	,const double dpi
	,void *image
	,const char *file_path
	,const bool bottom_left_is_origin_sw=false//def. Top Left is origin of image
 ) {
	/* TIFFファイルを保存のため開く
		バイトオーダー "w"=CPU依存,"wl"=LittleEndian, "wb"=BigEndian
	*/
	TIFF *tiff_head = TIFFOpen( file_path, "w" );

	/* 必須タグの設定 */
	TIFFSetField(tiff_head,TIFFTAG_IMAGEWIDTH,width);
	TIFFSetField(tiff_head,TIFFTAG_IMAGELENGTH,height);
	TIFFSetField(tiff_head,TIFFTAG_BITSPERSAMPLE,bits);
	TIFFSetField(tiff_head,TIFFTAG_COMPRESSION,COMPRESSION_NONE);
	int photometric = 0;
	if (bits == 1) {		/* モノクロ２階調 */
		photometric = PHOTOMETRIC_MINISWHITE;
	} else if (channels == 1) {	/* Grayscale */
		photometric = PHOTOMETRIC_MINISBLACK;
	} else {			/* フルカラー(RGB, RGBA)画像 */
		photometric = PHOTOMETRIC_RGB;
	}
	TIFFSetField(tiff_head,TIFFTAG_PHOTOMETRIC,photometric);
	if (bits == 1) {		/* モノクロ２階調 */
	 TIFFSetField(tiff_head,TIFFTAG_ROWSPERSTRIP,height);
	} else {
	 TIFFSetField(tiff_head,TIFFTAG_ROWSPERSTRIP,
		TIFFDefaultStripSize(tiff_head,(uint32)-1)
	 );
	}
	TIFFSetField(tiff_head,TIFFTAG_XRESOLUTION,dpi);
	TIFFSetField(tiff_head,TIFFTAG_YRESOLUTION,dpi);
	TIFFSetField(tiff_head,TIFFTAG_RESOLUTIONUNIT,RESUNIT_INCH);

	/* 選択タグの設定 */
	TIFFSetField(tiff_head,TIFFTAG_SAMPLESPERPIXEL,channels);
	//TIFFSetField(tiff_head,TIFFTAG_PLANARCONFIG,PLANARCONFIG_SEPARATE);
	TIFFSetField(tiff_head,TIFFTAG_PLANARCONFIG,PLANARCONFIG_CONTIG);
	if (bottom_left_is_origin_sw) {
	 TIFFSetField(tiff_head,TIFFTAG_ORIENTATION,ORIENTATION_BOTLEFT);
	} else {
	 TIFFSetField(tiff_head,TIFFTAG_ORIENTATION,ORIENTATION_TOPLEFT);
	}

	/* 画像保存 */
	int ret = 0;
	if (bits == 1) {		/* モノクロ２階調 */
		const int w_bytes = width/CHAR_BIT + ((width%CHAR_BIT)?1:0);
		if (-1 == TIFFWriteEncodedStrip(
			tiff_head ,0 ,image ,w_bytes*height
		)) {
			std::cerr << "Error : TIFFWriteEncodedStrip(,,,"
				<< w_bytes << "," << height << ")\n";
			ret = -1;
		}
	} else {
		unsigned char *sl = static_cast<unsigned char *>(image);
		for (int yy = 0 ;yy < height ;++yy
		,sl += width * channels * bits / CHAR_BIT) {
		 if (1 != TIFFWriteScanline(
			tiff_head ,sl ,yy ,(tsample_t)0
		 )) {
			std::cerr << "Error : TIFFWriteScanline(,,"
				<< yy << ",)\n";
			ret = -1;
		 }
		}
	}

	/* TIFFファイル閉じる */
	TIFFClose( tiff_head );

	return ret;
 }
}
#if defined DEBUG_WRITE_TIF
int main(int argc ,char *argv[]) {
	if (argc != 7) {
		std::cout << "Usage : " << argv[0]
			<< " h w channels bits dpi path\n";
		return 1;
	}
	const int height	= atoi( argv[1] );
	const int width		= atoi( argv[2] );
	const int channels	= atoi( argv[3] );
	const int bits		= atoi( argv[4] );
	const double dpi	= atof( argv[5] );
	const char *file_path	= argv[6];

	int scanline_bytes = 0;
	if (bits == 1) {		/* モノクロ２階調 */
		scanline_bytes = width/CHAR_BIT + ((width%CHAR_BIT)?1:0);
	} else {
		scanline_bytes = width*bits/CHAR_BIT;
	}
	void *image = calloc( height ,scanline_bytes );
	if (image == 0) {
		return 2;
	}

	const int ret = write_tif_(
		height ,width ,channels ,bits ,dpi ,image ,file_path
	);

	free (image);

	return ret;
}
#endif  /* !DEBUG_WRITE_TIF */
/*
rem :121,122 w! tes_tif_write.bat
cl /W4 /WX /MD /EHa /O2 /wd4819 /DDEBUG_WRITE_TIF /I%HOMEDRIVE%%%HOMEPATH%\utility_tools\vc2010md\x86\tiff-4.0.9\include tes_tif_write.cxx %HOMEDRIVE%%%HOMEPATH%\utility_tools\vc2010md\x86\tiff-4.0.9\lib\libtiff.lib /Fetes_tif_write
*/
