#include <string.h> /* for memset() */
#include "ptbl_returncode.h"
#include "pri.h"

#include "cpu_byte_order_is_little_endian.h"
#include "tga.h"

/* へッダー情報をファイルから読み込む */
static int _tga_read_head( BREAD *tp_bread, TGA_FILE_HEADER *tp_header )
{
	if (OK != bread_ui8(
	tp_bread,  (uint8_t *)&(tp_header->uc_numid) )) {
				_r_ui8err("uc_numid"); return NG; }
	if (OK != bread_ui8(
	tp_bread,  (uint8_t *)&(tp_header->uc_maptyp) )) {
				_r_ui8err("uc_maptyp"); return NG; }
	if (OK != bread_ui8(
	tp_bread,  (uint8_t *)&(tp_header->uc_imgtyp) )) {
				_r_ui8err("uc_imgtyp"); return NG; }
	if (OK != bread_ui16(
	tp_bread,   (uint8_t *)&(tp_header->s_maporig)  )) {
				_r_ui16err("s_maporig"); return NG; }
	if (OK != bread_ui16(
	tp_bread,   (uint8_t *)&(tp_header->s_mapsize) )) {
				_r_ui16err("s_mapsize"); return NG; }
	if (OK != bread_ui8(
	tp_bread,  (uint8_t *)&(tp_header->uc_mapbits)  )) {
				_r_ui8err("uc_mapbits"); return NG; }
	if (OK != bread_ui16(
	tp_bread,   (uint8_t *)&(tp_header->s_xorig)  )) {
				_r_ui16err("s_xorig"); return NG; }
	if (OK != bread_ui16(
	tp_bread,   (uint8_t *)&(tp_header->s_yorig)  )) {
				_r_ui16err("s_yorig"); return NG; }
	if (OK != bread_ui16(
	tp_bread,   (uint8_t *)&(tp_header->s_xsize)  )) {
				_r_ui16err("s_xsize"); return NG; }
	if (OK != bread_ui16(
	tp_bread,   (uint8_t *)&(tp_header->s_ysize)  )) {
				_r_ui16err("s_ysize"); return NG; }
	if (OK != bread_ui8(
	tp_bread,  (uint8_t *)&(tp_header->uc_pixsize)  )) {
				_r_ui8err("uc_pixsize"); return NG; }
	if (OK != bread_ui8(
	tp_bread,  (uint8_t *)&(tp_header->uc_imgdes)  )) {
				_r_ui8err("uc_imgdes"); return NG; }
	return OK;
}

static int _tga_read_check_head( TGA_FILE_HEADER *tp_header )
{
	/*
	32Bits,24Bits,16Bits,15Bits,8Bitsでなければ
	エラーとしてはじく
	*/
	switch (tp_header->uc_pixsize) {
	case 32: case 24: case 16: case 15: break;
	default:
		pri_funct_err_bttvr(
			"Error : bad tp_header->uc_pixsize<%d>.",
			tp_header->uc_pixsize);
		return NG;
	}
	return OK;
}

int tga_read_open( char *cp_fname, TGA_READ *tp_read )
{
	int	ii;
	unsigned char	uc_tmp;

	/* 引数チェック */
	if (NULL == cp_fname ) {
		pri_funct_err_bttvr(
			"Error : bad argument, cp_fname is NULL." );
		return NG;
	}
	if (NULL == tp_read ) {
		pri_funct_err_bttvr(
			"Error : bad argument, tp_read is NULL." );
		return NG;
	}

	/* 既にファイルオープンしていたらだめ */
	if (NULL != tp_read->t_bread._fp ) {
		pri_funct_err_bttvr(
			"Error : file<%s> is already opened.",cp_fname);
		return NG;
	}

	/* ファイルオープンする */
	if (OK != bread_open( cp_fname, &(tp_read->t_bread) )) {
		pri_funct_err_bttvr(
	 "Error : bread_open(-) returns NG." );
		return NG;
	}

	/* ファイルはリトルインディアンオーダーであるとして読み込む */
	if (cpu_byte_order_is_little_endian()) {
		bread_set_byte_swap_sw( OFF, &(tp_read->t_bread) );
	} else {
		bread_set_byte_swap_sw( ON, &(tp_read->t_bread) );
	}

	/* ファイルヘッダの読み込み */
	if (OK != _tga_read_head(
		&(tp_read->t_bread), &(tp_read->t_tga_file_header) )
	) {
		pri_funct_err_bttvr(
	 "Error : _tga_read_head(-) returns NG." );
		tga_read_close(tp_read);
		return NG;
	}

	/* ヘッダの値のチェック */
	if (OK != _tga_read_check_head(
		&(tp_read->t_tga_file_header)
	)) {
		pri_funct_err_bttvr(
	 "Error : _tga_read_check_head(-) returns NG." );
		tga_read_close(tp_read);
		return NG;
	}

	/* Skip id field data */
	for (ii = 0; ii < tp_read->t_tga_file_header.uc_numid; ++ii) {
		if (OK != bread_ui8(
		&(tp_read->t_bread), &uc_tmp )) {
			   _r_ui8err("uc_tmp");
			return NG;
		}
	}

	return OK;
}
