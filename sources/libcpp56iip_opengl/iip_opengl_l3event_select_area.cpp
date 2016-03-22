#include "pri.h"
#include "iip_opengl_l3event.h"

E_WVIEW_AREA iip_opengl_l3event::_select_area( long l_mouse_xp, long l_mouse_yp )
{
	long l_x1,l_x2, l_y1,l_y2;
	E_WVIEW_AREA	e_area = E_WVIEW_AREA_EXCEPT;

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l3event::select_area(-)" );
	}

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:	e_area = E_WVIEW_AREA_EXCEPT; break;
	case E_WVIEW_TYPE_MAIN:	e_area = E_WVIEW_AREA_MAIN; break;
	case E_WVIEW_TYPE_SUB:	e_area = E_WVIEW_AREA_SUB; break;

	/* 左右分割 */
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
		/* 左画像の右端+1(separeterの表示開始)位置 */
		l_x1 = (long)(	this->_d_separete_x_ratio *
				this->_l_view_x_size)
			- (this->_l_seaprete_thickness / 2L);
		/* 右画像の左端(表示開始)位置 */
		l_x2 = l_x1 + this->_l_seaprete_thickness;

		if (l_mouse_xp < l_x1) {
			e_area = E_WVIEW_AREA_MAIN;
		} else if (l_mouse_xp < l_x2) {
			e_area = E_WVIEW_AREA_SEPARATOR;
		} else {
			e_area = E_WVIEW_AREA_SUB;
		}
		break;

	/* 上下分割 */
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		/* 下画像の上端+1(separeterの表示開始)位置 */
		l_y1 = (long)(	this->_d_separete_y_ratio *
				this->_l_view_y_size)
			- (this->_l_seaprete_thickness / 2L);
		/* 上画像の下端(表示開始)位置 */
		l_y2 = l_y1 + this->_l_seaprete_thickness;

		if (l_mouse_yp < l_y1) {
			e_area = E_WVIEW_AREA_MAIN;
		} else if (l_mouse_yp < l_y2) {
			e_area = E_WVIEW_AREA_SEPARATOR;
		} else {
			e_area = E_WVIEW_AREA_SUB;
		}
		break;
	}

	return e_area;
}
