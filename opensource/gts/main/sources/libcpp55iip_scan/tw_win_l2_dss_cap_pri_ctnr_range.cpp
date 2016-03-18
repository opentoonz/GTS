#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::_cap_pri_ctnr_range( TW_UINT16 ui16_cap, char *cp_cap_name )
{
	short	s_MinValue,
		s_MaxValue,
		s_StepSize,
		s_DefaultValue,
		s_CurrentValue;
	TW_RANGE tw_range;

	if (OK != this->_cap_get_ctnr_range( ui16_cap, &tw_range )) {
		pri_funct_err_bttvr(
	 "Error : this->_cap_get_ctnr_range(%s<%u>,) returns NG.",
			cp_cap_name,
			ui16_cap
		);
		return NG;
	}

	/* tw_range.MinValue,...tw_range.CurrentValueは
	unsigned long(TW_UINT32)型だが、
	tw_range.MinValueはマイナスの時があるので、
	強制的にlongとして扱う
	*/
	s_MinValue = (short)(tw_range.MinValue);
	s_MaxValue = (short)(tw_range.MaxValue);
	s_StepSize = (short)(tw_range.StepSize);
	s_DefaultValue = (short)(tw_range.DefaultValue);
	s_CurrentValue = (short)(tw_range.CurrentValue);
	pri_funct_msg_vr(
	"%-16s 0x%04x TW_RANGE type %u min %d max %d step %d def %d crnt %d",
		cp_cap_name,
		ui16_cap,
		tw_range.ItemType,
		s_MinValue,
		s_MaxValue,
		s_StepSize,
		s_DefaultValue,
		s_CurrentValue
	);

	return OK;
}
