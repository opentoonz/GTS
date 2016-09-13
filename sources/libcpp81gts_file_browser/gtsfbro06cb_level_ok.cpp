#include <cstdlib>	/* atoi() */
#include <cstring>
#include <string>	// std::to_string
#include <FL/fl_ask.H>	/* fl_alert(-) */
#include "gtsfbro06cb_level.h"
#if !defined GTS_DEBUG
# include "gts_master.h"
#endif
#include "gts_gui.h"

void gtsfbro06cb_level::cb_ok( void )
{
	const char *ccp_file;
	int i_sta,i_end;

	ccp_file = cl_gts_gui.strinp_level_file->value();
	if ((NULL == ccp_file) || ('\0' == ccp_file[0])) {
		pri_funct_err_bttvr(
	  "Error : cl_gts_gui.strinp_level_file->value() is null string"
	  	);
		fl_alert("level name is not exist");
		return;
	}

	i_sta = static_cast<int>(cl_gts_gui.valinp_level_start->value());
	if ((i_sta < 1) || (9999 < i_sta)) {
		pri_funct_err_bttvr(
	    "Error : cl_gts_gui.valinp_level_start->value()<%d> is zero or minus"
			, i_sta);
		std::string str("bad level start number=");
		str += std::to_string(i_sta);
		fl_alert( str.c_str() );
		return;
	}

	i_end = static_cast<int>(cl_gts_gui.valinp_level_end->value());
	if ((i_end < 1) || (9999 < i_end)) {
		pri_funct_err_bttvr(
	    "Error : cl_gts_gui.valinp_level_end->value()<%d> is zero or minus"
			, i_end);
		std::string str("bad level end number=");
		str += std::to_string(i_end);
		fl_alert( str.c_str() );
		return;
	}

#if !defined GTS_DEBUG
	// GUI Scroll
	cl_gts_gui.selbro_fnum_list->topline(0);

	/* 以前のリストをすべて削除 */
	cl_gts_master.cl_file_number_list.remove_all();

	/* ファイルの存在をチェックしながらリストを設定 */
	if (cl_gts_gui.choice_level_continue_type->value()
	==  cl_gts_master.cl_file_number_list.get_end_type_value()) {
		// End type
	 if (i_sta <= i_end) {
	  cl_gts_master.cl_file_number_list.make_fnum_list_with_chk_mark(
		i_sta ,i_end
	  );
	 }
	 else {
	  cl_gts_master.cl_file_number_list.make_fnum_list_with_chk_mark(
		i_end ,i_sta
	  );
	 }
	}
	else { // Endless type
	 cl_gts_master.cl_file_number_list.append_fnum_list_with_chk_mark(
		static_cast<int>( cl_gts_gui.valinp_level_start->value() )
	 );
	}

	/* frame number listにlevel名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
		cl_gts_master.cl_bro_level.cp_levelname()
	);

	/* 新たに作ったリストは全て選択状態にする */
	cl_gts_master.cl_file_number_list.select_all();

	/* ファイル名表示 */
	cl_gts_master._print_window_headline();

	/* 切抜きはしないのでOFFにしておく */
	//cl_gts_master.cl_ogl_view.crop_area(OFF);
#endif

	/* GUIの状態を記憶する Cancel用のメモリ */
	this->memory_from_gui(
		cl_gts_gui.filinp_level_dir->value()
	);

	/* levelの終了に伴うx1view windowの閉じでは、
	表示スイッチをOFFにしない */
	cl_gts_gui.window_x1view->hide(); /* x1 Window閉じる */
	cl_gts_gui.menite_level->clear(); /* menuのcheckを消す */
	cl_gts_gui.window_level->hide();  /* Window閉じる */
}
