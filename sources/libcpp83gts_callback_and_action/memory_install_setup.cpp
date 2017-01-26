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

		if (words.at(0) == "browser_directory_path") {
			this->browser_directory_path = words.at(1);
 cl_gts_master.cl_config.set_dir_path( words.at(1) );
 cl_gts_master.cl_trace_batch.set_dir_path(words.at(1));
		} else
		if (words.at(0) == "image_file_format") {
			this->image_file_format = words.at(1);
		} else
		if (words.at(0) == "area_rot90") {
			this->area_rot90 = words.at(1);
		} else
		if (words.at(0) == "short_cut_key_start_scan") {
			// start_scan	Enter(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_start_scan(words.at(1).c_str());
		} else
		if (words.at(0) == "short_cut_key_rescan") {
			// rescan	Space(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_rescan(words.at(1).c_str());
		} else
		if (words.at(0) == "short_cut_key_next_scan") {
			// next_scan	Enter(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_next_scan(words.at(1).c_str());
		} else
		if (words.at(0) == "short_cut_key_stop_scan") {
			// stop_scan	Esc(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_stop_scan(words.at(1).c_str());
		}
		else {
			pri_funct_err_bttvr(
 	"Warning : memory_install_setup::load() : ignore '%s' at line %d"
			,words.at(0) ,ii );
		}
	}
	ifs.close();/* ファイル閉じる */
}
