#ifndef __ptbl_stdint_h__
#define __ptbl_stdint_h__

/* 固定ビット数の整数変数の定義 */

/* Windowsではstdint.hが見つからない */
#if defined _WIN32
typedef signed char		int8_t;
typedef short int		int16_t;
typedef int			int32_t;
typedef unsigned char		uint8_t;
typedef unsigned short int	uint16_t;
typedef unsigned int		uint32_t;
#else
# include <stdint.h>
#endif

#endif /* !__ptbl_stdint_h__ */
