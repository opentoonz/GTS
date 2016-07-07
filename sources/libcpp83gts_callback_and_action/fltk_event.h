#ifndef __fltk_event_h__
#define __fltk_event_h__

#include "ptbl_returncode.h"

typedef enum {
E_ACT_NOTHING = 1,		/* 実行予約はなにもない */
E_ACT_ALL_VIEW,			/* 全体を(step倍率で)表示 */
E_ACT_ZOOM_UP_TWICE_AT_CEN,	/* Viewportの中心で2倍づつ拡大 */
E_ACT_ZOOM_DOWN_HALF_AT_CEN,	/* Viewportの中心で1/2倍づつ縮小 */
E_ACT_ZOOM_UP_STEP_AT_CEN,	/* Viewportの中心で1stepづつ拡大 */
E_ACT_ZOOM_DOWN_STEP_AT_CEN,	/* Viewportの中心で1stepづつ縮小 */
E_ACT_ZOOM_D16,			/* 縮小1/16倍 */
E_ACT_ZOOM_D08,			/* 縮小1/8倍 */
E_ACT_ZOOM_D04,			/* 縮小1/4倍 */
E_ACT_ZOOM_D02,			/* 縮小1/2倍 */
E_ACT_ZOOM_E01,			/* 等倍1倍 */
E_ACT_ZOOM_U02,			/* 拡大2倍 */
E_ACT_ZOOM_U04,			/* 拡大4倍 */
E_ACT_ZOOM_U08,			/* 拡大8倍 */
E_ACT_ZOOM_U16,			/* 拡大16倍 */
E_ACT_ZOOM_UP_TWICE_AT_POS,	/* 指定位置で2倍づつ拡大 */
E_ACT_ZOOM_DOWN_HALF_AT_POS,	/* 指定位置で1/2倍づつ縮小 */
E_ACT_ZOOM_UP_STEP_AT_POS,	/* 指定位置で1stepづつ拡大 */
E_ACT_ZOOM_DOWN_STEP_AT_POS,	/* 指定位置で1stepづつ縮小 */
E_ACT_SCROLL_CENTER,		/* 中心へ移動 */
E_ACT_SCROLL_LEFT_SIDE,		/* 左端へ移動 */
E_ACT_SCROLL_RIGHT_SIDE,	/* 右端へ移動 */
E_ACT_SCROLL_UP_SIDE,		/* 上端へ移動 */
E_ACT_SCROLL_DOWN_SIDE,		/* 下端へ移動 */
E_ACT_SCROLL_LEFT_STEP,		/* 左方向へ移動 */
E_ACT_SCROLL_RIGHT_STEP,	/* 右方向へ移動 */
E_ACT_SCROLL_UP_STEP,		/* 上方向へ移動 */
E_ACT_SCROLL_DOWN_STEP,		/* 左方向へ移動 */
E_ACT_SCROLL_LEFTSIDE_STEP,	/* 左端方向へ移動 */
E_ACT_SCROLL_RIGHTSIDE_STEP,	/* 右端方向へ移動 */
E_ACT_SCROLL_UPSIDE_STEP,	/* 上端方向へ移動 */
E_ACT_SCROLL_DOWNSIDE_STEP,	/* 下端方向へ移動 */
E_ACT_SCROLL_BLOCK,		/* データ上のPixel単位の移動(拡大時) */
E_ACT_SCROLL_SMOOTH,		/* スムース移動(拡大時) */
E_ACT_SCROLL_X_ABSOLUTE,	/* 横方向の絶対位置へ移動(scrollbar) */
E_ACT_SCROLL_Y_ABSOLUTE,	/* 縦方向の絶対位置へ移動(scrollbar) */
E_ACT_MOVE_START,		/* 連続移動の開始 */
E_ACT_MOVE_DRAG,		/* 連続移動中 */
E_ACT_MOVE_STOP,		/* 連続移動の停止 */
E_ACT_MOVE_PASSIVE,		/* 移動 */
E_ACT_CHANNEL_RGB_TO_RGB,	/* RGB表示 */
E_ACT_CHANNEL_RED_TO_RED,	/* Red  チャンネルを赤く表示 */
E_ACT_CHANNEL_GRE_TO_GRE,	/* Greenチャンネルを緑に表示 */
E_ACT_CHANNEL_BLU_TO_BLU,	/* Blue チャンネルを青く表示 */
E_ACT_CHANNEL_ALP_TO_GRAY,	/* Alphaチャンネルを白黒表示 */
E_ACT_CHANNEL_RED_TO_GRAY,	/* Red  チャンネルを白黒表示 */
E_ACT_CHANNEL_GRE_TO_GRAY,	/* Greenチャンネルを白黒表示 */
E_ACT_CHANNEL_BLU_TO_GRAY,	/* Blue チャンネルを白黒表示 */
E_ACT_WVIEW_MAIN,		/* 2画像の内、メイン画像を表示 */
E_ACT_WVIEW_SUB,		/* 2画像の内、サブ画像を表示 */
E_ACT_WVIEW_LR_PARALLEL,	/* 2画像を左右に表示 */
E_ACT_WVIEW_UD_PARALLEL,	/* 2画像を上下に表示 */
E_ACT_WVIEW_LR_ONION,		/* 2画像を左右に皮むき表示(予約) */
E_ACT_WVIEW_UD_ONION,		/* 2画像を上下に皮むき表示(予約) */
E_ACT_CROP_ON,			/* 切抜き枠表示と編集 */
E_ACT_CROP_OFF,			/* 切抜き枠非表示 */
E_ACT_ESCAPE,			/* 実行キャンセル */
E_ACT_QUIT			/* 終了 */
} E_ACT;

/* 各イベントの最後の状態を保持するクラス(イベントを得ることはしない) */
class fltk_event {
public:
	fltk_event() {
		this->_e_act = E_ACT_NOTHING;

		this->_i_keyboard_sw = OFF;
		this->_i_keyboard = 0;

		this->_i_mouse_motion_sw = OFF;
		this->_i_mouse_button_sw = OFF;

		this->_l_mouse_x = 0L;
		this->_l_mouse_y = 0L;

		this->_l_movestart_mouse_x = 0L;
		this->_l_movestart_mouse_y = 0L;

		this->_i_mouse_left_dragging = OFF;
		this->_i_mouse_middle_dragging = OFF;

		this->_i_mouse_which_button = 0;
		this->_i_mouse_button_state = 0;

		this->_l_scrollbar_x_val = 0L;
		this->_l_scrollbar_x_min = 0L;
		this->_l_scrollbar_x_max = 0L;
		this->_l_scrollbar_y_val = 0L;
		this->_l_scrollbar_y_min = 0L;
		this->_l_scrollbar_y_max = 0L;
	}

	void  set_e_act( E_ACT e_act )   {this->_e_act = e_act;}
	E_ACT get_e_act( void )  { return this->_e_act; }

	void set_mouse_motion( long x, long y );
	void set_mouse_button( int button, int state, long x, long y );
	void set_mouse_to_act( void );

	void set_keyboard( int key );
	void set_keyboard_to_act( void );

	void set_l_scrollbar_x_val( long ll )
	{ this->_l_scrollbar_x_val = ll; }
	long get_l_scrollbar_x_val( void ) { return
	  this->_l_scrollbar_x_val; }
	void set_l_scrollbar_x_min( long ll )
	{ this->_l_scrollbar_x_min = ll; }
	long get_l_scrollbar_x_min( void ) { return
	  this->_l_scrollbar_x_min; }
	void set_l_scrollbar_x_max( long ll )
	{ this->_l_scrollbar_x_max = ll; }
	long get_l_scrollbar_x_max( void ) { return
	  this->_l_scrollbar_x_max; }

	void set_l_scrollbar_y_val( long ll )
	{ this->_l_scrollbar_y_val = ll; }
	long get_l_scrollbar_y_val( void ) { return
	  this->_l_scrollbar_y_val; }
	void set_l_scrollbar_y_min( long ll )
	{ this->_l_scrollbar_y_min = ll; }
	long get_l_scrollbar_y_min( void ) { return
	  this->_l_scrollbar_y_min; }
	void set_l_scrollbar_y_max( long ll )
	{ this->_l_scrollbar_y_max = ll; }
	long get_l_scrollbar_y_max( void ) { return
	  this->_l_scrollbar_y_max; }

	void set_l_movestart_mouse_x( long ll )
	{ this->_l_movestart_mouse_x = ll; }
	void set_l_movestart_mouse_y( long ll )
	{ this->_l_movestart_mouse_y = ll; }

	void set_i_mouse_middle_dragging( int sw )
	{ this->_i_mouse_middle_dragging=sw; }

	long get_l_mouse_x( void ) { return this->_l_mouse_x; }
	long get_l_mouse_y( void ) { return this->_l_mouse_y; }

	long        get_l_movestart_mouse_x( void )
	{ return this->_l_movestart_mouse_x; }
	long        get_l_movestart_mouse_y( void )
	{ return this->_l_movestart_mouse_y; }

	int         get_i_mouse_middle_dragging( void )
	{ return this->_i_mouse_middle_dragging; }

	bool clicked_mouse_middle_button( void );
private:
	E_ACT	_e_act;

	int	_i_keyboard_sw;
	int	_i_keyboard;

	int	_i_mouse_motion_sw,
		_i_mouse_button_sw;

	long	_l_mouse_x,
		_l_mouse_y;

	long	_l_movestart_mouse_x,
		_l_movestart_mouse_y;

	int	_i_mouse_left_dragging,
		_i_mouse_middle_dragging;

	int	_i_mouse_which_button,
		_i_mouse_button_state;

	long	_l_scrollbar_x_val,
		_l_scrollbar_x_min,
		_l_scrollbar_x_max,
		_l_scrollbar_y_val,
		_l_scrollbar_y_min,
		_l_scrollbar_y_max;
};

#endif /* !__fltk_event_h__ */
