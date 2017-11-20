#include <cmath> /* floor() */
#include "calc_hsv_rgb.h"

double calc::clamp_cyclic360( double h360 )
{
	while (h360 <    0.) { h360 += 360.; }	/* 0<= */
	while (360. <= h360) { h360 -= 360.; }	/* <360 */
	return h360;
}
void calc::hsv_to_rgb(
	const double h, const double s, const double v
	, double& r, double& g, double& b
) {
	if (s < 1.0e-6) { r = g = b = v; }	/* 無彩色の場合 */
	else {					/* 有彩色の場合 */
		const double h6 = h / 60.; /* Renge 360 --> 6 */
		const int i=static_cast<int>(floor(h6));	/* 整数値 */
		const double f = h6 - i;			/* 小数部 */
		const double p1 = v * (1.0 - s);
		const double p2 = v * (1.0 - s * f);
		const double p3 = v * (1.0 - s * (1.0 - f));
		switch (i) {
		case 0: r = v;   g = p3;  b = p1;  break;
		case 1: r = p2;  g = v;   b = p1;  break;
		case 2: r = p1;  g = v;   b = p3;  break;
		case 3: r = p1;  g = p2;  b = v;   break;
		case 4: r = p3;  g = p1;  b = v;   break;
		case 5: r = v;   g = p1;  b = p2;  break;
		}
	}
}

void calc::rgb_to_hsv(
	const double r, const double g, const double b
	, double& h, double& s, double& v
) {
	/* r,g,bのうちの最大値 */
	double maxv = r > g ? r : g; if (b > maxv) maxv = b;

	/* 明度(Value) */
	v = maxv;

	/* 完全黒の場合 */
	if (v <= 0.) {
		//h = 0.;	/* 無彩色の場合のdefault位置 */
		s = 0.;	/* 無彩色値 */
		return;
	}

	/* r,g,bのうちの最小値 */
	double minv = r < g ? r : g; if (b < minv) minv = b;

	/* 無彩色の場合 */
	if (minv == maxv) {
		//h = 0.;	/* 無彩色の場合のdefault位置 */
		s = 0.;	/* 無彩色値 */
		return;
	}

	/* 有彩色の場合(minv < maxv) */
	s = (maxv - minv) / maxv;

	/* R - Y - G - C - B - M - R
	   0   1   2   3   4   5   <6
	   0  60 120 180 240 300 <360 */

	/* -1〜0〜1 マゼンタ(M)から黄色(Y)までの間の色 */
	if (maxv == r)	{ h = (g - b)/(maxv - minv); if(h<0.){h += 6.;} }
	else

	/*  1〜2〜3 黄色(Y)からシアン(C)までの間の色 */
	if (maxv == g)	{ h = 2.0+(b - r)/(maxv - minv); }

	/*  3〜4〜5 シアン(C)からマゼンタ(M)までの間の色 */
	else		{ h = 4.0+(r - g)/(maxv - minv); }
	h *= 60.; /* Renge 6 --> 360 */
}
