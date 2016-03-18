#ifndef __iip_opengl_l2data_h__
#define __iip_opengl_l2data_h__

#include "iip_precision.h"
#include "iip_opengl_l1edit.h"

class iip_opengl_l2data {
public:
	iip_opengl_l2data( void )
	{
		this->_i_mv_sw = OFF;
		this->_i_pv_sw = OFF;
		this->_i_cv_sw = OFF;
		this->_i_bw_use_uchar_sw = ON;

		this->cl_iip_chan.set_ccp_object_name_of_mv(
			"iip_canvas_for_channels0");
	}
	void set_i_mv_sw( int sw ) {
		this->_i_mv_sw = sw;
		this->cl_iip_prec.set_i_mv_sw( sw );
		this->cl_iip_chan.set_i_mv_sw( sw );
		this->cl_iip_view.set_i_mv_sw( sw );
	}
	void set_i_pv_sw( int sw ) {
		this->_i_pv_sw = sw;
		this->cl_iip_prec.set_i_pv_sw( sw );
		this->cl_iip_chan.set_i_pv_sw( sw );
		this->cl_iip_view.set_i_pv_sw( sw );
	}
	void set_i_cv_sw( int sw ) {
		this->_i_cv_sw = sw;
		this->cl_iip_prec.set_i_cv_sw( sw );
		this->cl_iip_chan.set_i_cv_sw( sw );
		this->cl_iip_view.set_i_cv_sw( sw );
	}
	int get_i_mv_sw( void ) { return this->_i_mv_sw; }
	int get_i_pv_sw( void ) { return this->_i_pv_sw; }
	int get_i_cv_sw( void ) { return this->_i_cv_sw; }

	void set_i_bw_use_uchar_sw( int sw ) {
	  //this->_i_bw_use_uchar_sw = ON; }
	  this->_i_bw_use_uchar_sw = sw; }

	/* 表示用の精度にした画像
		RGB(A)    --> unsigned charのRGB(A)RGB(A)...
		Grayscale --> unsigned char
		BW        --> 元の画像を参照 or unsigned char
	*/
	iip_precision	cl_iip_prec;

	/* RGB(A)でchannel毎表示のための画像
		RGB(A)    --> unsigned charのRRR...GGG...BBB...(AAA...)
		Grayscale --> cl_iip_precの画像を参照
		BW        --> cl_iip_precの画像を参照
	*/
	iip_canvas	cl_iip_chan;

	/* 画像表示 */
	iip_opengl_l1edit	cl_iip_view;

	/* method */
	int set_imagedata( iip_canvas *clp_parent );

private:
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	int	_i_bw_use_uchar_sw;

	void _from_uchar_rgbargba_to_rrggbbaa(
		unsigned char *ucharp_rgbargba,
		long l_w, long l_h, long l_ch,
		unsigned char *ucharp_rrggbbaa );
};

#endif /* !__iip_opengl_l2data_h__ */
