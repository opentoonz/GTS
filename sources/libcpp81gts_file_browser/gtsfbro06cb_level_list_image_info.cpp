#include <string.h>
#include <time.h>	/* for time_t */
#include <sys/types.h>	/* for stat() */
#include <sys/stat.h>	/* for stat() */
#include "iip_read.h"
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

int gtsfbro06cb_level::_info_datetimereturn( const time_t *tp_time )
{
	struct tm *tp_tm;
	char ca6[6];

	tp_tm = localtime( tp_time );
	if (NULL == tp_tm) {
		pri_funct_err_bttvr(
			"Error : localtime(-) returns NULL.");
		return NG;
	}

	snprintf(ca6,6,"%4d-",  tp_tm->tm_year+1900); this->text_add(ca6);
	snprintf(ca6,6,"%02d-", tp_tm->tm_mon+1); this->text_add(ca6);
	snprintf(ca6,6,"%02d ", tp_tm->tm_mday); this->text_add(ca6);
	snprintf(ca6,6,"%02d:", tp_tm->tm_hour); this->text_add(ca6);
	snprintf(ca6,6,"%02d:", tp_tm->tm_min); this->text_add(ca6);
	snprintf(ca6,6,"%02d\n",  tp_tm->tm_sec); this->text_add(ca6);

	return OK;
}
int gtsfbro06cb_level::_info_image_by_dir_and_file( const char *ccp_dir, const char *ccp_file )
{
	struct stat t_stat;
	iip_read cl_iip_read;
	char ca16[16];

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

	/* textクリア */
	this->text_clear();

	this->text_add("Dir : ");
	 this->text_add(ccp_dir);
	  this->text_add("\n");
	this->text_add("File\n");
	 this->text_add(" Name : ");
	  this->text_add(ccp_file);

	/* File情報 */
	if (stat( this->cp_path(), &t_stat)) {
		/* ファイルがない場合は、そう表示し... */
		this->text_add(" is not exist\n");
		/* 画像を非表示し... */
		cl_gts_gui.box_level_image->hide();
		cl_gts_gui.box_level_x1view->hide();
		/* 後の表示はしない */
		return OK;
	}
	/* 情報表示 */
	this->text_add("\n");

	this->text_add(" Size : ");
	snprintf(ca16,16,"%d bytes\n",  (int)t_stat.st_size);
	this->text_add(ca16);

	this->text_add(" Last Modify : ");
	if (OK != this->_info_datetimereturn(&t_stat.st_mtime)) {
		pri_funct_err_bttvr(
	 "Error : this->_info_datetimereturn(-) returns NG" );
		return NG;
	}

	this->text_add(" Last Change : ");
	if (OK != this->_info_datetimereturn(&t_stat.st_ctime)) {
		pri_funct_err_bttvr(
	 "Error : this->_info_datetimereturn(-) returns NG" );
		return NG;
	}

	/* 画像ヘッド情報読込み */
	if (OK != cl_iip_read.cl_name.set_name( this->cp_path() )) {
		pri_funct_err_bttvr(
	"Error :  cl_iip_read.cl_name.set_name(%s) returns NG",
			this->cp_path()
		);
		return NG;
	}
	if (OK != cl_iip_read.header()) {
		pri_funct_err_bttvr(
	"Error :  cl_iip_read.header() returns NG"
		);
		return NG;
	}

	this->text_add("Image\n");
	 this->text_add(" Size(WxH  Pix) : ");
	  snprintf(ca16,16,"%ld", cl_iip_read.get_l_width() );
	  this->text_add(ca16);
	  this->text_add("x");
	  snprintf(ca16,16,"%ld", cl_iip_read.get_l_height() );
	  this->text_add(ca16);
	this->text_add("  ");
	switch (cl_iip_read.get_l_channels()) {
	case 4: this->text_add("RGBA"); break;
	case 3: this->text_add("RGB"); break;
	case 1: if (E_CH_NUM_BITBW ==
		cl_iip_read.cl_ch_info.get_e_ch_num_type()) {
			this->text_add("BW"); break;
		} else {
			this->text_add("Grayscale"); break;
		}
		break;
	}
	this->text_add(" ");
	/* 本来は"/usr/include/limits.h"のCHAR_BITから値を求めるが
	ここでは簡略化した */
	switch (cl_iip_read.cl_ch_info.get_e_ch_num_type()) {
	case E_CH_NUM_EMPTY: this->text_add("0"); break;
	case E_CH_NUM_UCHAR: this->text_add("8"); break;
	case E_CH_NUM_USHRT: this->text_add("16"); break;
	case E_CH_NUM_ULONG: this->text_add("32"); break;
	case E_CH_NUM_DOUBL: this->text_add("64"); break;
	case E_CH_NUM_BITBW: this->text_add("1"); break;
	}
	this->text_add("bits\n");

	if (	cl_iip_read.get_d_tif_dpi_x() ==
		cl_iip_read.get_d_tif_dpi_y()
	) {
		this->text_add(" DPI : ");
		snprintf(ca16,16,"%g", cl_iip_read.get_d_tif_dpi_x() );
		this->text_add(ca16);
	} else {
		this->text_add(" DPI(X Y) : ");
		snprintf(ca16,16,"%g", cl_iip_read.get_d_tif_dpi_x() );
		this->text_add(ca16);
		snprintf(ca16,16," %g", cl_iip_read.get_d_tif_dpi_y() );
		this->text_add(ca16);
	}
	// this->text_add("\n");

	/* 画像表示 */
	if (cl_gts_gui.menite_level_view_sw->value()) {
	 cl_gts_gui.box_level_image->show();
	 cl_gts_gui.box_level_x1view->show();
	 if (OK != this->_image_by_dir_and_file( ccp_dir, ccp_file )) {
		pri_funct_err_bttvr(
	  "Error : this->_image_by_dir_and_file(%s,%s) returns NG",
			ccp_dir, ccp_file
		);
		return NG;
	 }
	} else {
		/* ファイルはあるけど、非表示指定のとき */
		cl_gts_gui.box_level_image->hide();
		cl_gts_gui.box_level_x1view->hide();
	}

	return OK;
}
int gtsfbro06cb_level::_info_image_by_dir_and_num( const char *ccp_file_for_head, int i_num )
{
	const char *ccp_gui_dir;
	char ca4096[4096];

	this->v_path_dir_part_zero();
	this->v_path_dir_part_cutting();

/***pri_funct_msg_vr( "%s %d : ligut_level_info_rgb_sub<%d> <%s>",
__FILE__,
__LINE__,
cl_gts_gui.menite_level_view_rgb_full_sw->value(),
cl_gts_gui.filinp_level_rgb_scan_dir->value()
);***/
	if (cl_gts_gui.menite_level_view_rgb_full_sw->value()) {
		ccp_gui_dir =
			cl_gts_gui.filinp_level_rgb_scan_dir->value();
		if (OK != this->i_lpath_cat_file_for_full(
			ccp_file_for_head, i_num
		)) {
			pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_for_full(%s,%d) returns NG",
				ccp_file_for_head,
				i_num
			);
			return NG;
		}
	} else {
		ccp_gui_dir = cl_gts_gui.filinp_level_dir->value();
		if (OK != this->i_lpath_cat_file_by_num(
			ccp_file_for_head, i_num
		)) {
			pri_funct_err_bttvr(
	 "Error : this->i_lpath_cat_file_by_num(%s,%d) returns NG",
				ccp_file_for_head,
				i_num
			);
			return NG;
		}
	}
	strcpy( ca4096, this->cp_path() );

	/* ファイル情報表示 */
	if (OK != this->_info_image_by_dir_and_file(
		ccp_gui_dir, ca4096
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_info_image_by_dir_and_file(%s,%s)",
		ccp_gui_dir, ca4096
		);
		return NG;
	}

	return OK;
}

/* --------------------------------------------------------- */
/* listクリック時の処理 */
int gtsfbro06cb_level::_list_image_info( ST_DIR_OR_FILE_INFO *stp_dir_or_file_info )
{
	const char *ccp_gui_dir; 

	cl_gts_gui.scroll_level_info_number->slider_size(1.0);

	/* Dir設定 */
	if (E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE ==
	stp_dir_or_file_info->e_type) {
		ccp_gui_dir =
			cl_gts_gui.filinp_level_rgb_scan_dir->value();
	} else
	if (E_DIR_OR_FILE_IS_NUM_IMAGE ==
	stp_dir_or_file_info->e_type) {
		ccp_gui_dir = cl_gts_gui.filinp_level_dir->value();
	}
	else {
		pri_funct_err_bttvr(
		"Error : bad stp_dir_or_file_info->e_type" );
		return NG;
	}
	/* ファイル情報表示 */
	if (OK != this->_info_image_by_dir_and_file(
		ccp_gui_dir, stp_dir_or_file_info->cp_name
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_info_image_by_dir_and_file(%s,%s)",
		ccp_gui_dir, stp_dir_or_file_info->cp_name);
		return NG;
	}

	return OK;
}
int gtsfbro06cb_level::_list_image_info( ST_DIR_OR_LEVEL_INFO *stp_dir_or_level_info )
{
	cl_gts_gui.scroll_level_info_number->linesize(1);
	cl_gts_gui.scroll_level_info_number->slider_size(
		1.0/
		(stp_dir_or_level_info->i_end_num -
		stp_dir_or_level_info->i_start_num + 1)
	);
	cl_gts_gui.scroll_level_info_number->minimum(
		(double)(stp_dir_or_level_info->i_start_num)
	);
	cl_gts_gui.scroll_level_info_number->maximum(
		(double)(stp_dir_or_level_info->i_end_num)
	);
	((Fl_Valuator *)(cl_gts_gui.scroll_level_info_number))->value(
		(double)(stp_dir_or_level_info->i_start_num)
	);

	cl_gts_gui.valinp_level_crnt->value(
		stp_dir_or_level_info->i_start_num
	);

	if (OK != this->_info_image_by_dir_and_num(
		//stp_dir_or_level_info->cp_name,
		stp_dir_or_level_info->name,
		stp_dir_or_level_info->i_start_num
	)) {
		pri_funct_err_bttvr(
	 "Error : this->_info_image_by_dir_and_num(%s,%d)",
		//stp_dir_or_level_info->cp_name,
		stp_dir_or_level_info->name,
		stp_dir_or_level_info->i_start_num
		);
		return NG;
	}

	return OK;
}

/* --------------------------------------------------------- */
/* スクロールバーあるいは数値指定による表示変更 */
/* 表示ON/OFFスイッチによる表示変更 */
void gtsfbro06cb_level::cb_info_redisplay( void )
{
	int	i_list_num;
	ST_DIR_OR_LEVEL_INFO *stp_dir_or_level_info;
	ST_DIR_OR_FILE_INFO *stp_dir_or_file_info;
	const char *ccp_gui_dir; 

	/* listが選択していないときは動作しない */
	i_list_num = cl_gts_gui.selbro_level_list->value() - 1;
	if (i_list_num < 0) {
		return;
	}

	/* list表示が各file毎のとき */
	if (0 == cl_gts_gui.choice_level_list_form->value()) {
		stp_dir_or_file_info =
			this->stp_dir_or_file_info(i_list_num);
		if (NULL == stp_dir_or_file_info) {
			pri_funct_err_bttvr(
		 "Error : this->stp_dir_or_file_info(%d) returns NULL",
				i_list_num );
			return;
		}
		/* Dir設定 */
		if (E_DIR_OR_FILE_IS_NOT_TRACEING_RGB_IMAGE ==
		stp_dir_or_file_info->e_type) {
			ccp_gui_dir =
			 cl_gts_gui.filinp_level_rgb_scan_dir->value();
		} else
		if (E_DIR_OR_FILE_IS_NUM_IMAGE ==
		stp_dir_or_file_info->e_type) {
			ccp_gui_dir =
			 cl_gts_gui.filinp_level_dir->value();
		}
		else {
			pri_funct_err_bttvr(
			"Error : bad stp_dir_or_file_info->e_type" );
			return;
		}
		/* ファイル情報表示 */
		if (OK != this->_info_image_by_dir_and_file(
			ccp_gui_dir, stp_dir_or_file_info->cp_name
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_info_image_by_dir_and_file(%s,%s)",
			ccp_gui_dir, stp_dir_or_file_info->cp_name);
			return;
		}

		return;
	} else {
	/* list表示が各level毎のとき */
		stp_dir_or_level_info =
			this->stp_dir_or_level_info(i_list_num);
		if (NULL == stp_dir_or_level_info) {
			pri_funct_err_bttvr(
		 "Error : this->stp_dir_or_level_info(%d) returns NULL",
				i_list_num );
			return;
		}

		if (OK != this->_info_image_by_dir_and_num(
			//stp_dir_or_level_info->cp_name,
			stp_dir_or_level_info->name,
			cl_gts_gui.scroll_level_info_number->value()
		)) {
			pri_funct_err_bttvr(
		 "Error : this->_info_image_by_dir_and_num(%s,%d)",
			//stp_dir_or_level_info->cp_name,
			stp_dir_or_level_info->name,
			cl_gts_gui.scroll_level_info_number->value()
			);
			return;
		}
	}
	return;
}
