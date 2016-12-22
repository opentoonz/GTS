#include <stdio.h>
#include <string.h>
#include <string>
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
	std::ifstream ifs( old_path.c_str() );
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
		int xx=0,yy=0,ww=0,hh=0;
		if (1 <= ret) { key = words.at(0); }
		if (2 <= ret) { di = words.at(1); }
		if (3 <= ret) { xx = atoi(words.at(2).c_str()); }
		if (4 <= ret) { yy = atoi(words.at(3).c_str()); }
		if (5 <= ret) { ww = atoi(words.at(4).c_str()); }
		if (6 <= ret) { hh = atoi(words.at(5).c_str()); }

		if ((this->str_config_dir_ == key) && (2 == ret)) {
			cl_gts_master.cl_config.set_dir_path(
				di.c_str() );
		}
		else if ((this->str_window_opengl_==key) && (6==ret)) {
		cl_gts_gui.window_opengl->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_next_scan_==key) && (4==ret)) {
			if (di == "show") {
		////cl_gts_gui.menite_next_scan->set();
		//cl_gts_gui.window_opengl->show();/* Need for Minimize */
		//cl_gts_gui.window_next_scan->show();
			}
		cl_gts_gui.window_next_scan->position(xx,yy);
		}
		else if ((this->str_window_level_==key)
		&& ((4==ret) || (6==ret)/* for old format */)) {
			if (di == "show") {
		cl_gts_gui.menite_level->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_level_set->show();
			}
		cl_gts_gui.window_level_set->position(xx,yy);
		}
#if 0
		else if ((this->str_window_level_browse_==key)
		&& (6==ret)) {
		cl_gts_gui.window_level_browse->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_config_load_==key) && (6==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_config_load->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_config_load->show();
			}
		cl_gts_gui.window_config_load->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_config_save_as_==key) && (6==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_config_save_as->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_config_save_as->show();
			}
		cl_gts_gui.window_config_save_as->resize(xx,yy,ww,hh);
		}
#endif
		else if ((this->str_window_crop_area_and_rot90_==key)&&(4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_crop_area_and_rot90->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_crop_area_and_rot90->show();
			}
		cl_gts_gui.window_crop_area_and_rot90->position(xx,yy);
		}
		else if ((this->str_window_pixel_type_and_bright_==key)&&(4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_pixel_type_and_bright->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_pixel_type_and_bright->show();
			}
		cl_gts_gui.window_pixel_type_and_bright->position(xx,yy);
		}
		else if ((this->str_window_color_trace_==key) && (4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_color_trace->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_color_trace->show();
			}
		cl_gts_gui.window_color_trace->position(xx,yy);
		}
		else if ((this->str_window_fnum_list_==key) && (6==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_fnum_list->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_fnum_list->show();
			}
		cl_gts_gui.window_fnum_list->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_trace_batch_==key) && (6==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_trace_batch->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_trace_batch->show();
			}
		cl_gts_gui.window_trace_batch->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_thickness_==key) && (6==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_thickness->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_thickness->show();
			}
		cl_gts_gui.window_thickness->resize(xx,yy,ww,hh);
		}
		else if ((this->str_window_edit_color_==key) && (4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_edit_color->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_edit_color->show();
			}
		cl_gts_gui.window_edit_color->position(xx,yy);
		}
		else if ((this->str_window_edit_hab_min_max_==key) && (4==ret)) {
			if (di == "show") {
		cl_gts_gui.menite_edit_hsv_min_max->set();
		cl_gts_gui.window_opengl->show();/* Need for Minimize */
		cl_gts_gui.window_hab_histogram->show();
			}
		cl_gts_gui.window_hab_histogram->position(xx,yy);
		}
#ifndef _WIN32
		else if ((this->str_sane_device_name_ == key) && (2 == ret)) {
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
