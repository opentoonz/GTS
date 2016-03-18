#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_imagelayout_get( TW_IMAGELAYOUT *p_tw_imagelayout )
{
	TW_UINT16 rc;

	rc = this->ds_entry(
		DG_IMAGE,DAT_IMAGELAYOUT,MSG_GET,
		(TW_MEMREF *)p_tw_imagelayout
	);

	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_IMAGE,DAT_IMAGELAYOUT,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	return OK;
}
