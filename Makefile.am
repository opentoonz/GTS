ACLOCAL_AMFLAGS = -I m4
CPPFLAGS += -DPKGDATADIR='"$(pkgdatadir)"'

pkgdata_DATA = \
			   sources/main/_gts-scan_area.txt \
			   sources/main/gts_install_setup.txt

noinst_LTLIBRARIES = libgts.la

libgts_la_CPPFLAGS = \
				   -Isources/libc11portable \
				   -Isources/libc12pri \
				   -Isources/libc14image_rw_base \
				   -Isources/libc16image_rw_tif \
				   -Isources/libc18image_rw_tga \
				   -Isources/libcpp31calcu_precision \
				   -Isources/libcpp38calcu_rgb_to_hsv \
				   -Isources/libcpp51iip_canvas \
				   -Isources/libcpp52iip_rw \
				   -Isources/libcpp53iip_precision \
				   -Isources/libcpp55iip_scan \
				   -Isources/libcpp56iip_opengl \
				   -Isources/libcpp64iip_rot90 \
				   -Isources/libcpp69iip_scale_by_subpixel \
				   -Isources/libcpp71iip_color_trace_hab \
				   -Isources/libcpp72iip_erase_dot_noise \
				   -Isources/libcpp82gts_hsv_histogram \
				   -Isources/libcpp83gts_callback_and_action \
				   $(TIFF_CFLAGS) \
				   $(FLTK_CPPFLAGS) \
				   -std=c++11

libgts_la_SOURCES = \
					sources/libc11portable/ptbl_cpu_is_little_endian.c \
					sources/libc11portable/ptbl_dir_or_file_is_exist.c \
					sources/libc11portable/ptbl_get_cp_hostname.c \
					sources/libc11portable/ptbl_get_cp_loginname.c \
					sources/libc11portable/ptbl_get_cp_username.c \
					sources/libc11portable/ptbl_get_cp_userrealname.c \
					sources/libc11portable/ptbl_mkdir.c \
					sources/libc11portable/ptbl_utils_about_path.c \
					sources/libc12pri/pri_cv.c \
					sources/libc12pri/pri_msg_and_err.c \
					sources/libc14image_rw_base/bread.c \
					sources/libc14image_rw_base/bwrite.c \
					sources/libc16image_rw_tif/tif_bw_invert.c \
					sources/libc16image_rw_tif/tif_bw_read.c \
					sources/libc16image_rw_tif/tif_bw_reverse.c \
					sources/libc16image_rw_tif/tif_bw_write.c \
					sources/libc16image_rw_tif/tif_image_read.c \
					sources/libc16image_rw_tif/tif_image_read_header.c \
					sources/libc16image_rw_tif/tif_image_read_y_manual.c \
					sources/libc16image_rw_tif/tif_image_write.c \
					sources/libc16image_rw_tif/tif_init_rw_header.c \
					sources/libc16image_rw_tif/tif_read_close.c \
					sources/libc16image_rw_tif/tif_read_get_reverse_sw.c \
					sources/libc16image_rw_tif/tif_read_open.c \
					sources/libc16image_rw_tif/tif_read_sca_all.c \
					sources/libc16image_rw_tif/tif_read_sca_y.c \
					sources/libc16image_rw_tif/tif_read_scanline.c \
					sources/libc16image_rw_tif/tif_read_til_all.c \
					sources/libc16image_rw_tif/tif_read_tile.c \
					sources/libc16image_rw_tif/tif_stat.c \
					sources/libc16image_rw_tif/tif_write_close.c \
					sources/libc16image_rw_tif/tif_write_get_param.c \
					sources/libc16image_rw_tif/tif_write_header.c \
					sources/libc16image_rw_tif/tif_write_open.c \
					sources/libc16image_rw_tif/tif_write_scanline.c \
					sources/libc18image_rw_tga/tga_image_read.c \
					sources/libc18image_rw_tga/tga_image_read_header.c \
					sources/libc18image_rw_tga/tga_image_write.c \
					sources/libc18image_rw_tga/tga_init_file_header.c \
					sources/libc18image_rw_tga/tga_read_close.c \
					sources/libc18image_rw_tga/tga_read_init.c \
					sources/libc18image_rw_tga/tga_read_open.c \
					sources/libc18image_rw_tga/tga_read_scanline.c \
					sources/libc18image_rw_tga/tga_stat.c \
					sources/libc18image_rw_tga/tga_write_close.c \
					sources/libc18image_rw_tga/tga_write_init.c \
					sources/libc18image_rw_tga/tga_write_open.c \
					sources/libc18image_rw_tga/tga_write_scanline.c \
					sources/libc18image_rw_tga/tga_write_setup_header.c \
					sources/libcpp31calcu_precision/calcu_precision.cpp \
					sources/libcpp38calcu_rgb_to_hsv/from_hsv.cpp \
					sources/libcpp38calcu_rgb_to_hsv/to_hsv.cpp \
					sources/libcpp51iip_canvas/iip_canvas.cpp \
					sources/libcpp51iip_canvas/iip_channel_info.cpp \
					sources/libcpp52iip_rw/check_save.cpp \
					sources/libcpp52iip_rw/iip_read_file.cpp \
					sources/libcpp52iip_rw/iip_read_header.cpp \
					sources/libcpp52iip_rw/iip_read_set_tif_param.cpp \
					sources/libcpp52iip_rw/iip_write_file.cpp \
					sources/libcpp52iip_rw/iip_write_set_file_attrbute_from_read.cpp \
					sources/libcpp52iip_rw/iip_write_set_tif_param.cpp \
					sources/libcpp52iip_rw/name_strings.cpp \
					sources/libcpp53iip_precision/iip_precision.cpp \
					sources/libcpp53iip_precision/iip_precision_bw_to_uchargray.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_channel.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_draw.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_edit_crop.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_method.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_position.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_scroll.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_select.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l1edit_zoom.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l2data_set_imagedata.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l3event_draw.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l3event_init_viewparam.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l3event_method.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l3event_select_area.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l3event_set_imagedata.cpp \
					sources/libcpp56iip_opengl/iip_opengl_l3event_wview.cpp \
					sources/libcpp64iip_rot90/iip_rot90.cpp \
					sources/libcpp64iip_rot90/iip_rot90_bitbw.cpp \
					sources/libcpp64iip_rot90/iip_rot90_doubl.cpp \
					sources/libcpp64iip_rot90/iip_rot90_uchar.cpp \
					sources/libcpp64iip_rot90/iip_rot90_ulong.cpp \
					sources/libcpp64iip_rot90/iip_rot90_ushrt.cpp \
					sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_calcu_bresenham.cpp \
					sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_exec.cpp \
					sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_mem.cpp \
					sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_set_canvas.cpp \
					sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_uchar.cpp \
					sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_ushrt.cpp \
					sources/libcpp71iip_color_trace_hab/calcu_color_trace_hab.cpp \
					sources/libcpp71iip_color_trace_hab/calcu_histogram_hab.cpp \
					sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_doubl.cpp \
					sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_exec.cpp \
					sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_uchar.cpp \
					sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_ulong.cpp \
					sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_ushrt.cpp \
					sources/libcpp72iip_erase_dot_noise/calcu_erase_dot_noise.cpp \
					sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_exec.cpp \
					sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_uchar.cpp \
					sources/libcpp82gts_hsv_histogram/fltk_1000_range_cyclic.cpp \
					sources/libcpp82gts_hsv_histogram/fltk_1000_range_minmax.cpp \
					sources/libcpp82gts_hsv_histogram/fltk_1000x100_histogram.cpp \
					sources/libcpp82gts_hsv_histogram/fltk_1000x10_color_belt.cpp \
					sources/libcpp83gts_callback_and_action/gts_gui.cpp \
					sources/libcpp83gts_callback_and_action/gts_master.cpp \
					sources/libcpp83gts_callback_and_action/cb_change_view.cpp \
					sources/libcpp83gts_callback_and_action/cb_choice_pixel_type.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_edit_color.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_edit_hsv_minmax.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_enhancement_src.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_enhancement_tgt.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_src.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_thickness.cpp \
					sources/libcpp83gts_callback_and_action/cb_color_trace_view_area.cpp \
					sources/libcpp83gts_callback_and_action/cb_config.cpp \
					sources/libcpp83gts_callback_and_action/cb_file_number_list.cpp \
					sources/libcpp83gts_callback_and_action/cb_level.cpp \
					sources/libcpp83gts_callback_and_action/cb_quit.cpp \
					sources/libcpp83gts_callback_and_action/cb_read_and_save.cpp \
					sources/libcpp83gts_callback_and_action/cb_read_and_trace_and_preview.cpp \
					sources/libcpp83gts_callback_and_action/cb_rotate_per_90.cpp \
					sources/libcpp83gts_callback_and_action/cb_scan_and_preview.cpp \
					sources/libcpp83gts_callback_and_action/cb_scan_and_save.cpp \
					sources/libcpp83gts_callback_and_action/cb_scan_full_area_and_crop.cpp \
					sources/libcpp83gts_callback_and_action/cb_scnr_area.cpp \
					sources/libcpp83gts_callback_and_action/cb_trace_batch.cpp \
					sources/libcpp83gts_callback_and_action/dogascan_area_rot90.cpp \
					sources/libcpp83gts_callback_and_action/dogascan_area_val_and_opengl_rect.cpp \
					sources/libcpp83gts_callback_and_action/dogascan_event.cpp \
					sources/libcpp83gts_callback_and_action/dogascan_print_window_headline.cpp \
					sources/libcpp83gts_callback_and_action/dogascan_scrollbar.cpp \
					sources/libcpp83gts_callback_and_action/fltk_event.cpp \
					sources/libcpp83gts_callback_and_action/fltk_opengl_draw.cpp \
					sources/libcpp83gts_callback_and_action/fltk_opengl_handle.cpp \
					sources/libcpp83gts_callback_and_action/igs_lex_white_space_and_double_quote.cpp \
					sources/libcpp83gts_callback_and_action/ids_path_fltk_native_browse.cpp \
					sources/libcpp83gts_callback_and_action/ids_path_level_from_files.cpp \
					sources/libcpp83gts_callback_and_action/iipg_color_trace.cpp \
					sources/libcpp83gts_callback_and_action/iipg_rot90.cpp \
					sources/libcpp83gts_callback_and_action/iipg_save.cpp \
					sources/libcpp83gts_callback_and_action/iipg_scan.cpp \
					sources/libcpp83gts_callback_and_action/iipg_view.cpp \
					sources/libcpp83gts_callback_and_action/memory_config_load.cpp \
					sources/libcpp83gts_callback_and_action/memory_config_save.cpp \
					sources/libcpp83gts_callback_and_action/memory_config_trace_src_hsv_load.cpp \
					sources/libcpp83gts_callback_and_action/memory_config_trace_src_hsv_save.cpp \
					sources/libcpp83gts_callback_and_action/memory_desktop_load.cpp \
					sources/libcpp83gts_callback_and_action/memory_desktop_save.cpp \
					sources/libcpp83gts_callback_and_action/memory_install_setup.cpp \
					sources/libcpp83gts_callback_and_action/memory_scan_area.cpp \
					sources/libcpp83gts_callback_and_action/memory_short_cut_key.cpp

if WINDOWS
libgts_la_CPPFLAGS += -Ithirdparty/twain/twain-2.3
libgts_la_SOURCES += \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_entry.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_get_cc.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_init_tw_id.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_pri_cc.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_pri_error.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_state1to2.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_state2to1.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_state2to3.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_state3to2.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_state3to4.cpp \
					 sources/libcpp55iip_scan/tw_win_l1_dsm_state4to3.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_calc.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_ctnr.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_ctnr_onev.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_ctnr_range.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_get_param_onev.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_ctnr_enum.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_ctnr_onev.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_ctnr_range.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_param_enum.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_param_onev.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_pri_param_range.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_set_ctnr.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_set_ctnr_onev.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_cap_set_param_onev.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_get.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_get_reso.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_pri.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imageinfo_pri_all.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_get.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_pri.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_pri_all.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_set.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_imagelayout_set_area.cpp \
					 sources/libcpp55iip_scan/tw_win_l2_dss_setupmemxfer_pri.cpp \
					 sources/libcpp55iip_scan/tw_win_l3_dsi_state4to5.cpp \
					 sources/libcpp55iip_scan/tw_win_l3_dsi_state5to4.cpp \
					 sources/libcpp55iip_scan/tw_win_l3_dsi_state5to6to5event.cpp \
					 sources/libcpp55iip_scan/tw_win_l3_dsi_state6to7to6native.cpp \
					 sources/libcpp55iip_scan/tw_win_l3_dsi_state6to7to6select.cpp \
					 sources/libcpp55iip_scan/tw_win_l4_scan_orc.cpp \
					 sources/libcpp55iip_scan/tw_win_l4_scan_pri_dib_header.cpp \
					 sources/libcpp55iip_scan/tw_win_l4_scan_trans_image.cpp
else
libgts_la_CPPFLAGS += $(SANE_CFLAGS)
libgts_la_SOURCES += \
					 sources/libcpp55iip_scan/sane_scan.cpp
endif

bin_PROGRAMS = gts
gts_LDFLAGS = $(SANE_LDFLAGS)
gts_CPPFLAGS = $(libgts_la_CPPFLAGS)
gts_LDADD = \
			libgts.la \
			$(TIFF_LIBS) \
			$(FLTK_LIBS) \
			$(SANE_LIBS)
gts_SOURCES = sources/main/main.cpp

