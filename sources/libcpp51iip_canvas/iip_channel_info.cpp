#include <limits.h>	/* CHAR_BIT */
#include "pri.h"
#include "iip_channel_info.h"

/*
 * チャンネル
 */
void iip_channel_info::set_e_ch_num_type( E_CH_NUM_TYPE e_type )
{
	switch (e_type) {
	case E_CH_NUM_EMPTY:
		this->_l_bytes = -1L;
		this->_l_bits = 0L;
		this->_e_num_form = E_NUM_INTEGER;
		break;
	case E_CH_NUM_UCHAR:
		this->_l_bytes = sizeof(unsigned char);
		this->_l_bits = this->_l_bytes * CHAR_BIT;
		this->_e_num_form = E_NUM_INTEGER;
		break;
	case E_CH_NUM_USHRT:
		this->_l_bytes = sizeof(unsigned short);
		this->_l_bits = this->_l_bytes * CHAR_BIT;
		this->_e_num_form = E_NUM_INTEGER;
		break;
	case E_CH_NUM_ULONG:
		this->_l_bytes = sizeof(unsigned long);
		this->_l_bits = this->_l_bytes * CHAR_BIT;
		this->_e_num_form = E_NUM_INTEGER;
		break;
	case E_CH_NUM_DOUBL:
		this->_l_bytes = sizeof(double);
		this->_l_bits = this->_l_bytes * CHAR_BIT;
		this->_e_num_form = E_NUM_FLOATING;
		break;
	case E_CH_NUM_BITBW:
		this->_l_bytes = 0L;
		this->_l_bits = 1L;
		this->_e_num_form = E_NUM_INTEGER;
		break;
	}

	this->_e_type = e_type;
}

E_CH_NUM_TYPE iip_channel_info::get_e_ch_num_type( void )
{
	return this->_e_type;
}

/* get_cp_ch_num_type()は、関数のオーバーロードやってます。
注意事項：デフォルト引数は使ってはいけません、
	  どっちの関数を呼んだのか区別がつかなくなります。
*/
const char *iip_channel_info::get_cp_ch_num_type( E_CH_NUM_TYPE e_type )
{
	switch (e_type) {
	case E_CH_NUM_UCHAR: return "u_char";
	case E_CH_NUM_USHRT: return "u_short";
	case E_CH_NUM_ULONG: return "u_long";
	case E_CH_NUM_DOUBL: return "double";
	case E_CH_NUM_BITBW: return "bit_bw";
	case E_CH_NUM_EMPTY: return "empty";
	}
	return "empty"; /* for MS-C(Version 12.00.8804) warning */

}
const char *iip_channel_info::get_cp_ch_num_type( void )
{
	return this->get_cp_ch_num_type(
		this->get_e_ch_num_type() );
}

int iip_channel_info::chk_e_ch_num_type( void )
{
	int	i_ret = OK,
		i_bad_bits = OK,
		i_bad_form = OK;

	switch (this->_e_type) {
	case E_CH_NUM_UCHAR:
	case E_CH_NUM_USHRT:
	case E_CH_NUM_ULONG:
		if (this->_l_bytes * CHAR_BIT != this->_l_bits) {
			i_bad_bits = NG; i_ret = NG; }
		if (E_NUM_INTEGER != this->_e_num_form) {
			i_bad_form = NG; i_ret = NG; }
		break;
	case E_CH_NUM_DOUBL:
		if (this->_l_bytes * CHAR_BIT != this->_l_bits) {
			i_bad_bits = NG; i_ret = NG; }
		if (E_NUM_FLOATING != this->_e_num_form) {
			i_bad_form = NG; i_ret = NG; }
		break;
	case E_CH_NUM_BITBW:
		if (1L != this->_l_bits) {
			i_bad_bits = NG; i_ret = NG; }
		if (E_NUM_INTEGER != this->_e_num_form) {
			i_bad_form = NG; i_ret = NG; }
		break;
	case E_CH_NUM_EMPTY:
		pri_funct_err_bttvr(
			"Error : bad %ld bytes... empty settting",
			this->_l_bytes
		);
		i_ret = NG;
		break;
	default:
		pri_funct_err_bttvr(
			"Error : bad %ld bytes, bad programmer",
			this->_l_bytes
		);
		i_ret = NG;
		break;
	}

	if (NG == i_bad_bits) {
		pri_funct_err_bttvr(
			"Error : bad %ld bits at %ld bytes",
			this->_l_bits,
			this->_l_bytes
		);
	}
	if (NG == i_bad_form) {
		pri_funct_err_bttvr(
			"Error : bad e_num_form %ld at %ld bytes",
			this->_e_num_form,
			this->_l_bytes
		);
	}

	return i_ret;
}
