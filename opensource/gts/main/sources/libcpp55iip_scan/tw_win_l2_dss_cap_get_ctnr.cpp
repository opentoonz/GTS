#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

/* get capability with container */
int tw_win_l2_dss::_cap_get_ctnr( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability )
{
	TW_UINT16 rc;

	/*
	www.twain.org/docs/Spec1_9_197.pdf
	 Page71, 75
	 Chapter 4 -> Advenced Application Implementation
	 -> Capability -> Capability Negotiation -> Negotiation(Part 1)
	*/

	/* Step 1 : 初期値を設定 */
	p_tw_capability->Cap = ui16_cap;
	p_tw_capability->ConType = TWON_DONTCARE16;
	p_tw_capability->hContainer = NULL;

	/* Step 2,3 : 関数を実行し、値をとってくる */
	rc = this->ds_entry(
		DG_CONTROL,DAT_CAPABILITY,MSG_GET,
		(TW_MEMREF)p_tw_capability
	);

	/* Step 4 : 戻り値をチェックする。ノーサポート、あるいはエラー
		    なら、コンディションコードをチェックする */
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_CAPABILITY,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	/* コンテナにデータが確保されていない...
	前のチェックで引っかかっているはずなので、ここで引っかかる
	ということは、TWAIN プログラミングの実装に問題がある。 */
	if (NULL == p_tw_capability->hContainer) {
		pri_funct_err_bttvr(
	   "Error : p_tw_capability->hContainer is NULL." );
		return NG;
	}

	return OK;
}

/* get_current capability with container */
int tw_win_l2_dss::_cap_getcrnt_ctnr( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability )
{
	TW_UINT16 rc;

	/* Step 1 : 初期値を設定 */
	p_tw_capability->Cap = ui16_cap;
	p_tw_capability->ConType = TWON_DONTCARE16;
	p_tw_capability->hContainer = NULL;

	/* Step 2,3 : 関数を実行し、値をとってくる */
	rc = this->ds_entry(
		DG_CONTROL,DAT_CAPABILITY,MSG_GETCURRENT,
		(TW_MEMREF)p_tw_capability
	);

	/* Step 4 : 戻り値をチェックする。ノーサポート、あるいはエラー
		    なら、コンディションコードをチェックする */
	if (TWRC_SUCCESS != rc) {
		if (OK != this->ds_pri_error(
		"DG_CONTROL,DAT_CAPABILITY,MSG_GETCURRENT", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		}
		return NG;
	}

	/* コンテナにデータが確保されていない...
	前のチェックで引っかかっているはずなので、ここで引っかかる
	ということは、TWAIN プログラミングの実装に問題がある。 */
	if (NULL == p_tw_capability->hContainer) {
		pri_funct_err_bttvr(
	   "Error : p_tw_capability->hContainer is NULL." );
		return NG;
	}

	return OK;
}
