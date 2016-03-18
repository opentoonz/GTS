#ifndef __iip_scale_by_subpixel_h__
#define __iip_scale_by_subpixel_h__

#include "iip_canvas.h"

class iip_scale_by_subpixel : public iip_canvas {
public:
	iip_scale_by_subpixel()
	{
		this->set_ccp_object_name_of_mv(
			"iip_scale_by_subpixel");
		this->_lp_width = NULL;
		this->_lp_height = NULL;
		this->_lp_scanline = NULL;
		this->_l_x_subpixel_division = 0L;
		this->_l_y_subpixel_division = 0L;
		this->_l_subpixel_min_div = 4L;
		this->_l_free_incr_and_accum_width = 0L;
		this->_l_free_incr_and_accum_height = 0L;
		this->_l_free_incr_and_accum_channels = 0L;
	}
	~iip_scale_by_subpixel()
	{
		this->mem_free_incr_and_accum();
	}
	void set_l_x_div( long x ) { this->_l_x_subpixel_division=x; }
	void set_l_y_div( long y ) { this->_l_y_subpixel_division=y; }
	void set_l_min_div( long m ) { this->_l_subpixel_min_div=m; }

	long get_l_x_div( void ) {return this->_l_x_subpixel_division;}
	long get_l_y_div( void ) {return this->_l_y_subpixel_division;}
	long get_l_min_div( void ) {return this->_l_subpixel_min_div;}

	/* サイズのチェックとカンバスメモリの参照あるいは確保 */
	int set_canvas( void );

	void exec( void );

	void mem_free_incr_and_accum( void );

private:
	long	*_lp_width,
		*_lp_height,
		*_lp_scanline;
	long	_l_free_incr_and_accum_width,
		_l_free_incr_and_accum_height,
		_l_free_incr_and_accum_channels;
	long	_l_x_subpixel_division,
		_l_y_subpixel_division,
		_l_subpixel_min_div;

	/* 親と子両方の画像の大きさを設定した後に呼ぶこと */
	int _mem_alloc_incr_and_accum( void );

	long _calcu_subpixel_division( long l_sx, long l_sy );
	/* subpixelの値がゼロであれば画像の大きさから自動的に設定する
	subpixelの値がゼロでなければその値で実行する */
	void _set_subpixel_division( void );

	void _calcu_bresenham( long l_dx, long l_dy, long *lp_y, long l_inc );
	void _exec_uchar( unsigned char *ucharp_in, unsigned char *ucharp_out, long l_out_width, long l_out_height, long l_out_channels, long l_x_subpixel, long l_y_subpixel, long *lp_width, long *lp_height, long *lp_scanline );
	void _exec_ushrt( unsigned short *ushrtp_in, unsigned short *ushrtp_out, long l_out_width, long l_out_height, long l_out_channels, long l_x_subpixel, long l_y_subpixel, long *lp_width, long *lp_height, long *lp_scanline );
};

#endif /* !__iip_scale_by_subpixel_h__ */
