#include <assert.h>
#include "FL/fl_ask.H"	// fl_alert(-)
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_master.h"

void gts_master::cb_config_save( void )
{
	/* configファイルへのパス名を得る
		いままでのloadしたconfigファイルで最新の名前 */
	const std::string filepath( this->cl_memo_config.memory_of_path );

	/* まだconfigファイルをloadしていないとき */
	if ( filepath.empty() ) {
		fl_alert("Not Load Config file yet.");
		return;
	}

	/* すでに存在するなら上書き確認のダイオローグを表示 */
	if (ptbl_dir_or_file_is_exist( const_cast<char *>(filepath.c_str()) )) {
		if (0 == fl_ask("Overwrite<%s>?",filepath.c_str())) { return; }
	}
	/* 存在しないときは保存確認のダイオローグを表示 */
	else {
		if (0 == fl_ask("Save<%s>?",filepath.c_str())) { return; }
	}

	/* config情報を保存する */
	if (OK != this->cl_memo_config.save( filepath.c_str() )) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_config.save(%s) returns NG",
			filepath );
		return;
	}
}
