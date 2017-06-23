/*
	ファイル名格納用の一時保管バッファの大きさとして、
	FILENAME_MAXを使いたいが、HP-UXにて14である等、
	各システムで値が違っており統一性がなく、使えない。
	代わりの定義(PTBL_FILE_PATH_BUF_MAX)をしておく
	(2005-01-05)

	ファイルパス格納用の一時保管バッファの大きさとして、
	PATH_MAX,_POSIX_PATH_MAXがあるが、
	各システムで値が違っており統一性がない
	(2005-10-07)

	代わりの定義(PTBL_FILE_PATH_BUF_MAX)を、
	PTBL_PATH_MAXに変更。
	(2005-10-13)
*/

#if 0	/* ここから〜値を決めるための参考 */
Redhat9
/usr/include/stdio.h --> /usr/include/bits/stdio_lim.h
#define FILENAME_MAX 4096

WindowsXp
/cygdrive/c/Program\ Files/Microsoft\ Visual\ Studio/VC98/Include/STDIO.H
#define FILENAME_MAX    260

IRIX6.5.x
/usr/include/stdio.h
#define FILENAME_MAX    1024

HP-UX B.11.11 U
/usr/include/stdio.h
#define FILENAME_MAX    14
*/

Redhat9
/usr/include/linux/limits.h
#define PATH_MAX       4096 /* # chars in a path name */
/usr/include/bits/posix1_lim.h
#define _POSIX_PATH_MAX 256 /* Number of bytes in a pathname. */

WindowsXp (注意)-D_POSIX_オプションが必要
C:\Program Files\Microsoft Visual Studio\VC98\Include\LIMITS.H
#define PATH_MAX        512
#define _POSIX_PATH_MAX 255

HP-UX B.11.11 U
/usr/include/limits.h
#define PATH_MAX    1023    /* max number of characters in a pathname (not including terminating null) */
#define _POSIX_PATH_MAX 255 /* The number of bytes in a pathname */

Windows7 64bit(2017-06-23)
VC2013
+-- C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\include\stdlib.h
    +-- #define _MAX_PATH   260 // max. length of full pathname
パスの長さの制限は最大260文字(終端含む)となっている...らしい

Windows NT系(2017-06-23)
(Windows NT〜Windows 8.1)は
フルパス約32,767文字まで対応、がアプリが対応してない場合がある
#endif	/* 値を決めるための参考〜ここまで */

#ifndef PTBL_PATH_MAX
#define PTBL_PATH_MAX 4096
#endif
