#ifndef __calcu_precision_h__
#define __calcu_precision_h__

#include <math.h>	/* floor() */
#include <limits.h>	/* CHAR_BIT */

class calcu_precision {
public:
	/* バイトでの最大整数値を得る */
	unsigned long bytes_to_max( unsigned long ul_bytes );

	/* 最大整数値から倍精度浮動小数値の最大値を得る */
	/* doubleの16桁精度に考慮して計算すること、
	   ★doubleの15桁の精度を越えたとき、繰り上がってしまう。
	   詳細は"history.txt"(2005.01.24) */
	double max_to_double( unsigned long ul_max );

	/* 0〜1.0値(d_val)を、
	最大数(d_max)を元にして整数にする */
	unsigned long dbl_to_ul_by_dmax( double d_val, double d_max );
private:
};

#endif /* !__calcu_precision_h__ */
