#include "FL/fl_ask.H"  // fl_alert(-)
#include "pri.h"
#include "ids_path_fltk_native_browse.h"
#include "gts_str_language.h"	// gts_str::
#include "cb_trace_batch.h"
#include "gts_gui.h"
#include "gts_master.h"

/* 選択したものだけtrace実行 */
void cb_trace_batch::cb_run( void )
{
	/* リストループ */
	for (int ii=1
	;ii<=cl_gts_gui.selbro_trace_batch_config_list->size() ;++ii) {

	 /* 選択してなければ何もしない */
	 if (cl_gts_gui.selbro_trace_batch_config_list->selected(ii)==0) {
		continue;
	 }

	 /* 読込んで設定する。このときtrace batch情報のみ設定しない */
	 const char *fpath
	    =cl_gts_gui.selbro_trace_batch_config_list->text(ii);
	 if (OK !=
	 cl_gts_master.cl_config.loading_and_set_dpath_fname(fpath,false)) {
		pri_funct_err_bttvr(
"Error : cl_gts_master.cl_config.loading_and_set_dpath_fname(%s,false) returns NG"
		 	,fpath );
		return;
	 }

	 /* 全画面をredraw */
	 Fl::check();

	 /* trace実行 */
	 if (cl_gts_master.cl_trace_files.cb_start( false ) == NG) {
		break; /* Error then break */
	 }

	 /* 終了したら選択を外す */
	 cl_gts_gui.selbro_trace_batch_config_list->select( ii ,0 );
	}
}

/* run listに同じものがあればそれを、なければ追加し、select状態にする */
namespace {
int number_of_same_( const std::string& fpath )
{
	for (int ii=1 ;ii<=cl_gts_gui.selbro_trace_batch_config_list->size()
	;++ii) {
		/* 同じパスがあった */
		if (fpath==cl_gts_gui.selbro_trace_batch_config_list->text(ii)
		) {
			return ii;
		}
	}
	return -1;
}
} // namespace
void cb_trace_batch::cb_add_or_select( void )
{
	/* ユーザーがブラウザーで複数のconfig.txtファイルを選択する */
	int filter_current=0; /* "TEXT\t*.txt"を示す */
	std::vector< std::string > vecstr(
		ids::path::fltk_native_browse_open_files(
//			"Add Config File"
			gts_str::trace_batch::add_config
			,this->dir_path_
			,""
			,"TEXT\t*.txt\n"
			, filter_current
		)
	);

	/* キャンセルしたか、選択しなかった */
	if (vecstr.at(0).empty()) {
		return;
	}

	this->dir_path_ = vecstr.at(0);

	for (auto fpath : vecstr) {
 	 const int ii= number_of_same_(fpath);/* 同じものがあればその位置 */
 	 if (0 <= ii) {	/* 同じパスがある */
	  /* 同じパスをselect状態にする */
	  cl_gts_gui.selbro_trace_batch_config_list->select(ii);
	 }
	 else {		/* 同じパスはない */
	  /* 新規パスを加える */
	  cl_gts_gui.selbro_trace_batch_config_list->insert(
	   cl_gts_gui.selbro_trace_batch_config_list->size()+1 ,fpath.c_str()
	  );
	  /* 追加したパスをselect状態にする */
	  cl_gts_gui.selbro_trace_batch_config_list->select(
	   cl_gts_gui.selbro_trace_batch_config_list->size()
	  );
	 }
	}
}

namespace {
int how_many_select_(int& crntnum)
{
	int counter=0;
	for (int ii=1;ii<=cl_gts_gui.selbro_trace_batch_config_list->size()
	;++ii) {
	 if (cl_gts_gui.selbro_trace_batch_config_list->selected(ii)==1) {
		++counter;
		crntnum = ii;
	 }
	}
	return counter;
}
} // namespace
void cb_trace_batch::cb_upper( void )
{
	int crntnum = -1;
	int selnum = how_many_select_( crntnum );
	if (selnum != 1) {
		fl_alert(
//			"Select only one(%d selected)"
			gts_str::trace_batch::too_many_selected
			,selnum);
		return;
	}

	if (1 < crntnum) {
	 cl_gts_gui.selbro_trace_batch_config_list->move( crntnum ,crntnum-1 );
	}
}

void cb_trace_batch::cb_lower( void )
{
	int crntnum = -1;
	int selnum = how_many_select_( crntnum );
	if (selnum != 1) {
		fl_alert(
//			"Select only one(%d selected)"
			gts_str::trace_batch::too_many_selected
			,selnum);
		return;
	}

	if (crntnum < cl_gts_gui.selbro_trace_batch_config_list->size()) {
	 cl_gts_gui.selbro_trace_batch_config_list->move(crntnum ,crntnum+1);
	}
}

void cb_trace_batch::cb_delete( void )
{
	for (int ii=1;ii<=cl_gts_gui.selbro_trace_batch_config_list->size();) {
	 if (cl_gts_gui.selbro_trace_batch_config_list->selected(ii)==1) {
	  cl_gts_gui.selbro_trace_batch_config_list->remove(ii);
	 }
	 else {
		++ii;
	 }
	}
}
