#include <stdio.h>
#include <stdlib.h> /* free() */
#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "pri.h"
#include "bwrite.h"

/*** バイナリ書き出しヘッダー初期化 ***/
void bwrite_init_head( BWRITE *tp_ )
{
	tp_->_fp = NULL;
	tp_->_i_byte_swap_sw = OFF;
}

/*** バイトスワップをしながら、あるいはせずに書くスイッチの設定 ***/
void bwrite_set_byte_swap_sw( int sw, BWRITE *tp_ )
{
	tp_->_i_byte_swap_sw = sw;
}
int bwrite_get_byte_swap_sw( BWRITE *tp_ )
{
	return tp_->_i_byte_swap_sw;
}

/*** ファイルを開く ***/
int bwrite_open( char *cp_fname, BWRITE *tp_ )
{
	if (NULL != tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : file<%s> already opened.", cp_fname);
		return NG;
	}

#if defined _WIN32
	char* path = ptbl_charcode_cp932_from_utf8(cp_fname);
	tp_->_fp = fopen( path ,"wb" );
	free(path);
#else
	tp_->_fp = fopen( cp_fname, "wb" );
#endif
	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : fopen(%s,r) returns NULL.", cp_fname );
		return NG;
	}
	return OK;
}

/*** ファイルを閉じる ***/
int bwrite_close( BWRITE *tp_ )
{
	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bwrite_close(-).");
		return NG;
	}

	if (fclose( tp_->_fp )) {
		/***pri_funct_err_bttvr(
			"Error : fclose(0x%x) returns not zero.",
			(unsigned int)(tp_->_fp) );***/
		pri_funct_err_bttvr(
			"Error : fclose(0x%p) returns not zero.",
			tp_->_fp );
		return NG;
	}

	bwrite_init_head( tp_ );

	return OK;
}

/*** 書き出し位置の移動 ***/
int bwrite_seek( BWRITE *tp_, long l_pos )
{
	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, at bwrite_seek(-).");
		return NG;
	}
	if (fseek(tp_->_fp, l_pos, SEEK_SET)) {
		pri_funct_err_bttvr(
		"Error : fseek(fp,po<%ld>,SEEK_SET) returns not zero.",
			l_pos);
		return NG;
	}
	return OK;
}

/*** 基本書き出し関数
     他の書き出し関数はすべてこの関数を使って書く ***/
static int _bwrite_byte( int i_cc, BWRITE *tp_ )
{
	int	i_;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at _bwrite_byte(-).");
		return EOF;
	}

	/*
		fputc()はintのデータを受け取り、unsigned charに
		キャストしstream(tp_->_fp)に書き込む。
		ISO 9899;1990(limits.h)では
			intは16ビット以上である
			charは8ビット以上である
		2004.06.24 wrote
	*/
	i_ = fputc( i_cc, tp_->_fp );
	if (EOF == i_) {
		/***pri_funct_err_bttvr(
			"Error : fputs(%d,0x%x) returns EOF.",
			i_cc, (unsigned int)(tp_->_fp) );***/
		pri_funct_err_bttvr(
			"Error : fputs(%d,0x%p) returns EOF.",
			i_cc, tp_->_fp );
		if (ferror(tp_->_fp)) {
			pri_funct_err_bttvr(
	"Error : ferror(-) returns not zero, at _bwrite_byte(-)." );
		}
		else {
		pri_funct_err_bttvr(
	"Error : but no error, not eof, at _bwrite_byte(-).");
		}
	}
	return i_;
}

/* 書き出し関数でのデータサイズの考え方
	ANSI Cでは
		charは1byteである
		1byteは何ビットが決まっていない
	ISO 9899;1990(limits.h)では
		charは8ビット以上である
		intは16ビット以上である
	でありcharの大きさは決まらない。
	が、バイナリーデータの大きさが決まらないでは済まないので、
	今までの習慣から(デファクトスタンダードとして)、
		charは8bitsである
	として、_bread_byte()が取ってきた数値は
	8bitsサイズとして扱うこととする
	2004.06.24 wrote
*/
/*** １バイト単位書き出し ***/
int bwrite_ui8( uint8_t *ui8p, BWRITE *tp_ )
{
	int	i_, i_1;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bwrite_ui8(-).");
		return NG;
	}

	i_1 = (int)(ui8p[0]);

	i_ = _bwrite_byte(i_1, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
			"Error : _bwrite_byte(-) returns EOF." );
		return NG;
	}

	return OK;
}

/*** ２バイト単位書き出し ***/
int bwrite_ui16( uint8_t *ui8p, BWRITE *tp_ )
{
	int	i_1, i_2, i_;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bwrite_ui16(-).");
		return NG;
	}

	if (ON == tp_->_i_byte_swap_sw) {	/* x86 */
		i_1 = (int)ui8p[1];
		i_2 = (int)ui8p[0];
	}
	else {					/* 68x */
		i_1 = (int)ui8p[0];
		i_2 = (int)ui8p[1];
	}

	i_ = _bwrite_byte(i_1, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
		"Error : _bwrite_byte(-)<1st call> returns EOF." );
		return NG;
	}
	i_ = _bwrite_byte(i_2, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
		"Error : _bwrite_byte(-)<2nd call> returns EOF." );
		return NG;
	}

	return OK;
}

/*** ４バイト単位書き出し ***/
int bwrite_ui32( uint8_t *ui8p, BWRITE *tp_ )
{
	int	i_1, i_2, i_3, i_4, i_;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bwrite_ui32(-).");
		return NG;
	}

	if (ON == tp_->_i_byte_swap_sw) {	/* x86 */
		i_1 = (int)ui8p[3];
		i_2 = (int)ui8p[2];
		i_3 = (int)ui8p[1];
		i_4 = (int)ui8p[0];
	}
	else {					/* 68x */
		i_1 = (int)ui8p[0];
		i_2 = (int)ui8p[1];
		i_3 = (int)ui8p[2];
		i_4 = (int)ui8p[3];
	}

	i_ = _bwrite_byte(i_1, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
		"Error : _bwrite_byte(-)<1st call> returns EOF." );
		return NG;
	}
	i_ = _bwrite_byte(i_2, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
		"Error : _bwrite_byte(-)<2nd call> returns EOF." );
		return NG;
	}
	i_ = _bwrite_byte(i_3, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
		"Error : _bwrite_byte(-)<3rd call> returns EOF." );
		return NG;
	}
	i_ = _bwrite_byte(i_4, tp_);
	if (EOF == i_) {
		pri_funct_err_bttvr(
		"Error : _bwrite_byte(-)<4th call> returns EOF." );
		return NG;
	}

	return OK;
}

/*** １バイト単位配列書き出し ***/
/* i32_incr is 1,2,3,... */
int bwrite_ui8array( int32_t i32_size, uint8_t *ui8p, int32_t i32_incr, BWRITE *tp_ )
{
	int32_t	ii;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, at bwrite_ui8array(-).");
		return NG;
	}
	if (i32_incr <= 0) {
		pri_funct_err_bttvr(
		"Error : bat argument i32_incr<%d>,", i32_incr);
		return NG;
	}

	for (ii = 0; ii < i32_size; ++ii) {
		if (OK != bwrite_ui8(ui8p, tp_)) {
			pri_funct_err_bttvr(
		"Error : bwrite_ui8(-)<%d/%d call> returns NG.",
				ii, i32_size );
			return NG;
		}
		ui8p += 1 * i32_incr;
	}

	return OK;
}

/*** ２バイト単位配列書き出し ***/
/* i32_incr is 1,2,3,... */
int bwrite_ui16array( int32_t i32_size, uint8_t *ui8p, int32_t i32_incr, BWRITE *tp_ )
{
	int32_t	ii;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, at bwrite_ui16array(-).");
		return NG;
	}
	if (i32_incr <= 0) {
		pri_funct_err_bttvr(
		"Error : bad argument i32_incr<%d>.", i32_incr);
		return NG;
	}

	for (ii = 0; ii < i32_size; ++ii) {
		if (OK != bwrite_ui16(ui8p, tp_)) {
		pri_funct_err_bttvr(
		"Error : bwrite_ui16(-)<%d/%d call> returns NG.",
				ii, i32_size );
			return NG;
		}
		ui8p += 2 * i32_incr;
	}

	return OK;
}

/*** ４バイト単位配列書き出し ***/
/* i32_incr is 1,2,3,... */
int bwrite_ui32array( int32_t i32_size, uint8_t *ui8p, int32_t i32_incr, BWRITE *tp_ )
{
	int32_t	ii;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, at bwrite_ui32array(-).");
		return NG;
	}
	if (i32_incr <= 0) {
		pri_funct_err_bttvr(
		"Error : bad argument i32_incr<%d>.", i32_incr);
		return NG;
	}

	for (ii = 0; ii < i32_size; ++ii) {
		if (OK != bwrite_ui32(ui8p, tp_)) {
		pri_funct_err_bttvr(
		"Error : bwrite_ui32(-)<%d/%d call> returns NG.",
				ii, i32_size );
			return NG;
		}
		ui8p += 4 * i32_incr;
	}

	return OK;
}

