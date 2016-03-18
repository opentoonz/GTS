#include <math.h>
#include "iip_opengl_l1edit.h"

/* ズーム値を指定して、表示位置と新ズーム値を設定する */
void iip_opengl_l1edit::__set_d_zoom( double d_zoom, long l_x_pos, long l_y_pos )
{
	double	d_x,d_y;

#if defined i386_redhat9_linux2_4
	/* Redhat9のOpenGLではGL_LUMINANCEの縮小でコアダンプする */
//	if (d_zoom < 1.0) { d_zoom = 1.0; }
#endif

	/* 上下座標(l_y_pos)は左上原点なので上下反転する */
	l_y_pos = this->_l_view_y_size - 1L - l_y_pos;

	/* 画像zoom後左下原点から新zoomの中心までの距離 */
	d_x = (double)l_x_pos - (double)this->_l_xp;
	d_y = (double)l_y_pos - (double)this->_l_yp;

	/* 等倍画像左下原点から新zoomの中心までの距離 */
	d_x /= this->_d_zoom;
	d_y /= this->_d_zoom;

	/* 新しい倍率での、
	画像zoom後左下原点から新zoomの中心までの距離 */
	d_x *= d_zoom;
	d_y *= d_zoom;

	/* 画像の表示位置 */
	d_x = (double)l_x_pos - d_x;
	d_y = (double)l_y_pos - d_y;

	/* 画像の表示位置の設定 */
	this->_l_xp = (long)floor(d_x);
	this->_l_yp = (long)floor(d_y);

	/* 新zoom値の設定 */
	this->_d_zoom = d_zoom;
}

void iip_opengl_l1edit::__incr_l_zoom( void )
{
	/* 最大倍率は１６倍まで */
	if (16L <= this->_l_zoom) return;

	++this->_l_zoom;

	/* ー１かゼロのとき、１倍にリセットする */
	if ((-1 <= this->_l_zoom)
	&&        (this->_l_zoom <= 0L)) {
		   this->_l_zoom = 1L;
	}
}

void iip_opengl_l1edit::__decr_l_zoom( void )
{
#if defined i386_redhat9_linux2_4
	/* Redhat9のOpenGLではGL_LUMINANCE画像の縮小でコアダンプする */
//	if (this->_l_zoom <= 1L) return;
#endif
	/* 最小倍率は１／１６倍まで */
	if (this->_l_zoom <= -16L) return;

	--this->_l_zoom;

	/* ー１かゼロのとき、１／２倍にリセットする */
	if ((-1 <= this->_l_zoom)
	&&        (this->_l_zoom <= 0L)) {
		   this->_l_zoom = -2L;
	}
}

/*--------------------------------------------------------*/

void iip_opengl_l1edit::_decr_zoom( long l_xp, long l_yp )
{
	double	dd;

	this->__decr_l_zoom();

	if (this->_l_zoom < 0L) {
		dd = 1.0 / -(double)this->_l_zoom; }
	else {	dd =        (double)this->_l_zoom; }
	this->__set_d_zoom( dd, l_xp, l_yp );
}
void iip_opengl_l1edit::_incr_zoom( long l_xp, long l_yp )
{
	double	dd;

	this->__incr_l_zoom();

	if (this->_l_zoom < 0L) {
		dd = 1.0 / -(double)this->_l_zoom; }
	else {	dd =        (double)this->_l_zoom; }
	this->__set_d_zoom( dd, l_xp, l_yp );
}

void iip_opengl_l1edit::_zoom_twice( long l_xp, long l_yp )
{
	if (this->_l_zoom < -16L) { this->_l_zoom = -16L; }
	else if (this->_l_zoom < -8L) { this->_l_zoom = -8L; }
	else if (this->_l_zoom < -4L) { this->_l_zoom = -4L; }
	else if (this->_l_zoom < -2L) { this->_l_zoom = -2L; }
	else if (this->_l_zoom < 1L) { this->_l_zoom = 1L; }
	else if (this->_l_zoom < 2L) { this->_l_zoom = 2L; }
	else if (this->_l_zoom < 4L) { this->_l_zoom = 4L; }
	else if (this->_l_zoom < 8L) { this->_l_zoom = 8L; }
	else if (this->_l_zoom < 16L) { this->_l_zoom = 16L; }

	this->_direct_zoom( l_xp, l_yp, this->_l_zoom );
}
void iip_opengl_l1edit::_zoom_half( long l_xp, long l_yp )
{
	if (16L < this->_l_zoom) { this->_l_zoom = 16L; }
	else if (8L < this->_l_zoom) { this->_l_zoom = 8L; }
	else if (4L < this->_l_zoom) { this->_l_zoom = 4L; }
	else if (2L < this->_l_zoom) { this->_l_zoom = 2L; }
	else if (1L < this->_l_zoom) { this->_l_zoom = 1L; }
	else if (-2L < this->_l_zoom) { this->_l_zoom = -2L; }
	else if (-4L < this->_l_zoom) { this->_l_zoom = -4L; }
	else if (-8L < this->_l_zoom) { this->_l_zoom = -8L; }
	else if (-16L < this->_l_zoom) { this->_l_zoom = -16L; }

	this->_direct_zoom( l_xp, l_yp, this->_l_zoom );
}

void iip_opengl_l1edit::_direct_zoom( long l_xp, long l_yp, long l_zoom )
{
	double	dd;

	/* 最大倍率は１６倍まで */
	if (16L < l_zoom) l_zoom = 16L;
	/* 最小倍率は１／１６倍まで */
	if (l_zoom < -16L) l_zoom = -16L;
#if defined i386_redhat9_linux2_4
	/* Redhat9のOpenGLではGL_LUMINANCEの縮小でコアダンプする */
//	if (l_zoom < 1L) l_zoom = 1L;
#endif

	this->_l_zoom = l_zoom;

	if (this->_l_zoom < 0L) {
		dd = 1.0 / -(double)this->_l_zoom; }
	else {	dd =        (double)this->_l_zoom; }
	this->__set_d_zoom( dd, l_xp, l_yp );
}

void iip_opengl_l1edit::_set_zoom_x1_and_center( void )
{
	this->__set_d_zoom( 1.0, this->_l_view_x_size/2L, this->_l_view_y_size/2L );
	this->_l_zoom = 1L;
	this->_set_l_xp_center();
	this->_set_l_yp_center();
}

void iip_opengl_l1edit::_zoom_allview_and_scroll_center( void )
{
	double	d_win_s, d_s, dd;
	/* 
	 * 拡大を幅に合わせる条件の計算
	 *	xs / ys < wi / he
	 *	--> 両辺にys,heを掛ける
	 *	xs * he < wi * ys
	 *	(ただしすべてプラスの値)
	 */
	if ((this->_l_view_x_size * this->get_l_height()) <
	    (this->get_l_width() * this->_l_view_y_size)) {
		d_win_s = (double)this->_l_view_x_size;
		d_s = (double)this->get_l_width();
	} else {
		d_win_s = (double)this->_l_view_y_size;
		d_s = (double)this->get_l_height();
	}
	/* 縮小する場合 */
	if (d_win_s <= d_s) { dd = -ceil( d_s / d_win_s ); }
	/* 拡大する場合 */
	else			  { dd = floor( d_win_s / d_s ); }
#if defined i386_redhat9_linux2_4
	/* Redhat9のOpenGLではGL_LUMINANCEの縮小でコアダンプする */
//	if (dd < 1.0) dd = 1.0;
#endif
	this->_l_zoom = (long)dd;

	if (dd < 0.0) { dd = 1.0 / -dd; }
	this->__set_d_zoom( dd, this->_l_view_x_size/2L, this->_l_view_y_size/2L );

	this->_set_l_xp_center();
	this->_set_l_yp_center();

	this->_set_position();
}
