#include <string.h>
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

/* GUIの状態を記憶する */
void gtsfbro06cb_level::memory_from_gui( const char* level_dir_path )
{
	// save dir path
	if (level_dir_path != nullptr) {
		if ( OK != this->i_path_cpy_dir( level_dir_path ) ) {
			pri_funct_err_bttvr(
		"Error : this->i_path_cpy_dir(%s) returns NG"
				,level_dir_path );
			return;
		}
		this->v_path_memory();
	}

	// save file head
	this->save_file_head_ = cl_gts_gui.strinp_level_save_file_head->value();

	// save and open start
	this->saveopen_start_ = cl_gts_gui.valinp_level_saveopen_num_start->value();

	// save and open end
	this->saveopen_end_   = cl_gts_gui.valinp_level_saveopen_num_end->value();

	// save and open continue type
	this->saveopen_continue_type_ =
		cl_gts_gui.choice_level_save_num_continue_type->text();

	// save image format
	this->save_image_format_ =
		cl_gts_gui.choice_level_save_image_format->value();

	// open dir path
	this->open_dir_path_ =
		cl_gts_gui.filinp_level_open_dir_path->value();

	// open file head
	this->open_file_head_ =
		cl_gts_gui.strinp_level_open_name->value();

	// open image format
	this->open_image_format_ =
		cl_gts_gui.choice_level_open_image_file_format->value();
}
/* 記憶からGUI復元 */
void gtsfbro06cb_level::memory_to_gui( void )
{
	// save dir path
	cl_gts_gui.filinp_level_save_dir_path->value( this->cp_memory() );
	cl_gts_gui.filinp_level_save_dir_path->position(
		strlen(this->cp_memory())
	);

	// save file head
	cl_gts_gui.strinp_level_save_file_head->value( this->save_file_head_.c_str());

	// save and open start
	cl_gts_gui.valinp_level_saveopen_num_start->value(this->saveopen_start_ );

	// save and open end
	cl_gts_gui.valinp_level_saveopen_num_end->value(  this->saveopen_end_ );

	// save and open continue type
	if (!(this->saveopen_continue_type_.empty())) {
	 cl_gts_gui.choice_level_save_num_continue_type->value(
	  cl_gts_gui.choice_level_save_num_continue_type->find_item(
		this->saveopen_continue_type_.c_str()
	  )
	 );
	}
	if (cl_gts_gui.choice_level_save_num_continue_type->text()
	== std::string("End")) {
		cl_gts_gui.valinp_level_saveopen_num_end->show();
		cl_gts_gui.choice_level_save_num_endless_direction->hide();
		cl_gts_gui.selbro_fnum_list->activate();
	}
	else {
		cl_gts_gui.valinp_level_saveopen_num_end->hide();
		cl_gts_gui.choice_level_save_num_endless_direction->show();
		cl_gts_gui.selbro_fnum_list->deactivate();
	}

	// save image format
	if (!(this->save_image_format_.empty())) {
	 cl_gts_gui.choice_level_save_image_format->value(
	  cl_gts_gui.choice_level_save_image_format->find_item(
		this->save_image_format_.c_str()
	  )
	 );
	}

	// open dir path
	cl_gts_gui.filinp_level_open_dir_path->value(
		this->open_dir_path_.c_str()
	);
	cl_gts_gui.filinp_level_open_dir_path->position(
		this->open_dir_path_.size()
	);

	// open file head
	cl_gts_gui.strinp_level_open_name->value(
		this->open_file_head_.c_str()
	);

	// open image format
	if (!(this->open_image_format_.empty())) {
	 cl_gts_gui.choice_level_open_image_file_format->value(
	  cl_gts_gui.choice_level_open_image_file_format->find_item(
		this->open_image_format_.c_str()
	  )
	 );
	}
}
int gtsfbro06cb_level::i_init( void )
{
	/* 画像情報表示用テキスト */
	this->init_text_buffer();

	/* GUIの状態を記憶する */
	/* Dirパス --> ここではデフォルト設定を使う gtsfbro01path_base.h */
	this->memory_from_gui( nullptr/* Dirパスはメモリしない */ );

	/* GUIにpath設定 */
	this->change_level_dir( this->cp_memory() );

	/* GUIにlist表示 */
	if (OK != this->change_level_list() ) {
		pri_funct_err_bttvr(
	 "Error : this->change_level_list() returns NG");
		return NG;
	}

	return OK;
}
