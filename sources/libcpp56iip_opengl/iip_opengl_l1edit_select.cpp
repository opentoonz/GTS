#include <math.h>
#include "pri.h"
#include "iip_opengl_l1edit.h"

/* マウスが動いているとき常時選択動作する */
/* 変化があったとき(選択しなくなったときも含めて)ONを戻す */
int iip_opengl_l1edit::_select( long l_xp, long l_yp )
{
	E_SELECT_PART	e_select_part;
	int	i_ret;

	/* マウスは左上原点、ここでは左下原点 */
	l_yp = this->_l_view_y_size - 1L - l_yp;
	/* 初期値 */
	e_select_part = E_SELECT_NOTHING;

	/* 切抜き編集が有効なら切抜きエリア選択 */
	if (ON == this->_i_crop_disp_sw) {
	 e_select_part = this->_selection_crop_picker( l_xp, l_yp );
	}

	/* 切抜き隅エリア以外は、強制的に画像を選ぶ */
	if (E_SELECT_NOTHING == e_select_part) {
		e_select_part = E_SELECT_IMAGE;
	}

	/* 変化したときはONを返す */
	if (this->_e_select_part != e_select_part) {
		i_ret = ON;
	} else {i_ret = OFF;}

	/* 新しい値を設定 */
	this->_e_select_part = e_select_part;

	return i_ret;
}

namespace {
 bool in_rect_area_(
	const double xp ,const double yp
	,const double x1 ,const double y1
	,const double x2 ,const double y2
 ) {
	if ( (x1<=xp) && (xp<=x2) && (y1<=yp) && (yp<=y2) ) { return true; }
	return false;
 }
 bool in_point_area_(
	const double xp ,const double yp
	,const double xc ,const double yc ,const double ra/* radius */
 ) {
	return in_rect_area_( xp ,yp ,xc-ra ,yc-ra ,xc+ra ,yc+ra );
 }
 E_SELECT_PART select_for_crop_(
	const double xp ,const double yp
	,const double x1 ,const double y1
	,const double x2 ,const double y2 ,const double ra/* radius */
 ) {
	const double xc = (x1 + x2) / 2.0;
	const double yc = (y1 + y2) / 2.0;
	if (in_point_area_(xp,yp,x1,y1,ra)) { return E_SELECT_LEFTBOTTOM; }
	if (in_point_area_(xp,yp,x1,yc,ra)) { return E_SELECT_LEFT; }
	if (in_point_area_(xp,yp,x1,y2,ra)) { return E_SELECT_LEFTTOP; }
	if (in_point_area_(xp,yp,xc,y2,ra)) { return E_SELECT_TOP; }
	if (in_point_area_(xp,yp,x2,y2,ra)) { return E_SELECT_RIGHTTOP; }
	if (in_point_area_(xp,yp,x2,yc,ra)) { return E_SELECT_RIGHT; }
	if (in_point_area_(xp,yp,x2,y1,ra)) { return E_SELECT_RIGHTBOTTOM; }
	if (in_point_area_(xp,yp,xc,y1,ra)) { return E_SELECT_BOTTOM; }
	if (in_point_area_(xp,yp,xc,yc,ra)) { return E_SELECT_CENTER; }
	return E_SELECT_NOTHING;
 }
}
E_SELECT_PART iip_opengl_l1edit::_selection_crop_picker( long xp,long yp ) {
	double	x1 ,y1 ,x2 ,y2;

	this->_get_crop_disp_area(
		(double)(this->_l_xp),
		(double)(this->_l_yp),
		(double)(this->_l_crop_xp),
		(double)(this->_l_crop_yp),
		(double)(this->_l_crop_width),
		(double)(this->_l_crop_height),
		&x1, &y1, &x2, &y2
	);

	return select_for_crop_(
		xp ,yp, x1, y1, x2, y2 ,this->_l_crop_select_radius
	);
}
