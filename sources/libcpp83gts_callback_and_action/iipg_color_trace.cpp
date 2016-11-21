#include <FL/Fl.H>

#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

int gts_master::_iipg_color_trace_setup( void )
{
	iip_canvas *clp_ro90, *clp_trac;
	long l_sz_ro90, l_sz_trac;

	if (ON == this->i_mv_sw()) {
		pri_funct_msg_ttvr(
			"gts_master::_iipg_color_trace()" );
	}

	/* 画像処理class */
	clp_ro90 = &(this->cl_iip_ro90);
	clp_trac = &(this->cl_iip_trac);

	/* 全体の大きさが以前と違う場合はメモリ確保しなおし */
	l_sz_ro90 = 	clp_ro90->get_l_height() *
			clp_ro90->get_l_channels() *
			clp_ro90->get_l_scanline_channel_bytes();
	l_sz_trac = 	clp_trac->get_l_height() *
			clp_trac->get_l_channels() *
			clp_trac->get_l_scanline_channel_bytes();
	if (l_sz_ro90 != l_sz_trac) {
		this->cl_iip_trac.set_clp_parent(&(this->cl_iip_ro90));
		this->cl_iip_trac.set_canvas_size(&(this->cl_iip_ro90));
		/* メモリの取りなおし */
		if (OK != this->cl_iip_trac.mem_alloc_canvas()) {
			pri_funct_err_bttvr(
		 "Error : this->cl_iip_trac.mem_alloc_canvas() returns NG" );
			return NG;
		}
		this->cl_iip_edot.set_clp_parent(&(this->cl_iip_trac));
		this->cl_iip_edot.set_canvas_size(&(this->cl_iip_trac));
		this->cl_iip_edot.set_vp_reference_canvas(
			this->cl_iip_trac.get_vp_canvas()
		);
	}
	/* 全体は同じだが、各々の大きさが違う場合はサイズ設定しなおし */
	else if (
	(clp_ro90->get_l_width() !=
	 clp_trac->get_l_width()) ||
	(clp_ro90->get_l_height() !=
	 clp_trac->get_l_height()) ||
	(clp_ro90->get_l_channels() !=
	 clp_trac->get_l_channels()) ||
	(clp_ro90->cl_ch_info.get_e_ch_num_type() !=
	 clp_trac->cl_ch_info.get_e_ch_num_type()) ||
	(clp_ro90->cl_ch_info.get_l_bytes() !=
	 clp_trac->cl_ch_info.get_l_bytes()) ||
	(clp_ro90->cl_ch_info.get_l_bits() !=
	 clp_trac->cl_ch_info.get_l_bits())
	) {
		/* 親のサイズを元に設定をしなおす */
		this->cl_iip_trac.set_clp_parent(&(this->cl_iip_ro90));
		this->cl_iip_trac.set_canvas_size(&(this->cl_iip_ro90));

		this->cl_iip_edot.set_clp_parent(&(this->cl_iip_trac));
		this->cl_iip_edot.set_canvas_size(&(this->cl_iip_trac));
	}

	/* fltkメニューから実行パラメータをセットする */
	this->cl_color_trace_enhancement.src_set_from_gui();

	/* トレース範囲を全域に初期化 */
	this->cl_iip_trac.set_l_area_xpos( 0L );
	this->cl_iip_trac.set_l_area_ypos( 0L );
	this->cl_iip_trac.set_l_area_xsize(
	 this->cl_iip_trac.get_l_width() );
	this->cl_iip_trac.set_l_area_ysize(
	 this->cl_iip_trac.get_l_height() );

	this->cl_iip_edot.set_l_area_xpos( 0L );
	this->cl_iip_edot.set_l_area_ypos( 0L );
	this->cl_iip_edot.set_l_area_xsize(
	 this->cl_iip_edot.get_l_width() );
	this->cl_iip_edot.set_l_area_ysize(
	 this->cl_iip_edot.get_l_height() );

	return OK;
}
void gts_master::_iipg_color_trace_exec( int i_area_sw )
{
	if (ON == i_area_sw) {
		this->cl_iip_trac.set_l_area_xpos(
		 this->cl_ogl_view.get_i_glcrop_xpos()
		);
		this->cl_iip_trac.set_l_area_ypos(
		 this->cl_ogl_view.get_i_glcrop_ypos()
		);
		this->cl_iip_trac.set_l_area_xsize(
		 this->cl_ogl_view.get_i_glcrop_width()
		);
		this->cl_iip_trac.set_l_area_ysize(
		 this->cl_ogl_view.get_i_glcrop_height()
		);

		this->cl_iip_edot.set_l_area_xpos(
		 this->cl_ogl_view.get_i_glcrop_xpos()
		);
		this->cl_iip_edot.set_l_area_ypos(
		 this->cl_ogl_view.get_i_glcrop_ypos()
		);
		this->cl_iip_edot.set_l_area_xsize(
		 this->cl_ogl_view.get_i_glcrop_width()
		);
		this->cl_iip_edot.set_l_area_ysize(
		 this->cl_ogl_view.get_i_glcrop_height()
		);
	}

	/* トレース */
	if (cl_gts_gui.chkbtn_filter_rgb_color_trace_sw->value()) {
		this->cl_iip_trac.exec(&(this->cl_cal_trac));/* 2値化処理 */
	} else {
		this->cl_iip_trac.copy_image_from_parent(
		 this->cl_iip_trac.get_ccp_object_name_of_mv()
		);	/* 処理しないのでコピーだけする */
	}

	/* erase dot noise */
	if (cl_gts_gui.chkbtn_filter_rgb_erase_1dot_sw->value()) {
		this->cl_iip_edot.exec();
	}
}
