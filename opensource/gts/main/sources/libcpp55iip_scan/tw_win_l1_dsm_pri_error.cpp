#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/* this->_dsm_entry(-)に関するエラー表示 */
int tw_win_l1_dsm::_dsm_pri_error( char *cp_tri, TW_UINT16 rc )
{
	TW_UINT16 ui16_cc;

	/* 戻り値が成功(TWRC_SUCCESS)の場合、なにもせずOKを返す */
	if (TWRC_SUCCESS == rc) { return OK; }

	/* 戻り値が成功(TWRC_SUCCESS)でない場合、基本のエラー表示 */
	pri_funct_err_bttvr(
		"Error : this->_dsm_entry(%s,) returns %u.",
		cp_tri, rc );

	/* 戻り値が失敗(TWRC_FAILURE)の場合、Condition Codeを得る */
	if (TWRC_FAILURE == rc) {
		/* Condition Codeを得るのに失敗 */
		if (OK != this->_get_dsm_cc( &ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_get_dsm_cc(-) returns NG." );
			return NG;
		}
		/* /* Condition Codeの意味を表示 */
		if (OK != this->_pri_cc( ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_pri_cc(-) returns NG.");
			return NG;
		}
	}
	return OK;
}

/* this->ds_entry(-)に関するエラー表示 */
int tw_win_l1_dsm::ds_pri_error( char *cp_tri, TW_UINT16 rc )
{
	TW_UINT16 ui16_cc;

	/* 戻り値が成功(TWRC_SUCCESS)の場合、なにもせずOKを返す */
	if (TWRC_SUCCESS == rc) { return OK; }

	/* 戻り値が成功(TWRC_SUCCESS)でない場合、基本のエラー表示 */
	pri_funct_err_bttvr(
		"Error : this->_ds_entry(%s,) returns %u.",
		cp_tri, rc );

	/* 戻り値が失敗(TWRC_FAILURE)の場合、Condition Codeを得る */
	if (TWRC_FAILURE == rc) {
		/* Condition Codeを得るのに失敗 */
		if (OK != this->_get_ds_cc( &ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_get_ds_cc(-) returns NG." );
			return NG;
		}
		/* /* Condition Codeの意味を表示 */
		if (OK != this->_pri_cc( ui16_cc )) {
			pri_funct_err_bttvr(
		 "Error : this->_pri_cc(-) returns NG.");
			return NG;
		}
	}
	return OK;
}
