#include <limits.h> /* CHAR_BIT */
#include "tif.h"

/* モノクロ２階調画像の上下反転 */
void tif_bw_reverse( long l_w, long l_h, unsigned char *ucharp_image )
{
	long	l_w_bytes;
	long	xx,yy;
	unsigned char *ucharp_top, *ucharp_bottom, uchar_tmp;

	l_w_bytes = l_w/CHAR_BIT + ((l_w%CHAR_BIT)?1:0);
	ucharp_top = ucharp_image;
	ucharp_bottom = ucharp_image + l_w_bytes * (l_h-1L);

	for (yy = 0L; yy < l_h/2; ++yy) {
		for (xx = 0L; xx < l_w_bytes; ++xx) {
			uchar_tmp = ucharp_top[xx];
			ucharp_top[xx] = ucharp_bottom[xx];
			ucharp_bottom[xx] = uchar_tmp;
		}
		ucharp_top += l_w_bytes;
		ucharp_bottom -= l_w_bytes;
	}
}
