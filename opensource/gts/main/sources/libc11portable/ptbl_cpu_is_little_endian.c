#include "ptbl_stdint.h"
#include "ptbl_funct.h"

/* カレントシステムのバイトオーダーが
   ビッグインディアンなのかリトルインディアンなのか判定
	little endian なら 1 を返す
	big    endian なら 0 を返す
 */

int ptbl_cpu_is_little_endian( void )
{
	union { int32_t i; int8_t c[4]; } u;
/*
 byte orderの説明
  union uにて、
   int32_t i に1を加えると、
	--------+---------------+--------
   int32_t i	|             1 |
	--------+---------------+--------
		              |
		              v
		+---+---+---+---+
   int8_t c[4]	|   |   |   | 1 |
		+---+---+---+---+
		  0   1   2   3   Big Endian
		              |
		              v
		+---+---+---+---+
   int8_t c[4]	|   |   |   | 1 |
		+---+---+---+---+
		  3   2   1   0   Little Endian
   Big    Endianでは、u.c[3] が 1
   Little Endianでは、u.c[0] が 1
   となる。
*/
	u.i = 1;
	return (1 == u.c[0]);
}

