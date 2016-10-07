#include <FL/Fl.H>
#include "fltk_event.h"
 
//FL_PUSH
void mouse_state::event_push( const int button ,const long x ,const long y )
{
	this->x_ = this->move_start_x_ = x;
	this->y_ = this->move_start_y_ = y;
	this->which_button_ = button;
	this->button_click_sw_  = true;
}

//FL_RELEASE
void mouse_state::event_release( const int button ,const long x ,const long y )
{
	this->x_ = x;
	this->y_ = y;
	this->which_button_ = button;
	this->button_click_sw_ = false;
}

//FL_MOVE
void mouse_state::event_move( const long x ,const long y )
{
	this->x_ = x;
	this->y_ = y;
}

//FL_DRAG
void mouse_state::event_drag( const long x ,const long y )
{
	this->x_ = x;
	this->y_ = y;
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
