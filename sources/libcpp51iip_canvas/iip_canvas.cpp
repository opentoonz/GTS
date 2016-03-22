#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy() */
#include <limits.h>	/* CHAR_BIT */
#include <assert.h>
#include "pri.h"
#include "iip_canvas.h"

/* 色チャンネル毎のバイト数を求める */
long iip_canvas::_get_l_scanline_channel_bytes( long l_width, long l_bytes )
{
	/* 1bitモノクロ２階調 */
	if (0L == l_bytes) {
		return l_width / CHAR_BIT +
			((0L == (l_width % CHAR_BIT))? 0L: 1L);
	}
	/* その他 --- バイト単位のチャンネル */
	else {
		return	l_width * l_bytes;
	}
}

/* カンバスの色チャンネル毎のバイト数を求める */
long iip_canvas::get_l_scanline_channel_bytes( void )
{
	return this->_get_l_scanline_channel_bytes(
			this->_l_width,
			this->cl_ch_info.get_l_bytes()
	);
}

/* 大きさが同じで、さらに
条件が整っていれば、親からカンバスをコピーする */
void iip_canvas::copy_image_from_parent( const char *ccp_object_name_of_mv )
{
	iip_canvas *clpp;

	clpp = this->get_clp_parent();

	/*
	親がいて、
	かつ、親が画像をもっていて、
	かつ、自分が独立したカンバスメモリをもっているなら、
	親の画像を自分のカンバスにコピーする
	(自分のカンバスに複写して処理する) */
	if ((NULL != clpp)
	&&  (NULL != clpp->get_vp_canvas())
	&&  (ON == this->get_i_must_be_free_self_sw()) ) {
		(void)memcpy(
			this->get_vp_canvas(),
			clpp->get_vp_canvas(),
			this->_l_height *
			this->_l_channels *
			this->get_l_scanline_channel_bytes()
		);
		/* Method表示 */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"%s : copy from parent canvas",
				ccp_object_name_of_mv
			);
		}
	}
}

/* カンバスメモリを確保する */
int iip_canvas::mem_alloc_canvas( void )
{
	/* 既存のメモリ開放 */
	this->mem_free_canvas();

	/* サイズのチェック、大きさがゼロだとだめ */
	if ((this->_l_width) <= 0L) {
		pri_funct_err_bttvr(
		"Error : this->_l_width<%ld> is bad.",
			this->_l_width );
		return NG;
	}
	if ((this->_l_height) <= 0L) {
		pri_funct_err_bttvr(
		"Error : this->_l_height<%ld> is bad.",
			this->_l_height);
		return NG;
	}
	if ((this->_l_channels) <= 0L) {
		pri_funct_err_bttvr(
		"Error : this->_l_channels<%ld> is bad.",
			this->_l_channels );
		return NG;
	}

	if (OK != this->cl_ch_info.chk_e_ch_num_type()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_ch_info.chk_e_ch_num_type() returns NG" );
		return NG;
	}

	/* Method and Parameter表示 */
	if ((ON == this->_i_mv_sw) || (ON == this->_i_pv_sw)) {
		assert( NULL != this->_ccp_object_name_of_mv );
		pri_funct_msg_ttvr(
			"Alloc. %s %d bytes(%d x %d x %d x %s)",
			this->_ccp_object_name_of_mv,
			this->_l_height *
			this->_l_channels *
			this->get_l_scanline_channel_bytes(),
			this->_l_width,
			this->_l_height,
			this->_l_channels,
			this->cl_ch_info.get_cp_ch_num_type()
		);
	}

	/* メモリ確保 */
	this->_vp_canvas = calloc(
		this->_l_height,
		this->_l_channels *
		this->get_l_scanline_channel_bytes()
	);

	/* 確保したメモリの大きさを記憶しておく(free時表示のため) */
	this->_l_free_width = this->_l_width;
	this->_l_free_height = this->_l_height;
	this->_l_free_channels = this->_l_channels;
	this->_cl_free_ch_info.set_e_ch_num_type(
		this->cl_ch_info.get_e_ch_num_type() );

	if (NULL == this->_vp_canvas) {
		pri_funct_err_bttvr(
		  "Error : calloc(%ld, %ld x %ld) returns NULL.",
			this->_l_height,
			this->_l_channels,
			this->get_l_scanline_channel_bytes()
		);
		return NG;
	}

	/* メモリ管理(free())を自分がやる */
	this->_i_must_be_free_self_sw = ON;

	return OK;
}

/* カンバスメモリを開放する */
void iip_canvas::mem_free_canvas( void )
{
	/* canvasがない */
	if (NULL == this->_vp_canvas) { return; }

	/* canvasは参照しているので勝手に開放しない */
	if (OFF == this->_i_must_be_free_self_sw) { return; }

	/* Method and Parameter表示 */
	if ((ON == this->_i_mv_sw) || (ON == this->_i_pv_sw)) {
		assert( NULL != this->_ccp_object_name_of_mv );

		pri_funct_msg_ttvr(
			"Free %s %d bytes(%d x %d x %d x %s)",
			this->_ccp_object_name_of_mv,
			this->_l_free_height *
			this->_l_free_channels *
			this->_get_l_scanline_channel_bytes(
			 this->_l_free_width,
			 this->_cl_free_ch_info.get_l_bytes()
			),
			this->_l_free_width,
			this->_l_free_height,
			this->_l_free_channels,
			this->_cl_free_ch_info.get_cp_ch_num_type()
		);
	}
	free( this->_vp_canvas );
	this->_vp_canvas = NULL;
	this->_i_must_be_free_self_sw = OFF;
}
