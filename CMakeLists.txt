cmake_minimum_required(VERSION 3.10)

project(GTS VERSION 2.5.1 LANGUAGES C CXX)

# Default to a Release build when none is specified (single-config generators).
get_property(_is_multi GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT _is_multi AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type (Release or Debug)" FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Release Debug)
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(GNUInstallDirs)
include(CheckSymbolExists)
include(CheckCXXSourceCompiles)
find_package(PkgConfig REQUIRED)

# ---------------------------------------------------------------------------
# Platform
# ---------------------------------------------------------------------------
set(GTS_PLATFORM_DEFINES "")
if(WIN32)
  list(APPEND GTS_PLATFORM_DEFINES _WIN32)
elseif(APPLE)
  list(APPEND GTS_PLATFORM_DEFINES _MACOS)
endif()

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
pkg_check_modules(TIFF REQUIRED IMPORTED_TARGET libtiff-4)
pkg_check_modules(GLEW REQUIRED IMPORTED_TARGET glew)
find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)

# FLTK: use fltk-config, as the autoconf build does.
find_program(FLTK_CONFIG fltk-config)
if(NOT FLTK_CONFIG)
  message(FATAL_ERROR "fltk-config is required")
endif()
execute_process(COMMAND ${FLTK_CONFIG} --cxxflags
                OUTPUT_VARIABLE FLTK_CXXFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${FLTK_CONFIG} --use-gl --ldflags
                OUTPUT_VARIABLE FLTK_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
separate_arguments(FLTK_CXXFLAGS UNIX_COMMAND "${FLTK_CXXFLAGS}")
separate_arguments(FLTK_LDFLAGS UNIX_COMMAND "${FLTK_LDFLAGS}")

if(NOT WIN32)
  pkg_check_modules(SANE REQUIRED IMPORTED_TARGET sane-backends)
endif()

if(APPLE)
  find_package(Boost REQUIRED COMPONENTS filesystem system)
endif()

# ---------------------------------------------------------------------------
# config.h (generated into the build tree; replaces autoconf's config.h)
# ---------------------------------------------------------------------------
check_symbol_exists(strerror_r "string.h" HAVE_STRERROR_R)
check_symbol_exists(secure_getenv "stdlib.h" HAVE_SECURE_GETENV)
check_symbol_exists(__secure_getenv "stdlib.h" HAVE___SECURE_GETENV)

# GNU strerror_r returns char*, XSI returns int.
if(HAVE_STRERROR_R)
  check_cxx_source_compiles("
    #include <string.h>
    int main() { char b[8]; char* p = strerror_r(0, b, sizeof b); return p != 0; }"
    STRERROR_R_CHAR_P)
endif()

check_cxx_source_compiles("#include <GL/glu.h>\nint main() { return 0; }" HAVE_GL_GLU_H)
if(NOT HAVE_GL_GLU_H)
  check_cxx_source_compiles("#include <OpenGL/glu.h>\nint main() { return 0; }" HAVE_OPENGL_GLU_H)
endif()

string(TIMESTAMP CONFIGURATION_DATE "%Y-%m-%d")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/config.h.cmake.in
               ${CMAKE_CURRENT_BINARY_DIR}/config.h)

# ---------------------------------------------------------------------------
# libgts (static, internal)
# ---------------------------------------------------------------------------
set(GTS_SOURCES
    sources/lib_util/calc_hsv_rgb.cpp
    sources/lib_util/calc_hsv_xyz.cpp
    sources/lib_util/calc_rad_deg.cpp
    sources/lib_util/cppl_file_system.cpp
    sources/lib_util/cppl_stop_watch.cpp
    sources/lib_util/opengl_camera_eye.cpp
    sources/lib_util/opengl_vertex_buffer_object.cpp
    sources/lib_util/osapi_exist.cpp
    sources/lib_util/osapi_getenv.cpp
    sources/lib_util/osapi_gethostname.cpp
    sources/lib_util/osapi_getusername.cpp
    sources/lib_util/osapi_log_with_msg_and_id.cpp
    sources/lib_util/osapi_mbs_wcs.cpp
    sources/lib_util/osapi_mkdir.cpp
    sources/lib_util/osapi_str_from_errid.cpp
    sources/lib_image_rw/image_common.cpp
    sources/lib_image_rw/image_tif_common.cpp
    sources/lib_image_rw/image_tif_read_handle.cpp
    sources/lib_image_rw/image_tif_read_handle_info.cpp
    sources/lib_image_rw/image_tif_reader.cpp
    sources/lib_image_rw/image_tif_write_handle.cpp
    sources/lib_image_rw/image_tif_writer.cpp
    sources/libc12pri/pri_cv.c
    sources/libc12pri/pri_msg_and_err.c
    sources/libc14image_rw_base/bread.c
    sources/libc14image_rw_base/bwrite.c
    sources/libc14image_rw_base/cpu_byte_order_is_little_endian.c
    sources/libc18image_rw_tga/tga_image_read.c
    sources/libc18image_rw_tga/tga_image_read_header.c
    sources/libc18image_rw_tga/tga_image_write.c
    sources/libc18image_rw_tga/tga_init_file_header.c
    sources/libc18image_rw_tga/tga_read_close.c
    sources/libc18image_rw_tga/tga_read_init.c
    sources/libc18image_rw_tga/tga_read_open.c
    sources/libc18image_rw_tga/tga_read_scanline.c
    sources/libc18image_rw_tga/tga_stat.c
    sources/libc18image_rw_tga/tga_write_close.c
    sources/libc18image_rw_tga/tga_write_init.c
    sources/libc18image_rw_tga/tga_write_open.c
    sources/libc18image_rw_tga/tga_write_scanline.c
    sources/libc18image_rw_tga/tga_write_setup_header.c
    sources/libcpp31calcu_precision/calcu_precision.cpp
    sources/libcpp51iip_canvas/iip_canvas.cpp
    sources/libcpp51iip_canvas/iip_channel_info.cpp
    sources/libcpp52iip_rw/iip_read_file.cpp
    sources/libcpp52iip_rw/iip_read_header.cpp
    sources/libcpp52iip_rw/iip_read_set_tif_param.cpp
    sources/libcpp52iip_rw/iip_write_file.cpp
    sources/libcpp52iip_rw/iip_write_set_file_attrbute_from_read.cpp
    sources/libcpp52iip_rw/iip_write_set_tif_param.cpp
    sources/libcpp52iip_rw/name_strings.cpp
    sources/libcpp53iip_precision/iip_precision.cpp
    sources/libcpp53iip_precision/iip_precision_bw_to_uchargray.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_channel.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_draw.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_edit_crop.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_method.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_position.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_scroll.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_select.cpp
    sources/libcpp56iip_opengl/iip_opengl_l1edit_zoom.cpp
    sources/libcpp56iip_opengl/iip_opengl_l2data_set_imagedata.cpp
    sources/libcpp56iip_opengl/iip_opengl_l3event_draw.cpp
    sources/libcpp56iip_opengl/iip_opengl_l3event_init_viewparam.cpp
    sources/libcpp56iip_opengl/iip_opengl_l3event_method.cpp
    sources/libcpp56iip_opengl/iip_opengl_l3event_select_area.cpp
    sources/libcpp56iip_opengl/iip_opengl_l3event_set_imagedata.cpp
    sources/libcpp56iip_opengl/iip_opengl_l3event_wview.cpp
    sources/libcpp64iip_rot90/iip_rot90.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_crop_and_downsample.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_calcu_bresenham.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_exec.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_mem.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_set_canvas.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_uchar.cpp
    sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_ushrt.cpp
    sources/libcpp71iip_trace_by_hsv/calc_trace_by_hsv.cpp
    sources/libcpp71iip_trace_by_hsv/iip_trace_by_hsv.cpp
    sources/libcpp72iip_erase_dot_noise/calcu_erase_dot_noise.cpp
    sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_exec.cpp
    sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_uchar.cpp
    sources/libcpp83gts_callback_and_action/gts_file_path.cpp
    sources/libcpp83gts_callback_and_action/gts_gui.cpp
    sources/libcpp83gts_callback_and_action/gts_master.cpp
    sources/libcpp83gts_callback_and_action/cb_area_and_rot90.cpp
    sources/libcpp83gts_callback_and_action/cb_change_view.cpp
    sources/libcpp83gts_callback_and_action/cb_color_trace_view_area.cpp
    sources/libcpp83gts_callback_and_action/cb_config.cpp
    sources/libcpp83gts_callback_and_action/cb_image.cpp
    sources/libcpp83gts_callback_and_action/cb_number.cpp
    sources/libcpp83gts_callback_and_action/cb_pixel_type_and_bright.cpp
    sources/libcpp83gts_callback_and_action/cb_quit.cpp
    sources/libcpp83gts_callback_and_action/cb_read_and_trace_and_preview.cpp
    sources/libcpp83gts_callback_and_action/cb_scan_and_preview.cpp
    sources/libcpp83gts_callback_and_action/cb_scan_and_save.cpp
    sources/libcpp83gts_callback_and_action/cb_set_number_format.cpp
    sources/libcpp83gts_callback_and_action/cb_trace_batch.cpp
    sources/libcpp83gts_callback_and_action/cb_trace_files.cpp
    sources/libcpp83gts_callback_and_action/cb_trace_params.cpp
    sources/libcpp83gts_callback_and_action/dogascan_event.cpp
    sources/libcpp83gts_callback_and_action/dogascan_print_window_headline.cpp
    sources/libcpp83gts_callback_and_action/dogascan_scrollbar.cpp
    sources/libcpp83gts_callback_and_action/fl_gl_cyclic_color_wheel.cpp
    sources/libcpp83gts_callback_and_action/fl_gl_hsv_view.cpp
    sources/libcpp83gts_callback_and_action/fl_gl_image_view.cpp
    sources/libcpp83gts_callback_and_action/fltk_event.cpp
    sources/libcpp83gts_callback_and_action/igs_lex_white_space_and_double_quote.cpp
    sources/libcpp83gts_callback_and_action/ids_path_extensions.cpp
    sources/libcpp83gts_callback_and_action/ids_path_fltk_native_browse.cpp
    sources/libcpp83gts_callback_and_action/ids_path_level_from_files.cpp
    sources/libcpp83gts_callback_and_action/iipg_color_trace.cpp
    sources/libcpp83gts_callback_and_action/iipg_rot90.cpp
    sources/libcpp83gts_callback_and_action/iipg_save.cpp
    sources/libcpp83gts_callback_and_action/iipg_scan.cpp
    sources/libcpp83gts_callback_and_action/iipg_view.cpp
    sources/libcpp83gts_callback_and_action/memory_config_load.cpp
    sources/libcpp83gts_callback_and_action/memory_config_save.cpp
    sources/libcpp83gts_callback_and_action/memory_desktop_load.cpp
    sources/libcpp83gts_callback_and_action/memory_desktop_save.cpp
)

if(WIN32)
  list(APPEND GTS_SOURCES
    sources/libcpp55iip_scan/tw_win_l1_dsm_entry.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_get_cc.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_init_tw_id.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_pri_cc.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_pri_error.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_state1to2.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_state2to1.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_state2to3.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_state3to2.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_state3to4.cpp
    sources/libcpp55iip_scan/tw_win_l1_dsm_state4to3.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_calc.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_ctnr.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_ctnr_onev.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_ctnr_range.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_param_onev.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_ctnr_enum.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_ctnr_onev.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_ctnr_range.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_param_enum.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_param_onev.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_param_range.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_set_ctnr.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_set_ctnr_onev.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_cap_set_param_onev.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_get.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_get_reso.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_pri.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_pri_all.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_get.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_pri.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_pri_all.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_set.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_set_area.cpp
    sources/libcpp55iip_scan/tw_win_l2_dss_setupmemxfer_pri.cpp
    sources/libcpp55iip_scan/tw_win_l3_dsi_state4to5.cpp
    sources/libcpp55iip_scan/tw_win_l3_dsi_state5to4.cpp
    sources/libcpp55iip_scan/tw_win_l3_dsi_state5to6to5event.cpp
    sources/libcpp55iip_scan/tw_win_l3_dsi_state6to7to6native.cpp
    sources/libcpp55iip_scan/tw_win_l3_dsi_state6to7to6select.cpp
    sources/libcpp55iip_scan/tw_win_l4_scan_orc.cpp
    sources/libcpp55iip_scan/tw_win_l4_scan_pri_dib_header.cpp
    sources/libcpp55iip_scan/tw_win_l4_scan_trans_image.cpp
  )
else()
  list(APPEND GTS_SOURCES
    sources/libcpp55iip_scan/sane_scan.cpp
  )
endif()

add_library(gts_lib STATIC ${GTS_SOURCES})
set_target_properties(gts_lib PROPERTIES OUTPUT_NAME gts)

target_include_directories(gts_lib PUBLIC
  ${CMAKE_CURRENT_BINARY_DIR}    # config.h
  sources/lib_util
  sources/lib_image_rw
  sources/libc12pri
  sources/libc14image_rw_base
  sources/libc18image_rw_tga
  sources/libcpp31calcu_precision
  sources/libcpp51iip_canvas
  sources/libcpp52iip_rw
  sources/libcpp53iip_precision
  sources/libcpp55iip_scan
  sources/libcpp56iip_opengl
  sources/libcpp64iip_rot90
  sources/libcpp69iip_scale_by_subpixel
  sources/libcpp71iip_trace_by_hsv
  sources/libcpp72iip_erase_dot_noise
  sources/libcpp83gts_callback_and_action
)

target_compile_definitions(gts_lib PUBLIC
  HAVE_CONFIG_H
  PKGDATADIR="${CMAKE_INSTALL_FULL_DATADIR}/GTS"
  ${GTS_PLATFORM_DEFINES}
)
target_compile_options(gts_lib PUBLIC ${FLTK_CXXFLAGS})
target_link_libraries(gts_lib PUBLIC
  PkgConfig::TIFF
  PkgConfig::GLEW
  OpenGL::GLU
  OpenGL::GL
  Threads::Threads
  ${FLTK_LDFLAGS}
)

if(WIN32)
  target_include_directories(gts_lib PUBLIC thirdparty/twain/twain-2.3)
else()
  target_link_libraries(gts_lib PUBLIC PkgConfig::SANE)
endif()

if(APPLE)
  target_link_libraries(gts_lib PUBLIC Boost::filesystem Boost::system)
endif()

# ---------------------------------------------------------------------------
# gts executable
# ---------------------------------------------------------------------------
add_executable(gts sources/main/main.cpp)
target_link_libraries(gts PRIVATE gts_lib)

install(TARGETS gts RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES sources/main/gts_initial_configuration.txt
        DESTINATION ${CMAKE_INSTALL_DATADIR}/GTS)
