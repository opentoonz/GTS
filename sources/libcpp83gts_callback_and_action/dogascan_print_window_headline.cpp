#include <string>
#include <sstream>
#include "gts_gui.h"
#include "gts_master.h"
#include "ids_path_level_from_files.h" // ids::path::from_fpath_to_dpath_fname(-)

int gts_master::print_window_headline( void )
{
	const char* nothing_str = "nothing";

	/* Configファイル名
	過去にloadしたconfigファイルで一番最新の名前 */
	std::string config_filename;
	{
		std::string dpath;
		ids::path::from_fpath_to_dpath_fname(
			this->cl_memo_config.memory_of_path
			,dpath ,config_filename
		);
	}
	if (config_filename.empty()) { /* セットできないときはnothing表示 */
		config_filename = nothing_str;
	}

	/* Save Level名 */ 
	std::string level_name(
		cl_gts_gui.strinp_level_save_file_head->value()
	);
	if (level_name.empty()) { /* セットできないときはnothing表示 */
		level_name = nothing_str;
	}

	/* 画像拡大率 */
	const long l_zoom = this->cl_ogl_view.get_l_zoom();

	/* Main Window Barに表示
	Exsample1 "gts-2.3.0  Config A  SaveLevel A_full"
	Exsample2 "gts-2.3.0  Config A  SaveLevel A_full  Zoom x1"
	Exsample3 "gts-2.3.0  Config A  SaveLevel A_full  Zoom x1/16"
	*/
	std::ostringstream ost;
	ost	<< cl_gts_master.cp_release_name()
		<< "-" << cl_gts_master.cp_release_number()
		<< "  Config " << config_filename
		<< "  SaveLevel " << level_name;
	if  (0 < l_zoom) {	ost << "  Zoom x" << l_zoom; }
	else if (l_zoom < 0) {	ost << "  Zoom x1/" << -l_zoom; }
	cl_gts_gui.window_opengl->label( ost.str().c_str() );

	return OK;
}
