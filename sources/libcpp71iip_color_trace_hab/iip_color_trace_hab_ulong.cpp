#include "pri.h"
#include "calc_hsv_rgb.h"
#include "iip_color_trace_hab.h"

#define	UL (unsigned long)

void iip_color_trace_hab::_exec_ulong( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned long *ulongp_in, double d_in_max_div, calcu_color_trace_base *clp_calcu_color_trace_hab, unsigned long *ulongp_out, double d_out_max_mul )
{
	long	l_start, l_scansize;
	long	xx,yy;
	double	d_red, d_gre, d_blu;
	double	d_hh, d_aa, d_bb;
	unsigned long	*ulongp_in_x, *ulongp_out_x;

	l_height;

	l_scansize = l_width * l_channels;
	l_start = l_area_ypos * l_scansize + l_area_xpos * l_channels;
	ulongp_in += l_start;
	ulongp_out += l_start;

	/* histogramを初期化する */
	this->cl_hab_hist.init( l_area_xsize, l_area_ysize );

	for (yy = 0L; yy < l_area_ysize; ++yy) {

	 /* カウントダウン表示中 */
	 if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	 ulongp_in_x = ulongp_in;
	 ulongp_out_x = ulongp_out;

	 for (xx = 0L; xx < l_area_xsize; ++xx) {
		calc::rgb_to_hsv(
			(double)(ulongp_in_x[CH_RED])/d_in_max_div,
			(double)(ulongp_in_x[CH_GRE])/d_in_max_div,
			(double)(ulongp_in_x[CH_BLU])/d_in_max_div,
			d_hh, d_aa, d_bb );

		/* histogramを設定する */
		this->cl_hab_hist.add(
			ulongp_in_x[CH_RED] == ulongp_in_x[CH_GRE] &&
			ulongp_in_x[CH_GRE] == ulongp_in_x[CH_BLU]
			,d_hh,d_aa,d_bb
		);

		clp_calcu_color_trace_hab->exec(
			 d_hh,  d_aa,  d_bb,
			&d_red, &d_gre, &d_blu );

		ulongp_out_x[CH_RED] = UL(d_red * d_out_max_mul);
		ulongp_out_x[CH_GRE] = UL(d_gre * d_out_max_mul);
		ulongp_out_x[CH_BLU] = UL(d_blu * d_out_max_mul);
	  	ulongp_in_x  += l_channels;
	  	ulongp_out_x += l_channels;
	 }
	 ulongp_in  += l_scansize;
	 ulongp_out += l_scansize;
	}
}
