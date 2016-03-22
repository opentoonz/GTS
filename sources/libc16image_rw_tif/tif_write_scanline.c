#include "ptbl_returncode.h"
#include "pri.h"
#include "tif.h"

int tif_write_scanline( uint32_t ui32_yy, void *vp_scanline, TIF_IMAGE_RW *tp_write )
{
	/* チェック */
	if (NULL == tp_write->tp_tiff_head) {
		pri_funct_err_bttvr( "Error : Not opened file." );
		return NG;
	}
	/* バッファのデータを書き出す */
	/**	TIFFWriteScanline(
		tp_write->tp_tiff_head,
		(tdata_t)vp_scanline,
		ui32_yy,
		TIFFScanlineSize(tp_write->tp_tiff_head));**/

	if (1 != TIFFWriteScanline(
		tp_write->tp_tiff_head,
		(tdata_t)vp_scanline,
		ui32_yy,
		(tsample_t)0
	) ) {
		pri_funct_err_bttvr(
			"Error : TIFFWriteScanline(-) returns not 1." );
		return NG;
	}

	return	OK;
}
