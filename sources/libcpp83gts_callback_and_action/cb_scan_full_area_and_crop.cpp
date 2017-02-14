#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_scan_full_area_and_crop( void )
{
	iip_canvas *clp_scan;

	/* フルエリアでスキャンを実行 */
	int return_code=NG;
	clp_scan = this->iipg_scan( return_code ,true/* full_area_sw */ );
	if (return_code == NG) {
		pri_funct_err_bttvr(
	  "Error : this->iipg_scan() returns NG" );
		return;
	}
	if (return_code == CANCEL) {
		return;
	}
	if (nullptr == clp_scan) {
		pri_funct_err_bttvr(
	  "Error : this->iipg_scan() returns nullptr" );
		return;
	}

	/* スキャンした画像とCropエリアの表示 */
	this->rot_and_trace_and_enoise_and_preview(
		clp_scan ,cl_gts_gui.choice_rot90->value() ,true ,true
	);

	/* CropしたときAreaが数値と違う問題の暫定解決のため以下入れる!!! */
	/* 初期値は物理的最大範囲 */
	if (cl_gts_gui.valinp_area_x_pos->value() == 0
	&&  cl_gts_gui.valinp_area_y_pos->value() == 0
	&&  cl_gts_gui.valinp_area_x_size->value() == 0
	&&  cl_gts_gui.valinp_area_y_size->value() == 0
	) {
	    cl_gts_gui.valinp_area_y_size->value(
	    	this->cl_iip_scan.d_physical_height()
	    );
	    cl_gts_gui.valinp_area_x_size->value(
	    	this->cl_iip_scan.d_physical_width()
	    );
	}
	/* GUI数値を画像表示ルーチンにセット */
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
