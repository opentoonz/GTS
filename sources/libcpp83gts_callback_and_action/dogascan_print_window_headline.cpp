#include <string>
#include <sstream>
#include "gts_gui.h"
#include "gts_master.h"
#include "ids_path_level_from_files.h" // ids::path::from_fpath_to_dpath_fname(-)

int gts_master::print_window_headline( void )
{
	/* 過去にOpen/Saveしたconfigファイルで一番最新の名前 */ 
	std::string fname( cl_gts_master.cl_config.get_save_file_name() );
	if (fname.empty()) {
		fname = "nothing";
	}

	/* 画像拡大率 */
	const long l_zoom = this->cl_ogl_view.get_l_zoom();

	/* Main Window Barに表示
	Exsample1 "gts-2.3.0  Config A"
	Exsample2 "gts-2.3.0  Config A  Zoom x1"
	Exsample3 "gts-2.3.0  Config A  Zoom x1/16"
	*/
	std::ostringstream ost;
	ost	<< cl_gts_master.cp_release_name()
		<< "-" << cl_gts_master.cp_release_number()
		<< "  Config " << fname
		;
	if  (0 < l_zoom) {	ost << "  Zoom x" << l_zoom; }
	else if (l_zoom < 0) {	ost << "  Zoom x1/" << -l_zoom; }
	cl_gts_gui.window_main_view->label( ost.str().c_str() );

	return OK;
}
