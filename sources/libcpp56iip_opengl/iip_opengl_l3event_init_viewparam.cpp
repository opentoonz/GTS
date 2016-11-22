#include "pri.h"
#include "iip_opengl_l3event.h"

/* 表示のパラメータの初期化 */
void iip_opengl_l3event::init_viewparam( long l_view_xs, long l_view_ys )
{
	long	l_xp,l_yp,
		l_xs,l_ys,
		l_x1,l_x2,
		l_y1,l_y2;

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l3event::init_viewparam(-)" );
	}

	this->_l_view_x_size = l_view_xs;
	this->_l_view_y_size = l_view_ys;

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
		break;
	case E_WVIEW_TYPE_MAIN:
		this->_clp_main->init_viewport(l_view_xs,l_view_ys);
		this->_clp_main->all_view();
		if (this->_clp_sub != nullptr) {
		 this->_clp_sub->init_viewport(l_view_xs,l_view_ys);
		 this->_clp_sub->all_view();
		}
		break;
	case E_WVIEW_TYPE_SUB:
		this->_clp_main->init_viewport(l_view_xs,l_view_ys);
		this->_clp_main->all_view();
		this->_clp_sub->init_viewport(l_view_xs,l_view_ys);
		this->_clp_sub->all_view();
		break;

	/* 左右分割 */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		/* 左画像の右端+1(separeterの表示開始)位置 */
		l_x1 = (long)(this->_d_separete_x_ratio * l_view_xs)
			- (this->_l_seaprete_thickness / 2L);
		/* 右画像の左端(表示開始)位置 */
		l_x2 = l_x1 + this->_l_seaprete_thickness;

		l_xp = 0L;
		l_yp = 0L;
		l_xs = l_x1;
		l_ys = l_view_ys;
		this->_clp_main->init_viewport( l_xs,l_ys, l_xp,l_yp);
		this->_clp_main->all_view();

		l_xp = l_x2;
		l_yp = 0L;
		l_xs = l_view_xs - l_x2;
		l_ys = l_view_ys;
		this->_clp_sub->init_viewport( l_xs,l_ys, l_xp,l_yp);
		this->_clp_sub->all_view();
		break;

	/* 上下分割 */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		/* 下画像の上端+1(separeterの表示開始)位置 */
		l_y1 = (long)(this->_d_separete_y_ratio * l_view_ys)
			- (this->_l_seaprete_thickness / 2L);
		/* 上画像の下端(表示開始)位置 */
		l_y2 = l_y1 + this->_l_seaprete_thickness;

		l_xp = 0L;
		l_yp = 0L;
		l_xs = l_view_xs;
		l_ys = l_y1;
		this->_clp_main->init_viewport( l_xs,l_ys, l_xp,l_yp);
		this->_clp_main->all_view();

		l_xp = 0L;
		l_yp = l_y2;
		l_xs = l_view_xs;
		l_ys = l_view_ys - l_y2;
		this->_clp_sub->init_viewport( l_xs,l_ys, l_xp,l_yp);
		this->_clp_sub->all_view();
		break;
	}
}
