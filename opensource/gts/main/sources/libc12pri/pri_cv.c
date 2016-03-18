#include <stdio.h>
#include "pri.h"

static int32_t	pri_param_i32_ysize,
		pri_param_i32_pos_before;

/* カウントダウン開始 */
void pri_funct_cv_start( int32_t i32_ys )
{
	/* 目盛表示 */
	(void)fprintf(stdout,
	"0%%  10   20   30   40   50   60   70   80   90   100%%\n" );
	(void)fprintf(stdout,
	"....v....v....v....v....v....v....v....v....v....v\n" );

	/* パラメータ初期設定 */
	pri_param_i32_ysize = i32_ys;
	pri_param_i32_pos_before = 0;
}
/* カウントダウン実行中 */
void pri_funct_cv_run( int32_t i32_y )
{
	int32_t	i32_pos_current, ii;

	/* 目盛上の現在位置(1...50) */
	i32_pos_current = 50 * (i32_y + 1) / pri_param_i32_ysize;

	/* 一回で45度くるくるカウンター */
	/******switch (i32_y%4) {
	case 0: (void)fprintf(stdout, "-\b"  ); break;
	case 1: (void)fprintf(stdout, "\\\b" ); break;
	case 2: (void)fprintf(stdout, "|\b"  ); break;
	case 3: (void)fprintf(stdout, "/\b"  ); break;
	}
	(void)fflush(stdout);******/

	/* 一回前の目盛位置と同じなら抜ける */
	if (i32_pos_current == pri_param_i32_pos_before) return;

	/* 目盛が進んだとき */
	for (ii = pri_param_i32_pos_before; ii<i32_pos_current; ++ii) {
		/* 一目盛以上進んだときのすき間 */
		if ((ii + 1) < i32_pos_current) {
			(void)fprintf(stdout, "." );
		}
		/* 一目盛分 */
		else {
			(void)fprintf(stdout, "^" );
		}
	}
	(void)fflush(stdout);

	/* 現在位置を記憶する */
	pri_param_i32_pos_before = i32_pos_current;
}
/* カウントダウン終了 */
void pri_funct_cv_end( void )
{
	/* 改行 */
	(void)fprintf(stdout, "\n" );
}

