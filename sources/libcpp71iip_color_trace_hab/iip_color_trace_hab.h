#ifndef __iip_color_trace_hab_h__
#define __iip_color_trace_hab_h__

#include "iip_canvas.h"
#include "calcu_histogram_hab.h"
#include "calcu_color_trace_hab.h"
#include "calcu_color_trace_sep_hsv.h"

class iip_color_trace_hab : public iip_canvas {
public:
	iip_color_trace_hab()
	{
		this->set_ccp_object_name_of_mv("iip_color_trace_hab");
		this->_l_area_xpos = 0L;
		this->_l_area_ypos = 0L;
		this->_l_area_xsize = 0L;
		this->_l_area_ysize = 0L;
	}

	void set_l_area_xpos( long ll ) { this->_l_area_xpos = ll; }
	void set_l_area_ypos( long ll ) { this->_l_area_ypos = ll; }
	void set_l_area_xsize( long ll ) { this->_l_area_xsize = ll; }
	void set_l_area_ysize( long ll ) { this->_l_area_ysize = ll; }
	long get_l_area_xpos( void ) { return this->_l_area_xpos; }
	long get_l_area_ypos( void ) { return this->_l_area_ypos; }
	long get_l_area_xsize( void ) { return this->_l_area_xsize; }
	long get_l_area_ysize( void ) { return this->_l_area_ysize; }

	calcu_histogram_hab	cl_hab_hist;

	void exec( calcu_color_trace_base *clp_calcu_color_trace_hab );
private:
	long	_l_area_xpos,
		_l_area_ypos,
		_l_area_xsize,
		_l_area_ysize;

	void _exec_doubl( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, double *doublp_in, calcu_color_trace_base *clp_calcu_color_trace_hab, double *doublp_out );
	void _exec_uchar( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned char *ucharp_in, double d_in_max_div, calcu_color_trace_base *clp_calcu_color_trace_hab, unsigned char *ucharp_out, double d_out_max_mul );
	void _exec_ulong( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned long *ulongp_in, double d_in_max_div, calcu_color_trace_base *clp_calcu_color_trace_hab, unsigned long *ulongp_out, double d_out_max_mul );
	void _exec_ushrt( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned short *ushrtp_in, double d_in_max_div, calcu_color_trace_base *clp_calcu_color_trace_hab, unsigned short *ushrtp_out, double d_out_max_mul );
};

#endif /* !__iip_color_trace_hab_h__ */
