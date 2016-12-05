#include <FL/fl_ask.H> // fl_alert()
#include <ctype.h> // isdigit()
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "pri.h"
#include "igs_lex_white_space_and_double_quote.h"
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {

/* この関数(set_level_num_continue_type_())はgts_masterへ移設すべき */
void set_level_num_continue_type_( const std::string& str1 )
{
	const Fl_Menu_Item* crnt =
		cl_gts_gui.choice_level_num_continue_type->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }

	    cl_gts_gui.choice_level_num_continue_type->value(crnt);
	//if (cl_gts_gui.choice_level_num_continue_type->value() == 0) {
	if (cl_gts_gui.choice_level_num_continue_type->text()
	== std::string("End")) {
		cl_gts_gui.valinp_level_num_end->show();
		cl_gts_gui.choice_level_num_endless_direction->hide();
		cl_gts_gui.selbro_fnum_list->activate();
	}
	else {
		cl_gts_gui.valinp_level_num_end->hide();
		cl_gts_gui.choice_level_num_endless_direction->show();
		cl_gts_gui.selbro_fnum_list->deactivate();
	}
}
void set_level_num_endless_direction_( const std::string& str1 )
{
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_level_num_endless_direction->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }

	cl_gts_gui.choice_level_num_endless_direction->value(crnt);
}
void set_level_save_image_format_( const std::string& str1 )
{
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_level_save_image_format->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }

	cl_gts_gui.choice_level_save_image_format->value(crnt);
	cl_gts_master.cl_bro_level.cb_set_save_image_file_extension();
}
void set_level_open_image_format_( const std::string& str1 )
{
	const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_level_open_image_format->find_item(
			str1.c_str() );
	if (crnt == nullptr) { return; }
	cl_gts_gui.choice_level_open_image_format->value(crnt);
	cl_gts_master.cl_bro_level.cb_set_open_image_file_extension();
}
void set_level_list_form_( const std::string& str1 )
{
#if 0
	if (isdigit(str1.c_str()[0])) {/* For Legacy Format...Delete sameday */
		cl_gts_gui.choice_level_list_form->value(
		 std::stoi(str1) // use C++11,throw exception then error
		);
	}
	else {
#endif
		const Fl_Menu_Item *crnt =
		 cl_gts_gui.choice_level_list_form->find_item(
			str1.c_str() );
		if (crnt == nullptr) { return; }
		cl_gts_gui.choice_level_list_form->value( crnt );
//	}

	/* File/Level表示によってボタンを表示/非表示する */
	if (cl_gts_gui.choice_level_list_form->text()
	== std::string("File")) {
		cl_gts_gui.menite_level_shift_number->deactivate();
		cl_gts_gui.menite_level_view_rgb_full_sw->deactivate();
	} else {
		cl_gts_gui.menite_level_shift_number->activate();
		cl_gts_gui.menite_level_view_rgb_full_sw->activate();
	}
}
void set_rotate_per_90_( const std::string& str1 )
{
	if (isdigit(str1.c_str()[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_rot90->value(
		  std::stoi(str1) // use C++11,throw exception then error
		 );
	}
	else {
	/*
		0=CW_-90 , 1=CW_0 , 2=CW_90 , 3=CW_180
		0=CW_-90はScannerにとっての正対なのでこれ以外は回転処理必要
		1=CW_0は作業者にとっての正対
	*/
		const Fl_Menu_Item *crnt =
			cl_gts_gui.choice_rot90->find_item( str1.c_str() );
		if (crnt == nullptr) { return; }

		cl_gts_gui.choice_rot90->value( crnt );
	}
	/* 回転値(システム設定値)をメモリする */
	cl_gts_master.set_i_rotate_per_90(
	 cl_gts_gui.choice_rot90->value() );
}
void set_pixel_type_( const std::string& str1 )
{
	if (isdigit(str1.c_str()[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_pixel_type->value(
		  std::stoi(str1) // use C++11,throw exception then error
		 );
	}
	else {
		const Fl_Menu_Item *crnt =
			cl_gts_gui.choice_pixel_type->find_item(
				str1.c_str() );
		if (crnt == nullptr) { return; }

		cl_gts_gui.choice_pixel_type->value( crnt );
	}
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
	};
}

} // namespace

void memory_config::load_ifs_(
	std::ifstream& ifs
	,const int load_trace_batch_sw
	,bool& fnum_list_sw
	,bool& trace_batch_list_sw
	,bool& level_list_redisplay_sw
	,bool& level_num_continue_type_sw
)
{
	std::string str;
	for (int ii = 1 ;std::getline(ifs,str) ;++ii) {/* 一行読む */
		if (str.empty()) { continue; }/* 空行は無視 */
		if ('#' == str.at(0)) { continue; }/* コメント行は無視 */
		std::vector< std::string > words; /* 単語に分割 */
		igs::lex::white_space_and_double_quote(str,words);
		if (words.size() < 2) { continue; }/* キーワードしかない */

		/* キーワードと、数値が1語以上(2<=words.size())ある */

		//---------- config ----------

		if ((2 == words.size()) &&
		(words.at(0) == this->str_config_dir_)) {
			cl_gts_master.cl_bro_config.init_config_dir(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_config_load_file_ )) {
			cl_gts_gui.strinp_config_load_file->value(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_config_save_as_file_)) {
			cl_gts_gui.strinp_config_save_as_file->value(
				words.at(1).c_str() );
		}

		//---------- level ----------

		else if ((2 == words.size()) &&
		((words.at(0)==this->str_level_save_dir_path_) ||
		 (words.at(0)==this->str_level_save_dir_path_legacy2016_))
		) {
			cl_gts_master.cl_bro_level.init_level_dir(
				words.at(1).c_str() );
			level_list_redisplay_sw = true;
		}
		else if ((2 == words.size()) &&
		((words.at(0)==this->str_level_save_file_head_) ||
		 (words.at(0)==this->str_level_save_file_head_legacy2016_))
		) {
			cl_gts_gui.strinp_level_save_file_head->value(
				words.at(1).c_str() );
			/* openも同時に設定、ファイル後述で別設定可能 */
			cl_gts_gui.strinp_level_open_file_head->value(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_num_start_)) {
			cl_gts_gui.valinp_level_num_start->value(
			//atof(words.at(1).c_str()) // not return error
			//strtod(words.at(1).c_str()) // return error
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_num_end_ )) {
			cl_gts_gui.valinp_level_num_end->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) && (words.at(0)
		==this->str_level_num_continue_type_)) {
			set_level_num_continue_type_( words.at(1) );
			level_num_continue_type_sw = true;
		}
		else if ((2 == words.size()) && (words.at(0)
		==this->str_level_num_endless_direction_)) {
			set_level_num_endless_direction_( words.at(1) );
		}
		else if ((2 == words.size()) &&
		((words.at(0) ==this->str_level_save_image_format_) ||
		 (words.at(0) ==this->str_level_save_image_format_legacy2016_))
		) {
			set_level_save_image_format_( words.at(1) );
			/* openも同時に設定、ファイル後述で別設定可能 */
			set_level_open_image_format_( words.at(1) );
		}

		else if ((2 == words.size()) &&
		((words.at(0) == this->str_filter_rgb_erase_dot_noise_sw_) ||
		 (words.at(0) == this->str_filter_rgb_erase_dot_noise_sw_legacy2016_))
		) {
			cl_gts_gui.chkbtn_filter_rgb_erase_dot_noise_sw->value(
				(words.at(1) == this->str_on_) ?1 :0
			);
		}
		else if ((2 == words.size()) &&
		((words.at(0) == this->str_filter_rgb_color_trace_sw_) ||
		 (words.at(0) == this->str_filter_rgb_color_trace_sw_legacy2016_))
		) {
			cl_gts_gui.chkbtn_filter_rgb_color_trace_sw->value(
				(words.at(1) == this->str_on_) ?1 :0
			);
		}

		else if ((2 == words.size()) &&
		((words.at(0) == this->str_level_open_dir_path_ ) ||
		 (words.at(0) == this->str_level_open_dir_path_legacy2016_))
		) {
			cl_gts_gui.filinp_level_open_dir_path->value(
				words.at(1).c_str() );
			cl_gts_gui.filinp_level_open_dir_path->position(
				words.at(1).size() );
			level_list_redisplay_sw = true;
		}

		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_open_file_head_)) {
			cl_gts_gui.strinp_level_open_file_head->value(
				words.at(1).c_str() );
		}
		else if ((2 == words.size()) && (words.at(0)
		==this->str_level_open_image_format_)) {
			set_level_open_image_format_( words.at(1) );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_level_list_form_)) {
			set_level_list_form_( words.at(1) );
			level_list_redisplay_sw = true;
		}

		//---------- area ----------

		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_select_ )) {
			const Fl_Menu_Item *crnt =
				cl_gts_gui.choice_area_selecter->find_item(
					words.at(1).c_str() );
			if (crnt != nullptr) {
			 cl_gts_gui.choice_area_selecter->value(crnt);
			 cl_gts_master.cb_area_selecter();
			}
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_x_pos_ )) {
			cl_gts_gui.valinp_area_x_pos->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_y_pos_ )) {
			cl_gts_gui.valinp_area_y_pos->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_aspect_ratio_select_)) {
			const Fl_Menu_Item *crnt =
		cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(
				words.at(1).c_str() );
			if (crnt != 0) {
		cl_gts_gui.choice_area_aspect_ratio_selecter->value(crnt);
		cl_gts_master.cb_area_aspect_ratio_selecter();
			}
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_x_size_)) {
			cl_gts_gui.valinp_area_x_size->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_y_size_)) {
			cl_gts_gui.valinp_area_y_size->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_x_pixel_ )) {
			cl_gts_gui.valinp_area_x_pixel->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_y_pixel_ )) {
			cl_gts_gui.valinp_area_y_pixel->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_area_resolution_dpi_ )) {
			cl_gts_gui.valinp_area_reso->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rotate_per_90_ )) {
			set_rotate_per_90_( words.at(1) );
		}

		//---------- scanner info. ----------

		/* スキャナー情報
			this->str_scanner_type_
			cl_gts_gui.txtout_scanner_type
			this->str_scanner_x_max_
			cl_gts_gui.valout_scanner_width_max
			this->str_scanner_y_max_
			cl_gts_gui.valout_scanner_height_max
		はTWAINドライバーから取るべきなので、
		ファイルからは設定しない
		*/

		//---------- pixel type ----------

		else if ((2 == words.size()) &&
		(words.at(0) == this->str_pixel_type_ )) {
			set_pixel_type_( words.at(1) );
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_bw_threshold_ )) {
			cl_gts_gui.valinp_bw_threshold->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_bw_threshold)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_grayscale_brightness_ )) {
			cl_gts_gui.valinp_grays_brightness->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_brightness)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_grayscale_contrast_ )) {
			cl_gts_gui.valinp_grays_contrast->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_contrast)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_grayscale_gamma_ )) {
			cl_gts_gui.valinp_grays_gamma->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_grays_gamma)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rgb_brightness_ )) {
			cl_gts_gui.valinp_rgb_brightness->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_brightness)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rgb_contrast_ )) {
			cl_gts_gui.valinp_rgb_contrast->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_contrast)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}
		else if ((2 == words.size()) &&
		(words.at(0) == this->str_rgb_gamma_ )) {
			cl_gts_gui.valinp_rgb_gamma->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_gamma)->value(
	std::stod(words.at(1)) // use C++11,throw exception then error
			);
		}

		//---------- legacy ----------

		/* color trace real time sw情報
		は固定にしたので設定しない
		this->str_color_trace_real_time_
		cl_gts_gui.menite_color_trace_real_time
		*/

		//---------- Number ----------

		else if (( (2==words.size())
			|| (3==words.size())
			|| (4==words.size())
		) && (words.at(0) == this->str_file_number_frame_)) {
			/* ファイル番号リストの一番始めにやること */
			if (false == fnum_list_sw) {
			 /* ファイル番号リストの存在の有無 */
			 fnum_list_sw = true;
			 /* 以前のリストをすべて削除 */
			 cl_gts_master.cl_file_number_list.remove_all();
			}

			/* 実際の画像ファイルの有無を調べて
			リストの最後に追加する */
	cl_gts_master.cl_file_number_list.append_fnum_list_with_chk_mark(
	 std::stoi(words.at(1)) // use C++11,throw exception then error
	);

			/* 選択状態の再現 */
			if (
			 ((2<words.size()) &&
	 		  (words.at(2) == this->str_file_number_selected_)
			 )
	 		||
			 ((3<words.size()) &&
			  (words.at(3) == this->str_file_number_selected_)
			 )
			) {
				cl_gts_gui.selbro_fnum_list->select(
				 cl_gts_gui.selbro_fnum_list->size());
			}
		}

		//---------- trace batch ----------

		else if ( (2 == words.size()) &&
		(words.at(0) == this->str_trace_batch_dir_ )) {
			if (ON != load_trace_batch_sw) { continue; }

		 cl_gts_master.cl_bro_trace_batch.init_trace_batch_dir(
				words.at(1).c_str() );
		}

		else if ( (2==words.size()) &&
		(words.at(0) == this->str_trace_batch_list_)) {
			if (ON != load_trace_batch_sw) { continue; }

			/* ファイル番号リストの一番始めにやること */
			if (false == trace_batch_list_sw) {
				/* ファイル番号リストの存在の有無 */
				trace_batch_list_sw = true;
				/* 以前のリストをすべて削除 */
				while (0 <
			cl_gts_gui.selbro_trace_batch_run_list->size()) {
			cl_gts_gui.selbro_trace_batch_run_list->remove(1);
				}
			}

			/* リストの最後に追加する */
			cl_gts_gui.selbro_trace_batch_run_list->insert(
			cl_gts_gui.selbro_trace_batch_run_list->size()+1,
				words.at(1).c_str()
			);
		}

		//---------- color trace enhancement----------

		else {
			if (!this->load_trace_src_hsv_( words )) {
				pri_funct_err_bttvr(
	 "Warning : memory_config::load_trace_src_hsv_(-) : ignore '%s' at line %d"
				,str.c_str() ,ii );
			}
		}
	}
}
int memory_config::load( const std::string& file_path, int load_trace_batch_sw )
{
 try { /* ファイル読込と伴う設定でのエラーを例外処理で行う */
	this->memory_of_path = file_path; /* 正常保存ならファイル名の記憶 */
	bool fnum_list_sw = false;
	bool trace_batch_list_sw = false;
	bool level_list_redisplay_sw = false;
	bool level_num_continue_type_sw = false;

	//---------- read file ----------
  {
	std::ifstream ifs( file_path );/* ファイル開く */
	ifs.exceptions(std::ios_base::failbit);/* エラー時例外送出設定 */
   try {	/* std::getline()はEOFの場合も例外を投げてしまう */
	this->load_ifs_( ifs
		, load_trace_batch_sw
		, fnum_list_sw
		, trace_batch_list_sw
		, level_list_redisplay_sw
		, level_num_continue_type_sw
	); /* ファイル読む */
   }
   catch ( std::fstream::failure& e ) {
	if ( std::ios_base::eofbit == false ) {
		throw; /* EOF以外の例外はエラーなので再び投げる */
	}
   }
	ifs.close(); /* ファイル閉じる */
  }

	//---------- after reading ----------

#if 0	/* --> configにセットする項目がない時は現状維持する */
	/* ファイルにframe listがない事が分かった時はlistをクリアする */
	if (false == fnum_list_sw) {
		/* 以前のリストをすべて削除 */
		cl_gts_master.cl_file_number_list.remove_all();
	}

	/* ファイルにtrace_batch listがない事が分かった時はlistをクリア */
	if (ON == load_trace_batch_sw) {
	 if (false == trace_batch_list_sw) {
		/* 以前のリストをすべて削除 */
		while (0 <
		cl_gts_gui.selbro_trace_batch_run_list->size()) {
		 cl_gts_gui.selbro_trace_batch_run_list->remove(1);
		}
	 }
	}

	/* frame number insert項目をゼロクリアする */
	/* --> configにセットする項目がない時は現状維持する */
	cl_gts_gui.norinp_fnum_insert->value(NULL);

	/* Level/Fileリストを再表示する */
	/* --> Dialog開くときセットするべきなのでここではやらない */
	if (true == level_list_redisplay_sw) {
		cl_gts_master.cl_bro_level.cb_list_redisplay();
	}
#endif

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	cl_gts_master.cl_color_trace_thickness.cb_enh_01();
	cl_gts_master.cl_color_trace_thickness.cb_enh_02();
	cl_gts_master.cl_color_trace_thickness.cb_enh_03();
	cl_gts_master.cl_color_trace_thickness.cb_enh_04();
	cl_gts_master.cl_color_trace_thickness.cb_enh_05();
	cl_gts_master.cl_color_trace_thickness.cb_enh_06();

	/* LevelのCancelを可能にするためmemoryしておく */
	cl_gts_master.cl_bro_level.memory_from_gui(
		cl_gts_gui.filinp_level_save_dir_path->value()
	);

	/* ファイル名を表示する */
	cl_gts_master.print_window_headline();

	/* frame number listにlevel名を表示する */
	cl_gts_gui.norout_crnt_scan_level_of_fnum->value(
		cl_gts_master.cl_bro_level.cp_levelname()
	);

	/* level名からfileが上書きなら注意表示 */
	cl_gts_master.cl_bro_level.cb_level_name();

	/* LevelのEnd/Endless指定がない時はStart...End指定にする */
	if (!level_num_continue_type_sw) {
		cl_gts_gui.valinp_level_num_end->show();
		cl_gts_gui.choice_level_num_endless_direction->hide();
		cl_gts_gui.selbro_fnum_list->activate();
		cl_gts_gui.choice_level_num_continue_type->value(0/*End*/);
	}

	/* 画面は空白表示する指定(データは残っている) */
	cl_gts_master.cl_ogl_view.no_view_canvas();

	/* 画面クリア設定 */
	cl_gts_master.cl_ogl_view.clear_opengl(
		cl_gts_gui.opengl_view->w(),
		cl_gts_gui.opengl_view->h()
	);
	/* 画面クリア */
	cl_gts_gui.opengl_view->flush();

	/* 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview();
 }
 catch (const std::ios_base::failure& e) {
	std::ostringstream ost;
	ost	<< "Error in loading \"" << file_path << "\","
		<< e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
 catch (...) {
	fl_alert( "Error in saving." );/* ユーザーに知らせる */
	return NG;
 }
	return OK;
}
