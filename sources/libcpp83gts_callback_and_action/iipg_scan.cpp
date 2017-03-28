#include <iostream>
#include <string>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

int gts_master::iipg_scan_open_setup_unit_get_spec_( void )
{
	/* すべてセンチメータ単位で処理する */
	this->cl_iip_scan.i_centimeters_sw(ON);

	/* TWAIN開く */
	if (OK != this->cl_iip_scan.open()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.open() returns NG.");
		return NG;
	}

	/* スキャナーに対して、スキャンの単位を一番始めに設定 */
	if (OK != this->cl_iip_scan.setup_unit()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.setup_unit() returns NG.");
		return NG;
	}

	/* スキャナーのハード情報を取って来て...
		cap_get_dp_x_native_resolution()
		cap_get_dp_y_native_resolution()
		cap_get_dp_physical_width()
		cap_get_dp_physical_height()
	*/
	if (OK != this->cl_iip_scan.get_physical_param()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.get_physical_param() returns NG.");
		return NG;
	}
std::cout
	<< "Scanner Native Resolution\n" /* ハードウェア自体の解像度 */
	<< " X=" << this->cl_iip_scan.d_x_native_resolution()
	<< " Y=" << this->cl_iip_scan.d_y_native_resolution() << "\n"
	<< "Scanner Physical Size\n" /* 物理的大きさ */
	<< " W=" << this->cl_iip_scan.d_physical_width()
	<< " H=" << this->cl_iip_scan.d_physical_height()
	<< std::endl;

	/* スキャナー幅と高さをユーザー指定の回転をする */
	double	d_maxcm_w=0 ,d_maxcm_h=0;
	cl_gts_master.cl_area_and_rot90.calc_rot90_size(
		cl_gts_gui.choice_rot90->value()
		, cl_gts_master.cl_iip_scan.d_physical_width()
		, cl_gts_master.cl_iip_scan.d_physical_height()
		, &d_maxcm_w
		, &d_maxcm_h
	);
std::cout
	<< "Scanner Physical Size Rotated\n"
	<< " W=" << d_maxcm_w
	<< " H=" << d_maxcm_h
	<< std::endl;

	/* スキャナー幅高さをユーザー指定の回転してメニューに設定 */
	cl_gts_gui.valout_scanner_size_cm_w->value(d_maxcm_w);
	cl_gts_gui.valout_scanner_size_cm_h->value(d_maxcm_h);

	/* スキャナー型番をメニューに設定 */
	cl_gts_gui.txtout_scanner_type->value(
		cl_gts_master.cl_iip_scan.get_cp_machine_type()
	);

	return OK;
}

int gts_master::iipg_scan_action_( const bool full_area_sw )
{
	/*
		メニュー値からスキャナーへ渡す値を得る
	*/

	/* スキャン範囲を得る */
	double	d_cm_x=0,d_cm_y=0,d_cm_w=0,d_cm_h=0;
	if (full_area_sw) {
		/* スキャナーのフルサイズ */
		this->cl_area_and_rot90.calc_rot90_offset_and_size(
			-cl_gts_gui.choice_rot90->value()/* マイナス回転 */
			, 0.0
			, 0.0
			, cl_gts_gui.valout_scanner_size_cm_w->value()
			, cl_gts_gui.valout_scanner_size_cm_h->value()
			, cl_gts_gui.valout_scanner_size_cm_w->value()
			, cl_gts_gui.valout_scanner_size_cm_h->value()
			, &d_cm_x
			, &d_cm_y
			, &d_cm_w
			, &d_cm_h
		);
	}
	else {
		/* ユーザー指定サイズ */
		this->cl_area_and_rot90.calc_rot90_offset_and_size(
			-cl_gts_gui.choice_rot90->value()/* マイナス回転 */
			, cl_gts_gui.valinp_area_offset_cm_x->value()
			, cl_gts_gui.valinp_area_offset_cm_y->value()
			, cl_gts_gui.valinp_area_size_cm_w->value()
			, cl_gts_gui.valinp_area_size_cm_h->value()
			, cl_gts_gui.valout_scanner_size_cm_w->value()
			, cl_gts_gui.valout_scanner_size_cm_h->value()
			, &d_cm_x
			, &d_cm_y
			, &d_cm_w
			, &d_cm_h
		);
	}
std::cout
	<< "TWAIN Scanner Area\n"
	<< " Start X=" << d_cm_x << " Y=" << d_cm_y << "\n"
	<< " Size  W=" << d_cm_w << " H=" << d_cm_h
	<< std::endl;

	/* 左右 */
	this->cl_iip_scan.d_left( d_cm_x );
	this->cl_iip_scan.d_right( d_cm_x + d_cm_w );

	/* 上下 */
	this->cl_iip_scan.d_top( d_cm_y );
	this->cl_iip_scan.d_bottom( d_cm_y + d_cm_h );

	/* 解像度 */
	this->cl_iip_scan.d_x_resolution(
		cl_gts_gui.valinp_area_reso->value() );
	this->cl_iip_scan.d_y_resolution(
		cl_gts_gui.valinp_area_reso->value() );

#ifndef _WIN32
    // the requested resolution may be adjusted, so update the GUI value
    cl_gts_gui.valinp_area_reso->value(this->cl_iip_scan.d_x_resolution());
#endif

	/* ピクセルタイプ */
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:	/* bw */
		this->cl_iip_scan.e_pixeltype( E_PIXELTYPE_BW );
		this->cl_iip_scan.d_threshold(
			cl_gts_gui.valinp_bw_threshold->value() );
		break;
	case 1:	/* grayscale */
		this->cl_iip_scan.e_pixeltype( E_PIXELTYPE_GRAYSCALE );
		this->cl_iip_scan.d_brightness(
			cl_gts_gui.valinp_grayscale_brightness->value() );
		this->cl_iip_scan.d_contrast(
			cl_gts_gui.valinp_grayscale_contrast->value() );
		this->cl_iip_scan.d_gamma(
			cl_gts_gui.valinp_grayscale_gamma->value() );
		break;
	case 2:	/* rgb */
		this->cl_iip_scan.e_pixeltype( E_PIXELTYPE_RGB );
		this->cl_iip_scan.d_brightness(
			cl_gts_gui.valinp_rgb_brightness->value() );
		this->cl_iip_scan.d_contrast(
			cl_gts_gui.valinp_rgb_contrast->value() );
		this->cl_iip_scan.d_gamma(
			cl_gts_gui.valinp_rgb_gamma->value() );
		break;
	}

	/* 回転 */
	/***this->cl_iip_scan.i_orientation(
		cl_gts_gui.choice_rot90->value()
	);***/


	/* ...スキャナーへ送る */
	if (OK != this->cl_iip_scan.setup_action()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.setup_action() returns NG.");
		return NG;
	}

	/* 設定したスキャナー情報を表示 */
	if (ON == this->_i_pv_sw) {
		if (OK != this->cl_iip_scan.print_all()) {
			pri_funct_err_bttvr(
		 "Error : this->cl_iip_scan.print_all() returns NG" );
			return NG;
		}
	}

	/* 画像をスキャンして読む */
	const int ret = this->cl_iip_scan.read();
	if (NG == ret) {
		pri_funct_err_bttvr(
	       "Error : this->cl_iip_scan.read() returns NG.");
		return NG;
	}

	/* ユーザー操作によるキャンセル */
	if (ret == CANCEL) {
		return CANCEL;
	}

	return OK;
}

/*---------------------------------------------------------*/

iip_canvas *gts_master::iipg_scan(
	int&return_code/* OK/NG/CANCEL*/ ,const bool full_area_sw
)
{
	if (OK != this->iipg_scan_open_setup_unit_get_spec_()) {
		return NULL;
	}

	return_code = this->iipg_scan_action_( full_area_sw );
	if (return_code == NG) {
		pri_funct_err_bttvr(
	     "Error : this->iipg_scan_action_(-) returns NG.");
		/* ここでエラーがおきてもclose()はやる */
std::string str("Scan Critical Error!\nSave Config and Restart!");
fl_alert(str.c_str());
	}

	if (OK != this->cl_iip_scan.close()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.close() returns NG.");
std::string str("Scan Close Critical Error!\nSave Config and Restart!");
fl_alert(str.c_str());
		return NULL;
	}

	return this->cl_iip_scan.get_clp_canvas();
}

/*---------------------------------------------------------*/

int gts_master::iipg_scan_get_scanner_info_( void )
{
	if (OK != this->iipg_scan_open_setup_unit_get_spec_()) {
		return NG;
	}

#ifndef _WIN32
	// override some GUI default values from gts_gui.fl
	/* sane_scan.cppでthreshold/brightness/contrastを得ている */
	/* Threshold/Brightness/Contrastの初期設定をGUIに表示 */
	cl_gts_gui.valinp_bw_threshold->value(
		this->cl_iip_scan.d_threshold()
	);
	((Fl_Valuator *)cl_gts_gui.scrbar_bw_threshold)->value(
		this->cl_iip_scan.d_threshold()
	);
	cl_gts_gui.valinp_grayscale_brightness->value(
		this->cl_iip_scan.d_brightness()
	);
	((Fl_Valuator *)cl_gts_gui.scrbar_grayscale_brightness)->value(
		this->cl_iip_scan.d_brightness()
	);
	cl_gts_gui.valinp_rgb_brightness->value(
		this->cl_iip_scan.d_brightness()
	);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_brightness)->value(
		this->cl_iip_scan.d_brightness()
	);
	cl_gts_gui.valinp_grayscale_contrast->value(
		this->cl_iip_scan.d_contrast()
	);
	((Fl_Valuator *)cl_gts_gui.scrbar_grayscale_contrast)->value(
		this->cl_iip_scan.d_contrast()
	);
	cl_gts_gui.valinp_rgb_contrast->value(
		this->cl_iip_scan.d_contrast()
	);
	((Fl_Valuator *)cl_gts_gui.scrbar_rgb_contrast)->value(
		this->cl_iip_scan.d_contrast()
	);
#endif
	/* Area位置とサイズの初期設定をGUIに表示 */
	cl_gts_gui.valinp_area_offset_cm_x->value(0.0);
	cl_gts_gui.valinp_area_offset_cm_y->value(0.0);
	cl_gts_gui.valinp_area_size_cm_w->value(
	 cl_gts_gui.valout_scanner_size_cm_w->value()
	);
	cl_gts_gui.valinp_area_size_cm_h->value(
	 cl_gts_gui.valout_scanner_size_cm_h->value()
	);
	this->cl_area_and_rot90.getset_x_pixel_from_x_size();
	this->cl_area_and_rot90.getset_y_pixel_from_y_size();

	/* TWAIN閉じる */
	if (OK != this->cl_iip_scan.close()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.close() returns NG.");
		return NG;
	}

	return OK;
}

