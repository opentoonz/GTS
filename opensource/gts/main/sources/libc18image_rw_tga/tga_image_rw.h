#ifndef __tga_image_rw_h__
#define __tga_image_rw_h__

#ifdef __cplusplus
extern "C" {
#endif

extern void *tga_image_read( char *cp_fname, long *lp_width, long *lp_height, long *lp_channels, long *lp_bytes, int i_mv_sw, int i_pv_sw, int i_cv_sw );

extern int tga_image_read_header( char *cp_fname, long *lp_width, long *lp_height, long *lp_channels, long *lp_bytes );

extern int tga_image_write( void *vp_image, long l_width, long l_height, long l_channels, long l_bytes, int i_rle_sw, char *cp_fname, int i_mv_sw, int i_pv_sw, int i_cv_sw );

#ifdef __cplusplus
}
#endif

#endif /* !__tga_image_rw_h__ */
