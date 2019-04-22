#ifndef __iip_channel_info_h__
#define __iip_channel_info_h__

#include <stdio.h>
#include "ptbl_returncode.h"

/* チャンネルタイプ */
typedef	enum {
	E_CH_NUM_EMPTY = 1, /* empty(not set channel_number_type) */
	E_CH_NUM_UCHAR, /* unsigned char */
	E_CH_NUM_USHRT, /* unsigned short */
	E_CH_NUM_ULONG, /* unsigned long */
	E_CH_NUM_FLOAT, /* float */
	E_CH_NUM_DOUBL, /* double */
	E_CH_NUM_BITBW  /* 1bitでモノクロ２階調 */
} E_CH_NUM_TYPE;

class iip_channel_info {
public:
	iip_channel_info()
	{
		this->set_e_ch_num_type( E_CH_NUM_EMPTY );
	}
	~iip_channel_info()
	{
		this->set_e_ch_num_type( E_CH_NUM_EMPTY );
	}
	/* タイプを指定することで各パラメータを設定する */
	void set_e_ch_num_type( E_CH_NUM_TYPE e_type );

	/* 各パラメータからタイプを返す */
	E_CH_NUM_TYPE get_e_ch_num_type( void );

	/* 各パラメータからタイプ名を返す
	get_cp_ch_num_type()は、関数のオーバーロードやってます。
	注意事項：デフォルト引数は使ってはいけません、
		  どっちの関数を呼んだのか区別がつかなくなります。
	*/
	const char *get_cp_ch_num_type( void );
	const char *get_cp_ch_num_type( E_CH_NUM_TYPE e_type );

	/* (正常に)設定してあるかチェック */
	int chk_e_ch_num_type( void );

	/* キャンバスメモリ確保のためチャンネルバイト数
	E_CH_NUM_BITBWのときはゼロを返す */
	long get_l_bytes( void ) { return this->_l_bytes; }

	/* TIFFファイルに保存する時に必要なmethod */
	long get_l_bits( void ) { return this->_l_bits; }

private:
	long	_l_bytes,
		_l_bits;
	E_CH_NUM_TYPE _e_type;
};

#endif /* !__iip_channel_info_h__ */
