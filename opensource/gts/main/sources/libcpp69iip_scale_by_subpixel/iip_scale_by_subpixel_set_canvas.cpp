#include "pri.h"
#include "iip_scale_by_subpixel.h"

int iip_scale_by_subpixel::set_canvas( void )
{
	iip_canvas *clpp;

	clpp = this->get_clp_parent();

	/* 親(元画像)がなくてはscaleができない */
	if (NULL == clpp) {
		pri_funct_err_bttvr(
			"Error : this->get_clp_parent() is NULL");
		return NG;
	}

	/* チャネル数が違うと処理できない */
	if (clpp->get_l_channels() != this->get_l_channels()) {
		pri_funct_err_bttvr(
		"Error : different channels <%ld> and <%ld>",
			clpp->get_l_channels(),
			this->get_l_channels()
		);
		return NG;
	}
	/* チャネルタイプが違うと処理できない */
	if (clpp->cl_ch_info.get_e_ch_num_type()
	!=  this->cl_ch_info.get_e_ch_num_type()) {
		pri_funct_err_bttvr(
		"Error : different channel type <%ld> and <%ld>",
			clpp->cl_ch_info.get_e_ch_num_type(),
			this->cl_ch_info.get_e_ch_num_type()
		);
		return NG;
	}
	/* チャネルタイプuchar,ushort以外の画像は処理できない */
	switch ( this->cl_ch_info.get_e_ch_num_type() ) {
	case E_CH_NUM_UCHAR:
	case E_CH_NUM_USHRT:
		break;
	case E_CH_NUM_ULONG:
	case E_CH_NUM_DOUBL:
	case E_CH_NUM_BITBW:
	case E_CH_NUM_EMPTY:
		pri_funct_err_bttvr(
	"Error : this->cl_ch_info.get_e_ch_num_type()<%d>",
			this->cl_ch_info.get_e_ch_num_type());
		return NG;
	}

	/* 同じ大きさなら(処理しないというユーザーの要求である)
	→ 親キャンバスを参照する(reference) */
	if (	(clpp->get_l_width() == this->get_l_width()) &&
		(clpp->get_l_height() == this->get_l_height())
	) {
		this->set_vp_reference_canvas(clpp->get_vp_canvas());
		return OK;
	}

	/* (メモリ確保の前に)以前のメモリを開放 */
	this->mem_free_incr_and_accum();
	this->mem_free_canvas();

	/* 処理するのでメモリ確保 */
	if (OK != this->mem_alloc_canvas()) {
		pri_funct_err_bttvr(
	 "Error : this->mem_alloc_canvas() returns NG");
		return NG;
	}
	if (OK != this->_mem_alloc_incr_and_accum()) {
		pri_funct_err_bttvr(
	 "Error : this->_mem_alloc_incr_and_accum() returns NG");
		return NG;
	}

	return OK;
}
