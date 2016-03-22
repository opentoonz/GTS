#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_cap_set_ctnr_onevalue( TW_UINT16 ui16_icap, TW_ONEVALUE tw_onevalue )
{
	TW_CAPABILITY	twCapability;
	pTW_ONEVALUE	p_tw_onevalue;

	/*
	www.twain.org/docs/Spec1_9_197.pdf
	 Page72,78
	 Chapter 4 -> Advenced Application Implementation
	 -> Capability -> Capability Negotiation -> Negotiation(Part 2)
	*/

	/* Step 1 : TW_CAPABILITY構造体の各値を設定 */
	twCapability.Cap = ui16_icap;
	twCapability.ConType = TWON_ONEVALUE;

	/* Step 2 : コンテナーメモリを確保し、値を設定
		GlobalAlloc(GHND,)は、移動可能メモリを確保し、
		確保したメモリの内容をゼロに初期化します。
		戻り値は、メモリオブジェクトのハンドルになります。
		ハンドルをポインタに変換するには、
		GlobalLock()関数を使用し、
		値を設定したのちGlobalUnlock()します。
	*/
	twCapability.hContainer = GlobalAlloc(GHND,sizeof(TW_ONEVALUE));
	if (NULL == twCapability.hContainer) {
		pri_funct_err_bttvr(
	"Error : GlobalAlloc(GHND,sizeof(TW_ONEVALUE)) returns NULL." );
		return NG;
	}
	p_tw_onevalue=(pTW_ONEVALUE)
	GlobalLock(twCapability.hContainer);
	*p_tw_onevalue = tw_onevalue; /* OneValueの設定 */
	GlobalUnlock(twCapability.hContainer);

	/* Step 3 : 送信し設定する
		(注)_cap_set_ctnr(-)の中で、 GlobalFree()してる
	*/
	if (OK!=this->_cap_set_ctnr(&twCapability)) {
		pri_funct_err_bttvr(
       "Error : this->_cap_set_ctnr(-) returns NG." );

		return NG;
	}

	return OK;
}

/*--------------------------------------------------------*/

int tw_win_l2_dss::_cap_set_ctnr_onevalue_bool( TW_BOOL bo_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	tw_onevalue.ItemType = TWTY_BOOL;
	tw_onevalue.Item = bo_val;

	if (OK != this->_cap_set_ctnr_onevalue(ui16_cap,
	tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_set_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	return OK;
}

int tw_win_l2_dss::_cap_set_ctnr_onevalue_fix32( double d_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	tw_onevalue.ItemType = TWTY_FIX32;
	this->_double_to_fix32( d_val,
		(TW_FIX32 *)&(tw_onevalue.Item) );

	if (OK != this->_cap_set_ctnr_onevalue(ui16_cap,
	tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_set_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	return OK;
}

int tw_win_l2_dss::_cap_set_ctnr_onevalue_ui16( TW_UINT16 ui16_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	tw_onevalue.ItemType = TWTY_UINT16;
	tw_onevalue.Item = ui16_val;

	if (OK != this->_cap_set_ctnr_onevalue(ui16_cap,
	tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_set_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	return OK;
}
