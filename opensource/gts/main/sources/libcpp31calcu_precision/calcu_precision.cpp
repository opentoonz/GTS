#include <math.h>	/* floor() */
#include <limits.h>	/* CHAR_BIT */

#include "ptbl_returncode.h"
#include "calcu_precision.h"

/* バイトでの最大整数値を得る */
unsigned long calcu_precision::bytes_to_max( unsigned long ul_bytes )
{
	if (ul_bytes < sizeof(unsigned long)) {
		return (1UL << (CHAR_BIT * ul_bytes)) - 1UL;
	}
	/* オーバーフローを防ぐため別処理 */
	else if (ul_bytes == sizeof(unsigned long)) {
		return 0xffffffffUL;
	}
	/* 処理できない値(sizeof(unsigned long)より大きい))
	の場合 */
	return 0UL;
}

/* 最大整数値から倍精度浮動小数値の最大値を得る */
/* doubleの16桁精度に考慮して計算すること、
   ★doubleの15桁の精度を越えたとき、繰り上がってしまう。
   詳細は"history.txt"(2005.01.24) */
double calcu_precision::max_to_double( unsigned long ul_max )
{
	if      (1000000000UL<=ul_max){return (double)ul_max+0.999999;}
	else if (100000000UL<=ul_max){return (double)ul_max+0.9999999;}
	else if (10000000UL<=ul_max){return (double)ul_max+0.99999999;}
	else if (1000000UL<=ul_max){return (double)ul_max+0.999999999;}
	else if (100000UL<=ul_max){return (double)ul_max+0.9999999999;}
	else if (10000UL<=ul_max){return (double)ul_max+0.99999999999;}
	else if (1000UL<=ul_max){return (double)ul_max+0.999999999999;}
	else if (100UL<=ul_max){return (double)ul_max+0.9999999999999;}
	else if (10UL<=ul_max){return (double)ul_max+0.99999999999999;}
	else if (1UL<=ul_max){return (double)ul_max+0.999999999999999;}
	else return 0.0;
}

/* 0〜1.0値(d_val)を、
最大数(d_max)を元にして整数にする */
unsigned long calcu_precision::dbl_to_ul_by_dmax( double d_val, double d_max )
{
	return (unsigned long)floor( d_val * d_max );
}
