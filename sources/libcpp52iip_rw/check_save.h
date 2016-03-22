#ifndef __check_save_h__
#define __check_save_h__

#include "ptbl_returncode.h"

typedef enum {
	E_CHECK_SAVE_FORCE_MODE,
	E_CHECK_SAVE_ASK_MODE,
	E_CHECK_SAVE_SKIP_MODE
} E_CHECK_SAVE_MODE;

class check_save {
public:
	check_save( void )
	{
		/* 動作モードの初期設定 */
		this->_e_save_mode = E_CHECK_SAVE_FORCE_MODE;
		this->_i_use_of_all_cancel_sw = OFF;
	}

	/* ファイル保存モードの設定 */
	void set_force_mode( void ) { this->_e_save_mode =
    E_CHECK_SAVE_FORCE_MODE; }
	void set_ask_mode( void ) { this->_e_save_mode =
    E_CHECK_SAVE_ASK_MODE; }
	void set_skip_mode( void ) { this->_e_save_mode =
    E_CHECK_SAVE_SKIP_MODE; }

	/* askモードで、オールキャンセルも表示するスイッチ */
	void set_use_of_all_cancel( void ) {
	this->_i_use_of_all_cancel_sw = ON; }

	/*
	ファイル保存チェック
	戻り値は、_is_cancel(-)と同じ */
	int cancel( char *cp_fname );
private:
	E_CHECK_SAVE_MODE	_e_save_mode;
	int	_i_use_of_all_cancel_sw;

	/* 存在していて、かつskipモードなら(-->保存をとりやめる) */
	int _is_skip_mode( void ) { return (
  E_CHECK_SAVE_SKIP_MODE==this->_e_save_mode); }

	/* 存在していて、かつaskモードなら... */
	int _is_ask_mode( void ) { return (
  E_CHECK_SAVE_ASK_MODE==this->_e_save_mode); }

	/*
	askモードの場合、ユーザーが保存の判断をする
	戻り値は、0で上書き、1はcancel、2はall cancel */
	int _is_cancel( char *cp_fname );
};

#endif /* !__check_save_h__ */
