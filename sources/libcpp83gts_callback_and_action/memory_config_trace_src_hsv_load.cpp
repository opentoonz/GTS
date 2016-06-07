#include <string.h>	/* strcmp() */
#include <stdlib.h>
#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

E_MEMORY_CONFIG_LOAD_RET memory_config::_load_trace_src_hsv_by_fp( int i_num, char *cp1, char *cp2, char *cp3, char *cp4 )
{

	/* 01 ------------------------------------------------*/

	if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_chk_)) {
		cl_gts_gui.chkbtn_color_trace_01_chk->value(
			this->_chk_ON_OFF( cp2 )
		);
		if (cl_gts_gui.chkbtn_color_trace_01_chk->value()) {
			cl_gts_gui.group_color_trace_01grp->activate();
		} else {
			cl_gts_gui.group_color_trace_01grp->deactivate();
		}
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_src_hh_min_ )) {
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_src_hh_max_ )) {
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_src_aa_min_ )) {
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_src_aa_max_ )) {
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_src_bb_min_ )) {
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_src_bb_max_ )) {
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_max)->value(
			atof(cp2));
	}
	else if ((4 == i_num) &&
	!strcmp( cp1,this->str_color_trace_01_tgt_rgb_ )) {
cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			E_COLOR_TRACE_HAB_01,
			atoi(cp2),
			atoi(cp3),
			atoi(cp4)
		);
		cl_gts_gui.button_color_trace_01_tgt_rgb->redraw();
	}

	/* 02 ------------------------------------------------*/

	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_chk_)) {
		cl_gts_gui.chkbtn_color_trace_02_chk->value(
			this->_chk_ON_OFF( cp2 )
		);
		if (cl_gts_gui.chkbtn_color_trace_02_chk->value()) {
			cl_gts_gui.group_color_trace_02grp->activate();
		} else {
			cl_gts_gui.group_color_trace_02grp->deactivate();
		}
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_src_hh_min_ )) {
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_src_hh_max_ )) {
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_src_aa_min_ )) {
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_src_aa_max_ )) {
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_src_bb_min_ )) {
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_src_bb_max_ )) {
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_max)->value(
			atof(cp2));
	}
	else if ((4 == i_num) &&
	!strcmp( cp1,this->str_color_trace_02_tgt_rgb_ )) {
cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			E_COLOR_TRACE_HAB_02,
			atoi(cp2),
			atoi(cp3),
			atoi(cp4)
		);
		cl_gts_gui.button_color_trace_02_tgt_rgb->redraw();
	}

	/* 03 ------------------------------------------------*/

	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_chk_)) {
		cl_gts_gui.chkbtn_color_trace_03_chk->value(
			this->_chk_ON_OFF( cp2 )
		);
		if (cl_gts_gui.chkbtn_color_trace_03_chk->value()) {
			cl_gts_gui.group_color_trace_03grp->activate();
		} else {
			cl_gts_gui.group_color_trace_03grp->deactivate();
		}
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_src_hh_min_ )) {
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_src_hh_max_ )) {
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_src_aa_min_ )) {
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_src_aa_max_ )) {
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_src_bb_min_ )) {
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_src_bb_max_ )) {
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_max)->value(
			atof(cp2));
	}
	else if ((4 == i_num) &&
	!strcmp( cp1,this->str_color_trace_03_tgt_rgb_ )) {
cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			E_COLOR_TRACE_HAB_03,
			atoi(cp2),
			atoi(cp3),
			atoi(cp4)
		);
		cl_gts_gui.button_color_trace_03_tgt_rgb->redraw();
	}

	/* 04 ------------------------------------------------*/

	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_chk_)) {
		cl_gts_gui.chkbtn_color_trace_04_chk->value(
			this->_chk_ON_OFF( cp2 )
		);
		if (cl_gts_gui.chkbtn_color_trace_04_chk->value()) {
			cl_gts_gui.group_color_trace_04grp->activate();
		} else {
			cl_gts_gui.group_color_trace_04grp->deactivate();
		}
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_src_hh_min_ )) {
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_src_hh_max_ )) {
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_src_aa_min_ )) {
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_src_aa_max_ )) {
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_src_bb_min_ )) {
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_src_bb_max_ )) {
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_max)->value(
			atof(cp2));
	}
	else if ((4 == i_num) &&
	!strcmp( cp1,this->str_color_trace_04_tgt_rgb_ )) {
cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			E_COLOR_TRACE_HAB_04,
			atoi(cp2),
			atoi(cp3),
			atoi(cp4)
		);
		cl_gts_gui.button_color_trace_04_tgt_rgb->redraw();
	}

	/* 05 ------------------------------------------------*/

	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_chk_)) {
		cl_gts_gui.chkbtn_color_trace_05_chk->value(
			this->_chk_ON_OFF( cp2 )
		);
		if (cl_gts_gui.chkbtn_color_trace_05_chk->value()) {
			cl_gts_gui.group_color_trace_05grp->activate();
		} else {
			cl_gts_gui.group_color_trace_05grp->deactivate();
		}
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_src_hh_min_ )) {
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_src_hh_max_ )) {
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_src_aa_min_ )) {
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_src_aa_max_ )) {
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_src_bb_min_ )) {
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_src_bb_max_ )) {
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_max)->value(
			atof(cp2));
	}
	else if ((4 == i_num) &&
	!strcmp( cp1,this->str_color_trace_05_tgt_rgb_ )) {
cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			E_COLOR_TRACE_HAB_05,
			atoi(cp2),
			atoi(cp3),
			atoi(cp4)
		);
		cl_gts_gui.button_color_trace_05_tgt_rgb->redraw();
	}

	/* 06 ------------------------------------------------*/

	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_chk_)) {
		cl_gts_gui.chkbtn_color_trace_06_chk->value(
			this->_chk_ON_OFF( cp2 )
		);
		if (cl_gts_gui.chkbtn_color_trace_06_chk->value()) {
			cl_gts_gui.group_color_trace_06grp->activate();
		} else {
			cl_gts_gui.group_color_trace_06grp->deactivate();
		}
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_src_hh_min_ )) {
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_src_hh_max_ )) {
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_src_aa_min_ )) {
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_src_aa_max_ )) {
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_max)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_src_bb_min_ )) {
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_min)->value(
			atof(cp2));
	}
	else if ((2 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_src_bb_max_ )) {
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value(
			atof(cp2));
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_max)->value(
			atof(cp2));
	}
	else if ((4 == i_num) &&
	!strcmp( cp1,this->str_color_trace_06_tgt_rgb_ )) {
cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			E_COLOR_TRACE_HAB_06,
			atoi(cp2),
			atoi(cp3),
			atoi(cp4)
		);
		cl_gts_gui.button_color_trace_06_tgt_rgb->redraw();
	} else {
		return E_MEMORY_CONFIG_LOAD_NOTHING;
	}

	return E_MEMORY_CONFIG_LOAD_MATCH;
}
