#ifndef image_tif_writer_h
#define image_tif_writer_h

#include "image_common.h"

namespace image {
namespace tif {

/*
TIFF 6.0 Specificationより、
TIFFTAG_ORIENTATIONは、
	"Support for orientations other than 1 is not
	a Baseline TIFF requirement."
	"1以外の方向のサポートは、Baseline TIFFの要件ではない"
よって、
保存時のTIFFTAG_ORIENTATIONは、
特別理由がない限り、
画像をORIENTATION_TOPLEFTに変換し、
タグをORIENTATION_TOPLEFTとして保存する

ORIENTATION_TOPLEFT	1 上左	  0度回転	基準：左上原点：TIFF,SGI系
ORIENTATION_TOPRIGHT	2 上右			左右反転
ORIENTATION_BOTRIGHT	3 下右	180度回転	上下反転&左右反転
ORIENTATION_BOTLEFT	4 下左			上下反転：OpenGL系
ORIENTATION_LEFTTOP	5 左上			90度時計回り回転&左右反転
ORIENTATION_RIGHTTOP	6 右上	270度回転	Scan時
ORIENTATION_RIGHTBOT	7 右下			90度反時計回り回転&左右反転
ORIENTATION_LEFTBOT	8 左下	 90度回転
*/
/*------comment out-----------------------------------
以下標仕仕様(らしい)
#define	COMPRESSION_NONE	1	// dump mode
#define	COMPRESSION_CCITTRLE	2	// CCITT modified Huffman RLE
#define	COMPRESSION_PACKBITS	32773	// Macintosh RLE

以下拡張仕様(らしい)
#define	COMPRESSION_CCITTFAX3	3	// CCITT Group 3 fax encoding
#define	COMPRESSION_CCITT_T4	3       // CCITT T.4 (TIFF 6 name)
#define	COMPRESSION_CCITTFAX4	4	// CCITT Group 4 fax encoding
#define	COMPRESSION_CCITT_T6	4       // CCITT T.6 (TIFF 6 name)
#define	COMPRESSION_LZW		5       // Lempel-Ziv  & Welch
#define	COMPRESSION_JPEG	7	// %JPEG DCT compression
(注意)
CCITTFAX3,CCITTFAX4で２値画像を保存すると、
Photoshop CS2(9.0.2)で、
	1.ピクセル比が0.5となり
	2.PHOTOMETRIC_MINISBLACKの指定を無視して0-->white,1-->black
となる問題がある。
画像(5590x3417x1bits)のファイルサイズは、 
	COMPRESSION_NONE	2409444bytes(Photoshop CS2(9.0.2))
	COMPRESSION_CCITTFAX4	  21542bytes
	COMPRESSION_CCITTFAX3	 129696bytes
	COMPRESSION_CCITTRLE	 125934bytes
となる
------comment out----------------------------------*/
/*
const int compression_number ...
0 COMPRESSION_NONE	1	dump
1 COMPRESSION_LZW	5	Lempel-Ziv & Welch		Not monoBW
2 COMPRESSION_PACKBITS	32773	Macintosh RLE			Not monoBW
3 COMPRESSION_CCITTFAX4	4					Only monoBW
4 COMPRESSION_CCITTRLE	2	CCITT modified Huffman RL	Only monoBW
*/

/* TIFF画像ファイル保存クラス */
class writer : public common::writer {
public:
	writer();

	const char *const format_name(void) const;

	const size_t ext_count(void);
	const char *const ext_name(size_t count);

	const size_t compression_count(void);
	const char *const compression_name(size_t count);

	const bool error_from_properties(
		const common::properties& props
		, const int ext_number
		, std::ostringstream& error_or_warning_msg
	);
	void put_data(
		const common::properties& prop
		, const size_t image_bytes
		, const void* image_array
		, const int compression_number
		, const std::string& history_str
		, const std::string& file_path
	);

	/* image::tif::writer独自 */
	int comp_num_from_name_num( const int name_num );
private:
	static const char *const format_name_;
};

} // namespace tif
} // namespace image

#endif /* !image_tif_writer_h */
