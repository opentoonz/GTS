#ifndef image_common_h
#define image_common_h

#include <cstddef> /* std::size_t */
#include <string>  /* std::string */
#include <sstream> /* std::ostringstream */

namespace image { /* 画像に関する */
namespace common { /* 定義、宣言 */

/* データ並びに対する画像の向き */
namespace orientation {
 enum side {
	/* 例で説明 : topleftの場合 : Data並びの
		Raw(scanline)の開始は上(top)、
		Column(pixel)の開始は左(left)
	*/
#if 0
#define	TIFFTAG_ORIENTATION		274	/* +image orientation */
#define	    ORIENTATION_TOPLEFT		1	/* row 0 top,col 0 lhs */
#define	    ORIENTATION_TOPRIGHT	2	/* row 0 top,col 0 rhs */
#define	    ORIENTATION_BOTRIGHT	3	/* row 0 bottom,col 0 rhs */
#define	    ORIENTATION_BOTLEFT		4	/* row 0 bottom,col 0 lhs */
#define	    ORIENTATION_LEFTTOP		5	/* row 0 lhs,col 0 top */
#define	    ORIENTATION_RIGHTTOP	6	/* row 0 rhs,col 0 top */
#define	    ORIENTATION_RIGHTBOT	7	/* row 0 rhs,col 0 bottom */
#define	    ORIENTATION_LEFTBOT		8	/* row 0 lhs,col 0 bottom */
#endif
	/* 上記 tiff.hのORIENTATIONタグ値と合わせる */
	topleft = 1	/* Video(=default) */
	, toprigh
	, botrigh
	, botleft	/* OpenGL */
	, lefttop
	, rightop
	, righbot
	, leftbot
	, not_defined	/* 定義してない */ /* defaultはtopleft */
 };
}

/* 解像度の単位 */
namespace resolution {
 enum unit {
	not_defined=0	/* pic,sgi=定義してない=pixelに1対1=default */
	, meter		/* png(Spec 1.2) */
	, centimeter	/* tif(Spec 6.0) */
	, millimeter
	, inch		/* tif(Spec 6.0)=default */
	, nothing	/* tif(Spec 6.0)単位の指定がないとき */
 };
}

/* 画像固有情報(大きさ、データ並びに対する画像の向き、解像度) */
struct properties {
	properties():
		height(0), width(0), channels(0), bits(0)
		, orie_side(orientation::not_defined)
		, reso_unit(resolution::not_defined)
		, reso_x(0.)
		, reso_y(0.)
	{}
	size_t height , width , channels , bits;
	orientation::side orie_side;
	resolution::unit  reso_unit;
	double	reso_x, reso_y;
		/* tif(Spec 6.0) is float x y resolution */
		/* png(Spec 1.2) is unsigned integer x y resolution */
};

/* 画像ファイル読み込み抽象クラス */
class reader {
public:
 	/* 01 GUI等に表示するファイル書式名 */
	virtual const char* const format_name(void) const = 0;

	/* 02 利用可能な１個以上の拡張子の数 */
	virtual const size_t ext_count(void) = 0;

	/* 03 利用可能な１個以上の拡張子名 */
	virtual const char *const ext_name(size_t count) = 0;

	/* 04 ファイルヘッダタグから書式に一致したファイルか調べる */
	virtual const bool istag(
		const size_t bytes_count
		, const void* const tag_array
	) = 0;

	/* 05 情報を得る、詳細 */
	virtual void get_info(
		const std::string& file_path
		, std::string& info
	) = 0;

	/* 06 情報を得る、表形式、ヘッド */
	virtual void get_line_head(
		std::string& line_head
	) = 0;

	/* 07 情報を得る、表形式、１行 */
	virtual void get_line_info(
		const std::string& file_path
		, std::string& line_info
	) = 0;

	/* 08 画像、作業情報をメモリに読むため用意すべきサイズを得る */
	virtual void get_size(
		const std::string& file_path
		, size_t& image_bytes	// size_t for x32 and x64
		, size_t& history_bytes	// size_t for x32 and x64
	) = 0;

	/* 09 画像情報、画像、ヒストリ情報をメモリに読む
		正常終了でも例外処理throw、(デストラクタ)、でも、
		内部メモリ解放し、ファイルを閉じるよう設計する */
	virtual void get_data(
		const std::string& file_path
		, properties& props
		, const size_t image_bytes // size_t for x32 and x64
		, void* image_array /* モノ画像はゼロが黒 */
		, std::string& history_str
			/* date,time,host,user,application,project */
		, bool& break_sw /* 中断Switch。外からtureで中断 */
		, const size_t segment_bytes = 1000000
			/* 分割読込の個々サイズ(tif以外で使用する) */
	) = 0;

	/* 派生Classのdestructorを呼び出すため仮想destructorの空定義 */
	virtual ~reader(){}
};

/* 画像ファイル書き出し抽象クラス */
class writer {
public:
	virtual const char* const format_name(void) const = 0;
	virtual const size_t ext_count(void) = 0;
	virtual const char *const ext_name(size_t count) = 0;

	virtual const size_t compression_count(void) = 0;
	virtual const char *const compression_name(size_t count) = 0;

	virtual const bool error_from_properties(
		const properties& props
		, const int ext_number
		, std::ostringstream& error_or_warning_msg
	) = 0;
	virtual void put_data(
		const properties& props
		, const size_t image_bytes // size_t for x32 and x64
		, const void* image_array /* モノ画像はゼロが黒 */
		, const int compression_number
		, const std::string& history_str
			/* date,time,host,user,application,project */
		, const std::string& file_path
	) = 0;

	/* 派生Classのdestructorを呼び出すため仮想destructorの空定義 */
	virtual ~writer(){}
};

/* CPUのバイトオーダ */
std::string get_byte_order(void);

} // namespace common
} // namespace image

#endif /* !image_common_h */
