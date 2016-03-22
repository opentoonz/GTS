#include <FL/Fl.H>
#include "fltk_event.h"
 
void fltk_event::set_mouse_button( int button, int state, long x, long y )
{
	this->_i_mouse_button_sw = ON;
	this->_i_mouse_which_button = button;
	this->_i_mouse_button_state = state;
	this->_l_mouse_x = x;
	this->_l_mouse_y = y;
}
void fltk_event::set_mouse_motion( long x, long y )
{
	this->_i_mouse_motion_sw = ON;
	this->_l_mouse_x = x;
	this->_l_mouse_y = y;
}
void fltk_event::set_mouse_to_act( void )
{
	E_ACT	e_act;
	e_act = E_ACT_NOTHING;

	/* マウスボタンが変化していないときは何もしないように設定 */
	if (OFF == this->_i_mouse_button_sw) {
		this->_i_mouse_which_button = 0;
		this->_i_mouse_button_state = 0;
	}
	else {
		this->_i_mouse_button_sw = OFF;
	}

	/*
		2005.05.25
		マウスボタンを押す、あるいは離したとき、別のイベントが
		動作中で、それが終る前に、また、マウスボタンを離す、押
		す、あるいは移動のイベントが起こると、動かないか、ドラ
		ッグや停止から始まったりする。
		動かない場合はそれで良いが、開始が無視されて、移動や停
		止から始まった場合、それらイベントは無視したい。
	*/

	/* マウスボタンの変化 */
	switch (this->_i_mouse_which_button){
	case FL_LEFT_MOUSE:
		if (FL_PUSH == this->_i_mouse_button_state){
			e_act = E_ACT_ZOOM_UP_TWICE_AT_POS;
		}
		break;

	case FL_MIDDLE_MOUSE:
		if (FL_PUSH == this->_i_mouse_button_state) {
			e_act = E_ACT_MOVE_START;

			this->set_i_mouse_middle_dragging( ON );
		} else
		if (FL_RELEASE==this->_i_mouse_button_state){
		  if (ON == this->_i_mouse_middle_dragging) {
			e_act = E_ACT_MOVE_STOP;

			this->set_i_mouse_middle_dragging( OFF );
		  }
		}
		break;

	case FL_RIGHT_MOUSE:
		if (FL_PUSH == this->_i_mouse_button_state){
			e_act = E_ACT_ZOOM_DOWN_HALF_AT_POS;
		}
		break;
	}

	/* マウスが移動した */
	if (ON == this->_i_mouse_motion_sw) {
		if (ON == this->_i_mouse_middle_dragging) {
			e_act = E_ACT_MOVE_DRAG;
		} else {
			e_act = E_ACT_MOVE_PASSIVE;
		}
		this->_i_mouse_motion_sw = OFF;
	}

	this->_e_act = e_act;
}

/*--------------------------------------------------------*/

void fltk_event::set_keyboard( int key )
{
	this->_i_keyboard_sw = ON;
	this->_i_keyboard = key;
}
void fltk_event::set_keyboard_to_act( void )
{
	E_ACT	e_act;
	e_act = E_ACT_NOTHING;

	/* キーを設定していないときは何もしないように設定 */
	if (OFF == this->_i_keyboard_sw) {
		this->_i_keyboard = 0;
	}
	else {
		this->_i_keyboard_sw = OFF;
	}

	switch ( this->_i_keyboard ) {
	case ' ': e_act = E_ACT_ALL_VIEW; break;

	case '=': e_act = E_ACT_ZOOM_UP_TWICE_AT_CEN; break;
	case '-': e_act = E_ACT_ZOOM_DOWN_HALF_AT_CEN; break;
	case '+': e_act = E_ACT_ZOOM_UP_STEP_AT_CEN; break;
	case '_': e_act = E_ACT_ZOOM_DOWN_STEP_AT_CEN; break;
	case '1': e_act = E_ACT_ZOOM_D16; break;
	case '2': e_act = E_ACT_ZOOM_D08; break;
	case '3': e_act = E_ACT_ZOOM_D04; break;
	case '4': e_act = E_ACT_ZOOM_D02; break;
	case '5': e_act = E_ACT_ZOOM_E01; break;
	case '6': e_act = E_ACT_ZOOM_U02; break;
	case '7': e_act = E_ACT_ZOOM_U04; break;
	case '8': e_act = E_ACT_ZOOM_U08; break;
	case '9': e_act = E_ACT_ZOOM_U16; break;
	case FL_Page_Up:   e_act = E_ACT_ZOOM_UP_TWICE_AT_POS; break;
	case FL_Page_Down: e_act = E_ACT_ZOOM_DOWN_HALF_AT_POS; break;
	case FL_Home: e_act = E_ACT_ZOOM_UP_STEP_AT_POS; break;
	case FL_End:  e_act = E_ACT_ZOOM_DOWN_STEP_AT_POS; break;

	case 'c': e_act = E_ACT_SCROLL_CENTER; break;
	case 'H': e_act = E_ACT_SCROLL_LEFT_SIDE; break;
	case 'L': e_act = E_ACT_SCROLL_RIGHT_SIDE; break;
	case 'K': e_act = E_ACT_SCROLL_UP_SIDE; break;
	case 'J': e_act = E_ACT_SCROLL_DOWN_SIDE; break;
	case 'h': e_act = E_ACT_SCROLL_LEFT_STEP; break;
	case 'l': e_act = E_ACT_SCROLL_RIGHT_STEP; break;
	case 'k': e_act = E_ACT_SCROLL_UP_STEP; break;
	case 'j': e_act = E_ACT_SCROLL_DOWN_STEP; break;
	case FL_Left:  e_act = E_ACT_SCROLL_LEFTSIDE_STEP; break;
	case FL_Right: e_act = E_ACT_SCROLL_RIGHTSIDE_STEP; break;
	case FL_Up:    e_act = E_ACT_SCROLL_UPSIDE_STEP; break;
	case FL_Down:  e_act = E_ACT_SCROLL_DOWNSIDE_STEP; break;
	case 'i': e_act = E_ACT_SCROLL_BLOCK; break;
	case 'I': e_act = E_ACT_SCROLL_SMOOTH; break;

	case 'f': e_act = E_ACT_CHANNEL_RGB_TO_RGB; break;
	case 'r': e_act = E_ACT_CHANNEL_RED_TO_RED; break;
	case 'g': e_act = E_ACT_CHANNEL_GRE_TO_GRE; break;
	case 'b': e_act = E_ACT_CHANNEL_BLU_TO_BLU; break;
	case 'a': e_act = E_ACT_CHANNEL_ALP_TO_GRAY; break;
	case 'R': e_act = E_ACT_CHANNEL_RED_TO_GRAY; break;
	case 'G': e_act = E_ACT_CHANNEL_GRE_TO_GRAY; break;
	case 'B': e_act = E_ACT_CHANNEL_BLU_TO_GRAY; break;

	case 'm': e_act = E_ACT_WVIEW_MAIN; break;
	case 's': e_act = E_ACT_WVIEW_SUB; break;
	case 'p': e_act = E_ACT_WVIEW_LR_PARALLEL; break;
	case 'P': e_act = E_ACT_WVIEW_UD_PARALLEL; break;
	case 'o': e_act = E_ACT_WVIEW_LR_ONION; break;
	case 'O': e_act = E_ACT_WVIEW_UD_ONION; break;

	case 'y': e_act = E_ACT_CROP_ON; break;
	case 'Y': e_act = E_ACT_CROP_OFF; break;

	case 27:  e_act = E_ACT_ESCAPE; break;
	case 'q': e_act = E_ACT_QUIT; break;
	}

	this->_e_act = e_act;
}
