#ifndef gtsfbro01path_base_h
#define gtsfbro01path_base_h

#include <stdio.h> /* NULL */
#include <vector>
#include <string>

#if defined _WIN32
#define	snprintf _snprintf	/* For MS-C v12.00 */
#endif

#include "ptbl_path_max.h" /* PTBL_PATH_MAX(=4096) */
#include "ptbl_returncode.h"
#include "pri.h"

class gtsfbro01path_base {
public:
	gtsfbro01path_base()
		/*,imagefile_extensions_({ ".tif" ,".tga" })*/
		:_i_dir_part_length(0)
		,current_imagefile_extension_(0)
	{
#if defined _WIN32
		strcpy( this->_ca_path   ,"C:/" );
		strcpy( this->_ca_memory ,"C:/" );
#else
		strcpy( this->_ca_path   ,"/" );
		strcpy( this->_ca_memory ,"/" );
#endif
	}

	/* アプリ立ち上げ時の初期設定で使う */
	void setup_path( const char *path );


	const char* get_imagefile_extension( void ) const;
	void add_imagefile_extension( const std::string& ext );
	const int get_current_imagefile_extension( void ) const;
	void set_current_imagefile_extension( const int current );

protected:
	/* ファイル名が数字と拡張子をもったものかどうか調べる */
	const char *ccp_num4_and_ext(const char *ccp_file);

	/* ディレクトリとファイル名と拡張子からファイルパスを作る */
	int i_path_dir_file( const char *ccp_dir, const char *ccp_file,
		const char *ccp_ext = NULL );

	/* 現在ディレクトリ(ccp_dir)から下(ccp_down_dir)へ */
	int i_path_dir_down( const char *ccp_dir, const char *ccp_down_dir );

	/* 現在ディレクトリ(ccp_dir)から上へ */
	int i_path_dir_up( const char *ccp_dir );

	void v_path_dir_part_zero( void ) {
		this->_i_dir_part_length = 0;
	}
	void v_path_dir_part_cutting( void ) {
		this->_ca_path[this->_i_dir_part_length] = '\0';
	}

	void v_path_memory( void );
	void v_path_memory( const char *ccp );

	char *cp_memory( void );

	/* できたパスを見る、あるいは別途加工する */
	char *cp_path( void ) { return this->_ca_path; }

	/* ---------------------------------------------- */

	/* 頭にディレクトリをドーンと置く */
	int i_path_cpy_dir( const char *ccp_src,
		char *cp_dest = NULL, int i_dest_len = PTBL_PATH_MAX );

	/* パスの部品を後ろにつなげていく */
	int i_path_cat_part( const char *ccp_src,
		char *cp_dest = NULL, int i_dest_len = PTBL_PATH_MAX );

	/* ファイル名からその頭名を、後ろにつなげる */
	int i_path_cat_head( const char *ccp_src,
		int i_all_cat_sw=OFF,
		char *cp_dest=NULL, int i_dest_len=PTBL_PATH_MAX );

	/* 番号を4桁のゼロ詰めにして、後ろにつなげる */
	int i_path_cat_pad4( int i_num,
		char *cp_dest = NULL, int i_dest_len = PTBL_PATH_MAX );

	/* 拡張子はブラウザーからの選択指定なのでここでは指定しない */

private:
	/* 上記各methodでここにpath設定 */
	char _ca_path[PTBL_PATH_MAX];

	int _i_dir_part_length;

	/* GUIのCancel復帰用 */
	char _ca_memory[PTBL_PATH_MAX];

	std::vector<std::string> imagefile_extensions_;/* ここでは入れ物、継承後のインスタンス時に値をセットする */
	int current_imagefile_extension_;
};

#endif /* !gtsfbro01path_base_h */
/*
classの継承 2016-05-18

class gtsfbro01path_base {
class gtsfbro02list_base : public gtsfbro01path_base {
class gtsfbro03list_gui : public gtsfbro02list_base {
class gtsfbro04path_level : public gtsfbro03list_gui {
class gtsfbro04text_gui : public gtsfbro03list_gui {
class gtsfbro05list_config : public gtsfbro04text_gui {
class gtsfbro05list_level : public gtsfbro04path_level {
class gtsfbro05list_trace_batch : public gtsfbro04text_gui {
class gtsfbro06cb_level : public gtsfbro05list_level {
class gtsfbro06cb_config : public gtsfbro05list_config {
class gtsfbro06cb_trace_batch : public gtsfbro05list_trace_batch {

---

classの継承図 2016-05-18

gtsfbro01path_base
+-- gtsfbro02list_base
    +-- gtsfbro03list_gui
	+-- gtsfbro04path_level
	|   +-- gtsfbro05list_level
	|       +-- gtsfbro06cb_level		Level
	+-- gtsfbro04text_gui
	    +-- gtsfbro05list_config
	    |   +-- gtsfbro06cb_config		Config
	    +-- gtsfbro05list_trace_batch
	        +-- gtsfbro06cb_trace_batch	TraceBatch

---

imagefile_extension調査 2016-05-18

gtsfbro01path_base::i_path_cat_head(-)
gtsfbro02list_base::e_dir_or_file_type(-)
gtsfbro06cb_level::_rename_file_tif(-)
+-- gtsfbro01path_base::ccp_num4_and_ext(-)
    +-- get_imagefile_extension()

gtsfbro04path_level::i_lpath_cat_file_by_num(-)
gtsfbro04path_level::i_lpath_cat_file_for_full(-)
gtsfbro04path_level::i_lpath_cpy_head_means_level(-)
+-- gtsfbro01path_base::i_path_cat_head(-)

+-- gtsfbro02list_base::e_dir_or_file_type(-)
*/
