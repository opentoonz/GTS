#include "pri.h"
#include "cb_area_and_rot90.h"
#include "gts_gui.h"
#include "gts_master.h"

void cb_area_and_rot90::calc_rot90_size(
 int choice_rot90, double w , double h , double *w2 , double *h2
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

void cb_area_and_rot90::rot90_about_area_GUI_values_( const int rot90_diff )
{
	double	cm_x=0, cm_y=0
		, cm_w=0, cm_h=0
		, pix_w=0, pix_h=0
		, max_cm_w=0, max_cm_h=0;

	/* menuから数値(左上原点)を得て、
	rot90の変化に合わせて値を回転する */
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

	/* menuに数値(左上原点)を戻す */
	cl_gts_gui.valinp_area_x_pos->value(cm_x);
	cl_gts_gui.valinp_area_y_pos->value(cm_y);
	cl_gts_gui.valinp_area_x_size->value(cm_w);
	cl_gts_gui.valinp_area_y_size->value(cm_h);
	cl_gts_gui.valinp_area_x_pixel->value(pix_w),
	cl_gts_gui.valinp_area_y_pixel->value(pix_h),
	cl_gts_gui.valout_scanner_width_max->value(max_cm_w);
	cl_gts_gui.valout_scanner_height_max->value(max_cm_h);
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
	this->rot90_about_area_GUI_values_(
	 cl_gts_gui.choice_rot90->value() - this->previous_choice_rot90_
	);

	/* OpenGL Rect値を回転する(必ず(view)画像の回転の前に行なう) */
	{int	x=0 ,y=0 ,w=0 ,h=0; 
	 this->calc_rot90_offset_and_size<int>(
	 cl_gts_gui.choice_rot90->value() - this->previous_choice_rot90_
	,cl_gts_master.cl_ogl_view.get_l_crop_xp()
	,cl_gts_master.cl_ogl_view.get_l_crop_yp()
	,cl_gts_master.cl_ogl_view.get_l_crop_width()
	,cl_gts_master.cl_ogl_view.get_l_crop_height()
	,cl_gts_master.cl_ogl_view.get_l_width()
	,cl_gts_master.cl_ogl_view.get_l_height()
	,&x,&y,&w,&h
	 );
	 cl_gts_master.cl_ogl_view.set_crop_area(x,y,w,h);
	 cl_gts_gui.opengl_view->redraw();
	}

	/* 回転の現在値をメモリする */
	this->previous_choice_rot90_ = cl_gts_gui.choice_rot90->value();

	/* 画像あれば回転処理し表示する */
	cl_gts_master.rot_and_trace_and_enoise_and_preview_( 
		cl_gts_master.cl_iip_ro90.get_clp_parent()
		, cl_gts_gui.choice_rot90->value()
		, cl_gts_master.cl_ogl_view.get_crop_disp_sw()
	);

	/* menuからopengl rect値をセットする
	(直接回転しても値がリセットしてしまうための暫定措置) */
	/* ?????????????????????????????????????????????????? */
	cl_gts_master._from_area_val_to_opengl_rect();
}

