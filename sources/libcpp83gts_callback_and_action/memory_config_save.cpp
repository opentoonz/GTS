#include <ctime>
#include <iostream>
#include <iomanip>	// std::setw()
#include <string>
#include <fstream>
#include <sstream>
#include <FL/Fl.H>
#include <FL/fl_ask.H> // fl_alert()
#include "ptbl_funct.h" // ptbl_get_cp_username
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {

void save_stri_(
	const std::string& key ,const std::string& val ,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left  << key
	    << ' ' << '\"'  << std::right << val << '\"' << '\n';
}
void save_fl64_(
	const std::string& key ,const double val ,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left << key
	    << ' ' << std::right << std::setprecision(16) << val<< '\n';
	/*	double(=倍精度浮動小数点数)の精度は
		53bit約16桁(=53log10(2)=15.954589...) */
}
void save_3int_(
	const std::string& key ,const int rr ,const int gg ,const int bb
	,std::ofstream& ofs
)
{
	ofs << std::setw(28) << std::left << key
	    << ' ' << rr << ' ' << gg << ' ' << bb << '\n';
}

} // namespace

void memory_config::save_bool_( const std::string& key ,const char sw ,std::ofstream& ofs )
{
	ofs	<< std::setw(28) << std::left << key
		<< ' ' << std::right
		<< (sw==1 ?this->str_on_:this->str_off_) << '\n';
}
void memory_config::save_head_( std::ofstream& ofs )
{
	ofs	<< "# "  << cl_gts_master.cp_release_name()
		<< " : " << cl_gts_master.cp_release_number()
		<< " "   << cl_gts_master.cp_release_date()
		<< "\n";

	time_t tt = time(nullptr);
	ofs << "# date time : " << asctime(localtime(&tt));
	/* asctime()の戻り値は26文字とヌル文字の入った文字列へのポインター
	Example : "Fri Sep 13 00:00:00 1986\n\0"
	asctime()が返す文字列はstatic領域なのでfree()してはいけません
	*/

	const char* un = ptbl_get_cp_username();
	if (un == nullptr) { un = "unknown"; }
	ofs << "# username  : " << un << "\n\n";

	const char* hn = ptbl_get_cp_hostname();
	if (hn == nullptr) { hn = "unknown"; }
	ofs << "# hostname  : " << hn << "\n\n";
}
void memory_config::save_config_( std::ofstream& ofs )
{
	save_stri_( this->str_config_dir_path_
	,cl_gts_master.cl_config.get_dir_path() ,ofs );
	save_stri_( this->str_config_open_file_name_
	,cl_gts_master.cl_config.get_open_file_name() ,ofs );
	save_stri_( this->str_config_save_file_name_
	,cl_gts_master.cl_config.get_save_file_name() ,ofs );
}
void memory_config::save_scan_and_save_( std::ofstream& ofs )
{
	this->save_bool_( this->str_scan_filter_trace_sw_
		, cl_gts_gui.chkbtn_scan_filter_trace_sw->value() ,ofs );
	this->save_bool_( this->str_scan_filter_erase_dot_noise_sw_
		, cl_gts_gui.chkbtn_scan_filter_erase_dot_noise_sw->value() ,ofs);

	save_stri_( this->str_scan_save_dir_path_
	   ,cl_gts_gui.filinp_scan_save_dir_path->value() ,ofs );
	save_stri_( this->str_scan_save_file_head_
	   ,cl_gts_gui.strinp_scan_save_file_head->value() ,ofs );
	save_stri_( this->str_scan_save_number_format_
	   ,cl_gts_gui.strinp_scan_save_number_format->value() ,ofs );
	save_stri_( this->str_scan_save_image_format_
	   ,cl_gts_gui.choice_scan_save_image_format->text() ,ofs );

	save_fl64_( this->str_scan_num_start_
	   ,cl_gts_gui.valinp_scan_num_start->value() ,ofs );
	save_fl64_( this->str_scan_num_end_
	   ,cl_gts_gui.valinp_scan_num_end->value() ,ofs );
	save_stri_( this->str_scan_num_continue_type_
	   ,cl_gts_gui.choice_scan_num_continue_type->text() ,ofs);
	save_stri_( this->str_scan_num_endless_direction_
	   ,cl_gts_gui.choice_scan_num_endless_direction->text() ,ofs );
}
void memory_config::save_trace_files_( std::ofstream& ofs )
{
	save_stri_( this->str_trace_open_dir_path_
	   ,cl_gts_gui.filinp_trace_open_dir_path->value() ,ofs );
	save_stri_( this->str_trace_open_file_head_
	   ,cl_gts_gui.strinp_trace_open_file_head->value() ,ofs );
	save_stri_( this->str_trace_open_number_format_
	   ,cl_gts_gui.strinp_trace_open_number_format->value() ,ofs );
	save_stri_( this->str_trace_open_image_format_
	   ,cl_gts_gui.choice_trace_open_image_format->text() ,ofs );

	save_fl64_( this->str_trace_num_start_
	   ,cl_gts_gui.valinp_trace_num_start->value() ,ofs );
	save_fl64_( this->str_trace_num_end_
	   ,cl_gts_gui.valinp_trace_num_end->value() ,ofs );

/*
	this->save_bool_( this->str_trace_filter_trace_sw_
	  , cl_gts_gui.chkbtn_trace_filter_trace_sw->value() ,ofs );
*/
	this->save_bool_( this->str_trace_filter_erase_dot_noise_sw_
		, cl_gts_gui.chkbtn_trace_filter_erase_dot_noise_sw->value(),ofs);

	save_stri_( this->str_trace_save_dir_path_
	   ,cl_gts_gui.filinp_trace_save_dir_path->value() ,ofs );
	save_stri_( this->str_trace_save_file_head_
	   ,cl_gts_gui.strinp_trace_save_file_head->value() ,ofs );
	save_stri_( this->str_trace_save_number_format_
	   ,cl_gts_gui.strinp_trace_save_number_format->value() ,ofs );
	save_stri_( this->str_trace_save_image_format_
	   ,cl_gts_gui.choice_trace_save_image_format->text() ,ofs );
}
void memory_config::save_crop_area_and_rot90_( std::ofstream& ofs )
{
	save_stri_( this->str_area_select_
	   ,cl_gts_gui.choice_area_selecter->text() ,ofs );
	save_fl64_( this->str_area_x_pos_
	   ,cl_gts_gui.valinp_area_x_pos->value() ,ofs );
	save_fl64_( this->str_area_y_pos_
	   ,cl_gts_gui.valinp_area_y_pos->value() ,ofs );
	save_stri_( this->str_area_aspect_ratio_select_
	   ,cl_gts_gui.choice_area_aspect_ratio_selecter->text() ,ofs);
	save_fl64_( this->str_area_x_size_
	   ,cl_gts_gui.valinp_area_x_size->value() ,ofs );
	save_fl64_( this->str_area_y_size_
	   ,cl_gts_gui.valinp_area_y_size->value() ,ofs );
	save_fl64_( this->str_area_x_pixel_
	   ,cl_gts_gui.valinp_area_x_pixel->value() ,ofs );
	save_fl64_( this->str_area_y_pixel_
	   ,cl_gts_gui.valinp_area_y_pixel->value() ,ofs );
	save_fl64_( this->str_area_resolution_dpi_
	   ,cl_gts_gui.valinp_area_reso->value() ,ofs );
	save_stri_( this->str_rotate_per_90_
	   ,cl_gts_gui.choice_rot90->text() ,ofs );
	save_stri_( this->str_scanner_type_
	   ,cl_gts_gui.txtout_scanner_type->value() ,ofs );
	save_fl64_( this->str_scanner_x_max_
	   ,cl_gts_gui.valout_scanner_width_max->value() ,ofs );
	save_fl64_( this->str_scanner_y_max_
	   ,cl_gts_gui.valout_scanner_height_max->value() ,ofs );
}
void memory_config::save_pixel_type_and_bright_( std::ofstream& ofs )
{
	save_stri_( this->str_pixel_type_
	   ,cl_gts_gui.choice_pixel_type->text() ,ofs );

	save_fl64_( this->str_bw_threshold_
	   ,cl_gts_gui.valinp_bw_threshold->value() ,ofs );

	save_fl64_( this->str_grayscale_brightness_
	   ,cl_gts_gui.valinp_grayscale_brightness->value() ,ofs );
	save_fl64_( this->str_grayscale_contrast_
	   ,cl_gts_gui.valinp_grayscale_contrast->value() ,ofs );
	save_fl64_( this->str_grayscale_gamma_
	   ,cl_gts_gui.valinp_grayscale_gamma->value() ,ofs );

	save_fl64_( this->str_rgb_brightness_
	   ,cl_gts_gui.valinp_rgb_brightness->value() ,ofs );
	save_fl64_( this->str_rgb_contrast_
	   ,cl_gts_gui.valinp_rgb_contrast->value() ,ofs );
	save_fl64_( this->str_rgb_gamma_
	   ,cl_gts_gui.valinp_rgb_gamma->value() ,ofs );
}
void memory_config::save_trace_parameters_( std::ofstream& ofs )
{
	unsigned char uchar_red, uchar_gre, uchar_blu;

	/* 01 ------------------------------------------------ */
	this->save_bool_( this->str_color_trace_01_chk_
		, cl_gts_gui.chkbtn_color_trace_01_chk->value() ,ofs );
	save_fl64_( this->str_color_trace_01_src_hh_min_
	  , cl_gts_gui.valinp_color_trace_01_src_hh_min->value(),ofs);
	save_fl64_( this->str_color_trace_01_src_hh_max_
	  , cl_gts_gui.valinp_color_trace_01_src_hh_max->value(),ofs);
	save_fl64_( this->str_color_trace_01_src_aa_min_
	  , cl_gts_gui.valinp_color_trace_01_src_aa_min->value(),ofs);
	save_fl64_( this->str_color_trace_01_src_aa_max_
	  , cl_gts_gui.valinp_color_trace_01_src_aa_max->value(),ofs);
	save_fl64_( this->str_color_trace_01_src_bb_min_
	  , cl_gts_gui.valinp_color_trace_01_src_bb_min->value(),ofs);
	save_fl64_( this->str_color_trace_01_src_bb_max_
	  , cl_gts_gui.valinp_color_trace_01_src_bb_max->value(),ofs);

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_01 , &uchar_red, &uchar_gre, &uchar_blu );
	save_3int_( this->str_color_trace_01_tgt_rgb_
		, uchar_red, uchar_gre, uchar_blu ,ofs );
	save_stri_( this->str_color_trace_01_tgt_color_
		, cl_gts_gui.roubut_thickness_01_tgt_is_bl->value() == 1
		  ? this->str_color_black_ : this->str_color_not_black_
		, ofs
	);
	/* 02 ------------------------------------------------*/
	this->save_bool_( this->str_color_trace_02_chk_
		, cl_gts_gui.chkbtn_color_trace_02_chk->value() ,ofs );
	save_fl64_( this->str_color_trace_02_src_hh_min_
	  , cl_gts_gui.valinp_color_trace_02_src_hh_min->value(),ofs);
	save_fl64_( this->str_color_trace_02_src_hh_max_
	  , cl_gts_gui.valinp_color_trace_02_src_hh_max->value(),ofs);
	save_fl64_( this->str_color_trace_02_src_aa_min_
	  , cl_gts_gui.valinp_color_trace_02_src_aa_min->value(),ofs);
	save_fl64_( this->str_color_trace_02_src_aa_max_
	  , cl_gts_gui.valinp_color_trace_02_src_aa_max->value(),ofs);
	save_fl64_( this->str_color_trace_02_src_bb_min_
	  , cl_gts_gui.valinp_color_trace_02_src_bb_min->value(),ofs);
	save_fl64_( this->str_color_trace_02_src_bb_max_
	  , cl_gts_gui.valinp_color_trace_02_src_bb_max->value(),ofs);

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_02 , &uchar_red, &uchar_gre, &uchar_blu );
	save_3int_( this->str_color_trace_02_tgt_rgb_
		, uchar_red, uchar_gre, uchar_blu ,ofs );
	save_stri_( this->str_color_trace_02_tgt_color_
		, cl_gts_gui.roubut_thickness_02_tgt_is_bl->value() == 1
		  ? this->str_color_black_ : this->str_color_not_black_
		, ofs
	);
	/* 03 ------------------------------------------------*/
	this->save_bool_( this->str_color_trace_03_chk_
		, cl_gts_gui.chkbtn_color_trace_03_chk->value() ,ofs );
	save_fl64_( this->str_color_trace_03_src_hh_min_
	  , cl_gts_gui.valinp_color_trace_03_src_hh_min->value(),ofs);
	save_fl64_( this->str_color_trace_03_src_hh_max_
	  , cl_gts_gui.valinp_color_trace_03_src_hh_max->value(),ofs);
	save_fl64_( this->str_color_trace_03_src_aa_min_
	  , cl_gts_gui.valinp_color_trace_03_src_aa_min->value(),ofs);
	save_fl64_( this->str_color_trace_03_src_aa_max_
	  , cl_gts_gui.valinp_color_trace_03_src_aa_max->value(),ofs);
	save_fl64_( this->str_color_trace_03_src_bb_min_
	  , cl_gts_gui.valinp_color_trace_03_src_bb_min->value(),ofs);
	save_fl64_( this->str_color_trace_03_src_bb_max_
	  , cl_gts_gui.valinp_color_trace_03_src_bb_max->value(),ofs);

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_03 , &uchar_red, &uchar_gre, &uchar_blu );
	save_3int_( this->str_color_trace_03_tgt_rgb_
		, uchar_red, uchar_gre, uchar_blu ,ofs );
	save_stri_( this->str_color_trace_03_tgt_color_
		, cl_gts_gui.roubut_thickness_03_tgt_is_bl->value() == 1
		  ? this->str_color_black_ : this->str_color_not_black_
		, ofs
	);
	/* 04 ------------------------------------------------*/
	this->save_bool_( this->str_color_trace_04_chk_
		, cl_gts_gui.chkbtn_color_trace_04_chk->value() ,ofs );
	save_fl64_( this->str_color_trace_04_src_hh_min_
	  , cl_gts_gui.valinp_color_trace_04_src_hh_min->value(),ofs);
	save_fl64_( this->str_color_trace_04_src_hh_max_
	  , cl_gts_gui.valinp_color_trace_04_src_hh_max->value(),ofs);
	save_fl64_( this->str_color_trace_04_src_aa_min_
	  , cl_gts_gui.valinp_color_trace_04_src_aa_min->value(),ofs);
	save_fl64_( this->str_color_trace_04_src_aa_max_
	  , cl_gts_gui.valinp_color_trace_04_src_aa_max->value(),ofs);
	save_fl64_( this->str_color_trace_04_src_bb_min_
	  , cl_gts_gui.valinp_color_trace_04_src_bb_min->value(),ofs);
	save_fl64_( this->str_color_trace_04_src_bb_max_
	  , cl_gts_gui.valinp_color_trace_04_src_bb_max->value(),ofs);

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_04 , &uchar_red, &uchar_gre, &uchar_blu );
	save_3int_( this->str_color_trace_04_tgt_rgb_
		, uchar_red, uchar_gre, uchar_blu ,ofs );
	save_stri_( this->str_color_trace_04_tgt_color_
		, cl_gts_gui.roubut_thickness_04_tgt_is_bl->value() == 1
		  ? this->str_color_black_ : this->str_color_not_black_
		, ofs
	);
	/* 05 ------------------------------------------------*/
	this->save_bool_( this->str_color_trace_05_chk_
		, cl_gts_gui.chkbtn_color_trace_05_chk->value() ,ofs );
	save_fl64_( this->str_color_trace_05_src_hh_min_
	  , cl_gts_gui.valinp_color_trace_05_src_hh_min->value(),ofs);
	save_fl64_( this->str_color_trace_05_src_hh_max_
	  , cl_gts_gui.valinp_color_trace_05_src_hh_max->value(),ofs);
	save_fl64_( this->str_color_trace_05_src_aa_min_
	  , cl_gts_gui.valinp_color_trace_05_src_aa_min->value(),ofs);
	save_fl64_( this->str_color_trace_05_src_aa_max_
	  , cl_gts_gui.valinp_color_trace_05_src_aa_max->value(),ofs);
	save_fl64_( this->str_color_trace_05_src_bb_min_
	  , cl_gts_gui.valinp_color_trace_05_src_bb_min->value(),ofs);
	save_fl64_( this->str_color_trace_05_src_bb_max_
	  , cl_gts_gui.valinp_color_trace_05_src_bb_max->value(),ofs);

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_05 , &uchar_red, &uchar_gre, &uchar_blu );
	save_3int_( this->str_color_trace_05_tgt_rgb_
		, uchar_red, uchar_gre, uchar_blu ,ofs );
	save_stri_( this->str_color_trace_05_tgt_color_
		, cl_gts_gui.roubut_thickness_05_tgt_is_bl->value() == 1
		  ? this->str_color_black_ : this->str_color_not_black_
		, ofs
	);
	/* 06 ------------------------------------------------*/
	this->save_bool_( this->str_color_trace_06_chk_
		, cl_gts_gui.chkbtn_color_trace_06_chk->value() ,ofs );
	save_fl64_( this->str_color_trace_06_src_hh_min_
	  , cl_gts_gui.valinp_color_trace_06_src_hh_min->value(),ofs);
	save_fl64_( this->str_color_trace_06_src_hh_max_
	  , cl_gts_gui.valinp_color_trace_06_src_hh_max->value(),ofs);
	save_fl64_( this->str_color_trace_06_src_aa_min_
	  , cl_gts_gui.valinp_color_trace_06_src_aa_min->value(),ofs);
	save_fl64_( this->str_color_trace_06_src_aa_max_
	  , cl_gts_gui.valinp_color_trace_06_src_aa_max->value(),ofs);
	save_fl64_( this->str_color_trace_06_src_bb_min_
	  , cl_gts_gui.valinp_color_trace_06_src_bb_min->value(),ofs);
	save_fl64_( this->str_color_trace_06_src_bb_max_
	  , cl_gts_gui.valinp_color_trace_06_src_bb_max->value(),ofs);

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_06 , &uchar_red, &uchar_gre, &uchar_blu );
	save_3int_( this->str_color_trace_06_tgt_rgb_
		, uchar_red, uchar_gre, uchar_blu ,ofs );
	save_stri_( this->str_color_trace_06_tgt_color_
		,  cl_gts_gui.roubut_thickness_06_tgt_is_bl->value() == 1
		  ? this->str_color_black_ : this->str_color_not_black_
		, ofs
	);
}
void memory_config::save_trace_batch_( std::ofstream& ofs )
{
	save_stri_( this->str_trace_batch_dir_
		,cl_gts_master.cl_trace_batch.get_dir_path() ,ofs );

	/* リストを全てサーチ */
	for (int ii = 1;
	ii <= cl_gts_gui.selbro_trace_batch_config_list->size(); ++ii) {
	 save_stri_(this->str_trace_batch_list_
		,cl_gts_gui.selbro_trace_batch_config_list->text(ii) ,ofs );
	}
}
void memory_config::save_number_( std::ofstream& ofs )
{
	save_stri_( this->str_number_action_type_
	    ,cl_gts_gui.output_number_action_type->value() ,ofs );

	/* リストを全てサーチ */
	for (int ii = 1; ii <= cl_gts_gui.selbro_number_list->size(); ++ii) {
		ofs	<< this->str_file_number_frame_
			<< ' ' << cl_gts_gui.selbro_number_list->text(ii);
		if ( cl_gts_gui.selbro_number_list->selected(ii) ) {
		 ofs	<< ' ' << this->str_file_number_selected_;
		}
		ofs	<< '\n';
	}
}

int memory_config::save( const std::string& file_path )
{
 try {
	std::ofstream ofs(file_path); /* ファイル開く */
	ofs.exceptions(std::ios_base::failbit);/* エラー時例外送出設定 */
	this->save_head_(ofs);
	this->save_config_(ofs);
	this->save_scan_and_save_(ofs);
	this->save_trace_files_(ofs);
	this->save_crop_area_and_rot90_(ofs);
	this->save_pixel_type_and_bright_(ofs);
	this->save_trace_parameters_(ofs);
	this->save_trace_batch_(ofs);
	this->save_number_(ofs);
	ofs.close(); /* ファイル閉じる */
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
	ost << "Error(other) in saving.";
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
	return OK;
}
