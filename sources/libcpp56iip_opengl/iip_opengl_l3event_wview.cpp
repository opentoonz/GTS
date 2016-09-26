#include "pri.h"
#include "iip_opengl_l3event.h"

void iip_opengl_l3event::_set_pos_and_zoom_from_main_to_sub( void )
{
	if ((NULL != this->_clp_main)
	&&  (NULL != this->_clp_sub)) {
		this->_clp_sub->zoom_num(
		 this->_clp_main->get_l_zoom() );

		this->_clp_sub->move_xy_pos(
		 this->_clp_main->get_l_xp(),
		 this->_clp_main->get_l_yp() );
	}
}

void iip_opengl_l3event::_set_pos_and_zoom_from_sub_to_main( void )
{
	if ((NULL != this->_clp_main)
	&&  (NULL != this->_clp_sub)) {
		this->_clp_main->zoom_num(
		 this->_clp_sub->get_l_zoom() );

		this->_clp_main->move_xy_pos(
		 this->_clp_sub->get_l_xp(),
		 this->_clp_sub->get_l_yp() );
	}
}

void iip_opengl_l3event::wview_main( void )
{
	this->_wview( E_WVIEW_TYPE_MAIN );
	this->reshape_opengl(this->_l_view_x_size,this->_l_view_y_size);
}
void iip_opengl_l3event::wview_sub( void )
{
	this->_wview( E_WVIEW_TYPE_SUB );
	this->reshape_opengl(this->_l_view_x_size,this->_l_view_y_size);
}

void iip_opengl_l3event::wview_lr_parallel( void )
{
	this->_wview( E_WVIEW_TYPE_LR_PARALLEL );
	this->reshape_opengl(this->_l_view_x_size,this->_l_view_y_size);
	this->_set_pos_and_zoom_from_main_to_sub();
}

void iip_opengl_l3event::wview_lr_onion( void )
{
	this->_wview( E_WVIEW_TYPE_LR_ONION );
	this->reshape_opengl(this->_l_view_x_size,this->_l_view_y_size);
	this->_set_pos_and_zoom_from_main_to_sub();
}

void iip_opengl_l3event::wview_ud_parallel( void )
{
	this->_wview( E_WVIEW_TYPE_UD_PARALLEL );
	this->reshape_opengl(this->_l_view_x_size,this->_l_view_y_size);
	this->_set_pos_and_zoom_from_main_to_sub();
}

void iip_opengl_l3event::wview_ud_onion( void )
{
	this->_wview( E_WVIEW_TYPE_UD_PARALLEL );
	this->reshape_opengl(this->_l_view_x_size,this->_l_view_y_size);
	this->_set_pos_and_zoom_from_main_to_sub();
}

iip_opengl_l1edit *iip_opengl_l3event::get_clp_iip_view( void )
{
	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING:
		return NULL;
	case E_WVIEW_TYPE_MAIN:
		return this->_clp_main;
	case E_WVIEW_TYPE_SUB:
		return this->_clp_sub;
	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main) { return this->_clp_main; }
		if (NULL != this->_clp_sub) { return this->_clp_sub; }
	}
	return NULL;
}

/*--------------------------------------------------------*/

char *iip_opengl_l3event::_get_cp_wview_type( E_WVIEW_TYPE e_type )
{
	switch (e_type) {
	case E_WVIEW_TYPE_NOTHING:
     return "E_WVIEW_TYPE_NOTHING";
	case E_WVIEW_TYPE_MAIN:
     return "E_WVIEW_TYPE_MAIN";
	case E_WVIEW_TYPE_SUB:
     return "E_WVIEW_TYPE_SUB";
	case E_WVIEW_TYPE_LR_PARALLEL:
     return "E_WVIEW_TYPE_LR_PARALLEL";
	case E_WVIEW_TYPE_LR_ONION:
     return "E_WVIEW_TYPE_LR_ONION";
	case E_WVIEW_TYPE_UD_PARALLEL:
     return "E_WVIEW_TYPE_UD_PARALLEL";
	case E_WVIEW_TYPE_UD_ONION:
     return "E_WVIEW_TYPE_UD_ONION";
	}
	return NULL;
}

void iip_opengl_l3event::_wview( E_WVIEW_TYPE e_type )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr("iip_opengl_l3event::_wview()");
	}

	if ((NULL != this->_cl_unt_view[0].cl_iip_view.get_vp_canvas())
	&&(NULL != this->_cl_unt_view[1].cl_iip_view.get_vp_canvas())){
		switch (e_type) {
		case E_WVIEW_TYPE_NOTHING:
			if (ON == this->get_i_pv_sw()) {
				pri_funct_msg_vr(
					"arg is %s, but set %s.",
			this->_get_cp_wview_type(E_WVIEW_TYPE_NOTHING),
			this->_get_cp_wview_type(E_WVIEW_TYPE_MAIN)
				);
			}
			this->_clp_main =
				&(this->_cl_unt_view[0].cl_iip_view);
			this->_clp_sub = NULL;
			this->_e_wview_type = E_WVIEW_TYPE_MAIN;
			break;
		case E_WVIEW_TYPE_MAIN:
			this->_clp_main =
				&(this->_cl_unt_view[0].cl_iip_view);
/*
この内容だとE_WVIEW_TYPE_SUBにしたときsub画像がscrollしてない
scroll値をsubにもセットしておくため、表示はしないが画像セットしておく
記録としてまだここ残す 2016-09-21
			this->_clp_sub = NULL;
*/
			this->_clp_sub =
				&(this->_cl_unt_view[1].cl_iip_view);
			this->_e_wview_type = e_type;
			break;
		case E_WVIEW_TYPE_SUB:
/*
この内容だと表示しない
記録としてまだここ残す 2016-09-21
			this->_clp_main = NULL;
			this->_clp_sub =
				&(this->_cl_unt_view[1].cl_iip_view);
*/
			this->_clp_main =
				&(this->_cl_unt_view[0].cl_iip_view);
			this->_clp_sub =
				&(this->_cl_unt_view[1].cl_iip_view);
			this->_e_wview_type = e_type;
			break;
		case E_WVIEW_TYPE_LR_PARALLEL:
		case E_WVIEW_TYPE_LR_ONION:
		case E_WVIEW_TYPE_UD_PARALLEL:
		case E_WVIEW_TYPE_UD_ONION:
			this->_clp_main =
				&(this->_cl_unt_view[0].cl_iip_view);
			this->_clp_sub =
				&(this->_cl_unt_view[1].cl_iip_view);
			this->_e_wview_type = e_type;
			break;
		}
	} else
	if ((NULL == this->_cl_unt_view[0].cl_iip_view.get_vp_canvas())
	&&(NULL == this->_cl_unt_view[1].cl_iip_view.get_vp_canvas())){
		if (ON == this->get_i_pv_sw()) {
		 if (E_WVIEW_TYPE_NOTHING != e_type) {
			pri_funct_msg_vr( "arg is %s, but set %s.",
			this->_get_cp_wview_type(e_type),
			this->_get_cp_wview_type(E_WVIEW_TYPE_NOTHING)
			);
		 }
		}
		this->_clp_main = NULL;
		this->_clp_sub = NULL;
		this->_e_wview_type = E_WVIEW_TYPE_NOTHING;
	} else
	if ((NULL != this->_cl_unt_view[0].cl_iip_view.get_vp_canvas())
	&&(NULL == this->_cl_unt_view[1].cl_iip_view.get_vp_canvas())){
		if (ON == this->get_i_pv_sw()) {
		 if (E_WVIEW_TYPE_MAIN != e_type) {
			pri_funct_msg_vr( "arg is %s, but set %s.",
			this->_get_cp_wview_type(e_type),
			this->_get_cp_wview_type(E_WVIEW_TYPE_NOTHING)
			);
		 }
		}
		this->_clp_main = &(this->_cl_unt_view[0].cl_iip_view);
		this->_clp_sub = NULL;
		this->_e_wview_type = E_WVIEW_TYPE_MAIN;
	} else
	if ((NULL == this->_cl_unt_view[0].cl_iip_view.get_vp_canvas())
	&&(NULL != this->_cl_unt_view[1].cl_iip_view.get_vp_canvas())){
		if (ON == this->get_i_pv_sw()) {
		 if (E_WVIEW_TYPE_SUB != e_type) {
			pri_funct_msg_vr( "arg is %s, but set %s.",
			this->_get_cp_wview_type(e_type),
			this->_get_cp_wview_type(E_WVIEW_TYPE_NOTHING)
			);
		 }
		}
		this->_clp_main = NULL;
		this->_clp_sub = &(this->_cl_unt_view[1].cl_iip_view);
		this->_e_wview_type = E_WVIEW_TYPE_SUB;
	}
}
