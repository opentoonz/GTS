#include <cmath> // floor(-)
#include <FL/fl_ask.H> // fl_alert()
#include "pri.h"
#include "cb_area_and_rot90.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {
void differ_dpi_marking_(const bool sw)
{
	cl_gts_gui.valinp_area_reso->color(sw?FL_YELLOW:FL_WHITE);
	cl_gts_gui.valinp_area_reso->redraw();
}
}//namespace

/*
	Crop
*/

void cb_area_and_rot90::cb_scan_full_area_and_crop( void )
{
	/* Presetを解除する */
	cl_gts_gui.choice_area_selecter->value(0);
	cl_gts_gui.choice_area_aspect_ratio_selecter->value(0);
	cl_gts_gui.group_area_crop->activate();

	/* フルエリアでスキャンを実行
		このときCrop Areaはフルエリアではない
	*/
	int return_code=NG;
	iip_canvas* clp_scan = cl_gts_master.iipg_scan(
		return_code ,true/* scan_full_area_sw */
	);
	if (return_code == NG) {
		pri_funct_err_bttvr(
		      "Error : cl_gts_master.iipg_scan() returns NG" );
		return;
	}
	if (nullptr == clp_scan) {
		pri_funct_err_bttvr(
		      "Error : cl_gts_master.iipg_scan() returns nullptr" );
		return;
	}

	/* ユーザーからのキャンセルがあった */
	if (return_code == CANCEL) {
		return;
	}

	/* Cropしたときのdpiを記憶し、画像表示のdpiとする
	cl_gts_master.cl_iip_scan.d_x_resolution()
	の値はエラーやキャンセルの場合にもセットしてしまうので使えない */
	this->dpi_when_cropped_ = cl_gts_gui.valinp_area_reso->value();
	differ_dpi_marking_(false);

	/* スキャンした画像とCropエリアの表示 */
	cl_gts_master.rot_and_trace_and_enoise_and_preview(
		clp_scan ,cl_gts_gui.choice_rot90->value() ,true ,true
	);

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}

/*
	Preset
*/

void cb_area_and_rot90::cb_area_selecter( void )
{
	/* Areaセレクターで先頭のゼロを選択したときは"Custom" */
	if (0 == cl_gts_gui.choice_area_selecter->value()) {
		/* 各項目入力できるようにする */
		cl_gts_gui.group_area_crop->activate();
	}
	/* Areaセレクターで2番目以後を選択したとき */
	else {
		/* 現在選択位置からArea情報をコピーで得る */
		preset_axywhr area =
		cl_gts_master.cl_memo_scan_area.areas.at(
			cl_gts_gui.choice_area_selecter->value()-1
		);

		/* Start X Y cm */
		cl_gts_gui.valinp_area_x_pos->value( area.x );
		cl_gts_gui.valinp_area_y_pos->value( area.y );

		/* Screen Aspect Ratio選択位置 */
		cl_gts_gui.choice_area_aspect_ratio_selecter->value(
		cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(area.r.c_str())
		);

		/* Size W H cm */
		cl_gts_gui.valinp_area_x_size->value( area.w );
		cl_gts_gui.valinp_area_y_size->value( area.h );

		/* Size W H pixel */
		this->getset_x_pixel_from_x_size();
		this->getset_y_pixel_from_y_size();

		/* 各項目入力できなくする */
		cl_gts_gui.group_area_crop->deactivate();

		this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
		cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
	}
}

void cb_area_and_rot90::cb_area_aspect_ratio_selecter( void )
{
	/* Areaセレクターで先頭のゼロを選択したときは"Custom" */
	if (0 ==
	cl_gts_gui.choice_area_aspect_ratio_selecter->value()) {
		return;
	}
	/* Areaセレクターで2番目以後を選択したとき */
	else {
		/* 現在選択位置からArea情報をコピーで得る */
		preset_rwh ratio =
		cl_gts_master.cl_memo_scan_area.aspect_ratios.at(
		 cl_gts_gui.choice_area_aspect_ratio_selecter->value()-1
		);

		/* Size H cm */
		cl_gts_gui.valinp_area_y_size->value(
		 cl_gts_gui.valinp_area_x_size->value() * ratio.h / ratio.w
		);

		/* Size H pixel */
		this->getset_y_pixel_from_y_size();

		this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
		cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
	}
}

/*
	Area
*/

void cb_area_and_rot90::cb_area_x_pos( void )
{
	/* 先：横位置が大きすぎてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valout_scanner_width_max->value()
	 < (cl_gts_gui.valinp_area_x_pos->value() +
	    cl_gts_gui.valinp_area_x_size->value())
	) {
	    cl_gts_gui.valinp_area_x_pos->value(
	    cl_gts_gui.valout_scanner_width_max->value() -
	    cl_gts_gui.valinp_area_x_size->value()
	    ); /* x_sizeが大きすぎる(誤値だが...)とマイナスになる */
	}
	/* 後：横位置が小さくてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valinp_area_x_pos->value() < 0.0) {
	    cl_gts_gui.valinp_area_x_pos->value(0.0);
	}

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void cb_area_and_rot90::cb_area_y_pos( void )
{
	/* 先：縦位置が大きすぎてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valout_scanner_height_max->value()
	 < (cl_gts_gui.valinp_area_y_pos->value() +
	    cl_gts_gui.valinp_area_y_size->value())
	) {
	    cl_gts_gui.valinp_area_y_pos->value(
	    cl_gts_gui.valout_scanner_height_max->value() -
	    cl_gts_gui.valinp_area_y_size->value()
	    ); /* y_sizeが大きすぎる(誤値だが...)とマイナスになる */
	}
	/* 後：縦位置が小さくてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valinp_area_y_pos->value() < 0.0) {
	    cl_gts_gui.valinp_area_y_pos->value(0.0);
	}

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}

void cb_area_and_rot90::cb_area_x_size( void )
{
	/* 先：横位置が大きすぎてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valout_scanner_width_max->value()
	 < (cl_gts_gui.valinp_area_x_pos->value() +
	    cl_gts_gui.valinp_area_x_size->value())
	) {
	    cl_gts_gui.valinp_area_x_size->value(
	    cl_gts_gui.valout_scanner_width_max->value() -
	    cl_gts_gui.valinp_area_x_pos->value()
	    ); /* x_sizeが大きすぎる(誤値だが...)とマイナスになる */
	}
	/* 後：横位置が小さくてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valinp_area_x_size->value() < 0.0) {
	    cl_gts_gui.valinp_area_x_size->value(0.0);
	}

	/* Screen Aspect Ratioの指定があるときは
	cm高さ値とpixel高さ値を計算してGUIに表示 */
	this->getset_y_size_from_x_size_();

	/* cm幅値からpixel幅値を計算してGUIに表示 */
	this->getset_x_pixel_from_x_size();
	this->getset_y_pixel_from_y_size();

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void cb_area_and_rot90::cb_area_y_size( void )
{
	/* 先：縦位置が大きすぎてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valout_scanner_height_max->value()
	 < (cl_gts_gui.valinp_area_y_pos->value() +
	    cl_gts_gui.valinp_area_y_size->value())
	) {
	    cl_gts_gui.valinp_area_y_size->value(
	    cl_gts_gui.valout_scanner_height_max->value() -
	    cl_gts_gui.valinp_area_y_pos->value()
	    ); /* y_sizeが大きすぎる(誤値だが...)とマイナスになる */
	}

	/* 後：縦位置が小さくてはみ出す場合、範囲に収める */
	if (cl_gts_gui.valinp_area_y_size->value() < 0.0) {
	    cl_gts_gui.valinp_area_y_size->value(0.0);
	}

	/* Screen Aspect Ratioの指定があるときは
	cm高さ値とpixel高さ値を計算してGUIに表示 */
	this->getset_x_size_from_y_size_();

	/* cm幅値からpixel幅値を計算してGUIに表示 */
	this->getset_x_pixel_from_x_size();
	this->getset_y_pixel_from_y_size();

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}

void cb_area_and_rot90::cb_area_x_pixel_size( void )
{
	this->getset_x_size_from_x_pixel_();
	this->cb_area_x_size();
}
void cb_area_and_rot90::cb_area_y_pixel_size( void )
{
	this->getset_y_size_from_y_pixel_();
	this->cb_area_y_size();
}

void cb_area_and_rot90::cb_area_reso( void )
{
	/* 変化したDPIに合わせてAreaサイズの値を変更する */
	if (cl_gts_gui.radbut_area_reso_fix_cm->value()) {
		this->getset_x_pixel_from_x_size();
		this->getset_y_pixel_from_y_size();
	}
	else {
		this->check_dpi_or_size_from_pixel_();
	}

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */

	/* 既にCropしていて、かつ、その表示画像とDPIが一致しなくなった */
	if (0.0 < this->dpi_when_cropped_
	&&  this->dpi_when_cropped_ != cl_gts_gui.valinp_area_reso->value()
	) {
		differ_dpi_marking_(true);
		fl_alert( "Crop again!" );
	}
	else {
		/* また一回もCropしてない、あるいは
		既にCropしていてその表示画像とDPIが一致
		のときはdpiの変更は自由 */
		differ_dpi_marking_(false);
	}
}

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
		/* 回転のGUIは元に戻す、つまり動作させない */
		cl_gts_gui.choice_rot90->value(
			this->previous_choice_rot90_
		);
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

	this->copy_value_to_opengl(); /* 表示ルーチンにArea設定 */
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}

/*
	変換
*/

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
	return cm * dpi / 2.54;
}

/* cmサイズと対応するpixelサイズからdpiを得る */
double cb_area_and_rot90::dpi_from_cm_per_pixel_(
	const double cm ,const double pixel
)
{
	return pixel * 2.54 / cm;
}

void cb_area_and_rot90::getset_x_pixel_from_x_size( void )
{
	cl_gts_gui.valinp_area_x_pixel->value( 
		this->pixel_from_cm_(
			cl_gts_gui.valinp_area_x_size->value()
			,cl_gts_gui.valinp_area_reso->value()
		)
	);
}
void cb_area_and_rot90::getset_y_pixel_from_y_size( void )
{
	cl_gts_gui.valinp_area_y_pixel->value( 
		this->pixel_from_cm_(
			cl_gts_gui.valinp_area_y_size->value()
			,cl_gts_gui.valinp_area_reso->value()
		)
	);
}

void cb_area_and_rot90::getset_y_size_from_x_size_( void )
{
	if (0 < cl_gts_master.cl_memo_scan_area.aspect_ratios.size()
	&&  0 < cl_gts_gui.choice_area_aspect_ratio_selecter->value()
	) {
		preset_rwh ratio =
		cl_gts_master.cl_memo_scan_area.aspect_ratios.at(
		cl_gts_gui.choice_area_aspect_ratio_selecter->value()
			-1
		);
		cl_gts_gui.valinp_area_y_size->value(
		cl_gts_gui.valinp_area_x_size->value()  * ratio.h / ratio.w
		);
		cl_gts_gui.valinp_area_y_pixel->value(
		cl_gts_gui.valinp_area_x_pixel->value() * ratio.h / ratio.w
		);
	}
 }
void cb_area_and_rot90::getset_x_size_from_y_size_( void )
{
	if (0 < cl_gts_master.cl_memo_scan_area.aspect_ratios.size()
	&&  0 < cl_gts_gui.choice_area_aspect_ratio_selecter->value()
	) {
		preset_rwh ratio =
		cl_gts_master.cl_memo_scan_area.aspect_ratios.at(
		cl_gts_gui.choice_area_aspect_ratio_selecter->value()
			-1
		);
		cl_gts_gui.valinp_area_x_size->value(
		cl_gts_gui.valinp_area_y_size->value()  * ratio.w / ratio.h
		);
		cl_gts_gui.valinp_area_x_pixel->value(
		cl_gts_gui.valinp_area_y_pixel->value() * ratio.w / ratio.h
		);
	}
}

void cb_area_and_rot90::check_dpi_or_size_from_pixel_( void )
{
	const double x_cm_size = this->cm_from_pixel_(
		cl_gts_gui.valinp_area_x_pixel->value()
		,cl_gts_gui.valinp_area_reso->value()
	);
	const double y_cm_size = this->cm_from_pixel_(
		cl_gts_gui.valinp_area_y_pixel->value()
		,cl_gts_gui.valinp_area_reso->value()
	);
	if (
	((cl_gts_gui.valout_scanner_width_max->value()
	<
	( cl_gts_gui.valinp_area_x_pos->value() + x_cm_size )))
	||
	((cl_gts_gui.valout_scanner_height_max->value()
	<
	( cl_gts_gui.valinp_area_y_pos->value() + y_cm_size )))
	) {	/* 範囲外ならDPIを範囲内に収める */
		const double x_dpi = this->dpi_from_cm_per_pixel_(
			cl_gts_gui.valout_scanner_width_max->value()
			- cl_gts_gui.valinp_area_x_pos->value()
			,cl_gts_gui.valinp_area_x_pixel->value()
		);
		const double y_dpi = this->dpi_from_cm_per_pixel_(
			cl_gts_gui.valout_scanner_height_max->value()
			- cl_gts_gui.valinp_area_y_pos->value()
			,cl_gts_gui.valinp_area_y_pixel->value()
		);
		cl_gts_gui.valinp_area_reso->value(
			ceil( max( x_dpi , y_dpi ) )
		);
	}
	this->getset_x_size_from_x_pixel_();
	this->getset_y_size_from_y_pixel_();
}

void cb_area_and_rot90::getset_x_size_from_x_pixel_( void )
{
	cl_gts_gui.valinp_area_x_size->value( 
		this->cm_from_pixel_(
			cl_gts_gui.valinp_area_x_pixel->value()
			,cl_gts_gui.valinp_area_reso->value()
		)
	);
}
void cb_area_and_rot90::getset_y_size_from_y_pixel_( void )
{
	cl_gts_gui.valinp_area_y_size->value( 
		this->cm_from_pixel_(
			cl_gts_gui.valinp_area_y_pixel->value()
			,cl_gts_gui.valinp_area_reso->value()
		)
	);
}

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

void cb_area_and_rot90::copy_value_to_opengl( void )
{
	/* 解像度を得る */
	//const double dpi = cl_gts_gui.valinp_area_reso->value();
	const double dpi = this->dpi_when_cropped_;
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
	const int pix_x = static_cast<int>(floor(this->pixel_from_cm_(
							cm_x ,dpi)));
	      int pix_y = static_cast<int>(floor(this->pixel_from_cm_(
	      						cm_y ,dpi)));
	const int pix_w = static_cast<int>(floor(this->pixel_from_cm_(
							cm_w ,dpi)));
	const int pix_h = static_cast<int>(floor(this->pixel_from_cm_(
							cm_h ,dpi)));

	/* 座標系変換 Valueは左下原点 --> OpenGLは左上原点 */
//	pix_y = cl_gts_master.cl_ogl_view.get_l_height() - (pix_y + pix_h);

	/* エリアを変更 */
	cl_gts_master.cl_ogl_view.set_crop_area(pix_x ,pix_y ,pix_w ,pix_h);
}

