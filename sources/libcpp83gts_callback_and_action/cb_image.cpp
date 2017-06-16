#include <iostream>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "pri.h"
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
		"Open Image"
		,this->dir_path_.c_str()
		//,this->open_file_name_.c_str()
		,""
		,this->ext_open.get_native_filters()
		,filter_current
	).at(0);

	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* fpathからfolderpathとfilenameを記憶しとく */
	this->ext_open_filter_current_ = filter_current;
	ids::path::from_fpath_to_dpath_fname(
		fpath ,this->dir_path_ ,this->open_file_name_
	);
	this->save_file_name_ = this->open_file_name_;

	/* 画像読込表示 */
	cl_gts_master.cb_read_and_trace_and_preview( fpath );
}

void cb_image::save_as( void )
{
	/* Crop中は保存できない */
	if (cl_gts_master.cl_ogl_view.get_crop_disp_sw()) {
		fl_alert("Finish Cropping, Please Scan.");
		return;
	}
	/* ScanもReadもまだしていない */
	if (cl_gts_master.cl_iip_ro90.get_clp_parent() == nullptr ) {
		fl_alert("Please Any Scan or Open.");
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
		fl_alert("No Image");
		return;
	}

	/* NativeブラウザーSaveで開く */
	int filter_current = this->ext_save_filter_current_;
	std::string fpath = ids::path::fltk_native_browse_save(
		"Save Image As"
		,this->dir_path_
		,this->save_file_name_
		,this->ext_save.get_native_filters()
		,filter_current
	).at(0);

	/* Cancel */
	if (fpath.empty()) {
		return;
	}

	/* 保存名を記憶(開いた名前は変わらない) */
	ids::path::from_fpath_to_dpath_fname(
		fpath
		,this->dir_path_
		,this->save_file_name_
	);
	this->ext_save_filter_current_ = filter_current;

	/* 拡張子がなければ追加 */
	this->add_ext_if_not_exist( fpath );

	/* 処理：Rot90 and Effects(color Trace and Erase color dot noise) */
	if (cl_gts_master.rot_and_trace_and_enoise( parent ,rot90 ) != OK) {
		fl_alert("Effects Error");
		return;
	}

	/* 保存 */
	if (OK != cl_gts_master.iipg_save(
		&(cl_gts_master.cl_iip_edot)
		,const_cast<char *>(fpath.c_str())
		,dpi
		,rot90
		,read_attr
	)) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.iipg_save(-) returns NG" );
		fl_alert("Save \"%s\" Error" ,fpath.c_str() );
		return;
	}
}

void cb_image::add_ext_if_not_exist( std::string&fpath )
{
	/* fpathから拡張子を得る */

	/* 拡張子が規定の物かどうか調べる */
	for (int ii=0; ii<this->ext_save.size() ;++ii) {
		this->ext_save.str_from_num()
	}

	/* 拡張子が規定の物でないときは現在の指定の拡張子を与える、指定が複数の場合はデフォルト拡張子を与える???? */
	if ((fpath.size() < ext.size())
	||  (fpath.substr(fpath.size()-ext.size()) != ext)) {
		fpath += ext;
	}
}
