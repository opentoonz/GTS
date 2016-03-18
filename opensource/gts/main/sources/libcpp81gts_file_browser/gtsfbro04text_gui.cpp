#include <sys/types.h>	/* for stat() */
#include <sys/stat.h>	/* for stat() */
#include <FL/filename.H>
#include "gtsfbro04text_gui.h"

int gtsfbro04text_gui::view_gui_text( Fl_Text_Buffer *flp_text_buf )
{
	struct stat st_stat;

	/* directoryならなにもしない */
	if (fl_filename_isdir( this->cp_path() )) {
		pri_funct_err_bttvr(
   "Error : fl_filename_isdir(%s) returns not zero",this->cp_path() );
		return OK;
	}

	/* ファイルサイズを調べる */
	if (stat( this->cp_path() ,&st_stat)) {
		pri_funct_err_bttvr(
   "Error : stat(%s,) returns not zero", this->cp_path() );
		return NG;
	}

	/* バッファ(Fl_Text_Buffer)のテキストを
	ファイル(cp_path)のテキストに置き換える
	終端を考えてファイルサイズ+1を与えること */
	flp_text_buf->loadfile( this->cp_path(), st_stat.st_size+1 );

	return OK;
}
