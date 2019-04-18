#include <cstdio>	/* vsnprintf() */
#include <string>	/* std::string */
#include <stdexcept>	/* std::runtime_error */
#include <limits>	/* std::numeric_limits<unsigned char> */
#include "image_tif_common.h"

/*
libtiffのvariable argumentエラーメッセージをchar文字列にする
注意：スレッドセーフではない

#include <tiffio.h>
#include <cstdarg>
typedef void (*TIFFErrorHandler)(const char* module, const char* fmt, va_list ap);
TIFFErrorHandler TIFFSetErrorHandler(TIFFErrorHandler handler);

Exsample1: "tmp.tif;0: Invalid strip byte count, strip 0"
Exsample2: "tmp;Not a TIFF file, bad magic number 25462 (0x6376)
*/
namespace {
 const char *const format_name_ = { "TIFF(Tagged Image File Format)" };
 const char *const extensions_[] = { "tif" };
}
namespace image {
namespace tif {

void error_handler(
	const char* module ,const char* fmt ,va_list ap
) {
	std::string buf;
	buf += module;	/* 入力ファイル名("tmp.tif"等) */
	buf += ";";	/* 区切り */

	/* libtiffのエラーメッセージ */
	char msg_buf_[1000]; msg_buf_[0] = '\0';
	const int siz =
#if defined _WIN32 & (1200 == _MSC_VER) // vc6 compile_type
	_vsnprintf( msg_buf_ ,sizeof(msg_buf_) ,fmt ,ap );
#elif defined _WIN32 & (1400 <= _MSC_VER) // over vc2005 compile_type
	vsnprintf_s(msg_buf_ ,sizeof(msg_buf_) ,_TRUNCATE ,fmt ,ap );
#else
	vsnprintf(  msg_buf_ ,sizeof(msg_buf_) ,fmt ,ap );
#endif
	if (static_cast<int>(sizeof(msg_buf_)) <= siz) { msg_buf_[sizeof(msg_buf_)-1] = '\0';}
	buf += msg_buf_;

	throw std::runtime_error(buf);
}

const char *const format_name = format_name_;
const char *const ext_name(size_t number) { return extensions_[number]; }
size_t ext_count(void) { return sizeof(extensions_) / sizeof(char*); }

/* bitsサンプリングはTIFF以外にはなさそう(?)なので"image::tif"で定義 */
const size_t bytes_of_scanline(
	const size_t width , const size_t channels , const size_t bits
) {
	const size_t sl_bits = width * channels * bits;
	return sl_bits / std::numeric_limits<unsigned char>::digits
	+((0==(sl_bits % std::numeric_limits<unsigned char>::digits))?0:1);
	/* モノクロ２階調のみの場合 */
	// sl_bytes = width/CHAR_BIT + ((width%CHAR_BIT)?1:0);
}

/* 画像の上下反転 */
void reverse_top_bottom(
	  const size_t height
	, const size_t width
	, const size_t channels
	, const size_t bits
	, unsigned char *ucharp_image )
{
	const size_t sl_bytes = bytes_of_scanline( width ,channels ,bits );
	unsigned char *ucharp_top = ucharp_image;
	unsigned char *ucharp_bot = ucharp_image + sl_bytes * (height-1);

	for (size_t yy = 0; yy < height/2; ++yy) {
		for (size_t xx = 0; xx < sl_bytes; ++xx) {
			std::swap( ucharp_top[xx] , ucharp_bot[xx] );
		}
		ucharp_top += sl_bytes;
		ucharp_bot -= sl_bytes;
	}
}

} // namespace tif
} // namespace image
