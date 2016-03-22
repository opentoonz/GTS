#include <limits.h>	/* CHAR_BIT */

#include "pri.h"
#include "iip_precision.h"
#include "calcu_precision.h"

void iip_precision::_bw_to_uchargray( long l_width, long l_height, long l_max, unsigned char *ucharp_in_bw, unsigned char *ucharp_out_gray )
{
	long	xx,yy, l_in_bits;

	/* カウントダウン表示始め */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_start(l_height); }

	for (yy = 0L; yy < l_height; ++yy) {
	 /* カウントダウン表示中 */
	 if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }

	 for (l_in_bits = 0x80,xx = 0L; xx < l_width; ++xx) {
		if (ucharp_in_bw[0] & l_in_bits) {
			ucharp_out_gray[0] = (unsigned char)l_max;
		} else {
			ucharp_out_gray[0] = 0L;
		}

		if (	((CHAR_BIT-1) == (xx%CHAR_BIT)) ||
			((l_width-1) <= xx)
		) {
			++ucharp_in_bw;
			l_in_bits = 0x80;
		} else {l_in_bits >>= 1; }
		++ucharp_out_gray;
	 }
	}

	/* カウントダウン表示終了 */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_end(); }
}
