#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::imagelayout_set_d_area( double d_lef, double d_rig, double d_bot, double d_top )
{
	TW_IMAGELAYOUT tw_imagelayout;

	if (OK != this->_imagelayout_get( &tw_imagelayout )) {
		pri_funct_err_bttvr(
	 "Error : this->_imagelayout_get() returns NG." );
		return NG;
	}

	this->_double_to_fix32( d_lef,&(tw_imagelayout.Frame.Left) );
	this->_double_to_fix32( d_rig,&(tw_imagelayout.Frame.Right) );
	this->_double_to_fix32( d_bot,&(tw_imagelayout.Frame.Bottom) );
	this->_double_to_fix32( d_top,&(tw_imagelayout.Frame.Top) );

	if (OK != this->_imagelayout_set( &tw_imagelayout )) {
		pri_funct_err_bttvr(
	 "Error : this->_imagelayout_set() returns NG." );
		return NG;
	}

	return OK;
}
