#include "calcu_erase_dot_noise.h"
#include "iip_canvas.h"	/* CH_RED,CH_GRE,CH_BLU */

void calcu_erase_dot_noise::_setup_ip_equal(
	unsigned char *ucharp11,
	unsigned char *ucharp12,
	unsigned char *ucharp13,
	unsigned char *ucharp21,
	unsigned char *ucharp22,
	unsigned char *ucharp23,
	unsigned char *ucharp31,
	unsigned char *ucharp32,
	unsigned char *ucharp33,
	int	ip_equal[]
)
{
	unsigned long
		ul11,ul12,ul13,
		ul21,ul22,ul23,
		ul31,ul32,ul33;

	/* pixel値を数値化 */
	ul11 = (((unsigned long)ucharp11[CH_RED] << 16) |
		((unsigned long)ucharp11[CH_GRE] <<  8) |
		((unsigned long)ucharp11[CH_BLU]) );
	ul12 = (((unsigned long)ucharp12[CH_RED] << 16) |
		((unsigned long)ucharp12[CH_GRE] <<  8) |
		((unsigned long)ucharp12[CH_BLU]) );
	ul13 = (((unsigned long)ucharp13[CH_RED] << 16) |
		((unsigned long)ucharp13[CH_GRE] <<  8) |
		((unsigned long)ucharp13[CH_BLU]) );

	ul21 = (((unsigned long)ucharp21[CH_RED] << 16) |
		((unsigned long)ucharp21[CH_GRE] <<  8) |
		((unsigned long)ucharp21[CH_BLU]) );
	ul22 = (((unsigned long)ucharp22[CH_RED] << 16) |
		((unsigned long)ucharp22[CH_GRE] <<  8) |
		((unsigned long)ucharp22[CH_BLU]) );
	ul23 = (((unsigned long)ucharp23[CH_RED] << 16) |
		((unsigned long)ucharp23[CH_GRE] <<  8) |
		((unsigned long)ucharp23[CH_BLU]) );

	ul31 = (((unsigned long)ucharp31[CH_RED] << 16) |
		((unsigned long)ucharp31[CH_GRE] <<  8) |
		((unsigned long)ucharp31[CH_BLU]) );
	ul32 = (((unsigned long)ucharp32[CH_RED] << 16) |
		((unsigned long)ucharp32[CH_GRE] <<  8) |
		((unsigned long)ucharp32[CH_BLU]) );
	ul33 = (((unsigned long)ucharp33[CH_RED] << 16) |
		((unsigned long)ucharp33[CH_GRE] <<  8) |
		((unsigned long)ucharp33[CH_BLU]) );

	/* 中心と周りが同じ値か調べる */
	ip_equal[0] = (ul22 == ul11);
	ip_equal[1] = (ul22 == ul12);
	ip_equal[2] = (ul22 == ul13);
	ip_equal[3] = (ul22 == ul23);
	ip_equal[4] = (ul22 == ul33);
	ip_equal[5] = (ul22 == ul32);
	ip_equal[6] = (ul22 == ul31);
	ip_equal[7] = (ul22 == ul21);
}

void calcu_erase_dot_noise::_setup_ip_ucharp_histo(
	unsigned char *ucharp11,
	unsigned char *ucharp12,
	unsigned char *ucharp13,
	unsigned char *ucharp21,
	unsigned char *ucharp22,
	unsigned char *ucharp23,
	unsigned char *ucharp31,
	unsigned char *ucharp32,
	unsigned char *ucharp33,
	int	ip_equal[],
	int	ip_histo[],
	unsigned char *ucharpa_histo[]
)
{
	int	ii, jj;

	ucharp22;
	ip_equal;

	/* 回りの色を全てlistに設定 */
	ucharpa_histo[0] = ucharp11; ip_histo[0] = 1;
	ucharpa_histo[1] = ucharp12; ip_histo[1] = 1;
	ucharpa_histo[2] = ucharp13; ip_histo[2] = 1;
	ucharpa_histo[3] = ucharp23; ip_histo[3] = 1;
	ucharpa_histo[4] = ucharp33; ip_histo[4] = 1;
	ucharpa_histo[5] = ucharp32; ip_histo[5] = 1;
	ucharpa_histo[6] = ucharp31; ip_histo[6] = 1;
	ucharpa_histo[7] = ucharp21; ip_histo[7] = 1;

	/* 色の重複をまとめる(uniq) */
	for (ii = 0; ii < 8; ++ii) {
	 if (
		(0 < ip_histo[ii])	/* 自分が存在する */
	 ) {
	  for (jj = ii+1; jj < 8; ++jj) { /* 後ろと自身は見ない */
		if (
			(0 < ip_histo[jj]) &&	/* 相手が存在する */

			(ucharpa_histo[ii][CH_RED] ==
			 ucharpa_histo[jj][CH_RED]) &&
			(ucharpa_histo[ii][CH_GRE] ==
			 ucharpa_histo[jj][CH_GRE]) &&
			(ucharpa_histo[ii][CH_BLU] ==
			 ucharpa_histo[jj][CH_BLU]) /* 色が同じ */
		) {
			++ ip_histo[ii];	/* 自分にまとめる */
			ip_histo[jj] = 0;	/* 相手は消す */
		}
	  }
	 }
	}
}

int calcu_erase_dot_noise::_is_whiteblack(
	int	ip_histo[],
	unsigned char *ucharpa_histo[],
	unsigned char *ucharp22
)
{
	int	ii;

	/* 白地に黒の突起部分、黒地に白の突起部分は消さない */
	for (ii = 0; ii < 8; ++ii) {
		if (
			(0 < ip_histo[ii]) &&	/* 存在する */
			(
			 !((	(0xff == ucharpa_histo[ii][CH_RED]) &&
				(0xff == ucharpa_histo[ii][CH_GRE]) &&
				(0xff == ucharpa_histo[ii][CH_BLU])
			   ) || (
				(0x00 == ucharpa_histo[ii][CH_RED]) &&
				(0x00 == ucharpa_histo[ii][CH_GRE]) &&
				(0x00 == ucharpa_histo[ii][CH_BLU])
			 ))
			)
		) {
			break;	/* 色(白でも黒でもない)なら抜ける */
		}
	}
	/* 色がなく(上ループが最後までいった)、
	中心も色がないなら消さない */
	if (8 <= ii) {
		if ( (
			(0xff == ucharp22[CH_RED]) &&
			(0xff == ucharp22[CH_GRE]) &&
			(0xff == ucharp22[CH_BLU])
		) || (
			(0x00 == ucharp22[CH_RED]) &&
			(0x00 == ucharp22[CH_GRE]) &&
			(0x00 == ucharp22[CH_BLU])
		) ) {
			return 1;
		}
	}
	return 0;
}

unsigned char *calcu_erase_dot_noise::_get_ucharp_many_color(
	int	ip_equal[],
	int	ip_histo[],
	unsigned char *ucharpa_histo[]
)
{
	int	ii, i_count;
	unsigned char	*ucharp_tmp;

	/* 回りの色で、中心と違う、一番多い色で消す */
	/* 同じ回数現れた色は先にある色となる */
	i_count = 0;
	ucharp_tmp = NULL;
	for (ii = 0; ii < 8; ++ii) {
		if (
			(i_count < ip_histo[ii]) && /* 存在し、大きい */
			!ip_equal[ii]		/* 中心と違う色 */
		) {
			ucharp_tmp = ucharpa_histo[ii];
			i_count = ip_histo[ii];
		}
	}
	return ucharp_tmp;
}

unsigned char *calcu_erase_dot_noise::get_ucharp(
	unsigned char *ucharp11,
	unsigned char *ucharp12,
	unsigned char *ucharp13,
	unsigned char *ucharp21,
	unsigned char *ucharp22,
	unsigned char *ucharp23,
	unsigned char *ucharp31,
	unsigned char *ucharp32,
	unsigned char *ucharp33
)
{
	int	ii, i_count;
	int	ia_equal[8];
	int	ia_histo[8];
	unsigned char *ucharpa_histo[8];

	/* 中心と同じ値かどうか(周り色と)の比較を配列に設定 */
	this->_setup_ip_equal(
		ucharp11, ucharp12, ucharp13,
		ucharp21, ucharp22, ucharp23,
		ucharp31, ucharp32, ucharp33,
		ia_equal
	);

	/* 中心と同じ値のpixelの数をカウント */
	for (i_count = 0, ii = 0; ii < 8; ++ii) {
		if (ia_equal[ii]) { ++i_count; }
	}

	/* 判断1  中心と同じ値が3つ以上あると塗りつぶさない */
	if (3 <= i_count) { return NULL; }

	/* 判断2  周りとまったく違うなら塗りつぶす */
	if (i_count <= 0) {
		/* 周り色で(中心と違う)色のuniqリスト */
		this->_setup_ip_ucharp_histo(
			ucharp11, ucharp12, ucharp13,
			ucharp21, ucharp22, ucharp23,
			ucharp31, ucharp32, ucharp33,
			ia_equal,
			ia_histo,
			ucharpa_histo
		);
		/* 周り色で(中心と違う)一番多いものを返す */
		return this->_get_ucharp_many_color(
			ia_equal,
			ia_histo,
			ucharpa_histo);
	}

	/* 残るは、中心と同じ値がその周りに1,2個ある */

	/* 判断3  中心と同じ値が2個連続していると塗りつぶさない */
	for (ii = 0; ii < 8-1; ++ii) {
		if (ia_equal[ii] && ia_equal[ii+1]) { return NULL; }
	}
	if (ia_equal[7] && ia_equal[0]) { return NULL; }

	/* 周り色で(中心と違う)色のuniqリスト */
	this->_setup_ip_ucharp_histo(
		ucharp11, ucharp12, ucharp13,
		ucharp21, ucharp22, ucharp23,
		ucharp31, ucharp32, ucharp33,
		ia_equal,
		ia_histo,
		ucharpa_histo
	);

	/* 判断4  白地に黒の突起部分、黒地に白の突起部分は消さない */
	if (this->_is_whiteblack( ia_histo, ucharpa_histo, ucharp22 )) {
		return NULL;
	}

	/* 周り色で(中心と違う)一番多いものを返す */
	return this->_get_ucharp_many_color(
		ia_equal,
		ia_histo,
		ucharpa_histo);
}
