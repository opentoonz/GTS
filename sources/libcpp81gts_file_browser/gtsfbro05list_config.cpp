#include <string.h> /* strlen() */
#include <FL/fl_ask.H>
#include <FL/filename.H>
#include "gtsfbro05list_config.h"
#include "gts_gui.h"

void gtsfbro05list_config::init_text_buffer( void )
{
	cl_gts_gui.txtdis_config_load_text->buffer(
		&(this->_cl_fl_text_buffer_load) );
	cl_gts_gui.txtdis_config_save_as_text->buffer(
		&(this->_cl_fl_text_buffer_save_as) );
}

int gtsfbro05list_config::view_text_for_load( void )
{
	if (OK != this->i_path_dir_file(
		cl_gts_gui.filinp_config_load_dir->value(),
		cl_gts_gui.strinp_config_load_file->value()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s) returns NG",
		cl_gts_gui.filinp_config_load_dir->value(),
		cl_gts_gui.strinp_config_load_file->value()
		);
		return NG;
	}

	if (OK != this->view_gui_text(
		&(this->_cl_fl_text_buffer_load)
	)) {
		pri_funct_err_bttvr(
	 "Error : this->view_gui_text(-) returns NG" );
		return NG;
	}
	return OK;
}

int gtsfbro05list_config::view_text_for_save_as( void )
{
	if (OK != this->i_path_dir_file(
		cl_gts_gui.filinp_config_save_as_dir->value(),
		cl_gts_gui.strinp_config_save_as_file->value(),
		this->ccp_text_file_ext()
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_dir_file(%s,%s,%s) returns NULL",
		cl_gts_gui.filinp_config_save_as_dir->value(),
		cl_gts_gui.strinp_config_save_as_file->value(),
		this->ccp_text_file_ext()
		);
		return NG;
	}

	if (OK != this->view_gui_text(
		&(this->_cl_fl_text_buffer_save_as)
	)) {
		pri_funct_err_bttvr(
	 "Error : this->view_gui_text(-) returns NG");
		return NG;
	}
	return OK;
}

/*--------------------------------------------------------*/

void gtsfbro05list_config::_end( void )
{
	this->remove_gui_list( cl_gts_gui.selbro_config_save_as_list );
	this->remove_gui_list( cl_gts_gui.selbro_config_load_list );
	this->mem_free();
}

int gtsfbro05list_config::change_config_list( void )
{
	const char *ccp_dir;
	char ca_msg[PTBL_PATH_MAX];

	ccp_dir = cl_gts_gui.filinp_config_load_dir->value();

	/* dirが存在しない(nullパス("")は有効とする)
	ときはlist更新せず、Dialog表示して注意する */
	if (	(NULL == ccp_dir) ||
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
	 "Error : this->i_path_cpy_dir(%s) returns NG", ccp_dir );
		return NG;
	}

	this->_end();

	if (OK != this->mem_alloc( 0 )) {
		pri_funct_err_bttvr(
	 "Error : this->mem_alloc(0) returns NG" );
		return NG;
	}

	this->make_dir_or_file(
		E_DIR_OR_FILE_IS_DIR,
		E_DIR_OR_FILE_IS_TEXT );

	this->draw_gui_list( cl_gts_gui.selbro_config_load_list );
	this->draw_gui_list( cl_gts_gui.selbro_config_save_as_list );

	return OK;
}

void gtsfbro05list_config::change_config_dir( const char *ccp_dir )
{
	char *cp_gui_dir;

	if (NULL == ccp_dir) {
		cp_gui_dir = this->cp_path(); }
	else {	cp_gui_dir = (char *)ccp_dir; }

	cl_gts_gui.filinp_config_load_dir->value(cp_gui_dir);
	cl_gts_gui.filinp_config_load_dir->position(strlen(cp_gui_dir));
	cl_gts_gui.filinp_config_save_as_dir->value(cp_gui_dir);
	cl_gts_gui.filinp_config_save_as_dir->position(
		strlen(cp_gui_dir)
	);
}
int gtsfbro05list_config::init_config_dir( const char *ccp_dir )
{
	this->change_config_dir(ccp_dir);
	this->v_path_memory(ccp_dir);
	return this->change_config_list();
}
