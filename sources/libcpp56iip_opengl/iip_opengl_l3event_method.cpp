#include <string.h>
#include "iip_opengl_l3event.h"

void iip_opengl_l3event::all_view( void )
{
	/* 位置とズームの正確な一致 */
	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->all_view(); }
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->all_view(); }
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->all_view(); }
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}

void iip_opengl_l3event::scroll_center( void )
{

	/* 位置とズームの正確な一致 */
	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->scroll_center(); }
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->scroll_center(); }
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->scroll_center(); }

		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}

void iip_opengl_l3event::zoom_twice_at_center( void )
{

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_twice_at_center(); }
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_twice_at_center(); }
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_twice_at_center(); }
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}
void iip_opengl_l3event::zoom_half_at_center( void )
{

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_half_at_center(); }
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_half_at_center(); }
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_half_at_center(); }
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}

void iip_opengl_l3event::zoom_up_at_center( void )
{

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_up_at_center(); }
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_up_at_center(); }
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_up_at_center(); }
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}
void iip_opengl_l3event::zoom_down_at_center( void )
{

	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_down_at_center(); }
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_down_at_center(); }
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_down_at_center(); }
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}

void iip_opengl_l3event::zoom_num( long l_zoom )
{
	switch (this->_e_wview_type) {
	case E_WVIEW_TYPE_NOTHING: break;
	case E_WVIEW_TYPE_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_num(l_zoom);}
		break;
	case E_WVIEW_TYPE_SUB:
		if (NULL != this->_clp_sub )
		{	    this->_clp_sub->zoom_num(l_zoom);}
		break;

	case E_WVIEW_TYPE_LR_PARALLEL:
	case E_WVIEW_TYPE_LR_ONION:
	case E_WVIEW_TYPE_UD_PARALLEL:
	case E_WVIEW_TYPE_UD_ONION:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_num(l_zoom);}
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub))
		{ this->_set_pos_and_zoom_from_main_to_sub(); }
		break;
	}
}

void iip_opengl_l3event::scroll_left( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->scroll_left();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_left();}
}
void iip_opengl_l3event::scroll_to_left_side( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->scroll_to_left_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_to_left_side();}
}
void iip_opengl_l3event::fit_to_left_side( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->fit_to_left_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->fit_to_left_side();}
}

void iip_opengl_l3event::scroll_down( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->scroll_down();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_down();}
}
void iip_opengl_l3event::scroll_to_down_side( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->scroll_to_down_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_to_down_side();}
}
void iip_opengl_l3event::fit_to_down_side( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->fit_to_down_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->fit_to_down_side();}
}

void iip_opengl_l3event::scroll_up( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->scroll_up();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_up();}
}
void iip_opengl_l3event::scroll_to_up_side( void )
{
	if (NULL != this->_clp_main)
	{ 	    this->_clp_main->scroll_to_up_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_to_up_side();}
}
void iip_opengl_l3event::fit_to_up_side( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->fit_to_up_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->fit_to_up_side();}
}

void iip_opengl_l3event::scroll_right( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->scroll_right();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_right();}
}
void iip_opengl_l3event::scroll_to_right_side( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->scroll_to_right_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scroll_to_right_side();}
}
void iip_opengl_l3event::fit_to_right_side( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->fit_to_right_side();}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->fit_to_right_side();}
}

void iip_opengl_l3event::set_channel( int i_src, int i_tgt )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->set_channel(i_src,i_tgt);}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->set_channel(i_src,i_tgt);}
}

void iip_opengl_l3event::zoom_twice_at_pos( long l_x, long l_y )
{
	if (NULL == this->_clp_main) { return; }

	switch (this->_select_area(l_x,l_y)) {
	case E_WVIEW_AREA_EXCEPT: break;
	case E_WVIEW_AREA_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_twice_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub)) {
			this->_set_pos_and_zoom_from_main_to_sub();
		}
		break;
	case E_WVIEW_AREA_SEPARATOR: break;
	case E_WVIEW_AREA_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_twice_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_sub)
		&&  (NULL != this->_clp_main)) {
			this->_set_pos_and_zoom_from_sub_to_main();
		}
		break;
	};

}
void iip_opengl_l3event::zoom_half_at_pos( long l_x, long l_y )
{
	if (NULL == this->_clp_main) { return; }

	switch (this->_select_area(l_x,l_y)) {
	case E_WVIEW_AREA_EXCEPT: break;
	case E_WVIEW_AREA_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_half_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub)) {
			this->_set_pos_and_zoom_from_main_to_sub();
		}
		break;
	case E_WVIEW_AREA_SEPARATOR: break;
	case E_WVIEW_AREA_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_half_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_sub)
		&&  (NULL != this->_clp_main)) {
			this->_set_pos_and_zoom_from_sub_to_main();
		}
		break;
	};
}

void iip_opengl_l3event::zoom_up_at_pos( long l_x, long l_y )
{
	if (NULL == this->_clp_main) { return; }

	switch (this->_select_area(l_x,l_y)) {
	case E_WVIEW_AREA_EXCEPT: break;
	case E_WVIEW_AREA_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_up_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub)) {
			this->_set_pos_and_zoom_from_main_to_sub();
		}
		break;
	case E_WVIEW_AREA_SEPARATOR: break;
	case E_WVIEW_AREA_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_up_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_sub)
		&&  (NULL != this->_clp_main)) {
			this->_set_pos_and_zoom_from_sub_to_main();
		}
		break;
	};

}
void iip_opengl_l3event::zoom_down_at_pos( long l_x, long l_y )
{
	if (NULL == this->_clp_main) { return; }

	switch (this->_select_area(l_x,l_y)) {
	case E_WVIEW_AREA_EXCEPT: break;
	case E_WVIEW_AREA_MAIN:
		if (NULL != this->_clp_main)
		{	    this->_clp_main->zoom_down_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_main)
		&&  (NULL != this->_clp_sub)) {
			this->_set_pos_and_zoom_from_main_to_sub();
		}
		break;
	case E_WVIEW_AREA_SEPARATOR: break;
	case E_WVIEW_AREA_SUB:
		if (NULL != this->_clp_sub)
		{	    this->_clp_sub->zoom_down_at_pos(l_x,l_y);}
		if ((NULL != this->_clp_sub)
		&&  (NULL != this->_clp_main)) {
			this->_set_pos_and_zoom_from_sub_to_main();
		}
		break;
	};
}

void iip_opengl_l3event::drag_move_start( void )
{
	if (NULL != this->_clp_main) {
		this->_clp_main->drag_move_start();
	}
	if (NULL != this->_clp_sub ) {
		this->_clp_sub->drag_move_start();
	}
}
void iip_opengl_l3event::drag_move_stop( long l_move_x, long l_move_y )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->drag_move_stop(l_move_x,l_move_y);}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->drag_move_stop(l_move_x,l_move_y);}
}
void iip_opengl_l3event::drag_moving(
	long l_move_x
	,long l_move_y
	,double crop_aspect_ratio_w
	,double crop_aspect_ratio_h
) {
	if (NULL != this->_clp_main) {	   
	this->_clp_main->crop_aspect_ratio_w = crop_aspect_ratio_w;
	this->_clp_main->crop_aspect_ratio_h = crop_aspect_ratio_h;
	this->_clp_main->drag_moving(l_move_x,l_move_y);
	}
	if (NULL != this->_clp_sub ) {
	this->_clp_sub->crop_aspect_ratio_w = crop_aspect_ratio_w;
	this->_clp_sub->crop_aspect_ratio_h = crop_aspect_ratio_h;
	this->_clp_sub->drag_moving(l_move_x,l_move_y);
	}
}
int iip_opengl_l3event::mouse_moving( long l_mouse_x, long l_mouse_y )
{
	int	i_ret=0;

	if (NULL != this->_clp_main)
	{   i_ret = this->_clp_main->mouse_moving(l_mouse_x,l_mouse_y);}
	if (NULL != this->_clp_sub )
	{   i_ret = this->_clp_sub->mouse_moving(l_mouse_x,l_mouse_y);}
	return i_ret;
}

void iip_opengl_l3event::move_smooth( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->move_smooth();
		    this->_clp_main->reshape_opengl(); }
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->move_smooth();
		    this->_clp_sub->reshape_opengl(); }
}
void iip_opengl_l3event::move_pixel( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->move_pixel();
		    this->_clp_main->reshape_opengl(); }
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->move_pixel();
		    this->_clp_sub->reshape_opengl(); }
}
void iip_opengl_l3event::crop_area( int sw )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->set_i_crop_disp_sw(sw); }
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->set_i_crop_disp_sw(sw); }
}
void iip_opengl_l3event::escape_motion( void )
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->edit_crop_cancel(); }
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->edit_crop_cancel(); }
}

void iip_opengl_l3event::scrollbar_x(long l_val, long l_min, long l_max)
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->scrollbar_x(l_val,l_min,l_max);}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scrollbar_x(l_val,l_min,l_max);}
}
void iip_opengl_l3event::scrollbar_y(long l_val, long l_min, long l_max)
{
	if (NULL != this->_clp_main)
	{	    this->_clp_main->scrollbar_y(l_val,l_min,l_max);}
	if (NULL != this->_clp_sub )
	{	    this->_clp_sub->scrollbar_y(l_val,l_min,l_max);}
}

double iip_opengl_l3event::get_d_scrollbar_x_min( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_d_scrollbar_x_min();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_d_scrollbar_x_min();}
	return 0.0;
}
double iip_opengl_l3event::get_d_scrollbar_x_max( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_d_scrollbar_x_max();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_d_scrollbar_x_max();}
	return 0.0;
}
double iip_opengl_l3event::get_d_scrollbar_y_min( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_d_scrollbar_y_min();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_d_scrollbar_y_min();}
	return 0.0;
}
double iip_opengl_l3event::get_d_scrollbar_y_max( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_d_scrollbar_y_max();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_d_scrollbar_y_max();}
	return 0.0;
}

long iip_opengl_l3event::get_l_zoom( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_zoom();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_zoom();}
	return 0L;
}

/* 切抜き編集情報 */
long iip_opengl_l3event::get_l_width( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_width();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_width();}
	return 0L;
}
long iip_opengl_l3event::get_l_height( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_height();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_height();}
	return 0L;
}
long iip_opengl_l3event::get_l_crop_xp( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_crop_xp();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_crop_xp();}
	return 0L;
}
long iip_opengl_l3event::get_l_crop_yp( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_crop_yp();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_crop_yp();}
	return 0L;
}
long iip_opengl_l3event::get_l_crop_width( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_crop_width();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_crop_width();}
	return 0L;
}
long iip_opengl_l3event::get_l_crop_height( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_l_crop_height();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_l_crop_height();}
	return 0L;
}
E_SELECT_PART iip_opengl_l3event::get_e_select_part( void )
{
	if (NULL != this->_clp_main)
	{ return    this->_clp_main->get_e_select_part();}
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_e_select_part();}
	return E_SELECT_NOTHING;
}
void iip_opengl_l3event::set_crop_area(long l_xpos, long l_ypos, long l_xsize, long l_ysize )
{
	if (NULL != this->_clp_main) {
	 this->_clp_main->set_crop_area(l_xpos,l_ypos,l_xsize,l_ysize);
	}
	if (NULL != this->_clp_sub ) {
	 this->_clp_sub->set_crop_area(l_xpos,l_ypos,l_xsize,l_ysize);
	}
}

int iip_opengl_l3event::get_i_glcrop_xpos( void )
{
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_i_glcrop_xpos();}
	return 0;
}
int iip_opengl_l3event::get_i_glcrop_ypos( void )
{
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_i_glcrop_ypos();}
	return 0;
}
int iip_opengl_l3event::get_i_glcrop_width( void )
{
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_i_glcrop_width();}
	return 0;
}
int iip_opengl_l3event::get_i_glcrop_height( void )
{
	if (NULL != this->_clp_sub )
	{ return    this->_clp_sub->get_i_glcrop_height();}
	return 0;
}
iip_canvas *iip_opengl_l3event::get_clp_sub_canvas( void )
{
	return this->_clp_sub;
}
