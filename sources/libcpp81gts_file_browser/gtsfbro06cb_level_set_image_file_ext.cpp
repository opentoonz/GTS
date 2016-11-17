#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_set_image_file_extension( void )
{
/*	switch (cl_gts_gui.choice_level_save_image_format->value()) {
	case 0:
		this->set_current_imagefile_extension(0);
		// TIFF
		break;
	case 1:
		// TGA
		this->set_current_imagefile_extension(1);
		break;
	}*/

	// 0:TIFF 1:TGAでなければならない
	this->set_current_imagefile_extension(
		cl_gts_gui.choice_level_save_image_format->value()
	);

	this->change_level_list();
}
