#include "tw_win_l2_dss.h"

int tw_win_l2_dss::cap_pri_gamma( void )
{
	return this->_cap_pri_ctnr_onevalue_fix32(
		 ICAP_GAMMA,
		"ICAP_GAMMA" );
}

int tw_win_l2_dss::cap_pri_indicators( void )
{
	return this->_cap_pri_ctnr_onevalue_bool(
		 CAP_INDICATORS,
		"CAP_INDICATORS" );
}
