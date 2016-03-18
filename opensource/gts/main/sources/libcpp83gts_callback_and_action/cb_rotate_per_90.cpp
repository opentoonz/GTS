#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/* メニューの回転値に合わせて回転処理をおこなう */
int gts_master::rotate_per_90( void )
{
	int i_rot90_old, i_rot90_new;

	/* 古い値と新しい値を得る */
	i_rot90_old = this->_i_rotate_per_90;
	i_rot90_new = cl_gts_gui.choice_rot90->value();

	/* メニューの指定が回転してないときはなにもしない */
	if (i_rot90_old == i_rot90_new) { return OK; }

	if (ON == this->i_mv_sw()) {
		pri_funct_msg_ttvr(
			"gts_master::rotate_per_90(-)");
	}

	/*
	 * パラメータ値の回転(必ず両方実行する)
	 */

	/* areaの値を回転する */
	this->_area_rot90_menu( i_rot90_old, i_rot90_new );

	/* opengl rect値を回転する(必ず(view)画像の回転の前に行なう) */
	//this->_area_rot90_openglrect( i_rot90_old, i_rot90_new );

	/* 回転の現在値をメモリする */
	this->_i_rotate_per_90 = i_rot90_new;

	/*
	 * 画像あれば回転処理し表示する
	 */

	if (	(NULL != this->cl_iip_ro90.get_clp_parent()) &&
		(NULL != this->cl_iip_ro90.get_vp_canvas())
	) {
		/* 回転処理を実行 */
		if (OK != this->_iipg_rot90(
			this->cl_iip_ro90.get_clp_parent(),
			i_rot90_new
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_rot90(-) returns NG" );
			return NG;
		}

		/* 表示 */
		if (OK != this->_iipg_view_setup(-1)) {
			pri_funct_err_bttvr(
		 "Error : this->_iipg_view_setup(-) returns NG" );
			return NG;
		}
		this->_iipg_view_redraw();
	}

	/* menuからopengl rect値をセットする
	(直接回転しても値がリセットしてしまうための暫定措置) */
	this->_from_area_val_to_opengl_rect();

	return OK;
}
void gts_master::cb_rotate_per_90( void )
{
	if (OK != this->rotate_per_90()) {
		pri_funct_err_bttvr(
	 "Error : this->rotate_per_90() returns NG" );
	}
}
