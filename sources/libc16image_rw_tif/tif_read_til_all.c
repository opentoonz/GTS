#include <math.h>	/* ceil() */
#include "ptbl_returncode.h"
#include "pri.h"
#include "tif.h"

int tif_read_til_all( TIF_IMAGE_RW *tp_read, void *vp_image, uint32_t ui32_width, uint32_t ui32_height, uint32_t ui32_tile_width, uint32_t ui32_tile_height, uint16_t ui16_channels, uint16_t ui16_bytes, int i_reverse_sw, int i_cv_sw )
{
	int	i_tile_count,i_tile_size;
	uint8_t  *ui8p_yy, *ui8p_xx;
	uint32_t ui32_yy, ui32_xx;

	i_tile_size =
		(int)ceil( (double)ui32_height / ui32_tile_height ) *
		(int)ceil( (double)ui32_width  / ui32_tile_width  );

	/* カウントダウン表示始め */
	if (ON == i_cv_sw) { pri_funct_cv_start( i_tile_size ); }

	/* .tifファイルの読み込み位置 */
	if (ON == i_reverse_sw) {
	 	/* vp_imageデータのポインターを一番上の行に移動する */
		ui8p_yy = (unsigned char *)vp_image +
			(ui32_height-1) *
			ui32_width *
			ui16_channels *
			ui16_bytes;
	} else {
		ui8p_yy = (unsigned char *)vp_image;
	}

	i_tile_count = 0;
	for (	ui32_yy = 0;
		ui32_yy < ui32_height;
		ui32_yy += ui32_tile_height
	) {
		ui8p_xx = ui8p_yy;
		for (	ui32_xx = 0;
			ui32_xx < ui32_width;
			ui32_xx += ui32_tile_width
		) {
			/* カウントダウン表示中 */
			if (ON == i_cv_sw) {
				pri_funct_cv_run(i_tile_count);
			}
			/* タイル読み込み */
			if (NG == tif_read_tile(
				tp_read, ui32_xx, ui32_yy,
				(void *)ui8p_xx, i_reverse_sw
			)) {
				pri_funct_err_bttvr(
			 "Error : tif_read_tile(,%u,%u,,) returns NG.",
				ui32_xx,ui32_yy );
				return NG;
			}
			ui8p_xx +=
				ui32_tile_width *
				ui16_channels *
				ui16_bytes;
			++i_tile_count;
		}
		if (ON == i_reverse_sw) {
			ui8p_yy -=
				ui32_tile_height *
				ui32_width *
				ui16_channels *
				ui16_bytes;
		} else {
			ui8p_yy +=
				ui32_tile_height *
				ui32_width *
				ui16_channels *
				ui16_bytes;
		}
	 }

	/* カウントダウン表示終了 */
	if (ON == i_cv_sw) { pri_funct_cv_end(); }

	return OK;
}
