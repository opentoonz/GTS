#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_setupmemxfer_get( TW_SETUPMEMXFER *p_tw_setupmemxfer )
{
	TW_UINT16 rc;

	rc = this->ds_entry(
		DG_CONTROL,DAT_SETUPMEMXFER,MSG_GET,
		(TW_MEMREF *)p_tw_setupmemxfer
	);

	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_SETUPMEMXFER,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	return OK;
}

void tw_win_l2_dss::_setupmemxfer_pri( TW_SETUPMEMXFER *p_tw_setupmemxfer )
{
	pri_funct_msg_vr(
	"------ TW_SETUPMEMXFER ------" );

	pri_funct_msg_vr(
	"01/5 type      parameter  value");

	pri_funct_msg_vr(
	"02/5 TW_UINT32 MinBufSize %lu",
		p_tw_setupmemxfer->MinBufSize );
	pri_funct_msg_vr(
	"03/5 TW_UINT32 MaxBufSize %lu",
		p_tw_setupmemxfer->MaxBufSize );
	pri_funct_msg_vr(
	"04/5 TW_UINT32 Preferred  %lu",
		p_tw_setupmemxfer->Preferred );
}
int tw_win_l2_dss::setupmemxfer_pri_all( void )
{
	TW_SETUPMEMXFER tw_setupmemxfer;

	tw_setupmemxfer.MinBufSize = 0;
	tw_setupmemxfer.MaxBufSize = 0;
	tw_setupmemxfer.Preferred = 0;

	if (OK != this->_setupmemxfer_get( &tw_setupmemxfer )) {
		pri_funct_err_bttvr(
	 "Error : this->_setupmemxfer_get(-) returns NG" );
		return NG;
	}

	this->_setupmemxfer_pri( &tw_setupmemxfer );

	return OK;
}
