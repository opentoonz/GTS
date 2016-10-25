#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_scan_full_area_and_crop( void )
{
	// int i_max_area_sw;
	iip_canvas *clp_scan;

	/* フルエリアでスキャンを実行 */
	clp_scan = this->_iipg_scan( true/* full_area_sw */ );
	if (NULL == clp_scan) {
		pri_funct_err_bttvr(
	  "Error : this->_iipg_scan() returns NULL" );
		return;
	}

#if 0
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
#endif
	/* メイン画像のみ表示 */
	this->_wview_main();
	/* 画像表示状態をメニューに設定 */
	cl_gts_gui.menite_wview_main->setonly();

	this->rot_and_trace_and_preview_(
		clp_scan , cl_gts_gui.choice_rot90->value() , 3 , true
	);
}
