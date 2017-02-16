#include <cmath> // floor(-)
#include "pri.h"
#include "cb_area_and_rot90.h"
#include "gts_gui.h"
#include "gts_master.h"

/*
	Rot90
*/

void cb_area_and_rot90::calc_rot90_offset_and_size(
	int choice_rot90
	, const double x , const double y , const double w , const double h
	, const double maxw , const double maxh
	, double *x2 , double *y2 , double *w2 , double *h2
)
{
	/* 回転差計算をしてマイナスの場合の値をプラスにする
	0	 #   0       degree clock works
	1 = -3+4 #  90(-270) degree clock works
	2 = -2+4 # 180(-180) degree clock works
	3 = -1+4 # 270( -90) degree clock works
	*/
	if (choice_rot90 < 0) { choice_rot90 += 4; }

	/* 左上原点で90degree単位回転計算 */
	switch (choice_rot90) {
	case 0: *x2=x;		*y2=y;          *w2=w; *h2=h; break;
	case 1: *x2=maxh-(y+h); *y2=x;          *w2=h; *h2=w; break;
	case 2: *x2=maxw-(x+w); *y2=maxh-(y+h); *w2=w; *h2=h; break;
	case 3: *x2=y;		*y2=maxw-(x+w); *w2=h; *h2=w; break;
	}
}

void cb_area_and_rot90::calc_rot90_size(
	int choice_rot90
	, const double w , const double h , double *w2 , double *h2
)
{
	/* 回転差計算をしてマイナスの場合の値をプラスにする
	0	 #   0       degree clock works
	1 = -3+4 #  90(-270) degree clock works
	2 = -2+4 # 180(-180) degree clock works
	3 = -1+4 # 270( -90) degree clock works
	*/
	if (choice_rot90 < 0) { choice_rot90 += 4; }

	/* 左上原点で90degree単位回転計算 */
	switch (choice_rot90) {
	case 0: case 2: *w2 = w; *h2 = h; break;
	case 1: case 3: *w2 = h; *h2 = w; break;
	}
}

/* メニューの回転値に合わせて回転処理をおこなう */
void cb_area_and_rot90::cb_rotate_per_90_when_scan( void )
{
	/* 確認1：スキャン後の画像でなければ何もしない */
	if (cl_gts_master.cl_iip_scan.get_clp_canvas()
	!=  cl_gts_master.cl_iip_ro90.get_clp_parent()) {
		return;
	}

	/* 確認2：メニューの指定が回転してないときはなにもしない */
	if (	cl_gts_gui.choice_rot90->value()
	==  this->previous_choice_rot90_) {
		return;
	}

	/* 表示値を回転する */
	const int rot90_diff = cl_gts_gui.choice_rot90->value()
			 - this->previous_choice_rot90_;
	double	cm_x=0, cm_y=0
		, cm_w=0, cm_h=0
		, pix_w=0, pix_h=0
		, max_cm_w=0, max_cm_h=0;

	/* 数値(左上原点)を得て、rot90の変化に合わせて値を回転する */
	this->calc_rot90_offset_and_size(
		rot90_diff
		, cl_gts_gui.valinp_area_x_pos->value()
		, cl_gts_gui.valinp_area_y_pos->value()
		, cl_gts_gui.valinp_area_x_size->value()
		, cl_gts_gui.valinp_area_y_size->value()
		, cl_gts_gui.valout_scanner_width_max->value()
		, cl_gts_gui.valout_scanner_height_max->value()
		, &cm_x , &cm_y , &cm_w , &cm_h
	);
	this->calc_rot90_size(
		rot90_diff
		, cl_gts_gui.valinp_area_x_pixel->value()
		, cl_gts_gui.valinp_area_y_pixel->value()
		, &pix_w , &pix_h
	);
	this->calc_rot90_size(
		rot90_diff
		, cl_gts_gui.valout_scanner_width_max->value()
		, cl_gts_gui.valout_scanner_height_max->value()
		, &max_cm_w , &max_cm_h
	);

	/* 数値(左上原点)を戻す */
	cl_gts_gui.valinp_area_x_pos->value(cm_x);
	cl_gts_gui.valinp_area_y_pos->value(cm_y);
	cl_gts_gui.valinp_area_x_size->value(cm_w);
	cl_gts_gui.valinp_area_y_size->value(cm_h);
	cl_gts_gui.valinp_area_x_pixel->value(pix_w),
	cl_gts_gui.valinp_area_y_pixel->value(pix_h),
	cl_gts_gui.valout_scanner_width_max->value(max_cm_w);
	cl_gts_gui.valout_scanner_height_max->value(max_cm_h);

	/* 回転の現在値をメモリする */
	this->previous_choice_rot90_ = cl_gts_gui.choice_rot90->value();

	/* 画像あれば回転処理し表示する */
	cl_gts_master.rot_and_trace_and_enoise_and_preview( 
		cl_gts_master.cl_iip_ro90.get_clp_parent()
		, cl_gts_gui.choice_rot90->value()
		, cl_gts_master.cl_ogl_view.get_crop_disp_sw()
	);

	/* 表示値からopengl rect値をセットする */
	this->copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}

/*
	変換
*/

void cb_area_and_rot90::copy_opengl_to_value( void )
{
	/* 画像上のエリアハンドルを選択していること */
	if (
	(E_SELECT_NOTHING == cl_gts_master.cl_ogl_view.get_e_select_part())
	||
	(E_SELECT_IMAGE == cl_gts_master.cl_ogl_view.get_e_select_part())
	) {
		/* Areaをつかんでいないときはなにもしない */
		return;
	}

	/* 表示する画像があること */
	if ((cl_gts_master.cl_ogl_view.get_l_width() <= 0L)
	||  (cl_gts_master.cl_ogl_view.get_l_height() <= 0L)
	) {
		/* データがない(表示していない)ときはなにもしない  */
		return;
	}

	/* 解像度を得る */
	const double dpi = cl_gts_gui.valinp_area_reso->value();
	if (dpi <= 0.0) {
		pri_funct_err_bttvr(
	"Warning : cl_gts_gui.valinp_area_reso->value() returns <%g>"
			, dpi);
		return;
	}

	/* 画像objからエリア情報を得る */
	const int pix_x = cl_gts_master.cl_ogl_view.get_l_crop_xp();
	      int pix_y = cl_gts_master.cl_ogl_view.get_l_crop_yp();
	const int pix_w = cl_gts_master.cl_ogl_view.get_l_crop_width();
	const int pix_h = cl_gts_master.cl_ogl_view.get_l_crop_height();

	/* 座標系変換 srcは左下原点 --> tgtは左上原点 */
	pix_y		= cl_gts_master.cl_ogl_view.get_l_height()
		- (pix_y + pix_h);

	/* 表示値(cm)を得る */
	const double cm_x = this->cm_from_pixel_( pix_x ,dpi );
	const double cm_y = this->cm_from_pixel_( pix_y ,dpi );
	const double cm_w = this->cm_from_pixel_( pix_w ,dpi );
	const double cm_h = this->cm_from_pixel_( pix_h ,dpi );

	/* 数値を表示 */
	cl_gts_gui.valinp_area_x_pos->value(cm_x);
	cl_gts_gui.valinp_area_y_pos->value(cm_y);
	cl_gts_gui.valinp_area_x_size->value(cm_w);
	cl_gts_gui.valinp_area_y_size->value(cm_h);
	cl_gts_gui.valinp_area_x_pixel->value(static_cast<double>(pix_w));
	cl_gts_gui.valinp_area_y_pixel->value(static_cast<double>(pix_h));
}

/* pixel単位をcm単位に変換 */
double cb_area_and_rot90::cm_from_pixel_(
	const double pixel , const double dpi )
{
	return pixel * 2.54 / dpi;
}
/* cm単位をpixel単位に変換 */
double cb_area_and_rot90::pixel_from_cm_(
	const double cm , const double dpi )
{
	return floor( cm * dpi / 2.54 );
}

void cb_area_and_rot90::copy_value_to_opengl( void )
{
	/* 解像度を得る */
	const double dpi = cl_gts_gui.valinp_area_reso->value();
	if (dpi <= 0.0) {
		pri_funct_err_bttvr(
	"Warning : cl_gts_gui.valinp_area_reso->value() returns <%g>"
			, dpi);
		return;
	}

	/* 表示値(cm)を得る */
	const double cm_x = cl_gts_gui.valinp_area_x_pos->value();
	      double cm_y = cl_gts_gui.valinp_area_y_pos->value();
	const double cm_w = cl_gts_gui.valinp_area_x_size->value();
	const double cm_h = cl_gts_gui.valinp_area_y_size->value();

	/* 座標系変換 Valueは左下原点 --> OpenGLは左上原点 */
	cm_y		  = cl_gts_gui.valout_scanner_height_max->value()
		- (cm_y + cm_h);

	/* Area(offset(x,y) ,size(w,h))を得る */
	const int pix_x = static_cast<int>(this->pixel_from_cm_(cm_x ,dpi));
	      int pix_y = static_cast<int>(this->pixel_from_cm_(cm_y ,dpi));
	const int pix_w = static_cast<int>(this->pixel_from_cm_(cm_w ,dpi));
	const int pix_h = static_cast<int>(this->pixel_from_cm_(cm_h ,dpi));

	/* 座標系変換 Valueは左下原点 --> OpenGLは左上原点 */
//	pix_y = cl_gts_master.cl_ogl_view.get_l_height() - (pix_y + pix_h);

	/* エリアを変更 */
	cl_gts_master.cl_ogl_view.set_crop_area(pix_x ,pix_y ,pix_w ,pix_h);
}

