#ifndef image_tif_read_handle_h
#define image_tif_read_handle_h

#include <cstdint> /* int32_t */
#include <string>
#include "tiffio.h" /* TIFF uint32 */

/*
●ORIENTAION値の意味

6	右上	画像は90度反時計回り回転して保存
7	右下	画像は90度時計回り回転して左右反対に保存

コード1の「最初の行：上・最初の列：左」の場合、
イメージデータは一番上の行の左端からスキャンを開始し、
各行は左から右へ、上から下へという順番で保存されます
Define			コード	行列	スキャン開始位置：
-----------------------+-------+-------+------------------
ORIENTATION_TOPLEFT	1	上左	基準：左上原点：TIFF,SGI系
ORIENTATION_TOPRIGHT	2	上右	左右反転
ORIENTATION_BOTRIGHT	3	下右	上下反転&左右反転(or180度回転)
ORIENTATION_BOTLEFT	4	下左	上下反転：OpenGL系
ORIENTATION_LEFTTOP	5	左上	90度時計回り回転&左右反転
ORIENTATION_RIGHTTOP	6	右上	90度反時計回り回転：Scan時
ORIENTATION_RIGHTBOT	7	右下	90度反時計回り回転&左右反転
ORIENTATION_LEFTBOT	8	左下	90度時計回り回転
-----------------------+-------+-------+------------------

●ORIENTAION規定値以外の値の処理
・std::numeric_limits<unsigned int>::max() --> not defined
・0(古いphotoshopで作成したTIFFデータ)
・それ以外の規定値 --> not support
の場合、
default値のORIENTATION_TOPLEFTであるとして、
受け入れることにする 2012-12-14
*/

namespace image {
namespace tif {
 class read_handle { /* libtiffの(開く用)TIFFヘッダ生成破棄クラス */
 public:
  	/* クラスのインスタンス化時にTIFFファイルを開く
	ファイルがない等のときは例外を投げるので、try{}catch{}必須です
	*/
	explicit
	read_handle(const std::string& file_path);

	/* このlibで読めるTIFFの書式かどうかを調べてダメなら例外投げる */
	void check_parameters(void);

	/* ファイルから得た書式の情報を文字書式付で得る */
	std::string get_formed_parameter(void);

	/* libtiffの関数を使うときにTIFFヘッダー情報を渡すためのポインタ */
	operator TIFF*() { return this->p_; }

	/* 各TIFFのfield値を得る
		戻り値は、field値存在の有無
	*/
	/* 必須タグ このタグが無い時はデフォルト値を返すか、エラー例外 */
	uint32 imagewidth( bool& isexist );    /* タグないとエラー例外 */
	uint32 imagelength( bool& isexist );   /* タグないとエラー例外 */
	uint16 bitspersample( bool& isexist ); /* タグないと1を返す */
	uint16 compression( bool& isexist );   /* タグないとCOMPRESSION_NONE(1)を返す */
	uint16 photometric( bool& isexist );   /* タグないとエラー例外 */
	float xresolution( bool& isexist );    /* タグないとエラー例外 */
	float yresolution( bool& isexist );    /* タグないとエラー例外 */
	uint16 resolutionunit( bool& isexist );/* タグないとRESUNIT_INCH(2)を返す	 */
	/* 選択タグ このタグは任意なので、存在の有無のチェックが必要 */
	uint16 fillorder( bool& isexist );	/* タグ無か値がMin/MaxならFILLORDER_MSB2LSB(1)を返す */
	uint16 orientation( bool& isexist );	/* タグ無か値がMin/MaxならORIENTATION_TOPLEFT(1)を返す */
	uint16 samplesperpixel( bool& isexist );/* そのまま値を返す*/
	uint16 planarconfig( bool& isexist );	/* タグ無か値がMin/MaxならPLANARCONFIG_CONTIG(RGBRGB...)を返す */
	/* タイル情報 istiled()がtrueのみtilewidth(),tilelength()を使う */
	bool istiled(void);
	uint32 tilewidth( bool& isexist );
	uint32 tilelength( bool& isexist );

	/* TIFFファイルを閉じる */
	void close(void);

	/* このクラスが消滅したときTIFFファイルを閉じる */
	~read_handle();

  private:
	read_handle();

	TIFF *p_;
 };
}
}

#endif /* !image_tif_read_handle_h */
