#include "memory_config.h"
#include "gts_gui.h"
#include "gts_master.h"

bool memory_config::load_trace_src_hsv_( std::vector< std::string >& words )
{
	//---------- 1/6 ----------

	if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_chk_)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_01_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_01_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_01_chk->value()) {
		 cl_gts_gui.group_color_trace_01grp->activate();
		   cl_gts_gui.group_thickness_01grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_01grp->deactivate();
		   cl_gts_gui.group_thickness_01grp->deactivate();
		}
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_src_hh_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_src_hh_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_hh_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_src_aa_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_01);
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_src_aa_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_aa_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_src_bb_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_src_bb_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_01_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_01_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_01);
	}
	else if ((4 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_tgt_rgb_)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_01 , std::stod(words.at(1))
			, std::stod(words.at(2)) , std::stod(words.at(3))
		);
		cl_gts_gui.button_color_trace_01_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_01_tgt_rgb->redraw();
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_01_tgt_color_)) {
		  cl_gts_gui.roubut_thickness_01_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 2/6 ----------

	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_chk_)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_02_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_02_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_02_chk->value()) {
		 cl_gts_gui.group_color_trace_02grp->activate();
		   cl_gts_gui.group_thickness_02grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_02grp->deactivate();
		   cl_gts_gui.group_thickness_02grp->deactivate();
		}
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_src_hh_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_src_hh_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_hh_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_src_aa_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_02);
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_src_aa_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_aa_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_src_bb_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_src_bb_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_02_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_02_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_02);
	}
	else if ((4 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_tgt_rgb_)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_02 , std::stod(words.at(1))
			, std::stod(words.at(2)) , std::stod(words.at(3))
		);
		cl_gts_gui.button_color_trace_02_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_02_tgt_rgb->redraw();
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_02_tgt_color_)) {
		  cl_gts_gui.roubut_thickness_02_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 3/6 ----------

	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_chk_)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_03_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_03_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_03_chk->value()) {
		 cl_gts_gui.group_color_trace_03grp->activate();
		   cl_gts_gui.group_thickness_03grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_03grp->deactivate();
		   cl_gts_gui.group_thickness_03grp->deactivate();
		}
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_src_hh_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_src_hh_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_hh_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_src_aa_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_03);
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_src_aa_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_aa_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_src_bb_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_src_bb_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_03_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_03_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_03);
	}
	else if ((4 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_tgt_rgb_)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_03 , std::stod(words.at(1))
			, std::stod(words.at(2)) , std::stod(words.at(3))
		);
		cl_gts_gui.button_color_trace_03_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_03_tgt_rgb->redraw();
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_03_tgt_color_)) {
		  cl_gts_gui.roubut_thickness_03_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 4/6 ----------

	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_chk_)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_04_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_04_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_04_chk->value()) {
		 cl_gts_gui.group_color_trace_04grp->activate();
		   cl_gts_gui.group_thickness_04grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_04grp->deactivate();
		   cl_gts_gui.group_thickness_04grp->deactivate();
		}
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_src_hh_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_src_hh_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_hh_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_src_aa_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_04);
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_src_aa_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_aa_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_src_bb_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_src_bb_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_04_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_04_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_04);
	}
	else if ((4 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_tgt_rgb_)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_04 , std::stod(words.at(1))
			, std::stod(words.at(2)) , std::stod(words.at(3))
		);
		cl_gts_gui.button_color_trace_04_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_04_tgt_rgb->redraw();
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_04_tgt_color_)) {
		  cl_gts_gui.roubut_thickness_04_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 5/6 ----------

	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_chk_)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_05_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_05_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_05_chk->value()) {
		 cl_gts_gui.group_color_trace_05grp->activate();
		   cl_gts_gui.group_thickness_05grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_05grp->deactivate();
		   cl_gts_gui.group_thickness_05grp->deactivate();
		}
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_src_hh_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_src_hh_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_hh_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_src_aa_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_05);
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_src_aa_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_aa_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_src_bb_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_src_bb_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_05_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_05_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_05);
	}
	else if ((4 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_tgt_rgb_)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_05 , std::stod(words.at(1))
			, std::stod(words.at(2)) , std::stod(words.at(3))
		);
		cl_gts_gui.button_color_trace_05_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_05_tgt_rgb->redraw();
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_05_tgt_color_)) {
		  cl_gts_gui.roubut_thickness_05_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- 6/6 ----------

	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_chk_)) {
		const int chk = (words.at(1) == this->str_on_) ?1 :0;
		cl_gts_gui.chkbtn_color_trace_06_chk->value( chk );
		  cl_gts_gui.chkbtn_thickness_06_chk->value( chk );

		if (
		cl_gts_gui.chkbtn_color_trace_06_chk->value()) {
		 cl_gts_gui.group_color_trace_06grp->activate();
		   cl_gts_gui.group_thickness_06grp->activate();
		} else {
		 cl_gts_gui.group_color_trace_06grp->deactivate();
		   cl_gts_gui.group_thickness_06grp->deactivate();
		}
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_src_hh_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_hh_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_src_hh_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_hh_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_hh_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_src_aa_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_aa_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_min)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_06);
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_src_aa_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_aa_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_aa_max)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_src_bb_min_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_bb_min->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_min)->value( val );
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_src_bb_max_)) {
		const double val = std::stod(words.at(1));
		cl_gts_gui.valinp_color_trace_06_src_bb_max->value( val );
((Fl_Valuator *)cl_gts_gui.scrbar_color_trace_06_src_bb_max)->value( val );
		cl_gts_master.cl_color_trace_thickness.set_scrbar_inpval(
			    E_COLOR_TRACE_HAB_06);
	}
	else if ((4 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_tgt_rgb_)) {
	cl_gts_master.cl_color_trace_enhancement.tgt_set_uchar_rgb_color(
			    E_COLOR_TRACE_HAB_06 , std::stod(words.at(1))
			, std::stod(words.at(2)) , std::stod(words.at(3))
		);
		cl_gts_gui.button_color_trace_06_tgt_rgb->redraw();
		  cl_gts_gui.button_thickness_06_tgt_rgb->redraw();
	}
	else if ((2 == words.size()) &&
	(words.at(0) == this->str_color_trace_06_tgt_color_)) {
		  cl_gts_gui.roubut_thickness_06_tgt_is_bl->value(
			(words.at(1) == this->str_color_black_) ?1 :0
		 );
	}

	//---------- not defined ----------

	else {
		return false;
	}

	return true;
}
