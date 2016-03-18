#include <stdlib.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tif.h"

int tif_read_sca_y( TIF_IMAGE_RW *tp_read, void *vp_image, uint32_t ui32_width, uint32_t ui32_height, uint32_t ui32_h_read, uint16_t ui16_channels, uint16_t ui16_bytes, int i_reverse_sw, int i_cv_sw )
{
	uint8_t  *ui8p;
	uint32_t ui32_yy, ui32_y_read;

	/* カウントダウン表示始め */
	if (ON == i_cv_sw) {
		pri_funct_cv_start( ui32_h_read );
	}

	/* .tifファイルの読み込み位置 */
	if (ON == i_reverse_sw) {
	 	/* vp_imageデータのポインターを一番上の行に移動する */
		ui8p = (uint8_t *)vp_image +
			(ui32_h_read-1) *
			(ui32_width) *
			(ui16_channels) *
			(ui16_bytes);
	} else {
		ui8p = (uint8_t *)vp_image;
	}

	for (ui32_y_read=ui32_yy=0; ui32_y_read < ui32_h_read;) {

		/* カウントダウン表示中 */
		if (ON == i_cv_sw) { pri_funct_cv_run(ui32_y_read); }

		/* スキャンライン分の画像を読む */
		if (NG == tif_read_scanline(
			tp_read, ui32_yy, (void *)ui8p
		)) {
			pri_funct_err_bttvr(
		 "Error : tif_read_scanline(,%u,) returns NG.",
				ui32_yy );
			return NG;
		}

		/* 次のスキャンライン位置へ設定 */
		if (ON == i_reverse_sw) {
		 /* ポインターを下へ１行移動する */
		 ui8p -= (ui32_width) * (ui16_channels) * (ui16_bytes);
		} else {
		 ui8p += (ui32_width) * (ui16_channels) * (ui16_bytes);
		}
		/* 次へのカウント */
		++ui32_y_read;
		ui32_yy = (ui32_height-1)*ui32_y_read/(ui32_h_read-1);
	}

	/* カウントダウン表示終了 */
	if (ON == i_cv_sw) { pri_funct_cv_end(); }

	return OK;
}
