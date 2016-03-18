#ifndef __pri_h__
#define __pri_h__

#include "ptbl_stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void pri_funct_cv_start( int32_t i32_ys );
extern void pri_funct_cv_run( int32_t i32_y );
extern void pri_funct_cv_end( void );

extern void pri_funct_set_cp_title( char *cp_title );
extern void pri_funct_err_bttvr( const char* fmt, ...);
extern void pri_funct_msg_v( const char* fmt, ...);
extern void pri_funct_msg_vr( const char* fmt, ...);
extern void pri_funct_msg_ttvr( const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* !__pri_h__ */
