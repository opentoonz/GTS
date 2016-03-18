#include <stdio.h>
#include "ptbl_funct.h"
#include "check_save.h"

/*
askモードの場合、ユーザーが保存の判断をする
(戻り値 0:上書き、1:cancel、2:all cancel) */
int check_save::_is_cancel( char *cp_fname )
{
	char	buf[8];
	int loop_infinity = 1;
	while (loop_infinity) {
		(void)fprintf(stdout,
			"\nfile<%s> is exist.\n", cp_fname);
		if (ON == this->_i_use_of_all_cancel_sw) {
			(void)fprintf(stdout,
			"overwrite?[y(yes)/n(cancel)/a(all cancel)] >> "
			);
		} else {
			(void)fprintf(stdout,
			"overwrite?[y(yes)/n(cancel)] >> ");
		}
		(void)fflush(stdout);

		buf[0] = '\0';
		fgets(buf, 8, stdin);

		/* 上書き保存 */
		if      ('y' == buf[0]) return 0;

		else if ('n' == buf[0]) {
			(void)fprintf(stdout, "cancel save<%s>\n",
				cp_fname);
			return 1;
		}
		else if ('a' == buf[0]) {
		 if (ON == this->_i_use_of_all_cancel_sw) {
			(void)fprintf(stdout, "all cancel.\n");
			return 2;
		 }
		}
		(void)fprintf(stdout,
			"\007 Bad answer... retry." );
	}
	return 3;
}

/*
ファイル保存チェック
戻り値はthis->_is_cancel(-)と同じ */
int check_save::cancel( char *cp_fname )
{
	/* まず、ファイルの存在を調べて... */
	if ( ptbl_dir_or_file_is_exist( cp_fname )) {
		/* ファイルが存在なら... */
		if (this->_is_skip_mode()) {
			/* skipモードの場合はcancelする */
			(void)fprintf(stdout, "skip save<%s>\n",
				cp_fname);
			(void)fflush(stdout);
			return 1;
		}
		else if (this->_is_ask_mode()) {
			/* askモードの場合はユーザー判断を返す */
			return this->_is_cancel(cp_fname);
		}
	}
	/* 新規保存or設定によるオーバーライト */
	return 0;
}

