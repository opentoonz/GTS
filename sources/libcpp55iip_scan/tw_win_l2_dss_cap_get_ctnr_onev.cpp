#include "pri.h"
#include "tw_win_l2_dss.h"

/* get onevalue(container) */
int tw_win_l2_dss::_cap_get_ctnr_onevalue( TW_UINT16 ui16_cap, TW_ONEVALUE *p_tw_onevalue )
{
	TW_CAPABILITY	tw_capability;
	TW_ONEVALUE	*p_tw_ov;

	/* TWAIN機器からデータを取ってくる */
	if (OK != this->_cap_get_ctnr( ui16_cap, &tw_capability ) ) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr() returns NG." );
		return NG;
	}

	/* データのコンテナタイプが違う */
	if (TWON_ONEVALUE != tw_capability.ConType) {
		pri_funct_err_bttvr(
	"Error : tw_capability.ConType is not TWON_ONEVALUE." );

		/* Windows 特有のおまじない1/3 */
		GlobalFree( (HANDLE)tw_capability.hContainer );

		return NG;
	}

	/* Windows 特有のおまじない2/3 */
	p_tw_ov = (pTW_ONEVALUE)GlobalLock(
		(HANDLE)tw_capability.hContainer
	);

	/* データをコピーする */
	(*p_tw_onevalue) = (*p_tw_ov);

	/* Windows 特有のおまじない3/3 */
	GlobalUnlock( (HANDLE)tw_capability.hContainer );
	GlobalFree( (HANDLE)tw_capability.hContainer );

	return OK;
}

/*--------------------------------------------------------*/

/* get_current onevalue(container) */
int tw_win_l2_dss::_cap_getcrnt_ctnr_onevalue( TW_UINT16 ui16_cap, TW_ONEVALUE *p_tw_onevalue )
{
	TW_CAPABILITY	tw_capability;
	TW_ONEVALUE	*p_tw_ov;

	/* TWAIN機器からデータを取ってくる */
	if (OK != this->_cap_getcrnt_ctnr(ui16_cap,&tw_capability)) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_getcrnt_ctnr() returns NG." );
		return NG;
	}

	/* データのコンテナタイプが違う */
	if (TWON_ONEVALUE != tw_capability.ConType) {
		pri_funct_err_bttvr(
	"Error : tw_capability.ConType is not TWON_ONEVALUE." );

		/* Windows 特有のおまじない1/3 */
		GlobalFree( (HANDLE)tw_capability.hContainer );

		return NG;
	}

	/* Windows 特有のおまじない2/3 */
	p_tw_ov = (pTW_ONEVALUE)GlobalLock(
		(HANDLE)tw_capability.hContainer
	);

	/* データをコピーする */
	(*p_tw_onevalue) = (*p_tw_ov);

	/* Windows 特有のおまじない3/3 */
	GlobalUnlock( (HANDLE)tw_capability.hContainer );
	GlobalFree( (HANDLE)tw_capability.hContainer );

	return OK;
}

/*--------------------------------------------------------*/

int tw_win_l2_dss::_cap_get_ctnr_onevalue_bool( TW_UINT32 *ui32p_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	if (OK != this->_cap_get_ctnr_onevalue(
	ui16_cap, &tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}
	if (TWTY_BOOL != tw_onevalue.ItemType) {
		pri_funct_err_bttvr(
		"Error : %s tw_onevalue.ItemType is not TWTY_BOOL.",
			cp_cap_name );
		return NG;
	}

	*ui32p_val = tw_onevalue.Item;
	return OK;
}

int tw_win_l2_dss::_cap_get_ctnr_onevalue_fix32( double *dp_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	if (OK != this->_cap_get_ctnr_onevalue(
	ui16_cap, &tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}
	if (TWTY_FIX32 != tw_onevalue.ItemType) {
		pri_funct_err_bttvr(
		"Error : %s tw_onevalue.ItemType is not TWTY_FIX32.",
			cp_cap_name );
		return NG;
	}

	this->_fix32_to_double(
		(TW_FIX32 *)&(tw_onevalue.Item), dp_val );

	return OK;
}

/*--------------------------------------------------------*/

int tw_win_l2_dss::_cap_getcrnt_ctnr_onevalue_ui16( TW_UINT16 *ui16p_val, TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	if (OK != this->_cap_getcrnt_ctnr_onevalue(
	ui16_cap, &tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_getcrnt_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}
	if (TWTY_UINT16 != tw_onevalue.ItemType) {
		pri_funct_err_bttvr(
		"Error : %s tw_onevalue.ItemType is not TWTY_UINT16.",
			cp_cap_name );
		return NG;
	}

	/* ui32-->ui16だがオーバーフローの問題が起こる可能性は低い */
	*ui16p_val = (unsigned short)(tw_onevalue.Item);

	return OK;
}
