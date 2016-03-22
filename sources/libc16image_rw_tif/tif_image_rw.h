#ifndef __tif_image_rw_h__
#define __tif_image_rw_h__

#include "ptbl_stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void *tif_image_read( char *cp_fname,
long *lp_width,
long *lp_height,
long *lp_channels,
long *lp_bytes,
long *lp_bits,
double *dp_dpi_x,
double *dp_dpi_y,
long *lp_tile_width,
long *lp_tile_height,
long *lp_how_to_compression,
long *lp_orientation,
int i_mv_sw, int i_pv_sw, int i_cv_sw );

extern void *tif_image_read_y_manual( char *cp_fname,
long *lp_width,
long *lp_height,
long l_h_read,
long *lp_channels,
long *lp_bytes,
long *lp_bits,
double *dp_dpi_x,
double *dp_dpi_y,
long *lp_tile_width,
long *lp_tile_height,
long *lp_how_to_compression,
long *lp_orientation,
int i_mv_sw, int i_pv_sw, int i_cv_sw );

extern int tif_image_read_header( char *cp_fname,
long *lp_width,
long *lp_height,
long *lp_channels,
long *lp_bytes,
long *lp_bits,
double *dp_dpi_x,
double *dp_dpi_y,
long *lp_tile_width,
long *lp_tile_height,
long *lp_how_to_compression,
long *lp_orientation );

extern int tif_image_write( void *vp_image,
long l_width,
long l_height,
long l_channels,
long l_bytes,
long l_bits,
double d_dpi_x,
double d_dpi_y,
long l_how_to_compression,
long l_lzw_prediction_scheme,
long l_orientation,
long l_byte_swap_mode,
char *cp_fname,
int i_mv_sw, int i_pv_sw, int i_cv_sw );

extern int tif_write_get_i_compression_none( void );
extern int tif_write_get_i_compression_lzw( void );
extern int tif_write_get_i_compression_packbits( void );
extern int tif_write_get_i_compression_faxg4( void );

/*
 * Grayscale,RGB,RGBAの時は"rot0"がデフォルト
 * scannerのrawデータの場合ユーザーの取り方で指定する
 */
extern int tif_write_get_i_orientation_rot0( void );
extern int tif_write_get_i_orientation_rot90( void );
extern int tif_write_get_i_orientation_rot180( void );
extern int tif_write_get_i_orientation_rot270( void );
extern int tif_write_get_i_orientation_botleft_rot0( void );

#ifdef __cplusplus
}
#endif

#endif /* !__tif_image_rw_h__ */
