#include <stdlib.h>	/* for free() */
#include "tif.h"

void tif_write_close( TIF_IMAGE_RW *tp_write )
{
	if (NULL != tp_write->vp_tile) {
		free( tp_write->vp_tile );
		tp_write->vp_tile = NULL;
	}
	if (NULL != tp_write->tp_tiff_head) {
		TIFFClose( tp_write->tp_tiff_head );
		tp_write->tp_tiff_head = NULL;
	}
}
