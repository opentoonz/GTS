#include <assert.h>
#include <FL/fl_ask.H>
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

void gts_master::cb_config_save( void )
{
	char *cp_path;

	/* configファイルへのパス名を得る
		いままでのloadしたconfigファイルで最新の名前 */
	cp_path = this->cl_memo_config.cp_memory_path();

	/* cp_pathはNULLを返さない */
	assert(NULL != cp_path);

	/* まだconfigファイルをloadしていないとき */
	if ('\0' == cp_path[0]) {
		fl_alert("Not Load Config file yet.");
		return;
	}

	/* すでに存在するなら上書き確認のダイオローグを表示 */
	if (ptbl_dir_or_file_is_exist( cp_path )) {
		if (0 == fl_ask("Overwrite<%s>?",cp_path)) { return; }
	}
	/* 存在しないときは保存確認のダイオローグを表示 */
	else {
		if (0 == fl_ask("Save<%s>?",cp_path)) { return; }
	}

	/* config情報を保存する */
	if (OK != this->cl_memo_config.save( cp_path )) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_config.save(%s) returns NG",
			cp_path );
		return;
	}
}
