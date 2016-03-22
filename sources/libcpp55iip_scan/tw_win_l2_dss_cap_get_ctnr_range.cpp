#include "pri.h"
#include "tw_win_l2_dss.h"

/* get range(container) */
int tw_win_l2_dss::_cap_get_ctnr_range( TW_UINT16 ui16_cap, TW_RANGE *p_tw_range )
{
	TW_CAPABILITY	tw_capability;
	TW_RANGE	*p_tw_ra;

	/* TWAIN機器からデータを取ってくる */
	if (OK != this->_cap_get_ctnr( ui16_cap, &tw_capability ) ) {
		pri_funct_err_bttvr(
	 "Error : this->_get_capability() returns NG." );
		return NG;
	}

	/* データのコンテナタイプが違う */
	if (TWON_RANGE != tw_capability.ConType) {
		pri_funct_err_bttvr(
		 "Error : tw_capability.ConType is not TWON_RANGE." );

		/* Windows 特有のおまじない1/3 */
		GlobalFree( (HANDLE)tw_capability.hContainer );

		return NG;
	}

	/* Windows 特有のおまじない2/3 */
	p_tw_ra = (pTW_RANGE)GlobalLock(
		(HANDLE)tw_capability.hContainer
	);

	/* データをコピーする */
	(*p_tw_range) = (*p_tw_ra);

	/* Windows 特有のおまじない3/3 */
	GlobalUnlock( (HANDLE)tw_capability.hContainer );
	GlobalFree( (HANDLE)tw_capability.hContainer );

	return OK;
}
