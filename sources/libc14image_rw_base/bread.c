#include <stdio.h>
#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "pri.h"
#include "bread.h"

/*** バイナリ読み込みヘッダー初期化 ***/
void bread_init_head( BREAD *tp_ )
{
	tp_->_fp = NULL;
	tp_->_i_byte_swap_sw = OFF;
}

/*** バイトスワップをしながら、あるいはせずに読むスイッチの設定 ***/
void bread_set_byte_swap_sw( int sw, BREAD *tp_ )
{
	tp_->_i_byte_swap_sw = sw;
}
int bread_get_byte_swap_sw( BREAD *tp_ )
{
	return tp_->_i_byte_swap_sw;
}

/*** ファイルを開く ***/
int bread_open( char *cp_fname, BREAD *tp_ )
{
	if (NULL != tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : file<%s> already opened.", cp_fname);
		return NG;
	}

#if defined _WIN32
	tp_->_fp = fopen( ptbl_charcode_cp932_from_utf8(cp_fname) , "rb" );
#else
	tp_->_fp = fopen( cp_fname , "rb" );
#endif
	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : fopen(%s,r) returns NULL.", cp_fname );
		return NG;
	}
	return OK;
}

/*** ファイルを閉じる ***/
int bread_close( BREAD *tp_ )
{
	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bread_close(-).");
		return NG;
	}

	if (fclose( tp_->_fp )) {
		/***pri_funct_err_bttvr(
			"Error : fclose(0x%x) returns not zero.",
			(unsigned int)tp_->_fp );***/
		pri_funct_err_bttvr(
			"Error : fclose(0x%p) returns not zero.",
			tp_->_fp );
		return NG;
	}
	bread_init_head( tp_ );

	return OK;
}

/*** 読み込み位置の移動 ***/
int bread_seek( BREAD *tp_, long l_pos )
{
	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bread_seek(-).");
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

/*** 基本読み込み関数（他の読み込み関数はすべてこの関数を使って読む） ***/
static int _bread_byte( BREAD *tp_ )
{
	int	i_;

	if ((FILE *)NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at _bread_byte(-).");
		return EOF;
	}

	/*
		fgetc()はunsigned charとして読みintにキャストして返す
		ISO 9899;1990(limits.h)では
			charは8ビット以上である
			intは16ビット以上である
		2004.06.24 wrote
	*/
	i_ = fgetc( tp_->_fp );
	if (EOF == i_) {
		/* バイナリデータなのでEOFが帰ってくるのは問題である */
		/***pri_funct_err_bttvr(
			"Error : fgets(0x%x) returns EOF.",
			(unsigned int)(tp_->_fp) );***/
		pri_funct_err_bttvr(
			"Error : fgets(0x%p) returns EOF.",
			tp_->_fp );
		/* 読み込みエラーのとき */
		if (ferror(tp_->_fp)) {
			pri_funct_err_bttvr(
	"Error : ferror(-) returns not zero, at _bread_byte(-)." );
		}
		/* バイナリデータの場合、
		   ファイルエンドを越えて読んではいけない */
		else if (feof(tp_->_fp)) {
		pri_funct_err_bttvr(
		"Error : feof(-) returns not zero, at _bread_byte(-).");
		}
		/* エラーでも、ファイルエンドでもないのに
		   EOFが帰ってきた？！ */
		else {
			pri_funct_err_bttvr(
		"Error : but no error, not eof, at _bread_byte(-)" );
		}
	}
	return i_;
}

/* 読み込み関数でのデータサイズの考え方
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
/*** １バイト単位読み込み ***/
int bread_ui8( BREAD *tp_, uint8_t *ui8p )
{
	int	i_1;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bread_ui8(-).");
		return NG;
	}

	i_1 = _bread_byte( tp_ );
	if (EOF == i_1) {
		pri_funct_err_bttvr(
			"Error : _bread_byte() returns EOF.");
		return NG;
	}
	ui8p[0] = (uint8_t)i_1;

	return OK;
}

/*** ２バイト単位読み込み ***/
int bread_ui16( BREAD *tp_, uint8_t *ui8p )
{
	int	i_1, i_2;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bread_ui16(-).");
		return NG;
	}

	i_1 = _bread_byte( tp_ );
	if (EOF == i_1) {
		pri_funct_err_bttvr(
			"Error : _bread_byte()<1st call> returns EOF.");
		return NG;
	}
	i_2 = _bread_byte( tp_ );
	if (EOF == i_2) {
		pri_funct_err_bttvr(
			"Error : _bread_byte()<2nd call> returns EOF.");
		return NG;
	}

	if (ON == tp_->_i_byte_swap_sw) {	/* x86 */
		ui8p[0] = (uint8_t)i_2;
		ui8p[1] = (uint8_t)i_1;
	}
	else {					/* 68x */
		ui8p[0] = (uint8_t)i_1;
		ui8p[1] = (uint8_t)i_2;
	}

	return OK;
}

/*** ４バイト単位読み込み ***/
int bread_ui32( BREAD *tp_, uint8_t *ui8p )
{
	int	i_1, i_2, i_3, i_4;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
			"Error : Not fopen yet, at bread_ui32(-).");
		return NG;
	}

	i_1 = _bread_byte( tp_ );
	if (EOF == i_1) {
		pri_funct_err_bttvr(
			"Error : _bread_byte()<1st call> returns EOF.");
		return NG;
	}
	i_2 = _bread_byte( tp_ );
	if (EOF == i_2) {
		pri_funct_err_bttvr(
			"Error : _bread_byte()<2nd call> returns EOF.");
		return NG;
	}
	i_3 = _bread_byte( tp_ );
	if (EOF == i_3) {
		pri_funct_err_bttvr(
			"Error : _bread_byte()<3rd call> returns EOF.");
		return NG;
	}
	i_4 = _bread_byte( tp_ );
	if (EOF == i_4) {
		pri_funct_err_bttvr(
			"Error : _bread_byte()<4th call> returns EOF.");
		return NG;
	}

	if (ON == tp_->_i_byte_swap_sw) {	/* x86 */
		ui8p[0] = (uint8_t)i_4;
		ui8p[1] = (uint8_t)i_3;
		ui8p[2] = (uint8_t)i_2;
		ui8p[3] = (uint8_t)i_1;
	}
	else {					/* 68x */
		ui8p[0] = (uint8_t)i_1;
		ui8p[1] = (uint8_t)i_2;
		ui8p[2] = (uint8_t)i_3;
		ui8p[3] = (uint8_t)i_4;
	}

	return OK;
}

/*** １バイト単位配列読み込み ***/
/* i32_incr is 1,2,3,... */
int bread_ui8array( BREAD *tp_, int32_t i32_size, uint8_t *ui8p, int32_t i32_incr )
{
	int32_t ii;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, at bread_ui8array(-).");
		return NG;
	}
	if (i32_incr <= 0) {
		pri_funct_err_bttvr(
			"Error : bad argument i32_incr<%d>.", i32_incr);
		return NG;
	}

	for (ii = 0; ii < i32_size; ++ii) {
		if (OK != bread_ui8( tp_, ui8p )) {
			pri_funct_err_bttvr(
		"Error : bread_ui8(-)<%d/%d call> returns NG.",
				ii, i32_size );
			return NG;
		}
		ui8p += 1 * i32_incr;
	}

	return OK;
}

/*** ２バイト単位配列読み込み ***/
/* i32_incr is 1,2,3,... */
int bread_ui16array( BREAD *tp_, int32_t i32_size, uint8_t *ui8p, int32_t i32_incr )
{
	int32_t ii;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, at bread_ui16array(-).");
		return NG;
	}
	if (i32_incr <= 0) {
		pri_funct_err_bttvr(
		"Error : bad argument i32_incr<%d>.", i32_incr);
		return NG;
	}

	for (ii = 0L; ii < i32_size; ++ii) {
		if (OK != bread_ui16( tp_, ui8p )) {
		pri_funct_err_bttvr(
		"Error : bread_ui16(-)<%d/%d call> returns NG.",
				ii,i32_size );
			return NG;
		}
		ui8p += 2 * i32_incr;
	}

	return OK;
}

/*** ４バイト単位配列読み込み ***/
/* i32_incr is 1,2,3,... */
int bread_ui32array( BREAD *tp_, int32_t i32_size, uint8_t *ui8p, int32_t i32_incr )
{
	int32_t ii;

	if (NULL == tp_->_fp) {
		pri_funct_err_bttvr(
		"Error : Not fopen yet, bread_ui32array(-).");
		return NG;
	}
	if (i32_incr <= 0) {
		pri_funct_err_bttvr(
		"Error : bad argument i32_incr<%d>.", i32_incr);
		return NG;
	}

	for (ii = 0L; ii < i32_size; ++ii) {
		if (OK != bread_ui32( tp_, ui8p )) {
		pri_funct_err_bttvr(
		"Error : bread_ui32(-)<%d/%d call> returns NG.",
				ii, i32_size );
			return NG;
		}
		ui8p += 4 * i32_incr;
	}

	return OK;
}

