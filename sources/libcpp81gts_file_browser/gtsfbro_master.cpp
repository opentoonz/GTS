#include <stdlib.h> /* getenv() */
#include <FL/x.H> /* for fl_xid() */
#include "gts_master.h"
#include "gts_gui.h"

gts_master cl_gts_master;

int  gts_master::i_mv_sw( void ) const
{  return this->_i_mv_sw; }
void gts_master::i_mv_sw( int sw ) {
	this->_i_mv_sw = sw;
	//this->cl_iip_read.set_i_mv_sw( sw );
}
int  gts_master::i_pv_sw( void ) const
{  return this->_i_pv_sw; }
void gts_master::i_pv_sw( int sw ) {
	this->_i_pv_sw = sw;
	//this->cl_iip_read.set_i_pv_sw( sw );
}
int  gts_master::i_cv_sw( void ) const
{  return this->_i_cv_sw; }
void gts_master::i_cv_sw( int sw ) {
	this->_i_cv_sw = sw;
	//this->cl_iip_read.set_i_cv_sw( sw );
}

const char *gts_master::cp_application_name( void ) const
{	  return this->_cp_application_name; }
void gts_master::cp_application_name( char *cp_name )
{	  this->_cp_application_name = cp_name; }

const char *gts_master::cp_application_release_date( void ) const
{	  return this->_cp_application_release_date; }
void gts_master::cp_application_release_date( char *cp_date )
{	  this->_cp_application_release_date = cp_date; }

const char *gts_master::cp_application_release_number( void ) const
{ return this->_cp_application_release_number; }
void gts_master::cp_application_release_number( char *cp_num )
{	  this->_cp_application_release_number = cp_num; }

int gts_master::exec( void )
{
	/* fltk window and gui生成 */ 
	(void)cl_gts_gui.make_window();

	/* main window positon */
	cl_gts_gui.window_opengl->position(		100,100 );
	cl_gts_gui.window_config_load->position(	110,150 );
	cl_gts_gui.window_config_save_as->position(	120,200 );
	cl_gts_gui.window_level->position(		130,250 );
	cl_gts_gui.window_x1view->position(		140,300 );
	cl_gts_gui.window_trace_batch->position(	150,350 );

	/* levelシステム初期ディレクトリを設定 */
	/* text viewのバッファー設定 */
	if (OK != this->cl_bro_config.i_init()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_config.i_init() returns NG");
		return 1001;
	}
	if (OK != this->cl_bro_level.i_init()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_level.i_init() returns NG");
		return 1002;
	}
	if (OK != this->cl_bro_trace_batch.i_init()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_bro_trace_batch.i_init() returns NG");
		return 1003;
	}

	/* fltk windowのうちmain画面は必ず表示する */
	/* set_non_model()は始めにshowしたwindowがメイン */
	cl_gts_gui.window_opengl->show();

	/* keyのDrag and Dropをしない */
	Fl::dnd_text_ops(0);

	/* fltkイベントループ */
	return Fl::run();
}
