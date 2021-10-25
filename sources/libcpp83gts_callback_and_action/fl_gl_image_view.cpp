#include <iostream>	//std::cout
#include <cstdlib>
#include <algorithm>	// std::sort()
#include <limits>       // std::numerical_limits
#include <sstream>
#include "FL/fl_ask.H"  // fl_alert(-)
#include "pri.h"
#include "fl_gl_image_view.h"
#include "ids_path_level_from_files.h"
#include "cb_scan_and_save.h"
#include "cb_trace_files.h"
#include "gts_master.h"
#include "gts_gui.h"

void fl_gl_image_view::draw()
{
	/* char Fl_Gl_Window::valid() const;
	FLTKがこのウィンドウの新しいコンテキストを作成するとき、
	またはウィンドウのサイズが変更されたときにoffになり、
	draw()が呼び出された後にonになります
	*/
	/* reshape(windowサイズの変更か再表示の場合) */
	if (!(this->valid())) {
		/* Fl_Gl_Window widget,
		The default mode is FL_RGB|FL_DOUBLE|FL_DEPTH. */

		/* OpenGL初期化(アプリの生成後一回のみ実行) */
		static bool only_one_time_sw = true;
		if (only_one_time_sw) {
			cl_gts_master.cl_ogl_view.init_opengl();
			only_one_time_sw = false;
		}
	}

		/* viewport()とortho()を平行投影に設定する */
		//this->ortho();

		/* 画像データがあるとき */
		if (cl_gts_master.cl_ogl_view.is_main_canvas()) {
			cl_gts_master.cl_ogl_view.reshape_opengl(
				(long)(this->w()) , (long)(this->h())
			);
			cl_gts_master.set_scrollbar();
		}
		/* 画像データがないとき */
		else {
			cl_gts_master.cl_ogl_view.clear_opengl(
				(long)(this->w()) , (long)(this->h())
			);
		}

	if (cl_gts_master.cl_ogl_view.is_main_canvas()) {

		/* subエリアのカラートレス処理
		と(指定にあれば)ドットノイズ除去 */
		cl_gts_master.color_trace_in_view_area();

		/* image view表示 */
		cl_gts_master.cl_ogl_view.draw_opengl();

		/* スポイト位置表示 */
		if (0 <= this->pixel_r_) {
			cl_gts_master.cl_ogl_view.draw_image_pixel_pos(
				this->pixel_x_ ,this->pixel_y_
			);
		}

		/* hsv view再表示 */
		cl_gts_gui.hsv_view->redraw();
	}
}

namespace {

int fl_shortcut_up_down_left_right_( int key )
{
	iip_opengl_l3event& og = cl_gts_master.cl_ogl_view;

	/* Cropハンドル移動：Cropモードで、選択あり、選択Actionでない */
	if(og.get_e_select_part() != E_SELECT_NOTHING
	&& og.get_e_select_part() != E_SELECT_IMAGE
	&& og.get_crop_disp_sw()
	) {
		/* マウスポインター移動に合わせて画像表示パラメータを設定 */
		int xd = 0;
		int yd = 0;
		long zm = og.get_l_zoom();

		if (zm < 1L) { zm = 1L; }
		switch (key) {
		case FL_Up:	xd = 0; yd =-1 * zm; break;
		case FL_Down:	xd = 0; yd = 1 * zm; break;
		case FL_Left:	xd =-1 * zm; yd = 0; break;
		case FL_Right:	xd = 1 * zm; yd = 0; break;
		}
		og.drag_move_start();
		og.drag_moving( xd , yd , 0.0 , 0.0 );

		/* 画像表示パラメータの変更に合わせてGUIの値の変更 */
		cl_gts_master.cl_area_and_rot90.copy_opengl_to_value(
			og.get_e_select_part()
		);

		/* 画像再表示 */
		cl_gts_gui.image_view->redraw();

		return 1;
	}
	/* フレーム送り戻し：Cropでない、あるいは、Crop選択されてない */
	else {
		cb_number& fn = cl_gts_master.cl_number;
		switch (key) {
		case FL_Up:
			if (fn.selected_prev_frame()) {
			 cl_gts_master.cb_number_read_and_trace_and_preview();
			}
			break;
		case FL_Down:
			if (fn.selected_next_frame()) {
			 cl_gts_master.cb_number_read_and_trace_and_preview();
			}
			break;
		case FL_Left: /* Fl_ScrollBarのFL_Left イベントをCancel */
		case FL_Right:/* Fl_ScrollBarのFL_RightイベントをCancel */
			break;
		}
		return 1;
	}
	return 0;
}

/*------ dnd処理ここから ------*/
const std::string open_files_by_paste_( const std::string &dnd_str )
{
	/* 複数のファイルパスはエラー */
	if (std::string::npos != dnd_str.find("\n")) {
		return "Error : Need Only 1 Filepath";
	}

	/* 必要な情報に変える */
	std::string dpath , head , num_form , ext;
	int number=-1;
	std::vector<int> nums;
	ids::path::level_from_files(
		dnd_str ,dpath ,head ,num_form ,number ,ext ,nums
	);

	/* ファイルヘッド名がない */
	if ( head.empty() ) {
		return "Error : Need Head name";
	}

	/* Configファイル */
	if (ext == ".txt") {
		cl_gts_master.cl_config.loading_and_set_dpath_fname(
			dnd_str );
		return std::string();
	}

	/* 以下画像について... */

	/* 画像の拡張子(.tga/.tif)ではない */
	if ( cl_gts_master.cl_trace_files.ext_open.num_from_str(ext) < 0 ) {
		/* 拡張子が対応外 */
		return "Error : Need Extension .tga/.tif/.txt";
	}

	/* 単体画像ファイル開き表示 */
	if (nums.empty() || number == -1) {
		/* 画像読込表示 */
		cl_gts_master.cb_read_and_trace_and_preview( dnd_str );
		/* 場所は記憶しない */
	}
	/* 連番画像ファイル開き表示 */
	else {
		/* Traceの番号であることを表示して示す */
		cl_gts_master.cl_number.set_type_to_trace();

		/* ファイルパスから生成した部品を、GUI、その他セット */
		cl_gts_master.cl_trace_files.set_gui_for_open(
			dpath ,head ,num_form ,ext ,nums
		);

		/* 画像読込表示 */
		cl_gts_master.cb_number_read_and_trace_and_preview();
	}

	/* 画像を開いたときの初期表示を元画像の表示にする */
	cl_gts_master.cb_change_wview_main();
	cl_gts_gui.menite_wview_main->setonly();

	return std::string(); /* 正常終了 */
}
/*------ dnd処理ここまで ------*/

} // namespace

int fl_gl_image_view::handle( int event )
{
	mouse_state& ms = cl_gts_master.cl_fltk_event.cl_mouse_state;

	switch (event) {

	/*
	 * Keyboard Events
	 */
	//case FL_KEYDOWN:
	//case FL_KEYUP:
	//case FL_KEYBOARD:
	case FL_SHORTCUT:
		switch (Fl::event_key()) {
		case FL_Up: case FL_Down: case FL_Left: case FL_Right:
		 return fl_shortcut_up_down_left_right_(Fl::event_key());
		}
		return 0;

	/*
	 * Mouse Events
	 */
	case FL_DRAG: /* The mouse has moved with a button held down. */
		/* 扱う対象がないなら、何もしない */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;
		}

		/* マウスドラッグ位置を記憶 */
		ms.memory_drag_event( Fl::event_x() ,Fl::event_y() );

		/* 左ボタンによる実行を設定 */
		if (ms.which_button() == FL_LEFT_MOUSE
		) {
			/* reserveがなければ予約入れる
			既にreserveあれば予約せず何もしない */
			cl_gts_master.reserve( E_ACT_MOVE_DRAG );
		}

		return 1;

	case FL_MOVE: /* The mouse has moved without mouse drag. */
		/* 扱う対象がないなら、何もしない */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;
		}

		/* マウス移動位置を記憶 */
		ms.memory_move_event( Fl::event_x() ,Fl::event_y() );

		/* reserveがなければ予約入れる
			既にreserveあれば予約せず何もしない */
		cl_gts_master.reserve( E_ACT_MOVE_HOVER );

		return 1;

	case FL_PUSH: /* マウスボタンをクリックした瞬間 */
		/* 扱う対象がないなら、何もしない */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;
		}

		/* マウスボタンの状態と位置を記憶 */
		ms.memory_push_event(
			Fl::event_button() ,Fl::event_x() ,Fl::event_y()
		);

		/* 動作初期設定 */
		cl_gts_master.action( E_ACT_MOVE_START );

		/* 画像移動時、2値化画像からscan画像表示設定に... */
		cl_gts_master.cl_ogl_view.set_temporary_display_main_sw(
			ms.which_button() == FL_LEFT_MOUSE
		);

	if (Fl::event_state() & FL_CTRL) {
		/* カーソル位置から画像上の位置を得てセットする */
		cl_gts_master.cl_ogl_view.from_cursor_pos_to_image_pos(
			Fl::event_x() ,Fl::event_y()
			,this->w() ,this->h()
			,this->pixel_x_
			,this->pixel_y_
		);
/*std::cout
<< __FILE__ << " " << __LINE__
<< " mx=" << Fl::event_x()
<< " my=" << Fl::event_y()
<< " w=" << this->w()
<< " h=" << this->h()
<< std::endl;*/
		/* 画像上の位置から、画像のPixel情報を得る */
		cl_gts_master.cl_ogl_view.get_image_pixel(
			this->pixel_x_
			,this->pixel_y_

			,this->pixel_r_
			,this->pixel_g_
			,this->pixel_b_
			,this->pixel_channel_
			,this->pixel_byte_
			,this->pixel_bit_
		);

		/* 画像のPixel情報からxyz位置をセット(表示設定)する */
		{
		double ma = 255.;
		switch (this->pixel_byte_) {
		case 1: ma = (std::numeric_limits<unsigned char>::max)();
			break;
		case 2: ma = (std::numeric_limits<unsigned short>::max)();
			break;
		}
		cl_gts_gui.hsv_view->rgb_to_xyz(
			this->pixel_r_ / ma
			,this->pixel_g_ / ma
			,this->pixel_b_ / ma
		);
		}
/*std::cout
<< __FILE__ << " " << __LINE__
<< " x=" << this->pixel_x_
<< " y=" << this->pixel_y_
<< " r=" << this->pixel_r_
<< " g=" << this->pixel_g_
<< " b=" << this->pixel_b_
<< " ch=" << this->pixel_channel_
<< " by=" << this->pixel_byte_
<< " bi=" << this->pixel_bit_
<< std::endl;*/
	}

		/* ...再描画する */
		cl_gts_gui.image_view->flush();

		return 1;

	case FL_RELEASE: /* マウスボタンをリリースした瞬間 */
		/* 扱う対象がないなら、何もしない */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;
		}

		/* scan画像から2値化画像表示設定に... */
		cl_gts_master.cl_ogl_view.set_temporary_display_main_sw(
			false
		);

		/* 動作初期設定 */
		cl_gts_master.action( E_ACT_MOVE_STOP );

		/* ...再描画する */
		cl_gts_gui.image_view->flush();

		/* マウスボタンの状態と位置を記憶 */
		ms.memory_release_event(
			Fl::event_button() ,Fl::event_x() ,Fl::event_y()
		);

		return 1;

	case FL_MOUSEWHEEL:
		/* 扱う対象がないなら、何もしない */
		if (0 == cl_gts_master.cl_ogl_view.is_main_canvas()) {
			return 0;
		}
		/*
			Wheeling in the rear zoom down
			or
			Wheeling forward zoom up.
		*/
		if (0 < Fl::event_dy()) { /* Wheeling int the rear */
		 cl_gts_master.reserve_by_menu(E_ACT_ZOOM_OUT_HALF_AT_POS);
		}
		else {			  /* Wheeling forward */
		 cl_gts_master.reserve_by_menu(E_ACT_ZOOM_IN_TWICE_AT_POS);
		}
		return 1;

	case FL_DND_ENTER:
	case FL_DND_DRAG:
	case FL_DND_RELEASE:
		return 1;
	case FL_PASTE:
	{
		std::string err(open_files_by_paste_( Fl::event_text() ));
		if (!err.empty()) {
			fl_alert( err.c_str() );
		}
	}
		return 1;

	default:
		/* pass other events to the base class */
		return Fl_Gl_Window::handle(event);
	}
	return 0;
}
