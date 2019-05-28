#include "gts_str_language.h"

namespace gts_str {

namespace area_and_rot90 {
const char* offset_cm_x_big
	= "Too Big X!";
const char* offset_cm_x_small
	= "Too Small X!";
const char* offset_cm_y_big
	= "Too Big Y!";
const char* offset_cm_y_small
	= "Too Small Y!";
const char* size_cm_w_big
	= "Too Big W!";
const char* size_cm_w_small
	= "Too Small W!";
const char* size_cm_h_big
	= "Too Big H!";
const char* size_cm_h_small
	= "Too Small H!";
const char* dpi_out_of_range
	= "Must be %g ... %g DPI";
const char* crop_again
	= "Crop again!";
const char* need_only_1_filepath
	= "Error : Need Only 1 Filepath";
const char* bad_aspect_ratio_h
	= "Set H_Aspect_Ratio greater than zero!";
const char* bad_aspect_ratio_w
	= "Set W_Aspect_Ratio greater than zero!";
const char* click_h_or_w_button
	= "Click H or W button!";
} // area_and_rot90

namespace change_view {
const char* not_change
	= "Not change ,when Crop mode";
const char* no_image
	= "Need Image";
const char* no_rgb_image
	= "Need RGB Image";
const char* view_setup_error
	= "View setup Error";
} // change_view

namespace config {
const char* open
	= "Open Config";
const char* open_only_area_and_rot90
	= "Open Config only Area and Rot90";
const char* open_only_pixel_type_and_bright
	= "Open Config only Pixel Type and Bright";
const char* open_only_trace_params
	= "Open Config only Trace Params";
const char* save_as
	= "Save Config As";
const char* loading_config_error
	= "Error : at loading area_and_rot90 in config";
const char* need_ext_txt
	= "Error : Need Extension .txt";
} // config

namespace image {
const char* open
	= "Open Image";
const char* save_as
	= "Save Image As";
const char* save_as_can_not_when_crop
	= "Finish Cropping, Please Scan.";
const char* no_image
	= "Please Any Scan or Open.";
const char* need_extension
	= "Need Extension.";
const char* effects_error
	= "Effects Error";
const char* save_error
	= "Save \"%s\" Error";
} // image

namespace number {
const char* need_to_set_number
	= "Click [Set Number]!";
} // number

namespace scan_and_save {
const char* select_folder
	= "Select and Set Saving Folder for Scan";
const char* not_scan_number
	= "Set Number for Scan";
const char* need_scan_save_name
	= "Need Scan Save Name!";
const char* select_number
	= "Select Number!";
const char* bad_number
	= "Bad Number in Start!";
const char* bad_scan_number
	= "Bad Scan Number";
const char* scan_error
	= "Can not Scan(NG)";
const char* rot_and_trace_and_enoise_error
	= "Can not Fx";
const char* redraw_error
	= "Can not Redraw";
const char* can_not_get_save_path
	= "Can not get save_file_path at current_number";
const char* can_not_save
	= "Can not Save file";
} // scan_and_save

namespace trace_batch {
const char* add_config
	= "Add Config File";
} // trace_batch

namespace trace_files {
const char* open
	= "Open Images";
const char* select_folder
	= "Select and Set Saving Folder for Trace";
} // trace_files

} // gts_str
