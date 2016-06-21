#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

int memory_config::_save_trace_src_hsv_by_fp( FILE *fp )
{
	const char *ccp_chk = "%-24s %s\n";
	const char *ccp_src = "%-24s %.16g\n";
	const char *ccp_tgt = "%-24s %d %d %d\n";
	const char *ccp_col = "%-24s \"%s\"\n";

	int	i_ret;
	unsigned char uchar_red, uchar_gre, uchar_blu;

	/* 01 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, this->str_color_trace_01_chk_,
		cl_gts_gui.chkbtn_color_trace_01_chk->value()?
			this->str_on_:this->str_off_);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_01_src_hh_min_,
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_01_src_hh_max_,
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_01_src_aa_min_,
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_01_src_aa_max_,
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_01_src_bb_min_,
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_01_src_bb_max_,
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_01,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, this->str_color_trace_01_tgt_rgb_,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_col, this->str_color_trace_01_tgt_color_,
		cl_gts_gui.choice_thickness_01_tgt_src_preset->text(
		 cl_gts_gui.choice_thickness_01_tgt_src_preset->value()
		)
	);
	if (i_ret < 0) { return NG; }

	/* 02 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, this->str_color_trace_02_chk_,
		cl_gts_gui.chkbtn_color_trace_02_chk->value()?
			this->str_on_:this->str_off_);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_02_src_hh_min_,
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_02_src_hh_max_,
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_02_src_aa_min_,
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_02_src_aa_max_,
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_02_src_bb_min_,
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_02_src_bb_max_,
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_02,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, this->str_color_trace_02_tgt_rgb_,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_col, this->str_color_trace_02_tgt_color_,
		cl_gts_gui.choice_thickness_02_tgt_src_preset->text(
		 cl_gts_gui.choice_thickness_02_tgt_src_preset->value()
		)
	);
	if (i_ret < 0) { return NG; }

	/* 03 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, this->str_color_trace_03_chk_,
		cl_gts_gui.chkbtn_color_trace_03_chk->value()?
			this->str_on_:this->str_off_);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_03_src_hh_min_,
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_03_src_hh_max_,
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_03_src_aa_min_,
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_03_src_aa_max_,
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_03_src_bb_min_,
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_03_src_bb_max_,
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_03,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, this->str_color_trace_03_tgt_rgb_,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_col, this->str_color_trace_03_tgt_color_,
		cl_gts_gui.choice_thickness_03_tgt_src_preset->text(
		 cl_gts_gui.choice_thickness_03_tgt_src_preset->value()
		)
	);
	if (i_ret < 0) { return NG; }

	/* 04 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, this->str_color_trace_04_chk_,
		cl_gts_gui.chkbtn_color_trace_04_chk->value()?
			this->str_on_:this->str_off_);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_04_src_hh_min_,
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_04_src_hh_max_,
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_04_src_aa_min_,
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_04_src_aa_max_,
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_04_src_bb_min_,
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_04_src_bb_max_,
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_04,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, this->str_color_trace_04_tgt_rgb_,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_col, this->str_color_trace_04_tgt_color_,
		cl_gts_gui.choice_thickness_04_tgt_src_preset->text(
		 cl_gts_gui.choice_thickness_04_tgt_src_preset->value()
		)
	);
	if (i_ret < 0) { return NG; }

	/* 05 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, this->str_color_trace_05_chk_,
		cl_gts_gui.chkbtn_color_trace_05_chk->value()?
			this->str_on_:this->str_off_);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_05_src_hh_min_,
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_05_src_hh_max_,
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_05_src_aa_min_,
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_05_src_aa_max_,
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_05_src_bb_min_,
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_05_src_bb_max_,
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_05,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, this->str_color_trace_05_tgt_rgb_,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/* 06 ------------------------------------------------*/

	i_ret = fprintf(fp, ccp_chk, this->str_color_trace_06_chk_,
		cl_gts_gui.chkbtn_color_trace_06_chk->value()?
			this->str_on_:this->str_off_);
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_06_src_hh_min_,
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_06_src_hh_max_,
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_06_src_aa_min_,
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_06_src_aa_max_,
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_06_src_bb_min_,
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value() );
	if (i_ret < 0) { return NG; }

	i_ret = fprintf(fp, ccp_src, this->str_color_trace_06_src_bb_max_,
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value() );
	if (i_ret < 0) { return NG; }

	cl_gts_master.cl_color_trace_enhancement.tgt_get_uchar_rgb_color(
		E_COLOR_TRACE_HAB_06,
		&uchar_red, &uchar_gre, &uchar_blu );
	i_ret = fprintf(fp, ccp_tgt, this->str_color_trace_06_tgt_rgb_,
		uchar_red, uchar_gre, uchar_blu );
	if (i_ret < 0) { return NG; }

	/*------------------------------------------------*/
	return OK;
}
