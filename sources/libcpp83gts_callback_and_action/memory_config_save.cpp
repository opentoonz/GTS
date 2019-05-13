#include <ctime>
#include <iostream>
#include <iomanip>	// std::setw()
#include <string>
#include <fstream>
#include <sstream>
#include <FL/Fl.H>
#include <FL/fl_ask.H> // fl_alert()
#ifdef _WIN32
#include "osapi_mbs_wcs.h"	// osapi::cp932_from_utf8(-)
#endif
#include "osapi_getusername.h"
#include "osapi_gethostname.h"
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {

void save_stri_(
	const std::string& key ,const std::string& val ,std::ofstream& ofs
)
{
	ofs << std::setw(32) << std::left  << key
	    << ' ' << '\"'  << std::right << val << '\"' << '\n';
}
void save_fl64_(
	const std::string& key ,const double val ,std::ofstream& ofs
)
{
	ofs << std::setw(32) << std::left << key
	    << ' ' << std::right << std::setprecision(16) << val<< '\n';
	/*	double(=倍精度浮動小数点数)の精度は
		53bit約16桁(=53log10(2)=15.954589...) */
}
void save_3int_(
	const std::string& key ,const int rr ,const int gg ,const int bb
	,std::ofstream& ofs
)
{
	ofs << std::setw(32) << std::left << key
	    << ' ' << rr << ' ' << gg << ' ' << bb << '\n';
}

} // namespace

void memory_config::save_bool_( const std::string& key ,const int sw ,std::ofstream& ofs )
{
	ofs	<< std::setw(32) << std::left << key
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

#ifdef UNICODE
	std::string usern( osapi::mbs_from_wcs( osapi::getusername() ) );
	std::string hostn( osapi::mbs_from_wcs( osapi::gethostname() ) );
#else
	std::string usern( osapi::getusername() );
	std::string hostn( osapi::gethostname() );
#endif
	if (usern.empty()) { usern = "unknown"; }
	ofs << "# username  : " << usern << "\n";
	if (hostn.empty()) { hostn = "unknown"; }
	ofs << "# hostname  : " << hostn << "\n";
}
void memory_config::save_config_( std::ofstream& ofs )
{
	ofs << "\n# Config\n";
	save_stri_( this->str_config_dir_path_
	,cl_gts_master.cl_config.get_dir_path() ,ofs );
	save_stri_( this->str_config_open_file_name_
	,cl_gts_master.cl_config.get_open_file_name() ,ofs );
	save_stri_( this->str_config_save_file_name_
	,cl_gts_master.cl_config.get_save_file_name() ,ofs );
}
void memory_config::save_image_( std::ofstream& ofs )
{
	ofs << "\n# Image\n";
	save_stri_( this->str_image_dir_path_
	,cl_gts_master.cl_image.get_dir_path() ,ofs );
	save_stri_( this->str_image_open_file_name_
	,cl_gts_master.cl_image.get_open_file_name() ,ofs );
	save_stri_( this->str_image_open_image_format_
	,cl_gts_master.cl_image.get_open_image_format() ,ofs );
	save_stri_( this->str_image_save_file_name_
	,cl_gts_master.cl_image.get_save_file_name() ,ofs );
	save_stri_( this->str_image_save_image_format_
	,cl_gts_master.cl_image.get_save_image_format() ,ofs );
}
void memory_config::save_scan_and_save_( std::ofstream& ofs )
{
	ofs << "\n# " <<  cl_gts_gui.window_scan_and_save->label() << "\n";
	this->save_bool_( this->str_scan_filter_trace_sw_
		, cl_gts_gui.chkbtn_scan_filter_trace_sw->value() ,ofs );
	this->save_bool_( this->str_scan_filter_erase_dot_noise_sw_
		, cl_gts_gui.chkbtn_scan_filter_erase_dot_noise_sw->value() ,ofs);

	save_stri_( this->str_scan_save_dir_path_
	   ,cl_gts_gui.filinp_scan_save_dir_path->value() ,ofs );
	save_stri_( this->str_scan_save_file_head_
	   ,cl_gts_gui.strinp_scan_save_file_head->value() ,ofs );
	save_stri_( this->str_scan_save_number_format_
	   ,cl_gts_gui.output_scan_save_number_format->value() ,ofs );
	save_stri_( this->str_scan_save_image_format_
	   ,cl_gts_gui.choice_scan_save_image_format->text() ,ofs );

	save_fl64_( this->str_scan_num_start_
	   ,cl_gts_gui.valinp_scan_num_start->value() ,ofs );
	save_fl64_( this->str_scan_num_end_
	   ,cl_gts_gui.valinp_scan_num_end->value() ,ofs );
	{
	const char* str_nu_ct_ty = (
	(  cl_gts_gui.choice_scan_num_continue_type->value()
	== cl_gts_master.cl_number.get_end_type_value())
		? this->str_scan_num_continue_type_end_
		: this->str_scan_num_continue_type_endless_
	);
	save_stri_( this->str_scan_num_continue_type_ ,str_nu_ct_ty ,ofs);
	}
	save_stri_( this->str_scan_num_endless_direction_
	   ,cl_gts_gui.choice_scan_num_endless_direction->text() ,ofs );
}
void memory_config::save_trace_files_( std::ofstream& ofs )
{
	ofs << "\n# " <<  cl_gts_gui.window_trace_files->label() << "\n";
	save_stri_( this->str_trace_open_dir_path_
	   ,cl_gts_gui.filinp_trace_open_dir_path->value() ,ofs );
	save_stri_( this->str_trace_open_file_head_
	   ,cl_gts_gui.strinp_trace_open_file_head->value() ,ofs );
	save_stri_( this->str_trace_open_number_format_
	   ,cl_gts_gui.strinp_trace_open_number_format->value() ,ofs );
	save_stri_( this->str_trace_open_image_format_
	   ,cl_gts_gui.choice_trace_open_image_format->text() ,ofs );

	save_fl64_( this->str_trace_num_start_
	   ,cl_gts_gui.valout_trace_num_start->value() ,ofs );
	save_fl64_( this->str_trace_num_end_
	   ,cl_gts_gui.valout_trace_num_end->value() ,ofs );

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
	   ,cl_gts_gui.output_trace_save_number_format->value() ,ofs );
	save_stri_( this->str_trace_save_image_format_
	   ,cl_gts_gui.choice_trace_save_image_format->text() ,ofs );
}
void memory_config::save_crop_area_and_rot90_( std::ofstream& ofs )
{
	ofs << "\n# " <<  cl_gts_gui.window_area_and_rot90->label() << "\n";
	save_fl64_( this->str_area_offset_cm_x_
	   ,cl_gts_gui.valinp_area_offset_cm_x->value() ,ofs );
	save_fl64_( this->str_area_offset_cm_y_
	   ,cl_gts_gui.valinp_area_offset_cm_y->value() ,ofs );
	save_fl64_( this->str_area_size_cm_w_
	   ,cl_gts_gui.valinp_area_size_cm_w->value() ,ofs );
	save_fl64_( this->str_area_size_cm_h_
	   ,cl_gts_gui.valinp_area_size_cm_h->value() ,ofs );
	save_fl64_( this->str_area_size_pixel_w_
	   ,cl_gts_gui.valinp_area_size_pixel_w->value() ,ofs );
	save_fl64_( this->str_area_size_pixel_h_
	   ,cl_gts_gui.valinp_area_size_pixel_h->value() ,ofs );
	save_fl64_( this->str_area_resolution_dpi_
	   ,cl_gts_gui.valinp_area_reso->value() ,ofs );
	save_fl64_( this->str_area_aspect_ratio_w_
	   ,cl_gts_gui.valinp_area_aspect_ratio_w->value() ,ofs );
	save_fl64_( this->str_area_aspect_ratio_h_
	   ,cl_gts_gui.valinp_area_aspect_ratio_h->value() ,ofs );
	save_stri_( this->str_area_aspect_ratio_how_to_fix_
	   ,cl_gts_gui.radbut_area_aspect_ratio_w->value()?"W":"H" ,ofs );
	save_stri_( this->str_area_rotate_per_90_
	   ,cl_gts_gui.choice_rot90->text() ,ofs );
	save_stri_( this->str_scanner_type_
	   ,cl_gts_gui.txtout_scanner_type->value() ,ofs );
	save_fl64_( this->str_scanner_size_cm_w_
	   ,cl_gts_gui.valout_scanner_size_cm_w->value() ,ofs );
	save_fl64_( this->str_scanner_size_cm_h_
	   ,cl_gts_gui.valout_scanner_size_cm_h->value() ,ofs );
}
void memory_config::save_pixel_type_and_bright_( std::ofstream& ofs )
{
	ofs << "\n# " <<  cl_gts_gui.window_pixel_type_and_bright->label() << "\n";
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
void memory_config::save_trace_params_( std::ofstream& ofs )
{
	ofs << "\n# " <<  cl_gts_gui.window_trace_params->label() << "\n";

	this->save_bool_( this->str_trace_display_target_sw_
		, cl_gts_gui.chebut_trace_display_target_sw->value(),ofs);
	this->save_bool_( this->str_trace_display_main_sw_
		, cl_gts_gui.chebut_trace_display_main_sw->value(),ofs);

	std::vector<cb_trace_params::widget_set>& wset(
		cl_gts_master.cl_trace_params.widget_sets
	);
	for (unsigned ii=0 ; ii < wset.size() ; ++ii) {
		auto& trace_set = wset.at(ii);
		std::string ti( this->str_trace_params_title_ );
		ti += " ";
		ti += std::to_string(ii);
		ti += " ";

		this->save_bool_(
			ti+this->str_trace_enable_sw_
			,trace_set.chebut_enable_sw->value()
			,ofs
		);

		unsigned char r=0, g=0, b=0;
		cl_gts_master.cl_trace_params.get_target_rgb( ii ,r ,g ,b );
		save_3int_(
			ti+this->str_trace_target_rgb_
			,static_cast<int>(r)
			,static_cast<int>(g)
			,static_cast<int>(b)
			,ofs
		);

		save_fl64_(
			ti+this->str_trace_thickness_
			,trace_set.valinp_thickness->value()
			,ofs
		);

		save_fl64_(
			ti+this->str_trace_hue_min_
			,trace_set.valinp_hue_min->value()
			,ofs
		);

		save_fl64_(
			ti+this->str_trace_hue_max_
			,trace_set.valinp_hue_max->value()
			,ofs
		);
		this->save_bool_(
			ti+this->str_trace_rotate360_sw_
			,trace_set.chebut_rotate360_sw->value()
			,ofs
		);

		save_fl64_(
			ti+this->str_trace_slope_deg_
			,trace_set.valinp_slope_deg->value()
			,ofs
		);

		save_fl64_(
			ti+this->str_trace_intercept_
			,trace_set.valinp_intercept->value()
			,ofs
		);

		this->save_bool_(
			ti+this->str_trace_display_sw_
			,trace_set.chebut_display_sw->value()
			,ofs
		);
	}
}
void memory_config::save_trace_batch_( std::ofstream& ofs )
{
	ofs << "\n# " <<  cl_gts_gui.window_trace_batch->label() << "\n";
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
	ofs << "\n# " <<  cl_gts_gui.window_number->label() << "\n";
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
	/* ファイル開く */
#ifdef _WIN32
	std::ofstream ofs( osapi::cp932_from_utf8( file_path ) );
#else
	std::ofstream ofs(file_path);
#endif
	ofs.exceptions(std::ios_base::failbit);/* エラー時例外送出設定 */
	this->save_head_(ofs);
	this->save_config_(ofs);
	this->save_image_(ofs);
	this->save_scan_and_save_(ofs);
	this->save_trace_files_(ofs);
	this->save_crop_area_and_rot90_(ofs);
	this->save_pixel_type_and_bright_(ofs);
	//this->save_trace_parameters_(ofs);
	this->save_trace_params_(ofs);
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
