#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::imagelayout_pri_all( void )
{
	TW_IMAGELAYOUT tw_imagelayout;

	if (OK != this->_imagelayout_get( &tw_imagelayout )) {
		pri_funct_err_bttvr(
	 "Error : this->_imagelayout_get(-) returns NG" );
		return NG;
	}
	this->_imagelayout_pri( &tw_imagelayout );

	return OK;
}
