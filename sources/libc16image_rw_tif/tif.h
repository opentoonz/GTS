#ifndef __tif_h__
#define __tif_h__

#include "tiffio.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _tif_image_rw {
	TIFF	*tp_tiff_head;

	uint32_t ui32_image_width, ui32_image_length;
	uint32_t ui32_tile_width, ui32_tile_length;
	uint16_t ui16_compression;
	uint16_t ui16_orientation;
	uint16_t ui16_photometric;
	uint16_t ui16_bits_per_sample;
	uint16_t ui16_samples_per_pixel;
	uint16_t ui16_planar_configuration;
	float	f_dpi_x;
	float	f_dpi_y;

	int	i_tile_sw;
	void	*vp_tile;	/* read時はtile用バッファ、
				   write時はスキャンライン用バッファ */
} TIF_IMAGE_RW;

/* ヘッダー初期化関数 */
extern void tif_init_rw_header( TIF_IMAGE_RW *tp_rw_header );

/* 画像読み込み関数群 */
extern void tif_read_close( TIF_IMAGE_RW *tp_read );
extern int tif_read_get_reverse_sw( TIF_IMAGE_RW *tp_read );
extern int tif_read_open( char *cp_fname, TIF_IMAGE_RW *tp_read ) ;
extern int tif_read_sca_all( TIF_IMAGE_RW *tp_read, void *vp_image, uint32_t ui32_width, uint32_t ui32_height, uint16_t ui16_channels, uint16_t ui16_bytes, int i_reverse_sw, int i_cv_sw );
extern int tif_read_sca_y( TIF_IMAGE_RW *tp_read, void *vp_image, uint32_t ui32_width, uint32_t ui32_height, uint32_t ui32_h_read, uint16_t ui16_channels, uint16_t ui16_bytes, int i_reverse_sw, int i_cv_sw );
extern int tif_read_scanline( TIF_IMAGE_RW *tp_read, uint32_t yy, void *vp_scanline );
extern int tif_read_til_all( TIF_IMAGE_RW *tp_read, void *vp_image, uint32_t ui32_width, uint32_t ui32_height, uint32_t ui32_tile_width, uint32_t ui32_tile_height, uint16_t ui16_channels, uint16_t ui16_bytes, int i_reverse_sw, int i_cv_sw );
extern int tif_read_tile( TIF_IMAGE_RW *tp_read, uint32_t ui32_xpos, uint32_t ui32_ypos, void *vp_tile, int i_reverse_sw );
extern void tif_bw_invert( long l_w, long l_h, unsigned char *ucharp_image );
extern unsigned char *tif_bw_read( TIF_IMAGE_RW *tp_read, int i_reverse_sw, int i_pv_sw );
extern void tif_bw_reverse( long l_w, long l_h, unsigned char *ucharp_image );
extern int tif_bw_write( long l_width, long l_height, void *vp_image, TIF_IMAGE_RW *tp_write, int i_pv_sw );

/* 画像書き出し関数 */
extern void tif_write_close( TIF_IMAGE_RW *tp_write );
extern int tif_write_header( uint32_t ui32_width, uint32_t ui32_height, uint16_t ui16_samples, uint16_t ui16_bits, float f_dpi_x, float f_dpi_y, int i_how_to_compression, int i_lzw_prediction_scheme, uint16_t ui16_orientation, TIF_IMAGE_RW *tp_write );
extern int tif_write_open( char *cp_fname, int i_byte_swap_mode, TIF_IMAGE_RW *tp_write );
extern int tif_write_scanline( uint32_t ui32_yy, void *vp_scanline, TIF_IMAGE_RW *tp_write );

#ifdef __cplusplus
}
#endif

#endif /* !__tif_h__ */
