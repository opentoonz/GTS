#include "pri.h"
#include "calcu_rgb_to_hsv.h"
#include "iip_color_trace_hab.h"

void iip_color_trace_hab::_exec_doubl( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, double *doublp_in, calcu_color_trace_hab *clp_calcu_color_trace_hab, double *doublp_out )
{
	long	l_start, l_scansize;
	long	xx,yy;
	double	d_hh, d_aa, d_bb;
	double	*doublp_in_x, *doublp_out_x;
	calcu_rgb_to_hsv cl_rgb_to_hab;

	l_height;

	l_scansize = l_width * l_channels;
	l_start = l_area_ypos * l_scansize + l_area_xpos * l_channels;
	doublp_in += l_start;
	doublp_out += l_start;

	/* histogramを初期化する */
	this->cl_hab_hist.init( l_area_xsize, l_area_ysize );

	for (yy = 0L; yy < l_area_ysize; ++yy) {

	 /* カウントダウン表示中 */
	 if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	 doublp_in_x = doublp_in;
	 doublp_out_x = doublp_out;

	 for (xx = 0L; xx < l_area_xsize; ++xx) {
		cl_rgb_to_hab.to_hsv(
			doublp_in_x[CH_RED],
			doublp_in_x[CH_GRE],
			doublp_in_x[CH_BLU],
			&d_hh, &d_aa, &d_bb );

		/* histogramを設定する */
		this->cl_hab_hist.add(
			doublp_in_x[CH_RED] == doublp_in_x[CH_GRE] &&
			doublp_in_x[CH_GRE] == doublp_in_x[CH_BLU]
			,d_hh,d_aa,d_bb
		);

		clp_calcu_color_trace_hab->exec(
			 d_hh,  d_aa,  d_bb,
			&(doublp_out_x[CH_RED]),
			&(doublp_out_x[CH_GRE]),
			&(doublp_out_x[CH_BLU])
		);
	  	doublp_in_x  += l_channels;
	  	doublp_out_x += l_channels;
	 }
	 doublp_in  += l_scansize;
	 doublp_out += l_scansize;
	}
}
