#include "fltk_opengl.h"
#include "gts_master.h"
#include "gts_gui.h"

int fltk_opengl::handle( int event )
{
	/***int	cc;
	char	*cp;
	int	ii;***/

	switch(event) {
	/*
	 * Keyboard Events
	 */

	//case FL_KEYDOWN:
	//case FL_KEYBOARD:
	//case FL_KEYUP:
#if 0
	case FL_SHORTCUT:
		cc = Fl::event_key();
		cp = (char *)Fl::event_text();
		ii = Fl::event_length();
//pri_funct_msg_vr("key %c<%d>  text %c<%d>", cc,cc, cp[0],cp[0] );

		if (1 == ii) {
			cc = (int)(cp[0]);
		}

		/* キーの状態を記憶 */
		cl_gts_master.cl_fltk_event.set_keyboard( cc );

		/* キーの記憶から実行イベントを記憶 */
		cl_gts_master.cl_fltk_event.set_keyboard_to_act();

		/* 実行イベントと、idle callbackを設定 */
		cl_gts_master.reserve_by_key_event(
		 cl_gts_master.cl_fltk_event.get_e_act()
		);

		return 1;
#endif
	/*
	 * Mouse Events
	 */
	case FL_DRAG: /* The mouse has moved with a button held down. */
	case FL_MOVE: /* The mouse has moved without mouse drag. */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;}

		/* マウスの移動を記憶 */
		cl_gts_master.cl_fltk_event.set_mouse_motion(
			Fl::event_x(),Fl::event_y()
		);

		/* マウスの記憶から実行イベントを記憶 */
		cl_gts_master.cl_fltk_event.set_mouse_to_act();

		/* 実行イベントと、idle callbackを設定 */
		cl_gts_master.reserve(
		 cl_gts_master.cl_fltk_event.get_e_act()
		);

		return 1;

	case FL_PUSH: /* A mouse button has gone down */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;}

		/* マウスボタンの状態と位置を記憶 */
		cl_gts_master.cl_fltk_event.set_mouse_button(
			Fl::event_button(),
			FL_PUSH,
			Fl::event_x(),Fl::event_y()
		);

		/* マウスの記憶から実行イベントを記憶 */
		cl_gts_master.cl_fltk_event.set_mouse_to_act();

		/* 実行イベントと、idle callbackを設定 */
		//cl_gts_master.reserve(
		cl_gts_master.action(
		 cl_gts_master.cl_fltk_event.get_e_act()
		);

		/* (クリックした瞬間)2値化画像をscan画像に切替る指示 */
		cl_gts_master.cl_ogl_view.set_clicked_mouse_middle_button(
		 cl_gts_master.cl_fltk_event.clicked_mouse_middle_button()
		);

		/* ここで再表示 */
		cl_gts_gui.opengl_view->flush();

		return 1;

	case FL_RELEASE: /* A mouse button has been released. */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;}

		/* マウスボタンの状態と位置を記憶 */
		cl_gts_master.cl_fltk_event.set_mouse_button(
			Fl::event_button(),
			FL_RELEASE,
			Fl::event_x(),Fl::event_y()
		);

		/* マウスの記憶から実行イベントを記憶 */
		cl_gts_master.cl_fltk_event.set_mouse_to_act();

		/* 実行イベントと、idle callbackを設定 */
		//cl_gts_master.reserve(
		cl_gts_master.action(
		 cl_gts_master.cl_fltk_event.get_e_act()
		);

		/* (クリックした瞬間)2値化画像に(scan画像から)戻す */
		cl_gts_master.cl_ogl_view.set_clicked_mouse_middle_button(
			false
		);

		return 1;

	default:
		/* pass other events to the base class */
		return Fl_Gl_Window::handle(event);
	}
	return 0;
}
