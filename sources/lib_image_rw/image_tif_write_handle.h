#ifndef image_tif_write_handle_h
#define image_tif_write_handle_h

#include "tiffio.h" /* TIFF */

namespace image {
namespace tif {
 class write_handle { /* libtiffの(保存用)TIFFヘッダ生成破棄クラス */
 public:
 	/* クラスのインスタンス化時にTIFFファイルを開く
	ファイルがない等のときは例外を投げるので、try{}catch{}必須です
	*/
	explicit
	write_handle(const std::string& file_path);

	/* libtiffの関数を使うときにTIFFヘッダー情報を渡すためのポインタ */
	operator TIFF*() { return this->p_; }

	/* 各値の設定 */
	void set_uint16_throw( ttag_t tag, const unsigned int val );
	void set_uint32_throw( ttag_t tag, const unsigned int val );
	void set_float_throw(  ttag_t tag, const double val );

	/* TIFFファイルを閉じる */
	void close(void);

	/* このクラスが消滅したときTIFFファイルを閉じる */
	~write_handle();
  private:
	write_handle();

	TIFF *p_;
 };
}
}

#endif /* !image_tif_write_handle_h */
