#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

static bool while_scan_sw_=false;
void gts_master::cb_scan_and_preview( void )
{
	/* ショートカット動作のとき、連続してキーインしたときの誤動作防止 */
	/* マルチスレッドに非対応 */
	if ( while_scan_sw_ == true ) { return; }
	while_scan_sw_ = true;

	/* スキャンを実行 */
	int return_code=NG;
	iip_canvas* clp_scan = this->iipg_scan( return_code );
	if (return_code == NG) {
		pri_funct_err_bttvr(
		      "Error : this->iipg_scan() returns NG" );
		while_scan_sw_ = false;
		return;
	}
	if (return_code == CANCEL) {
		while_scan_sw_ = false;
		return;
	}
	if (NULL == clp_scan) {
		pri_funct_err_bttvr(
		      "Error : this->iipg_scan() returns NULL" );
		while_scan_sw_ = false;
		return;
	}

	this->rot_and_trace_and_enoise_and_preview(
		clp_scan
		, cl_gts_gui.choice_rot90->value()
	);

	/* Crop以外の画像表示をした場合 */
	this->cl_area_and_rot90.reset_dpi_to_zero_by_scan_or_preview();

	/* Trace --> Scan モードに自動切替 */
	this->cl_scan_and_save.cb_set_number();

	while_scan_sw_ = false;
}
