#ifndef __ptbl_funct_h__
#define __ptbl_funct_h__

#ifdef __cplusplus
extern "C" {
#endif

/* CPUが、Little Endianなら1を返す、Big Endianならゼロを返す */
extern int ptbl_cpu_is_little_endian( void );

/* ディレクトリあるいはファイルが存在すれば 1 を、なければ 0 を返す */
extern int ptbl_dir_or_file_is_exist( char *cp_path );

/* ホスト名を得る、ホスト名が見つからないときはNULLを戻す */
extern char *ptbl_get_cp_hostname( void );

/* login名を得る(Windowsではログオン名)見つからないときはNULLを戻す */
extern char *ptbl_get_cp_loginname( void );

/* 現在のユーザー名を得る(CygwinではAdmin...)
   見つからないときはNULLを戻す */
extern char *ptbl_get_cp_username( void );

/* 現在のユーザー名を得る(CygwinではAdmin...)
   見つからないときはNULLを戻す */
extern char *ptbl_get_cp_userrealname( void );

/* ディレクトリを１個作成する(戻り値 0:成功,-1:失敗) */
extern int ptbl_mkdir( char *cp_dirpath );

/* ファイルパスからファイル名のみ得る(尻の.exe等は残る) */
extern char *ptbl_get_cp_filename_from_path( char *cp_filepath );

/* パスの区切り文字を得る(文字列の方が使いやすいので) */
extern char *ptbl_get_cp_path_separeter( void );

#ifdef __cplusplus
}
#endif

#endif /* !__ptbl_funct_h__ */
