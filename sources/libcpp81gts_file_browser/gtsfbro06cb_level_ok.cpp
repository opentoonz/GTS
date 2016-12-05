#include <cstdlib>	/* atoi() */
#include <cstring>
#include <string>	// std::to_string
#include <FL/fl_ask.H>	/* fl_alert(-) */
#include "gtsfbro06cb_level.h"
#if !defined GTS_DEBUG
# include "gts_master.h"
#endif
#include "gts_gui.h"

#if 0
namespace {

/* ファイルの存在をチェックしながらリストを設定 */
void make_fnum_list_with_chk_mark_same_way_(
	const std::vector<int>& num_list /* こちら優先して使い設定 */
	, const int start_num	/* num_listが空ならこちらで設定 */
	, const int end_num
)
{
	/* num_listにセットしてあるならそれをGUIリストに設定する */
	if (!num_list.empty()) {
		for (int num : num_list) {
	 cl_gts_master.cl_file_number_list.append_fnum_list_with_chk_mark(
		num
	 );
		}
		return;
	}

	/* startからendまでをGUIリストに設定する */
	if (cl_gts_gui.choice_level_num_continue_type->value()
	==  cl_gts_master.cl_file_number_list.get_end_type_value()) {
		// End type
	 if (start_num <= end_num) {
	  cl_gts_master.cl_file_number_list.make_fnum_list_with_chk_mark(
		start_num ,end_num
	  );
	 }
	 else {
	  cl_gts_master.cl_file_number_list.make_fnum_list_with_chk_mark(
		end_num ,start_num
	  );
	 }
	}
	else { // Endless type
	 cl_gts_master.cl_file_number_list.append_fnum_list_with_chk_mark(
		static_cast<int>( cl_gts_gui.valinp_level_num_start->value() )
	 );
	}
}

} // namespace
#endif

void gtsfbro06cb_level::cb_ok( void )
{
	const char *ccp_file;
	int i_sta,i_end;

	ccp_file = cl_gts_gui.strinp_level_save_file_head->value();
	if ((NULL == ccp_file) || ('\0' == ccp_file[0])) {
		pri_funct_err_bttvr(
	  "Error : cl_gts_gui.strinp_level_save_file_head->value() is null string"
		);
		fl_alert("level name is not exist");
		return;
	}

	i_sta = static_cast<int>(cl_gts_gui.valinp_level_num_start->value());
	if ((i_sta < 1) || (9999 < i_sta)) {
		pri_funct_err_bttvr(
	    "Error : cl_gts_gui.valinp_level_num_start->value()<%d> is zero or minus"
			, i_sta);
		std::string str("bad level start number=");
		str += std::to_string(i_sta);
		fl_alert( str.c_str() );
		return;
	}

	i_end = static_cast<int>(cl_gts_gui.valinp_level_num_end->value());
	if ((i_end < 1) || (9999 < i_end)) {
		pri_funct_err_bttvr(
	    "Error : cl_gts_gui.valinp_level_num_end->value()<%d> is zero or minus"
			, i_end);
		std::string str("bad level end number=");
		str += std::to_string(i_end);
		fl_alert( str.c_str() );
		return;
	}

	std::vector<int> num_list;
	this->level_set( num_list ,i_sta ,i_end );
}

void gtsfbro06cb_level::level_set(
	const std::vector<int>& num_list
	, const int start_num
	, const int end_num
)
{
#if !defined GTS_DEBUG
#if 0
	/* 以前のリストをすべて削除 */
	cl_gts_master.cl_file_number_list.remove_all();

	/* ファイルの存在をチェックしながらリストを設定 */
//make_fnum_list_with_chk_mark_same_way_(num_list,start_num,end_num);
	cl_gts_master.cl_file_number_list.append_numbers_with_exist_mark(
		num_list ,start_num ,end_num
	);

	/* 新たに作ったリストは全て選択状態にする */
	cl_gts_master.cl_file_number_list.select_all();
#endif
	/* numberリストをファイル存在マーク付で再構築し選択状態にする */
	cl_gts_master.cl_file_number_list.remake_with_exist_mark_and_select(
		num_list ,start_num ,end_num
	);

	/* frame number listにlevel名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
		cl_gts_master.cl_bro_level.cp_levelname()
	);

	/* ファイル名表示 */
	cl_gts_master.print_window_headline();

	/* 切抜きはしないのでOFFにしておく */
	//cl_gts_master.cl_ogl_view.set_crop_disp_sw(OFF);
#endif

	/* GUIの状態を記憶する Cancel用のメモリ */
	this->memory_from_gui(
		cl_gts_gui.filinp_level_save_dir_path->value()
	);

	/* 画像表示 */
	cl_gts_master.cb_read_and_trace_and_preview();

	/* levelの終了に伴うx1view windowの閉じでは、
	表示スイッチをOFFにしない */
	cl_gts_gui.window_x1view->hide(); /* x1 Window閉じる */
	cl_gts_gui.window_level_browse->hide();  /* Window閉じる */

	/* RGB Scan Image _full画像の保存場所指定の時の状態復元 */
	if (cl_gts_gui.togbut_level_open_browse->value()) {
		cl_gts_gui.togbut_level_open_browse->clear();
		cl_gts_gui.filinp_level_save_dir_path->activate();
		cl_gts_gui.filinp_level_open_dir_path->deactivate();
	}
}
