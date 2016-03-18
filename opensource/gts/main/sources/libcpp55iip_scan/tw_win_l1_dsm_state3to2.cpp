#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* ソースマネージャ(DSM)のクローズ */
int tw_win_l1_dsm::state3to2( void )
{
	TW_UINT16 rc;

	/* 状態(state)が3でないときは何もしない */
	if (TWAIN_STATE3_SOURCE_MANAGER_OPENED != this->twain_state) {
		return OK;
	}

	assert(NULL != this->_hw_parent);

	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state3to2()" );
	}

	rc = this->_dsm_entry(
		DG_CONTROL,DAT_PARENT,MSG_CLOSEDSM,
		(TW_MEMREF)&(this->_hw_parent)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->_dsm_pri_error(
		"DG_CONTROL,DAT_PARENT,MSG_CLOSEDSM", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_dsm_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* 親へのハンドルをリセット */
	//this->_hw_parent = NULL;

	/* 状態(state)を2に戻す */
	this->twain_state = TWAIN_STATE2_SOURCE_MANAGER_LOADED;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 3 --> 2 : source manager closed" );
	}

	return OK;
}
