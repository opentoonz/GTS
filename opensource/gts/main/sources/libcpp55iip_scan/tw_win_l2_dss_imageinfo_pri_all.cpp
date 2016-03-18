#include "pri.h"
#include "tw_win_l2_dss.h"

int tw_win_l2_dss::imageinfo_pri_all( void )
{
	TW_IMAGEINFO tw_imageinfo;

	if (OK != this->_imageinfo_get( &tw_imageinfo )) {
		pri_funct_err_bttvr(
	 "Error : this->_get_imageinfo(-) returns NG" );
		return NG;
	}
	this->_imageinfo_pri( &tw_imageinfo );

	return OK;
}
