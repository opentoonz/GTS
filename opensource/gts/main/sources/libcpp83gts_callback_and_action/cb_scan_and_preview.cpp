#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_scan_and_preview( void )
{
	iip_canvas *clp_scan;

	/* スキャンを実行 */
	clp_scan = this->_iipg_scan();
	if (NULL == clp_scan) {
		pri_funct_err_bttvr(
	  "Error : this->_iipg_scan() returns NULL" );
		return;
	}

	/* 回転処理を実行 */
	if (OK != this->_iipg_rot90(
		clp_scan,
		cl_gts_gui.choice_rot90->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_rot90(-) returns NG" );
		return;
	}

	/* 表示 */
	if (OK != this->_iipg_view_setup()) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup() returns NG" );
		return;
	}
	this->_iipg_view_redraw();
}
