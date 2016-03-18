#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* ソース(DS)のクローズ */
int tw_win_l1_dsm::state4to3( void )
{
	TW_UINT16 rc;

	/* 状態(state)が4でないときは何もしない */
	if (TWAIN_STATE4_SOURCE_OPENED != this->twain_state) {
		return OK;
	}

	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state4to3()" );
	}

	rc = this->_dsm_entry(
		DG_CONTROL,DAT_IDENTITY,MSG_CLOSEDS,
		(TW_MEMREF)&(this->_SourceID)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->_dsm_pri_error(
		"DG_CONTROL,DAT_IDENTITY,MSG_CLOSEDS", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_dsm_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* 状態(state)を3に戻す */
	this->twain_state = TWAIN_STATE3_SOURCE_MANAGER_OPENED;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 4 --> 3 : source closes" );
		pri_funct_msg_ttvr(
		" SourceID.Id<%d> SourceID.ProductName<%s>",
			this->_SourceID.Id,
			this->_SourceID.ProductName );
	}

	return OK;
}
