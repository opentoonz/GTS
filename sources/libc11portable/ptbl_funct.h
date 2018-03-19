#ifndef __ptbl_funct_h__
#define __ptbl_funct_h__

#ifdef __cplusplus
extern "C" {
#endif

/* ディレクトリあるいはファイルが存在すれば 1 を、なければ 0 を返す */
extern int ptbl_dir_or_file_is_exist( char *cp_path );

/* ホスト名を得る、ホスト名が見つからないときはNULLを戻す */
extern char *ptbl_get_cp_hostname( void );

/* 現在のユーザー名を得る
	(unixではlogin名ではない場合あり)
	(CygwinではAdmin...)
   見つからないときはNULLを戻す */
extern char *ptbl_get_cp_username( void );

#if defined _WIN32
/* Windowsでファイルアクセルするときのパス名の日本語文字コードの変換 */
/* 戻り値は内部static文字配列なのでスレッドセーフではない */
char* ptbl_charcode_cp932_from_utf8(const char* utf8);
#endif   // _WIN32

#ifdef __cplusplus
}
#endif

#endif /* !__ptbl_funct_h__ */
