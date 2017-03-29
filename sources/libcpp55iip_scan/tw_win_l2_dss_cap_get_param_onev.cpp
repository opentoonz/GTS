#include <iostream>
#include <iomanip> // std::setprecision(std::numeric_limits<double>::max_digits10)
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::cap_get_dp_x_native_resolution( double *dp_x_native_res )
{
	return this->_cap_get_ctnr_onevalue_fix32(
		  dp_x_native_res,
		 ICAP_XNATIVERESOLUTION,
		"ICAP_XNATIVERESOLUTION" );
}

int tw_win_l2_dss::cap_get_dp_y_native_resolution( double *dp_y_native_res )
{
	return this->_cap_get_ctnr_onevalue_fix32(
		  dp_y_native_res,
		 ICAP_YNATIVERESOLUTION,
		"ICAP_YNATIVERESOLUTION" );
}

/* 接続スキャナに対応する最大取り込み幅 */
int tw_win_l2_dss::cap_get_dp_physical_width( double *dp_width )
{
	return this->_cap_get_ctnr_onevalue_fix32(
			   dp_width,
		 ICAP_PHYSICALWIDTH,
		"ICAP_PHYSICALWIDTH" );
}

/* 最大高さ */
/*int tw_win_l2_dss::cap_get_dp_physical_height( double *dp_height )
{
	return this->_cap_get_ctnr_onevalue_fix32(
			   dp_height,
		 ICAP_PHYSICALHEIGHT,
		"ICAP_PHYSICALHEIGHT" );
}*/
// Debug patch follow...
// for EPSON Scan 5.3.1.4 for DS-50000
int tw_win_l2_dss::cap_get_dp_physical_height( double *dp_height )
{
	int ret = this->_cap_get_ctnr_onevalue_fix32(
			   dp_height,
		 ICAP_PHYSICALHEIGHT,
		"ICAP_PHYSICALHEIGHT" );

	/*
	EPSON Scan v5.3.1.4でICAP_PHYSICALHEIGHTが254を返す問題の対処
	EPSON Scan v5.3.1.5で43.180007934570313を返すようになった
	*/
	if (43.18001 < *dp_height)
	{
		std::cout
			<< "Warning"
			<< " " << __FILE__
			<< " " << __FUNCTION__
			<< " line=" << __LINE__
			<< " physical_height="
	<< std::setprecision(std::numeric_limits<double>::max_digits10)
			<< *dp_height;
		*dp_height = 43.18;
		std::cout
			<< "->"
	<< std::setprecision(std::numeric_limits<double>::max_digits10)
			<< *dp_height
			<< std::endl;
	}

	return ret;
}

/* UI非表示でスキャンの可否を示します。
TRUE==tw_onevalue.Itemが返ると、UIサプレスモードでの動作が可能、
つまり、TW_USERINTERFACE.ShowUIをFALSEに設定することが可能である
*/
int tw_win_l2_dss::cap_get_lp_uicontrollable_sw( long *lp_bool )
{
	int	i_ret;
	TW_UINT32	ui32_val;

	i_ret = this->_cap_get_ctnr_onevalue_bool(
		&ui32_val,
		 CAP_UICONTROLLABLE,
		"CAP_UICONTROLLABLE" );
	if (TRUE == ui32_val) { *lp_bool = ON; }
	else                  { *lp_bool = OFF; }
	return i_ret;
}

/*----------------------------------------------------------*/

int tw_win_l2_dss::cap_getcrnt_lp_xfermech( long *lp_xfermech )
{
	TW_UINT16 ui16_val;
	int i_ret;

	i_ret = this->_cap_getcrnt_ctnr_onevalue_ui16(
		  &ui16_val,
		 ICAP_XFERMECH,
		"ICAP_XFERMECH" );

	*lp_xfermech = ui16_val;
	return i_ret;
}
