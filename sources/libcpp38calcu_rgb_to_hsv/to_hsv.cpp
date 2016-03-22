#include "calcu_rgb_to_hsv.h"
/*
 *** in  ***
 double r is 0.0...1.0
 double g is 0.0...1.0
 double b is 0.0...1.0
 *** out ***
 double *h is 0.0...360.0
 double *s is 0.0...1.0
 double *v is 0.0...1.0
*/
void calcu_rgb_to_hsv::to_hsv(double r, double g, double b, double *h, double *s, double *v)
{
	double min, max;

	/* r,g,bのうちの最大値 */
	max = r;
	if (max < g) max = g;
	if (max < b) max = b;

	/* r,g,bのうちの最小値 */
	min = r;
	if (g < min) min = g;
	if (b < min) min = b;

	/* 明度(Value) */
	*v = max;

	/* 彩度(Saturation) */
	if (min < max) { *s = (max - min) / max; } /* 有彩色 */
	else           { *s = 0.0;} /* 無彩色 */

	/* 色相(Hue) */
	if (0.0==(*s)) { *h = 0.0; }/* sがゼロのときhは意味を持たない */
	else {
		/* R - Y - G - C - B - M - R
			  0 = R
			 60 = Y
			120 = G
			180 = C
			240 = B
			300 = M
			360 = R
		*/

		/* -1 .. 1 マゼンタ(M)から黄色(Y)までの間の色 */
		if (r == max)	   *h =       (g - b) / (max - min);

		/*  1 .. 3 黄色(Y)からシアン(C)までの間の色 */
		else if (g == max) *h = 2.0 + (b - r) / (max - min);

		/*  3 .. 5 シアン(C)からマゼンタ(M)までの間の色 */
		else if (b == max) *h = 4.0 + (r - g) / (max - min);

		/* -60 ... 300 */
		*h = *h * 60.0;

		if (*h < 0.0) { *h += 360.0; }
	}
}
