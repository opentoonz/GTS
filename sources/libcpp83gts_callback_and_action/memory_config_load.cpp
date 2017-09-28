#include <ctype.h> // isdigit()
#include <FL/fl_ask.H> // fl_alert()
#include <iostream>
#include <fstream>
#include <sstream>
#include <string> // std::getline() , std::stod() --> C++11,throw exception then error
#include "pri.h"
#include "ptbl_funct.h" // ptbl_dir_or_file_is_exist(-)
#include "igs_lex_white_space_and_double_quote.h"
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace { //--------------------------------------------------------

void set_rotate_per_90_( const std::string& str1 )
{
	if (isdigit(str1.c_str()[0])) { /* For Legacy...Delete sameday */
		 cl_gts_gui.choice_rot90->value( std::stoi(str1) );
	}
	else {
	/*
		0=CW_-90 , 1=CW_0 , 2=CW_90 , 3=CW_180
		0=CW_-90はScannerにとっての正対なのでこれ以外は回転処理必要
		1=CW_0は作業者にとっての正対
	*/
		const Fl_Menu_Item *crnt =
			cl_gts_gui.choice_rot90->find_item( str1.c_str() );
		if (crnt == nullptr) {
			return;
		}
		cl_gts_gui.choice_rot90->value( crnt );
	}
	/* 設定したGUI値をメモリしとく */
	cl_gts_master.cl_area_and_rot90.set_previous_choice_rot90(
					  cl_gts_gui.choice_rot90->value()
	);
}
void set_pixel_type_( const std::string& str )
{
	if (isdigit(str.c_str()[0])) {/* For Legacy Format...Delete sameday */
		 cl_gts_gui.choice_pixel_type->value(
		  std::stoi(str) // use C++11,throw exception then error
		 );
	}
	else {
		cl_gts_master.cb_choice_pixel_type_title( str );
	}

	cl_gts_master.cb_choice_pixel_type_menu();
}

} // namespace -------------------------------------------------------

void memory_config::load_ifs_(
	std::ifstream& ifs
	,bool& scan_num_continue_type_sw
)
{
	if ( this->load_number_sw_ ) {
		/* numberリストをすべて削除 */
		cl_gts_gui.selbro_number_list->clear();
		cl_gts_gui.selbro_number_list->redraw();
	}

	if ( this->load_trace_batch_sw_ ) {
		/* trace_configリストをすべて削除 */
		cl_gts_gui.selbro_trace_batch_config_list->clear();
	}

	std::string str;
	for (int ii = 1 ;std::getline(ifs,str) ;++ii) {/* 一行読む */
		if (str.empty()) { continue; }/* 空行は無視 */
		if ('#' == str.at(0)) { continue; }/* コメント行は無視 */
		std::vector< std::string > words; /* 単語に分割 */
		igs::lex::white_space_and_double_quote(str,words);
		if (words.size() < 2) { continue; }/* キーワードしかない */

		/* キーワードと、数値が1語以上(2<=words.size())ある */

		if (	this->load_config_sw_
		&&	this->load_config_(words)) {
			continue;
		}
		if (	this->load_image_sw_
		&&	this->load_image_(words)) {
			continue;
		}
		if (	this->load_scan_and_save_sw_
		&&	this->load_scan_and_save_( words
		,scan_num_continue_type_sw)) {
			continue;
		}
		if (	this->load_trace_files_sw_
		&&	this->load_trace_files_(words)) {
			continue;
		}
		if (	this->load_crop_area_and_rot90_sw_
		&&	this->load_crop_area_and_rot90_(words)) {
			continue;
		}
		if (	this->load_pixel_type_and_bright_sw_
		&&	this->load_pixel_type_and_bright_(words)) {
			continue;
		}
		if (	this->load_trace_batch_sw_
		&&	this->load_trace_batch_(words)) {
			continue;
		}
		if (	this->load_number_sw_
		&&	this->load_number_(words)) {
			continue;
		}
		if (	this->load_trace_parameters_sw_
		&&	this->load_trace_parameters_(words)) {
			continue;
		}
		if (	this->load_trace_params_sw_
		&&	this->load_trace_params_(words)) {
			continue;
		}
		/* pri_funct_err_bttvr(
			"Warning : ignore '%s' at line %d"
			,str.c_str() ,ii ); */
	}
}

bool memory_config::load_config_( std::vector< std::string >& words )
{
	if (words.size() != 2) {
		return false;
	}

	if      (
	   (this->str_config_dir_path_ == words.at(0))
	|| (this->str_config_dir_path_legacy2016_ == words.at(0))) {
 cl_gts_master.cl_config.set_dir_path( words.at(1) );
	}
	else if (
	   (this->str_config_open_file_name_ == words.at(0))
	|| (this->str_config_open_file_name_legacy2016_ == words.at(0))) {
 cl_gts_master.cl_config.set_open_file_name( words.at(1) );
	}
	else if (
	   (this->str_config_save_file_name_ == words.at(0))
	|| (this->str_config_save_file_name_legacy2016_ == words.at(0))) {
 cl_gts_master.cl_config.set_save_file_name( words.at(1) );
	}
	else {
		return false; // not defined
	}

	return true;
}

bool memory_config::load_image_( std::vector< std::string >& words )
{
	if (words.size() != 2) {
		return false;
	}

	if( this->str_image_dir_path_ == words.at(0) ) {
 cl_gts_master.cl_image.set_dir_path( words.at(1) );
	}
	else if (
	    this->str_image_open_file_name_ == words.at(0) ) {
 cl_gts_master.cl_image.set_open_file_name( words.at(1) );
	}
	else if (
	    this->str_image_save_file_name_ == words.at(0) ) {
 cl_gts_master.cl_image.set_save_file_name( words.at(1) );
	}
	else if (
	    this->str_image_open_image_format_ == words.at(0) ) {
 cl_gts_master.cl_image.set_open_image_format( words.at(1) );
	}
	else if (
	    this->str_image_save_image_format_ == words.at(0) ) {
 cl_gts_master.cl_image.set_save_image_format( words.at(1) );
	}
	else {
		return false; // not defined
	}

	return true;
}

bool memory_config::load_scan_and_save_(
	std::vector< std::string >& words
	,bool& scan_num_continue_type_sw
)
{
	if (words.size() != 2) {
		return false;
	}

	const std::string& ke = words.at(0);
	const std::string& va = words.at(1);
	cb_scan_and_save& ss = cl_gts_master.cl_scan_and_save;
	cb_trace_files&   tf = cl_gts_master.cl_trace_files;

	if (	  (this->str_scan_filter_trace_sw_ == ke)
	||	  (this->str_scan_filter_trace_sw_legacy2017_ == ke)
	||	  (this->str_scan_filter_trace_sw_legacy2016_ == ke)
	) {	ss.cb_switch_scan_filter_trace( va == this->str_on_);
	}
	else if ((this->str_scan_filter_erase_dot_noise_sw_ == ke)
	||	 (this->str_scan_filter_erase_dot_noise_sw_legacy2017_==ke)
	||	 (this->str_scan_filter_erase_dot_noise_sw_legacy2016_==ke)
	) {    ss.cb_switch_scan_filter_erase_dot_noise(va==this->str_on_);
	}

	else if (  this->str_scan_save_dir_path_ == ke) {
	   cl_gts_gui.filinp_scan_save_dir_path->value( va.c_str() );
	   cl_gts_gui.filinp_scan_save_dir_path->position( va.size() );
	}
	else if ( (this->str_scan_save_dir_path_legacy2017_ == ke)
	||	  (this->str_scan_save_dir_path_legacy2016_ == ke)
	) {cl_gts_gui.filinp_scan_save_dir_path->value( va.c_str() );
	   cl_gts_gui.filinp_scan_save_dir_path->position( va.size() );
	/* 過去のconfig保存はsave情報が先、open情報は後に保存している */
	/* scan_save情報はscan_save,trace_open,trace_saveをセット */
	  cl_gts_gui.filinp_trace_open_dir_path->value( va.c_str() );
	  cl_gts_gui.filinp_trace_open_dir_path->position( va.size() );
	  cl_gts_gui.filinp_trace_save_dir_path->value( va.c_str() );
	  cl_gts_gui.filinp_trace_save_dir_path->position( va.size() );
	}
	else if (  this->str_scan_save_file_head_ == ke) {
	   cl_gts_gui.strinp_scan_save_file_head->value( va.c_str() );
	}
	else if ( (this->str_scan_save_file_head_legacy2017_ == ke)
	||	  (this->str_scan_save_file_head_legacy2016_ == ke)
	) {cl_gts_gui.strinp_scan_save_file_head->value( va.c_str() );
	/* 過去のconfig保存はsave情報が先、open情報は後に保存している */
	/* scan_save情報はscan_save,trace_open,trace_saveをセット */
	  cl_gts_gui.strinp_trace_open_file_head->value( va.c_str() );
	  cl_gts_gui.strinp_trace_save_file_head->value( va.c_str() );
	}
	else if (  this->str_scan_save_number_format_ == ke ) {
	   cl_gts_gui.output_scan_save_number_format->value( va.c_str() );
	}
	else if (  this->str_scan_save_image_format_ == ke) {
		     ss.cb_choice_save_image_format( va );
	}
	else if ( (this->str_scan_save_image_format_legacy2017_ == ke)
	||	  (this->str_scan_save_image_format_legacy2016_ == ke)
	) {	     ss.cb_choice_save_image_format( va );
	/* 過去のconfig保存はsave情報が先、open情報は後に保存している */
	/* scan_save情報はscan_save,trace_open,trace_saveをセット */
		     tf.cb_choice_open_image_format( va );
		     tf.cb_choice_save_image_format( va );
	}

	else if ( (this->str_scan_num_start_ == ke)
	||	  (this->str_scan_num_start_legacy2016_ == ke)
	) {cl_gts_gui.valinp_scan_num_start->value( std::stod(va) );
	}
	else if ( (this->str_scan_num_end_ == ke)
	||	  (this->str_scan_num_end_legacy2016_ == ke)
	) {cl_gts_gui.valinp_scan_num_end->value( std::stod(va) );
	}
	else if ( (this->str_scan_num_continue_type_ == ke)
	||	  (this->str_scan_num_continue_type_legacy2016_ == ke)
	) {	 ss.cb_choice_and_num_continue_type( va );
			     scan_num_continue_type_sw = true;
	}
	else if ( (this->str_scan_num_endless_direction_ == ke)
	||	  (this->str_scan_num_endless_direction_legacy2016_ == ke)
	) {	     ss.cb_choice_num_endless_direction( va );
	}
	else {
		return false; // not defined
	}
	return true;
}

bool memory_config::load_trace_files_( std::vector< std::string >& words )
{
	if (words.size() != 2) {
		return false;
	}

	const std::string& ke = words.at(0);
	const std::string& va = words.at(1);
	cb_trace_files&   tf = cl_gts_master.cl_trace_files;

	if (	  (this->str_trace_open_dir_path_ == ke)
	||	  (this->str_trace_open_dir_path_legacy2016_== ke)
	) {cl_gts_gui.filinp_trace_open_dir_path->value( va.c_str() );
	   cl_gts_gui.filinp_trace_open_dir_path->position( va.size() );
	}
	else if ( (this->str_trace_open_file_head_ == ke)
	||	  (this->str_trace_open_file_head_legacy2016_ == ke)
	) {cl_gts_gui.strinp_trace_open_file_head->value( va.c_str() );
	}
	else if (  this->str_trace_open_number_format_ == ke ) {
	   cl_gts_gui.strinp_trace_open_number_format->value( va.c_str() );
	}
	else if ( (this->str_trace_open_image_format_ == ke)
	||	  (this->str_trace_open_image_format_legacy2016_ == ke)
	) {	      tf.cb_choice_open_image_format( va );
	}
	else if (  this->str_trace_num_start_ == ke ) {
	   cl_gts_gui.valout_trace_num_start->value( std::stoi(va) );
	}
	else if (  this->str_trace_num_end_ == ke ) {
	   cl_gts_gui.valout_trace_num_end->value( std::stoi(va) );
	}
	/* trace_swはON固定 */
	else if ( this->str_trace_filter_erase_dot_noise_sw_ == ke
	) {    tf.cb_switch_trace_filter_erase_dot_noise(va==this->str_on_);
	}
	else if (  this->str_trace_save_dir_path_ == ke ) {
	   cl_gts_gui.filinp_trace_save_dir_path->value( va.c_str() );
	}
	else if (  this->str_trace_save_file_head_ == ke ) {
	   cl_gts_gui.strinp_trace_save_file_head->value( va.c_str() );
	}
	else if (  this->str_trace_save_number_format_ == ke ) {
	   cl_gts_gui.output_trace_save_number_format->value( va.c_str() );
	}
	else if (  this->str_trace_save_image_format_ == ke ) {
		      tf.cb_choice_save_image_format( va );
	}
	else {
		return false; // not defined
	}
	return true;
}

bool memory_config::load_crop_area_and_rot90_( std::vector< std::string >& words )
{
	if (words.size() != 2) {
		return false;
	}

	const std::string& ke = words.at(0);
	const std::string& va = words.at(1);

	if ( this->str_area_select_ == ke) {
		const Fl_Menu_Item *crnt =
			cl_gts_gui.choice_area_selecter->find_item(
				va.c_str() );
		if (crnt != nullptr) {
			cl_gts_gui.choice_area_selecter->value(crnt);
			cl_gts_master.cl_area_and_rot90.cb_area_selecter();
		}
	}
	else if ((this->str_area_offset_cm_x_		 == ke)
	||	 (this->str_area_offset_cm_x_legacy2017_ == ke)
	) {
	  cl_gts_gui.valinp_area_offset_cm_x->value( std::stod(va) );
	}
	else if ((this->str_area_offset_cm_y_		 == ke)
	||	 (this->str_area_offset_cm_y_legacy2017_ == ke)
	) {
	  cl_gts_gui.valinp_area_offset_cm_y->value( std::stod(va) );
	}
	else if ( this->str_area_aspect_ratio_select_ == ke) {
		const Fl_Menu_Item *crnt =
	       cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(
			va.c_str() );
		if (crnt != 0) {
	cl_gts_gui.choice_area_aspect_ratio_selecter->value(crnt);
	cl_gts_master.cl_area_and_rot90.cb_area_aspect_ratio_selecter();
		}
	}
	else if ((this->str_area_size_cm_w_		== ke)
	||	 (this->str_area_size_cm_w_legacy2017_  == ke)
	) {
	  cl_gts_gui.valinp_area_size_cm_w->value( std::stod(va) );
	}
	else if ((this->str_area_size_cm_h_		== ke)
	||	 (this->str_area_size_cm_h_legacy2017_  == ke)
	) {
	  cl_gts_gui.valinp_area_size_cm_h->value( std::stod(va) );
	}
	else if ((this->str_area_size_pixel_w_		  == ke)
	||	 (this->str_area_size_pixel_w_legacy2017_ == ke)
	) {
	  cl_gts_gui.valinp_area_size_pixel_w->value( std::stod(va) );
	}
	else if ((this->str_area_size_pixel_h_		  == ke)
	||	 (this->str_area_size_pixel_h_legacy2017_ == ke)
	) {
	  cl_gts_gui.valinp_area_size_pixel_h->value( std::stod(va) );
	}
	else if ( this->str_area_resolution_dpi_ ==  ke) {
	  cl_gts_gui.valinp_area_reso->value( std::stod(va) );
	}
	else if ( this->str_area_aspect_ratio_w_ ==  ke) {
	  cl_gts_gui.valinp_area_aspect_ratio_w->value( std::stod(va) );
	}
	else if ( this->str_area_aspect_ratio_h_ ==  ke) {
	  cl_gts_gui.valinp_area_aspect_ratio_h->value( std::stod(va) );
	}
	else if ( this->str_area_aspect_ratio_how_to_fix_ ==  ke) {
	  if (va == "W") {
	   cl_gts_gui.radbut_area_aspect_ratio_w->value(1);
	   cl_gts_gui.radbut_area_aspect_ratio_h->value(0);
	  } else
	  if (va == "H") {
	   cl_gts_gui.radbut_area_aspect_ratio_w->value(0);
	   cl_gts_gui.radbut_area_aspect_ratio_h->value(1);
	  }
	}
	else if ( (this->str_area_rotate_per_90_	    == ke)
	||	  (this->str_area_rotate_per_90_legacy2017_ == ke)
	) {
			set_rotate_per_90_( va );
	}

	//---------- scanner info. ----------

	/* スキャナー情報
			this->str_scanner_type_
			cl_gts_gui.txtout_scanner_type
			this->str_scanner_size_cm_w_
			cl_gts_gui.valout_scanner_size_cm_w
			this->str_scanner_size_cm_h_
			cl_gts_gui.valout_scanner_size_cm_h
		はTWAINドライバーから取るべきなので、
		ファイルからは設定しない
	*/
	else {
		return false; // not defined
	}
	return true;
}

bool memory_config::load_pixel_type_and_bright_(std::vector< std::string >& words)
{
	if (words.size() != 2) {
		return false;
	}

	const std::string& ke = words.at(0);
	const std::string& va = words.at(1);

	if ( ke == this->str_pixel_type_ ) {
		set_pixel_type_( va );
	}
	else if ( ke == this->str_bw_threshold_ ) {
		cl_gts_gui.valinp_bw_threshold->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_bw_threshold)->value( std::stod(va) );
	}
	else if ( ke == this->str_grayscale_brightness_ ) {
		cl_gts_gui.valinp_grayscale_brightness->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_grayscale_brightness)->value( std::stod(va) );
	}
	else if ( ke == this->str_grayscale_contrast_ ) {
		cl_gts_gui.valinp_grayscale_contrast->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_grayscale_contrast)->value( std::stod(va) );
	}
	else if ( ke == this->str_grayscale_gamma_ ) {
		cl_gts_gui.valinp_grayscale_gamma->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_grayscale_gamma)->value( std::stod(va) );
	}
	else if ( ke == this->str_rgb_brightness_ ) {
		cl_gts_gui.valinp_rgb_brightness->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_rgb_brightness)->value( std::stod(va) );
	}
	else if ( ke == this->str_rgb_contrast_ ) {
		cl_gts_gui.valinp_rgb_contrast->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_rgb_contrast)->value( std::stod(va) );
	}
	else if ( ke == this->str_rgb_gamma_ ) {
		cl_gts_gui.valinp_rgb_gamma->value( std::stod(va) );
((Fl_Valuator *)cl_gts_gui.scrbar_rgb_gamma)->value( std::stod(va) );
	}
	else {
		return false; // not defined
	}
	return true;
}

bool memory_config::load_trace_batch_(
	std::vector< std::string >& words
)
{
	if (words.size() != 2) {
		return false; // not find
	}

	const std::string& ke = words.at(0);
	const std::string& va = words.at(1);

	if (this->str_trace_batch_dir_ == ke) {
		cl_gts_master.cl_trace_batch.set_dir_path( va );
	}
	else if (this->str_trace_batch_list_ == ke) {
		/* リストの最後に追加する */
		cl_gts_gui.selbro_trace_batch_config_list->insert(
		 cl_gts_gui.selbro_trace_batch_config_list->size()+1,
		 va.c_str()
		);
	}
	else {
		return false; // not find
	}
	return true; // find
}

bool memory_config::load_number_(
	std::vector< std::string >& words
)
{
	if ( words.size() < 2 || 4 < words.size() ) {
		return false;
	}

	if ( words.at(0) == this->str_file_number_frame_ ) {
		/* 実際の画像ファイルの有無を調べて
		リストの最後に追加する */
		// use C++11,throw exception then error
		const int num = std::stoi(words.at(1));
		cl_gts_master.cl_number.append_without_S(num);

		/* 選択状態の再現 */
		if (
		 (	(2<words.size())
		 	&&(words.at(2) == this->str_file_number_selected_)
		 )
	 	||
		 (	(3<words.size())
			&&(words.at(3) == this->str_file_number_selected_)
		 )
		) {
			cl_gts_gui.selbro_number_list->select(
			cl_gts_gui.selbro_number_list->size());
		}
	}
	else if ( this->str_number_action_type_ == words.at(0) ) {
	  cl_gts_gui.output_number_action_type->value(words.at(1).c_str());
	}
	else {
		return false; // not defined
	}
	return true;
}

bool memory_config::load_trace_parameters_( std::vector< std::string >& words )
{
	/* 4項目のparameter */
	if (words.size() == 4) {
	 if (		this->str_color_trace_01_tgt_rgb_ == words.at(0)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_01 , std::stoi(words.at(1))
			, std::stoi(words.at(2)) , std::stoi(words.at(3))
		);
		cl_gts_gui.button_color_trace_01_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_01_tgt_rgb->redraw();
	 }
	 else if (	this->str_color_trace_02_tgt_rgb_ == words.at(0)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_02 , std::stoi(words.at(1))
			, std::stoi(words.at(2)) , std::stoi(words.at(3))
		);
		cl_gts_gui.button_color_trace_02_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_02_tgt_rgb->redraw();
	 }
	 else if (	this->str_color_trace_03_tgt_rgb_ == words.at(0)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_03 , std::stoi(words.at(1))
			, std::stoi(words.at(2)) , std::stoi(words.at(3))
		);
		cl_gts_gui.button_color_trace_03_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_03_tgt_rgb->redraw();
	 }
	 else if (	this->str_color_trace_04_tgt_rgb_ == words.at(0)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_04 , std::stoi(words.at(1))
			, std::stoi(words.at(2)) , std::stoi(words.at(3))
		);
		cl_gts_gui.button_color_trace_04_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_04_tgt_rgb->redraw();
	 }
	 else if (	this->str_color_trace_05_tgt_rgb_ == words.at(0)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_05 , std::stoi(words.at(1))
			, std::stoi(words.at(2)) , std::stoi(words.at(3))
		);
		cl_gts_gui.button_color_trace_05_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_05_tgt_rgb->redraw();
	 }
	 else if (	this->str_color_trace_06_tgt_rgb_ == words.at(0)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_06 , std::stoi(words.at(1))
			, std::stoi(words.at(2)) , std::stoi(words.at(3))
		);
		cl_gts_gui.button_color_trace_06_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_06_tgt_rgb->redraw();
	 }
	 else {
		return false; // not defined
	 }
	 return true;
	}

	/* ここ以後は2項目のparameterのみ見る */
	if (words.size() != 2) {
		return false; // not defined
	}

	//---------- 1/6 ----------

	if (		this->str_color_trace_01_chk_==words.at(0)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_01_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_01_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_01_chk->value()) {
		 cl_gts_gui.group_color_trace_01grp->activate();
		   cl_gts_gui.group_thickness_01grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_01grp->deactivate();
		   cl_gts_gui.group_thickness_01grp->deactivate();
		}
	}
	else if (	this->str_color_trace_01_src_hh_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_min)->value( val );
	}
	else if (	this->str_color_trace_01_src_hh_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_max)->value( val );
	}
	else if (	this->str_color_trace_01_src_aa_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_01);
	}
	else if (	this->str_color_trace_01_src_aa_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_max)->value( val );
	}
	else if (	this->str_color_trace_01_src_bb_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_min)->value( val );
	}
	else if (	this->str_color_trace_01_src_bb_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_01);
	}
	else if (	this->str_color_trace_01_tgt_color_==words.at(0)){
		  cl_gts_gui.roubut_thickness_01_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 2/6 ----------

	else if (	this->str_color_trace_02_chk_==words.at(0)){
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_02_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_02_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_02_chk->value()) {
		 cl_gts_gui.group_color_trace_02grp->activate();
		   cl_gts_gui.group_thickness_02grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_02grp->deactivate();
		   cl_gts_gui.group_thickness_02grp->deactivate();
		}
	}
	else if (	this->str_color_trace_02_src_hh_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_min)->value( val );
	}
	else if (	this->str_color_trace_02_src_hh_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_max)->value( val );
	}
	else if (	this->str_color_trace_02_src_aa_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_02);
	}
	else if (	this->str_color_trace_02_src_aa_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_max)->value( val );
	}
	else if (	this->str_color_trace_02_src_bb_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_min)->value( val );
	}
	else if (	this->str_color_trace_02_src_bb_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_02);
	}
	else if (	this->str_color_trace_02_tgt_color_==words.at(0)){
		  cl_gts_gui.roubut_thickness_02_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 3/6 ----------

	else if (	this->str_color_trace_03_chk_==words.at(0)){
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_03_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_03_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_03_chk->value()) {
		 cl_gts_gui.group_color_trace_03grp->activate();
		   cl_gts_gui.group_thickness_03grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_03grp->deactivate();
		   cl_gts_gui.group_thickness_03grp->deactivate();
		}
	}
	else if (	this->str_color_trace_03_src_hh_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_min)->value( val );
	}
	else if (	this->str_color_trace_03_src_hh_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_max)->value( val );
	}
	else if (	this->str_color_trace_03_src_aa_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_03);
	}
	else if (	this->str_color_trace_03_src_aa_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_max)->value( val );
	}
	else if (	this->str_color_trace_03_src_bb_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_min)->value( val );
	}
	else if (	this->str_color_trace_03_src_bb_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_03);
	}
	else if (	this->str_color_trace_03_tgt_color_==words.at(0)){
		  cl_gts_gui.roubut_thickness_03_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 4/6 ----------

	else if (	this->str_color_trace_04_chk_==words.at(0)){
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_04_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_04_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_04_chk->value()) {
		 cl_gts_gui.group_color_trace_04grp->activate();
		   cl_gts_gui.group_thickness_04grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_04grp->deactivate();
		   cl_gts_gui.group_thickness_04grp->deactivate();
		}
	}
	else if (	this->str_color_trace_04_src_hh_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_min)->value( val );
	}
	else if (	this->str_color_trace_04_src_hh_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_max)->value( val );
	}
	else if (	this->str_color_trace_04_src_aa_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_04);
	}
	else if (	this->str_color_trace_04_src_aa_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_max)->value( val );
	}
	else if (	this->str_color_trace_04_src_bb_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_min)->value( val );
	}
	else if (	this->str_color_trace_04_src_bb_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_04);
	}
	else if (	this->str_color_trace_04_tgt_color_==words.at(0)){
		  cl_gts_gui.roubut_thickness_04_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 5/6 ----------

	else if (	this->str_color_trace_05_chk_==words.at(0)){
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_05_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_05_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_05_chk->value()) {
		 cl_gts_gui.group_color_trace_05grp->activate();
		   cl_gts_gui.group_thickness_05grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_05grp->deactivate();
		   cl_gts_gui.group_thickness_05grp->deactivate();
		}
	}
	else if (	this->str_color_trace_05_src_hh_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_min)->value( val );
	}
	else if (	this->str_color_trace_05_src_hh_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_max)->value( val );
	}
	else if (	this->str_color_trace_05_src_aa_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_05);
	}
	else if (	this->str_color_trace_05_src_aa_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_max)->value( val );
	}
	else if (	this->str_color_trace_05_src_bb_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_min)->value( val );
	}
	else if (	this->str_color_trace_05_src_bb_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_05);
	}
	else if (	this->str_color_trace_05_tgt_color_==words.at(0)){
		  cl_gts_gui.roubut_thickness_05_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 6/6 ----------

	else if (	this->str_color_trace_06_chk_==words.at(0)){
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_06_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_06_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_06_chk->value()) {
		 cl_gts_gui.group_color_trace_06grp->activate();
		   cl_gts_gui.group_thickness_06grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_06grp->deactivate();
		   cl_gts_gui.group_thickness_06grp->deactivate();
		}
	}
	else if (	this->str_color_trace_06_src_hh_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_min)->value( val );
	}
	else if (	this->str_color_trace_06_src_hh_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_max)->value( val );
	}
	else if (	this->str_color_trace_06_src_aa_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_06);
	}
	else if (	this->str_color_trace_06_src_aa_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_max)->value( val );
	}
	else if (	this->str_color_trace_06_src_bb_min_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_min)->value( val );
	}
	else if (	this->str_color_trace_06_src_bb_max_==words.at(0)){
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_06);
	}
	else if (	this->str_color_trace_06_tgt_color_==words.at(0)){
		  cl_gts_gui.roubut_thickness_06_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}
	else {
		return false; // not defined
	}
	return true;
}
bool memory_config::load_trace_params_( std::vector< std::string >& words )
{
	if (words.size() == 2) {
	 if (words.at(0) == this->str_trace_display_main_sw_) {
		const int sw_num = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chebut_trace_display_main_sw->value( sw_num );
	 } else {
		return false; // not defined
	 }
	} else if ((words.size() == 4) || (words.size() == 6)) {
	 if (words.at(0) == this->str_trace_params_title_) {
	  const int num = std::stoi(words.at(1));
	  std::vector<cb_trace_params::widget_set>& vwset(
		cl_gts_master.cl_trace_params.widget_sets
	  );
	  if (num < 0 || static_cast<int>(vwset.size()) <= num) {
		return false; // bad number
	  }

	  cb_trace_params::widget_set& wset( vwset.at(num) );

	  if        (words.at(2) == this->str_trace_enable_sw_) {
		const int sw_num = (words.at(3) == this->str_on_) ?1 :0;
		wset.chebut_enable_sw->value(sw_num);
		if (sw_num == 1){ wset.group_trace->activate(); }
		else		{ wset.group_trace->deactivate(); }
	  } else if (words.at(2) == this->str_trace_target_rgb_) {
		if (words.size() != 6) {
			return false; // bad word's count
		}
		const uchar r = static_cast<uchar>(std::stoi(words.at(3)));
		const uchar g = static_cast<uchar>(std::stoi(words.at(4)));
		const uchar b = static_cast<uchar>(std::stoi(words.at(5)));
		cl_gts_master.cl_trace_params.set_target_rgb( num ,r,g,b );
		wset.button_target_rgb->redraw();
	  } else if (words.at(2) == this->str_trace_thickness_) {
		const double va = std::stod(words.at(3));
		wset.valinp_thickness->value(va);
		wset.roller_thickness->value(va);
	  } else if (words.at(2) == this->str_trace_hue_min_) {
		const double va = std::stod(words.at(3));
		wset.valinp_hue_min->value(va);
	  } else if (words.at(2) == this->str_trace_hue_max_) {
		const double va = std::stod(words.at(3));
		wset.valinp_hue_max->value(va);
	  } else if (words.at(2) == this->str_trace_slope_deg_) {
		const double va = std::stod(words.at(3));
		wset.valinp_slope_deg->value(va);
	  } else if (words.at(2) == this->str_trace_intercept_) {
		const double va = std::stod(words.at(3));
		wset.valinp_intercept->value(va);
	  } else if (words.at(2) == this->str_trace_display_sw_) {
		const int sw_num = (words.at(3) == this->str_on_) ?1 :0;
		wset.chebut_display_sw->value(sw_num);
	  } else {
		return false; // not defined
	  }
	 } else {
		return false; // not defined
	 }
	} else {
		return false; // not defined
	}
	return true;
}

int memory_config::load_only_trace_parameters( const std::string& file_path)
{
	this->load_config_sw_ = false;
	this->load_image_sw_ = false;
	this->load_scan_and_save_sw_ = false;
	this->load_trace_files_sw_ = false;
	this->load_crop_area_and_rot90_sw_ = false;
	this->load_pixel_type_and_bright_sw_ = false;
	this->load_trace_parameters_sw_ = true;	// <---------
	this->load_trace_params_sw_ = false;
	this->load_trace_batch_sw_ = false;
	this->load_number_sw_ = false;

	const int ret = this->load(file_path , this->load_trace_batch_sw_);

	this->load_config_sw_ = true;
	this->load_image_sw_ = true;
	this->load_scan_and_save_sw_ = true;
	this->load_trace_files_sw_ = true;
	this->load_crop_area_and_rot90_sw_ = true;
	this->load_pixel_type_and_bright_sw_ = true;
	this->load_trace_parameters_sw_ = true;
	this->load_trace_params_sw_ = true;
	this->load_trace_batch_sw_ = true;
	this->load_number_sw_ = true;
	return ret;
}
int memory_config::load_only_area_and_rot90( const std::string& file_path)
{
	this->load_config_sw_ = false;
	this->load_image_sw_ = false;
	this->load_scan_and_save_sw_ = false;
	this->load_trace_files_sw_ = false;
	this->load_crop_area_and_rot90_sw_ = true; // <---------
	this->load_pixel_type_and_bright_sw_ = false;
	this->load_trace_parameters_sw_ = false;
	this->load_trace_params_sw_ = false;
	this->load_trace_batch_sw_ = false;
	this->load_number_sw_ = false;

	const int ret = this->load(file_path , this->load_trace_batch_sw_);

	this->load_config_sw_ = true;
	this->load_image_sw_ = true;
	this->load_scan_and_save_sw_ = true;
	this->load_trace_files_sw_ = true;
	this->load_crop_area_and_rot90_sw_ = true;
	this->load_pixel_type_and_bright_sw_ = true;
	this->load_trace_parameters_sw_ = true;
	this->load_trace_params_sw_ = true;
	this->load_trace_batch_sw_ = true;
	this->load_number_sw_ = true;
	return ret;
}
int memory_config::load_only_pixel_type_and_bright( const std::string& file_path)
{
	this->load_config_sw_ = false;
	this->load_image_sw_ = false;
	this->load_scan_and_save_sw_ = false;
	this->load_trace_files_sw_ = false;
	this->load_crop_area_and_rot90_sw_ = false;
	this->load_pixel_type_and_bright_sw_ = true; // <----------
	this->load_trace_parameters_sw_ = false;
	this->load_trace_params_sw_ = false;
	this->load_trace_batch_sw_ = false;
	this->load_number_sw_ = false;

	const int ret = this->load(file_path , this->load_trace_batch_sw_);

	this->load_config_sw_ = true;
	this->load_image_sw_ = true;
	this->load_scan_and_save_sw_ = true;
	this->load_trace_files_sw_ = true;
	this->load_crop_area_and_rot90_sw_ = true;
	this->load_pixel_type_and_bright_sw_ = true;
	this->load_trace_parameters_sw_ = true;
	this->load_trace_params_sw_ = true;
	this->load_trace_batch_sw_ = true;
	this->load_number_sw_ = true;
	return ret;
}
int memory_config::load_only_trace_params( const std::string& file_path)
{
	this->load_config_sw_ = false;
	this->load_image_sw_ = false;
	this->load_scan_and_save_sw_ = false;
	this->load_trace_files_sw_ = false;
	this->load_crop_area_and_rot90_sw_ = false;
	this->load_pixel_type_and_bright_sw_ = false;
	this->load_trace_parameters_sw_ = false;
	this->load_trace_params_sw_ = true;	// <---------
	this->load_trace_batch_sw_ = false;
	this->load_number_sw_ = false;

	const int ret = this->load(file_path , this->load_trace_batch_sw_);

	this->load_config_sw_ = true;
	this->load_image_sw_ = true;
	this->load_scan_and_save_sw_ = true;
	this->load_trace_files_sw_ = true;
	this->load_crop_area_and_rot90_sw_ = true;
	this->load_pixel_type_and_bright_sw_ = true;
	this->load_trace_parameters_sw_ = true;
	this->load_trace_params_sw_ = true;
	this->load_trace_batch_sw_ = true;
	this->load_number_sw_ = true;
	return ret;
}

int memory_config::load( const std::string& file_path ,const bool load_trace_batch_sw )
{
 try { /* ファイル読込と伴う設定でのエラーを例外処理で行う */
	bool scan_num_continue_type_sw = false;

	//---------- read file ----------
  {
#if defined _WIN32
	std::ifstream ifs( ptbl_charcode_cp932_from_utf8(
			   file_path.c_str()
	));/* ファイル開く */
#else
	std::ifstream ifs( file_path );/* ファイル開く */
#endif
	ifs.exceptions(std::ios_base::failbit);/* エラー時例外送出設定 */
   try {	/* std::getline()はEOFの場合も例外を投げてしまう */
	this->load_trace_batch_sw_ =  load_trace_batch_sw;
	this->load_ifs_( ifs , scan_num_continue_type_sw ); /* 読む */
   }
   catch ( std::fstream::failure& ) {
	if ( std::ios_base::eofbit == false ) {
		throw; /* EOF以外の例外はエラーなので再び投げる */
	}
   }
	ifs.close(); /* ファイル閉じる */
  }

	//---------- after reading ----------

	/* "Thickness"ウインドウ各値を"Color Trace Enhancement"で再表示 */
	cl_gts_master.cl_color_trace_thickness.cb_enh_01();
	cl_gts_master.cl_color_trace_thickness.cb_enh_02();
	cl_gts_master.cl_color_trace_thickness.cb_enh_03();
	cl_gts_master.cl_color_trace_thickness.cb_enh_04();
	cl_gts_master.cl_color_trace_thickness.cb_enh_05();
	cl_gts_master.cl_color_trace_thickness.cb_enh_06();

	/* Scan and SaveのEnd/Endless指定がない時はStart...End指定にする */
	if (!scan_num_continue_type_sw && this->load_scan_and_save_sw_) {
	 cl_gts_master.cl_scan_and_save.cb_choice_and_num_continue_type(
	 	"End" );
	}

	if (	cl_gts_master.cl_number.is_scan()) {
		/* Numberウインドウに保存するFileHead名をセット */
		cl_gts_gui.output_number_file_head_name->value(
		 cl_gts_gui.strinp_scan_save_file_head->value()
		);

		/* NumberウインドウのActionTypeセット
		Scan/TraceウインドウのBGのセット */
		cl_gts_master.cl_number.set_type_to_scan();

		/* ファイル存在確認して'S'マーク表示 */
		cl_gts_master.cl_scan_and_save.check_existing_saved_file();
	} else
	if (	cl_gts_master.cl_number.is_trace()) {
		/* Numberウインドウに保存するFileHead名をセット */
		cl_gts_gui.output_number_file_head_name->value(
		 cl_gts_gui.strinp_trace_save_file_head->value()
		);

		/* NumberウインドウのActionTypeセット
		Scan/TraceウインドウのBGのセット */
		cl_gts_master.cl_number.set_type_to_trace();

		/* ファイル存在確認して'S'マーク表示 */
		cl_gts_master.cl_trace_files.check_existing_saved_file();
	}

	/* 画面は空白表示する指定(データは残っている) */
	cl_gts_master.cl_ogl_view.no_view_canvas();

	/* 画面クリア設定 */
	cl_gts_master.cl_ogl_view.clear_opengl(
		cl_gts_gui.image_view->w(),
		cl_gts_gui.image_view->h()
	);
	/* 画面クリア */
	cl_gts_gui.image_view->flush();

	/* 画像読込表示 */
	cl_gts_master.cb_number_read_and_trace_and_preview();
 }
 catch (const std::ios_base::failure& e) {
	std::ostringstream ost;
	ost	<< "Error(ios_base::failure) in loading \""
		<< file_path << "\","
		<< e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
 catch (std::exception& e) {
	std::ostringstream ost;
	ost	<< "Error(exception) in loading \""
		<< file_path << "\","
		<< e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
 catch (...) {
	std::ostringstream ost;
	ost << "Error(other) in loading.";/* ユーザーに知らせる */
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return NG;
 }
	return OK;
}
