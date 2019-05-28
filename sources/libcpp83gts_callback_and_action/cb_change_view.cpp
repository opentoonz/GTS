#include <FL/fl_ask.H> // fl_alert()
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_str_language.h" // gts_str::
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_change_wview_( E_WVIEW_TYPE wview_type )
{
	/* 画面の表示変更 */
	switch (wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:		this->_wview_main(); break;
	case E_WVIEW_TYPE_SUB:		this->_wview_sub();  break;
	case E_WVIEW_TYPE_LR_PARALLEL:	this->_wview_lr_parallel(); break;
	case E_WVIEW_TYPE_UD_PARALLEL:	this->_wview_ud_parallel(); break;
	case E_WVIEW_TYPE_LR_ONION: break;
	case E_WVIEW_TYPE_UD_ONION: break;
	}

	/* 表示 */
	cl_gts_gui.image_view->redraw(); /* 画像再表示 */
}

bool gts_master::check_change_wview( void )
{
	/* Crop実行時はなにもしない */
	if (cl_gts_master.cl_ogl_view.get_crop_disp_sw() == ON) {
		fl_alert(
//			"Not change ,when Crop mode"
			gts_str::change_view::not_change
		);
		return false;
	}

	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		fl_alert(
//			"Need Image"
			gts_str::change_view::no_image
		);
		return false;
	}

	/* データが、RGBフルカラーでないと実行しない */
	if (this->cl_iip_ro90.get_l_channels() < 3L) {
		fl_alert(
//			"Need RGB Image"
			gts_str::change_view::no_rgb_image
		);
		return false;
	}

	/* 表示準備 */
	if (OK != this->_iipg_view_setup()) {
		fl_alert(
//			"View setup Error"
			gts_str::change_view::view_setup_error
		);
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return false;
	}
	return true;
}
void gts_master::cb_change_wview_main( void )
{ this->cb_change_wview_( E_WVIEW_TYPE_MAIN );
}
void gts_master::cb_change_wview_sub( void )
{ this->cb_change_wview_( E_WVIEW_TYPE_SUB );
}
void gts_master::cb_change_wview_lr( void )
{ this->cb_change_wview_( E_WVIEW_TYPE_LR_PARALLEL );
}
void gts_master::cb_change_wview_ud( void )
{ this->cb_change_wview_( E_WVIEW_TYPE_UD_PARALLEL );
}

