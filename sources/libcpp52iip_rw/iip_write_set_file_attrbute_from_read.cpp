#include <stdio.h>
#include <assert.h>
#include "iip_read.h"
#include "iip_write.h"

void iip_write::set_file_attrbute_from_read( iip_read *clp )
{
	/* 引数(親)がNULLであってはならない */
	assert(NULL != clp);

	this->_d_tif_dpi_x       = clp->get_d_tif_dpi_x();
	this->_d_tif_dpi_y       = clp->get_d_tif_dpi_y();
	this->_l_tif_compression = clp->get_l_tif_compression();
	this->_l_tif_orientation = clp->get_l_tif_orientation();
}
