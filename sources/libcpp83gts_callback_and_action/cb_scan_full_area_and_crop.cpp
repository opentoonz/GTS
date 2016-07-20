#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_scan_full_area_and_crop( void )
{
	// int i_max_area_sw;
	iip_canvas *clp_scan;

	/* フルエリアでスキャンを実行 */
	cl_gts_gui.valinp_area_x_size->value(0.0);
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

	/* 画像(Crop枠も同時に)表示 */
	if (OK != this->_iipg_view_setup( ON )) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_view_setup(-) returns NG" );
		return;
	}
	this->iipg_view_redraw_();
}
