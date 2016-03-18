#include <assert.h>
#include "pri.h"
#include "tw_dmy_l1_scan.h"

int iip_scan::open( void )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "dummy open." );
	}

	return OK;
}

int iip_scan::print_all( void )
{

	pri_funct_msg_vr( "native_resolution x %.16g y %.16g",
		this->_d_x_native_resolution,
		this->_d_y_native_resolution );
	pri_funct_msg_vr( "physical_area     x %.16g y %.16g",
		this->_d_physical_width,
		this->_d_physical_height );

	return OK;
}

int iip_scan::read( void )
{
	iip_canvas *clp_canvas;
	long	l_w, l_h;

	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "dummy read...(alloc canvas)." );
	}

	clp_canvas = &(this->_cl_iip_canvas);

	/* 画像の大きさ、その他もろもろ設定して... */
	clp_canvas->set_i_mv_sw( this->get_i_mv_sw() );
	clp_canvas->set_i_pv_sw( this->get_i_pv_sw() );
	clp_canvas->set_i_cv_sw( this->get_i_cv_sw() );

	/* inchs */
	if (OFF == this->_i_units_centimeters_sw) {
		l_w = (long)((this->_d_right - this->_d_left) *
			this->_d_x_resolution);
		l_h = (long)((this->_d_top - this->_d_bottom) *
			this->_d_y_resolution);
	}
	/* centimeters */
	else {
		l_w = (long)((this->_d_right - this->_d_left) * 2.54 *
			this->_d_x_resolution);
		l_h = (long)((this->_d_top - this->_d_bottom) * 2.54 *
			this->_d_y_resolution);
	}
	clp_canvas->set_l_width(  l_w );
	clp_canvas->set_l_height( l_h );

	switch (this->_e_pixeltype) {
	case E_PIXELTYPE_BW:
	 clp_canvas->cl_ch_info.set_e_ch_num_type( E_CH_NUM_BITBW );
	 clp_canvas->set_l_channels( 1L );
		break;
	case E_PIXELTYPE_GRAYSCALE:
	 clp_canvas->cl_ch_info.set_e_ch_num_type( E_CH_NUM_UCHAR );
	 clp_canvas->set_l_channels( 1L );
		break;
	case  E_PIXELTYPE_RGB:
	 clp_canvas->cl_ch_info.set_e_ch_num_type( E_CH_NUM_UCHAR );
	 clp_canvas->set_l_channels( 3L );
		break;
	default:
		assert(0);
	}

	/* ...メモリ確保 */
	if (OK != clp_canvas->mem_alloc_canvas()) {
		pri_funct_err_bttvr(
	 "Error : clp_canvas->mem_alloc_canvas() returns NG."
		);
		return NG;
	}

	return OK;
}

int iip_scan::close( void )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "dummy close." );
	}
	return OK;
}
