#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* ソースマネージャ(DSM)のオープン
DSMの親のWindowハンドル(this->_hw_parent)設定必要 */
int tw_win_l1_dsm::state2to3( void )
{
	TW_UINT16 rc;

	/* 状態(state)が2でないときは何もしない */
	if (TWAIN_STATE2_SOURCE_MANAGER_LOADED != this->twain_state) {
		return OK;
	}

	assert(NULL != this->_hw_parent);

	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state2to3()" );
	}

	rc = this->_dsm_entry(
		DG_CONTROL,DAT_PARENT,MSG_OPENDSM,
		(TW_MEMREF)&(this->_hw_parent)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->_dsm_pri_error(
		"DG_CONTROL,DAT_PARENT,MSG_OPENDSM", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_dsm_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* 状態(state)を3に進める */
	this->twain_state = TWAIN_STATE3_SOURCE_MANAGER_OPENED;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 2 --> 3 : source manager opened" );
	}

	return OK;
}
