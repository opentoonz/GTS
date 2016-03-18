#include "memory_config_trace_src_hls.h"

int memory_config::_save_trace_src_hls_by_fp( FILE *fp )
{
	/*------------------------------------------------*/
	/*- 01 ----*/

	i_ret = fprintf(fp, "%-24s %s\n", STR_COLOR_TRACE_01_CHK,
			cl_gts_gui.chkbtn_color_trace_01_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_01_HUE_MIN,
		cl_gts_gui.valinp_color_trace_01_hue_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_01_HUE_MAX,
		cl_gts_gui.valinp_color_trace_01_hue_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_01_LIG_MIN,
		cl_gts_gui.valinp_color_trace_01_lig_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_01_LIG_MAX,
		cl_gts_gui.valinp_color_trace_01_lig_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_01_SAT_MIN,
		cl_gts_gui.valinp_color_trace_01_sat_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_01_SAT_MAX,
		cl_gts_gui.valinp_color_trace_01_sat_max->value() );
	if (i_ret < 0) { return NG; }

	/***Fl::get_color(
		Fl_Color(FL_FREE_COLOR + 0),
		uchar_red, uchar_gre, uchar_blu
	);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_01,
		&uchar_red, &uchar_gre, &uchar_blu );

	i_ret = fprintf(fp, "%-24s %d %d %d\n", STR_COLOR_TRACE_01_TGT,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*- 02 ----*/

	i_ret = fprintf(fp, "%-24s %s\n", STR_COLOR_TRACE_02_CHK,
			cl_gts_gui.chkbtn_color_trace_02_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_02_HUE_MIN,
		cl_gts_gui.valinp_color_trace_02_hue_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_02_HUE_MAX,
		cl_gts_gui.valinp_color_trace_02_hue_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_02_LIG_MIN,
		cl_gts_gui.valinp_color_trace_02_lig_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_02_LIG_MAX,
		cl_gts_gui.valinp_color_trace_02_lig_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_02_SAT_MIN,
		cl_gts_gui.valinp_color_trace_02_sat_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_02_SAT_MAX,
		cl_gts_gui.valinp_color_trace_02_sat_max->value() );
	if (i_ret < 0) { return NG; }

	/***Fl::get_color(
		Fl_Color(FL_FREE_COLOR + 1),
		uchar_red, uchar_gre, uchar_blu
	);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_02,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, "%-24s %d %d %d\n", STR_COLOR_TRACE_02_TGT,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*- 03 ----*/

	i_ret = fprintf(fp, "%-24s %s\n", STR_COLOR_TRACE_03_CHK,
			cl_gts_gui.chkbtn_color_trace_03_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_03_HUE_MIN,
		cl_gts_gui.valinp_color_trace_03_hue_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_03_HUE_MAX,
		cl_gts_gui.valinp_color_trace_03_hue_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_03_LIG_MIN,
		cl_gts_gui.valinp_color_trace_03_lig_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_03_LIG_MAX,
		cl_gts_gui.valinp_color_trace_03_lig_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_03_SAT_MIN,
		cl_gts_gui.valinp_color_trace_03_sat_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_03_SAT_MAX,
		cl_gts_gui.valinp_color_trace_03_sat_max->value() );
	if (i_ret < 0) { return NG; }

	/***Fl::get_color(
		Fl_Color(FL_FREE_COLOR + 2),
		uchar_red, uchar_gre, uchar_blu
	);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_03,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, "%-24s %d %d %d\n", STR_COLOR_TRACE_03_TGT,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*- 04 ----*/

	i_ret = fprintf(fp, "%-24s %s\n", STR_COLOR_TRACE_04_CHK,
			cl_gts_gui.chkbtn_color_trace_04_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_04_HUE_MIN,
		cl_gts_gui.valinp_color_trace_04_hue_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_04_HUE_MAX,
		cl_gts_gui.valinp_color_trace_04_hue_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_04_LIG_MIN,
		cl_gts_gui.valinp_color_trace_04_lig_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_04_LIG_MAX,
		cl_gts_gui.valinp_color_trace_04_lig_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_04_SAT_MIN,
		cl_gts_gui.valinp_color_trace_04_sat_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_04_SAT_MAX,
		cl_gts_gui.valinp_color_trace_04_sat_max->value() );
	if (i_ret < 0) { return NG; }

	/***Fl::get_color(
		Fl_Color(FL_FREE_COLOR + 3),
		uchar_red, uchar_gre, uchar_blu
	);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_04,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, "%-24s %d %d %d\n", STR_COLOR_TRACE_04_TGT,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*- 05 ----*/

	i_ret = fprintf(fp, "%-24s %s\n", STR_COLOR_TRACE_05_CHK,
			cl_gts_gui.chkbtn_color_trace_05_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_05_HUE_MIN,
		cl_gts_gui.valinp_color_trace_05_hue_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_05_HUE_MAX,
		cl_gts_gui.valinp_color_trace_05_hue_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_05_LIG_MIN,
		cl_gts_gui.valinp_color_trace_05_lig_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_05_LIG_MAX,
		cl_gts_gui.valinp_color_trace_05_lig_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_05_SAT_MIN,
		cl_gts_gui.valinp_color_trace_05_sat_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_05_SAT_MAX,
		cl_gts_gui.valinp_color_trace_05_sat_max->value() );
	if (i_ret < 0) { return NG; }

	/***Fl::get_color(
		Fl_Color(FL_FREE_COLOR + 4),
		uchar_red, uchar_gre, uchar_blu
	);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_05,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, "%-24s %d %d %d\n", STR_COLOR_TRACE_05_TGT,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*- 06 ----*/

	i_ret = fprintf(fp, "%-24s %s\n", STR_COLOR_TRACE_06_CHK,
			cl_gts_gui.chkbtn_color_trace_06_chk->value()?
			this->_ccp_on:this->_ccp_off);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_06_HUE_MIN,
		cl_gts_gui.valinp_color_trace_06_hue_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_06_HUE_MAX,
		cl_gts_gui.valinp_color_trace_06_hue_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_06_LIG_MIN,
		cl_gts_gui.valinp_color_trace_06_lig_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_06_LIG_MAX,
		cl_gts_gui.valinp_color_trace_06_lig_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_06_SAT_MIN,
		cl_gts_gui.valinp_color_trace_06_sat_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, "%-24s %.16g\n", STR_COLOR_TRACE_06_SAT_MAX,
		cl_gts_gui.valinp_color_trace_06_sat_max->value() );
	if (i_ret < 0) { return NG; }

	/***Fl::get_color(
		Fl_Color(FL_FREE_COLOR + 5),
		uchar_red, uchar_gre, uchar_blu
	);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_06,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, "%-24s %d %d %d\n", STR_COLOR_TRACE_06_TGT,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	return OK;
}
