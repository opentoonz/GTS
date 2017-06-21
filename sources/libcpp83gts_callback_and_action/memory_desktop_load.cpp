#include <stdio.h>
#include <string.h>
#include <string>	// std::stoi() C++11
#include <fstream>
#include <cerrno>
#include "pri.h"
#include "ptbl_returncode.h"
#include "ptbl_funct.h" // ptbl_getenv(-)
#include "memory_desktop.h"
#include "gts_gui.h"
#include "gts_master.h"
#include "igs_lex_white_space_and_double_quote.h"

int memory_desktop::set_desktop_file_path_( void ) {
	int ret = OK;

	/* 初回実行時のみuser_homeを設定する */
	if (this->user_home_.empty()) {
		ptbl_get_user_home(this->user_home_);
		if (this->user_home_.empty()) {
			ret = NG;
		}
	}

	/* 初回実行時のみfile_pathを設定する */
	if (this->desktop_file_path_.empty()) {
		/* 場所はホームディレクトリ固定 */
		this->desktop_file_path_ = this->user_home_;
		this->desktop_file_path_ += ptbl_get_cp_path_separeter();
#ifndef _WIN32
		this->desktop_file_path_ +=
			this->get_install_and_scan_area_and_desktop_dir();
		this->desktop_file_path_ += ptbl_get_cp_path_separeter();
		if (!ptbl_dir_or_file_is_exist(
			const_cast<char *>(this->desktop_file_path_.c_str())
		)) {
			ptbl_mkdir(this->desktop_file_path_.c_str());
		}
#endif
		this->desktop_file_path_ += this->str_desktop_filename2_;
	}

	return ret;
}
int memory_desktop::load( void ) {
	/* dirパスとfileパスをセットしとく */
	if (this->set_desktop_file_path_() != OK) {
		pri_funct_err_bttvr(
		 "set_desktop_file_path_(-) can not set dir");
		return NG;
	}

	/* 古いfileパスを得る */
	std::string old_path;
	old_path = this->user_home_;
	old_path += ptbl_get_cp_path_separeter();
	old_path += this->str_desktop_filename_;

	/* 古いfileパスでファイルあるならそちらを優先-->保存は標準パス */
	bool old_type_sw = false;

#if defined _WIN32
	char* path = ptbl_charcode_cp932_from_utf8( old_path.c_str() );
	std::ifstream ifs( path );
	free(path);
#else
	std::ifstream ifs( old_path );
#endif
	if (!ifs) {
		/* 古いファイルはない、ので標準ファイル名で探す */
		ifs.close();
		ifs.open( this->desktop_file_path_.c_str() );
		if (!ifs) { /* 最初はファイルがなくてもエラーではない */
			return OK;
		}
	} else {
		/* 古いファイルがある */
		old_type_sw = true;
	}
 
	for (int ii = 1 ;ifs ;++ii) {
		char buf[1000];
		buf[0] = '\0';
		ifs.getline(buf,1000);
		if ('#' == buf[0]) { continue; }
		if ('\0' == buf[0]) { continue; }

		std::vector< std::string > words;
		igs::lex::white_space_and_double_quote(buf,words);

		const int ret = words.size();
		std::string key;
		std::string di;
		int xx=200,yy=200,ww=200,hh=200;
		if (1 <= ret) { key = words.at(0); }
		if (2 <= ret) { di = words.at(1); }
		if (3 <= ret) { xx = std::stoi(words.at(2)); }
		if (4 <= ret) { yy = std::stoi(words.at(3)); }
		if (5 <= ret) { ww = std::stoi(words.at(4)); }
		if (6 <= ret) { hh = std::stoi(words.at(5)); }

		if ((this->str_config_dir_ == key) && (2 == ret)) {
			cl_gts_master.cl_config.set_dir_path(
				di.c_str() );
		}
		else if ((this->str_window_main_==key) && (6==ret)) {
		cl_gts_gui.window_main_view->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_next_scan_==key) && (4==ret)) {
			if (di == "show") {
		////cl_gts_gui.menite_next_scan->set();
		//cl_gts_gui.window_main_view->show();/* Need for Minimize */
		//cl_gts_gui.window_next_scan->show();
			}
		cl_gts_gui.window_next_scan->position(xx,yy);
		}
		else if ((this->str_window_area_and_rot90==key)
		&&(4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_area_and_rot90->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_area_and_rot90->show();
			}
		cl_gts_gui.window_area_and_rot90->position(xx,yy);
		}
		else if ((this->str_window_pixel_type_and_bright_==key)
		&& ((4==ret) || (6==ret)/* for old format */)) {
		cl_gts_gui.window_pixel_type_and_bright->resize( xx ,yy ,ww
		,cl_gts_gui.window_pixel_type_and_bright->h()  );
			if (di == "show") {
		cl_gts_gui.menite_pixel_type_and_bright->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_pixel_type_and_bright->show();
			}
		}
		else if ((this->str_window_scan_and_save_==key)
		&& ((4==ret) || (6==ret)/* for old format */)) {
		cl_gts_gui.window_scan_and_save->resize( xx ,yy ,ww
		,cl_gts_gui.window_scan_and_save->h()  );
			if (di == "show") {
		cl_gts_gui.menite_scan_and_save->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_scan_and_save->show();
			}
		}
		else if ((this->str_window_trace_files_==key)
		&& ((4==ret) || (6==ret)/* for old format */)) {
		cl_gts_gui.window_trace_files->resize( xx ,yy ,ww
		,cl_gts_gui.window_trace_files->h()  );
			if (di == "show") {
		cl_gts_gui.menite_trace_files->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_trace_files->show();
			}
		}
		else if ((this->str_window_number_==key)
		&& (6==ret)) {
		cl_gts_gui.window_number->resize( xx ,yy ,ww ,hh );
			if (di == "show") {
		cl_gts_gui.menite_number->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_number->show();
			}
		}
		else if ((this->str_window_trace_parameters_==key)
		&& (4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_trace_parameters->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_trace_parameters->show();
			}
		cl_gts_gui.window_trace_parameters->position(xx,yy);
		}
		else if ((this->str_window_trace_batch_==key)
		&& (6==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_trace_batch->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_trace_batch->show();
			}
		cl_gts_gui.window_trace_batch->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_trace_thickness_==key)
		&& (6==ret)) {
		cl_gts_gui.window_trace_thickness->resize( xx ,yy ,ww
		//,cl_gts_gui.window_trace_thickness->h()
		,hh
		);
		cl_gts_gui.group_trace_thickness->size(
		cl_gts_gui.window_trace_thickness->w()-15,215
		);
			if (di == "show") {
		cl_gts_gui.menite_trace_thickness->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_trace_thickness->show();
			}
		}
		else if ((this->str_window_trace_input_color_==key)
		&& (4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_trace_input_color->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_trace_input_color->show();
			}
		cl_gts_gui.window_trace_input_color->position(xx,yy);
		}
		else if ((this->str_window_trace_output_color_==key)
		&& ((4==ret) || (6==ret)/* for old format */)) {
		cl_gts_gui.window_trace_output_color->resize( xx ,yy ,ww
		,cl_gts_gui.window_trace_output_color->h()  );
			if (di == "show") {
		cl_gts_gui.menite_trace_output_color->set();
		cl_gts_gui.window_main_view->show();/* Need for Minimize */
		cl_gts_gui.window_trace_output_color->show();
			}
		}
#ifndef _WIN32
		else if ((this->str_sane_device_name_ == key)
		&& (2 == ret)) {
		cl_gts_master.cl_iip_scan.device_name((char*)di.c_str());
		}
#endif
		else {
			pri_funct_err_bttvr(
 	"Warning : memory_desktop::load() : ignore '%s' at line %d"
			,buf ,ii );
		}
	}

	ifs.close();

	/* 読み込みに成功したあと、古いタイプのファイルなら消す */
	if (old_type_sw == true) {
		::remove( old_path.c_str() );
	}

	return OK;
}
