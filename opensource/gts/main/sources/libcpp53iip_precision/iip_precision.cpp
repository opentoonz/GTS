#include <stdlib.h>
#include <string.h>	/* memcpy() */
#include <math.h>
#include <assert.h>

#include "ptbl_returncode.h"
#include "pri.h"
#include "iip_precision.h"
#include "calcu_precision.h"

int iip_precision::set_canvas( void )
{
	iip_canvas *clpp;

	clpp = this->get_clp_parent();

	/* pixelのchannel設定のチェック */
	if (OK != clpp->cl_ch_info.chk_e_ch_num_type()) {
		pri_funct_err_bttvr(
	 "Error : clpp->cl_ch_info.chk_e_ch_num_type() returns NG" );
		return NG;
	}
	if (OK != this->cl_ch_info.chk_e_ch_num_type()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_ch_info.chk_e_ch_num_type() returns NG" );
		return NG;
	}

	/* 片方のみモノクロ２階調の画像は
	BW --> unsigned char Grayscaleを除いて処理できない
	両方モノクロ２階調の画像なら変換せず参照する
	*/
	if ((E_CH_NUM_BITBW == clpp->cl_ch_info.get_e_ch_num_type())
	&&  (E_CH_NUM_BITBW != this->cl_ch_info.get_e_ch_num_type())
	&&  (E_CH_NUM_UCHAR != this->cl_ch_info.get_e_ch_num_type())
	) {
		pri_funct_err_bttvr(
 "Error : only clpp->cl_ch_info.get_e_ch_num_type() is E_CH_NUM_BITBW");
		return NG;
	}
	if ((E_CH_NUM_BITBW != clpp->cl_ch_info.get_e_ch_num_type())
	&&  (E_CH_NUM_BITBW == this->cl_ch_info.get_e_ch_num_type())) {
		pri_funct_err_bttvr(
 "Error : only this->cl_ch_info.get_e_ch_num_type() is E_CH_NUM_BITBW");
		return NG;
	}

	/* 精度変化なし → 親キャンバスを参照(reference) */
	if (clpp->cl_ch_info.get_e_ch_num_type()
	==  this->cl_ch_info.get_e_ch_num_type()) {
		this->set_vp_reference_canvas(clpp->get_vp_canvas());
	}

	/* 精度変化あり → 親キャンバスからの変換(mem_alloc-->exec) */
	else {
		if (OK != this->mem_alloc_canvas()) {
			pri_funct_err_bttvr(
			"Error : this->mem_alloc_canvas() returns NG");
			return NG;
		}
	}

	return OK;
}

void iip_precision::exec( void )
{
	iip_canvas	*clpp;
	long	l_width,
		l_height,
		l_ch;
	long	xx,yy,zz;
	unsigned char	*ucharp_i=0, *ucharp_o=0;
	unsigned short	*ushrtp_i=0, *ushrtp_o=0;
	unsigned long	*ulongp_i=0, *ulongp_o=0;
	double		*doublp_i=0, *doublp_o=0;
	double	d_max_i,
		d_max_o,
		d_val = 0;
	unsigned long	ul_val;
	E_CH_NUM_TYPE	e_ch_num_type_i,
			e_ch_num_type_o;
	calcu_precision	cl_prec;

	clpp = this->get_clp_parent();

	/* 精度変化なし → 親キャンバスを参照(reference)しているはず */
	if (clpp->cl_ch_info.get_e_ch_num_type()
	==  this->cl_ch_info.get_e_ch_num_type()) {
		return;
	}

	/* Method表示 */
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr( "%s : execute",
			this->get_ccp_object_name_of_mv()
		);
	}
	/* Parameter表示 */
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr( " sampling %s --> %s",
			clpp->cl_ch_info.get_cp_ch_num_type(),
			this->cl_ch_info.get_cp_ch_num_type()
		);
	}

	l_width = this->get_l_width();
	l_height = this->get_l_height();
	l_ch = this->get_l_channels();
	e_ch_num_type_i = clpp->cl_ch_info.get_e_ch_num_type();
	e_ch_num_type_o = this->cl_ch_info.get_e_ch_num_type();

	/* モノクロ２階調から、unsigned char grayscaleへの変換 */
	if ((E_CH_NUM_BITBW == clpp->cl_ch_info.get_e_ch_num_type())
	&&  (E_CH_NUM_UCHAR == this->cl_ch_info.get_e_ch_num_type())) {
		/* Parameter表示 */
		if (ON == this->get_i_pv_sw()) {
			pri_funct_msg_ttvr(
				" sampling 1bits  --> 8bits" );
		}
		this->_bw_to_uchargray(
			l_width, l_height,
			cl_prec.bytes_to_max( sizeof(unsigned char) ),
			(unsigned char *)clpp->get_vp_canvas(),
			(unsigned char *)this->get_vp_canvas()
		);
		return;	/* ここで終り */
	}

	/* 画像キャンバスの型別ポインターセット */
	switch (e_ch_num_type_i) {
	case E_CH_NUM_UCHAR:
		      ucharp_i =
	     (unsigned char *)clpp->get_vp_canvas(); break;
	case E_CH_NUM_USHRT:
		      ushrtp_i =
	     (unsigned short *)clpp->get_vp_canvas(); break;
	case E_CH_NUM_ULONG:
		      ulongp_i =
	     (unsigned long *)clpp->get_vp_canvas(); break;
	case E_CH_NUM_DOUBL:
		      doublp_i =
		     (double *)clpp->get_vp_canvas(); break;
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	switch (e_ch_num_type_o) {
	case E_CH_NUM_UCHAR:
		      ucharp_o =
	     (unsigned char *)this->get_vp_canvas(); break;
	case E_CH_NUM_USHRT:
		      ushrtp_o =
	     (unsigned short *)this->get_vp_canvas(); break;
	case E_CH_NUM_ULONG:
		      ulongp_o =
	     (unsigned long *)this->get_vp_canvas(); break;
	case E_CH_NUM_DOUBL:
		      doublp_o =
		     (double *)this->get_vp_canvas(); break;
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	/* 型別の最大値の設定 */
	d_max_i = (double)cl_prec.bytes_to_max(
			clpp->cl_ch_info.get_l_bytes()
	);
	d_max_o = cl_prec.max_to_double( cl_prec.bytes_to_max(
			this->cl_ch_info.get_l_bytes()
	) );

	/* Parameter表示 */
	if (ON == this->get_i_pv_sw()) {
		pri_funct_msg_ttvr(
		" sampling i_max_in<%.16g> --> d_max_out<%.16g>",
			d_max_i, d_max_o
		);
	}

	/* カウントダウン表示始め */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_start(l_height); }

	for (yy = 0L; yy < l_height; ++yy) {
	 /* カウントダウン表示中 */
	 if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	 for (xx = 0L; xx < l_width; ++xx) {
	  for (zz = 0L; zz < l_ch; ++zz) {

		switch (e_ch_num_type_i) {
		case E_CH_NUM_UCHAR:
		    d_val = (*ucharp_i)/d_max_i;
			    ++ucharp_i; break;
		case E_CH_NUM_USHRT:
		    d_val = (*ushrtp_i)/d_max_i;
			    ++ushrtp_i; break;
		case E_CH_NUM_ULONG:
		    d_val = (*ulongp_i)/d_max_i;
			    ++ulongp_i; break;
		case E_CH_NUM_DOUBL:
		    d_val = (*doublp_i);
			    ++doublp_i; break;
		case E_CH_NUM_BITBW: break; /* for no warning */
		case E_CH_NUM_EMPTY: break; /* for no warning */
		}

		ul_val = cl_prec.dbl_to_ul_by_dmax( d_val, d_max_o );

		switch (e_ch_num_type_o) {
		case E_CH_NUM_UCHAR:
			     *ucharp_o = (unsigned char)ul_val;
			    ++ucharp_o; break;
		case E_CH_NUM_USHRT:
			     *ushrtp_o = (unsigned short)ul_val;
			    ++ushrtp_o; break;
		case E_CH_NUM_ULONG:
			     *ulongp_o = (unsigned long)ul_val;
			    ++ulongp_o; break;
		case E_CH_NUM_DOUBL:
			     *doublp_o = d_val;
			    ++doublp_o; break;
		case E_CH_NUM_BITBW: break; /* for no warning */
		case E_CH_NUM_EMPTY: break; /* for no warning */
		}
	  }
	 }
	}

	/* カウントダウン表示終了 */
	if (ON == this->get_i_cv_sw()) { pri_funct_cv_end(); }

	return;
}
