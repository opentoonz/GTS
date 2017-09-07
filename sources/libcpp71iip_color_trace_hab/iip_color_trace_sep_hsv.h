#ifndef iip_color_trace_sep_hsv_h
#define iip_color_trace_sep_hsv_h

#include "iip_canvas.h"
#include "calcu_histogram_hab.h" /* compileを通すためだけのdummy include */
#include "calcu_color_trace_sep_hsv.h"

/*
	template
	INN,OUTについて
		unsigned char
		unsigned short
		unsigned long
		unsigned int	(=unsigned)
	のみサポート
		float
		double
	は処理できない
*/
/*template <class INN , class OUT>
void iip_color_trace_sep_hsv::_exec_uchar(
int width , int channels , INN *image_inn_top
, int area_xpos , int area_ypos , int area_xsize , int area_ysize
, const calcu_color_trace_sep_hsv& calcu_sep_hsv , OUT *image_out_top
);
template <unsigned char , unsigned char>
void iip_color_trace_sep_hsv::_exec_uchar(
int width , int channels , unsigned char *image_inn_top
, int area_xpos , int area_ypos , int area_xsize , int area_ysize
, const calcu_color_trace_sep_hsv& calcu_sep_hsv , unsigned char *image_out_top
);
template <unsigned short , unsigned short>
void iip_color_trace_sep_hsv::_exec_uchar(
int width , int channels , unsigned short *image_inn_top
, int area_xpos , int area_ypos , int area_xsize , int area_ysize
, const calcu_color_trace_sep_hsv& calcu_sep_hsv , unsigned short *image_out_top
);*/

//--------------------------------------------------

class iip_color_trace_sep_hsv : public iip_canvas {
public:
	iip_color_trace_sep_hsv()
		:area_xpos_(0)
		,area_ypos_(0)
		,area_xsize_(0)
		,area_ysize_(0)
	{	this->set_ccp_object_name_of_mv("iip_color_trace_sep_hsv");
	}

	void set_area_xpos( int xp ) { this->area_xpos_ = xp; }
	void set_area_ypos( int yp ) { this->area_ypos_ = yp; }
	void set_area_xsize( int xs ) { this->area_xsize_ = xs; }
	void set_area_ysize( int ys ) { this->area_ysize_ = ys; }

 calcu_histogram_hab cl_hab_hist; /* compileを通すためだけのdummy include */

	void exec( calcu_color_trace_sep_hsv& calcu_sep_hsv );
private:
	int	area_xpos_
		,area_ypos_
		,area_xsize_
		,area_ysize_;
};

#endif /* !iip_color_trace_sep_hsv_h */
