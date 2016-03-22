#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_file_or_level( void )
{
	this->change_level_list();

	if (0 == cl_gts_gui.choice_level_list_form->value()) {
		cl_gts_gui.button_level_shift_number->hide();
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->hide();
	} else {
		cl_gts_gui.button_level_shift_number->show();
		cl_gts_gui.ligbut_level_info_rgb_sub_sw->show();
	}
}
