#include <math.h> /* floor() */
#include "calcu_rgb_to_hsv.h"

/*
 *** in  ***
 色相 (Hue)        double h is 0.0...360.0
 彩度 (Saturation) double s is 0.0...1.0
 明度 (Value)      double v is 0.0...1.0
 *** out ***
 double *r is 0.0...1.0
 double *g is 0.0...1.0
 double *b is 0.0...1.0
*/
void calcu_rgb_to_hsv::from_hsv(double h, double s, double v, double *r, double *g, double *b)
{
	double	f,p,q,t,i;

	/* 無彩色の場合 */
	if (0.0 == s) { *r = *g = *b = v; }

	/* 有彩色の場合 */
	else {
		if (360.0 <= h) { h -= 360.0; }

		h /=60.0; /* 0〜359.999... --> 0〜5.999... */

		i = floor( h ); /* 最大整数値 */
		f = h - i; /* hの小数部 */

		p = v * (1.0 - s);
		q = v * (1.0 - (s * f));
		t = v * (1.0 - (s * (1.0 - f)));

		switch ((int)i) {
		case 0: *r = v; *g = t; *b = p; break;
		case 1: *r = q; *g = v; *b = p; break;
		case 2: *r = p; *g = v; *b = t; break;
		case 3: *r = p; *g = q; *b = v; break;
		case 4: *r = t; *g = p; *b = v; break;
		case 5: *r = v; *g = p; *b = q; break;
		}
	}
}
