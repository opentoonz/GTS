#ifndef image_tif_reader_h
#define image_tif_reader_h

#include "image_common.h"

namespace image {
namespace tif {

/* TIFF画像ファイル読み込みクラス */
class reader : public common::reader {
public:
	/* 01 GUI等に表示するファイル書式名 */
	const char* const format_name(void) const;

	/* 02 利用可能な１個以上の拡張子の数 */
	const size_t ext_count(void);

	/* 03 利用可能な１個以上の拡張子名 */
	const char *const ext_name(size_t count);

	/* 04 ファイルヘッダタグから書式に一致したファイルか調べる */
	const bool istag(
		const size_t byte_count
		, const void*const tag_array);

	/* 05 情報を得る、詳細 */
	void get_info(
		const std::string& file_path
		, std::string& info);

	/* 06 情報を得る、表形式、ヘッド */
	void get_line_head(
		std::string& line_head);

	/* 07 情報を得る、表形式、１行 */
	void get_line_info(
		const std::string& file_path
		, std::string& line_info);

	/* 08 画像、作業情報をメモリに読むため用意すべきサイズを得る */
	void get_size(
		const std::string& file_path
		, size_t& image_bytes
		, size_t& history_bytes);

	/* 09 画像情報、画像、ヒストリ情報をメモリに読む
		正常終了でも例外処理throw、(デストラクタ)、でも、
		内部メモリ解放し、ファイルを閉じるよう設計する
		props.orie_sideがTL(左上原点)の場合
		BL(OpenGL座標系=左下原点)に補正して読み込む	
	*/
	void get_data(
		const std::string& file_path
		, common::properties& props
		, const size_t image_bytes
		, void* image_array
		, std::string& history_str
		, bool& break_sw /* 中断Switch。外からtureで中断 */
		, const size_t segment_bytes = 1000000
			/* 分割読込の個々サイズ(tif以外で使用する) */
	);

private:
	static const char *const format_name_; /* ファイル書式名 */
};

} // namespace tif
} // namespace image

#endif /* !image_tif_reader_h */
