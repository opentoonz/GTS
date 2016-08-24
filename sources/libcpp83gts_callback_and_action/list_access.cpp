#include <stdio.h>	/* NULL */
#include <string.h>
#include <stdlib.h>	/* atoi() */

#include "ptbl_returncode.h"
#include "pri.h"

#include "list_access.h"

#include "gts_gui.h"

namespace {
 bool check_next_selected_( int list_num )
 {
	for (;list_num<=cl_gts_gui.selbro_fnum_list->size() ;++list_num) {
		if (cl_gts_gui.selbro_fnum_list->selected(list_num)) {
			return true;
		}
	}
	return false;
 }
}

/* リストを指定番号からサーチし、
次の選択されたリストの番号(1...)を得る
ない場合は-1を返す */
int list_access::_next_selected( int list_num )
{
	for (;list_num<=cl_gts_gui.selbro_fnum_list->size() ;++list_num) {
		if (cl_gts_gui.selbro_fnum_list->selected(list_num)) {
			/* EndressスイッチがON、かつ最後の選択だった */
			if (this->endress_sw_ == true
			&& !check_next_selected_(list_num+1)) {
				/* 最後の番号に+1の番号を得る */
				char numarray[8];
				(void)sprintf( numarray, "%04d"
	,atoi( cl_gts_gui.selbro_fnum_list->text(
		cl_gts_gui.selbro_fnum_list->size()
	) ) +1
				);
				/* listに追加して */
				cl_gts_gui.selbro_fnum_list->add(numarray);
				/* 選択状態にする */
				cl_gts_gui.selbro_fnum_list->select(
				 cl_gts_gui.selbro_fnum_list->size()
				);
			}
			return list_num;
		}
	}
	return -1;
}
int list_access::set_first_number( void )
{
	const char *cp_tmp;

	/* 01 選択されたフレームの先頭の順番を得る */
	this->_i_crnt_list_num = this->_next_selected( 1 );

	/* 02 選択されていないならゼロを返す */
	if (this->_i_crnt_list_num < 1) {
		pri_funct_err_bttvr(
			"Error : this->_next_selected(1) returns <%d>",
			this->_i_crnt_list_num );
		return 0;
	}

	/* 03 先頭の順番から、フレーム番号名を得る */
	cp_tmp = cl_gts_gui.selbro_fnum_list->text(
			this->_i_crnt_list_num);

	/* 04 選択されているのにフレーム番号名がない --> エラー */
	if (NULL == cp_tmp) {
		pri_funct_err_bttvr(
	"Error : cl_gts_gui.selbro_fnum_list->text(%d) returns NULL",
			this->_i_crnt_list_num
		);
		return -1;/* エラーリターンはマイナスの値 */
	}

	/* 05 フレーム番号名からフレーム番号を得る */
	this->_i_crnt_file_num = atoi(cp_tmp);

	/* 06 次の番号は未定 */
	this->_i_next_list_num = -1;
	this->_i_next_file_num = -1;

	/* 07 選択されたフレームの先頭の順番(1以上の値)を返す */
	return this->_i_crnt_list_num;
}
/*
エラー時のリカバリー用
int list_access::set_next_number( void )
と対で使うこと
this->_i_next_list_numとthis->_i_next_file_numを初期化する
*/
void list_access::reset_next_number( void )
{
	this->_i_next_list_num = -1;
	this->_i_next_file_num = -1;
}
/* this->_i_next_list_numとthis->_i_next_file_numを設定する */
int list_access::set_next_number( void )
{
	char *cp_tmp;

	/* 01 選択されたフレームの次の順番を得る */
	this->_i_next_list_num = this->_next_selected(
	 this->_i_crnt_list_num + 1 );

	/* 02 次がなければ(無効)次のフレーム番号を無効にしてこのmethod終 */
	if (this->_i_next_list_num < 1) {
	    this->_i_next_file_num = -1;
		return OK;
	}

	/* 03 次の順番から、フレーム番号名を得る */
	cp_tmp = (char *)cl_gts_gui.selbro_fnum_list->text(
		this->_i_next_list_num);

	/* 04 選択されているのにフレーム番号名がない --> エラー */
	if (NULL == cp_tmp) {
		pri_funct_err_bttvr(
	"Error : cl_gts_gui.selbro_fnum_list->text(%d) returns NULL",
		this->_i_next_list_num
		);
		return NG;
	}

	/* 05 フレーム番号名からフレーム番号を得る */
	this->_i_next_file_num = atoi( cp_tmp );

	return OK;
}

/*
次スキャンしようとしたらエラーの時のリカバリー用
void list_access::set_next_to_crnt_number( void )
と対で使うこと
*/
void list_access::reset_next_to_crnt_number( void )
{
	this->_i_crnt_list_num = this->crnt_list_num_for_reset_;
	this->_i_crnt_file_num = this->crnt_file_num_for_reset_;
}
/* 次のフレームを処理するとき呼ぶ */
void list_access::set_next_to_crnt_number( void )
{
	this->crnt_list_num_for_reset_ = this->_i_crnt_list_num;
	this->crnt_file_num_for_reset_ = this->_i_crnt_file_num;
	this->_i_crnt_list_num = this->_i_next_list_num;
	this->_i_crnt_file_num = this->_i_next_file_num;
	this->_i_next_list_num = -1;
	this->_i_next_file_num = -1;
}

/* "0000"--> "0000 S" , "0000 T" --> "0000 ST" */
int list_access::marking_src( int i_num )
{
	char *cp_tmp, ca8_tmp[8];

	cp_tmp = (char *)cl_gts_gui.selbro_fnum_list->text(i_num);
	if (NULL == cp_tmp) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_gui.selbro_fnum_list->text(%d) returns NULL",
		i_num
		);
		return NG;
	}

	if (4 == strlen(cp_tmp)) {
		/* "0001"のとき */
		(void)strcpy( ca8_tmp, cp_tmp );
		(void)strcat( ca8_tmp, " S" );
		cl_gts_gui.selbro_fnum_list->text(i_num, ca8_tmp);
	} else
	/* "0001 S" or "0001 T" */
	if (6 == strlen(cp_tmp)) {
		if ('T' == cp_tmp[5]) {
			/* "0001 T"のとき */
			(void)strcpy( ca8_tmp, cp_tmp );
			ca8_tmp[5] = 'S';
			ca8_tmp[6] = 'T';
			ca8_tmp[7] = '\0';
			cl_gts_gui.selbro_fnum_list->text(i_num, ca8_tmp);
		}
		/* "0001 S"ではなにもしない */
	}
	/* "0001 ST"ではなにもしない */

	return OK;
}
/* "0000"--> "0000 T" , "0000 S" --> "0000 ST" */
int list_access::marking_tgt( int i_num )
{
	char *cp_tmp, ca8_tmp[8];

	cp_tmp = (char *)cl_gts_gui.selbro_fnum_list->text(i_num);
	if (NULL == cp_tmp) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_gui.selbro_fnum_list->text(%d) returns NULL",
		i_num
		);
		return NG;
	}

	if (4 == strlen(cp_tmp)) {
		/* "0001"のとき */
		(void)strcpy( ca8_tmp, cp_tmp );
		(void)strcat( ca8_tmp, " T" );
		cl_gts_gui.selbro_fnum_list->text(i_num, ca8_tmp);
	} else
	/* "0001 S" or "0001 T" */
	if (6 == strlen(cp_tmp)) {
		if ('S' == cp_tmp[5]) {
			/* "0001 S"のとき */
			(void)strcpy( ca8_tmp, cp_tmp );
			ca8_tmp[5] = 'S';
			ca8_tmp[6] = 'T';
			ca8_tmp[7] = '\0';
			cl_gts_gui.selbro_fnum_list->text(i_num, ca8_tmp);
		}
		/* "0001 T"ではなにもしない */
	}
	/* "0001 ST"ではなにもしない */

	return OK;
}

void list_access::unselect( int i_num )
{
	cl_gts_gui.selbro_fnum_list->select(i_num, 0);
}

void list_access::remove_all( void )
{
	/* すべて削除 */
	while (0 < cl_gts_gui.selbro_fnum_list->size()) { 
	   	cl_gts_gui.selbro_fnum_list->remove(1);
	}
}
void list_access::select_all( void )
{
	int	ii;

	/* 全て選択状態にする */
	for (ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		cl_gts_gui.selbro_fnum_list->select(ii);
	}
}
