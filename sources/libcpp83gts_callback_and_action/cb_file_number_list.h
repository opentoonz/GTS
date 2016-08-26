#ifndef cb_file_number_list_h
#define cb_file_number_list_h

class cb_file_number_list {
public:
	cb_file_number_list()
		:crnt_list_num_(-1)
		,crnt_file_num_(-1)
		,next_list_num_(-1)
		,next_file_num_(-1)
		,prev_list_num_(-1)
		,prev_file_num_(-1)
		,endress_sw_(false)
	{
	}

	//--------------------------------------------------

	/* Insert項目に入力したフレーム番号をリストに追加(sort)セットする */
	void set_list_from_string( void );

	//--------------------------------------------------

	/* ファイル存在マークを付加したファイル番号をlistの最後に追加 */
	/* level okの時使用 */
	void append_fnum_list_with_chk_mark( const int file_num );

	/* 指定範囲の番号でlistを追加生成する(ファイル存在マーク付き) */
	/* configの設定時使用 */
	void make_fnum_list_with_chk_mark( const int start_num, const int end_num );

	//--------------------------------------------------

	void select_all( void );	/* 全て選択状態にする */
	void remove_all( void );	/* 選択に関わらずすべて削除 */
	void remove_selected( void );	/* 選択状態の項目をすべて削除 */

	//--------------------------------------------------

	void unselect( int list_num );	/* 選択状態を外す */
	int marking_scan_file( int list_num );/* Scan  fileの存在Mark付加 */
	int marking_trace_file(int list_num );/* Trace fileの存在Mark付加 */

	//--------------------------------------------------

/*
	画像の番号をたどる場合と動作
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

/*
	画像の番号をたどる方法
	(file番号とlist番号)
	1 初期化
		位置をすべて-1にセット
	2 現位置を得る
	  End
		a エラー処理のため、前位置を現位置に置換える
		b 現位置が初期化状態(-1)なら、現位置を初期位置にする
		c 現位置が初期化状態(-1)でなければ、現位置を次位置に置換える
		d 次処理があるか判断のため、次番号もここで取る
		e 次位置がなければ-1をセット
	  Endless
		a 初期化状態(-1)の場合Startをセット
		b 初期化状態(-1)でなければ+1/-1(1...9999の範囲でlimmiterかける)
	3 Errorが起きたら
		現位置を前位置に戻す
		エラーなので次をStopするため次番号に-1をセット
*/
	/*
	int set_first_number( void );
	void reset_next_number( void );
	int set_next_number( void );
	void reset_next_to_crnt_number( void );
	void set_next_to_crnt_number( void );
	*/
	void num_init( void );	/* 1 初期化 */
	void num_set( void );	/* 2 現位置を得る */
	void num_error( void );	/* 3 Errorが起きた */

private:
	int	crnt_list_num_
		, crnt_file_num_
		, next_list_num_
		, next_file_num_
		, prev_list_num_
		, prev_file_num_
		;

	/* ファイル存在マークを付加したファイル番号をlistの順位置に挿入 */
	/* Endless動作のnum_set()で使用 */
	void set_fnum_list_( const int file_num );
};

#endif /* !cb_file_number_list_h */
