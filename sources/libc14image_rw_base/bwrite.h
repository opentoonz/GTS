#ifndef __bwrite_h__
#define __bwrite_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bwrite {
	FILE	*_fp;
	int	_i_byte_swap_sw;
} BWRITE;

extern void bwrite_init_head( BWRITE *tp_ );
extern void bwrite_set_byte_swap_sw( int sw, BWRITE *tp_ );
extern int bwrite_get_byte_swap_sw( BWRITE *tp_ );
extern int bwrite_open( char *cp_fname, BWRITE *tp_ );
extern int bwrite_close( BWRITE *tp_ );
extern int bwrite_seek( BWRITE *tp_, long l_pos );
extern int bwrite_ui8( uint8_t *ui8p, BWRITE *tp_ );
extern int bwrite_ui16( uint8_t *ui8p, BWRITE *tp_ );
extern int bwrite_ui32( uint8_t *ui8p, BWRITE *tp_ );
extern int bwrite_ui8array( int32_t i32_size, uint8_t *ui8p, int32_t i32_incr, BWRITE *tp_ );
extern int bwrite_ui16array( int32_t i32_size, uint8_t *ui8p, int32_t i32_incr, BWRITE *tp_ );
extern int bwrite_ui32array( int32_t i32_size, uint8_t *ui8p, int32_t i32_incr, BWRITE *tp_ );

#ifdef __cplusplus
}
#endif

#endif /* __bwrite_h__ */
