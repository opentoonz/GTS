#include <fstream>
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
		if (str.empty()) { continue; }/* 空行無視 */
		if ('#' == str.at(0)) { continue; }/* コメント行無視 */

		std::vector< std::string > words; /* 言葉分け */
		igs::lex::white_space_and_double_quote(str,words);
		if (words.size() < 2) { continue; }/* キーワードしかない */

		/* キーワードと数値が1語以上(2<=words.size())ある */

		if (words.at(0) == "browser_directory_path") {
 cl_gts_master.cl_bro_config.setup_path(words.at(1).c_str());
 cl_gts_master.cl_bro_level.setup_path(words.at(1).c_str());
 cl_gts_master.cl_bro_trace_batch.setup_path(words.at(1).c_str());
		} else
		if (words.at(0) == "image_file_format") {
			if (words.at(1) == "TIFF") {
 cl_gts_master.cl_bro_level.set_current_imagefile_extension(0);
			} else if (words.at(1) == "TGA") {
 cl_gts_master.cl_bro_level.set_current_imagefile_extension(1);
			}
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
