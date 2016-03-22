#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

/*---------------------------------------------------------*/

/* 位置と大きさを回転する
位置を回転するとき大きさ情報も必要なため位置だけを回転する関数はできない
関数のオーバーロード機能により引数が全てdoubleの場合とlongの場合で使う
*/
void gts_master::__area_rot90_d_pos_and_size( int i_rot90, double d_x, double d_y, double d_w, double d_h, double d_max_w, double d_max_h, double *dp_x, double *dp_y, double *dp_w, double *dp_h )
{
	/* マイナス回転はプラスにする
		i_rot90の値(回転差)は、
		-3(-270=90) =1,
		-2(-180=180) =2,
		-1(-90=270) =3,
		 0(0),
		 1(90),
		 2(180),
		 3(270)
	*/
	if (i_rot90 < 0) {
		i_rot90 += 4;
	}

	/* 左上原点で計算 */
	switch (i_rot90) {
	case 0: // 0 degree clock works
		*dp_x = d_x;
		*dp_y = d_y;
		*dp_w = d_w;
		*dp_h = d_h;
		break;
	case 1: // 90 degree clock works
		*dp_x = d_max_h - (d_y + d_h);
		*dp_y = d_x;
		*dp_w = d_h;
		*dp_h = d_w;
		break;
	case 2: // 180 degree clock works
		*dp_x = d_max_w - (d_x + d_w);
		*dp_y = d_max_h - (d_y + d_h);
		*dp_w = d_w;
		*dp_h = d_h;
		break;
	case 3: // 270 degree clock works
		*dp_x = d_y;
		*dp_y = d_max_w - (d_x + d_w);
		*dp_w = d_h;
		*dp_h = d_w;
		break;
	}
}

void gts_master::__area_rot90_l_pos_and_size( int i_rot90, long l_x, long l_y, long l_w, long l_h, long l_max_w, long l_max_h, long *lp_x, long *lp_y, long *lp_w, long *lp_h )
{
	/* マイナス回転はプラスにする
		i_rot90の値(回転差)は、
		-3(-270=90) =1,
		-2(-180=180) =2,
		-1(-90=270) =3,
		 0(0),
		 1(90),
		 2(180),
		 3(270)
	*/
	if (i_rot90 < 0) {
		i_rot90 += 4;
	}

	/* 左上原点で計算 */
	switch (i_rot90) {
	case 0: // 0 degree clock works
		*lp_x = l_x;
		*lp_y = l_y;
		*lp_w = l_w;
		*lp_h = l_h;
		break;
	case 1: // 90 degree clock works
		*lp_x = l_max_h - (l_y + l_h);
		*lp_y = l_x;
		*lp_w = l_h;
		*lp_h = l_w;
		break;
	case 2: // 180 degree clock works
		*lp_x = l_max_w - (l_x + l_w);
		*lp_y = l_max_h - (l_y + l_h);
		*lp_w = l_w;
		*lp_h = l_h;
		break;
	case 3: // 270 degree clock works
		*lp_x = l_y;
		*lp_y = l_max_w - (l_x + l_w);
		*lp_w = l_h;
		*lp_h = l_w;
		break;
	}
}

/*---------------------------------------------------------*/

/* 大きさのみ回転する
関数のオーバーロード機能により引数が全てdoubleの場合とlongの場合で使う
*/
void gts_master::__area_rot90_size( int i_rot90, double d_w, double d_h, double *dp_w, double *dp_h )
{
	/* マイナス回転はプラスにする
		i_rot90の値(回転差)は、
		-3(-270=90) =1,
		-2(-180=180) =2,
		-1(-90=270) =3,
		 0(0),
		 1(90),
		 2(180),
		 3(270)
	*/
	if (i_rot90 < 0) {
		i_rot90 += 4;
	}

	switch (i_rot90) {
	case 0: // 0 degree clock works
	case 2: // 180 degree clock works
		*dp_w = d_w;
		*dp_h = d_h;
		break;
	case 1: // 90 degree clock works
	case 3: // 270 degree clock works
		*dp_w = d_h;
		*dp_h = d_w;
		break;
	}
}

/*---------------------------------------------------------*/
/*---------------------------------------------------------*/

void gts_master::_area_rot90_menu( int i_rot90_old, int i_rot90_new )
{
	double	d_cm_x,
		d_cm_y,
		d_cm_w,
		d_cm_h,
		d_pix_w,
		d_pix_h,
		d_max_cm_w,
		d_max_cm_h;

	/* menuから数値(左上原点)を得て、
	rot90の変化に合わせて値を回転する */
	this->__area_rot90_d_pos_and_size(
		i_rot90_new - i_rot90_old,
		cl_gts_gui.valinp_area_x_pos->value(),
		cl_gts_gui.valinp_area_y_pos->value(),
		cl_gts_gui.valinp_area_x_size->value(),
		cl_gts_gui.valinp_area_y_size->value(),
		cl_gts_gui.valout_scanner_width_max->value(),
		cl_gts_gui.valout_scanner_height_max->value(),
		&d_cm_x,
		&d_cm_y,
		&d_cm_w,
		&d_cm_h
	);
	this->__area_rot90_size(
		i_rot90_new - i_rot90_old,
		cl_gts_gui.valinp_area_x_pixel->value(),
		cl_gts_gui.valinp_area_y_pixel->value(),
		&d_pix_w,
		&d_pix_h
	);
	this->__area_rot90_size(
		i_rot90_new - i_rot90_old,
		cl_gts_gui.valout_scanner_width_max->value(),
		cl_gts_gui.valout_scanner_height_max->value(),
		&d_max_cm_w,
		&d_max_cm_h
	);

	/* menuに数値(左上原点)を戻す */
	cl_gts_gui.valinp_area_x_pos->value(d_cm_x);
	cl_gts_gui.valinp_area_y_pos->value(d_cm_y);
	cl_gts_gui.valinp_area_x_size->value(d_cm_w);
	cl_gts_gui.valinp_area_y_size->value(d_cm_h);
	cl_gts_gui.valinp_area_x_pixel->value(d_pix_w),
	cl_gts_gui.valinp_area_y_pixel->value(d_pix_h),
	cl_gts_gui.valout_scanner_width_max->value(d_max_cm_w);
	cl_gts_gui.valout_scanner_height_max->value(d_max_cm_h);
}

/* 注意!!!画像自体の回転の前に行なうこと */
void gts_master::_area_rot90_openglrect( int i_rot90_old, int i_rot90_new )
{
	long	l_pix_x,l_pix_y,l_pix_w,l_pix_h;

	this->__area_rot90_l_pos_and_size(
		i_rot90_new - i_rot90_old,
		this->cl_ogl_view.get_l_crop_xp(),
		this->cl_ogl_view.get_l_crop_yp(),
		this->cl_ogl_view.get_l_crop_width(),
		this->cl_ogl_view.get_l_crop_height(),
		this->cl_ogl_view.get_l_width(),
		this->cl_ogl_view.get_l_height(),
		&l_pix_x,&l_pix_y,&l_pix_w,&l_pix_h );

	this->cl_ogl_view.set_crop_area(l_pix_x,l_pix_y,l_pix_w,l_pix_h);
}

/*---------------------------------------------------------*/
