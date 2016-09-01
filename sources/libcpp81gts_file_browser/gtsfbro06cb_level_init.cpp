#include <string.h>
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::set_level_filename_memory_( const char *ccp_fname )
{
	/* strncpy()は、
	最初のnバイトの中にNULL文字が無ければ、
	コピーの結果としてできる文字列は
	NULLで終端していないものになる。
	*/
	strncpy(
	this->level_filename_memory_ ,ccp_fname ,PTBL_PATH_MAX
	);
	this->level_filename_memory_[PTBL_PATH_MAX-1] = '\0';
}
void gtsfbro06cb_level::set_rgb_scan_dir_memory_( const char *ccp_fname )
{
	strncpy(
	this->_ca_rgb_scan_dir_memory,ccp_fname,PTBL_PATH_MAX
	);
	this->_ca_rgb_scan_dir_memory[PTBL_PATH_MAX-1] = '\0';
}

/* GUIの状態を記憶する */
void gtsfbro06cb_level::memory_from_gui( const char* level_dir_path )
{
	/* 01. Dirパス */
	if (level_dir_path != nullptr) {
		if ( OK != this->i_path_cpy_dir( level_dir_path ) ) {
			pri_funct_err_bttvr(
		"Error : this->i_path_cpy_dir(%s) returns NG"
						,level_dir_path
			);
			return;
		}
		this->v_path_memory();
	}

	/* 02 file/levelのlist表示切替(Renumberボタンの表示OFF/ONも) */
	this->_i_list_form_memory =
		cl_gts_gui.choice_level_list_form->value();

	/* 03 Level名 */
	this->set_level_filename_memory_(
		cl_gts_gui.strinp_level_file->value()
	);

	/* 04 Level開始番号 */
	this->_i_start_memory =
		(int)cl_gts_gui.valinp_level_start->value();

	/* 05 Level終端番号 */
	this->_i_end_memory   =
		(int)cl_gts_gui.valinp_level_end->value();

	/* 06 Level終端タイプ */
	this->continue_type_memory_ =
		cl_gts_gui.choice_level_continue_type->value();

	/* 07 Level Endless時増減方向 */
	this->endless_direction_memory_ =
		cl_gts_gui.choice_level_endless_direction->value();

	/* 08 保存(開くときも)画像ファイル書式 */
	this->image_file_format_ =
		cl_gts_gui.choice_level_image_file_format->value();

	/* 09 等倍画像表示スイッチ */
	/*this->_i_x1view_sw_memory =
		cl_gts_gui.ligbut_level_image_x1_sw->value();*/

	/* 10 画像全体表示スイッチ */
	/*this->_i_view_sw_memory =
		cl_gts_gui.ligbut_level_view_sw->value();*/

	/* 11 _full dirパス */
	this->set_rgb_scan_dir_memory_(
		cl_gts_gui.filinp_level_rgb_scan_dir->value()
	);

	/* 12 RGBスキャン時、トレスを実行し保存するスイッチ */
	this->_i_save_color_trace_level_sw_memory =
		cl_gts_gui.chkbtn_level_rgb_trace_save_sw->value();

	/* 13 RGBスキャン画像保存sw */
	this->save_rgb_scanimage_sw_memory_ =
		cl_gts_gui.chkbtn_level_rgb_full_save_sw->value();

	/* 14 RGBスキャン画像ファイル名に_full付けるsw */
	this->rgb_with_full_sw_ =
		cl_gts_gui.chkbtn_level_rgb_with_full_sw->value();

	/* 15 dirパス/_full dirパスのブラウジング切替えスイッチ */
	/*this->_i_rgb_scan_browse_sw_memory =
		cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value();*/

	/* 16 _full等倍画像表示スイッチ */
	/*this->_i_info_rgb_sub_sw_memory =
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->value();*/
}

/* 記憶からGUI復元 */
void gtsfbro06cb_level::memory_to_gui( void )
{
	/* 01 Dirパス */
	cl_gts_gui.filinp_level_dir->value(
		this->cp_memory()
	);
	cl_gts_gui.filinp_level_dir->position(
		strlen(this->cp_memory())
	);

	/* 02 file/levelのlist表示切替(Renumberボタンの表示OFF/ONも) */
	cl_gts_gui.choice_level_list_form->value(
		this->_i_list_form_memory
	);
	if (0 == cl_gts_gui.choice_level_list_form->value()) {
		cl_gts_gui.button_level_shift_number->hide();
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->hide();
	} else {
		cl_gts_gui.button_level_shift_number->show();
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->show();
	}

	/* 03 Level名 */
	cl_gts_gui.strinp_level_file->value(
		this->level_filename_memory_
	);

	/* 04 Level開始番号 */
	cl_gts_gui.valinp_level_start->value(
		(double)this->_i_start_memory );

	/* 05 Level終端番号 */
	cl_gts_gui.valinp_level_end->value(
		(double)this->_i_end_memory );

	/* 06 Level終端タイプ */
	cl_gts_gui.choice_level_continue_type->value(
		this->continue_type_memory_ );

	/* 07 Level Endless時増減方向 */
	cl_gts_gui.choice_level_endless_direction->value(
		this->endless_direction_memory_ );

	/* End/Endlessによる表示設定  */
	if (cl_gts_gui.choice_level_continue_type->value() == 0) {
		cl_gts_gui.valinp_level_end->show();
		cl_gts_gui.choice_level_endless_direction->hide();
	}
	else {
		cl_gts_gui.valinp_level_end->hide();
		cl_gts_gui.choice_level_endless_direction->show();
	}

	/* 08 保存(開くときも)画像ファイル書式 */
	cl_gts_gui.choice_level_image_file_format->value(
		this->image_file_format_
	);

	/* 09 等倍画像表示スイッチ */
	/*cl_gts_gui.ligbut_level_image_x1_sw->value(
		this->_i_x1view_sw_memory
	);*/

	/* 10 画像全体表示スイッチ */
	/*cl_gts_gui.ligbut_level_view_sw->value(
		this->_i_view_sw_memory
	);*/

	/* 11 _full dirパス */
	cl_gts_gui.filinp_level_rgb_scan_dir->value(
		this->_ca_rgb_scan_dir_memory
	);
	cl_gts_gui.filinp_level_rgb_scan_dir->position(
		strlen(this->_ca_rgb_scan_dir_memory)
	);

	/* 12 RGBスキャン時、トレスを実行し保存するスイッチ */
	cl_gts_gui.chkbtn_level_rgb_trace_save_sw->value(
		this->_i_save_color_trace_level_sw_memory
	);

	/* 13 RGBスキャン画像保存sw */
	cl_gts_gui.chkbtn_level_rgb_full_save_sw->value(
		this->save_rgb_scanimage_sw_memory_
	);

	/* 14 RGBスキャン画像ファイル名に_full付けるsw */
	cl_gts_gui.chkbtn_level_rgb_with_full_sw->value(
		this->rgb_with_full_sw_
	);

	/* 15 dirパス/_full dirパスのブラウジング切替えスイッチ */
	/*cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value(
		this->_i_rgb_scan_browse_sw_memory
	);
	if (cl_gts_gui.ligbut_level_rgb_scan_browse_sw->value()) {
		cl_gts_gui.filinp_level_dir->deactivate();
		cl_gts_gui.filinp_level_rgb_scan_dir->activate();
	} else {
		cl_gts_gui.filinp_level_dir->activate();
		cl_gts_gui.filinp_level_rgb_scan_dir->deactivate();
	}*/

	/* 16 _full等倍画像表示スイッチ */
	/*cl_gts_gui.ligbut_level_info_rgb_sub_sw->value(
		this->_i_info_rgb_sub_sw_memory
	);*/
}

int gtsfbro06cb_level::i_init( void )
{
	/* 画像情報表示用テキスト */
	this->init_text_buffer();

	/* GUIの状態を記憶する */
	/* Dirパス --> ここではデフォルト設定を使う gtsfbro01path_base.h */
	this->memory_from_gui( nullptr/* Dirパスはメモリしない */ );

	/* GUIにpath設定 */
	this->change_level_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return NG;
	}

	return OK;
}
