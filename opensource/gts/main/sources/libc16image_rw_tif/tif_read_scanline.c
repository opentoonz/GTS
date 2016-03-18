#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"

/*
	スキャンラインフォーマット画像の、
	1スキャンライン分のみ、読み込む
	なお、
	Compression algorithm does not support random access.
	つまり、圧縮フォーマットの場合は、
	ゼロライン(yy=0)から順にとらないと読み込めない
	vp_scanlineは読み込み始める場所へのポインター
*/
int tif_read_scanline( TIF_IMAGE_RW *tp_read, uint32_t yy, void *vp_scanline )
{
	if (NULL == tp_read ) {
		pri_funct_err_bttvr(
			"Error : bad argument, tp_read is NULL." );
		return NG;
	}
	if (NULL == tp_read->tp_tiff_head ) {
		pri_funct_err_bttvr(
	"Error : bad argument, tp_read->tp_tiff_head is NULL." );
		return NG;
	}
	if (NULL == vp_scanline ) {
		pri_funct_err_bttvr(
			"Error : bad argument, vp_scanline is NULL." );
		return NG;
	}

	if ( -1 == TIFFReadScanline(
		tp_read->tp_tiff_head,
		/*(tdata_t)*/vp_scanline, yy, (tsample_t)0
	) ) {
		pri_funct_err_bttvr(
	  "Error : TIFFReadScanline(%p,%p,%u,0) returns minus.",
			tp_read->tp_tiff_head, vp_scanline, yy );
		return NG;
	}
	return OK;
}
