#include "pri.h"
#include "calcu_rgb_to_hsv.h"
#include "iip_color_trace_hab.h"

#define	US (unsigned short)

void iip_color_trace_hab::_exec_ushrt( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned short *ushrtp_in, double d_in_max_div, calcu_color_trace_hab *clp_calcu_color_trace_hab, unsigned short *ushrtp_out, double d_out_max_mul )
{
	long	l_start, l_scansize;
	long	xx,yy;
	double	d_red, d_gre, d_blu;
	double	d_hh, d_aa, d_bb;
	unsigned short	*ushrtp_in_x, *ushrtp_out_x;
	calcu_rgb_to_hsv cl_rgb_to_hab;

	l_height;

	l_scansize = l_width * l_channels;
	l_start = l_area_ypos * l_scansize + l_area_xpos * l_channels;
	ushrtp_in += l_start;
	ushrtp_out += l_start;

	/* histogramを初期化する */
	this->cl_hab_hist.init( l_area_xsize, l_area_ysize );

	for (yy = 0L; yy < l_area_ysize; ++yy) {

	 /* カウントダウン表示中 */
	 if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	 ushrtp_in_x = ushrtp_in;
	 ushrtp_out_x = ushrtp_out;

	 for (xx = 0L; xx < l_area_xsize; ++xx) {
		cl_rgb_to_hab.to_hsv(
			(double)(ushrtp_in_x[CH_RED])/d_in_max_div,
			(double)(ushrtp_in_x[CH_GRE])/d_in_max_div,
			(double)(ushrtp_in_x[CH_BLU])/d_in_max_div,
			&d_hh, &d_aa, &d_bb );

		/* histogramを設定する */
		this->cl_hab_hist.add(
			ushrtp_in_x[CH_RED] == ushrtp_in_x[CH_GRE] &&
			ushrtp_in_x[CH_GRE] == ushrtp_in_x[CH_BLU]
			,d_hh,d_aa,d_bb
		);

		clp_calcu_color_trace_hab->exec(
			 d_hh,  d_aa,  d_bb,
			&d_red, &d_gre, &d_blu );

		ushrtp_out_x[CH_RED] = US(d_red * d_out_max_mul);
		ushrtp_out_x[CH_GRE] = US(d_gre * d_out_max_mul);
		ushrtp_out_x[CH_BLU] = US(d_blu * d_out_max_mul);
	  	ushrtp_in_x  += l_channels;
	  	ushrtp_out_x += l_channels;
	 }
	 ushrtp_in  += l_scansize;
	 ushrtp_out += l_scansize;
	}
}
