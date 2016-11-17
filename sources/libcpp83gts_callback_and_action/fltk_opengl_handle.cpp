#include <cstdlib>
#include <algorithm>	// std::sort()
#include "FL/fl_ask.H"  // fl_alert(-)
#include <sstream>
#include <filesystem>/* tr2::sys::path */
#include "fltk_opengl.h"
#include "gts_master.h"
#include "gts_gui.h"

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

		/* 画像再表示 */
		cl_gts_gui.opengl_view->redraw();

		/* 画像表示パラメータの変更に合わせてGUIの値の変更 */
		cl_gts_master.from_opengl_rect_to_area_val();

		return 1;
	}
	/* フレーム送り戻し：Cropでない、あるいは、Crop選択されてない */
	else {
		cb_file_number_list& fn = cl_gts_master.cl_file_number_list;
		switch (key) {
		case FL_Up:
			if (fn.selected_prev_frame()) {
			 cl_gts_master.cb_read_and_trace_and_preview();
			}
			break;
		case FL_Down:
			if (fn.selected_next_frame()) {
			 cl_gts_master.cb_read_and_trace_and_preview();
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
std::vector<std::string> split_(const std::string &str, char delim)
{
	std::stringstream strstr(str);
	std::string item;
	std::vector<std::string> elems;
	while (std::getline(strstr, item, delim)) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}

void separate_filehead_number_(
	const std::string& basename
	, std::string& filehead
	, std::string& number
)
{
	int ii=0;
	for (ii=basename.size()-1 ;0<=ii ;--ii) {
		if (!isdigit(basename.at( ii ))) { break; }
	}
	if (ii < 0) { /* 全体が数字になっている */
		filehead.clear();
		number = basename;
		return;
	}
	if (basename.at(ii) == '.' && 1 <= ii) {/* 区切り有り */
		filehead = basename.substr( 0 ,ii );
	} else {				/* 区切り無し */
		filehead = basename.substr( 0 ,ii+1 );
	}
	number   = basename.substr(ii+1);
}

void filepath_to_dir_head_num_ext_(
	const std::string& filepath
	, std::string& dir
	, std::string& head
	, std::string& num
	, std::string& ext
)
{
	std::tr2::sys::path path( filepath );
	dir = path.parent_path();
	separate_filehead_number_( path.basename() ,head ,num );
	ext = path.extension().substr(1);
}

bool check_(
	const std::vector<std::string>& strs
	, std::vector<int>& nums
	, int& start_num
	, int& end_num
	, std::vector<int>& diffs
	, std::string& dir_fst
	, std::string& head_fst
	, std::string& ext_fst
)
{
	bool only_first_sw = true;
	bool error_sw = false;

	for (const std::string& str : strs) {
		/* ファイルパスを部品に分割 */
		std::string dir;
		std::string head;
		std::string num;
		std::string ext;
		filepath_to_dir_head_num_ext_( str ,dir ,head ,num ,ext );
		/* ファイル番号文字を番号配列に格納 */
		if (num.empty())
		{	nums.push_back( 0 ); }
		else {	nums.push_back( std::stoi(num) ); }

		/* 始めのファイルパスでの初期セット */
		if (only_first_sw) {
			only_first_sw = false;
			/* 1個目のファイルパスが連番の基準 */
			dir_fst = dir;
			head_fst = head;
			ext_fst = ext;
			/* 1個目のファイルパスが基準なので違いスイッチOFF */
			diffs.push_back(0);
			/* 1個目以後のファイルパスでmin/maxの設定 */
			start_num = end_num = nums.back();
			continue;
		}

		/* 2個目以後のファイルパスでmin/maxの設定 */
		else {
			if (end_num < nums.back()) {
			    end_num = nums.back();
			}
			if (nums.back() < start_num) {
			    start_num = nums.back();
			}
		}
		/* 2個目以後のファイルパスと1個目との比較 */
		if (dir_fst != dir || head_fst != head || ext_fst != ext)
		{
			diffs.push_back(1);	/* 違いあり */
			error_sw = true;
		}
		else {
			diffs.push_back(0);	/* 違わない */
		}
	}

	return error_sw;
}

void message_bad_files_(
	const std::vector<std::string>& strs
	, const std::vector<int>& diffs
	, const std::vector<int>& nums
)
{
	std::string msg("Include Bad files...\n");
	for (unsigned ii=0 ;ii<strs.size() ;++ii) {
		msg += strs.at(ii);
		msg += " ";
		msg += ((diffs.at(ii)==1) ?"X" :"O");
		msg += " ";
		msg += std::to_string( nums.at(ii) );
		msg += "\n";
	}
	fl_alert( msg.c_str() ); /* !!! 多いと表示しきれない !!! */
}

void open_files_by_paste_( const std::string &dnd_str )
{
	/* DNDで取込んだ複数のファイルパスを1パスごとに格納 */
	std::vector<std::string> strs( split_( dnd_str ,'\n' ) );

	/* 必要な情報に変える */
	std::vector<int> diffs;
	std::vector<int> nums;
	int start_num=0;
	int end_num=0;
	std::string dire;
	std::string head;
	std::string exte;
	const bool error_sw = check_(
		strs ,nums ,start_num ,end_num ,diffs ,dire ,head ,exte
	);
	std::sort( nums.begin() ,nums.end() ); /* 昇順ソート */

	/* 拡張子のチェック(tga/tif/txt) */
	/* ファイルパスの種類と組み合わせがダメ */
	if ((exte != "tga"
	&&   exte != "tif"
	&&   exte != "txt"
	) 
	||  error_sw) {
		message_bad_files_( strs ,diffs ,nums );
		return;
	}

	if (exte == "txt") { /* config file */

	} else {	/* level */
		cl_gts_gui.filinp_level_save_dir_path->value( dire.c_str() );
		cl_gts_gui.strinp_level_save_file_head->value( head.c_str() );
		cl_gts_gui.valinp_level_saveopen_num_start->value( start_num );
		cl_gts_gui.valinp_level_saveopen_num_end->value( end_num );
		if ( exte == "tif" ) {
		 cl_gts_gui.choice_level_save_image_format->value(0);
		} else
		if ( exte == "tga" ) {
		 cl_gts_gui.choice_level_save_image_format->value(1);
		}
		cl_gts_master.cl_bro_level.cb_set_image_file_extension();
		cl_gts_master.cl_bro_level.level_set(
			nums ,start_num ,end_num
		);
	}
}
/*------ dnd処理ここまで ------*/

} // namespace

int fltk_opengl::handle( int event )
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

		/* ...再描画する */
		cl_gts_gui.opengl_view->flush();

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
		cl_gts_gui.opengl_view->flush();

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
		 cl_gts_master.reserve_by_menu(E_ACT_ZOOM_DOWN_HALF_AT_POS);
		}
		else {			  /* Wheeling forward */
		 cl_gts_master.reserve_by_menu(E_ACT_ZOOM_UP_TWICE_AT_POS);
		}
		return 1;

	case FL_DND_ENTER:
	case FL_DND_DRAG:
	case FL_DND_RELEASE:
		return 1;
	case FL_PASTE:
		open_files_by_paste_( Fl::event_text() );
		return 1;

	default:
		/* pass other events to the base class */
		return Fl_Gl_Window::handle(event);
	}
	return 0;
}
