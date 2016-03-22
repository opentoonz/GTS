#ifndef __iip_canvas_h__
#define __iip_canvas_h__

#include <stdio.h>
#include "ptbl_returncode.h"
#include "iip_channel_info.h"

/*
 * ピクセル情報
 */
#ifndef CH_RED
#define CH_RED 0 /* 配列格納時の赤チャンネルのオフセット位置 */
#endif
#ifndef CH_GRE
#define CH_GRE 1 /* 配列格納時の緑チャンネルのオフセット位置 */
#endif
#ifndef CH_BLU
#define CH_BLU 2 /* 配列格納時の青チャンネルのオフセット位置 */
#endif
#ifndef CH_ALP
#define CH_ALP 3 /* 配列格納時のαチャンネルのオフセット位置 */
#endif
#ifndef SZ_RGB
#define SZ_RGB 3 /* RGB配列格納時の大きさ */
#endif
#ifndef SZ_RGBA
#define SZ_RGBA 4 /* RGBA配列格納時の大きさ */
#endif

/*
 * カンバス
 */
class iip_canvas {
public:
	/* constructor */
	iip_canvas()
	{
		this->_i_mv_sw = 0;
		this->_i_pv_sw = 0;
		this->_i_cv_sw = 0;
		this->_ccp_object_name_of_mv = NULL;

		this->_clp_parent = NULL;
		this->_vp_canvas = NULL;
		this->_i_must_be_free_self_sw = OFF;

		this->_l_width = 0L;
		this->_l_height = 0L;
		this->_l_channels = 0L;

		this->_l_free_width = 0L;
		this->_l_free_height = 0L;
		this->_l_free_channels = 0L;
	}

	/* destructor */
	~iip_canvas()
	{
		this->mem_free_canvas();

		this->_i_mv_sw = 0;
		this->_i_pv_sw = 0;
		this->_i_cv_sw = 0;
		this->_ccp_object_name_of_mv = NULL;

		this->_clp_parent = NULL;
		this->_vp_canvas = NULL;
		this->_i_must_be_free_self_sw = OFF;

		this->_l_width = 0L;
		this->_l_height = 0L;
		this->_l_channels = 0L;
	}

	/* 継承して使うときのオブジェクト名を設定 */
	void set_ccp_object_name_of_mv( const char *ccp ) {
	  this->_ccp_object_name_of_mv = ccp; }
	const char *get_ccp_object_name_of_mv( void ) {
    return this->_ccp_object_name_of_mv; }

	/* 情報表示スイッチ */
	void set_i_mv_sw( int sw ) { this->_i_mv_sw = sw; }
	void set_i_pv_sw( int sw ) { this->_i_pv_sw = sw; }
	void set_i_cv_sw( int sw ) { this->_i_cv_sw = sw; }
	int get_i_mv_sw( void ) { return this->_i_mv_sw; }
	int get_i_pv_sw( void ) { return this->_i_pv_sw; }
	int get_i_cv_sw( void ) { return this->_i_cv_sw; }

	void set_l_width(    long ll ) { this->_l_width = ll; }
	void set_l_height(   long ll ) { this->_l_height = ll; }
	void set_l_channels( long ll ) { this->_l_channels = ll; }
	long get_l_width(    void ) { return this->_l_width; }
	long get_l_height(   void ) { return this->_l_height; }
	long get_l_channels( void ) { return this->_l_channels; }

	/* 各チャンネル毎の横バイト数を求める */
	long get_l_scanline_channel_bytes( void );

	/* 各チャンネル毎の情報 */
	iip_channel_info cl_ch_info;

	/* 他(親等)とつなげる、別の親とつながっていたら切れちゃうよん */
	void set_clp_parent( iip_canvas *clp ) {this->_clp_parent=clp;}

	/* 他(親等)のcanvasサイズをコピー
	(注意)元のcanvasを設定してから実行すること */
	void set_canvas_size( iip_canvas *clp ) {
		this->_l_width    = clp->get_l_width();
		this->_l_height   = clp->get_l_height();
		this->_l_channels = clp->get_l_channels();
		this->cl_ch_info.set_e_ch_num_type(
			clp->cl_ch_info.get_e_ch_num_type()
		);
	}

	/* 他(親等)のメモリを、参照(free()しない)canvasとして設定する
	(注意)元のcanvasを確保してから実行すること */
	void set_vp_reference_canvas( void *vp ) {
	  this->mem_free_canvas();
	  this->_vp_canvas = vp;
	  this->_i_must_be_free_self_sw = OFF;
	}
	/* 他(親等)からのメモリをcanvasに設定し管理(free)をここに任せる
	(注意)元のcanvasを確保してから実行すること */
	void set_vp_independence_canvas( void *vp ) {
	  this->mem_free_canvas();
	  this->_vp_canvas = vp;
	  this->_i_must_be_free_self_sw = ON;
	}

	/* 開放必要な(自前の)カンバスメモリか */
	int get_i_must_be_free_self_sw( void ) {
  return this->_i_must_be_free_self_sw;
	}

	/* 他(親等)の参照 */
	iip_canvas *get_clp_parent( void ) { return this->_clp_parent; }

	/* canvas生成 */
	int mem_alloc_canvas( void );

	/* canvas参照 */
	void *get_vp_canvas( void ) { return this->_vp_canvas;}

	/* 条件あえば、親の画像を自分のところにもってくる */
	void copy_image_from_parent( const char *ccp_object_name_of_mv );

	/* canvas消去 */
	void mem_free_canvas( void );
private:
	/* バーボーズは個々に設定し親からコピーしない */
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	/* pointerは変更できるが、指し示す文字列は変更できない */
	const char *_ccp_object_name_of_mv;

	iip_canvas *_clp_parent;

	/*
	canvasは外の(管理)メモリを参照したものでもよい。
	その場合、_i_must_be_free_self_swをOFFし、
	メモリ管理(free()するか否か)から外す。
	*/
	void	*_vp_canvas;
	int	_i_must_be_free_self_sw;

	/* 画像キャンバスの大きさ(byte単位) */
	long	_l_width,
		_l_height,
		_l_channels;

	/* 画像キャンバスの大きさfree時表示のための記憶 */
	long	_l_free_width,
		_l_free_height,
		_l_free_channels;
	iip_channel_info _cl_free_ch_info;

	/* 下請け関数etc. */
	long _get_l_scanline_channel_bytes(long l_width, long l_bytes);
};

#endif /* !__iip_canvas_h__ */
