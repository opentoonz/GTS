#include "tw_win_l2_dss.h"

int tw_win_l2_dss::cap_pri_units( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_UNITS,
		"ICAP_UNITS" );
}

int tw_win_l2_dss::cap_pri_xfermech( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_XFERMECH,
		"ICAP_XFERMECH" );
}

int tw_win_l2_dss::cap_pri_pixeltype( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_PIXELTYPE,
		"ICAP_PIXELTYPE" );
}

/* 各色チャンネルあたりのビット長を表示する。
値は接続したスキャナーに依存します。

たとえば、48ビットカラー出力可能な機種では、1,8,16が、
36ビットカラー出力機種では、1,8,12となります。
*/
int tw_win_l2_dss::cap_pri_bitdepth( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_BITDEPTH,
		"ICAP_BITDEPTH" );
}

int tw_win_l2_dss::cap_pri_orientation( void )
{
	return this->_cap_pri_ctnr_enum_ui16(
		 ICAP_ORIENTATION,
		"ICAP_ORIENTATION" );
}
