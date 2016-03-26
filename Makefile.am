lib_LTLIBRARIES = libc11portable.la \
				  libc12pri.la \
				  libc14image_rw_base.la \
				  libc16image_rw_tif.la \
				  libc18image_rw_tga.la \
				  libcpp31calcu_precision.la \
				  libcpp38calcu_rgb_to_hsv.la \
				  libcpp51iip_canvas.la

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

