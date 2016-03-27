ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libc11portable.la \
				  libc12pri.la \
				  libc14image_rw_base.la \
				  libc16image_rw_tif.la \
				  libc18image_rw_tga.la \
				  libcpp31calcu_precision.la \
				  libcpp38calcu_rgb_to_hsv.la \
				  libcpp51iip_canvas.la \
				  libcpp52iip_rw.la \
				  libcpp53iip_precision.la \
				  libcpp56iip_opengl.la \
				  libcpp64iip_rot90.la \
				  libcpp69iip_scale_by_subpixel.la \
				  libcpp71iip_color_trace_hab.la \
				  libcpp72iip_erase_dot_noise.la

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
libc12pri_la_CFLAGS = -Isources/libc11portable
libc12pri_la_SOURCES = \
						  sources/libc12pri/pri_cv.c \
						  sources/libc12pri/pri_msg_and_err.c

libc14image_rw_base_la_LDFLAGS = -version-info 0:0:0
libc14image_rw_base_la_CFLAGS = -Isources/libc12pri -Isources/libc11portable
libc14image_rw_base_la_SOURCES = \
								 sources/libc14image_rw_base/bread.c \
								 sources/libc14image_rw_base/bwrite.c

libc16image_rw_tif_la_LDFLAGS = -version-info 0:0:0
libc16image_rw_tif_la_CFLAGS = -Isources/libc12pri -Isources/libc11portable $(TIFF_CFLAGS)
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
libc18image_rw_tga_la_CFLAGS = -Isources/libc14image_rw_base -Isources/libc12pri -Isources/libc11portable
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
libcpp31calcu_precision_la_CPPFLAGS = -Isources/libc11portable
libcpp31calcu_precision_la_SOURCES = \
									 sources/libcpp31calcu_precision/calcu_precision.cpp

libcpp38calcu_rgb_to_hsv_la_LDFLAGS = -version-info 0:0:0
libcpp38calcu_rgb_to_hsv_la_CPPFLAGS = -Isources/libc11portable
libcpp38calcu_rgb_to_hsv_la_SOURCES = \
									 sources/libcpp38calcu_rgb_to_hsv/from_hsv.cpp \
									 sources/libcpp38calcu_rgb_to_hsv/to_hsv.cpp

libcpp51iip_canvas_la_LDFLAGS = -version-info 0:0:0
libcpp51iip_canvas_la_CPPFLAGS = -Isources/libcpp31calcu_precision -Isources/libc12pri -Isources/libc11portable
libcpp51iip_canvas_la_SOURCES = \
								sources/libcpp51iip_canvas/iip_canvas.cpp \
								sources/libcpp51iip_canvas/iip_channel_info.cpp

libcpp52iip_rw_la_LDFLAGS = -version-info 0:0:0
libcpp52iip_rw_la_CPPFLAGS = -Isources/libcpp51iip_canvas -Isources/libc18image_rw_tga -Isources/libc16image_rw_tif -Isources/libc14image_rw_base -Isources/libc12pri -Isources/libc11portable
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
libcpp53iip_precision_la_CPPFLAGS = -Isources/libcpp51iip_canvas -Isources/libcpp31calcu_precision -Isources/libc12pri -Isources/libc11portable
libcpp53iip_precision_la_SOURCES = \
								   sources/libcpp53iip_precision/iip_precision.cpp \
								   sources/libcpp53iip_precision/iip_precision_bw_to_uchargray.cpp

libcpp56iip_opengl_la_LDFLAGS = -version-info 0:0:0
libcpp56iip_opengl_la_CPPFLAGS = -Isources/libcpp53iip_precision -Isources/libcpp51iip_canvas -Isources/libc12pri -Isources/libc11portable
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
libcpp64iip_rot90_la_CPPFLAGS = -Isources/libcpp51iip_canvas -Isources/libc12pri -Isources/libc11portable
libcpp64iip_rot90_la_SOURCES = \
							   sources/libcpp64iip_rot90/iip_rot90.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_bitbw.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_doubl.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_uchar.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_ulong.cpp \
							   sources/libcpp64iip_rot90/iip_rot90_ushrt.cpp

libcpp69iip_scale_by_subpixel_la_LDFLAGS = -version-info 0:0:0
libcpp69iip_scale_by_subpixel_la_CPPFLAGS = -Isources/libcpp51iip_canvas -Isources/libc12pri -Isources/libc11portable
libcpp69iip_scale_by_subpixel_la_SOURCES = \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_calcu_bresenham.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_exec.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_mem.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_set_canvas.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_uchar.cpp \
										   sources/libcpp69iip_scale_by_subpixel/iip_scale_by_subpixel_ushrt.cpp

libcpp71iip_color_trace_hab_la_LDFLAGS = -version-info 0:0:0
libcpp71iip_color_trace_hab_la_CPPFLAGS = -Isources/libcpp51iip_canvas -Isources/libcpp38calcu_rgb_to_hsv -Isources/libcpp31calcu_precision -Isources/libc12pri -Isources/libc11portable
libcpp71iip_color_trace_hab_la_SOURCES = \
										 sources/libcpp71iip_color_trace_hab/calcu_color_trace_hab.cpp \
										 sources/libcpp71iip_color_trace_hab/calcu_histogram_hab.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_doubl.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_exec.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_uchar.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_ulong.cpp \
										 sources/libcpp71iip_color_trace_hab/iip_color_trace_hab_ushrt.cpp

libcpp72iip_erase_dot_noise_la_LDFLAGS = -version-info 0:0:0
libcpp72iip_erase_dot_noise_la_CPPFLAGS = -Isources/libcpp51iip_canvas -Isources/libcpp38calcu_rgb_to_hsv -Isources/libcpp31calcu_precision -Isources/libc12pri -Isources/libc11portable
libcpp72iip_erase_dot_noise_la_SOURCES = \
										 sources/libcpp72iip_erase_dot_noise/calcu_erase_dot_noise.cpp \
										 sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_exec.cpp \
										 sources/libcpp72iip_erase_dot_noise/iip_erase_dot_noise_uchar.cpp

