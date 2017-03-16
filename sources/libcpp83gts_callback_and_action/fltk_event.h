#ifndef fltk_event_h
#define fltk_event_h

#include "ptbl_returncode.h"

/* マウスの最後の状態を保持するクラス */
class mouse_state {
public:
	mouse_state()
		:x_(0)
		,y_(0)
		,move_start_x_(0)
		,move_start_y_(0)
		,which_button_(0)
		,button_click_sw_(false)
	{}

	//FL_PUSH
	void memory_push_event(
		const int button ,const long x ,const long y
	);

	//FL_RELEASE
	void memory_release_event(
		const int button ,const long x ,const long y
	);

	//FL_MOVE
	void memory_move_event( const long x ,const long y );

	//FL_DRAG
	void memory_drag_event( const long x ,const long y );

	int x(void) { return this->x_; }
	int y(void) { return this->y_; }
	int x_move(void) { return this->x_ - this->move_start_x_; }
	int y_move(void) { return this->y_ - this->move_start_y_; }
	int which_button(void) { return this->which_button_; } /* FL_LEFT_MOUSE/FL_MIDDLE_MOUSE/FL_RIGHT_MOUSE */
	bool is_clicked(void) { return this->button_click_sw_; }
	void escape_clicked(void) { this->button_click_sw_ = false; }

private:
	int	x_	/* 横位置 */
		,y_;	/* 縦位置 */
	int	move_start_x_	/* FL_PUSHの時の位置の記憶 */
		,move_start_y_;	/* FL_PUSHの時の位置の記憶 */

	int	which_button_;		/* ボタンの種類 */
	bool	button_click_sw_;	/* ボタンの状態 */
};

//---------------------------------

typedef enum {
E_ACT_NOTHING = 1,		/* 実行予約はなにもない */
E_ACT_ALL_VIEW,			/* 全体を(step倍率で)表示 */
E_ACT_ZOOM_IN_TWICE_AT_CEN,	/* Viewportの中心で2倍づつ拡大 */
E_ACT_ZOOM_OUT_HALF_AT_CEN,	/* Viewportの中心で1/2倍づつ縮小 */
E_ACT_ZOOM_IN_STEP_AT_CEN,	/* Viewportの中心で1stepづつ拡大 */
E_ACT_ZOOM_OUT_STEP_AT_CEN,	/* Viewportの中心で1stepづつ縮小 */
E_ACT_ZOOM_D16,			/* 縮小1/16倍 */
E_ACT_ZOOM_D08,			/* 縮小1/8倍 */
E_ACT_ZOOM_D04,			/* 縮小1/4倍 */
E_ACT_ZOOM_D02,			/* 縮小1/2倍 */
E_ACT_ZOOM_E01,			/* 等倍1倍 */
E_ACT_ZOOM_U02,			/* 拡大2倍 */
E_ACT_ZOOM_U04,			/* 拡大4倍 */
E_ACT_ZOOM_U08,			/* 拡大8倍 */
E_ACT_ZOOM_U16,			/* 拡大16倍 */
E_ACT_ZOOM_IN_TWICE_AT_POS,	/* 指定位置で2倍づつ拡大 */
E_ACT_ZOOM_OUT_HALF_AT_POS,	/* 指定位置で1/2倍づつ縮小 */
E_ACT_ZOOM_IN_STEP_AT_POS,	/* 指定位置で1stepづつ拡大 */
E_ACT_ZOOM_OUT_STEP_AT_POS,	/* 指定位置で1stepづつ縮小 */
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
E_ACT_MOVE_STOP,		/* 連続移動の停止(予約) */
E_ACT_MOVE_HOVER,		/* 移動 */
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

		this->_l_scrollbar_x_val = 0L;
		this->_l_scrollbar_x_min = 0L;
		this->_l_scrollbar_x_max = 0L;
		this->_l_scrollbar_y_val = 0L;
		this->_l_scrollbar_y_min = 0L;
		this->_l_scrollbar_y_max = 0L;
	}

	void  set_e_act( E_ACT e_act )   {this->_e_act = e_act;}
	E_ACT get_e_act( void )  { return this->_e_act; }

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

	/* マウスの最後の状態を保持するクラス */
	mouse_state cl_mouse_state;

private:
	E_ACT	_e_act;

	int	_i_keyboard_sw;
	int	_i_keyboard;

	long	_l_scrollbar_x_val,
		_l_scrollbar_x_min,
		_l_scrollbar_x_max,
		_l_scrollbar_y_val,
		_l_scrollbar_y_min,
		_l_scrollbar_y_max;
};

#endif /* !fltk_event_h */
