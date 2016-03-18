#ifndef __tif_stat_h__
#define __tif_stat_h__

#include "tif.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int tif_stat_detail( int i_count, char **cpp_name );
extern int tif_stat_column( int i_count, char **cpp_name );
extern void tif_stat_for_pv( TIF_IMAGE_RW *tp_read );

#ifdef __cplusplus
}
#endif

#endif /* __tif_stat_h__ */
