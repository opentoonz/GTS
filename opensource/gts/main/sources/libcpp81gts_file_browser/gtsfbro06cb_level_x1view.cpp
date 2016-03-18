#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_x1view_cancel( void )
{
	cl_gts_gui.ligbut_level_image_x1_sw->value(0);
	cl_gts_gui.window_x1view->hide();
}

void gtsfbro06cb_level::cb_x1view_wintgl( void )
{
	if (	cl_gts_gui.ligbut_level_image_x1_sw->value()) {
		cl_gts_gui.window_x1view->show();
	} else {
		cl_gts_gui.window_x1view->hide();
	}
}
