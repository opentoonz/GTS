#include <string.h> /* for memset() */

#include "ptbl_funct.h"
#include "ptbl_returncode.h"
#include "pri.h"

#include "tga.h"

static int _tga_write_header( TGA_FILE_HEADER *tp_header, BWRITE *tp_bwrite )
{
	if (OK != bwrite_ui8(
	(uint8_t *)&(tp_header->uc_numid), tp_bwrite )) {
		     _w_ui8err("uc_numid"); return NG; }
	if (OK != bwrite_ui8(
	(uint8_t *)&(tp_header->uc_maptyp), tp_bwrite )) {
		     _w_ui8err("uc_maptyp"); return NG; }
	if (OK != bwrite_ui8(
	(uint8_t *)&(tp_header->uc_imgtyp), tp_bwrite )) {
		     _w_ui8err("uc_imgtyp"); return NG; }
	if (OK != bwrite_ui16(
	(uint8_t *)&(tp_header->s_maporig), tp_bwrite )) {
		    _w_ui16err("s_maporig"); return NG; }
	if (OK != bwrite_ui16(
	(uint8_t *)&(tp_header->s_mapsize), tp_bwrite )) {
		    _w_ui16err("s_mapsize"); return NG; }
	if (OK != bwrite_ui8(
	(uint8_t *)&(tp_header->uc_mapbits), tp_bwrite )) {
		     _w_ui8err("uc_mapbits"); return NG; }
	if (OK != bwrite_ui16(
	(uint8_t *)&(tp_header->s_xorig), tp_bwrite )) {
		    _w_ui16err("s_xorig"); return NG; }
	if (OK != bwrite_ui16(
	(uint8_t *)&(tp_header->s_yorig), tp_bwrite )) {
		    _w_ui16err("s_yorig"); return NG; }
	if (OK != bwrite_ui16(
	(uint8_t *)&(tp_header->s_xsize), tp_bwrite )) {
		    _w_ui16err("s_xsize"); return NG; }
	if (OK != bwrite_ui16(
	(uint8_t *)&(tp_header->s_ysize), tp_bwrite )) {
		    _w_ui16err("s_ysize"); return NG; }
	if (OK != bwrite_ui8(
	(uint8_t *)&(tp_header->uc_pixsize), tp_bwrite )) {
		     _w_ui8err("uc_pixsize"); return NG; }
	if (OK != bwrite_ui8(
	(uint8_t *)&(tp_header->uc_imgdes), tp_bwrite )) {
		     _w_ui8err("uc_imgdes"); return NG; }

	return OK;
}

int tga_write_open( char *cp_fname, TGA_WRITE *tp_write )
{
	if (NULL == tp_write ) {
		pri_funct_err_bttvr(
			"Error : bad argument, tp_write is NULL." );
		return NG;
	}
	if (NULL == cp_fname ) {
		pri_funct_err_bttvr(
			"Error : bad argument, cp_fname is NULL." );
		return NG;
	}
	if (NULL != tp_write->t_bwrite._fp ) {
		pri_funct_err_bttvr(
		"Error : Already opened, at tga_write_open(-)." );
		return NG;
	}

	/* ファイルオープン */
	if (OK != bwrite_open( cp_fname, &(tp_write->t_bwrite) )) {
		pri_funct_err_bttvr(
	 "Error : bwrite_open(-) returns NG." );
		return NG;
	}

	/* ファイルをリトルインディアンで保存する */
	if (ptbl_cpu_is_little_endian()) {
		bwrite_set_byte_swap_sw( OFF, &(tp_write->t_bwrite) );
	} else {
		bwrite_set_byte_swap_sw( ON, &(tp_write->t_bwrite) );
	}

	/* へッダー情報を書き出す */
	if (OK != _tga_write_header(
		&(tp_write->t_tga_file_header),
		&(tp_write->t_bwrite) )
	) {
		pri_funct_err_bttvr(
	 "Error : _tga_write_header(-) returns NG." );
		return NG;
	}

	return OK;
}
