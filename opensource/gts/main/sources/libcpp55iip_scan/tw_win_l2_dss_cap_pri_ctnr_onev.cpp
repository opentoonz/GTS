#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_cap_pri_ctnr_onevalue_bool( TW_UINT16 ui16_cap, char *cp_cap_name )
{
	TW_ONEVALUE tw_onevalue;

	if (OK != this->_cap_get_ctnr_onevalue( ui16_cap, &tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	pri_funct_msg_vr(
	"%-16s 0x%04x TW_ONEV. type %u item %lu",
		cp_cap_name,
		ui16_cap,
		tw_onevalue.ItemType,
		tw_onevalue.Item
	);

	return OK;
}

int tw_win_l2_dss::_cap_pri_ctnr_onevalue_fix32( TW_UINT16 ui16_cap, char *cp_cap_name )
{
	double	d_val;
	TW_ONEVALUE tw_onevalue;

	if (OK != this->_cap_get_ctnr_onevalue( ui16_cap, &tw_onevalue )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_onevalue(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	this->_fix32_to_double(
		(TW_FIX32 *)&(tw_onevalue.Item), &d_val );

	pri_funct_msg_vr(
	"%-16s 0x%04x TW_ONEV. type %u item %.16g",
		cp_cap_name,
		ui16_cap,
		tw_onevalue.ItemType,
		d_val
	);

	return OK;
}
