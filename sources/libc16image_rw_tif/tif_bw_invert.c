#include <limits.h> /* CHAR_BIT */
#include "tif.h"

/* モノクロ２階調画像の白黒反転 */
void tif_bw_invert( long l_w, long l_h, unsigned char *ucharp_image )
{
	long	l_w_bytes;
	long	xx,yy;

	l_w_bytes = l_w/CHAR_BIT + ((l_w%CHAR_BIT)?1:0);

	for (yy = 0L; yy < l_h; ++yy) {
	for (xx = 0L; xx < l_w_bytes; ++xx) {
		ucharp_image[0] = ~ucharp_image[0];
		++ucharp_image;
	}
	}
}
