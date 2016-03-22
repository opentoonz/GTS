#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l2_dss.h"

void tw_win_l2_dss::_double_to_fix32(double d_val, TW_FIX32 *p_tw_fix32)
{
	TW_INT32 ui32_val;
	ui32_val = (TW_INT32)(d_val * 65536.0 + 0.5);
	p_tw_fix32->Whole = (TW_INT16)(ui32_val>>16);
	p_tw_fix32->Frac = (TW_UINT16)(ui32_val&0x0000ffffL);
}

void tw_win_l2_dss::_fix32_to_double(TW_FIX32 *p_tw_fix32, double *dp_val)
{
	*dp_val = p_tw_fix32->Whole +
		( p_tw_fix32->Frac / 65536.0);
}
