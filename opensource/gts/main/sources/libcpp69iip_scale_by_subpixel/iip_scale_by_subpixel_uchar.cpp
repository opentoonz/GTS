#include "pri.h"
#include "iip_scale_by_subpixel.h"

/* char byteサンプリングのデータの処理 */
void iip_scale_by_subpixel::_exec_uchar( unsigned char *ucharp_in, unsigned char *ucharp_out, long l_out_width, long l_out_height, long l_out_channels, long l_x_subpixel, long l_y_subpixel, long *lp_width, long *lp_height, long *lp_scanline )
{
	long	l_xy_subpixel;
	long	xx,yy,zz,xs,ys;
	long	*lp_w,
		*lp_scan;
	unsigned char	*ucharp_in_x;

	l_xy_subpixel = l_y_subpixel * l_x_subpixel;

	/* 縦方向へ出力画像のpixel毎移動 */
	for (yy = 0L; yy < l_out_height; ++yy) {

	    /* カウントダウン表示中 */
	    if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }

	    /* subpixel値の積算値をscanline積算配列へ */
	    for (ys = 0L; ys < l_y_subpixel; ++ys) {
		/* 縦のsubpixel毎にscanlineを積算する */
		lp_w = lp_width;
		ucharp_in_x = ucharp_in;
		lp_scan = lp_scanline;

		/* 横方向へ出力画像のpixel毎移動 */
		for (xx = 0L; xx < l_out_width; ++xx) {
		    /* 横方向へ出力画像のsubpixel毎移動 */
		    for (xs = 0L; xs < l_x_subpixel; ++xs) {
			/* 深さ方向の積算 */
			for (zz = 0L; zz < l_out_channels; ++zz) {
				lp_scan[zz] += ucharp_in_x[zz];
			}
			ucharp_in_x += *lp_w++;
		    }
		    lp_scan += l_out_channels;
		}
		ucharp_in += *lp_height++;
	    }

	    /* scanline積算配列から画像配列へ移し変え */
	    lp_scan = lp_scanline;
	    for (xx = 0L; xx < l_out_width; ++xx) {
		for (zz = 0L; zz < l_out_channels; ++zz) {
			*ucharp_out++ = (unsigned char)(
				(*lp_scan) / l_xy_subpixel
			);
			*lp_scan = 0; /* 次のyループのための初期化 */
			++lp_scan;
		}
	    }
	}
}
