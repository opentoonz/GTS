//#include <iostream>
#include <string>
#include <cstring>
#include <FL/Fl.H>
//#include "enumerations.h"
#include "gts_gui.h"
//#include "gts_master.h"
#include "memory_short_cut_key.h"

namespace {
 /* keyがspaceキーならtrueを返し、それ以外はfalseを返す */
 bool get_key_code_( const char *key ,int&code ) {
	if (!strcmp( "Space" ,key )) { code = ' '; return true; } else
	if (!strcmp( "Enter" ,key )) { code = FL_Enter; } else
	if (!strcmp( "Esc"   ,key )) { code = FL_Escape; } else
				     { code = 0; }
	return false;
 }
}
memory_short_cut_key::memory_short_cut_key()
	:start_scan_code_(0)
	,rescan_code_(0)
	,next_scan_code_(0)
	,stop_scan_code_(0)
	,focus_number_(f_n_nothing_)
{
}
//--------------------------------------------------------------------
void	  memory_short_cut_key::setup_start_scan( const char *key ) {
	get_key_code_( key ,this->start_scan_code_ );
}
void	  memory_short_cut_key::setup_rescan( const char *key ) {
				this->rescan_label_key_ = key;
	if (get_key_code_( key ,this->rescan_code_ )) {
      this->focus_number_ = this->f_n_rescan_;
	}
}
void	  memory_short_cut_key::setup_next_scan( const char *key ) {
				this->next_scan_label_key_ = key;
	if (get_key_code_( key ,this->next_scan_code_ )) {
      this->focus_number_ = this->f_n_next_scan_;
	}
}
void	  memory_short_cut_key::setup_stop_scan( const char *key ) {
				this->stop_scan_label_key_ = key;
	if (get_key_code_( key ,this->stop_scan_code_ )) {
      this->focus_number_ = this->f_n_stop_scan_;
	}
}
//--------------------------------------------------------------------
void memory_short_cut_key::set_shortcut( void ) {
	if (this->start_scan_code_ != 0) {
	 cl_gts_gui.menite_scan_save->shortcut(this->start_scan_code_ );
	}
	if (		this->rescan_code_ != 0) {
	    cl_gts_gui.button_rescan->shortcut(
			this->rescan_code_ );
	}

	if (!	this->rescan_label_key_.empty()) {
		this->rescan_label_all_ =
    cl_gts_gui.button_rescan->label();
		this->rescan_label_all_ += '(';
		this->rescan_label_all_ +=
		this->rescan_label_key_;
		this->rescan_label_all_ += ')';
    cl_gts_gui.button_rescan->label(
		this->rescan_label_all_.c_str() );
	}

	if (		this->next_scan_code_ != 0) {
	    cl_gts_gui.button_next_scan->shortcut(
			this->next_scan_code_ );
	}

	if (!	this->next_scan_label_key_.empty()) {
		this->next_scan_label_all_ =
    cl_gts_gui.button_next_scan->label();
		this->next_scan_label_all_ += '(';
		this->next_scan_label_all_ +=
		this->next_scan_label_key_;
		this->next_scan_label_all_ += ')';
    cl_gts_gui.button_next_scan->label( 
		this->next_scan_label_all_.c_str() );
	}

	if (		this->stop_scan_code_ != 0) {
	    cl_gts_gui.button_stop_scan->shortcut(
			this->stop_scan_code_ );
	}

	if (!	this->stop_scan_label_key_.empty()) {
		this->stop_scan_label_all_ =
    cl_gts_gui.button_stop_scan->label();
		this->stop_scan_label_all_ += '(';
		this->stop_scan_label_all_ +=
		this->stop_scan_label_key_;
		this->stop_scan_label_all_ += ')';
    cl_gts_gui.button_stop_scan->label( 
		this->stop_scan_label_all_.c_str() );
	}
}
void memory_short_cut_key::set_space_key_focus_in_next_scan( void ) {
    if(this->focus_number_ == this->f_n_rescan_) {
        Fl::focus( cl_gts_gui.button_rescan );
    } else if(this->focus_number_ == this->f_n_next_scan_) {
        Fl::focus( cl_gts_gui.button_next_scan );
    } else if(this->focus_number_ == this->f_n_stop_scan_) {
        Fl::focus( cl_gts_gui.button_stop_scan );
    }
}
