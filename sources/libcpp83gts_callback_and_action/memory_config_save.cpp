#include <FL/Fl.H>
#include <FL/fl_ask.H> // fl_alert()
#include <ctime>
#include <iomanip>	// std::setw()
#include <string>
#include <fstream>
#include <sstream>
#include "ptbl_funct.h" // ptbl_get_cp_username
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

//--------------------------------------------------
void memory_config::save_str_(
	const std::string& key ,const std::string& val ,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left  << key
	    << ' ' << '\"'  << std::right << val << '\"' << '\n';
}
void memory_config::save_word_(
	const std::string& key ,const std::string& val ,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left << key
	    << ' ' << std::right << val<< '\n';
}
void memory_config::save_f64_(
	const std::string& key ,const double val ,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left << key
	    << ' ' << std::right << std::setprecision(16) << val<< '\n';
	/*	double(=倍精度浮動小数点数)の精度は
		53bit約16桁(=53log10(2)=15.954589...) */
}
void memory_config::save_3int_(
	const std::string& key ,const int rr ,const int gg ,const int bb
	,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left << key
	    << ' ' << rr << ' ' << gg << ' ' << bb << '\n';
}
//----------
void memory_config::save_head_( std::ofstream& ofs )
{
	time_t tt = time(nullptr);
	ofs << "# date and time : " << asctime(localtime(&tt));
	/* asctime()の戻り値は26文字とヌル文字の入った文字列へのポインター
		Example : "Fri Sep 13 00:00:00 1986\n\0"
		cpの示す文字列はstatic領域なのでfree()してはいけません
	*/

	const char* cp = ptbl_get_cp_username();
	if (cp == nullptr) { cp = "unknown"; }
	ofs << "# current user  : " << cp << "\n#\n";
}
void memory_config::save_config_( std::ofstream& ofs )
{
	this->save_str_( this->str_config_dir_
		,cl_gts_gui.filinp_config_load_dir->value() ,ofs );
	this->save_str_( this->str_config_load_file_
		,cl_gts_gui.strinp_config_load_file->value() ,ofs );
	this->save_str_( this->str_config_save_as_file_
		,cl_gts_gui.strinp_config_save_as_file->value() ,ofs );
}
void memory_config::save_level_( std::ofstream& ofs )
{
	this->save_str_( this->str_level_save_dir_path_
		,cl_gts_gui.filinp_level_save_dir_path->value() ,ofs );
	this->save_str_( this->str_level_save_file_head_
		,cl_gts_gui.strinp_level_save_file_head->value() ,ofs );
	this->save_f64_( this->str_level_num_start_
		,cl_gts_gui.valinp_level_num_start->value()
		,ofs );
	this->save_f64_( this->str_level_num_end_
		,cl_gts_gui.valinp_level_num_end->value()
		,ofs );
	this->save_str_( this->str_level_num_continue_type_
		,cl_gts_gui.choice_level_num_continue_type->text()
		,ofs);
	this->save_str_( this->str_level_num_endless_direction_
		,cl_gts_gui.choice_level_num_endless_direction->text()
		,ofs );
	this->save_str_( this->str_level_save_image_format_
		,cl_gts_gui.choice_level_save_image_format->text() ,ofs );

	this->save_word_( this->str_filter_rgb_erase_dot_noise_sw_
		, cl_gts_gui.chkbtn_filter_rgb_erase_dot_noise_sw->value()?
		 this->str_on_:this->str_off_,ofs );
	this->save_word_( this->str_filter_rgb_color_trace_sw_
		, cl_gts_gui.chkbtn_filter_rgb_color_trace_sw->value()?
			this->str_on_:this->str_off_ ,ofs );

	this->save_str_( this->str_level_open_dir_path_
		,cl_gts_gui.filinp_level_open_dir_path->value() ,ofs );
	this->save_str_( this->str_level_open_file_head_
		,cl_gts_gui.strinp_level_open_file_head->value() ,ofs );
	this->save_str_( this->str_level_open_image_format_
		,cl_gts_gui.choice_level_open_image_format->text() ,ofs );

	this->save_str_( this->str_level_list_form_
		,cl_gts_gui.choice_level_list_form->text() ,ofs );
}
void memory_config::save_area_( std::ofstream& ofs )
{
	this->save_str_(	this->str_area_select_
		       ,cl_gts_gui.choice_area_selecter->text() ,ofs );
	this->save_f64_(	this->str_area_x_pos_
		       ,cl_gts_gui.valinp_area_x_pos->value() ,ofs );
	this->save_f64_(	this->str_area_y_pos_
		       ,cl_gts_gui.valinp_area_y_pos->value() ,ofs );
	this->save_str_(	this->str_area_aspect_ratio_select_
		       ,cl_gts_gui.choice_area_aspect_ratio_selecter->text()
		       ,ofs);
	this->save_f64_(	this->str_area_x_size_
		       ,cl_gts_gui.valinp_area_x_size->value() ,ofs );
	this->save_f64_(	this->str_area_y_size_
		       ,cl_gts_gui.valinp_area_y_size->value() ,ofs );
	this->save_f64_(	this->str_area_x_pixel_
		       ,cl_gts_gui.valinp_area_x_pixel->value() ,ofs );
	this->save_f64_(	this->str_area_y_pixel_
		       ,cl_gts_gui.valinp_area_y_pixel->value() ,ofs );
	this->save_f64_(	this->str_area_resolution_dpi_
		       ,cl_gts_gui.valinp_area_reso->value() ,ofs );
	this->save_str_(	this->str_rotate_per_90_
			       ,cl_gts_gui.choice_rot90->text() ,ofs );
	this->save_str_(	this->str_scanner_type_
		       ,cl_gts_gui.txtout_scanner_type->value() ,ofs );
	this->save_f64_(	this->str_scanner_x_max_
		       ,cl_gts_gui.valout_scanner_width_max->value() ,ofs );
	this->save_f64_(	this->str_scanner_y_max_
		       ,cl_gts_gui.valout_scanner_height_max->value() ,ofs );
}
void memory_config::save_pixel_type_( std::ofstream& ofs )
{
	this->save_str_(	this->str_pixel_type_
		       ,cl_gts_gui.choice_pixel_type->text() ,ofs );

	this->save_f64_(	this->str_bw_threshold_
		       ,cl_gts_gui.valinp_bw_threshold->value() ,ofs );

	this->save_f64_(	this->str_grayscale_brightness_
		       ,cl_gts_gui.valinp_grays_brightness->value() ,ofs );
	this->save_f64_(	this->str_grayscale_contrast_
		       ,cl_gts_gui.valinp_grays_contrast->value() ,ofs );
	this->save_f64_(	this->str_grayscale_gamma_
		       ,cl_gts_gui.valinp_grays_gamma->value() ,ofs );

	this->save_f64_(	this->str_rgb_brightness_
		       ,cl_gts_gui.valinp_rgb_brightness->value() ,ofs );
	this->save_f64_(	this->str_rgb_contrast_
		       ,cl_gts_gui.valinp_rgb_contrast->value() ,ofs );
	this->save_f64_(	this->str_rgb_gamma_
		       ,cl_gts_gui.valinp_rgb_gamma->value() ,ofs );
}
void memory_config::save_fnum_( std::ofstream& ofs )
{
	/* リストを全てサーチ */
	for (int ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		ofs	<< this->str_file_number_frame_
			<< ' ' << cl_gts_gui.selbro_fnum_list->text(ii);
		if ( cl_gts_gui.selbro_fnum_list->selected(ii) ) {
		 ofs	<< ' ' << this->str_file_number_selected_;
		}
		ofs	<< '\n';
	}
}
void memory_config::save_trace_batch_( std::ofstream& ofs )
{
	this->save_str_( this->str_trace_batch_dir_
		,cl_gts_gui.filinp_trace_batch_dir->value() ,ofs );

	/* リストを全てサーチ */
	for (int ii = 1;
	ii <= cl_gts_gui.selbro_trace_batch_run_list->size(); ++ii) {
	 this->save_str_(this->str_trace_batch_list_
		,cl_gts_gui.selbro_trace_batch_run_list->text(ii) ,ofs );
	}
}
//----------
int memory_config::save( const char *file_path )
{
 try {
	std::ofstream ofs(file_path); /* ファイル開く */
	ofs.exceptions(std::ios_base::failbit);/* エラー時例外送出設定 */
	this->save_head_(ofs);
	this->save_config_(ofs);
	this->save_level_(ofs);
	this->save_area_(ofs);
	this->save_pixel_type_(ofs);
	this->save_trace_src_hsv_(ofs);
	this->save_fnum_(ofs);
	this->save_trace_batch_(ofs);
	ofs.close(); /* ファイル閉じる */

	this->memory_of_path = file_path; /* 正常保存ならファイル名の記憶 */
	cl_gts_master.print_window_headline(); /* ファイル名を表示する */
 }
 catch (const std::ios_base::failure& e) {
	std::ostringstream ost;
	ost	<< "Error(ios_base::failure) in saving \""
		<< file_path << "\","
		<< e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
 catch (std::exception& e) {
	std::ostringstream ost;
	ost	<< "Error(exception) in saving \""
		<< file_path << "\","
		<< e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
 catch (...) {
	std::ostringstream ost;
	ost << "Error(other) in saving.";/* ユーザーに知らせる */
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
	return OK;
}
//--------------------------------------------------
