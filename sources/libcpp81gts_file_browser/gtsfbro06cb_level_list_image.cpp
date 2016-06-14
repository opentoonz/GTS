#include <time.h>	/* clock() */
#include <math.h>	/* for pow() */
#include <FL/Fl_Image.H>
#include "ptbl_funct.h"
#include "iip_precision.h"
#include "iip_read.h"
#include "iip_scale_by_subpixel.h"
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

int gtsfbro06cb_level::_image_by_dir_and_file( const char *ccp_dir, const char *ccp_file )
{
	clock_t t_start;
	double d_ratio, d_scale;
	long l_margin;
	static iip_read			*clp_iip_read = NULL;
	static iip_precision		*clp_iip_prec = NULL;
	static iip_scale_by_subpixel	*clp_iip_scal = NULL;
	static Fl_RGB_Image		*clp_fl_rgb_image = NULL;
	static Fl_RGB_Image		*clp_x1_fl_rgb_image = NULL;
	static char ca32[32];

	t_start = clock(); /* 処理開始直前の時間を保存 */

	/* FilePath設定 */
	if (OK != this->i_path_dir_file(
			ccp_dir, ccp_file
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NG",
			ccp_dir, ccp_file
		);
		return NG;
	}

	if (!ptbl_dir_or_file_is_exist( this->cp_path() )) {
		/* ファイルがない */
		return OK;
	}

	if (NULL !=	clp_x1_fl_rgb_image) {
		delete	clp_x1_fl_rgb_image;
			clp_x1_fl_rgb_image=NULL;
	}
	if (NULL !=	clp_fl_rgb_image) {
		delete	clp_fl_rgb_image;
			clp_fl_rgb_image=NULL;
	}
	if (NULL !=	clp_iip_scal) {
		delete	clp_iip_scal;
			clp_iip_scal=NULL;
	}
	if (NULL !=	clp_iip_prec) {
		delete	clp_iip_prec;
			clp_iip_prec=NULL;
	}
	if (NULL !=	clp_iip_read) {
		delete	clp_iip_read;
			clp_iip_read=NULL;
	}
	clp_iip_read = new iip_read;
	clp_iip_prec = new iip_precision;
	clp_iip_scal = new iip_scale_by_subpixel;

	/* 画像読込み */
	if (OK != clp_iip_read->cl_name.set_name( this->cp_path() )) {
		pri_funct_err_bttvr(
	"Error :  clp_iip_read->cl_name.set_name(%s) returns NG",
			this->cp_path()
		);
		return NG;
	}
	if (OK != clp_iip_read->file()) {
		pri_funct_err_bttvr(
	"Error :  clp_iip_read->file() returns NG"
		);
		return NG;
	}
	if (clp_iip_read->get_l_width() <= 0L) {
		pri_funct_err_bttvr(
  "Error :  clp_iip_read->get_l_width() returns less than 1"
		);
		return NG;
	}
	if (clp_iip_read->get_l_height() <= 0L) {
		pri_funct_err_bttvr(
  "Error :  clp_iip_read->get_l_height() returns less than 1"
		);
		return NG;
	}

	/* 親子接続 */
	clp_iip_prec->set_clp_parent(clp_iip_read);
	clp_iip_scal->set_clp_parent(clp_iip_prec);

	/* 親の画像大きさをセット */
	clp_iip_prec->set_canvas_size(clp_iip_read);

	/* スケール処理と表示はすべてuchar(CHAR_BITS)サイズ
	白黒２値画像はGrayScaleにする */
	clp_iip_prec->cl_ch_info.set_e_ch_num_type(
		E_CH_NUM_UCHAR
	);

	/* 親の画像大きさをセット */
	clp_iip_scal->set_canvas_size(clp_iip_prec);

	/* 表示widgetの大きさにスケールをかける */
	l_margin = 24;
	d_ratio = (double)(	clp_iip_read->get_l_width()) /
				clp_iip_read->get_l_height();
	if (	d_ratio <
		((double)(cl_gts_gui.box_level_image->w()-l_margin) /
			 (cl_gts_gui.box_level_image->h()-l_margin)
		)
	) {
		/* 横幅が大きい */
		clp_iip_scal->set_l_width(
		 (long)((cl_gts_gui.box_level_image->h()-l_margin) *
			 d_ratio
		 )
		);
		clp_iip_scal->set_l_height(
			cl_gts_gui.box_level_image->h()-l_margin);

		d_scale = (double)(clp_iip_scal->get_l_height()) /
				clp_iip_read->get_l_height();
	} else {
		/* 縦幅が大きい */ 
		clp_iip_scal->set_l_width(
			cl_gts_gui.box_level_image->w()-l_margin);
		clp_iip_scal->set_l_height(
		 (long)( (cl_gts_gui.box_level_image->w()-l_margin) /
			 d_ratio
		 )
		);

		d_scale = (double)(clp_iip_scal->get_l_width()) /
				clp_iip_read->get_l_width();
	}

	/* 画像カンバスの準備 */
	if (OK != clp_iip_prec->set_canvas()) {
		pri_funct_err_bttvr(
	 "Error : clp_iip_prec->set_canvas() returns NG" );
		return NG;
	}
	if (OK != clp_iip_scal->set_canvas()) {
		pri_funct_err_bttvr(
	 "Error : clp_iip_scal->set_canvas() returns NG" );
		return NG;
	}

	/* 画像生成 */
	clp_iip_prec->exec();
	clp_iip_scal->exec();

	/*上下反転 */
	unsigned char *ucharp_top;
	unsigned char *ucharp_bot;
	unsigned char uchar_tmp;
	long xx,yy,zz,cc, l_w,l_h,l_ch,l_w_ch;
	double d_gamma;

	ucharp_top = (unsigned char *)(clp_iip_scal->get_vp_canvas());
	ucharp_bot = ucharp_top +
			clp_iip_scal->get_l_channels() *
			clp_iip_scal->get_l_width() *
		       (clp_iip_scal->get_l_height()-1);
	l_h = clp_iip_scal->get_l_height()/2;
	l_w = clp_iip_scal->get_l_width();
	l_ch = clp_iip_scal->get_l_channels();
	l_w_ch = l_w * l_ch;
	for (yy = 0L; yy < l_h; ++yy) {
	 for (xx = 0L; xx < l_w; ++xx) {
	  for (zz = 0L; zz < l_ch; ++zz) {
		cc = xx * l_ch + zz;
		uchar_tmp = ucharp_top[cc];
		ucharp_top[cc] = ucharp_bot[cc];
		ucharp_bot[cc] = uchar_tmp;
	  }
	 }
	 ucharp_top += l_w_ch;
	 ucharp_bot -= l_w_ch;
	}
	/* 線強調(ガンマ補正による) */
	d_gamma = 1.5;
	ucharp_top = (unsigned char *)(clp_iip_scal->get_vp_canvas());
	l_h = clp_iip_scal->get_l_height();
	for (yy = 0L; yy < l_h; ++yy) {
	 for (xx = 0L; xx < l_w; ++xx) {
	  for (zz = 0L; zz < l_ch; ++zz) {
		ucharp_top[0] = (unsigned char)(
			pow(ucharp_top[0]/255.0, d_gamma) * 255.999999
		);
		++ ucharp_top;
	  }
	 }
	}

	/* 画像設定 */
	clp_fl_rgb_image = new Fl_RGB_Image(
		(const unsigned char *)(clp_iip_scal->get_vp_canvas()),
		(int)(clp_iip_scal->get_l_width()),
		(int)(clp_iip_scal->get_l_height()),
		(int)(clp_iip_scal->get_l_channels())
	);

	/* 表示 */
	cl_gts_gui.box_level_image->image( clp_fl_rgb_image );
	cl_gts_gui.box_level_image->align(
		FL_ALIGN_CENTER | FL_ALIGN_CLIP );

	/* x1viewへ表示 ------------------------------------------- */
	ucharp_top = (unsigned char *)(clp_iip_prec->get_vp_canvas());
	ucharp_bot = ucharp_top +
			clp_iip_prec->get_l_channels() *
			clp_iip_prec->get_l_width() *
		       (clp_iip_prec->get_l_height()-1);
	l_h = clp_iip_prec->get_l_height()/2;
	l_w = clp_iip_prec->get_l_width();
	l_ch = clp_iip_prec->get_l_channels();
	l_w_ch = l_w * l_ch;
	for (yy = 0L; yy < l_h; ++yy) {
	 for (xx = 0L; xx < l_w; ++xx) {
	  for (zz = 0L; zz < l_ch; ++zz) {
		cc = xx * l_ch + zz;
		uchar_tmp = ucharp_top[cc];
		ucharp_top[cc] = ucharp_bot[cc];
		ucharp_bot[cc] = uchar_tmp;
	  }
	 }
	 ucharp_top += l_w_ch;
	 ucharp_bot -= l_w_ch;
	}
	clp_x1_fl_rgb_image = new Fl_RGB_Image(
		(const unsigned char *)(clp_iip_prec->get_vp_canvas()),
		(int)(clp_iip_prec->get_l_width()),
		(int)(clp_iip_prec->get_l_height()),
		(int)(clp_iip_prec->get_l_channels())
	);
	cl_gts_gui.box_level_x1view->image( clp_x1_fl_rgb_image );
	cl_gts_gui.box_level_x1view->size(
		(int)(clp_iip_prec->get_l_width()),
		(int)(clp_iip_prec->get_l_height())
	);
	cl_gts_gui.box_level_x1view->redraw();

	/* 画像表示のための全時間をはかり表示する ----------------- */
	t_start = clock() - t_start;
		/* 123456789012345678901234567 */
		/* 10.123%(100x100)(10.123sec) */
	snprintf( ca32,32,"%7.3f%%(%ldx%ld)(%.3gsec)",
		d_scale*100.0,
		clp_iip_scal->get_l_width(),
		clp_iip_scal->get_l_height(),
		(double)t_start/CLOCKS_PER_SEC
	);
	cl_gts_gui.box_level_image->label( ca32 );
	cl_gts_gui.box_level_image->redraw();

	return OK;
}
