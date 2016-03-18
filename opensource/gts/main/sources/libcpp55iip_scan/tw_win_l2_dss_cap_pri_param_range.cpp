#include "tw_win_l2_dss.h"

int tw_win_l2_dss::cap_pri_brightness( void )
{
	return this->_cap_pri_ctnr_range(
		 ICAP_BRIGHTNESS,
		"ICAP_BRIGHTNESS" );
}

int tw_win_l2_dss::cap_pri_contrast( void )
{
	return this->_cap_pri_ctnr_range(
		 ICAP_CONTRAST,
		"ICAP_CONTRAST" );
}

int tw_win_l2_dss::cap_pri_xresolution( void )
{
	return this->_cap_pri_ctnr_range(
		 ICAP_XRESOLUTION,
		"ICAP_XRESOLUTION" );
}
int tw_win_l2_dss::cap_pri_yresolution( void )
{
	return this->_cap_pri_ctnr_range(
		 ICAP_YRESOLUTION,
		"ICAP_YRESOLUTION" );
}

int tw_win_l2_dss::cap_pri_threshold( void )
{
	return this->_cap_pri_ctnr_range(
		 ICAP_THRESHOLD,
		"ICAP_THRESHOLD" );
}
