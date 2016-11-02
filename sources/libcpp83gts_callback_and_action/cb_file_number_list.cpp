#include <cstdlib>	// atoi()
#include <cctype>	// isdigit()
#include <cassert>	// assert()
#include <cstring>
//#include "ptbl_returncode.h"
//#include "pri.h"
#include "ptbl_funct.h"
#include "cb_file_number_list.h"
#include "gts_gui.h"
#include "gts_master.h"

namespace {
 const char *next_num_( const char* str ,int* rsz ,int* file_num )
 {
	int	ii = 0 ,jj = 0;
	char	buffer[1024];

	assert( nullptr != str );
	assert( nullptr != rsz );	/* remainssize */
	assert( nullptr != file_num );

	if ( (*rsz) <= 0 ) {
		return nullptr;
	}

	/* 10進数字('0'〜'9')の文字位置(ii)を探す */
	for ( ;'\0' != str[ii] && 0 < (*rsz) ;++ii ,--(*rsz)) {
		if (isdigit(str[ii])) { break; }
	}

	/* 続いて、10進数字('0'〜'9')以外の文字位置(ii)を探す
	   かつ、10進数字('0'〜'9')の文字を抜出す */
	for ( ;'\0' != str[ii] && 0 < (*rsz) ;++ii ,--(*rsz)) {
		if (!isdigit(str[ii])) { break; }
		buffer[jj++] = str[ii];
	}

	/* 数値を得る */
	if ( 0 < jj ) {
		buffer[jj] = '\0';
		*file_num = atoi( buffer );
	}

	/* 続けて、次の10進数字('0'〜'9')の文字位置(ii)を探す */
	for ( ;'\0' != str[ii] && 0 < (*rsz) ;++ii ,--(*rsz)) {
		if (isdigit(str[ii])) {
			return &str[ii]; /* 数値位置発見 */
		}
	}

	/* 現位置で数値を得たが、次の数値文字がない場合 */
	if ( 0 < jj ) {
		return &str[ii-1];
		/* 最後の数値位置(nullptr以外を返すための無意味な値) */
	}

	/* 次の10進数字('0'〜'9')の文字位置(ii)はない */
	return nullptr;
 }
}

void cb_file_number_list::set_list_from_string( void )
{
	const char* str;/* 複数数値含文字列の数値始まり位置へのpointer */
	int	rsz;	/* 残り文字数(Remain SiZe) */
	int	file_num;
	int	ii ,jj;
	char	ca8_tmp[8];

	/* "1" ,"0001" ,"1 2 3" ,"0001 0002 0003" ,etc. */
	str = cl_gts_gui.norinp_fnum_insert->value();
	rsz = cl_gts_gui.norinp_fnum_insert->size();

	while (nullptr != (str = next_num_( str ,&rsz ,&file_num ))) {
		/* file number listから、insertする
		(file_numと同じかより大きいfile(jj)の)位置(ii)を得る */
		for (ii=1; ii<=cl_gts_gui.selbro_fnum_list->size(); ++ii) {
			jj = atoi( cl_gts_gui.selbro_fnum_list->text(ii) );
			if (file_num <= jj) { break; }
		}
		/* すでにあるフレームは飛ばして次へ */
		if (jj == file_num) { continue; }
		/* insert&Scroll for viewing */
		sprintf( ca8_tmp ,"%04d" ,file_num );
		cl_gts_gui.selbro_fnum_list->insert( ii ,ca8_tmp );
		cl_gts_gui.selbro_fnum_list->middleline( ii );
	}
}

//------------------------------------------------------------

namespace {
 /* ファイルのヘッダー情報を得る */
 int set_file_header_info_( const char *cp_file, iip_read *clp_read )
 {
	assert(nullptr != cp_file);
	assert(nullptr != clp_read);

	/* ファイルが存在しなければ、なにもせず、OKで終る */
	if (!ptbl_dir_or_file_is_exist(const_cast<char*>(cp_file))) {
		return OK;
	}

	/* ファイル名をセットして... */
	if (OK != clp_read->cl_name.set_name(const_cast<char*>(cp_file))) {
		pri_funct_err_bttvr(
 	 "Error : clp_read->cl_name.set_name(%s) returns NG",
			cp_file);
		return NG;
	}
	/* ファイルヘッダー情報を得る */
	if (OK != clp_read->header()) {
		pri_funct_err_bttvr(
 	 "Error : clp_read->header() returns NG");
		return NG;
	}
	return OK;
 }

 /* ファイルの存在マークを文字列で返す
	マークは、"0001 ST"の、ST部分
	画像の種類毎に扱いが違う
	rgbのとき
		S -> Scanファイル("A_full.0001.tif"等)
		T -> Traceファイル("A.0001.tif"等)
	grayscaleのとき
		S -> scanファイル("A.0001.tif")
		T -> 存在しない
	BWのとき
		S -> scanファイル("A.0001.tif")
		T -> 存在しない
 */
 const char* get_mark_str_by_checking_file_( const int file_num )
 {
	iip_read	cl_read_target,
			cl_read_rgbscan;
	const char* cp_path;
	const char	*cp_s = "S",
			*cp_t = "T",
			*cp_st = "ST";

	/* 画像のファイルパスを得る */
	cp_path = cl_gts_master.cl_bro_level.cp_filepath(file_num);
	if (nullptr == cp_path) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.cp_filepath(%d) returns nullptr."
			, file_num );
		return nullptr;
	}

	/* 画像ファイルの情報を取る */
	if (OK != set_file_header_info_(cp_path, &cl_read_target )) {
		pri_funct_err_bttvr(
 	 "Error : set_file_header_info_(%s,) returns NG",
			cp_path);
		return nullptr;
	}

	/* ファイルヘッドに_fullを付加した画像ファイルパスを得る */
	cp_path = cl_gts_master.cl_bro_level.cp_filepath_full(file_num);
	if (nullptr == cp_path) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_master.cl_bro_level.cp_filepath_full(%d) returns nullptr."
	 		, file_num );
		return nullptr;
	}
	/* ファイルヘッドに_fullを付加した画像ファイルの情報を取る */
	if (OK != set_file_header_info_(cp_path, &cl_read_rgbscan )) {
		pri_funct_err_bttvr(
 	 "Error : set_file_header_info_(%s,) returns NG",
			cp_path);
		return nullptr;
	}

	/* モノクロ２値画像 */
	if (E_CH_NUM_BITBW ==
	cl_read_target.cl_ch_info.get_e_ch_num_type()) { return cp_s; }

	/* GrayScale画像 */
	else if (1L == cl_read_target.get_l_channels()) { return cp_s; }

	/* RGB Scan and Trace画像 */
	else if ((3L <= cl_read_target.get_l_channels()) &&
		 (3L <= cl_read_rgbscan.get_l_channels())) {return cp_st;}
	/* RGB Scan画像 */
	else if (3L <= cl_read_rgbscan.get_l_channels()) { return cp_s; }
	/* RGB Trace画像 */
	else if (3L <= cl_read_target.get_l_channels()) { return cp_t; }

	/* ファイルがない */
	else if ((0L == cl_read_target.get_l_channels()) &&
		 (0L == cl_read_rgbscan.get_l_channels())) {return nullptr;}

	pri_funct_err_bttvr( "Error : bad file type" );
	return nullptr;
 }
}

/* ファイル存在マークを付加したファイル番号をlistの最後に追加 */
void cb_file_number_list::append_fnum_list_with_chk_mark( const int file_num )
{
	char buffer[8];
	const char *mark_str;

	(void)sprintf(buffer, "%04d", file_num );

	mark_str = get_mark_str_by_checking_file_(file_num);
	/* ファイルチェックでエラーが起きたとしても実行を続ける */
	if ( mark_str != nullptr ) {
		(void)strcat( buffer ," " );
		(void)strcat( buffer ,mark_str );
	}

	cl_gts_gui.selbro_fnum_list->insert(
		cl_gts_gui.selbro_fnum_list->size()+1,
		buffer
	);
}

/* 指定範囲の番号でlistを追加生成する(ファイル存在マーク付き) */
void cb_file_number_list::make_fnum_list_with_chk_mark( const int start_num, const int end_num )
{
	int	ii;
	/* ファイルの存在をチェックしながらリストを設定 */
	for (ii = start_num; ii <= end_num; ++ii) { 
		this->append_fnum_list_with_chk_mark( ii );
	}
}

//------------------------------------------------------------

/* 全て選択状態にする */
void cb_file_number_list::select_all( void )
{
	for (int ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		cl_gts_gui.selbro_fnum_list->select(ii);
	}
}

/* 選択に関わらずすべて削除 */
void cb_file_number_list::remove_all( void )
{
	// GUI Scroll
	cl_gts_gui.selbro_fnum_list->topline(0);

	// delete all list
	while (0 < cl_gts_gui.selbro_fnum_list->size()) { 
	   	cl_gts_gui.selbro_fnum_list->remove(1);
	}
}

/* 選択状態の項目をすべて削除 */
void cb_file_number_list::remove_selected( void )
{
	for (int ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size();) {
		if ( cl_gts_gui.selbro_fnum_list->selected(ii) ) {
			cl_gts_gui.selbro_fnum_list->remove(ii);
		} else { ++ii; }
	}
}

/* 選択状態を外す */
void cb_file_number_list::unselect( int list_num )
{
	cl_gts_gui.selbro_fnum_list->select(list_num, 0);
}

/* Scan image fileの存在Mark付加
	"0000"--> "0000 S" , "0000 T" --> "0000 ST" */
int cb_file_number_list::marking_scan_file( int list_num )
{
	const char *list_text;
	char buffer[8];

	list_text = cl_gts_gui.selbro_fnum_list->text(list_num);
	if (nullptr == list_text) {
		pri_funct_err_bttvr(
	"Error : cl_gts_gui.selbro_fnum_list->text(%d) returns nullptr"
			, list_num
		);
		return NG;
	}

	if (4 == strlen(list_text)) {
		/* "0001"のとき"0001 S"に変更する */
		(void)strcpy( buffer, list_text );
		(void)strcat( buffer, " S" );
		cl_gts_gui.selbro_fnum_list->text(list_num, buffer);
	} else
	/* "0001 S" or "0001 T" */
	if (6 == strlen(list_text)) {
		if ('T' == list_text[5]) {
			/* "0001 T"のとき"0001 ST"に変更する */
			(void)strcpy( buffer, list_text );
			buffer[5] = 'S';
			buffer[6] = 'T';
			buffer[7] = '\0';
			cl_gts_gui.selbro_fnum_list->text(list_num, buffer);
		}
		/* "0001 S"ではなにもしない */
	}
	/* "0001 ST"ではなにもしない */

	return OK;
}

/* Trace image fileの存在Mark付加
	"0000"--> "0000 T" , "0000 S" --> "0000 ST" */
int cb_file_number_list::marking_trace_file( int list_num )
{
	const char *list_text;
	char buffer[8];

	list_text = cl_gts_gui.selbro_fnum_list->text(list_num);
	if (nullptr == list_text) {
		pri_funct_err_bttvr(
	 "Error : cl_gts_gui.selbro_fnum_list->text(%d) returns nullptr"
			, list_num
		);
		return NG;
	}

	if (4 == strlen(list_text)) {
		/* "0001"のとき"0001 T"に変更する */
		(void)strcpy( buffer, list_text );
		(void)strcat( buffer, " T" );
		cl_gts_gui.selbro_fnum_list->text(list_num, buffer);
	} else
	/* "0001 S" or "0001 T" */
	if (6 == strlen(list_text)) {
		if ('S' == list_text[5]) {
			/* "0001 S"のとき"0001 ST"に変更する */
			(void)strcpy( buffer, list_text );
			buffer[5] = 'S';
			buffer[6] = 'T';
			buffer[7] = '\0';
			cl_gts_gui.selbro_fnum_list->text(list_num, buffer);
		}
		/* "0001 T"ではなにもしない */
	}
	/* "0001 ST"ではなにもしない */

	return OK;
}

//------------------------------------------------------------
#if 0
/* 1 初期化 */
void cb_file_number_list::number_init( void )
{
	/* 位置をすべて-1にセット */
	this->crnt_list_num_ = -1;
	this->crnt_file_num_ = -1;
	this->next_list_num_ = -1;
	this->next_file_num_ = -1;
}

namespace {
 int next_selected_( int list_num )
 {
	for (;list_num <= cl_gts_gui.selbro_fnum_list->size() ;++list_num) {
		if (cl_gts_gui.selbro_fnum_list->selected(list_num)) {
			return return list_num;
		}
	}
	return -1;
 }
 int prev_selected_( int list_num )
 {
	for (;1 <= list_num ;--list_num) {
		if (cl_gts_gui.selbro_fnum_list->selected(list_num)) {
			return return list_num;
		}
	}
	return -1;
 }
 int search_list_from_file_num_( const int file_num )
 {
	int ii;
	int jj;
	for (ii=1 ;ii <= cl_gts_gui.selbro_fnum_list->size() ;++ii) {
		jj = atoi( cl_gts_gui.selbro_fnum_list->text( ii ) );
		if (file_num == jj) { return ii; }
	}
	return -1;
 }
}
/* 2 現位置を得る */
void cb_file_number_list::number_set( void )
{
	/* End指定
	--> GUIのlistの選択をたどる
	--> GUIのlistに対しては参照のみ
	--> マークと選択解除は外で
	*/
	if ( cl_gts_gui.choice_level_continue_type->value() == 0 ) {
	/* a 現位置が初期化状態(-1)なら、現位置を初期位置にする */
		if (this->crnt_list_num_ < 1) {
			if (
				cl_gts_gui.valinp_level_start->value()
				<= cl_gts_gui.valinp_level_end->value()
			) {
				/* 順送り(start <= end)の初期位置 */
				this->crnt_list_num_= next_selected_(1);
			}
			else {
				/* 逆送り(start > end)の初期位置 */
				this->crnt_list_num_= prev_selected_(
					cl_gts_gui.selbro_fnum_list->size()
				);
			}
			if (this->crnt_list_num_ < 1) { /* 選択がない */
				this->crnt_file_num_ = -1;
			}
			else { /* 選択項目の表示番号を得る */
				this->crnt_file_num_ = atoi( 
					cl_gts_gui.selbro_fnum_list->text(
				this->crnt_list_num_
					)
				);
			}
		}
	/* b 現位置が初期化状態(-1)でなければ、現位置を次位置に置換える */
		else {
			this->crnt_list_num_ = this->next_list_num_;
			this->crnt_file_num_ = this->next_file_num_;
		}
	/* c 次番号を得る(次処理があるか判断のためここで取る) */
	/* d 次位置がなければ-1をセット */
		if (1 <= this->crnt_list_num_) {/* 現位置がなければ次ない */
			if (
				cl_gts_gui.valinp_level_start->value()
				<= cl_gts_gui.valinp_level_end->value()
			) {
				/* 順送り(start <= end)の次位置 */
				this->next_list_num_= next_selected_(
					this->crnt_list_num_ + 1
				);
			}
			else {
				/* 逆送り(start > end)の次位置 */
				this->next_list_num_= prev_selected_(
					this->crnt_list_num_ - 1
				);
			}
			if (this->next_list_num_ < 1) { /* 次選択がない */
				this->next_file_num_ = -1;
			}
			else { /* 次選択項目の表示番号を得る */
				this->next_file_num_ = atoi( 
					cl_gts_gui.selbro_fnum_list->text(
				this->next_list_num_
					)
				);
			}
		}
	}
	/* Endless指定
	--> GUIのlistの選択は無視
	--> LevelのStart番号から始まる
	--> GUIのlist項目(になければ追加して)選択状態にする(処理開始準備)
	--> マークと選択解除は外で
	*/
	else {
	/* a 現位置が初期化状態(-1)なら、現位置を初期位置(Start)にする */
		if (this->crnt_list_num_ < 1) {
			/* Start番号を現位置とする */
			this->crnt_file_num_ = 
				cl_gts_gui.valinp_level_start->value();
			/* Start番号に一致するlist番号あれば現位置とする */
			this->crnt_list_num_ = search_list_from_file_num_(
			 this->crnt_file_num_
			);
		}

	/* b 現位置が初期化状態(-1)でなければ、現位置を次位置に置換える */
		else {
			this->crnt_list_num_ = this->next_list_num_;
			this->crnt_file_num_ = this->next_file_num_;
		}

	/* c 一致する現位置(がなければGUI listに追加してそれ)を(再)設定 */
		this->crnt_list_num_ = insert_and_select_fnum_in_list_(
			this->crnt_file_num_
		);

	/* d 既存でも新規追加でも、選択状態にする */
		if (1 <= this->crnt_list_num_) {
			cl_gts_gui.selbro_fnum_list->select(
				this->crnt_list_num_
			);
		}

	/* e 次番号を得る(次処理があるか判断のためここで取る) */
		if (cl_gts_gui.choice_level_endless_direction->value() == 0)
		{
			this->next_list_num_ = this->crnt_list_num_ + 1;
			this->next_file_num_ = this->crnt_file_num_ + 1;
		}
		if (cl_gts_gui.choice_level_endless_direction->value() == 1)
		{
			this->next_list_num_ = this->crnt_list_num_ - 1;
			this->next_file_num_ = this->crnt_file_num_ - 1;
		}

	/* f 次位置が1...9999外であれば-1をセット */
		if (this->next_list_num_ < 1 || this->next_file_num_ < 1) {
				this->next_list_num_ = -1;
				this->next_file_num_ = -1;
		}
		if (9999<this->next_list_num_ || 9999<this->next_file_num_) {
				this->next_list_num_ = -1;
				this->next_file_num_ = -1;
		}
	}
}
#endif

namespace {
 int next_selected_( int list_num )
 {
	for (;list_num <= cl_gts_gui.selbro_fnum_list->size() ;++list_num) {
		if (cl_gts_gui.selbro_fnum_list->selected(list_num)) {
			return list_num;
		}
	}
	return -1;
 }
 int prev_selected_( int list_num )
 {
	for (;1 <= list_num ;--list_num) {
		if (cl_gts_gui.selbro_fnum_list->selected(list_num)) {
			return list_num;
		}
	}
	return -1;
 }
 /* 全て選択解除にする */
 void unselect_all_( void )
 {
	for (int ii = 1; ii <= cl_gts_gui.selbro_fnum_list->size(); ++ii) {
		cl_gts_gui.selbro_fnum_list->select(ii ,0);
	}
 }
 /* listの順位置に挿入し、選択状態にして、既にあるならその位置を返す */
 int insert_and_select_fnum_in_list_( const int file_num )
 {
	int ii,jj;
	char buffer[8];

	/* size + 1までループして最後でも追加するようにする */
	for (ii= 1 ;ii <= cl_gts_gui.selbro_fnum_list->size() ;++ii) {
		jj = atoi( cl_gts_gui.selbro_fnum_list->text(ii) );
		if (file_num == jj) {/* 既にあるなら何もしないで... */
			cl_gts_gui.selbro_fnum_list->select( ii );/* 選択 */
			return ii;
		}
		if (file_num < jj) { /* listの順位置に挿入 */
			(void)sprintf(buffer, "%04d", file_num );
			cl_gts_gui.selbro_fnum_list->insert( ii ,buffer );
			cl_gts_gui.selbro_fnum_list->select( ii );/* 選択 */
			return ii;
		}
	}
	/* listの最後に追加 */
	(void)sprintf(buffer, "%04d", file_num );
	cl_gts_gui.selbro_fnum_list->add( buffer );
	cl_gts_gui.selbro_fnum_list->select(
	 cl_gts_gui.selbro_fnum_list->size()
	);/* 選択 */
	return ii;
 }
}

/* 現位置と現番号から次の処理位置と処理番号を得る */
void cb_file_number_list::set_next_num_from_crnt_( const int continue_type_value )
{
	/* 現位置がなければ次もない */
	if (this->crnt_list_num_ < 1 || this->crnt_file_num_ < 1) {
		this->next_list_num_ = -1;
		this->next_file_num_ = -1;
		return;
	}
	if ( continue_type_value == this->end_type_value_ ) {
		/* End指定 */
		if (
			cl_gts_gui.valinp_level_start->value()
			<= cl_gts_gui.valinp_level_end->value()
		) {
			/* 順送り(start <= end)の次選択位置 */
			this->next_list_num_= next_selected_(
				this->crnt_list_num_ + 1
			);
		}
		else {
			/* 逆送り(start > end)の次選択位置 */
			this->next_list_num_= prev_selected_(
				this->crnt_list_num_ - 1
			);
		}
		if (this->next_list_num_ < 1) { /* 選択がないなら-1 */
			this->next_file_num_ = -1;
		}
		else { /* 選択あったら、その項目の表示番号を得る */
			this->next_file_num_ = atoi( 
				cl_gts_gui.selbro_fnum_list->text(
					this->next_list_num_
				)
			);
		}
	}
	else	/* Endless指定 */
	if ( continue_type_value == this->endless_type_value_ ) {

		if (cl_gts_gui.choice_level_endless_direction->value() == 0)
		{
			this->next_list_num_ = this->crnt_list_num_ + 1;
			this->next_file_num_ = this->crnt_file_num_ + 1;
		}
		if (cl_gts_gui.choice_level_endless_direction->value() == 1)
		{
			this->next_list_num_ = this->crnt_list_num_;
			this->next_file_num_ = this->crnt_file_num_ - 1;
		}

		/* 次位置が1...9999外であれば-1 */
		if (this->next_list_num_ < 1 || this->next_file_num_ < 1) {
			this->next_list_num_ = -1;
			this->next_file_num_ = -1;
		}
		if (9999<this->next_list_num_|| 9999<this->next_file_num_) {
			this->next_list_num_ = -1;
			this->next_file_num_ = -1;
		}
	}
}

/* 初期化 */
void cb_file_number_list::counter_start( const int continue_type_value )
{
	if ( continue_type_value == this->end_type_value_ ) {
		/* End指定 */

		/* GUIのfile number listの選択をたどる */
		/* 処理後のマーキングと選択解除は外で行う */

		if (
			cl_gts_gui.valinp_level_start->value()
			<= cl_gts_gui.valinp_level_end->value()
		) {
			/* 順送り(start <= end)の初期位置 */
			this->crnt_list_num_= next_selected_(1);
		}
		else {
			/* 逆送り(start > end)の初期位置 */
			this->crnt_list_num_= prev_selected_(
				cl_gts_gui.selbro_fnum_list->size()
			);
		}
		if (this->crnt_list_num_ < 1) { /* listに選択がない */
			this->crnt_file_num_ = -1;
		}
		else { /* 選択があるなら、項目の表示番号を得る */
			this->crnt_file_num_ = atoi( 
				cl_gts_gui.selbro_fnum_list->text(
					this->crnt_list_num_
				)
			);
		}
	}
	else /* Endless指定 */
	if ( continue_type_value == this->endless_type_value_ ) {
		/* GUIのlistの選択は無視 */
		/* 処理後のマーキングと選択解除は外で行う */

		/* LevelのStart番号から始まる */
		this->crnt_file_num_ = 
		 static_cast<int>(cl_gts_gui.valinp_level_start->value());

		/* start番号が範囲外 */
		if (this->crnt_file_num_< 1 || 9999< this->crnt_file_num_) {
			this->crnt_file_num_ = -1;
			this->crnt_list_num_ = -1;
		}

		/* Start番号に一致するlist番号あれば現位置とし、
		なければ追加して現位置とし、
		選択状態にする */
		else {
			this->crnt_list_num_=
			insert_and_select_fnum_in_list_(
				this->crnt_file_num_
			);
			if (	this->crnt_list_num_< 1) {
				this->crnt_file_num_ = -1;
				this->crnt_list_num_ = -1;
			}
		}
	}
	/* 次番号を得る(次処理があるか判断のためここで取る)
	次位置がなければ-1をセット */
	this->set_next_num_from_crnt_( continue_type_value );
}

/* 現位置を得る */
void cb_file_number_list::counter_next( const int continue_type_value )
{
	/* 次へ */
	this->crnt_list_num_ = this->next_list_num_;
	this->crnt_file_num_ = this->next_file_num_;

	/* Endless指定 */
	if ( continue_type_value == this->endless_type_value_ ) {
		/* File番号に一致するlist番号あれば現位置とし、
		なければ追加して現位置とし、
		選択状態にする */
		if (1 <= this->crnt_file_num_) {
			this->crnt_list_num_ =
			insert_and_select_fnum_in_list_(
				this->crnt_file_num_
			);
			if (	this->crnt_list_num_< 1) {
				this->crnt_file_num_ = -1;
				this->crnt_list_num_ = -1;
			}
		}
	}
	/* 次番号を得る(次処理があるか判断のためここで取る)
	次位置がなければ-1をセット */
	this->set_next_num_from_crnt_( continue_type_value );
}

/* 選択のフレーム送り/戻しをする */
bool cb_file_number_list::selected_prev_frame(void)
{
	if (cl_gts_gui.selbro_fnum_list->size() < 1) {
		return false; /* File Number Listないときはなにもしない */
	}
	const int ll = prev_selected_(
		cl_gts_gui.selbro_fnum_list->size()
	); /* 選択の最後尾番号 */
	if (ll < 0) {	/* なにも選択がない */
		cl_gts_gui.selbro_fnum_list->select(
			cl_gts_gui.selbro_fnum_list->size()
		); /* List最後尾を選択 */
	}
	else {				/* 選択あり */
	 if (1 < ll) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_fnum_list->select(ll-1); /* 次を選択 */
	 }
	 else {
	  /* 先頭に到達したら... */
	  if (cl_gts_gui.menite_frame_cyclic->value() != 0) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_fnum_list->select(
			cl_gts_gui.selbro_fnum_list->size()
		); /* List最後尾を選択 */
	  }
	  else {
	 	return false; /* ストップ */
	  }
	 }
	}
	return true;
}

bool cb_file_number_list::selected_next_frame(void)
{
	if (cl_gts_gui.selbro_fnum_list->size() < 1) {
		return false; /* File Number Listないときはなにもしない */
	}
	const int ll = next_selected_(1); /* 選択の先頭番号 */
	if (ll < 0) {	/* なにも選択がない */
		cl_gts_gui.selbro_fnum_list->select(1); /* List先頭を選択 */
	}
	else {				/* 選択あり */
	 if (ll < cl_gts_gui.selbro_fnum_list->size()) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_fnum_list->select(ll+1); /* 次を選択 */
	 }
	 else {
	  /* 後尾に到達したら... */
	  if (cl_gts_gui.menite_frame_cyclic->value() != 0) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_fnum_list->select(1); /* List先頭を選択 */
	  }
	  else {
	 	return false; /* ストップ */
	  }
	 }
	}
	return true;
}

