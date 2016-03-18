#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/* メモリは、
なければ新規確保、大きさが同じなら流用、違うなら再確保する */
int gts_master::_iipg_rot90( iip_canvas *clp_parent, int i_rotate_per_90 )
{
	iip_rot90 *clp_ro90;
	long	l_sz_ro90_old, l_sz_ro90_new;

	if (ON == this->i_mv_sw()) {
		pri_funct_msg_ttvr( "gts_master::_iipg_rot90(-)" );
	}

	/* 画像処理用class */
	clp_ro90 = &(this->cl_iip_ro90);

	/* 接続先(scan or read)は変更する場合あるのでここでセット */
	clp_ro90->set_clp_parent(clp_parent);

	/* いままでの画像メモリの大きさ */
	l_sz_ro90_old =	clp_ro90->get_l_height() *
			clp_ro90->get_l_channels() *
			clp_ro90->get_l_scanline_channel_bytes();

	/* 親のサイズを元に設定をしなおし... */
	clp_ro90->set_canvas_size(clp_parent);

	/* ...回転角度を設定し... */
	switch (i_rotate_per_90) {
	case 0: clp_ro90->set_clockwork_000(); break;
	case 1: clp_ro90->set_clockwork_090(); break;
	case 2: clp_ro90->set_clockwork_180(); break;
	case 3: clp_ro90->set_clockwork_270(); break;
	}

	/* ...値を回転する */
	this->cl_iip_ro90.rot_canvas_size();

	/* 回転したあとの画像メモリの大きさ */
	l_sz_ro90_new =	clp_ro90->get_l_height() *
			clp_ro90->get_l_channels() *
			clp_ro90->get_l_scanline_channel_bytes();

	/* 必要な大きさが以前と違う場合はメモリ確保しなおし */
	if (l_sz_ro90_old != l_sz_ro90_new) {
		/* メモリの取りなおし */
		if (OK != this->cl_iip_ro90.mem_alloc_canvas()) {
			pri_funct_err_bttvr(
	"Error : this->cl_iip_ro90.mem_alloc_canvas() returns NG" );
			return NG;
		}
	}

	/* 回転実行 */
	this->cl_iip_ro90.exec();

	return OK;
}
