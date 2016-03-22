#include <stdio.h>
#include "tif.h"

void tif_init_rw_header( TIF_IMAGE_RW *tp_rw_header )
{
	tp_rw_header->tp_tiff_head = NULL;

	tp_rw_header->ui32_image_width = 0;
	tp_rw_header->ui32_image_length = 0;
	tp_rw_header->ui32_tile_width = 0;
	tp_rw_header->ui32_tile_length = 0;
	tp_rw_header->ui16_compression = 0;
	tp_rw_header->ui16_orientation = 0;
	tp_rw_header->ui16_photometric = 0;
	tp_rw_header->ui16_bits_per_sample = 0;
	tp_rw_header->ui16_samples_per_pixel = 0;
	tp_rw_header->ui16_planar_configuration = 0;
	tp_rw_header->f_dpi_x = 0.0;
	tp_rw_header->f_dpi_y = 0.0;

	tp_rw_header->i_tile_sw = 0;
	tp_rw_header->vp_tile = NULL; /* read時はtile用バッファ、
		write時は2byteスキャンラインbyte-swap用バッファ */
}
