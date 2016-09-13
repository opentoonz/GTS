#include <string.h> /* strncpy() */
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::_cancel( void )
{
	/* Cancel用のメモリから画面を元に戻す */
	/* 記憶からGUI復元 */
	this->memory_to_gui();

	/* listを再表示 */
	if (OK != this->change_level_list()) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list(%s) returns NG" );
		return;
	}
}
void gtsfbro06cb_level::cb_cancel( void )
{
	this->_cancel();

	/* add 2013-09-25 level名からfileが上書きなら注意表示 */
	this->cb_level_name();

	/* levelの終了に伴うx1view windowの閉じでは、
	表示スイッチをOFFにしない */
	cl_gts_gui.window_x1view->hide(); /* x1 Window閉じる */
	cl_gts_gui.menite_level->clear(); /* menuのcheckを消す */
	cl_gts_gui.window_level->hide();  /* Window閉じる */
}
