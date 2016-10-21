#include <math.h>
#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::from_opengl_rect_to_area_val( void )
{
	long	l_image_w,
		l_image_h;
	long	l_pix_x,
		l_pix_y,
		l_pix_w,
		l_pix_h;
	double	d_cm_x,
		d_cm_y,
		d_cm_w,
		d_cm_h;
	double	d_dpi;

#if 0 /* ----------------------- commnet out ----------------------- */
	if (0 == this->cl_ogl_view.is_main_canvas()) { return; }
#endif /* ----------------------- commnet out ----------------------- */

	if ((E_SELECT_NOTHING == this->cl_ogl_view.get_e_select_part())
	||  (E_SELECT_IMAGE == this->cl_ogl_view.get_e_select_part())) {
		/* Areaをつかんでいないときはなにもしない */
		return;
	}

	/* 画像objから画像サイズを得る */
	l_image_w = this->cl_ogl_view.get_l_width();
	l_image_h = this->cl_ogl_view.get_l_height();
	if ((l_image_w <= 0L) || (l_image_h <= 0L)) {
		/* データがない(表示していない)ときはなにもしない  */
		return;
	}

	/* menuから解像度を得る(dot per inchs) */
	//d_dpi = cl_gts_gui.valinp_area_reso->value();
	d_dpi = this->cl_iip_scan.d_x_resolution();
	if (d_dpi <= 0.0) {
		pri_funct_err_bttvr(
	//"Error : cl_gts_gui.valinp_area_reso->value() returns <%g>",
	"Error : this->cl_iip_scan.d_x_resolution() returns <%g>",
			d_dpi);
		return;
	}

	/* 画像objからエリア情報を得る */
	l_pix_x = this->cl_ogl_view.get_l_crop_xp();
	l_pix_y = this->cl_ogl_view.get_l_crop_yp();
	l_pix_w = this->cl_ogl_view.get_l_crop_width();
	l_pix_h = this->cl_ogl_view.get_l_crop_height();

	/* 座標系変換 srcは左下原点 --> tgtは左上原点 */
	l_pix_y = l_image_h - (l_pix_y + l_pix_h);

	/* pixel単位をcm単位に変換 */
	d_cm_x = (double)l_pix_x * 2.54 / d_dpi;
	d_cm_y = (double)l_pix_y * 2.54 / d_dpi;
	d_cm_w = (double)l_pix_w * 2.54 / d_dpi;
	d_cm_h = (double)l_pix_h * 2.54 / d_dpi;

	/* menuに表示 */
	cl_gts_gui.valinp_area_x_pos->value(d_cm_x);
	cl_gts_gui.valinp_area_y_pos->value(d_cm_y);
	cl_gts_gui.valinp_area_x_size->value(d_cm_w);
	cl_gts_gui.valinp_area_y_size->value(d_cm_h);
	cl_gts_gui.valinp_area_x_pixel->value((double)l_pix_w);
	cl_gts_gui.valinp_area_y_pixel->value((double)l_pix_h);
}

void gts_master::_from_area_val_to_opengl_rect( void )
{
	double	d_cm_x,
		d_cm_y,
		d_cm_w,
		d_cm_h;
	long	l_image_h,
		l_pix_x,
		l_pix_y,
		l_pix_w,
		l_pix_h;
	double	d_dpi;

	/* 表示画像のサイズを得る */
	l_image_h = this->cl_ogl_view.get_l_height();

#if 0 /* ----------------------- commnet out ----------------------- */
	/* 画像を表示していないときは実行しない */
	if (0 == this->cl_ogl_view.is_main_canvas()) { return; }

	if (l_image_h <= 0L) {
		/* データがない(表示していない)ときはなにもしない  */
		return;
	}
#endif /* ----------------------- commnet out ----------------------- */

	/* menuから数値を得る */
	d_cm_x = cl_gts_gui.valinp_area_x_pos->value();
	d_cm_y = cl_gts_gui.valinp_area_y_pos->value();
	d_cm_w = cl_gts_gui.valinp_area_x_size->value();
	d_cm_h = cl_gts_gui.valinp_area_y_size->value();

	/* menuから解像度を得る(dot per inchs) */
	//d_dpi = cl_gts_gui.valinp_area_reso->value();
	d_dpi = this->cl_iip_scan.d_x_resolution();
	if (d_dpi <= 0.0) {
		pri_funct_err_bttvr(
	//"Error : cl_gts_gui.valinp_area_reso->value() returns <%g>",
	"Error : this->cl_iip_scan.d_x_resolution() returns <%g>",
			d_dpi);
		return;
	}

	/* cm単位をpixel単位に変換 */
	l_pix_x = (long)floor(d_cm_x * d_dpi / 2.54);
	l_pix_y = (long)floor(d_cm_y * d_dpi / 2.54);
	l_pix_w = (long)floor(d_cm_w * d_dpi / 2.54);
	l_pix_h = (long)floor(d_cm_h * d_dpi / 2.54);

	/* 座標系変換 srcは左下原点 --> tgtは左上原点 */
	l_pix_y = l_image_h - (l_pix_y + l_pix_h);

	/* エリアを変更 */
	this->cl_ogl_view.set_crop_area(l_pix_x,l_pix_y,l_pix_w,l_pix_h);

	/* 変更したので、再表示 */
	cl_gts_gui.opengl_view->redraw();
}

