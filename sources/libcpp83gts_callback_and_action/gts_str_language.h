#ifndef gts_str_language_h
#define gts_str_language_h

namespace gts_str {

namespace area_and_rot90 {
extern const char* offset_cm_x_big;
extern const char* offset_cm_x_small;
extern const char* offset_cm_y_big;
extern const char* offset_cm_y_small;
extern const char* size_cm_w_big;
extern const char* size_cm_w_small;
extern const char* size_cm_h_big;
extern const char* size_cm_h_small;
extern const char* dpi_out_of_range;
extern const char* crop_again;
extern const char* bad_aspect_ratio_h;
extern const char* bad_aspect_ratio_w;
extern const char* click_h_or_w_button;
extern const char* not_inside_then_limit;
extern const char* not_inside_then_limit_cancel;
extern const char* not_inside_then_limit_size;
extern const char* not_inside_then_limit_dpi;
} // area_and_rot90

namespace change_view {
extern const char* not_change;
extern const char* no_image;
extern const char* no_rgb_image;
extern const char* view_setup_error;
} // change_view

namespace config {
extern const char* open;
extern const char* open_only_area_and_rot90;
extern const char* open_only_pixel_type_and_bright;
extern const char* open_only_trace_params;
extern const char* save_as;
extern const char* need_only_1_filepath;
extern const char* loading_config_error;
extern const char* need_ext_txt;
extern const char* use_save_config_as;
extern const char* ask_overwrite;
extern const char* ask_save;
} // config

namespace image {
extern const char* open;
extern const char* save_as;
extern const char* save_as_can_not_when_crop;
extern const char* no_image;
extern const char* need_extension;
extern const char* effects_error;
extern const char* save_error;
} // image

namespace number {
extern const char* need_to_set_number;
} // number

namespace scan_and_save {
extern const char* select_folder;
extern const char* not_scan_number;
extern const char* need_scan_save_name;
extern const char* select_number;
extern const char* bad_number;
extern const char* bad_scan_number;
extern const char* scan_error;
extern const char* rot_and_trace_and_enoise_error;
extern const char* redraw_error;
extern const char* can_not_get_save_path;
extern const char* can_not_save;
} // scan_and_save

namespace trace_batch {
extern const char* add_config;
extern const char* too_many_selected;
} // trace_batch

namespace trace_files {
extern const char* open_images;
extern const char* select_folder;
extern const char* not_trace_number;
extern const char* need_trace_open_name;
extern const char* need_trace_save_name;
extern const char* check_open_folder_and_filename;
extern const char* check_save_folder_and_filename;
extern const char* select_number;
extern const char* filename_without_head_or_number;
extern const char* empty_rename_filename;
extern const char* number_is_out_of_range;
extern const char* no_head_in_filepath;
extern const char* bad_extension_in_filepath;
extern const char* not_number_file;
extern const char* ask_do_trace;
extern const char* ask_do_not_trace;
extern const char* ask_and_erase_dot_noise;
extern const char* ask_rename;
extern const char* ask_renumber;
extern const char* input_new_level_name;
extern const char* input_new_start_number;
} // trace_files

namespace fl_gl_image_view {
extern const char* need_image_head_name;
extern const char* need_extension_of_image;
} // fl_gl_image_view

namespace quit {
extern const char* ask_quit;
} // quit

} // gts_str

#endif /* !gts_str_language_h */
