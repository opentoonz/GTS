#include "memory_config.h"
#include "memory_config_trace_src_hsv.h"
#include "gts_gui.h"
#include "gts_master.h"

int memory_config::_save_trace_src_hsv_by_fp( FILE *fp )
{
	const char *ccp_chk = "%-24s %s\n";
	const char *ccp_src = "%-24s %.16g\n";
	const char *ccp_tgt = "%-24s %d %d %d\n";

	int	i_ret;
	unsigned char uchar_red, uchar_gre, uchar_blu;

	/* 01 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, STR_COLOR_TRACE_01_CHK,
		cl_gts_gui.chkbtn_color_trace_01_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_01_SRC_HH_MIN,
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_01_SRC_HH_MAX,
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_01_SRC_AA_MIN,
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_01_SRC_AA_MAX,
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_01_SRC_BB_MIN,
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_01_SRC_BB_MAX,
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_01,
		&uchar_red, &uchar_gre, &uchar_blu );

	i_ret = fprintf(fp, ccp_tgt, STR_COLOR_TRACE_01_TGT_RGB,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/* 02 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, STR_COLOR_TRACE_02_CHK,
		cl_gts_gui.chkbtn_color_trace_02_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_02_SRC_HH_MIN,
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_02_SRC_HH_MAX,
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_02_SRC_AA_MIN,
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_02_SRC_AA_MAX,
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_02_SRC_BB_MIN,
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_02_SRC_BB_MAX,
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_02,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, STR_COLOR_TRACE_02_TGT_RGB,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/* 03 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, STR_COLOR_TRACE_03_CHK,
		cl_gts_gui.chkbtn_color_trace_03_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_03_SRC_HH_MIN,
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_03_SRC_HH_MAX,
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_03_SRC_AA_MIN,
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_03_SRC_AA_MAX,
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_03_SRC_BB_MIN,
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_03_SRC_BB_MAX,
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_03,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, STR_COLOR_TRACE_03_TGT_RGB,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/* 04 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, STR_COLOR_TRACE_04_CHK,
		cl_gts_gui.chkbtn_color_trace_04_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_04_SRC_HH_MIN,
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_04_SRC_HH_MAX,
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_04_SRC_AA_MIN,
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_04_SRC_AA_MAX,
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_04_SRC_BB_MIN,
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_04_SRC_BB_MAX,
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_04,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, STR_COLOR_TRACE_04_TGT_RGB,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/* 05 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, STR_COLOR_TRACE_05_CHK,
		cl_gts_gui.chkbtn_color_trace_05_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_05_SRC_HH_MIN,
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_05_SRC_HH_MAX,
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_05_SRC_AA_MIN,
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_05_SRC_AA_MAX,
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_05_SRC_BB_MIN,
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_05_SRC_BB_MAX,
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_05,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, STR_COLOR_TRACE_05_TGT_RGB,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/* 06 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, STR_COLOR_TRACE_06_CHK,
		cl_gts_gui.chkbtn_color_trace_06_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_06_SRC_HH_MIN,
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_06_SRC_HH_MAX,
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_06_SRC_AA_MIN,
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_06_SRC_AA_MAX,
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_06_SRC_BB_MIN,
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, STR_COLOR_TRACE_06_SRC_BB_MAX,
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_06,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, STR_COLOR_TRACE_06_TGT_RGB,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*------------------------------------------------*/
	return OK;
}
