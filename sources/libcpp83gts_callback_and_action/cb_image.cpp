#include <iostream>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "pri.h"
#include "osapi_exist.h" // osapi::exist_utf8_mbs(-)
#include "gts_str_language.h"	// gts_str::
#include "ids_path_level_from_files.h"
#include "ids_path_fltk_native_browse.h"
#include "cb_image.h"
#include "gts_gui.h"
#include "gts_master.h"

void cb_image::open( void )
{
	/* NativeブラウザーOpenで開く */
	int filter_current = this->ext_open_filter_current_;
	const std::string fpath = ids::path::fltk_native_browse_open(
//		"Open Image"
		gts_str::image::open
		,this->dir_path_
		,"" /* 開くときは選択が必須のためファイル名は空白表示 */
		,this->ext_open.get_native_filters()
		,filter_current
	).at(0);

	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* 有効なパスを開いたらその状態を記憶する */
	ids::path::from_fpath_to_dpath_fname(
		fpath ,this->dir_path_ ,this->open_file_name_
	);
	this->ext_open_filter_current_ = filter_current;

	/* 次の保存時は、ここで開いた名前と拡張子が初期値 */
	this->save_file_name_ = this->open_file_name_;
	this->ext_save_filter_current_ = this->ext_open_filter_current_;

	/* 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview( fpath );

	/* 画像を開いたときの初期表示を元画像の表示にする */
	cl_gts_master.cb_change_wview_main();
	cl_gts_gui.menite_wview_main->setonly();
}

void cb_image::save_as( void )
{
	/* Crop中は保存できない */
	if (cl_gts_master.cl_ogl_view.get_crop_disp_sw()) {
		fl_alert(
//			"Finish Cropping, Please Scan."
			gts_str::image::save_as_can_not_when_crop
		);
		return;
	}
	/* ScanもReadもまだしていない */
	if (cl_gts_master.cl_iip_ro90.get_clp_parent() == nullptr ) {
		fl_alert(
//			"Please Any Scan or Open."
			gts_str::image::no_image
		);
		return;
	}

	/* parameter */
	iip_canvas* parent = nullptr;
	int rot90=0;
	double dpi = 0;
	iip_read* read_attr = nullptr;

	/* ファイル読込後 */
	if ( &(cl_gts_master.cl_iip_read)
	==     cl_gts_master.cl_iip_ro90.get_clp_parent() ) {
		parent = &(cl_gts_master.cl_iip_read);
		rot90 = 0; /* 画像コンバート処理のみで、回転はしない */
		dpi = cl_gts_master.cl_iip_read.get_d_tif_dpi_x();
		read_attr = &(cl_gts_master.cl_iip_read);
	}
	else
	/* スキャン後 */
	if (   cl_gts_master.cl_iip_scan.get_clp_canvas()
	==     cl_gts_master.cl_iip_ro90.get_clp_parent() ) {
		parent = cl_gts_master.cl_iip_scan.get_clp_canvas();
		rot90 = cl_gts_gui.choice_rot90->value();
		dpi = cl_gts_gui.valinp_area_reso->value();
	} else {
		fl_alert(
//			"No Image"
			gts_str::image::no_image
		);
		return;
	}

	/* NativeブラウザーSaveで開く */
	int filter_current = this->ext_save_filter_current_;
	std::string fpath;
	if (this->save_as_set_scan_images_path_sw) {
		fpath = ids::path::fltk_native_browse_save(
//		"Save Image As"
		gts_str::image::save_as
		,cl_gts_gui.filinp_scan_save_dir_path->value()
		,cl_gts_gui.strinp_scan_save_file_head->value()
		,this->ext_save.get_native_filters()
		,filter_current
		).at(0);
	} else {
		fpath = ids::path::fltk_native_browse_save(
//		"Save Image As"
		gts_str::image::save_as
		,this->dir_path_
		,this->save_file_name_
		,this->ext_save.get_native_filters()
		,filter_current
		).at(0);
	}

	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* 拡張子がなければ */
	if (this->ext_save_is_exist_( fpath ) == false) {
		/* 拡張子指定されていれば */
		if (filter_current < this->ext_save.size()) {
			/* 拡張子追加する */
			fpath+= this->ext_save.str_from_num(filter_current);

			/* ダイオローグを表示 */
			if (osapi::exist_utf8_mbs(fpath)) {
				/* すでに存在するなら上書き確認 */
				if (0 == fl_ask(
//			"Overwrite \"%s\"?"
					gts_str::config::ask_overwrite
					,fpath.c_str() )){
					return;
				}
			}
		}
		/* ユーザーによる拡張子指定ない
		(Image Files(*.tga;*.tif)/All Files(*.*)) */
		else {
			fl_alert(
//			"Need Extension."
				gts_str::image::need_extension
			);
			return;
		}
	}

	/* 有効なパスを開いたらその状態を記憶する */
	ids::path::from_fpath_to_dpath_fname(
		fpath ,this->dir_path_ ,this->save_file_name_
	);
	this->ext_save_filter_current_ = filter_current;

	/* 処理：Rot90 and Effects(color Trace and Erase color dot noise) */
	if (cl_gts_master.rot_and_trace_and_enoise( parent ,rot90 ) != OK) {
		fl_alert(
//			"Effects Error"
			gts_str::image::effects_error
		);
		return;
	}

	/* 保存 */
	if (OK != cl_gts_master.iipg_save(
		&(cl_gts_master.cl_iip_edot)
				/* 処理したEffectの最後Node画像を保存 */
		// &(cl_gts_master.cl_iip_ro90)
				/* スキャン画像の保存 */
		,const_cast<char *>(fpath.c_str())
		,dpi

		//,rot90
 /* 2019-04-08 回転処理してあるのにさらに"rot90"で回転タグつけてはダメ */
		,0

		,read_attr
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.iipg_save(-) returns NG" );
		fl_alert(
//			"Save \"%s\" Error"
			gts_str::image::save_error
			,fpath.c_str() );
		return;
	}
}

bool cb_image::ext_save_is_exist_( std::string& fpath )
{
	/* 拡張子が規定の物なら、既に有効な拡張子が付いている */
	for (int ii=0; ii<this->ext_save.size() ;++ii) {
		/* 各拡張子... */
		std::string ext( this->ext_save.str_from_num(ii) );

		/* パスが各拡張子より長く... */
		if ((ext.size() <= fpath.size())
		/* 拡張子が同一である */
		&&  (ext == fpath.substr(fpath.size()-ext.size()))) {
			return true;
		}
	}
	return false;
}
