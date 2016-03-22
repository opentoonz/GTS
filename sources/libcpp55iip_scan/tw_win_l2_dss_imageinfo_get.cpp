#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_imageinfo_get( TW_IMAGEINFO *p_tw_imageinfo )
{
	TW_UINT16 rc;

	rc = this->ds_entry(
		DG_IMAGE,DAT_IMAGEINFO,MSG_GET,
		(TW_MEMREF *)p_tw_imageinfo
	);

	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_IMAGE,DAT_IMAGEINFO,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	return OK;
}
