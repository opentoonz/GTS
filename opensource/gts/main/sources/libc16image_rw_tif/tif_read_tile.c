#include "ptbl_returncode.h"
#include "pri.h"

#include "tif.h"

static void _tif_read_tile_convert_8bits_sample( TIF_IMAGE_RW *tp_read, uint8_t *ui8p_in_top, uint8_t *ui8p_out_top, uint32_t ui32_ww, uint32_t ui32_hh, uint32_t ui32_cc, int i_reverse_sw )
{
	uint8_t *ui8p_in_y, *ui8p_out_y,
		*ui8p_in_x, *ui8p_out_x;
	uint32_t ui32_xx, ui32_yy, ui32_zz;
	int	i_in_scanline_size,
		i_out_scanline_size;

	i_in_scanline_size  = (int)tp_read->ui32_tile_width  * ui32_cc;
	i_out_scanline_size = (int)tp_read->ui32_image_width * ui32_cc;

	ui8p_in_y = ui8p_in_top;
	ui8p_out_y = ui8p_out_top;
	for (ui32_yy = 0; ui32_yy < ui32_hh; ++ui32_yy) {
		ui8p_in_x = ui8p_in_y;
		ui8p_out_x = ui8p_out_y;
		for (ui32_xx = 0; ui32_xx < ui32_ww; ++ui32_xx) {
		 for (ui32_zz = 0; ui32_zz < ui32_cc; ++ui32_zz) {
			*ui8p_out_x++ = *ui8p_in_x++;
		 }
		}
		ui8p_in_y += i_in_scanline_size;
		if (ON == i_reverse_sw) {
		 ui8p_out_y -= i_out_scanline_size;
		}
		else {
		 ui8p_out_y += i_out_scanline_size;
		}
	}
}
static void _tif_read_tile_convert_16bits_sample( TIF_IMAGE_RW *tp_read, uint16_t *ui16p_in_top, uint16_t *ui16p_out_top, uint32_t ui32_ww, uint32_t ui32_hh, uint32_t ui32_cc, int i_reverse_sw )
{
	uint16_t *ui16p_in_y, *ui16p_out_y,
		 *ui16p_in_x, *ui16p_out_x;
	uint32_t ui32_xx, ui32_yy, ui32_zz;
	int	i_in_scanline_size,
		i_out_scanline_size;

	i_in_scanline_size  = (int)tp_read->ui32_tile_width  * ui32_cc;
	i_out_scanline_size = (int)tp_read->ui32_image_width * ui32_cc;

	ui16p_in_y = ui16p_in_top;
	ui16p_out_y = ui16p_out_top;
	for (ui32_yy = 0; ui32_yy < ui32_hh; ++ui32_yy) {
		ui16p_in_x = ui16p_in_y;
		ui16p_out_x = ui16p_out_y;
		for (ui32_xx = 0; ui32_xx < ui32_ww; ++ui32_xx) {
		 for (ui32_zz = 0; ui32_zz < ui32_cc; ++ui32_zz) {
			*ui16p_out_x++ = *ui16p_in_x++;
		 }
		}
		ui16p_in_y += i_in_scanline_size;
		if (ON == i_reverse_sw) {
		 ui16p_out_y -= i_out_scanline_size;
		}
		else {
		 ui16p_out_y += i_out_scanline_size;
		}
	}
}

/* タイルフォーマット画像を読む */
int tif_read_tile( TIF_IMAGE_RW *tp_read, uint32_t ui32_xpos, uint32_t ui32_ypos, void *vp_tile, int i_reverse_sw )
{
	uint32_t ui32_ww, ui32_hh;

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
	if (NULL == tp_read->vp_tile ) {
		pri_funct_err_bttvr(
	"Error : bad argument, tp_read->vp_tile is NULL." );
		return NG;
	}

	/* TIFF ライブラリで読み込む */
	if ( -1 == TIFFReadTile(
		tp_read->tp_tiff_head, (tdata_t)tp_read->vp_tile,
		ui32_xpos, ui32_ypos, 0, (tsample_t)0
	)) {
		pri_funct_err_bttvr(
	  "Error : TIFFReadTile(,,%u,%u,,) returns minus.",
			ui32_xpos,
			ui32_ypos );
		return NG;
	}

	/* タイルがエリア外のときの対処 (2000.11.7)*/
	if ((tp_read->ui32_image_width  - ui32_xpos)
	<    tp_read->ui32_tile_width) {
		ui32_ww = tp_read->ui32_image_width  - ui32_xpos;
	} else {
		ui32_ww = tp_read->ui32_tile_width;
	}
	if ((tp_read->ui32_image_length - ui32_ypos)
	<    tp_read->ui32_tile_length) {
		ui32_hh = tp_read->ui32_image_length - ui32_ypos;
	} else {
		ui32_hh = tp_read->ui32_tile_length;
	}

	/* 読み込んだタイルデータを画像バッファに移す */
	if (8 == tp_read->ui16_bits_per_sample) {
		_tif_read_tile_convert_8bits_sample(
			tp_read,
			(uint8_t *)tp_read->vp_tile,
			(uint8_t *)vp_tile,
			ui32_ww, ui32_hh,
			(uint32_t)(tp_read->ui16_samples_per_pixel),
			i_reverse_sw
		);
	}
	else if (16 == tp_read->ui16_bits_per_sample) {
		_tif_read_tile_convert_16bits_sample(
			tp_read,
			(uint16_t *)tp_read->vp_tile,
			(uint16_t *)vp_tile,
			ui32_ww, ui32_hh,
			(uint32_t)(tp_read->ui16_samples_per_pixel),
			i_reverse_sw
		);
	}

	return OK;
}
