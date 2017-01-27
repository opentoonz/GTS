#include <string>	// std::stoi() C++11
#include <cctype>	// isdigit()
#include <cassert>	// assert()
#include <cstring>
#include <sstream>	// std::ostringstream
#include <iomanip>	// std::setw()
#include "ptbl_funct.h"
#include "ids_path_level_from_files.h"
#include "cb_number.h"
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
		*file_num = std::stoi( buffer );
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
} // namespace

namespace {

void insert_( const std::string& str ,const int list_num/* 1,2,3... */)
{
	cl_gts_gui.selbro_number_list->insert( list_num ,str.c_str() );
}

void insert_without_S_( const int file_num ,const int list_num/*1,2,3...*/)
{
	std::ostringstream ost;
	ost << std::setfill('0') << std::setw(4) << file_num;
	insert_( ost.str() ,list_num );
}
void insert_with_S_( const int file_num ,const int list_num/*1,2,3...*/)
{
	std::ostringstream ost;
	ost << std::setfill('0') << std::setw(4) << file_num << " S";
	insert_( ost.str() ,list_num );
}

} // namespace

//------------------------------------------------------------

/* saveファイル存在マーク付加した(orしない)ファイル番号をlistの最後に追加 */
void cb_number::append_without_S( const int file_num )
{
	insert_without_S_( file_num ,cl_gts_gui.selbro_number_list->size()+1);
}
void cb_number::append_with_S( const int file_num )
{
	insert_with_S_( file_num ,cl_gts_gui.selbro_number_list->size()+1 );
}

//------------------------------------------------------------

void cb_number::cb_set_list_from_string( void )
{
	/* 複数数値含文字列 "1" ,"0001" ,"1 2 3" ,"0001 0002 0003" ,etc. */
	const char* str = cl_gts_gui.norinp_number_input->value();

	/* 残り文字数(Remain SiZe) */
	int	rsz = cl_gts_gui.norinp_number_input->size();

	int	file_num = -1;

	while (nullptr != (str = next_num_( str ,&rsz ,&file_num ))) {
		int ii = -1;
		int jj = -1;
		/* file number listから、insertする
		(file_numと同じかより大きいfile(jj)の)位置(ii)を得る */
		for (ii=1 ;ii<=cl_gts_gui.selbro_number_list->size() ;++ii) {
			jj = this->file_num_from_list_num( ii );
			if (file_num <= jj) { break; }
		}
		/* すでにあるフレームは飛ばして次へ */
		if (jj == file_num) { continue; }

		/* insert&Scroll for viewing */
		if (ptbl_dir_or_file_is_exist(const_cast<char*>(
			this->get_save_path( file_num ).c_str()
		))) {
			insert_with_S_( file_num ,ii);
		}
		else {
			insert_without_S_( file_num ,ii);
		}

		cl_gts_gui.selbro_number_list->middleline( ii );
	}

	/* 新たにセットした数値を元に存在チェック表示 */
	cl_gts_master.cl_scan_and_save.cb_check_existing_saved_file();
	cl_gts_master.cl_trace_files.cb_check_existing_saved_file();
}

//------------------------------------------------------------

/* 全て選択状態にする */
void cb_number::select_all( void )
{
	for (int ii = 1; ii <= cl_gts_gui.selbro_number_list->size(); ++ii) {
		cl_gts_gui.selbro_number_list->select(ii);
	}
}

/* 選択に関わらずすべて削除 */
void cb_number::remove_all( void )
{
/*
	// GUI Scroll
	cl_gts_gui.selbro_number_list->topline(0);

	// delete all list
	while (0 < cl_gts_gui.selbro_number_list->size()) { 
	   	cl_gts_gui.selbro_number_list->remove(1);
	}
*/
	cl_gts_gui.selbro_number_list->clear();
}

/* 選択状態の項目をすべて削除 */
void cb_number::cb_remove_selected( void )
{
	for (int ii = 1; ii <= cl_gts_gui.selbro_number_list->size();) {
		if ( cl_gts_gui.selbro_number_list->selected(ii) ) {
			cl_gts_gui.selbro_number_list->remove(ii);
		} else { ++ii; }
	}

	/* 新たにセットした数値を元に存在チェック表示 */
	cl_gts_master.cl_scan_and_save.cb_check_existing_saved_file();
	cl_gts_master.cl_trace_files.cb_check_existing_saved_file();
}

/* 選択状態を外す */
void cb_number::unselect( int list_num )
{
	cl_gts_gui.selbro_number_list->select(list_num, 0);
}

void cb_number::add_S( const int list_num )
{
	std::string numstr( cl_gts_gui.selbro_number_list->text(list_num) );
	if (numstr.size() == 4) {
		numstr += " S";
		cl_gts_gui.selbro_number_list->text(list_num, numstr.c_str());
	}
}

//------------------------------------------------------------
/* cb_trace_files.h,cpp使用 */

int cb_number::file_num_from_list_num( int list_num )
{
	if (list_num<1 || cl_gts_gui.selbro_number_list->size() < list_num) {
		return -1;
	}
	return std::stoi( cl_gts_gui.selbro_number_list->text(list_num) );
}

int cb_number::next_selected_list_num( int list_num )
{
	if (list_num<1 || cl_gts_gui.selbro_number_list->size() < list_num) {
		return -1;
	}
	for (;list_num <= cl_gts_gui.selbro_number_list->size() ;++list_num) {
		if (cl_gts_gui.selbro_number_list->selected(list_num)) {
			return list_num;
		}
	}
	return -1;
}

//------------------------------------------------------------

namespace {
 int prev_selected_( int list_num )
 {
	for (;1 <= list_num ;--list_num) {
		if (cl_gts_gui.selbro_number_list->selected(list_num)) {
			return list_num;
		}
	}
	return -1;
 }
 /* 全て選択解除にする */
 void unselect_all_( void )
 {
	for (int ii = 1; ii <= cl_gts_gui.selbro_number_list->size(); ++ii) {
		cl_gts_gui.selbro_number_list->select(ii ,0);
	}
 }
 } // namespace

 /* listの順位置に挿入し、選択状態にして、既にあるならその位置を返す */
 int cb_number::insert_and_select_fnum_in_list_( const int file_num )
 {
	int ii,jj;
	char buffer[8];

	/* size + 1までループして最後でも追加するようにする */
	for (ii= 1 ;ii <= cl_gts_gui.selbro_number_list->size() ;++ii) {
		jj = this->file_num_from_list_num( ii );
		if (file_num == jj) {/* 既にあるなら何もしないで... */
			cl_gts_gui.selbro_number_list->select( ii );/* 選択 */
			return ii;
		}
		if (file_num < jj) { /* listの順位置に挿入 */
			(void)sprintf(buffer, "%04d", file_num );
			cl_gts_gui.selbro_number_list->insert( ii ,buffer );
			cl_gts_gui.selbro_number_list->select( ii );/* 選択 */
			return ii;
		}
	}
	/* listの最後に追加 */
	(void)sprintf(buffer, "%04d", file_num );
	cl_gts_gui.selbro_number_list->add( buffer );
	cl_gts_gui.selbro_number_list->select(
	 cl_gts_gui.selbro_number_list->size()
	);/* 選択 */
	return ii;
}

/* 現位置と現番号から次の処理位置と処理番号を得る */
void cb_number::set_next_num_from_crnt_(
	const int continue_type_value
	,const bool forward_sw
)
{
	/* 現位置がなければ次もない */
	if (this->crnt_list_num_ < 1 || this->crnt_file_num_ < 1) {
		this->next_list_num_ = -1;
		this->next_file_num_ = -1;
		return;
	}
	if ( continue_type_value == this->end_type_value_ ) {
		/* End指定 */
		if ( forward_sw ) {
			/* 順送り(start <= end)の次選択位置 */
			this->next_list_num_= this->next_selected_list_num(
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
			this->next_file_num_ =
			 this->file_num_from_list_num(this->next_list_num_);
		}
	}
	else	/* Endless指定 */
	if ( continue_type_value == this->endless_type_value_ ) {

		if (cl_gts_gui.choice_scan_num_endless_direction->value() == 0)
		{
			this->next_list_num_ = this->crnt_list_num_ + 1;
			this->next_file_num_ = this->crnt_file_num_ + 1;
		}
		if (cl_gts_gui.choice_scan_num_endless_direction->value() == 1)
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
void cb_number::counter_start( const int continue_type_value )
{
	if ( continue_type_value == this->end_type_value_ ) {
		/* End指定 */

		/* GUIのfile number listの選択をたどる */
		/* 処理後のマーキングと選択解除は外で行う */

		if (
			cl_gts_gui.valinp_scan_num_start->value()
			<= cl_gts_gui.valinp_scan_num_end->value()
		) {
			/* 順送り(start <= end)の初期位置 */
			this->crnt_list_num_= this->next_selected_list_num(1);
		}
		else {
			/* 逆送り(start > end)の初期位置 */
			this->crnt_list_num_= prev_selected_(
				cl_gts_gui.selbro_number_list->size()
			);
		}
		if (this->crnt_list_num_ < 1) { /* listに選択がない */
			this->crnt_file_num_ = -1;
		}
		else { /* 選択があるなら、項目の表示番号を得る */
			this->crnt_file_num_ =
			 this->file_num_from_list_num(this->crnt_list_num_);
		}
	}
	else /* Endless指定 */
	if ( continue_type_value == this->endless_type_value_ ) {
		/* GUIのlistの選択は無視 */
		/* 処理後のマーキングと選択解除は外で行う */

		/* LevelのStart番号から始まる */
		this->crnt_file_num_ = 
		 static_cast<int>(cl_gts_gui.valinp_scan_num_start->value());

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
	this->set_next_num_from_crnt_(
		continue_type_value
		,cl_gts_gui.valinp_scan_num_start->value() <=
		 cl_gts_gui.valinp_scan_num_end->value()
	);
}

/* 現位置を得る */
void cb_number::counter_next( const int continue_type_value )
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
	this->set_next_num_from_crnt_(
		continue_type_value
		,cl_gts_gui.valinp_scan_num_start->value() <=
		 cl_gts_gui.valinp_scan_num_end->value()
	);
}

/* 選択のフレーム送り/戻しをする */
bool cb_number::selected_prev_frame(void)
{
	if (cl_gts_gui.selbro_number_list->size() < 1) {
		return false; /* File Number Listないときはなにもしない */
	}
	const int ll = prev_selected_(
		cl_gts_gui.selbro_number_list->size()
	); /* 選択の最後尾番号 */
	if (ll < 0) {	/* なにも選択がない */
		cl_gts_gui.selbro_number_list->select(
			cl_gts_gui.selbro_number_list->size()
		); /* List最後尾を選択 */
	}
	else {				/* 選択あり */
	 if (1 < ll) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_number_list->select(ll-1); /* 次を選択 */
	 }
	 else {
	  /* 先頭に到達したら... */
	  if (cl_gts_gui.menite_frame_cyclic->value() != 0) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_number_list->select(
			cl_gts_gui.selbro_number_list->size()
		); /* List最後尾を選択 */
	  }
	  else {
	 	return false; /* ストップ */
	  }
	 }
	}
	return true;
}

bool cb_number::selected_next_frame(void)
{
	if (cl_gts_gui.selbro_number_list->size() < 1) {
		return false; /* File Number Listないときはなにもしない */
	}
	const int ll = this->next_selected_list_num(1); /* 選択の先頭番号 */
	if (ll < 0) {	/* なにも選択がない */
		cl_gts_gui.selbro_number_list->select(1); /* List先頭を選択 */
	}
	else {				/* 選択あり */
	 if (ll < cl_gts_gui.selbro_number_list->size()) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_number_list->select(ll+1); /* 次を選択 */
	 }
	 else {
	  /* 後尾に到達したら... */
	  if (cl_gts_gui.menite_frame_cyclic->value() != 0) {
		unselect_all_();/* 選択全解除 */
		cl_gts_gui.selbro_number_list->select(1); /* List先頭を選択 */
	  }
	  else {
	 	return false; /* ストップ */
	  }
	 }
	}
	return true;
}

//--------------------------------------------------
/* Scan/Trace別の動作 */
void cb_number::set_type_to_scan(void)
{
	cl_gts_gui.output_number_action_type->value( this->str_type_scan_ );
}

void cb_number::set_type_to_trace(void)
{
	cl_gts_gui.output_number_action_type->value( this->str_type_trace_ );
}
bool cb_number::is_scan(void)
{
	return this->get_type_() == this->str_type_scan_;
}
bool cb_number::is_trace(void)
{
	return this->get_type_() == this->str_type_trace_;
}

const std::string cb_number::get_type_(void)
{
	return cl_gts_gui.output_number_action_type->value();
}
/* numsをリスト表示しファイル存在なら'S'マーク付ける & 保存名表示 */
void cb_number::append_checked_S_and_set_name_by_number_list_( const std::vector<int>& nums )
{
	const std::string ty( this->get_type_() );
	if (ty.empty()) {
		return;
	}
	if      (ty == this->str_type_scan_) {
		for (int nn : nums) {
			if (ptbl_dir_or_file_is_exist(const_cast<char*>(
	cl_gts_master.cl_scan_and_save.get_save_path(nn).c_str()
			))) {
				this->append_with_S(nn);
			}
			else {
				this->append_without_S(nn);
			}
		}
		/* Numberウインドウ 保存level名表示 */
		cl_gts_gui.output_number_file_head_name->value(
		cl_gts_gui.strinp_scan_save_file_head->value()
		);
	}
	else if (ty == this->str_type_trace_) {
		for (int nn : nums) {
			if (ptbl_dir_or_file_is_exist(const_cast<char*>(
	cl_gts_master.cl_trace_files.get_save_path(nn).c_str()
		))) {
				this->append_with_S(nn);
			}
			else {
				this->append_without_S(nn);
			}
		}
		/* Numberウインドウ 保存level名表示 */
		cl_gts_gui.output_number_file_head_name->value(
		cl_gts_gui.strinp_trace_save_file_head->value()
		);
	}
}
/* s,eをリスト表示しファイル存在なら'S'マーク付ける & 保存名表示 */
void cb_number::append_checked_S_and_set_name_from_start_to_end( const int num_start ,const int num_end )
{
	const std::string ty( this->get_type_() );
	if (ty.empty()) {
		return;
	}
	if      (ty == this->str_type_scan_) {
		for (int nn = num_start ;nn <= num_end ;++nn) {
			if (ptbl_dir_or_file_is_exist(const_cast<char*>(
	cl_gts_master.cl_scan_and_save.get_save_path(nn).c_str()
			))) {
				this->append_with_S(nn);
			}
			else {
				this->append_without_S(nn);
			}
		}
		/* Numberウインドウ 保存level名表示 */
		cl_gts_gui.output_number_file_head_name->value(
		cl_gts_gui.strinp_scan_save_file_head->value()
		);
	}
	else if (ty == this->str_type_trace_) {
		for (int nn = num_start ;nn <= num_end ;++nn) {
			if (ptbl_dir_or_file_is_exist(const_cast<char*>(
	cl_gts_master.cl_trace_files.get_save_path(nn).c_str()
		))) {
				this->append_with_S(nn);
			}
			else {
				this->append_without_S(nn);
			}
		}
		/* Numberウインドウ 保存level名表示 */
		cl_gts_gui.output_number_file_head_name->value(
		cl_gts_gui.strinp_trace_save_file_head->value()
		);
	}
}

const std::string cb_number::get_save_path( const int number )
{
	const std::string ty( this->get_type_() );
	if (ty.empty()) {
		return std::string();
	}
	if      (ty == this->str_type_scan_) {
		return cl_gts_master.cl_scan_and_save.get_save_path(number);
	}
	else if (ty == this->str_type_trace_) {
		return cl_gts_master.cl_trace_files.get_save_path(number);
	}
	return std::string();
}

/* Numberウインドウをnumberリストで再構築 */
void cb_number::reset_by_number_list( const std::vector<int>& nums )
{
	/* Numberウインドウ List再構築 */
	this->remove_all(); /* リスト全消去 */
	this->append_checked_S_and_set_name_by_number_list_( nums );
	this->select_all(); /* リスト全選択 */

	/* Numberウインドウ 即表示 */
	cl_gts_gui.window_number->flush();
}
/* Numberウインドウをnumberリストで再構築 */
void cb_number::reset_from_start_to_end( const int num_start ,const int num_end )
{
	/* Numberウインドウ List再構築 */
	this->remove_all(); /* リスト全消去 */
	this->append_checked_S_and_set_name_from_start_to_end(
		num_start ,num_end
	);
	this->select_all(); /* リスト全選択 */

	/* Numberウインドウ 即表示 */
	cl_gts_gui.window_number->flush();
}
