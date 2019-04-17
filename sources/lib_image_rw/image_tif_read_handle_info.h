#ifndef image_tif_read_handle_info_h
#define image_tif_read_handle_info_h

#include <string>  // std::string

namespace image {
namespace tif {

/* tifファイルの情報を得る */
std::string get_info(
	  const std::string& name
	, const std::string& file_path
);

/* tifファイルの情報を一行単位で得る */
std::string get_line_head( void );
std::string get_line_info( const std::string& file_path );

/* --- ここからtiff独自 --- */

/* CPUのバイトオーダを得る */
std::string get_byte_order(void);

/* 圧縮種類のリストを得る */
std::string get_compression_list(void);

/* 画像向き種類のリストを得る */
std::string get_orientation_list(void);

/* 画像種類リストを得る */
std::string get_photometric_list(void);

/* 画像格納順序リストを得る */
std::string get_planarconfig_list(void);

/* データビットの向きリストを得る */
std::string get_fillorder_list(void);

/* libtiffによるTIFF情報の表示 */
void print_tiff_directory(int argc, char *argv[]);

} // namespace tif
} // namespace image

#endif /* !image_tif_read_handle_info_h */
