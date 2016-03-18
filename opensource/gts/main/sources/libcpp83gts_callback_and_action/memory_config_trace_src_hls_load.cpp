
		/*------------------------------------------------*/
		/*-- 01 ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_CHK)) {
			cl_gts_gui.chkbtn_color_trace_01_chk->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
if (cl_gts_gui.chkbtn_color_trace_01_chk->value()) {
    cl_gts_gui.group_color_trace_01grp->activate();
} else {
    cl_gts_gui.group_color_trace_01grp->deactivate();
}
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_HUE_MIN )) {
			cl_gts_gui.valinp_color_trace_01_hue_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_hue_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_HUE_MAX )) {
			cl_gts_gui.valinp_color_trace_01_hue_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_hue_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_LIG_MIN )) {
			cl_gts_gui.valinp_color_trace_01_lig_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_lig_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_LIG_MAX )) {
			cl_gts_gui.valinp_color_trace_01_lig_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_lig_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_SAT_MIN )) {
			cl_gts_gui.valinp_color_trace_01_sat_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_sat_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_SAT_MAX )) {
			cl_gts_gui.valinp_color_trace_01_sat_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_sat_max)->value(
				atof(ca_scan2));
		}
		else if ((4 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_01_TGT )) {
			/***Fl::set_color(
				Fl_Color(FL_FREE_COLOR + 0),
				(unsigned char)(atoi(ca_scan2)),
				(unsigned char)(atoi(ca_scan3)),
				(unsigned char)(atoi(ca_scan4))
			);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
				E_COLOR_TRACE_01,
				atoi(ca_scan2),
				atoi(ca_scan3),
				atoi(ca_scan4)
			);
			cl_gts_gui.button_color_trace_01_tgt->redraw();
		}

		/*-- 02 ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_CHK)) {
			cl_gts_gui.chkbtn_color_trace_02_chk->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
if (cl_gts_gui.chkbtn_color_trace_02_chk->value()) {
    cl_gts_gui.group_color_trace_02grp->activate();
} else {
    cl_gts_gui.group_color_trace_02grp->deactivate();
}
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_HUE_MIN )) {
			cl_gts_gui.valinp_color_trace_02_hue_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_hue_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_HUE_MAX )) {
			cl_gts_gui.valinp_color_trace_02_hue_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_hue_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_LIG_MIN )) {
			cl_gts_gui.valinp_color_trace_02_lig_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_lig_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_LIG_MAX )) {
			cl_gts_gui.valinp_color_trace_02_lig_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_lig_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_SAT_MIN )) {
			cl_gts_gui.valinp_color_trace_02_sat_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_sat_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_SAT_MAX )) {
			cl_gts_gui.valinp_color_trace_02_sat_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_sat_max)->value(
				atof(ca_scan2));
		}
		else if ((4 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_02_TGT )) {
			/***Fl::set_color(
				Fl_Color(FL_FREE_COLOR + 1),
				(unsigned char)(atoi(ca_scan2)),
				(unsigned char)(atoi(ca_scan3)),
				(unsigned char)(atoi(ca_scan4))
			);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
				E_COLOR_TRACE_02,
				atoi(ca_scan2),
				atoi(ca_scan3),
				atoi(ca_scan4)
			);
			cl_gts_gui.button_color_trace_02_tgt->redraw();
		}

		/*-- 03 ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_CHK)) {
			cl_gts_gui.chkbtn_color_trace_03_chk->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
if (cl_gts_gui.chkbtn_color_trace_03_chk->value()) {
    cl_gts_gui.group_color_trace_03grp->activate();
} else {
    cl_gts_gui.group_color_trace_03grp->deactivate();
}
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_HUE_MIN )) {
			cl_gts_gui.valinp_color_trace_03_hue_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_hue_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_HUE_MAX )) {
			cl_gts_gui.valinp_color_trace_03_hue_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_hue_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_LIG_MIN )) {
			cl_gts_gui.valinp_color_trace_03_lig_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_lig_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_LIG_MAX )) {
			cl_gts_gui.valinp_color_trace_03_lig_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_lig_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_SAT_MIN )) {
			cl_gts_gui.valinp_color_trace_03_sat_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_sat_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_SAT_MAX )) {
			cl_gts_gui.valinp_color_trace_03_sat_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_sat_max)->value(
				atof(ca_scan2));
		}
		else if ((4 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_03_TGT )) {
			/***Fl::set_color(
				Fl_Color(FL_FREE_COLOR + 2),
				(unsigned char)(atoi(ca_scan2)),
				(unsigned char)(atoi(ca_scan3)),
				(unsigned char)(atoi(ca_scan4))
			);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
				E_COLOR_TRACE_03,
				atoi(ca_scan2),
				atoi(ca_scan3),
				atoi(ca_scan4)
			);
			cl_gts_gui.button_color_trace_03_tgt->redraw();
		}

		/*-- 04 ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_CHK)) {
			cl_gts_gui.chkbtn_color_trace_04_chk->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
if (cl_gts_gui.chkbtn_color_trace_04_chk->value()) {
    cl_gts_gui.group_color_trace_04grp->activate();
} else {
    cl_gts_gui.group_color_trace_04grp->deactivate();
}
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_HUE_MIN )) {
			cl_gts_gui.valinp_color_trace_04_hue_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_hue_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_HUE_MAX )) {
			cl_gts_gui.valinp_color_trace_04_hue_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_hue_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_LIG_MIN )) {
			cl_gts_gui.valinp_color_trace_04_lig_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_lig_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_LIG_MAX )) {
			cl_gts_gui.valinp_color_trace_04_lig_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_lig_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_SAT_MIN )) {
			cl_gts_gui.valinp_color_trace_04_sat_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_sat_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_SAT_MAX )) {
			cl_gts_gui.valinp_color_trace_04_sat_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_sat_max)->value(
				atof(ca_scan2));
		}
		else if ((4 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_04_TGT )) {
			/***Fl::set_color(
				Fl_Color(FL_FREE_COLOR + 3),
				(unsigned char)(atoi(ca_scan2)),
				(unsigned char)(atoi(ca_scan3)),
				(unsigned char)(atoi(ca_scan4))
			);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
				E_COLOR_TRACE_04,
				atoi(ca_scan2),
				atoi(ca_scan3),
				atoi(ca_scan4)
			);
			cl_gts_gui.button_color_trace_04_tgt->redraw();
		}

		/*-- 05 ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_CHK)) {
			cl_gts_gui.chkbtn_color_trace_05_chk->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
if (cl_gts_gui.chkbtn_color_trace_05_chk->value()) {
    cl_gts_gui.group_color_trace_05grp->activate();
} else {
    cl_gts_gui.group_color_trace_05grp->deactivate();
}
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_HUE_MIN )) {
			cl_gts_gui.valinp_color_trace_05_hue_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_hue_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_HUE_MAX )) {
			cl_gts_gui.valinp_color_trace_05_hue_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_hue_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_LIG_MIN )) {
			cl_gts_gui.valinp_color_trace_05_lig_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_lig_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_LIG_MAX )) {
			cl_gts_gui.valinp_color_trace_05_lig_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_lig_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_SAT_MIN )) {
			cl_gts_gui.valinp_color_trace_05_sat_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_sat_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_SAT_MAX )) {
			cl_gts_gui.valinp_color_trace_05_sat_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_sat_max)->value(
				atof(ca_scan2));
		}
		else if ((4 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_05_TGT )) {
			/***Fl::set_color(
				Fl_Color(FL_FREE_COLOR + 4),
				(unsigned char)(atoi(ca_scan2)),
				(unsigned char)(atoi(ca_scan3)),
				(unsigned char)(atoi(ca_scan4))
			);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
				E_COLOR_TRACE_05,
				atoi(ca_scan2),
				atoi(ca_scan3),
				atoi(ca_scan4)
			);
			cl_gts_gui.button_color_trace_05_tgt->redraw();
		}

		/*-- 06 ---*/

		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_CHK)) {
			cl_gts_gui.chkbtn_color_trace_06_chk->value(
				this->_chk_ON_OFF( ca_scan2 )
			);
if (cl_gts_gui.chkbtn_color_trace_06_chk->value()) {
    cl_gts_gui.group_color_trace_06grp->activate();
} else {
    cl_gts_gui.group_color_trace_06grp->deactivate();
}
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_HUE_MIN )) {
			cl_gts_gui.valinp_color_trace_06_hue_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_hue_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_HUE_MAX )) {
			cl_gts_gui.valinp_color_trace_06_hue_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_hue_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_LIG_MIN )) {
			cl_gts_gui.valinp_color_trace_06_lig_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_lig_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_LIG_MAX )) {
			cl_gts_gui.valinp_color_trace_06_lig_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_lig_max)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_SAT_MIN )) {
			cl_gts_gui.valinp_color_trace_06_sat_min->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_sat_min)->value(
				atof(ca_scan2));
		}
		else if ((2 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_SAT_MAX )) {
			cl_gts_gui.valinp_color_trace_06_sat_max->value(
				atof(ca_scan2));
	((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_sat_max)->value(
				atof(ca_scan2));
		}
		else if ((4 == i_ret) &&
		!strcmp( ca_scan1,STR_COLOR_TRACE_06_TGT )) {
			/***Fl::set_color(
				Fl_Color(FL_FREE_COLOR + 5),
				(unsigned char)(atoi(ca_scan2)),
				(unsigned char)(atoi(ca_scan3)),
				(unsigned char)(atoi(ca_scan4))
			);***/
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
				E_COLOR_TRACE_06,
				atoi(ca_scan2),
				atoi(ca_scan3),
				atoi(ca_scan4)
			);
			cl_gts_gui.button_color_trace_06_tgt->redraw();
		}

