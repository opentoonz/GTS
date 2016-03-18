#include <stdlib.h>	/* free() */
#include "tif.h"

void tif_read_close( TIF_IMAGE_RW *tp_read )
{
	tp_read->ui32_image_width = 0;
	tp_read->ui32_image_length = 0;
	tp_read->ui32_tile_width = 0;
	tp_read->ui32_tile_length = 0;
	tp_read->ui16_compression = 0;
	tp_read->ui16_orientation = 0;
	tp_read->ui16_photometric = 0;
	tp_read->ui16_bits_per_sample = 0;
	tp_read->ui16_samples_per_pixel = 0;
	tp_read->ui16_planar_configuration = 0;
	tp_read->f_dpi_x = 0.0;
	tp_read->f_dpi_y = 0.0;
	tp_read->i_tile_sw = 0;
	if (NULL != tp_read->vp_tile) {
		free( tp_read->vp_tile );
		tp_read->vp_tile = NULL;
	}
	if (NULL != tp_read->tp_tiff_head) {
		TIFFClose( tp_read->tp_tiff_head );
		tp_read->tp_tiff_head = NULL;
	}
}
