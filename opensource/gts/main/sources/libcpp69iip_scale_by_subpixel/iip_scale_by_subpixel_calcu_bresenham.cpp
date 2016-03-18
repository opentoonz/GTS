#include <assert.h>
#include "iip_scale_by_subpixel.h"

void iip_scale_by_subpixel::_calcu_bresenham( long l_dx, long l_dy, long *lp_y, long l_inc )
{
	long l_pos_crnt,l_pos_bu;
	long yy;

	/* どちらか大きさがないときは無効 */
	assert(0 <= l_dx);
	assert(0 <= l_dy);

	/* l_dxよりl_dyが小さいときは無効 */
	assert(l_dx <= l_dy);

	/* y方向に傾いている
	    y +      *          +---+
	      |     *           |inc|
	      |    *            |inc|
	      |   *             | 0 |
	  OUT +   *             |inc|
	      |  *              |inc|
	      | *               |inc|
	      |*                |inc|
	    0 +---+---+---+	+---+
	      0           x
                   IN
	*/
	if (l_dx <= l_dy) {
		l_pos_bu = 0L;
		for (yy = 0L; yy < l_dy; ++yy) {
			l_pos_crnt = (yy+1L) * (l_dx+1L) / (l_dy+1L);
			if (l_pos_bu < l_pos_crnt) {
				lp_y[yy] = l_inc;
				l_pos_bu = l_pos_crnt;
			} else {
				lp_y[yy] = 0L;
			}
		}
	}
}
