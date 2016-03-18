#ifndef __tga_stat_h__
#define __tga_stat_h__

#include "tga.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int tga_stat_detail( int i_count, char **cpp_name );
extern int tga_stat_column( int i_count, char **cpp_name );
extern void tga_stat_for_pv( TGA_FILE_HEADER *tp_tga );

#ifdef __cplusplus
}
#endif

#endif /* !__tga_stat_h__ */
