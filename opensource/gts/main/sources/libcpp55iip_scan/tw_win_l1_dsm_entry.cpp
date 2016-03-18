#include "tw_win_l1_dsm.h"

/* Data Source Managerへ(State 2...3)のアクセス */
TW_UINT16 tw_win_l1_dsm::_dsm_entry( TW_UINT32 ui32_dg, TW_UINT16 ui16_dat, TW_UINT16 ui16_msg, TW_MEMREF p_data )
{
	return this->_p_dsm_entry(
		&(this->_AppID),
		NULL,
		ui32_dg,
		ui16_dat,
		ui16_msg,
		p_data
	);
}

/* Data Sourceへ(State 4...7)のアクセス
第２引数(pTW_IDENTITY pDest)は&(this->_SourceID) */
TW_UINT16 tw_win_l1_dsm::ds_entry( TW_UINT32 ui32_dg, TW_UINT16 ui16_dat, TW_UINT16 ui16_msg, TW_MEMREF p_data )
{
	return this->_p_dsm_entry(
		&(this->_AppID),
		&(this->_SourceID),
		ui32_dg,
		ui16_dat,
		ui16_msg,
		p_data
	);
}
