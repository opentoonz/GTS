#include "pri.h"
#include "tw_win_l1_dsm.h"

int tw_win_l1_dsm::_get_dsm_cc( TW_UINT16 *ui16p_cc )
{
	TW_UINT16 rc;
	TW_STATUS twStatus = {0, 0};

	rc = this->_dsm_entry(
		DG_CONTROL,DAT_STATUS,MSG_GET,
		(TW_MEMREF *)&twStatus
	);

	if (TWRC_SUCCESS != rc) {
		pri_funct_err_bttvr(
    "Error : this->_dsm_entry() returns %u(twcc %d)",
			rc, twStatus.ConditionCode
		);
		return NG;
	}

	*ui16p_cc = twStatus.ConditionCode;
	return OK;
}

int tw_win_l1_dsm::_get_ds_cc( TW_UINT16 *ui16p_cc )
{
	TW_UINT16 rc;
	TW_STATUS twStatus = {0, 0};

	rc = this->ds_entry(
		DG_CONTROL,DAT_STATUS,MSG_GET,
		(TW_MEMREF *)&twStatus
	);

	if (TWRC_SUCCESS != rc) {
		pri_funct_err_bttvr(
    "Error : this->ds_entry() returns %u(twcc %d)",
			rc, twStatus.ConditionCode
		);
		return NG;
	}

	*ui16p_cc = twStatus.ConditionCode;
	return OK;
}
