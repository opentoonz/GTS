#ifndef image_tif_common_h
#define image_tif_common_h

namespace image {
namespace tif {

void error_handler( const char* module ,const char* fmt ,va_list ap );

extern const char *const format_name;
const char *const ext_name(size_t number);
size_t ext_count(void);

/* bitsサンプリングはTIFF以外にはなさそう(?)なので"image::tif"で定義 */
const size_t bytes_of_scanline(
	const size_t width , const size_t channels , const size_t bits
);

/* 画像の上下反転 */
void reverse_top_bottom(
	  const size_t height
	, const size_t width
	, const size_t channels
	, const size_t bits
	, unsigned char *ucharp_image
);

} // namespace tif
} // namespace image

#endif /* !image_tif_common_h */
