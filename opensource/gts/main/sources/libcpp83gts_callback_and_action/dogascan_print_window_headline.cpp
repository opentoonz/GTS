#include <string.h>
#include "ptbl_path_max.h"
#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

int gts_master::_print_window_headline( void )
{
	char *cp_config_file, *cp_level_head;
	int i_len;
	long l_zoom;
	const char	*ccp_nothing = "nothing";
	char ca_buf[PTBL_PATH_MAX];

	/* configファイル名
		過去にloadしたconfigファイルで一番最新の名前 */
	cp_config_file = this->cl_memo_config.cp_memory_path();
	if (	(NULL != cp_config_file) &&
		(NULL != strrchr(cp_config_file, '/'))
	) {
	 cp_config_file = strrchr( cp_config_file, '/' );
	 ++cp_config_file;
	}

	/* 名前がセットできないときはnothing表示 */
	if (	(NULL == cp_config_file) ||
		('\0' == cp_config_file[0])
	) {
		cp_config_file = (char *)ccp_nothing;
	}

	/* levelファイル名
		menuのlevel file名の項目からとって来る */
	/******if (OK != this->cl_bro_level.i_lpath_cpy_head_means_level(
		cl_gts_gui.strinp_level_file->value(),ON
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_lpath_cpy_head_means_level(%s,%d) returns NG",
		cl_gts_gui.strinp_level_file->value(),ON
		);
		return NG;
	}
	cp_level_head = this->cl_bro_level.cp_path();*********/

	cp_level_head  = this->cl_bro_level.cp_levelname();
	if (NULL == cp_level_head) {
		pri_funct_err_bttvr(
		"Error : this->cl_bro_level.cp_levelname() returns NG"
		);
		return NG;
	}

	if (	(NULL == cp_level_head) ||
		('\0' == cp_level_head[0])
	) {
		cp_level_head = (char *)ccp_nothing;
	}

	/* zoom値 */
	l_zoom = this->cl_ogl_view.get_l_zoom();

	i_len = strlen(cl_gts_master.cp_release_name());
	i_len += strlen( "-0000  " );
	i_len += strlen( "Config " );
	i_len += strlen(cp_config_file);
	i_len += strlen( "  Level " );
	i_len += strlen(cp_level_head);
	i_len += strlen( "  Zoom " );
	i_len += 3L;
	if (PTBL_PATH_MAX <= i_len) { /* 大きすぎ */
		pri_funct_err_bttvr(
		"Error : too long<%d> directroy path<%s%s%s%s%sx%ld>",
			i_len,
			"Config ", cp_config_file,
			"  Level ", cp_level_head,
			"  Zoom ", l_zoom );
		return NG;
	}

	if (0L == l_zoom) {
		(void)sprintf( ca_buf,
			"%s-%s  Config %s  Level %s",
			cl_gts_master.cp_release_name(),
			cl_gts_master.cp_release_number(),
			cp_config_file, cp_level_head);
	} else if (0L < l_zoom) {
		(void)sprintf( ca_buf,
			"%s-%s  Config %s  Level %s  Zoom x%ld",
			cl_gts_master.cp_release_name(),
			cl_gts_master.cp_release_number(),
			cp_config_file, cp_level_head, l_zoom);
	} else {
		(void)sprintf( ca_buf,
			"%s-%s  Config %s  Level %s  Zoom x1/%ld",
			cl_gts_master.cp_release_name(),
			cl_gts_master.cp_release_number(),
			cp_config_file, cp_level_head, -l_zoom);
	}

	cl_gts_gui.window_opengl->label(ca_buf);

	return OK; 
}
