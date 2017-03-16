#include <iostream>
#include "FL/fl_ask.H"  // fl_alert(-)
#include "ids_path_level_from_files.h"
#include "cb_pixel_type_and_bright.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_choice_pixel_type( void )
{
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:
		cl_gts_gui.group_bw->show();
		cl_gts_gui.group_grays->hide();
		cl_gts_gui.group_rgb->hide();
		break;
	case 1:
		cl_gts_gui.group_bw->hide();
		cl_gts_gui.group_grays->show();
		cl_gts_gui.group_rgb->hide();
		break;
	case 2:
		cl_gts_gui.group_bw->hide();
		cl_gts_gui.group_grays->hide();
		cl_gts_gui.group_rgb->show();
		break;
	}
}

//--------------------

void fltk_button_pixel_type_and_bright::draw()
{
	Fl_Button::draw();
}

namespace {

/* エラーがあればその情報を文字で返す、成功ならempty文字列を返す */
const std::string dnd_paste_( const std::string &dnd_str )
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

	/* Config file */
	if (ext == ".txt") {
		if (cl_gts_master.cl_memo_config.load_only_pixel_type_and_bright(
		dnd_str ) == NG) {
		 return "Error : at loading pixel_type_and_bright in config";
		}
	}
	/* 拡張子が対応外エラー */
	else {
		return "Error : Need Extension .txt";
	}
	return std::string();
}

} // namespace

int fltk_button_pixel_type_and_bright::handle( int event )
{
	switch (event) {
	case FL_DND_ENTER:
	case FL_DND_DRAG:
	case FL_DND_RELEASE:
		return 1;

	case FL_PASTE: // DND Paste
	{
		std::string err(dnd_paste_( Fl::event_text() ));
		if (!err.empty()) {
			fl_alert( err.c_str() );
		}
	}
		return 1;

	default:
		/* pass other events to the base class */
		return Fl_Button::handle(event);
	}
	return 0;
}
