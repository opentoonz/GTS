#ifndef __ptbl_funct_h__
#define __ptbl_funct_h__

#ifdef __cplusplus
extern "C" {
#endif

/* ディレクトリあるいはファイルが存在すれば 1 を、なければ 0 を返す */
extern int ptbl_dir_or_file_is_exist( char *cp_path );

#if defined _WIN32
/* Windowsでファイルアクセルするときのパス名の日本語文字コードの変換 */
/* 戻り値は内部static文字配列なのでスレッドセーフではない */
char* ptbl_charcode_cp932_from_utf8(const char* utf8);
#endif   // _WIN32

#ifdef __cplusplus
}
#endif

#endif /* !__ptbl_funct_h__ */
