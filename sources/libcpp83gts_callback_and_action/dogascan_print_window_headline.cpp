#include <string.h>
#include "ptbl_path_max.h"
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

int gts_master::_print_window_headline( void )
{
	const char* nothing_str = "nothing";

	/* configファイル名 過去にloadしたconfigファイルで一番最新の名前 */
	std::string config_filename( this->cl_memo_config.memory_of_path );
	if ( !config_filename.empty() ) {
		auto pos = config_filename.rfind('/');
		if (std::string::npos != pos) {
			config_filename.erase( 0 ,pos+1 );
		}
	}
	if (config_filename.empty()) {/* セットできないときはnothing表示 */
		config_filename = nothing_str;
	}

	/* level名 */ 
	if (NULL ==      this->cl_bro_level.cp_levelname()) {
		pri_funct_err_bttvr(
		"Error : this->cl_bro_level.cp_levelname() returns NG"
		);
		return NG;
	}

	std::string level_name(
		this->cl_bro_level.cp_levelname()
	);
	if (level_name.empty()) { /* セットできないときはnothing表示 */
		level_name = nothing_str;
	}

	/* zoom値 */
	long l_zoom = this->cl_ogl_view.get_l_zoom();

	int i_len = strlen(cl_gts_master.cp_release_name());
	i_len += strlen( "-0000  " );
	i_len += strlen( "Config " );
	i_len += config_filename.length();
	i_len += strlen( "  Level " );
	i_len += level_name.length();
	i_len += strlen( "  Zoom " );
	i_len += 3L;
	if (PTBL_PATH_MAX <= i_len) { /* 大きすぎ */
		pri_funct_err_bttvr(
		"Error : too long<%d> directroy path<%s%s%s%s%sx%ld>",
			i_len,
			"Config ", config_filename.c_str(),
			"  Level ", level_name.c_str(),
			"  Zoom ", l_zoom );
		return NG;
	}

	char ca_buf[PTBL_PATH_MAX];
	if (0L == l_zoom) {
		(void)sprintf( ca_buf,
			"%s-%s  Config %s  Level %s",
			cl_gts_master.cp_release_name(),
			cl_gts_master.cp_release_number(),
			config_filename.c_str(), level_name.c_str());
	} else if (0L < l_zoom) {
		(void)sprintf( ca_buf,
			"%s-%s  Config %s  Level %s  Zoom x%ld",
			cl_gts_master.cp_release_name(),
			cl_gts_master.cp_release_number(),
			config_filename.c_str(), level_name.c_str(), l_zoom);
	} else {
		(void)sprintf( ca_buf,
			"%s-%s  Config %s  Level %s  Zoom x1/%ld",
			cl_gts_master.cp_release_name(),
			cl_gts_master.cp_release_number(),
			config_filename.c_str(), level_name.c_str(), -l_zoom);
	}

	cl_gts_gui.window_opengl->label(ca_buf);

	return OK;
}
