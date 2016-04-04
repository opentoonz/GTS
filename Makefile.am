ACLOCAL_AMFLAGS = -I m4
CPPFLAGS += -DPKGDATADIR='"$(pkgdatadir)"'

pkgdata_DATA = \
			   sources/main/_gts-scan_area.txt \
			   sources/main/gts_install_setup.txt

lib_LTLIBRARIES = \
				  libc11portable.la \
				  libc12pri.la \
				  libc14image_rw_base.la \
				  libc16image_rw_tif.la \
				  libc18image_rw_tga.la \
				  libcpp31calcu_precision.la \
				  libcpp38calcu_rgb_to_hsv.la \
				  libcpp51iip_canvas.la \
				  libcpp52iip_rw.la \
				  libcpp53iip_precision.la \
				  libcpp55iip_scan.la \
				  libcpp56iip_opengl.la \
				  libcpp64iip_rot90.la \
				  libcpp69iip_scale_by_subpixel.la \
				  libcpp71iip_color_trace_hab.la \
				  libcpp72iip_erase_dot_noise.la \
				  libcpp81gts_file_browser.la \
				  libcpp82gts_hsv_histogram.la \
				  libcpp83gts_callback_and_action.la

libc11portable_la_LDFLAGS = -version-info 0:0:0
libc11portable_la_SOURCES = \
							sources/libc11portable/ptbl_cpu_is_little_endian.c \
							sources/libc11portable/ptbl_dir_or_file_is_exist.c \
							sources/libc11portable/ptbl_get_cp_hostname.c \
							sources/libc11portable/ptbl_get_cp_loginname.c \
							sources/libc11portable/ptbl_get_cp_username.c \
							sources/libc11portable/ptbl_get_cp_userrealname.c \
							sources/libc11portable/ptbl_mkdir.c \
							sources/libc11portable/ptbl_utils_about_path.c

libc12pri_la_LDFLAGS = -version-info 0:0:0
libc12pri_la_CFLAGS = \
					  -Isources/libc11portable
libc12pri_la_SOURCES = \
						  sources/libc12pri/pri_cv.c \
						  sources/libc12pri/pri_msg_and_err.c

libc14image_rw_base_la_LDFLAGS = -version-info 0:0:0
libc14image_rw_base_la_CFLAGS = \
								-Isources/libc12pri \
								-Isources/libc11portable
libc14image_rw_base_la_SOURCES = \
								 sources/libc14image_rw_base/bread.c \
								 sources/libc14image_rw_base/bwrite.c

libc16image_rw_tif_la_LDFLAGS = -version-info 0:0:0
libc16image_rw_tif_la_CFLAGS = \
							   -Isources/libc12pri \
							   -Isources/libc11portable \
							   $(TIFF_CFLAGS)
libc16image_rw_tif_la_SOURCES = \
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
								sources/libc16image_rw_tif/tif_write_scanline.c

libc18image_rw_tga_la_LDFLAGS = -version-info 0:0:0
libc18image_rw_tga_la_CFLAGS = \
							   -Isources/libc14image_rw_base \
							   -Isources/libc12pri \
							   -Isources/libc11portable
libc18image_rw_tga_la_SOURCES = \
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
								sources/libc18image_rw_tga/tga_write_setup_header.c

libcpp31calcu_precision_la_LDFLAGS = -version-info 0:0:0
libcpp31calcu_precision_la_CPPFLAGS = \
									  -Isources/libc11portable
libcpp31calcu_precision_la_SOURCES = \
									 sources/libcpp31calcu_precision/calcu_precision.cpp

libcpp38calcu_rgb_to_hsv_la_LDFLAGS = -version-info 0:0:0
libcpp38calcu_rgb_to_hsv_la_CPPFLAGS = \
									   -Isources/libc11portable
libcpp38calcu_rgb_to_hsv_la_SOURCES = \
									 sources/libcpp38calcu_rgb_to_hsv/from_hsv.cpp \
									 sources/libcpp38calcu_rgb_to_hsv/to_hsv.cpp

libcpp51iip_canvas_la_LDFLAGS = -version-info 0:0:0
libcpp51iip_canvas_la_CPPFLAGS = \
								 -Isources/libcpp31calcu_precision \
								 -Isources/libc12pri \
								 -Isources/libc11portable
libcpp51iip_canvas_la_SOURCES = \
								sources/libcpp51iip_canvas/iip_canvas.cpp \
								sources/libcpp51iip_canvas/iip_channel_info.cpp

libcpp52iip_rw_la_LDFLAGS = -version-info 0:0:0
libcpp52iip_rw_la_CPPFLAGS = \
							 -Isources/libcpp51iip_canvas \
							 -Isources/libc18image_rw_tga \
							 -Isources/libc16image_rw_tif \
							 -Isources/libc14image_rw_base \
							 -Isources/libc12pri \
							 -Isources/libc11portable
libcpp52iip_rw_la_SOURCES = \
							sources/libcpp52iip_rw/check_save.cpp \
							sources/libcpp52iip_rw/iip_read_file.cpp \
							sources/libcpp52iip_rw/iip_read_header.cpp \
							sources/libcpp52iip_rw/iip_read_set_tif_param.cpp \
							sources/libcpp52iip_rw/iip_write_file.cpp \
							sources/libcpp52iip_rw/iip_write_set_file_attrbute_from_read.cpp \
							sources/libcpp52iip_rw/iip_write_set_tif_param.cpp \
							sources/libcpp52iip_rw/name_strings.cpp

libcpp53iip_precision_la_LDFLAGS = -version-info 0:0:0
libcpp53iip_precision_la_CPPFLAGS = \
									-Isources/libcpp51iip_canvas \
									-Isources/libcpp31calcu_precision \
									-Isources/libc12pri \
									-Isources/libc11portable
libcpp53iip_precision_la_SOURCES = \
								   sources/libcpp53iip_precision/iip_precision.cpp \
								   sources/libcpp53iip_precision/iip_precision_bw_to_uchargray.cpp

libcpp55iip_scan_la_LDFLAGS = -version-info 0:0:0
libcpp55iip_scan_la_CPPFLAGS = \
							   -Isources/libcpp51iip_canvas \
							   -Isources/libc12pri \
							   -Isources/libc11portable
if WINDOWS
libcpp55iip_scan_la_CPPFLAGS += -Ithirdparty/twain/twain-2.3
libcpp55iip_scan_la_SOURCES = \
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
libcpp55iip_scan_la_LDFLAGS += $(SANE_LDFLAGS)
libcpp55iip_scan_la_CPPFLAGS += \
								$(SANE_CFLAGS) \
								$(FLTK_CPPFLAGS)
libcpp55iip_scan_la_SOURCES = \
							  sources/libcpp55iip_scan/sane_scan.cpp
endif

libcpp56iip_opengl_la_LDFLAGS = -version-info 0:0:0
libcpp56iip_opengl_la_CPPFLAGS = \
								 -Isources/libcpp53iip_precision \
								 -Isources/libcpp51iip_canvas \
								 -Isources/libc12pri \
								 -Isources/libc11portable
libcpp56iip_opengl_la_SOURCES = \
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
								sources/libcpp56iip_opengl/iip_opengl_l3event_wview.cpp

libcpp64iip_rot90_la_LDFLAGS = -version-info 0:0:0
libcpp64iip_rot90_la_CPPFLAGS = \
								-Isources/libcpp51iip_canvas \
								-Isources/libc12pri \
								-Isources/libc11portable
libcpp64iip_rot90_la_SOURCES = \
							   sources/libcpp64iip_rot90/iip_rot90.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_bitbw.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_doubl.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_uchar.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_ulong.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_ushrt.cpp

libcpp69iip_scale_by_subpixel_la_LDFLAGS = -version-info 0:0:0
libcpp69iip_scale_by_subpixel_la_CPPFLAGS = \
											-Isources/libcpp51iip_canvas \
											-Isources/libc12pri \
											-Isources/libc11portable
libcpp69iip_scale_by_subpixel_la_SOURCES = \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_calcu_bresenham.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_exec.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_mem.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_set_canvas.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_uchar.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_ushrt.cpp

libcpp71iip_color_trace_hab_la_LDFLAGS = -version-info 0:0:0
libcpp71iip_color_trace_hab_la_CPPFLAGS = \
										  -Isources/libcpp51iip_canvas \
										  -Isources/libcpp38calcu_rgb_to_hsv \
										  -Isources/libcpp31calcu_precision \
										  -Isources/libc12pri \
										  -Isources/libc11portable
libcpp71iip_color_trace_hab_la_SOURCES = \
										 sources/libcpp71iip_color_trace_hab/calcu_color_trace_hab.cpp \
										 sources/libcpp71iip_color_trace_hab/calcu_histogram_hab.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_doubl.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_exec.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_uchar.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_ulong.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_ushrt.cpp

libcpp72iip_erase_dot_noise_la_LDFLAGS = -version-info 0:0:0
libcpp72iip_erase_dot_noise_la_CPPFLAGS = \
										  -Isources/libcpp51iip_canvas \
										  -Isources/libcpp38calcu_rgb_to_hsv \
										  -Isources/libcpp31calcu_precision \
										  -Isources/libc12pri \
										  -Isources/libc11portable
libcpp72iip_erase_dot_noise_la_SOURCES = \
										 sources/libcpp72iip_erase_dot_noise/calcu_erase_dot_noise.cpp \
										 sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_exec.cpp \
										 sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_uchar.cpp

libcpp81gts_file_browser_la_LDFLAGS = -version-info 0:0:0
libcpp81gts_file_browser_la_CPPFLAGS = \
									   -Isources/libcpp81gts_file_browser \
									   -Isources/libcpp83gts_callback_and_action \
									   -Isources/libcpp82gts_hsv_histogram \
									   -Isources/libcpp72iip_erase_dot_noise \
									   -Isources/libcpp71iip_color_trace_hab \
									   -Isources/libcpp69iip_scale_by_subpixel \
									   -Isources/libcpp64iip_rot90 \
									   -Isources/libcpp56iip_opengl \
									   -Isources/libcpp55iip_scan \
									   -Isources/libcpp53iip_precision \
									   -Isources/libcpp52iip_rw \
									   -Isources/libcpp51iip_canvas \
									   -Isources/libcpp38calcu_rgb_to_hsv \
									   -Isources/libc12pri \
									   -Isources/libc11portable \
									   $(FLTK_CPPFLAGS)
if WINDOWS
libcpp81gts_file_browser_la_CPPFLAGS += -Ithirdparty/twain/twain-2.3
endif
libcpp81gts_file_browser_la_SOURCES = \
									  sources/libcpp81gts_file_browser/gtsfbro01path_base.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro02list_base.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro03list_gui.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro04path_level.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro04text_gui.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro05list_config.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro05list_level.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro05list_level_fold.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro05list_trace_batch.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_init.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_load_cancel.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_load_dir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_load_dir_up.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_load_list.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_load_ok.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_load_wintgl.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_cancel.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_dir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_dir_up.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_file.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_list.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_ok.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_config_save_as_wintgl.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_browse_sw.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_cancel.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_dir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_dir_up.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_file_or_level.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_init.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_list.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_list_image.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_list_image_info.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_list_redisplay.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_mkdir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_name.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_ok.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_rename.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_rename_dir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_rename_file_tif.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_rename_level_tif.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_renumber.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_renumber_level_tif.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_rgb_scan_dir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_wintgl.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_level_x1view.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_add.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_alladd.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_cancel.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_dir.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_dir_up.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_init.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_list.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_run.cpp \
									  sources/libcpp81gts_file_browser/gtsfbro06cb_trace_batch_wintgl.cpp

libcpp82gts_hsv_histogram_la_LDFLAGS = -version-info 0:0:0
libcpp82gts_hsv_histogram_la_CPPFLAGS = \
										-Isources/libcpp82gts_hsv_histogram \
										-Isources/libcpp83gts_callback_and_action \
										-Isources/libcpp81gts_file_browser \
										-Isources/libcpp72iip_erase_dot_noise \
										-Isources/libcpp71iip_color_trace_hab \
										-Isources/libcpp69iip_scale_by_subpixel \
										-Isources/libcpp64iip_rot90 \
										-Isources/libcpp56iip_opengl \
										-Isources/libcpp55iip_scan \
										-Isources/libcpp53iip_precision \
										-Isources/libcpp52iip_rw \
										-Isources/libcpp51iip_canvas \
										-Isources/libcpp38calcu_rgb_to_hsv \
										-Isources/libc12pri \
										-Isources/libc11portable \
										$(FLTK_CPPFLAGS)
if WINDOWS
libcpp82gts_hsv_histogram_la_CPPFLAGS += -Ithirdparty/twain/twain-2.3
endif
libcpp82gts_hsv_histogram_la_SOURCES = \
									   sources/libcpp82gts_hsv_histogram/fltk_1000_range_cyclic.cpp \
									   sources/libcpp82gts_hsv_histogram/fltk_1000_range_minmax.cpp \
									   sources/libcpp82gts_hsv_histogram/fltk_1000x100_histogram.cpp \
									   sources/libcpp82gts_hsv_histogram/fltk_1000x10_hsv_belt_image.cpp

libcpp83gts_callback_and_action_la_LDFLAGS = -version-info 0:0:0
libcpp83gts_callback_and_action_la_CPPFLAGS = \
											  -Isources/libcpp82gts_hsv_histogram \
											  -Isources/libcpp81gts_file_browser \
											  -Isources/libcpp72iip_erase_dot_noise \
											  -Isources/libcpp71iip_color_trace_hab \
											  -Isources/libcpp64iip_rot90 \
											  -Isources/libcpp56iip_opengl \
											  -Isources/libcpp55iip_scan \
											  -Isources/libcpp53iip_precision \
											  -Isources/libcpp52iip_rw \
											  -Isources/libcpp51iip_canvas \
											  -Isources/libcpp38calcu_rgb_to_hsv \
											  -Isources/libc12pri \
											  -Isources/libc11portable \
											  $(FLTK_CPPFLAGS)
if WINDOWS
libcpp83gts_callback_and_action_la_CPPFLAGS += -Ithirdparty/twain/twain-2.3
endif
libcpp83gts_callback_and_action_la_SOURCES = \
											 sources/libcpp83gts_callback_and_action/gts_gui.cpp \
											 sources/libcpp83gts_callback_and_action/gts_master.cpp \
											 sources/libcpp83gts_callback_and_action/cb_change_view.cpp \
											 sources/libcpp83gts_callback_and_action/cb_choice_pixel_type.cpp \
											 sources/libcpp83gts_callback_and_action/cb_color_trace_full_area.cpp \
											 sources/libcpp83gts_callback_and_action/cb_color_trace_src.cpp \
											 sources/libcpp83gts_callback_and_action/cb_color_trace_tgt.cpp \
											 sources/libcpp83gts_callback_and_action/cb_color_trace_view_area.cpp \
											 sources/libcpp83gts_callback_and_action/cb_config_save.cpp \
											 sources/libcpp83gts_callback_and_action/cb_fnum_edit_insert.cpp \
											 sources/libcpp83gts_callback_and_action/cb_quit.cpp \
											 sources/libcpp83gts_callback_and_action/cb_read_and_preview.cpp \
											 sources/libcpp83gts_callback_and_action/cb_read_and_save.cpp \
											 sources/libcpp83gts_callback_and_action/cb_read_and_trace.cpp \
											 sources/libcpp83gts_callback_and_action/cb_rotate_per_90.cpp \
											 sources/libcpp83gts_callback_and_action/cb_scan_and_preview.cpp \
											 sources/libcpp83gts_callback_and_action/cb_scan_and_save.cpp \
											 sources/libcpp83gts_callback_and_action/cb_scan_full_area_and_crop.cpp \
											 sources/libcpp83gts_callback_and_action/cb_scnr_area.cpp \
											 sources/libcpp83gts_callback_and_action/color_trace_enhancement_src.cpp \
											 sources/libcpp83gts_callback_and_action/color_trace_enhancement_tgt.cpp \
											 sources/libcpp83gts_callback_and_action/dogascan_area_rot90.cpp \
											 sources/libcpp83gts_callback_and_action/dogascan_area_val_and_opengl_rect.cpp \
											 sources/libcpp83gts_callback_and_action/dogascan_event.cpp \
											 sources/libcpp83gts_callback_and_action/dogascan_print_window_headline.cpp \
											 sources/libcpp83gts_callback_and_action/dogascan_scrollbar.cpp \
											 sources/libcpp83gts_callback_and_action/fltk_event.cpp \
											 sources/libcpp83gts_callback_and_action/fltk_opengl_draw.cpp \
											 sources/libcpp83gts_callback_and_action/fltk_opengl_handle.cpp \
											 sources/libcpp83gts_callback_and_action/igs_lex_white_space_and_double_quote.cpp \
											 sources/libcpp83gts_callback_and_action/iipg_color_trace.cpp \
											 sources/libcpp83gts_callback_and_action/iipg_rot90.cpp \
											 sources/libcpp83gts_callback_and_action/iipg_save.cpp \
											 sources/libcpp83gts_callback_and_action/iipg_scan.cpp \
											 sources/libcpp83gts_callback_and_action/iipg_view.cpp \
											 sources/libcpp83gts_callback_and_action/image_mark_access.cpp \
											 sources/libcpp83gts_callback_and_action/list_access.cpp \
											 sources/libcpp83gts_callback_and_action/memory_config_load.cpp \
											 sources/libcpp83gts_callback_and_action/memory_config_save.cpp \
											 sources/libcpp83gts_callback_and_action/memory_config_trace_src_hsv_load.cpp \
											 sources/libcpp83gts_callback_and_action/memory_config_trace_src_hsv_save.cpp \
											 sources/libcpp83gts_callback_and_action/memory_desktop_load.cpp \
											 sources/libcpp83gts_callback_and_action/memory_desktop_save.cpp \
											 sources/libcpp83gts_callback_and_action/memory_scan_area.cpp \
											 sources/libcpp83gts_callback_and_action/memory_short_cut_key.cpp

bin_PROGRAMS = gts
gts_CPPFLAGS = \
			   -Isources/libcpp83gts_callback_and_action \
			   -Isources/libcpp82gts_hsv_histogram \
			   -Isources/libcpp81gts_file_browser \
			   -Isources/libcpp72iip_erase_dot_noise \
			   -Isources/libcpp71iip_color_trace_hab \
			   -Isources/libcpp64iip_rot90 \
			   -Isources/libcpp56iip_opengl \
			   -Isources/libcpp55iip_scan \
			   -Isources/libcpp53iip_precision \
			   -Isources/libcpp52iip_rw \
			   -Isources/libcpp51iip_canvas \
			   -Isources/libc12pri \
			   -Isources/libc11portable \
			   $(FLTK_CPPFLAGS)
if WINDOWS
gts_CPPFLAGS += -Ithirdparty/twain/twain-2.3
endif
gts_LDADD = \
			libcpp83gts_callback_and_action.la \
			libcpp82gts_hsv_histogram.la \
			libcpp81gts_file_browser.la \
			libcpp72iip_erase_dot_noise.la \
			libcpp71iip_color_trace_hab.la \
			libcpp69iip_scale_by_subpixel.la \
			libcpp64iip_rot90.la \
			libcpp56iip_opengl.la \
			libcpp55iip_scan.la \
			libcpp53iip_precision.la \
			libcpp52iip_rw.la \
			libcpp51iip_canvas.la \
			libcpp38calcu_rgb_to_hsv.la \
			libcpp31calcu_precision.la \
			libc18image_rw_tga.la \
			libc16image_rw_tif.la \
			libc14image_rw_base.la \
			libc12pri.la \
			libc11portable.la \
			$(TIFF_LIBS) \
			$(FLTK_LIBS) \
			$(SANE_LIBS)
gts_SOURCES = sources/main/main.cpp

