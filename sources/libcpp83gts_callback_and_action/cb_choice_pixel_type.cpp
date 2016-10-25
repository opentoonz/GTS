#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

#if 0
void gts_master::_change_view_main( void )
{
	/* データがないときはなにもしない */
	if (NULL == this->cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* 表示準備 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}

	/* 画面の表示変更 */
	switch (this->cl_ogl_view.get_e_wview_type()) {
	case E_WVIEW_TYPE_NOTHING:
		break;
	case E_WVIEW_TYPE_MAIN:
		break;

	case E_WVIEW_TYPE_SUB:
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_ONION:
		this->_wview_main();
		break;
	}

	/* 表示 */
	this->iipg_view_redraw_();
}
#endif
void gts_master::cb_choice_pixel_type( void )
{
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:
		cl_gts_gui.group_bw->show();
		cl_gts_gui.group_grays->hide();
		cl_gts_gui.group_rgb->hide();

//		this->_change_view_main();
		break;
	case 1:
		cl_gts_gui.group_bw->hide();
		cl_gts_gui.group_grays->show();
		cl_gts_gui.group_rgb->hide();

//		this->_change_view_main();
		break;
	case 2:
		cl_gts_gui.group_bw->hide();
		cl_gts_gui.group_grays->hide();
		cl_gts_gui.group_rgb->show();
		break;
	}
}
