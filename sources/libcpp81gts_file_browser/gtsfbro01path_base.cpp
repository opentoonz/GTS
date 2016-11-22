#include <stdio.h>
#include <string.h> /* strcmp() */
#include <ctype.h> /* isdigit() */
#include "gtsfbro01path_base.h"

void gtsfbro01path_base::setup_path( const char *path )
{
	strncpy( this->_ca_path,   path, PTBL_PATH_MAX );
	strncpy( this->_ca_memory, path, PTBL_PATH_MAX );
	this->_ca_path[PTBL_PATH_MAX-1] = '\0';
	this->_ca_memory[PTBL_PATH_MAX-1] = '\0';
}
const char *gtsfbro01path_base::ccp_num4_and_ext(const char *ccp_file)
{
	size_t t_len;

	/* ".0000.tif"は9文字 */
	t_len = strlen(ccp_file);
	if (	(9 < t_len) &&
		(0 == strcmp(	this->get_save_imagefile_extension(),
				&(ccp_file[t_len-4]) )) &&
		isdigit(ccp_file[t_len-5]) &&
		isdigit(ccp_file[t_len-6]) &&
		isdigit(ccp_file[t_len-7]) &&
		isdigit(ccp_file[t_len-8]) &&
		('.' == ccp_file[t_len-9])
	) {
		return &(ccp_file[t_len-9]);
	}
	return NULL;
}

/* パスの部品を後ろにつなげていく
	1.結果の文字長さをチェックする
	2.文字列(ccp_src)頭にセパレータがあれば除いて追加する
		"/dir/" + "/filehead.0001.tif" -->
		"/dir/" +  "filehead.0001.tif" -->
					"/dir/filehead.0001.tif"
		""      +  "filehead.0001.tif" -->
					"filehead.0001.tif"
	3.結果文字列最後にはセパレータを付けないし、チェックもしない
*/
int gtsfbro01path_base::i_path_cat_part( const char *ccp_src, char *cp_dest, int i_dest_len )
{
	int i_src_len;

	/* メモリを指定しないなら、このクラスのinstanceメモリを使う */
	if (NULL == cp_dest) { cp_dest = this->_ca_path; }

	/* 1.文字長さをチェックする */
	i_src_len = strlen(cp_dest) + strlen(ccp_src);
	if (i_dest_len <= i_src_len) { /* 大きすぎ */
		pri_funct_err_bttvr(
			"Error : too long<%d> directroy path<%s>+<%s>",
			i_src_len,cp_dest,ccp_src);
		return NG;
	}

	/* 2.文字列頭にセパレータがあれば除いて追加する */
	if (	('/'  == ccp_src[0]) ||
		('\\' == ccp_src[0])
	) { ++ccp_src; }

	(void)strcat( cp_dest, ccp_src );

	/* 3.文字列最後にはセパレータを付けないし、チェックもしない */
	return OK;
}

/* 頭にディレクトリをドーンと置く
	1.dirパスがヌル文字列の場合、そのままヌル文字列とする
	2.文字長さをチェックする
	3.文字列最後にはセパレータを付ける
		"/dir"  --> "/dir/" : なければ付ける
		"/dir/" --> "/dir/" : あればそのまま
*/
int gtsfbro01path_base::i_path_cpy_dir( const char *ccp_src, char *cp_dest, int i_dest_len )
{
	int i_src_len, i_src_len_result;

	/* メモリを指定しないなら... */
	if (NULL == cp_dest) {
		/* このクラスのinstanceメモリを初期化する */
		this->v_path_dir_part_zero();
		this->v_path_dir_part_cutting();

		/* このクラスのinstanceメモリを使う */
		cp_dest = this->_ca_path;
	} else {
		cp_dest[0] = '\0';
	}

	/* コピーする文字列の長さを得る */
	i_src_len = strlen( ccp_src );

	/* 1.ヌル文字列の場合、ヌル文字列を設定する */
	if (i_src_len <= 0) {
		return OK;
	}

	/* 文字列最後にセパレータが... */
	if (	('/'  != ccp_src[i_src_len-1]) &&
		('\\' != ccp_src[i_src_len-1])
	) {
		i_src_len_result = i_src_len + 1; /* ない(後加) */
	} else {
		i_src_len_result = i_src_len;     /* ある */
	}

	/* 2.文字長さをチェックする */
	if (i_dest_len <= i_src_len_result) { /* 大きすぎ */
		pri_funct_err_bttvr(
			"Error : too long<%d> directroy path<%s>",
			i_src_len_result,ccp_src);
		return NG;
	}

	/* dir pathをコピーする */
	(void)strcpy( cp_dest, ccp_src );

	/* 3.文字列最後にセパレータがなければ付ける */
	if (i_src_len < i_src_len_result) {
		(void)strcat( cp_dest, "/" );
	}

	/* 格納したディレクトリパス文字列の大きさをメモリする */
	this->_i_dir_part_length = i_src_len_result;

	return OK;
}

/* ファイル名からその頭名を、後ろにつなげる
	1.文字列(ccp_src)頭にセパレータがあれば除く
		"/dir/" + "/filehead.0001.tif" -->
		"/dir/" +  "filehead.0001.tif" --> "/dir/filehead
	2.ファイル名のヘッド部分の認識
	 指示がない(OFF==i_file_head_cut_sw)あるいは、
	 文字列(ccp_src)に(.0000.tif)がない場合、
	 全体をヘッドとみなす
	 "/dir/" + "file.head.0001.tif" --> "/dir/file.head.0001.tif"
	 "/dir/" + "file.head"          --> "/dir/file.head"
	 指示があり(ON==i_file_head_cut_sw)
	 文字列(ccp_src)に(.0000.tif)がある場合、
	 ヘッド部分を分離し切り出す
	 "/dir/" + "file.head.0001.tif" --> "/dir/file.head"
	 "/dir/" + "file.head"          --> "/dir/file.head"
	3.結果の文字長さをチェックする
	4.結果の文字列最後にはセパレータを付けないしチェックもしない
*/
int gtsfbro01path_base::i_path_cat_head( const char *ccp_src, int i_file_head_cut_sw, char *cp_dest, int i_dest_len )
{
	int ii,i_len;
	const char *ccp_head_sepa;

	/* メモリを指定しないなら、このクラスのinstanceメモリを使う */
	if (NULL == cp_dest) { cp_dest = this->_ca_path; }

	/* 1.文字列頭にセパレータがあれば除いて追加する */
	if (	('/'  == ccp_src[0]) ||
		('\\' == ccp_src[0])
	) { ++ccp_src; }

	/* 2.ファイル名のヘッド部分の認識
	 指示がない(OFF==i_file_head_cut_sw)あるいは、
	 文字列(ccp_src)に(.0000.tif)がない場合、
	 全体をヘッドとみなす */
	ccp_head_sepa = this->ccp_num4_and_ext(ccp_src);
	if (	(OFF == i_file_head_cut_sw) ||
		(NULL == ccp_head_sepa)
	) {
		i_len = strlen(cp_dest) + strlen(ccp_src);
		/* 3.文字長さをチェックする */
		if (i_dest_len <= i_len) { /* 大きすぎ */
			pri_funct_err_bttvr(
			"Error : too long<%d> directroy path<%s>+<%s>",
			i_len,cp_dest,ccp_src);
			return NG;
		}
		(void)strcat( cp_dest, ccp_src );
		return OK;
	}

	/* ヘッド部分のみをコピー */
	i_len = strlen(cp_dest);
	for (ii = 0; ccp_head_sepa != &(ccp_src[ii]); ++ii, ++i_len) {
		/* 3.文字長さをチェックする */
		if (i_dest_len <= (i_len+1)) { /* 大きすぎ */
			pri_funct_err_bttvr(
			"Error : too long<%d> directroy path<%s>",
				i_len+1, cp_dest
			);
			return NG;
		}
		cp_dest[i_len] = ccp_src[ii];
		cp_dest[i_len+1] = '\0';
	}

	/* 4.文字列最後にはセパレータを付けないし、チェックもしない */
	return OK;
}

/* 番号を4桁のゼロ詰めにして、後ろにつなげる
	例: "/dir/file" + 1  = "/dir/file.0001"
*/
int gtsfbro01path_base::i_path_cat_pad4( int i_num, char *cp_dest, int i_dest_len )
{
	char ca6_tmp[6];

	(void)snprintf( ca6_tmp,6, ".%04d", i_num );

	if (OK != this->i_path_cat_part(ca6_tmp,cp_dest,i_dest_len)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_part(%s,%s,%d) returns NG",
			ca6_tmp,cp_dest,i_dest_len );
		return NG;
	}

	return OK;
 }

/* ------------------------------------------------------ */

/*	現在ディレクトリ(ccp_dir)と
	現在ファイル(ccp_file)と
	カレント拡張子(ccp_ext)から、pathを生成する

	現在ファイル(ccp_file)は必ず必要。

	現在ディレクトリ(ccp_dir)と
	カレント拡張子(ccp_ext)はNULLの場合も正常処理する。
*/
int gtsfbro01path_base::i_path_dir_file( const char *ccp_dir, const char *ccp_file, const char *ccp_ext )
{
	char	*cp_tmp;

	if (OK != this->i_path_cpy_dir( ccp_dir )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG.", ccp_dir );
		return NG;
	}

	if ( (NULL == ccp_file) || ('\0' == ccp_file[0]) ) {
		pri_funct_err_bttvr("Error : ccp_file is nothing");
		return NG;
	}

	if (OK != this->i_path_cat_part( ccp_file )) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_part(%s) returns NG.", ccp_file );
		return NG;
	}

	/* 拡張子の指定なし(NULL)ならこれでpath完成 */
	if (NULL == ccp_ext) { return OK; }

	cp_tmp = strrchr( this->_ca_path, '.' );
	/* 拡張子がないか、ccp_ext(".tif"等)と違うとき追加する */
	if ((NULL == cp_tmp) || strcmp( cp_tmp, ccp_ext )) {
		if (OK != this->i_path_cat_part( ccp_ext )) {
			pri_funct_err_bttvr(
		 "Error : this->i_path_cat_part(%s) returns NG.",
				ccp_ext
			);
			return NG;
		}
	}

	return OK;
}

/* 現在ディレクトリ(ccp_dir)から下(ccp_down_dir)へ
 例1: "/dir"  + "file.0001.tif"  -->
 例2: "/dir"  + "/file.0001.tif" -->
 例3: "/dir/" + "file.0001.tif"  -->
 例4: "/dir/" + "/file.0001.tif" -->
 例1〜4は全て
      "/dir/" + "file.0001.tif" = "/dir/file.0001.tif"
 と直して処理するのでOKです。

	注：パスの最後にはセパレータがつかない
		例: "/dir" + "subdir" --> "/dir/subdir"
*/
int gtsfbro01path_base::i_path_dir_down( const char *ccp_dir, const char *ccp_down_dir )
{
	if (OK != this->i_path_cpy_dir(
			ccp_dir
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG.",
			ccp_dir
		);
		return NG;
	}

	if (OK != this->i_path_cat_part(
			ccp_down_dir
	)) {
		pri_funct_err_bttvr(
	 "Error : this->i_path_cat_part(%s) returns NG.",
			ccp_down_dir
		);
		return NG;
	}

	return OK;
}

/* 現在ディレクトリ(ccp_dir)から上へ
	注：パスの最後にはセパレータがつかない
		例1: "/dir/subdir"  --> "/dir"
		例2: "/dir/subdir/" --> "/dir"
*/
int gtsfbro01path_base::i_path_dir_up( const char *ccp_dir )
{
	int i_len;
	char *cp_dest, *cp_unix, *cp_dos;

	/* dirパスをセットする、文字列の最後に'/'が付く */
	if (OK != this->i_path_cpy_dir(
			ccp_dir
	)) {

		pri_funct_err_bttvr(
	 "Error : this->i_path_cpy_dir(%s) returns NG.",
			ccp_dir
		);
		return NG;
	}

	/* このクラスのinstanceメモリを使う */
	cp_dest = this->_ca_path;

	/* パスが1文字より大きくて、最後にセパレータ文字があり、
	"C:/"等でないとき、最後のセパレータ文字を消す */
	i_len = strlen(cp_dest);
	if (	(1 < i_len) &&
		(	('/'  == cp_dest[i_len-1]) ||
			('\\' == cp_dest[i_len-1])
		)
	) {
		/* for Windows path */
		if ((3 != i_len) || (':' != cp_dest[1])) {
			cp_dest[i_len-1] = '\0';
		}
	}

	/* ディレクトリパスの最後からセパレータ文字を探す */
	cp_unix = strrchr( cp_dest, '/'  );
	cp_dos  = strrchr( cp_dest, '\\' );

	/* セパレータ文字が一つだけ存在する
		"/data" --> "/"   --> "/"
		"C:/Users" --> "C:/"   --> "C:/"
	*/
	if (	(
			(NULL!=cp_unix) &&
			(strchr(cp_dest,'/' )==cp_unix)
		) || (
			(NULL!=cp_dos ) &&
			(strchr(cp_dest,'\\')==cp_dos )
		)
	) {
		/* セパレータ文字が文字列の最後の文字のとき */
		/* rootまでいってしまっているので上がらない */
		if (	('\\' == cp_dest[strlen(cp_dest)-1]) ||
			('/' == cp_dest[strlen(cp_dest)-1])
		) {
			/* 格納したDirパス文字列の大きさをメモリする */
			this->_i_dir_part_length = strlen(cp_dest);
			return OK;
		}
		/* 最後のDir Upでrootへ */
		else {
			if (NULL != cp_unix) { ++cp_unix; }
			if (NULL != cp_dos) { ++cp_dos; }
		}
	}

	/* UNIX用とDOS用両方が見つかってしまった場合 */
	if ((NULL != cp_unix) && (NULL != cp_dos)) {
		if (cp_unix < cp_dos) {	cp_dos[0]  = '\0'; }
		else                  { cp_unix[0] = '\0'; }
	}

	/* UNIX用のみ見つけた場合 */
	else if (NULL != cp_unix) { cp_unix[0] = '\0'; }

	/* DOS用のみ見つけた場合 */
	else if (NULL != cp_dos) { cp_dos[0] = '\0'; }

	/* UNIX用もDOS用も見つからなかった場合何もしない */

	/* 格納したディレクトリパス文字列の大きさをメモリする */
	this->_i_dir_part_length = strlen(cp_dest);

	return OK;
}

/* 指定の設定を記憶する */
void gtsfbro01path_base::v_path_memory( const char *ccp )
{
	if (NULL != ccp) { strcpy( this->_ca_memory, ccp ); }
}
/* 現在の設定を記憶する */
void gtsfbro01path_base::v_path_memory( void )
{
	/* this->_ca_pathがnullパス("")でもOK */
	strcpy( this->_ca_memory, this->_ca_path );
}

char *gtsfbro01path_base::cp_memory( void )
{
	/* nullパス("")の場合もあり */
	return this->_ca_memory;
}


void gtsfbro01path_base::add_imagefile_extension( const std::string& ext )
{
	this->imagefile_extensions_.push_back( ext );
}
const char* gtsfbro01path_base::get_save_imagefile_extension( void ) const
{
	return this->imagefile_extensions_.at(
		this->current_save_imagefile_extension_
	).c_str();
}
const char* gtsfbro01path_base::get_open_imagefile_extension( void ) const
{
	return this->imagefile_extensions_.at(
		this->current_open_imagefile_extension_
	).c_str();
}
const int gtsfbro01path_base::get_current_save_imagefile_extension( void ) const
{
	return this->current_save_imagefile_extension_;
}
const int gtsfbro01path_base::get_current_open_imagefile_extension( void ) const
{
	return this->current_open_imagefile_extension_;
}
void gtsfbro01path_base::set_current_save_imagefile_extension(
	const int current
)
{
	if (
	 current < 0 ||
	 static_cast<int>(this->imagefile_extensions_.size()) <= current
	) {
		return;
	}
	this->current_save_imagefile_extension_ = current;
}
void gtsfbro01path_base::set_current_open_imagefile_extension(
	const int current
)
{
	if (
	 current < 0 ||
	 static_cast<int>(this->imagefile_extensions_.size()) <= current
	) {
		return;
	}
	this->current_open_imagefile_extension_ = current;
}
