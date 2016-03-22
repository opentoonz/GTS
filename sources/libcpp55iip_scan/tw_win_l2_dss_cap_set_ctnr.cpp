#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

/* set capability with container */
int tw_win_l2_dss::_cap_set_ctnr( TW_CAPABILITY *p_tw_capability )
{
	TW_UINT16	rc;

	/* コンテナーメモリは呼出し側で確保しなければならない */
	assert(NULL != p_tw_capability->hContainer);

	/* 値をtwain sourceに設定する */
	rc = this->ds_entry(
		DG_CONTROL,DAT_CAPABILITY,MSG_SET,
		(TW_MEMREF)p_tw_capability
	);

	/* コンテナーメモリの用事が終ったのでここで開放してしまう */
	GlobalFree(p_tw_capability->hContainer);
	p_tw_capability->hContainer = NULL;

	/* 戻り値をチェック
	TWRC_SUCCESS - 正常に値をsetした
	TWRC_FAILURE - エラー、コンディションコードをチェックする
	TWRC_CHECKSTATUS - 正確に設定できなかったので(?)、
		指定した値にできるだけ近い値を設定した。
		どうなったかは、MSG_GETで値をみろ
		...ということか?(2004.11.30)
	*/
	if (TWRC_SUCCESS != rc) {
		if (TWRC_CHECKSTATUS == rc) {
			pri_funct_err_bttvr(
 "Error : this->ds_entry(DG_CONTROL,DAT_CAPABILITY,MSG_SET,) returns TWRC_CHECKSTATUS" );
		} else {
		 if (OK != this->ds_pri_error(
		 "DG_CONTROL,DAT_CAPABILITY,MSG_GET", rc )) {
			pri_funct_err_bttvr(
		 "Error : this->ds_pri_error() returns NG" );
		 }
		}
		return NG;
	}

	return OK;
}
