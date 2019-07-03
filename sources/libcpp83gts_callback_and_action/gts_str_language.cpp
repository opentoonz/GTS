#include "gts_str_language.h"

namespace gts_str {

namespace area_and_rot90 {
const char* offset_cm_x_big
	= "Too Big X";
const char* offset_cm_x_small
	= "Too Small X";
const char* offset_cm_y_big
	= "Too Big Y";
const char* offset_cm_y_small
	= "Too Small Y";
const char* size_cm_w_big
	= "Too Big W";
const char* size_cm_w_small
	= "Too Small W";
const char* size_cm_h_big
	= "Too Big H";
const char* size_cm_h_small
	= "Too Small H";
const char* dpi_out_of_range
	= "Must be %g ... %g DPI";
const char* crop_again
	= "Crop again";
const char* bad_aspect_ratio_h
	= "Set H_Aspect_Ratio greater than zero";
const char* bad_aspect_ratio_w
	= "Set W_Aspect_Ratio greater than zero";
const char* click_h_or_w_button
	= "Click H or W button";
const char* not_inside_then_limit
	= "Not inside , Limit...";
const char* not_inside_then_limit_cancel
	= "Cancel";
const char* not_inside_then_limit_size
	= "Size";
const char* not_inside_then_limit_dpi
	= "DPI";
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
const char* need_only_1_filepath
	= "Error : Need Only 1 Filepath";
const char* loading_config_error
	= "Error : at loading in config";
const char* need_ext_txt
	= "Error : Need Extension .txt";
const char* use_save_config_as
	= "Use \'Save Config As\'";
const char* ask_overwrite
	= "Overwrite \"%s\"?";
const char* ask_save
	= "Save \"%s\"?";
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
	= "Click [Set Number]";
} // number

namespace scan_and_save {
const char* select_folder
	= "Select and Set Saving Folder for Scan";
const char* not_scan_number
	= "Set Number for Scan";
const char* need_scan_save_name
	= "Need Scan Save Name";
const char* select_number
	= "Select Number";
const char* bad_number
	= "Bad Number in Start";
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
const char* too_many_selected
	= "Select only one(%d selected)";
} // trace_batch

namespace trace_files {
const char* open_images
	= "Open Images";
const char* select_folder
	= "Select and Set Saving Folder for Trace";
const char* not_trace_number
	= "Set Folder and File and [Set Number] for Trace";
const char* need_trace_open_name
	= "Need Trace Open Name";
const char* need_trace_save_name
	= "Need Trace Save Name";
const char* check_open_folder_and_filename
	= "Check Open Folder and File name";
const char* check_save_folder_and_filename
	= "Check Save Folder and File name";
const char* select_number
	= "Select Number";
const char* filename_without_head_or_number
	= "Not exist name or number in \'%s\'";
const char* empty_rename_filename
	= "Error:rename \"%s\" \"%s\"";
const char* number_is_out_of_range
	= "Error : Number need 0...9999 range\nFrom\n %s\nTo\n %s\nNumber List\n %s\n";
const char* no_head_in_filepath
	= "No Head in File";
const char* bad_extension_in_filepath
	= "Bad Extension\"%s\" in File";
const char* not_number_file
	= "No Number in File";
const char* ask_do_trace
	= "Trace";
const char* ask_do_not_trace
	= "Not Trace";
const char* ask_and_erase_dot_noise
	= " and Erase Dot Noise";
const char* ask_rename
	= "Rename\nFrom\n %s\nTo\n %s\nNumber List\n %s\nOK?";
const char* ask_renumber
	= "Renumber\nFrom\n %s\nTo\n %s\nNumber List\n %s\nOK?";
const char* input_new_level_name
	= "Enter New Level Name";
const char* input_new_start_number
	= "Enter New Start Number";
} // trace_files

namespace fl_gl_image_view {
const char* need_image_head_name
	= "Error : Need Head name";
const char* need_extension_of_image
	= "Error : Need Extension .tga/.tif/.txt";
} // fl_gl_image_view

namespace quit {
const char* ask_quit
	= "Are you sure you want to quit?";
} // quit

} // gts_str
