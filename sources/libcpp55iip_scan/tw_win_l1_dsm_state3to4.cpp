#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* (デバイス選択し)ソース(DS)のオープン */
/* 引数はデータソースＩＤ */
/* システムデフォルト値は、ul_id = 0; cp_str32[0] = '\0' */
int tw_win_l1_dsm::state3to4( unsigned long ul_id, char *cp_str32 )
{
	TW_UINT16 rc;

	/* 状態(state)が3でないときは何もしない */
	if (TWAIN_STATE3_SOURCE_MANAGER_OPENED != this->twain_state) {
		return OK;
	}
	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state3to4()" );
	}

	/* check arg */
	assert( NULL != cp_str32 );
	if (32 < strlen( cp_str32 )) {
		pri_funct_err_bttvr(
			"Error : strlen(ProductName<%s>) is over 32.",
			cp_str32);
		return NG;
	}

	/* デバイスの選択
	twain.hより...
		typedef unsigned long TW_UINT32, FAR *pTW_UINT32;
		typedef char TW_STR32[34], FAR *pTW_STR32;
		typedef struct {
		TW_UINT32  Id;
		...
		TW_STR32 ProductName;
		} TW_IDENTITY, FAR * pTW_IDENTITY;
	*/
	this->_SourceID.Id = ul_id;
	strcpy( this->_SourceID.ProductName, cp_str32 );

	rc = this->_dsm_entry(
		DG_CONTROL,DAT_IDENTITY,MSG_OPENDS,
		(TW_MEMREF)&(this->_SourceID)
	);
	if (TWRC_SUCCESS != rc) {
		if (OK != this->_dsm_pri_error(
		"DG_CONTROL,DAT_IDENTITY,MSG_OPENDS", rc
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_dsm_pri_error(-) returns NG." );
		}
		return NG;
	}

	/* 状態(state)を4に進める */
	this->twain_state = TWAIN_STATE4_SOURCE_OPENED;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 3 --> 4 : source opened" );
		pri_funct_msg_ttvr(
		" SourceID.Id<%d> SourceID.ProductName<%s>",
			this->_SourceID.Id,
			this->_SourceID.ProductName );
	}

	return OK;
}
