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
extern const char* need_only_1_filepath;
extern const char* bad_aspect_ratio_h;
extern const char* bad_aspect_ratio_w;
extern const char* click_h_or_w_button;
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
extern const char* loading_config_error;
extern const char* need_ext_txt;
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
} // trace_batch

namespace trace_files {
extern const char* open;
extern const char* select_folder;
} // trace_files

} // gts_str

#endif /* !gts_str_language_h */
