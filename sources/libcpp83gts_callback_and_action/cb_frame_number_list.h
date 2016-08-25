#ifndef cb_frame_number_list_h
#define cb_frame_number_list_h

class cb_frame_number_list {
public:
	cb_frame_number_list()
	{
	}

	/* Insert項目に入力したフレーム番号をリストに追加(sort)セットする */
	void set_list_from_string( void );

	/* ファイル存在マークを付加したファイル番号をlistの最後に追加 */
	/* level okの時使用 */
	void append_fnum_list_with_chk_mark( const int file_num );

	/* 指定範囲の番号でlistを追加生成する(ファイル存在マーク付き) */
	/* configの設定時使用 */
	void make_fnum_list_with_chk_mark( const int start_num, const int end_num );
private:
};

#endif /* !cb_frame_number_list_h */
