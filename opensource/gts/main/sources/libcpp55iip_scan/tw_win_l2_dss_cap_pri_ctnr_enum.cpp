#include "pri.h"
#include "tw_win_l2_dss.h"

/* get enumeration_ui16(container) */
int tw_win_l2_dss::_cap_get_ctnr_enum_ui16_not_free( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability, TW_ENUMERATION **pp_tw_enumration )
{
	/* TWAIN機器からデータを取ってくる */
	if (OK != this->_cap_get_ctnr( ui16_cap, p_tw_capability ) ) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr() returns NG." );
		return NG;
	}

	/* データのコンテナタイプが違う */
	if (TWON_ENUMERATION != p_tw_capability->ConType) {
		pri_funct_err_bttvr(
	"Error : p_tw_capability->ConType is not TWON_ENUMERATION." );

		/* Windows 特有のおまじない1/3 */
		GlobalFree( (HANDLE)p_tw_capability->hContainer );
		return NG;
	}

	/* Windows 特有のおまじない2/3 */
	(*pp_tw_enumration) = (pTW_ENUMERATION)GlobalLock(
		(HANDLE)p_tw_capability->hContainer
	);

	/* データが一つもない */
	if ((*pp_tw_enumration)->NumItems <= 0) {
		pri_funct_err_bttvr(
   "Error : (*pp_tw_enumration)->NumItems is zero." );
		GlobalUnlock( (HANDLE)p_tw_capability->hContainer );
		GlobalFree( (HANDLE)p_tw_capability->hContainer );
		return NG;
	}

	/* データ配列の型チェック */
	if (TWTY_UINT16 != (*pp_tw_enumration)->ItemType) {
		pri_funct_err_bttvr(
	"Error : (*pp_tw_enumration)->ItemType is not TWTY_UINT16." );
		GlobalUnlock( (HANDLE)p_tw_capability->hContainer );
		GlobalFree( (HANDLE)p_tw_capability->hContainer );
		return NG;
	}

	/*
	GlobalUnlock( (HANDLE)p_tw_capability->hContainer );
	GlobalFree( (HANDLE)p_tw_capability->hContainer );
	せずに戻るので、呼び出し元で実行すること。
	*/

	return OK;
}

int tw_win_l2_dss::_cap_pri_ctnr_enum_ui16( TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_CAPABILITY tw_capability;
	TW_ENUMERATION *p_tw_enumration;
	unsigned short	*ushortp_tmp;

	long	ii;


	if (OK != this->_cap_get_ctnr_enum_ui16_not_free( ui16_cap,
	&tw_capability, &p_tw_enumration )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_enum_ui16_not_free(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	pri_funct_msg_vr(
	"%-16s 0x%04x TW_ENUM. type %u num %lu crnt %lu def %lu",
		cp_cap_name,
		ui16_cap,
		p_tw_enumration->ItemType,
		p_tw_enumration->NumItems,
		p_tw_enumration->CurrentIndex,
		p_tw_enumration->DefaultIndex
	);

	/* p_tw_enumration->ItemList[ii]は unsigned char(TW_UINT8)型
	p_tw_enumration->ItemType is 4
	#define TWTY_UINT16 0x0004
	*/
	ushortp_tmp = (unsigned short *)(p_tw_enumration->ItemList);

	pri_funct_msg_v( "\t\t\t\t" );
	for (ii = 0L; ii < (long)(p_tw_enumration->NumItems); ++ii) {
		pri_funct_msg_v( " %u", ushortp_tmp[ii] );
	}
	pri_funct_msg_v( "\n" );

	/* Windows 特有のおまじない3/3 */
	GlobalUnlock( (HANDLE)tw_capability.hContainer );
	GlobalFree( (HANDLE)tw_capability.hContainer );

	return OK;
}
