#include <stdlib.h>
#include <assert.h>
#include "pri.h"
#include "iip_scale_by_subpixel.h"

/*
	l_sx --> IN
	l_sy --> OUT
	INとOUTに対するsubpixel数を返す
*/
long iip_scale_by_subpixel::_calcu_subpixel_division( long l_sx, long l_sy )
{
	/* どちらか大きさがないときは無効 */
	if ((l_sx <= 0L) || (l_sy <= 0L)) {
		return 0L;
	}
	/* 等倍 : 大きさが等しいときはsubpixelは使わないので1を返す */
	else if (l_sx == l_sy) {
		return 1L;
	}
	/* 拡大 : l_sy(OUT)のほうが解像度高いとき */
	else if (l_sx < l_sy) {
		/* 拡大はニアレストネイバー法とする */
		return 1L;
	}

	/* 縮小 : l_sx(IN)のほうが解像度高いとき(これが主) */

	/* 縮小が整数倍のときはその比をsubpixel数として返す */
	else if (0L == (l_sx % l_sy)) {
		return l_sx / l_sy;
	}

	/* 比がmin_divを越えたら、その比をsubpixelとする */
	else if (this->_l_subpixel_min_div < (l_sx/l_sy+1L)) {
		return l_sx / l_sy + 1L;
	}
	/* 比がmin_div以下のときは、
	subpixelをmin_divに固定 */
	else {
		return this->_l_subpixel_min_div;
	}
}
void iip_scale_by_subpixel::_set_subpixel_division( void )
{
	iip_canvas *clpp;
	clpp = this->get_clp_parent();

	/* ユーザーによるsubpixel数が設定していないときは自動設定する */

	if (	(0L == this->_l_x_subpixel_division) ||
		(0L == this->_l_y_subpixel_division)) {

		/* ユーザーへの実行メッセージ */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"%s : set subpixel_division",
				this->get_ccp_object_name_of_mv()
			);
		}
	}

	if (0L == this->_l_x_subpixel_division) {
		this->_l_x_subpixel_division =
			this->_calcu_subpixel_division(
				clpp->get_l_width(),
				this->get_l_width()
			);
		/* ユーザーへのパラメータ値メッセージ */
		if (ON == this->get_i_pv_sw()) {
			pri_funct_msg_ttvr(
			" x  in %ld  out %ld  mindiv %ld  div %ld",
				clpp->get_l_width(),
				this->get_l_width(),
				this->_l_subpixel_min_div,
				this->_l_x_subpixel_division
			);
		}
	}
	if (0L == this->_l_y_subpixel_division) {
		this->_l_y_subpixel_division =
			this->_calcu_subpixel_division(
				clpp->get_l_height(),
				this->get_l_height()
			);
		/* ユーザーへのパラメータ値メッセージ */
		if (ON == this->get_i_pv_sw()) {
			pri_funct_msg_ttvr(
			" y  in %ld  out %ld  mindiv %ld  div %ld",
				clpp->get_l_height(),
				this->get_l_height(),
				this->_l_subpixel_min_div,
				this->_l_y_subpixel_division
			);
		}
	}
	/* subpixel_divisionが小さいとalloc時NULLを返す */
}

int iip_scale_by_subpixel::_mem_alloc_incr_and_accum( void )
{
	/* 以前の残りを開放 */
	this->mem_free_incr_and_accum();

	/* subpixel_divisionが指定されていなければ自動的に数値を設定 */
	this->_set_subpixel_division();

	/* Method and Parameter表示 */
	if ((ON == this->get_i_mv_sw())
	||  (ON == this->get_i_pv_sw())) {
		assert( NULL != this->get_ccp_object_name_of_mv() );
		pri_funct_msg_ttvr(
			"Alloc. %s %d bytes(%d x %d x %d)",
			this->get_ccp_object_name_of_mv(),
			this->get_l_width() *
			this->_l_x_subpixel_division *
			sizeof(long),
			this->get_l_width(),
			this->_l_x_subpixel_division,
			sizeof(long) );
	}
	/* x位置増分値配列バッファ確保 */
	this->_lp_width = (long *)calloc(
		this->get_l_width() * this->_l_x_subpixel_division,
		sizeof(long)
	);
	if (NULL == this->_lp_width) {
		pri_funct_err_bttvr(
		 "Error : calloc(%ld x %ld,%ld) return NULL",
			this->get_l_width(),
			this->_l_x_subpixel_division,
			sizeof(long) );
		return NG;
	}
	this->_l_free_incr_and_accum_width = this->get_l_width();

/*
 2000.03.11
  iip_scale_by_subpixel->exec()内、変数la_heightについては、必要の２倍のメモリをとること
   tif,rgbファイルのとき、
   無駄に多めにメモリーを確保しないと、write()時にbus errorする
  原因
   不明
   l01_image_c/との関係か？
   l01_image_c/には、他の問題を抱えているので、根本見直し必要
    rgb 16bits file r/w
    tif tile format r/w

	la_height = (long *)calloc(
		l_out_height * l_out_height_subpixel * 2, sizeof(long) );
	念のためここのコメント残す(2005.08.05)
*/
	/* Method and Parameter表示 */
	if ((ON == this->get_i_mv_sw())
	||  (ON == this->get_i_pv_sw())) {
		assert( NULL != this->get_ccp_object_name_of_mv() );
		pri_funct_msg_ttvr(
			"Alloc. %s %d bytes(%d x %d x %d)",
			this->get_ccp_object_name_of_mv(),
			this->get_l_height() *
			this->_l_y_subpixel_division *
			sizeof(long),
			this->get_l_height(),
			this->_l_y_subpixel_division,
			sizeof(long) );
	}
	/* y位置増分値配列バッファ確保 */
	this->_lp_height = (long *)calloc(
		this->get_l_height() * this->_l_y_subpixel_division,
		sizeof(long)
	);
	if (NULL == this->_lp_height) {
		pri_funct_err_bttvr(
		 "Error : calloc(%ld x %ld,%ld) return NULL",
			this->get_l_height(),
			this->_l_y_subpixel_division,
			sizeof(long) );
		this->mem_free_incr_and_accum();
		return NG;
	}
	this->_l_free_incr_and_accum_height = this->get_l_height();

	/* Method and Parameter表示 */
	if ((ON == this->get_i_mv_sw())
	||  (ON == this->get_i_pv_sw())) {
		assert( NULL != this->get_ccp_object_name_of_mv() );
		pri_funct_msg_ttvr(
			"Alloc. %s %d bytes(%d x %d x %d)",
			this->get_ccp_object_name_of_mv(),
			this->get_l_width() *
			this->get_l_channels() *
			sizeof(long),
			this->get_l_width(),
			this->get_l_channels(),
			sizeof(long) );
	}
	/* スキャンラインアキュームレション計算用バッファ確保 */
	this->_lp_scanline = (long *)calloc(
		this->get_l_width() * this->get_l_channels(),
		sizeof(long)
	);
	if (NULL == this->_lp_scanline) {
		pri_funct_err_bttvr(
		 "Error : calloc(%ld x %ld,%ld) return NULL",
			this->get_l_width(),
			this->get_l_channels(),
			sizeof(long) );
		this->mem_free_incr_and_accum();
		return NG;
	}
	this->_l_free_incr_and_accum_channels = this->get_l_channels();

	return OK;
}

void iip_scale_by_subpixel::mem_free_incr_and_accum( void )
{
	if (NULL !=  this->_lp_scanline) {
		/* Method and Parameter表示 */
		if ((ON == this->get_i_mv_sw())
		||  (ON == this->get_i_pv_sw())) {
			assert(NULL!=this->get_ccp_object_name_of_mv());
			pri_funct_msg_ttvr(
			"Free %s %d bytes(%d x %d x %d )",
			this->get_ccp_object_name_of_mv(),
			this->_l_free_incr_and_accum_width *
			this->_l_free_incr_and_accum_channels *
			sizeof(long),
			this->_l_free_incr_and_accum_width,
			this->_l_free_incr_and_accum_channels,
			sizeof(long)
			);
		}
		free(this->_lp_scanline);
		     this->_lp_scanline = NULL;
	}
	if (NULL !=  this->_lp_height) {
		/* Method and Parameter表示 */
		if ((ON == this->get_i_mv_sw())
		||  (ON == this->get_i_pv_sw())) {
			assert(NULL!=this->get_ccp_object_name_of_mv());
			pri_funct_msg_ttvr(
			"Free %s %d bytes(%d x %d x %d )",
			this->get_ccp_object_name_of_mv(),
			this->_l_free_incr_and_accum_height *
			this->_l_y_subpixel_division *
			sizeof(long),
			this->_l_free_incr_and_accum_height,
			this->_l_y_subpixel_division,
			sizeof(long)
			);
		}
		free(this->_lp_height);
		     this->_lp_height = NULL;
	}
	if (NULL !=  this->_lp_width) {
		/* Method and Parameter表示 */
		if ((ON == this->get_i_mv_sw())
		||  (ON == this->get_i_pv_sw())) {
			assert(NULL!=this->get_ccp_object_name_of_mv());
			pri_funct_msg_ttvr(
			"Free %s %d bytes(%d x %d x %d )",
			this->get_ccp_object_name_of_mv(),
			this->_l_free_incr_and_accum_width *
			this->_l_x_subpixel_division *
			sizeof(long),
			this->_l_free_incr_and_accum_width,
			this->_l_x_subpixel_division,
			sizeof(long)
			);
		}
		free(this->_lp_width);
		     this->_lp_width = NULL;
	}
}
