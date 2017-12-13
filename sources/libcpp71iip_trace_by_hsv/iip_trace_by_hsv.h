#ifndef iip_trace_by_hsv_h
#define iip_trace_by_hsv_h

#include <vector>
#include <string>
#include "calc_trace_by_hsv.h"
#include "iip_canvas.h"
#include "opengl_vertex_buffer_object.h"

/*
	template
	INN,OUTのPixel値要素について
		unsigned char
		unsigned short
		unsigned long
		unsigned int	(=unsigned)
	のみサポート
		float
		double
	は処理できない
*/
class iip_trace_by_hsv : public iip_canvas {
public:
	iip_trace_by_hsv()
	:area_xpos_(0)
	,area_ypos_(0)
	,area_xsize_(0)
	,area_ysize_(0)
	{	this->set_ccp_object_name_of_mv("iip_trace_by_hsv");
	}

	void set_area_xpos( const int xp ) { this->area_xpos_ = xp; }
	void set_area_ypos( const int yp ) { this->area_ypos_ = yp; }
	void set_area_xsize( const int xs ) { this->area_xsize_ = xs; }
	void set_area_ysize( const int ys ) { this->area_ysize_ = ys; }

	std::string exec( 
		const std::vector<calc::trace_by_hsv_params>& hsv_params
		,const bool white_out_of_area_sw
		,const bool random_position_sw
		,opengl::vertex_buffer_object& vbo
	);

private:
	int	area_xpos_
		,area_ypos_
		,area_xsize_
		,area_ysize_;
};

#endif /* !iip_trace_by_hsv_h */
