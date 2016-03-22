#include "pri.h"
#include "calcu_erase_dot_noise.h"
#include "iip_erase_dot_noise.h"

void iip_erase_dot_noise::_exec_uchar( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned char *ucharp_in, unsigned char *ucharp_out )
{
	long	l_start, l_scansize;
	long	xx,yy;
	unsigned char	*ucharp_in_y1,*ucharp_in_y2,*ucharp_in_y3;
	unsigned char	*ucharp_in_x11,*ucharp_in_x12,*ucharp_in_x13,
			*ucharp_in_x21,*ucharp_in_x22,*ucharp_in_x23,
			*ucharp_in_x31,*ucharp_in_x32,*ucharp_in_x33;
	unsigned char	*ucharp_out_y1,*ucharp_out_y2;
	unsigned char	*ucharp_out_x1,*ucharp_out_x2;
	unsigned char	*ucharp_tmp;

	calcu_erase_dot_noise	cl_dot;

	l_height;

	/* 初期値 */
	l_scansize = l_width * l_channels;
	l_start = l_area_ypos * l_scansize + l_area_xpos * l_channels;
	ucharp_in += l_start;
	ucharp_out += l_start;

	/* 縦方向ポインター初期化 */
	ucharp_in_y1 = ucharp_in;
	ucharp_in_y2 = ucharp_in_y3 = NULL;
	ucharp_out_y1 = ucharp_out;
	ucharp_out_y2 = NULL;

	/* 縦方向ループ */
	for (yy = 0L; yy < l_area_ysize; ++yy,
	 /* 縦方向の3連ポインター進める */
	 ucharp_in_y3 = ucharp_in_y2,
	 ucharp_in_y2 = ucharp_in_y1,
	 ucharp_in_y1 += l_scansize,
	 ucharp_out_y2 = ucharp_out_y1,
	 ucharp_out_y1 += l_scansize
	) {

	 /* カウントダウン表示中 */
	 if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }

	 /* 3連満ちるまで */
	 if (NULL == ucharp_in_y3) { continue; }

	 /* 横方向ポインター初期化 */
	 ucharp_in_x11 = ucharp_in_y1;
	 ucharp_in_x12 = ucharp_in_x13 = NULL;
	 ucharp_in_x21 = ucharp_in_y2;
	 ucharp_in_x22 = ucharp_in_x23 = NULL;
	 ucharp_in_x31 = ucharp_in_y3;
	 ucharp_in_x32 = ucharp_in_x33 = NULL;
	 ucharp_out_x1 = ucharp_out_y2;
	 ucharp_out_x2 = NULL;

	 /* 横方向ループ */
	 for (xx = 0L; xx < l_area_xsize; ++xx,
		/* 横方向の3x3連ポインター進める */
		ucharp_in_x33 = ucharp_in_x32,
		ucharp_in_x32 = ucharp_in_x31,
		ucharp_in_x31 += l_channels,
		ucharp_in_x23 = ucharp_in_x22,
		ucharp_in_x22 = ucharp_in_x21,
		ucharp_in_x21 += l_channels,
		ucharp_in_x13 = ucharp_in_x12,
		ucharp_in_x12 = ucharp_in_x11,
		ucharp_in_x11 += l_channels,
		ucharp_out_x2 = ucharp_out_x1,
		ucharp_out_x1 += l_channels
	 ) {
		/* 3連満ちるまで */
		if (NULL == ucharp_in_x13) { continue; }

		/* dotをつぶすか判断 */
		ucharp_tmp = cl_dot.get_ucharp(
			ucharp_in_x11,ucharp_in_x12,ucharp_in_x13,
			ucharp_in_x21,ucharp_in_x22,ucharp_in_x23,
			ucharp_in_x31,ucharp_in_x32,ucharp_in_x33
		);

		/* dotをつぶす */
		if (NULL != ucharp_tmp) {
			ucharp_out_x2[CH_RED] = ucharp_tmp[CH_RED];
			ucharp_out_x2[CH_GRE] = ucharp_tmp[CH_GRE];
			ucharp_out_x2[CH_BLU] = ucharp_tmp[CH_BLU];
		}
	 }
	}
}
