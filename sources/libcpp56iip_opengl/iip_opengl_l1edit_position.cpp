#include <math.h>
#include "pri.h"
#include "iip_opengl_l1edit.h"

/*
this->_l_view_x_size
this->_l_view_y_size
this->get_l_width()
this->get_l_height()
this->_l_xp
this->_l_yp
this->_d_zoom
から、
以下のOpenGL表示用パラメータをセットする
+-----------------------------------------------------------+
|                                                           |
|<----------------- <this->get_l_width()> ----------------->|
|                                                           |
|                         画像全体                          |
|                                                           |
|                  +----------------------+        _d_scrollbar_y_min
|                  |                 ^    |                 |
|                  |      表示部分   |    |                 |
|                  |                 |    |                 |
|                  |   _glsi_width   |    |                 |
|                  |<----------------+--->|                 |
|                  |                 |    |                 |
|                  |    _glsi_height |    |                 |
| _gli_skip_pixels |                 v    |                 |
|<---------------> +----------------------+        _d_scrollbar_y_min
|                  ^\                                       |
|                  | +--> 表示上の位置                      |
|                  |    (_gli_rasterpos_x,_gli_rasterpos_y) |
|                  | _gli_skip_rows                         |
|                  |                                        |
|                  v                                        |
+-----------------------------------------------------------+
^\                 ^                      ^
  \                |                      |
   \        _d_scrollbar_x_min     _d_scrollbar_x_max
    \
     \
      +--> <this->_l_xp,this->_l_yp>

memo 2005.05.09.mon
拡大表示(x2,x3,x4,...,x16)の時で、
gli_rasterpos_x,あるいはgli_rasterpos_yが、
拡大値の等倍でないマイナス値のとき表示しない。
拡大値の等倍でないプラス値は表示する。
memo 2005.05.13.fri
つまり、gli_rasterpos_x,gli_rasterpos_yが、
glViewport()の範囲に入っていないと
表示は消えてしまう→表示枠外に余白をとることで対処
memo 2005.05.18.thu
this->get_l_width()が、_gli_skip_pixels + _glsi_widthと等しく、かつ、
this->get_l_height()が、_gli_skip_rows + _glsi_heightと等しくないと、
WindowsXpのOpenGLではhang upする、Redhat9では動作してしまう。
*/
void iip_opengl_l1edit::_set_position( void )
{
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "iip_opengl_l1edit::_set_position(-)" );
	}

	this->_glsi_width = (GLsizei)this->get_l_width();
	this->_glsi_height = (GLsizei)this->get_l_height();
	this->_gli_skip_pixels = (GLint)0;
	this->_gli_skip_rows = (GLint)0;

	/* OpenGL縮小表示(zoom<1)は処理後画像として等倍表示(zoom=1)する */
	const double disp_zoom = this->_d_zoom < 1.0 ?1.0 : this->_d_zoom;

	/* 左側は表示範囲内 */
	if (0L <= this->_l_xp) {
		/* 右側が表示をはみ出す(表示寸) */
		if (	(double)this->_l_view_x_size < (
				(double)this->_l_xp +
				floor(	(double)this->get_l_width() *
					disp_zoom
				)
			)
		) {
			/* 表示する画像幅(実寸) */
			/* 端数のpixelも表示する */
			this->_glsi_width = (GLsizei)ceil(
				(double)(this->_l_view_x_size-this->_l_xp) /
				disp_zoom
				);
		}
		/* 右側が表示範囲内 */ /* 初期位置で表示 */
	}
	/* 左側は表示をはみ出す */
	else {
		this->_gli_skip_pixels = (GLint)floor(
			(double)(-this->_l_xp) / disp_zoom
		);
		/* 右側が表示をはみ出す
			(表示寸)(左右両側が表示をはみ出す) */
		if (	(double)this->_l_view_x_size < (
				(double)this->_l_xp +
				floor(	(double)this->get_l_width() *
					disp_zoom
				)
			)
		) {
			/* 左右両側がはみ出すときは1pixel分大きく表示 */
			this->_glsi_width = (GLsizei)ceil(
				(double)this->_l_view_x_size / disp_zoom
			);
		}
		/* 右側が表示範囲内 */
		else {
			this->_glsi_width =
			 this->get_l_width() - this->_gli_skip_pixels;
		}
	}

	/* 下は表示範囲内 */
	if (0L <= this->_l_yp) {
		/* 上側が表示をはみ出す(表示寸) */
		if (	(double)this->_l_view_y_size < (
				(double)this->_l_yp +
				floor(	(double)this->get_l_height() *
					disp_zoom
				)
			)
		) {
			/* 表示する画像高さ(実寸) */
			/* 端数のpixelも表示する */
			this->_glsi_height = (GLsizei)ceil(
				(double)(this->_l_view_y_size-this->_l_yp) /
				disp_zoom
				);
		}
		/* 上側が表示範囲内 */ /* 初期位置で表示 */
	}
	/* 下は表示をはみ出す */
	else {
		this->_gli_skip_rows = (GLint)floor(
			(double)(-this->_l_yp) / disp_zoom
		);
		/* 上側が表示をはみ出す
			(表示寸)(上下両側が表示をはみ出す) */
		if (	(double)this->_l_view_y_size < (
				(double)this->_l_yp +
				floor(	(double)this->get_l_height() *
					disp_zoom
				)
			)
		) {
			/* 上下両側がはみ出すときは1pixel分大きく表示 */
			this->_glsi_height = (GLsizei)ceil(
				(double)this->_l_view_y_size / disp_zoom
			);
		}
		/* 上側が表示範囲内 */
		else {
			this->_glsi_height =
			 this->get_l_height() - this->_gli_skip_rows;
		}
	}

	/* 画像の表示開始位置 */
	this->_gli_rasterpos_x = this->_l_xp;
	this->_gli_rasterpos_y = this->_l_yp;

	/* 左右Crop表示時の横始点(左)位置 */
	if (this->_gli_rasterpos_x < 0L) {
		/* ゼロより大きいときはスムーススクロール */
		if (0L < this->_l_margin_for_zoomup_smooth_scroll) {
		 /* 拡大表示の場合、表示上のPixel位置へ */
		 if (1L < this->_l_zoom) {
			this->_gli_rasterpos_x %= this->_l_zoom;
			if (this->_glsi_width <
			(this->get_l_width() - this->_gli_skip_pixels)){
				++this->_glsi_width;
			}
		 }
		 /* 等倍か縮小表示の場合Cropの開始位置をゼロに指定 */
		 else {
			this->_gli_rasterpos_x = 0L;
		 }
		}
		/* ゼロだと、データ上の1Pixel毎スクロール */
		else {
			this->_gli_rasterpos_x = 0L;
		}
	}

	/* 上下Crop表示時の縦始点(下)位置 */
	if (this->_gli_rasterpos_y < 0L) {
		/* ゼロより大きいときはスムーススクロール */
		if (0L < this->_l_margin_for_zoomup_smooth_scroll) {
		 /* 拡大表示の場合、表示上のPixel位置へ */
		 if (1L < this->_l_zoom) {
			this->_gli_rasterpos_y %= this->_l_zoom;
			if (this->_glsi_height <
			(this->get_l_height() - this->_gli_skip_rows)){
				++this->_glsi_height;
			}
		 }
		 /* 等倍か縮小表示の場合Cropの開始位置をゼロに指定 */
		 else {
			this->_gli_rasterpos_y = 0L;
		 }
		}
		/* ゼロだと、データ上の1Pixel毎スクロール */
		else {
			this->_gli_rasterpos_y = 0L;
		}
	}

//this->_glsi_width  = this->_glsi_width  / 2L - this->_gli_rasterpos_x;
//this->_glsi_height = this->_glsi_height / 2L - this->_gli_rasterpos_y;

	/*
	 * スクロールバーの表示用設定
	 */

	/* 左位置 */
	this->_d_scrollbar_x_min =
		(double)(-this->_l_xp) /
		ceil((double)this->get_l_width() * disp_zoom);
	/******if (this->_d_scrollbar_x_min < 0.0)
	{   this->_d_scrollbar_x_min = 0.0; }******/

	/* 右位置 */
	this->_d_scrollbar_x_max =
		(double)(-this->_l_xp + this->_l_view_x_size) /
		ceil((double)this->get_l_width() * disp_zoom);
	/******if (1.0 < this->_d_scrollbar_x_max)
	{   this->_d_scrollbar_x_max = 1.0; }******/

	/* 下位置 */
	this->_d_scrollbar_y_min =
		(double)(-this->_l_yp) /
		ceil((double)this->get_l_height() * disp_zoom);
	/******if (this->_d_scrollbar_y_min < 0.0)
	{   this->_d_scrollbar_y_min = 0.0; }******/

	/* 上位置 */
	this->_d_scrollbar_y_max =
		(double)(-this->_l_yp + this->_l_view_y_size) /
		ceil((double)this->get_l_height() * disp_zoom);
	/******if (1.0 < this->_d_scrollbar_y_max)
	{   this->_d_scrollbar_y_max = 1.0; }******/

	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_vr( " x min %.16g max %.16g",
			this->_d_scrollbar_x_min,
			this->_d_scrollbar_x_max
		);
		pri_funct_msg_vr( " y min %.16g max %.16g",
			this->_d_scrollbar_y_min,
			this->_d_scrollbar_y_max
		);
	}
}
