#include <iostream> // std::cout
#include <fstream>
#include "pri.h"
#include "igs_lex_white_space_and_double_quote.h"
#include "memory_scan_area.h" // gts_file_path(-)
#include "gts_master.h"

void memory_install_setup::load( const std::string& exe_file_path )
{
	const char *file_name = "gts_install_setup.txt";
	std::string path = gts_file_path(exe_file_path.c_str(), file_name);
	if (path.empty()) { return; }/* ファイルが存在しない */

	std::ifstream ifs( path );/* ファイル開く */
	if (!ifs) { return; } /* ファイルが開けない */

	std::string str;
	for (int ii = 1 ;std::getline(ifs,str) ;++ii) {/* 一行読む */
		if (str.empty()) { continue; }/* 空行は無視 */
		if ('#' == str.at(0)) { continue; }/* コメント行は無視 */

		std::vector< std::string > words; /* 単語に分割 */
		igs::lex::white_space_and_double_quote(str,words);
		if (words.size() < 2) { continue; }/* キーワードしかない */

		/* キーワードと、数値が1語以上(2<=words.size())ある */

		if (	     "browser_top_folder" == words.at(0) ) {
			this->browser_top_folder  =  words.at(1);
		} else
		if (	     "save_number_format" == words.at(0)) {
			this->save_number_format  =  words.at(1);
		} else
		if (	     "image_file_format" == words.at(0)) {
			this->image_file_format  =  words.at(1);
		} else
		if (	     "area_resolution_dpi" == words.at(0) ) {
			this->area_resolution_dpi  =  words.at(1);
		} else
		if (	     "area_rotate_per_90" == words.at(0) ) {
			this->area_rotate_per_90  =  words.at(1);
		} else
		if (	     "pixel_type" == words.at(0) ) {
			this->pixel_type  =  words.at(1);
		} else
		if (	     "scan_num_endless_direction" == words.at(0) ) {
			this->scan_num_endless_direction = words.at(1);
		} else
		if (	"short_cut_key_start_scan" == words.at(0)) {
   cl_gts_master.cl_memo_short_cut_key.setup_start_scan(words.at(1).c_str());
			// start_scan	Enter(Default)
		} else
		if (	"short_cut_key_rescan" == words.at(0)) {
   cl_gts_master.cl_memo_short_cut_key.setup_rescan(words.at(1).c_str());
			// rescan	Space(Default)
		} else
		if (	"short_cut_key_next_scan" == words.at(0)) {
   cl_gts_master.cl_memo_short_cut_key.setup_next_scan(words.at(1).c_str());
			// next_scan	Enter(Default)
		} else
		if (	"short_cut_key_stop_scan" == words.at(0)) {
   cl_gts_master.cl_memo_short_cut_key.setup_stop_scan(words.at(1).c_str());
			// stop_scan	Esc(Default)
		}
		else {
			pri_funct_err_bttvr(
 	"Warning : memory_install_setup::load() : ignore '%s' at line %d"
			,words.at(0) ,ii );
		}
	}
	ifs.close();/* ファイル閉じる */
}
