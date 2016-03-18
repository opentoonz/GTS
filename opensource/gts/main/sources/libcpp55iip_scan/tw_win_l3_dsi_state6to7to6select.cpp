#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* State 6→7  アプリ：転送をソースに指示 */
int tw_win_l3_dsi::_state6to7to6select( void )
{
	long	l_xfermech;

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_ttvr( "tw_win_l3_dsi::_state6to7to6select()" );
	}

	if (OK != this->cap_getcrnt_lp_xfermech( &l_xfermech )) {
		return NG;
	}

	switch (l_xfermech) {
	case TWSX_NATIVE:
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr( "TWSX_NATIVE" );
		}
		/* 画像の転送 */
		if (OK != this->_state6to7to6native()) {
			pri_funct_err_bttvr(
		 "Error : this->_state6to7to6native() returns NG." );
			return NG;
		}
		break;
	case TWSX_MEMORY:
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr( "TWSX_MEMORY" );
		}
/* DG_IMAGE, DAT_IMAGEMEMXFER, MSG_GET, */
		break;
	case TWSX_FILE:
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr("TWSX_FILE, no action");
		}
		break;
	case TWSX_FILE2:
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr("TWSX_FILE2, no action");
		}
		break;
	default:
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"bad xfermech<%ld>", l_xfermech );
		}
		break;
	}

	return OK;
}
