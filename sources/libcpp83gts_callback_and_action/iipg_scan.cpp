#include <iostream>
#include <string>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

/* スキャナーのハードウェア情報をメニューに設定 */
void gts_master::_iipg_scan_set_physical_param( void )
{
	double	d_maxcm_w ,d_maxcm_h;

	/* スキャナーから回転処理含んだメニューに設定する最大広さ値を得る */
	this->__area_rot90_size(
		cl_gts_gui.choice_rot90->value()
		, this->cl_iip_scan.d_physical_width()
		, this->cl_iip_scan.d_physical_height()
		, &d_maxcm_w
		, &d_maxcm_h
	);
std::cout
	<< "Scanner Physical Size Rotated\n"
	<< " W=" << d_maxcm_w
	<< " H=" << d_maxcm_h
	<< std::endl;

	/* メニューに設定 */
	cl_gts_gui.valout_scanner_width_max->value(d_maxcm_w);
	cl_gts_gui.valout_scanner_height_max->value(d_maxcm_h);

	/* マシンの型番をメニューにセット */
	cl_gts_gui.txtout_scanner_type->value(
		this->cl_iip_scan.get_cp_machine_type()
	);
}

void gts_master::_iipg_scan_get_from_gui( const bool full_area_sw )
{
	double	d_cm_x,d_cm_y,d_cm_w,d_cm_h;

std::cout
	<< "GUI\n"
	<< " RotNo  =" << cl_gts_gui.choice_rot90->value() << "\n"
	<< " Start X=" << cl_gts_gui.valinp_area_x_pos->value()
	<<       " Y=" << cl_gts_gui.valinp_area_y_pos->value() << "\n"
	<< " Size  W=" << cl_gts_gui.valinp_area_x_size->value()
	<<       " H=" << cl_gts_gui.valinp_area_y_size->value() << "\n"
	<< " Max   W=" << cl_gts_gui.valout_scanner_width_max->value()
	<<       " H=" << cl_gts_gui.valout_scanner_height_max->value()
	<< std::endl;

	if (full_area_sw) {
		double	d_maxcm_w,d_maxcm_h;
		/* スキャナーからメニューに設定する最大広さ値を得る */
		this->__area_rot90_size(
			cl_gts_gui.choice_rot90->value()
			, this->cl_iip_scan.d_physical_width()
			, this->cl_iip_scan.d_physical_height()
			, &d_maxcm_w
			, &d_maxcm_h
		);
		/* メニュー値からスキャナーへ渡す値を得る */
		this->__area_rot90_d_pos_and_size(
			-cl_gts_gui.choice_rot90->value()/* マイナス回転 */
			, 0.0
			, 0.0
			, d_maxcm_w
			, d_maxcm_h
			, d_maxcm_w
			, d_maxcm_h
			, &d_cm_x
			, &d_cm_y
			, &d_cm_w
			, &d_cm_h
		);
	}
	else {
		this->__area_rot90_d_pos_and_size(
			-cl_gts_gui.choice_rot90->value()/* マイナス回転 */
			, cl_gts_gui.valinp_area_x_pos->value()
			, cl_gts_gui.valinp_area_y_pos->value()
			, cl_gts_gui.valinp_area_x_size->value()
			, cl_gts_gui.valinp_area_y_size->value()
			, cl_gts_gui.valout_scanner_width_max->value()
			, cl_gts_gui.valout_scanner_height_max->value()
			, &d_cm_x
			, &d_cm_y
			, &d_cm_w
			, &d_cm_h
		);
	}

std::cout
	<< "Scan\n"
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
# ifndef _WIN32
    // the requested resolution may be adjusted, so update the GUI value
    cl_gts_gui.valinp_area_reso->value(this->cl_iip_scan.d_x_resolution());
# endif

	/* ピクセルタイプ */
	/* cl_gts_gui.choice_pixel_type -> 0:bw,1:gray,2:rgb */
	/* cl_iip_scan -> E_PIXELTYPE_BW/..._GRAYSCALE/..._RGB */
	switch (cl_gts_gui.choice_pixel_type->value()) {
	case 0:	/* bw */
		this->cl_iip_scan.e_pixeltype( E_PIXELTYPE_BW );
		this->cl_iip_scan.d_threshold(
			cl_gts_gui.valinp_bw_threshold->value() );

		/******this->cl_iip_scan.d_brightness( 0.0 );
		this->cl_iip_scan.d_contrast( 0.0 );
		this->cl_iip_scan.d_gamma( 1.0 );*****/

		break;
	case 1:	/* grayscale */
		this->cl_iip_scan.e_pixeltype( E_PIXELTYPE_GRAYSCALE );

		/***this->cl_iip_scan.d_threshold( 0.0 );***/

		this->cl_iip_scan.d_brightness(
			cl_gts_gui.valinp_grayscale_brightness->value() );
		this->cl_iip_scan.d_contrast(
			cl_gts_gui.valinp_grayscale_contrast->value() );
		this->cl_iip_scan.d_gamma(
			cl_gts_gui.valinp_grayscale_gamma->value() );
		break;
	case 2:	/* rgb */
		this->cl_iip_scan.e_pixeltype( E_PIXELTYPE_RGB );

		/***this->cl_iip_scan.d_threshold( 0.0 );***/

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
}

int gts_master::_iipg_scan_action( const bool full_area_sw )
{
	/* スキャナーに対して、スキャンの単位を一番始めに設定 */
	if (OK != this->cl_iip_scan.setup_unit()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.setup_unit() returns NG.");
		return NG;
	}

	/* スキャナーのハード情報を取って来て... */
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

	/* ...メニューにセット */
	this->_iipg_scan_set_physical_param();

	/* メニューの(スキャン動作)情報を取って来て... */
	this->_iipg_scan_get_from_gui( full_area_sw );

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
	if (OK != this->cl_iip_scan.read()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.read() returns NG.");
		return NG;
	}
	return OK;
}

/*---------------------------------------------------------*/

iip_canvas *gts_master::iipg_scan( const bool full_area_sw )
{
	int	i_ret;

	/* すべてセンチメータ単位で処理する */
	this->cl_iip_scan.i_centimeters_sw(ON);

	if (OK != this->cl_iip_scan.open()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.open() returns NG.");
		return NULL;
	}

	i_ret = OK;
	if (OK != this->_iipg_scan_action( full_area_sw )) {
		pri_funct_err_bttvr(
	 "Error : this->_iipg_scan_action(-) returns NG.");
		/* ここでエラーがおきてもclose()はやる */
		i_ret = NG;
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
	if (NG == i_ret) { return NULL; }

	return this->cl_iip_scan.get_clp_canvas();
}

/*---------------------------------------------------------*/

int gts_master::_iipg_scan_get_scanner_info( void )
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

	/* スキャナーのハード情報を取って来て... */
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

	// override some GUI default values from gts_gui.fl
	if(this->cl_iip_scan.d_x_native_resolution()) {
		// from scanner
		cl_gts_gui.valinp_area_reso->value(
			this->cl_iip_scan.d_x_native_resolution()
		);
	} else {
		// from header
		cl_gts_gui.valinp_area_reso->value(
			this->cl_iip_scan.d_x_resolution()
		);
	}
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

	/* ...メニューにセット */
	this->_iipg_scan_set_physical_param();

	/* TWAIN閉じる */
	if (OK != this->cl_iip_scan.close()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_scan.close() returns NG.");
		return NG;
	}

	return OK;
}
