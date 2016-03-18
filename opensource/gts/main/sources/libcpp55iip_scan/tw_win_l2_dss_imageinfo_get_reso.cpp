#include "pri.h"
#include "tw_win_l2_dss.h"

/* get resolution */
int tw_win_l2_dss::imageinfo_get_dp_reso( double *dp_dpi_x, double *dp_dpi_y )
{
	TW_IMAGEINFO tw_imageinfo;

	if (OK != this->_imageinfo_get( &tw_imageinfo )) {
		pri_funct_err_bttvr(
	 "Error : this->_get_imageinfo(-) returns NG" );
		return NG;
	}
	this->_fix32_to_double( &(tw_imageinfo.XResolution),dp_dpi_x );
	this->_fix32_to_double( &(tw_imageinfo.YResolution),dp_dpi_y );

	return OK;
}
