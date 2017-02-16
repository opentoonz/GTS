#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_scnr_area_x_pos( void ) {
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void gts_master::cb_scnr_area_y_pos( void ) {
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
namespace {
 void fix_y_from_x_( void ) {
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
 void fix_x_from_y_( void ) {
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
}
void gts_master::cb_scnr_area_x_size( void ) {
	/* cm幅値からpixel幅値を計算してGUIに表示 */
	const double siz = cl_gts_gui.valinp_area_x_size->value();
	const double dpi = cl_gts_gui.valinp_area_reso->value();
	cl_gts_gui.valinp_area_x_pixel->value( siz * dpi / 2.54 );

	/* Screen Aspect Ratioの指定があるときは
	cm高さ値とpixel高さ値を計算してGUIに表示 */
	fix_y_from_x_();

	/* OpenGL画像表示のエリア枠を再表示 */
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void gts_master::cb_scnr_area_y_size( void ) {
	/* cm幅値からpixel幅値を計算してGUIに表示 */
	const double siz = cl_gts_gui.valinp_area_y_size->value();
	const double dpi = cl_gts_gui.valinp_area_reso->value();
	cl_gts_gui.valinp_area_y_pixel->value( siz * dpi / 2.54 );

	/* Screen Aspect Ratioの指定があるときは
	cm高さ値とpixel高さ値を計算してGUIに表示 */
	fix_x_from_y_();

	/* OpenGL画像表示のエリア枠を再表示 */
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void gts_master::cb_scnr_area_x_pixel( void ) {
	/* pixel幅値からcm幅値を計算してGUIに表示 */
	const double pix = cl_gts_gui.valinp_area_x_pixel->value();
	const double dpi = cl_gts_gui.valinp_area_reso->value();
	cl_gts_gui.valinp_area_x_size->value( pix * 2.54 / dpi );

	/* Screen Aspect Ratioの指定があるときは
	cm高さ値とpixel高さ値を計算してGUIに表示 */
	fix_y_from_x_();

	/* OpenGL画像表示のエリア枠を再表示 */
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void gts_master::cb_scnr_area_y_pixel( void ) {
	/* pixel幅値からcm幅値を計算してGUIに表示 */
	const double pix = cl_gts_gui.valinp_area_y_pixel->value();
	const double dpi = cl_gts_gui.valinp_area_reso->value();
	cl_gts_gui.valinp_area_y_size->value( pix * 2.54 / dpi );

	/* Screen Aspect Ratioの指定があるときは
	cm高さ値とpixel高さ値を計算してGUIに表示 */
	fix_x_from_y_();

	/* OpenGL画像表示のエリア枠を再表示 */
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}
void gts_master::cb_scnr_area_reso( void ) {
	if (cl_gts_gui.radbut_area_reso_fix_cm->value()) {
		cl_gts_gui.valinp_area_x_pixel->value( 
		cl_gts_gui.valinp_area_x_size->value()
		* cl_gts_gui.valinp_area_reso->value() / 2.54 );
		cl_gts_gui.valinp_area_y_pixel->value( 
		cl_gts_gui.valinp_area_y_size->value()
		* cl_gts_gui.valinp_area_reso->value() / 2.54 );
	} else {
		cl_gts_gui.valinp_area_x_size->value( 
		cl_gts_gui.valinp_area_x_pixel->value() * 2.54
		/ cl_gts_gui.valinp_area_reso->value() );
		cl_gts_gui.valinp_area_y_size->value( 
		cl_gts_gui.valinp_area_y_pixel->value() * 2.54
		/ cl_gts_gui.valinp_area_reso->value() );
	}
	this->cl_area_and_rot90.copy_value_to_opengl();
	cl_gts_gui.opengl_view->redraw(); /* 変更したので、再表示 */
}

