#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

int gts_master::_iipg_view_setup( int i_max_area_sw )
{
	int	i_sw;

	/* 大きさの違う画像を表示するのか? */
	i_sw = OFF;
	if (
	(0 == this->cl_ogl_view.is_main_canvas()) ||
	(this->cl_ogl_view.get_l_width() !=
	 this->cl_iip_ro90.get_l_width()) ||
	(this->cl_ogl_view.get_l_height() !=
	 this->cl_iip_ro90.get_l_height())
	) {
		i_sw = ON;
	}

	/* 親子接続、画像大きさ、表示チャンネル(R,G,B,A,RGB)設定 */
	if (OK != this->cl_ogl_view.set_imagedata(
		&(this->cl_iip_ro90), &(this->cl_iip_trac)
	)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_ogl_view.set_imagedata(-) returns NG" );
		return NG;
	}

	/* 最大サイズの場合切抜きをするのでON、それ以外はOFF */
	if (ON == i_max_area_sw) {
		this->cl_ogl_view.set_crop_disp_sw(ON);
	} else if (OFF == i_max_area_sw) {
		this->cl_ogl_view.set_crop_disp_sw(OFF);
	}/* ONでもOFFでもないとき(-1)はなにもしない-->以前の状態 */

	/* 始めて、あるいは大きさの違う画像を表示するときは */
	if (ON == i_sw) {
		/* Viewport, orth2d, 画像データとのパラメータ計算 */
		this->cl_ogl_view.reshape_opengl(
			cl_gts_gui.opengl_view->w(),
			cl_gts_gui.opengl_view->h()
		);

		/* OpenGL表示エリアの設定、フルサイズ表示の設定 */
		this->cl_ogl_view.init_viewparam(
			cl_gts_gui.opengl_view->w(),
			cl_gts_gui.opengl_view->h()
		);

		/* スクロールバー */
		this->set_scrollbar();

		/* zoom値表示 */
		this->print_window_headline();
	}

	return OK;
}
