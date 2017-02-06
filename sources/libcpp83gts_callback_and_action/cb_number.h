#ifndef cb_number_h
#define cb_number_h

#include <vector>

class cb_number {
public:
	cb_number()
		:crnt_list_num_(-1)
		,crnt_file_num_(-1)
		,next_list_num_(-1)
		,next_file_num_(-1)
		,backup_crnt_list_num_(-1)
		,backup_crnt_file_num_(-1)
		,str_type_scan_("Scan")
		,str_type_trace_("Trace")
	{
	}

	//--------------------------------------------------

	/* Insert項目に入力したフレーム番号をリストに追加(sort)セットする */
	void cb_set_list_from_string( void );

	//--------------------------------------------------

	/* ファイル存在マーク付加(orしない)ファイル番号をlistの最後に追加 */
	void append_without_S( const int file_num );
	void append_with_S( const int file_num );

	//--------------------------------------------------

	void select_all( void );	/* 全て選択状態にする */
	void remove_all( void );	/* 選択に関わらずすべて削除 */
	void cb_remove_selected( void );/* 選択状態の項目をすべて削除 */

	//--------------------------------------------------

	void unselect( int list_num );	/* 選択状態を外す */

	/* 指定の項目に(付いていなければ)"S"マークを付加する */
	void add_S( const int list_num );

	//--------------------------------------------------

	/* 画像の番号をたどる場合と動作
		-スキャンする
			--> Endlessの場合list番号とfile番号は一致する
			--> Endlessの-1の場合1で止まる。+1ではEndless
		-トレスする
			--> Endlessであってもlist選択部分のみの処理
		-プレビューする
			--> 選択した最初の一枚を得る。
	*/
	int get_crnt_list_num(void) const { return this->crnt_list_num_; }
	int get_crnt_file_num(void) const { return this->crnt_file_num_; }
	int get_next_file_num(void) const { return this->next_file_num_; }

	/* 画像の番号をたどる方法を指定するための番号(scan時はGUI値から) */
	int get_end_type_value(void) const { return this->end_type_value_; }
	int get_endless_type_value(void) const {
		return this->endless_type_value_;
	}

	/* 画像の番号をたどる (file番号とlist番号) */
	/* 1 初期化し、開始位置 */
	void counter_start( const int continue_type_value );
	/* 2 次へ辿り、現位置を得る */
	void counter_next( const int continue_type_value );
	/* 3 Cancel動作のため一つ前に戻す */
	void counter_cancel_one_step( void );

	/* 選択のフレーム送り/戻しをする */
	bool selected_prev_frame(void);
	bool selected_next_frame(void);

	//--------------------------------------------------

	int file_num_from_list_num( int list_num );

	/* 独自に選択をたどるための機能 */
	int next_selected_list_num( int list_num );

	//--------------------------------------------------
	/* Scan動作なのかTrace動作なのかを示す仕組み */
	void set_type_to_scan(void);
	void set_type_to_trace(void);
	bool is_scan(void);
	bool is_trace(void);

	void reset_by_number_list( const std::vector<int>& nums );
	void reset_from_start_to_end(const int num_start,const int num_end);

	const std::string get_save_path( const int num );

private:
	int	crnt_list_num_
		, crnt_file_num_
		, next_list_num_
		, next_file_num_
		, backup_crnt_list_num_
		, backup_crnt_file_num_
		;

	const char* str_type_scan_;
	const char* str_type_trace_;

	//-------------------------------------

	enum choice_level_continue_type_value_ {
		end_type_value_		// 0
		,endless_type_value_	// 1
	};

	int insert_and_select_fnum_in_list_( const int file_num );

	void set_next_num_from_crnt_(
		const int continue_type_value
		,const bool forward_sw
	);

	void append_checked_S_and_set_name_by_number_list_(
		const std::vector<int>& nums
	);
	void append_checked_S_and_set_name_from_start_to_end(
		const int num_start ,const int num_end
	);
	const std::string get_save_head_( void );
	const std::string get_type_(void);
};

#endif /* !cb_number_h */
