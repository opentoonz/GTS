#ifndef __bread_h__
#define __bread_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bread {
	FILE	*_fp;
	int	_i_byte_swap_sw;
} BREAD;

extern void bread_init_head( BREAD *tp_ );
extern void bread_set_byte_swap_sw( int sw, BREAD *tp_ );
extern int bread_get_byte_swap_sw( BREAD *tp_ );
extern int bread_open( char *cp_fname, BREAD *tp_ );
extern int bread_close( BREAD *tp_ );
extern int bread_seek( BREAD *tp_, long l_pos );
extern int bread_ui8( BREAD *tp_, uint8_t *ui8p );
extern int bread_ui16( BREAD *tp_, uint8_t *ui8p );
extern int bread_ui32( BREAD *tp_, uint8_t *ui8p );
extern int bread_ui8array( BREAD *tp_, int32_t i32_size, uint8_t *ui8p, int32_t i32_incr );
extern int bread_ui16array( BREAD *tp_, int32_t i32_size, uint8_t *ui8p, int32_t i32_incr );
extern int bread_ui32array( BREAD *tp_, int32_t i32_size, uint8_t *ui8p, int32_t i32_incr );

#ifdef __cplusplus
}
#endif

#endif /* __bread_h__ */
