#include <stdio.h>
#include <string.h>	/* strcmp() */
#include <FL/fl_ask.H>
#include "gtsfbro05list_trace_batch.h"
#include "gts_gui.h"

int gtsfbro05list_trace_batch::get_i_1st_selected( void )
{
	int	ii;
	for (ii=1; ii<=cl_gts_gui.selbro_trace_batch_list->size(); ++ii){
		if    (cl_gts_gui.selbro_trace_batch_list->selected(ii)) {
			return ii;
		}
	}
	return -1;
}

void gtsfbro05list_trace_batch::init_text_buffer( void )
{
	cl_gts_gui.txtdis_trace_batch_text->buffer(
		&(this->_cl_fl_text_buffer) );
}

int gtsfbro05list_trace_batch::view_text( void )
{
	int i_selected;

	i_selected = this->get_i_1st_selected();
	if (i_selected < 0) {
		pri_funct_err_bttvr(
	    "Error : this->get_i_1st_selected() returns %d",i_selected);
		return NG; /* 選択されていない */
	}

	if (OK != this->i_path_dir_file(
		cl_gts_gui.filinp_trace_batch_dir->value(),
		cl_gts_gui.selbro_trace_batch_list->text(i_selected)
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NULL",
		cl_gts_gui.filinp_trace_batch_dir->value(),
		cl_gts_gui.selbro_trace_batch_list->text(i_selected)
		);
		return NG;
	}

	if (OK != this->view_gui_text(
		&(this->_cl_fl_text_buffer)
	)) {
		pri_funct_err_bttvr(
	 "Error : this->view_gui_text(-) returns NG" );
		return NG;
	}
	return OK;
}

/*--------------------------------------------------------*/

void gtsfbro05list_trace_batch::_end( void )
{
	this->remove_gui_list( cl_gts_gui.selbro_trace_batch_list );
	this->mem_free();
}

int gtsfbro05list_trace_batch::change_trace_batch_list( void )
{
	const char *ccp_dir;
	char ca_msg[PTBL_PATH_MAX];

	ccp_dir = cl_gts_gui.filinp_trace_batch_dir->value();

	/* dirが存在しない(nullパス("")は有効とする)
	ときはlist更新せず、Dialog表示して注意する */
	if (    (NULL == ccp_dir) ||
		(	('\0' != ccp_dir[0]) &&
			!fl_filename_isdir( ccp_dir )
		)
	) {
		pri_funct_err_bttvr(
			"Error : dir path(%s) is not exist", ccp_dir );
		if (NULL == ccp_dir) {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"Dir path\n is not exist!");
		} else {
			snprintf(ca_msg,PTBL_PATH_MAX,
				"%s\n is not exist!",ccp_dir);
		}
		fl_alert(ca_msg);
		return OK;
	}

	if (OK != this->i_path_cpy_dir( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NULL", ccp_dir );
		return NG;
	}

	this->_end();

	if (OK != this->mem_alloc( 0 )) {
		pri_funct_err_bttvr(
	 "Error : this->mem_alloc(0) returns NULL" );
		return NG;
	}
	this->make_dir_or_file(
		E_DIR_OR_FILE_IS_DIR,
		E_DIR_OR_FILE_IS_TEXT );

	this->draw_gui_list( cl_gts_gui.selbro_trace_batch_list );

	return OK;
}

void gtsfbro05list_trace_batch::change_trace_batch_dir( const char *ccp_dir )
{
	char *cp_gui_dir;

	if (NULL == ccp_dir) {
		cp_gui_dir = this->cp_path(); }
	else {	cp_gui_dir = (char *)ccp_dir; }

	cl_gts_gui.filinp_trace_batch_dir->value(cp_gui_dir);
	cl_gts_gui.filinp_trace_batch_dir->position(strlen(cp_gui_dir));
}
int gtsfbro05list_trace_batch::init_trace_batch_dir( const char *ccp_dir )
{
	this->change_trace_batch_dir(ccp_dir);
	this->v_path_memory(ccp_dir);
	return this->change_trace_batch_list();
}
