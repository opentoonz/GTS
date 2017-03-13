#include <string.h>	/* memset() */
#include <stdlib.h>	/* exit() */
#include <ctype.h>

#include "pri.h"
#include "fltk_opengl.h"

#include "gts_master.h"
#include "gts_gui.h"

/*--------------------------------------------------------*/

void gts_master::_all_view( void )
{
	this->cl_ogl_view.all_view();
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}

void gts_master::_zoom_up_twice_at_cen( void )
{
	this->cl_ogl_view.zoom_twice_at_center();
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_down_half_at_cen( void )
{
	this->cl_ogl_view.zoom_half_at_center();
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_up_step_at_cen( void )
{
	this->cl_ogl_view.zoom_up_at_center();
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_down_step_at_cen( void )
{
	this->cl_ogl_view.zoom_down_at_center();
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}

void gts_master::__zoom_num( long l_zoom )
{
	this->cl_ogl_view.zoom_num( l_zoom );

	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_d16( void ) { this->__zoom_num(-16L);}
void gts_master::_zoom_d08( void ) { this->__zoom_num(-8L ); }
void gts_master::_zoom_d04( void ) { this->__zoom_num(-4L ); }
void gts_master::_zoom_d02( void ) { this->__zoom_num(-2L ); }
void gts_master::_zoom_e01( void ) { this->__zoom_num( 1L ); }
void gts_master::_zoom_u02( void ) { this->__zoom_num( 2L ); }
void gts_master::_zoom_u04( void ) { this->__zoom_num( 4L ); }
void gts_master::_zoom_u08( void ) { this->__zoom_num( 8L ); }
void gts_master::_zoom_u16( void ) { this->__zoom_num( 16L); }

void gts_master::_zoom_up_twice_at_pos( void )
{
	this->cl_ogl_view.zoom_twice_at_pos(
		cl_gts_master.cl_fltk_event.cl_mouse_state.x()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y()
	);
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_down_half_at_pos( void )
{
	this->cl_ogl_view.zoom_half_at_pos(
		cl_gts_master.cl_fltk_event.cl_mouse_state.x()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y()
	);
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_up_step_at_pos( void )
{
	this->cl_ogl_view.zoom_up_at_pos(
		cl_gts_master.cl_fltk_event.cl_mouse_state.x()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y()
	);
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_zoom_down_step_at_pos( void )
{
	this->cl_ogl_view.zoom_down_at_pos(
		cl_gts_master.cl_fltk_event.cl_mouse_state.x()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y()
	);
	this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}

void gts_master::_scroll_center( void )
{
	this->cl_ogl_view.scroll_center();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_left_side( void )
{	      this->cl_ogl_view.fit_to_left_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_right_side( void )
{	      this->cl_ogl_view.fit_to_right_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_up_side( void )
{	      this->cl_ogl_view.fit_to_up_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_down_side( void )
{	      this->cl_ogl_view.fit_to_down_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}

void gts_master::_scroll_left_step( void )
{	      this->cl_ogl_view.scroll_left();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_right_step( void )
{	      this->cl_ogl_view.scroll_right();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_up_step( void )
{	      this->cl_ogl_view.scroll_up();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_down_step( void )
{	      this->cl_ogl_view.scroll_down();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_leftside_step( void )
{	      this->cl_ogl_view.scroll_to_left_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_rightside_step( void )
{	      this->cl_ogl_view.scroll_to_right_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_upside_step( void )
{	      this->cl_ogl_view.scroll_to_up_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_downside_step( void )
{	      this->cl_ogl_view.scroll_to_down_side();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}

void gts_master::_scroll_block( void )
{
	this->cl_ogl_view.move_pixel();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_smooth( void )
{
	this->cl_ogl_view.move_smooth();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_scroll_x_absolute( void )
{
	this->cl_ogl_view.scrollbar_x(
		this->cl_fltk_event.get_l_scrollbar_x_val(),
		this->cl_fltk_event.get_l_scrollbar_x_min(),
		this->cl_fltk_event.get_l_scrollbar_x_max()
	);
	cl_gts_gui.opengl_view->redraw();
}
void gts_master::_scroll_y_absolute( void )
{
	this->cl_ogl_view.scrollbar_y(
		this->cl_fltk_event.get_l_scrollbar_y_val(),
		this->cl_fltk_event.get_l_scrollbar_y_min(),
		this->cl_fltk_event.get_l_scrollbar_y_max()
	);
	cl_gts_gui.opengl_view->redraw();
}

void gts_master::_move_hover( void )
{
	if (ON == this->cl_ogl_view.mouse_moving(
		cl_gts_master.cl_fltk_event.cl_mouse_state.x()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y()
	)) {
		cl_gts_gui.opengl_view->redraw();
	}
}
void gts_master::_move_start( void )
{
	/* 1 選択可能状態にする */
	this->cl_ogl_view.set_select_action_sw(true);

	/* 2 選択する */
	this->_move_hover();/* 再選択をする */

	/* 3 選択から移動の開始点の設定 */
	this->cl_ogl_view.drag_move_start();
}
void gts_master::_move_drag( void )
{
	/*
	考察
	DRAGによる表示がidleにより遅れて処理する場合
	マウスReleaseした後に行われることがあるかもしれない
	*/

	/* なにもつかんでいないので何もしない */
	if (this->cl_ogl_view.get_e_select_part() == E_SELECT_NOTHING) {
		return;
	}

	mouse_state& ms = cl_gts_master.cl_fltk_event.cl_mouse_state;
	if (!(
	/* 画像を移動するのは、マウス左ボタンで行う */
	(	this->cl_ogl_view.get_e_select_part() == E_SELECT_IMAGE
		&& ms.which_button() == FL_LEFT_MOUSE
	)
	/* Crop枠の変更は、マウス左ボタンで行う */
	||
	(	this->cl_ogl_view.get_e_select_part() != E_SELECT_IMAGE
		&& ms.which_button() == FL_LEFT_MOUSE
	)
	)) {
		/* ...のでなければ動作しないこと */
		return;
	}

	/* Cropエリア比が指定されていたらそれをセットし、指定なしならゼロ */
	double crop_aspect_ratio_w = 0.0;
	double crop_aspect_ratio_h = 0.0;

	/* 画像上のCrop修正をするときは自動的にAspect Ratio指定解除する */
	cl_gts_gui.choice_area_aspect_ratio_selecter->value(0);

	/* 画像上のCrop修正でもAspect Ratio固定する --> 将来... */
/************
	if (0 < cl_gts_master.cl_memo_scan_area.aspect_ratios.size()
	&&  0 < cl_gts_gui.choice_area_aspect_ratio_selecter->value()
	) {
		preset_rwh ratio =
		cl_gts_master.cl_memo_scan_area.aspect_ratios.at(
		cl_gts_gui.choice_area_aspect_ratio_selecter->value()
			-1
		);
		crop_aspect_ratio_w = ratio.w;
		crop_aspect_ratio_h = ratio.h;
	}
*************/

	/* マウスポインター移動に合わせて画像表示パラメータを設定 */
	this->cl_ogl_view.drag_moving(
		cl_gts_master.cl_fltk_event.cl_mouse_state.x_move()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y_move()
		, crop_aspect_ratio_w
		, crop_aspect_ratio_h
	);

	/* 画像再表示 */
	cl_gts_gui.opengl_view->redraw();

	/* scroll bar設定 */
	this->set_scrollbar();

	/* 画像表示パラメータの変更に合わせてGUIの値の変更 */
	this->cl_area_and_rot90.copy_opengl_to_value(
	 this->cl_ogl_view.get_e_select_part()
	);
}
void gts_master::_move_stop( void )
{
	/* 左ボタンでマウスリリースしたときCropを選択している */
	if (cl_gts_master.cl_fltk_event.cl_mouse_state.which_button()
	    == FL_LEFT_MOUSE
	&&  this->cl_ogl_view.get_e_select_part() != E_SELECT_NOTHING
	&&  this->cl_ogl_view.get_e_select_part() != E_SELECT_IMAGE
	&&  this->cl_ogl_view.get_e_select_part() == 
	    this->cl_ogl_view.get_select_part(
		  cl_gts_master.cl_fltk_event.cl_mouse_state.x()
		, cl_gts_master.cl_fltk_event.cl_mouse_state.y()
	    )
	) {
		/* 非選択状態に。hover時に選択しない */
		this->cl_ogl_view.set_select_action_sw(false);
	}
}

void gts_master::__set_channel( int i_src, int i_tgt )
{
	this->cl_ogl_view.set_channel( i_src, i_tgt );
	cl_gts_gui.opengl_view->redraw();
}
void gts_master::_channel_rgb_to_rgb( void )
{	  this->__set_channel(CH_RGB,CH_RGB);}
void gts_master::_channel_red_to_red( void )
{	  this->__set_channel(CH_RED,CH_RED);}
void gts_master::_channel_gre_to_gre( void )
{	  this->__set_channel(CH_GRE,CH_GRE);}
void gts_master::_channel_blu_to_blu( void )
{	  this->__set_channel(CH_BLU,CH_BLU);}
void gts_master::_channel_alp_to_gray( void )
{	  this->__set_channel(CH_ALP,CH_ALP);}
void gts_master::_channel_red_to_gray( void )
{	  this->__set_channel(CH_RED,CH_ALP);}
void gts_master::_channel_gre_to_gray( void )
{	  this->__set_channel(CH_GRE,CH_ALP);}
void gts_master::_channel_blu_to_gray( void )
{	  this->__set_channel(CH_BLU,CH_ALP);}

void gts_master::_wview_main( void )
{
	this->cl_ogl_view.wview_main();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_wview_sub( void )
{
	this->cl_ogl_view.wview_sub();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_wview_lr_parallel( void )
{
	this->cl_ogl_view.wview_lr_parallel();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_wview_ud_parallel( void )
{
	this->cl_ogl_view.wview_ud_parallel();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_wview_lr_onion( void )
{
	this->cl_ogl_view.wview_lr_onion();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}
void gts_master::_wview_ud_onion( void )
{
	this->cl_ogl_view.wview_ud_onion();
	//this->print_window_headline();
	cl_gts_gui.opengl_view->redraw();
	this->set_scrollbar();
}

void gts_master::_crop_on( void )
{
	this->cl_ogl_view.set_crop_disp_sw(ON);
	cl_gts_gui.opengl_view->redraw();
}
void gts_master::_crop_off( void )
{
	this->cl_ogl_view.set_crop_disp_sw(OFF);
	cl_gts_gui.opengl_view->redraw();
}

void gts_master::_escape( void )
{
	if (
 	this->cl_fltk_event.cl_mouse_state.which_button()==FL_LEFT_MOUSE
	&& this->cl_fltk_event.cl_mouse_state.is_clicked()
	) {
		this->cl_ogl_view.escape_motion();
		this->cl_fltk_event.cl_mouse_state.escape_clicked();
		cl_gts_gui.opengl_view->redraw();
	}
}
void gts_master::_quit( void )
{
	exit(0);
}

/*--------------------------------------------------------*/
/*---------------------- 即実行する ----------------------*/
void gts_master::action( E_ACT e_act )
{
/******
 switchだと、なぜか
gts_event.cxx:309: 警告: label `E_ACT_ALL_VIEW' defined but not used
gts_event.cxx:366: 警告: 列挙値 `E_ACT_ALL_VIEW' は switch 内で扱われていません
となり、実行しない。原因不明(2005.05.25)

 switch ( e_act ) {
 E_ACT_ALL_VIEW:               this->_all_view(); break;
 E_ACT_ZOOM_IN_TWICE_AT_CEN:   this->_zoom_up_twice_at_cen(); break;
 E_ACT_ZOOM_OUT_HALF_AT_CEN:   this->_zoom_down_half_at_cen();break;
 E_ACT_ZOOM_IN_STEP_AT_CEN:    this->_zoom_up_step_at_cen(); break;
 E_ACT_ZOOM_OUT_STEP_AT_CEN:   this->_zoom_down_step_at_cen();break;
 E_ACT_ZOOM_D16:               this->_zoom_d16(); break;
 E_ACT_ZOOM_D08:               this->_zoom_d08(); break;
 E_ACT_ZOOM_D04:               this->_zoom_d04(); break;
 E_ACT_ZOOM_D02:               this->_zoom_d02(); break;
 E_ACT_ZOOM_E01:               this->_zoom_e01(); break;
 E_ACT_ZOOM_U02:               this->_zoom_u02(); break;
 E_ACT_ZOOM_U04:               this->_zoom_u04(); break;
 E_ACT_ZOOM_U08:               this->_zoom_u08(); break;
 E_ACT_ZOOM_U16:               this->_zoom_u16(); break;
 E_ACT_ZOOM_IN_TWICE_AT_POS:   this->_zoom_up_twice_at_pos(); break;
 E_ACT_ZOOM_OUT_HALF_AT_POS:  this->_zoom_down_half_at_pos(); break;
 E_ACT_ZOOM_IN_STEP_AT_POS:    this->_zoom_up_step_at_pos(); break;
 E_ACT_ZOOM_OUT_STEP_AT_POS:  this->_zoom_down_step_at_pos(); break;
 E_ACT_SCROLL_CENTER:          this->_scroll_center(); break;
 E_ACT_SCROLL_LEFT_SIDE:       this->_scroll_left_side(); break;
 E_ACT_SCROLL_RIGHT_SIDE:      this->_scroll_right_side(); break;
 E_ACT_SCROLL_UP_SIDE:         this->_scroll_up_side(); break;
 E_ACT_SCROLL_DOWN_SIDE:       this->_scroll_down_side(); break;
 E_ACT_SCROLL_LEFT_STEP:       this->_scroll_left_step(); break;
 E_ACT_SCROLL_RIGHT_STEP:      this->_scroll_right_step(); break;
 E_ACT_SCROLL_UP_STEP:         this->_scroll_up_step(); break;
 E_ACT_SCROLL_DOWN_STEP:       this->_scroll_down_step(); break;
 E_ACT_SCROLL_LEFTSIDE_STEP:   this->_scroll_leftside_step(); break;
 E_ACT_SCROLL_RIGHTSIDE_STEP:  this->_scroll_rightside_step();break;
 E_ACT_SCROLL_UPSIDE_STEP:     this->_scroll_upside_step(); break;
 E_ACT_SCROLL_DOWNSIDE_STEP:   this->_scroll_downside_step(); break;
 E_ACT_SCROLL_BLOCK:           this->_scroll_block(); break;
 E_ACT_SCROLL_SMOOTH:          this->_scroll_smooth(); break;
 E_ACT_SCROLL_X_ABSOLUTE:      this->_scroll_x_absolute(); break;
 E_ACT_SCROLL_Y_ABSOLUTE:      this->_scroll_y_absolute(); break;
 E_ACT_MOVE_START:             this->_move_start(); break;
 E_ACT_MOVE_DRAG:              this->_move_drag();break;
 E_ACT_MOVE_STOP:              break;
 E_ACT_MOVE_HOVER:             this->_move_hover(); break;
 E_ACT_CHANNEL_RGB_TO_RGB:     this->_channel_rgb_to_rgb(); break;
 E_ACT_CHANNEL_RED_TO_RED:     this->_channel_red_to_red(); break;
 E_ACT_CHANNEL_GRE_TO_GRE:     this->_channel_gre_to_gre(); break;
 E_ACT_CHANNEL_BLU_TO_BLU:     this->_channel_blu_to_blu(); break;
 E_ACT_CHANNEL_ALP_TO_GRAY:    this->_channel_alp_to_gray(); break;
 E_ACT_CHANNEL_RED_TO_GRAY:    this->_channel_red_to_gray(); break;
 E_ACT_CHANNEL_GRE_TO_GRAY:    this->_channel_gre_to_gray(); break;
 E_ACT_CHANNEL_BLU_TO_GRAY:    this->_channel_blu_to_gray(); break;
 E_ACT_WVIEW_MAIN:             this->_wview_main(); break;
 E_ACT_WVIEW_SUB:              this->_wview_sub(); break;
 E_ACT_WVIEW_LR_PARALLEL:      this->_wview_lr_parallel(); break;
 E_ACT_WVIEW_UD_PARALLEL:      this->_wview_ud_parallel(); break;
 E_ACT_WVIEW_LR_ONION:         this->_wview_lr_onion(); break;
 E_ACT_WVIEW_UD_ONION:         this->_wview_ud_onion(); break;
 E_ACT_CROP_ON:                this->_crop_on(); break;
 E_ACT_CROP_OFF:               this->_crop_off(); break;
 E_ACT_ESCAPE:                 this->_escape(); break;
 E_ACT_QUIT:                   this->_quit(); break;
 }**********/

	if      (E_ACT_ALL_VIEW == e_act) {
		this->_all_view();
	}
	else if (E_ACT_ZOOM_IN_TWICE_AT_CEN == e_act) {
		this->_zoom_up_twice_at_cen();
	}
	else if (E_ACT_ZOOM_OUT_HALF_AT_CEN == e_act) {
		this->_zoom_down_half_at_cen();
	}
	else if (E_ACT_ZOOM_IN_STEP_AT_CEN == e_act) {
		this->_zoom_up_step_at_cen();
	}
	else if (E_ACT_ZOOM_OUT_STEP_AT_CEN == e_act) {
		this->_zoom_down_step_at_cen();
	}
	else if (E_ACT_ZOOM_D16 == e_act) {
		this->_zoom_d16();
	}
	else if (E_ACT_ZOOM_D08 == e_act) {
		this->_zoom_d08();
	}
	else if (E_ACT_ZOOM_D04 == e_act) {
		this->_zoom_d04();
	}
	else if (E_ACT_ZOOM_D02 == e_act) {
		this->_zoom_d02();
	}
	else if (E_ACT_ZOOM_E01 == e_act) {
		this->_zoom_e01();
	}
	else if (E_ACT_ZOOM_U02 == e_act) {
		this->_zoom_u02();
	}
	else if (E_ACT_ZOOM_U04 == e_act) {
		this->_zoom_u04();
	}
	else if (E_ACT_ZOOM_U08 == e_act) {
		this->_zoom_u08();
	}
	else if (E_ACT_ZOOM_U16 == e_act) {
		this->_zoom_u16();
	}
	else if (E_ACT_ZOOM_IN_TWICE_AT_POS == e_act) {
		this->_zoom_up_twice_at_pos();
	}
	else if (E_ACT_ZOOM_OUT_HALF_AT_POS == e_act) {
		this->_zoom_down_half_at_pos();
	}
	else if (E_ACT_ZOOM_IN_STEP_AT_POS == e_act) {
		this->_zoom_up_step_at_pos();
	}
	else if (E_ACT_ZOOM_OUT_STEP_AT_POS == e_act) {
		this->_zoom_down_step_at_pos();
	}
	else if (E_ACT_SCROLL_CENTER == e_act) {
		this->_scroll_center();
	}
	else if (E_ACT_SCROLL_LEFT_SIDE == e_act) {
		this->_scroll_left_side();
	}
	else if (E_ACT_SCROLL_RIGHT_SIDE == e_act) {
		this->_scroll_right_side();
	}
	else if (E_ACT_SCROLL_UP_SIDE == e_act) {
		this->_scroll_up_side();
	}
	else if (E_ACT_SCROLL_DOWN_SIDE == e_act) {
		this->_scroll_down_side();
	}
	else if (E_ACT_SCROLL_LEFT_STEP == e_act) {
		this->_scroll_left_step();
	}
	else if (E_ACT_SCROLL_RIGHT_STEP == e_act) {
		this->_scroll_right_step();
	}
	else if (E_ACT_SCROLL_UP_STEP == e_act) {
		this->_scroll_up_step();
	}
	else if (E_ACT_SCROLL_DOWN_STEP == e_act) {
		this->_scroll_down_step();
	}
	else if (E_ACT_SCROLL_LEFTSIDE_STEP == e_act) {
		this->_scroll_leftside_step();
	}
	else if (E_ACT_SCROLL_RIGHTSIDE_STEP == e_act) {
		this->_scroll_rightside_step();
	}
	else if (E_ACT_SCROLL_UPSIDE_STEP == e_act) {
		this->_scroll_upside_step();
	}
	else if (E_ACT_SCROLL_DOWNSIDE_STEP == e_act) {
		this->_scroll_downside_step();
	}
	else if (E_ACT_SCROLL_BLOCK == e_act) {
		this->_scroll_block();
	}
	else if (E_ACT_SCROLL_SMOOTH == e_act) {
		this->_scroll_smooth();
	}
	else if (E_ACT_SCROLL_X_ABSOLUTE == e_act) {
		this->_scroll_x_absolute();
	}
	else if (E_ACT_SCROLL_Y_ABSOLUTE == e_act) {
		this->_scroll_y_absolute();
	}
	else if (E_ACT_MOVE_HOVER == e_act) {
		this->_move_hover();
	}
	else if (E_ACT_MOVE_START == e_act) {
		this->_move_start();
	}
	else if (E_ACT_MOVE_DRAG == e_act) {
		this->_move_drag();
	}
	else if (E_ACT_MOVE_STOP == e_act) {
		this->_move_stop();
	}
	else if (E_ACT_CHANNEL_RGB_TO_RGB == e_act) {
		this->_channel_rgb_to_rgb();
	}
	else if (E_ACT_CHANNEL_RED_TO_RED == e_act) {
		this->_channel_red_to_red();
	}
	else if (E_ACT_CHANNEL_GRE_TO_GRE == e_act) {
		this->_channel_gre_to_gre();
	}
	else if (E_ACT_CHANNEL_BLU_TO_BLU == e_act) {
		this->_channel_blu_to_blu();
	}
	else if (E_ACT_CHANNEL_ALP_TO_GRAY == e_act) {
		this->_channel_alp_to_gray();
	}
	else if (E_ACT_CHANNEL_RED_TO_GRAY == e_act) {
		this->_channel_red_to_gray();
	}
	else if (E_ACT_CHANNEL_GRE_TO_GRAY == e_act) {
		this->_channel_gre_to_gray();
	}
	else if (E_ACT_CHANNEL_BLU_TO_GRAY == e_act) {
		this->_channel_blu_to_gray();
	}
	else if (E_ACT_WVIEW_MAIN == e_act) {
		this->_wview_main();
	}
	else if (E_ACT_WVIEW_SUB == e_act) {
		this->_wview_sub();
	}
	else if (E_ACT_WVIEW_LR_PARALLEL == e_act) {
		this->_wview_lr_parallel();
	}
	else if (E_ACT_WVIEW_UD_PARALLEL == e_act) {
		this->_wview_ud_parallel();
	}
	else if (E_ACT_WVIEW_LR_ONION == e_act) {
		this->_wview_lr_onion();
	}
	else if (E_ACT_WVIEW_UD_ONION == e_act) {
		this->_wview_ud_onion();
	}
	else if (E_ACT_CROP_ON == e_act) {
		this->_crop_on();
	}
	else if (E_ACT_CROP_OFF == e_act) {
		this->_crop_off();
	}
	else if (E_ACT_ESCAPE == e_act) {
		this->_escape();
	}
	else if (E_ACT_QUIT == e_act) {
		this->_quit();
	}
}

/*--------------------------------------------------------*/
/*--------------- アイドリング時に実行する ---------------*/
static void _fltk_cb_idle( void *vp )
{
	/* 予約時指定の動作で処理実行 */
	cl_gts_master.action( cl_gts_master.cl_fltk_event.get_e_act() );

	/* 処理の予約を解除 */
	cl_gts_master.cl_fltk_event.set_e_act( E_ACT_NOTHING );

	/* 処理が済んだらidle設定を解除 */
	if (Fl::has_idle(_fltk_cb_idle)) { Fl::remove_idle(_fltk_cb_idle); }
}

/* reserve()は座標値など連続するイベントで溜まって対応できない処理で使用 */
void gts_master::reserve( E_ACT e_act )
{
	/* 予約が有効でなければ何もしない */
	if (E_ACT_NOTHING == e_act) { return; }

	/* 未処理のidle待ちがあるならそれを優先し今回処理は捨てる */
//	if (Fl::has_idle(_fltk_cb_idle)) { return; }

	/* 未処理のidle待ちがあるならそれを削除し今回処理を優先 */
	if (Fl::has_idle(_fltk_cb_idle)) { Fl::remove_idle(_fltk_cb_idle); }

	/* 動作設定をして... */
	cl_gts_master.cl_fltk_event.set_e_act( e_act );

	/* 実行の予約をする */
	Fl::add_idle(_fltk_cb_idle);
}
/*------ ショートカット、あるいはGUIイベントの実行 -------*/
void gts_master::reserve_by_menu( E_ACT e_act )
{ if (ON == this->_i_enable_act_menu_sw) { this->reserve(e_act); } }

/*------------- handle()によるイベントの実行 -------------*/
void gts_master::reserve_by_key_event( E_ACT e_act )
{ if (ON == this->_i_enable_act_key_event_sw) {this->reserve(e_act); } }

/*---------- GUIのScrollBarによるイベントの実行 ----------*/
void gts_master::reserve_by_scroll_x( int ii )
{
	this->cl_fltk_event.set_l_scrollbar_x_val((long)ii);
	this->reserve(E_ACT_SCROLL_X_ABSOLUTE);
}
void gts_master::reserve_by_scroll_y( int ii )
{
	this->cl_fltk_event.set_l_scrollbar_y_val((long)ii);
	this->reserve(E_ACT_SCROLL_Y_ABSOLUTE);
}
