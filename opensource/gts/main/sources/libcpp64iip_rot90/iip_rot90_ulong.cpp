#include <stdio.h>

#include "ptbl_returncode.h"
#include "pri.h"
#include "iip_rot90.h"

void iip_rot90::_exec_ulong( long l_width,long l_height,long l_channels, unsigned long *ulongp_in, unsigned long *ulongp_out )
{
	long	xx,yy,zz;

	if (IIP_ROT_CLOCKWORK_090 == this->_e_clockwork) {
	 for (yy = 0L; yy < l_height; ++yy) {
	  if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	  for (xx = 0L; xx < l_width; ++xx) {
	   for (zz = 0L; zz < l_channels; ++zz) {
		 ulongp_out[
			yy * l_channels * l_width +
			xx * l_channels +
			zz
		 ] = ulongp_in[
			xx * l_channels * l_height +
			(l_height - 1L - yy) * l_channels +
			zz
		 ];
	   }
	  }
	 }
	} else if (IIP_ROT_CLOCKWORK_180 == this->_e_clockwork) {
	 for (yy = 0L; yy < l_height; ++yy) {
	  if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	  for (xx = 0L; xx < l_width; ++xx) {
	   for (zz = 0L; zz < l_channels; ++zz) {
		 ulongp_out[
			yy * l_channels * l_width +
			xx * l_channels +
			zz
		 ] = ulongp_in[
			(l_height - 1L - yy) * l_channels * l_width +
			(l_width  - 1L - xx) * l_channels +
			zz
		 ];
	   }
	  }
	 }
	} else if (IIP_ROT_CLOCKWORK_270 == this->_e_clockwork) {
	 for (yy = 0L; yy < l_height; ++yy) {
	  if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	  for (xx = 0L; xx < l_width; ++xx) {
	   for (zz = 0L; zz < l_channels; ++zz) {
		 ulongp_out[
			yy * l_channels * l_width +
			xx * l_channels +
			zz
		 ] = ulongp_in[
			(l_width - 1L - xx) * l_channels * l_height +
			yy * l_channels +
			zz
		 ];
	   }
	  }
	 }
	}
}
