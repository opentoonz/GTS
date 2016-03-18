#include <stdio.h>
#include <limits.h>	/* CHAR_BIT */

#include "ptbl_returncode.h"
#include "pri.h"
#include "iip_rot90.h"

void iip_rot90::_exec_bitbw( long l_width,long l_height, long l_in_sca_ch_size, unsigned char *ucharp_in, long l_out_scan_ch_size, unsigned char *ucharp_out )
{
	long	xx,yy,
		l_in_byte_pos,  l_in_bit_pos,  l_in_and_bit,
		l_out_byte_pos, l_out_bit_pos, l_out_and_bit, l_out_bit;
	unsigned char *ucharp_in_x, *ucharp_out_x;

	/* 元絵(ucharp_in)のbitから、カレント絵(ucharp_out)のbitとの
	orを取っているので、
	カレント絵(ucharp_out)はゼロクリアしなければいけない
	2005.07.12.tue */
	if (IIP_ROT_CLOCKWORK_090 != this->_e_clockwork) {
	for (yy = 0L; yy < l_height; ++yy) {
	for (xx = 0L; xx < l_out_scan_ch_size; ++xx) {
		ucharp_out[yy * l_out_scan_ch_size + xx] = 0;
	}
	}
	}

	if (IIP_ROT_CLOCKWORK_090 == this->_e_clockwork) {
	 ucharp_in += (l_height-1L)/CHAR_BIT;
	 for (yy = 0L; yy < l_height; ++yy) {
	  if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	  l_in_bit_pos  = (l_height-1L-yy)%CHAR_BIT;
	  l_in_and_bit  = 0x80>>l_in_bit_pos;
	  ucharp_in_x = ucharp_in;
	  ucharp_out_x = ucharp_out;
	  for (	xx=0L; xx < l_width; ++xx ) {
		l_out_bit_pos = xx%CHAR_BIT;
		l_out_and_bit = 0x80>>l_out_bit_pos;
		if ((*ucharp_in_x) & l_in_and_bit) {
			*ucharp_out_x |= l_out_and_bit;
		} else {
			*ucharp_out_x &= ~l_out_and_bit;
		}
		ucharp_in_x += l_in_sca_ch_size;
		if ((CHAR_BIT-1) == l_out_bit_pos) { ++ucharp_out_x; }
	  }
	  if (0 == l_in_bit_pos) { --ucharp_in; }
	  ucharp_out += l_out_scan_ch_size;
	 }
	} else if (IIP_ROT_CLOCKWORK_180 == this->_e_clockwork) {
	 for (yy = 0L; yy < l_height; ++yy) {
	  if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	  for (xx = 0L; xx < l_width; ++xx) {
		l_in_byte_pos = (l_width -1L-xx)/CHAR_BIT;
		l_in_bit_pos  = (l_width -1L-xx)%CHAR_BIT;
		l_out_byte_pos = xx/CHAR_BIT;
		l_out_bit_pos  = xx%CHAR_BIT;
		if (ucharp_in[
			(l_height-1L-yy)* l_in_sca_ch_size +
			l_in_byte_pos
		] & (0x80>>l_in_bit_pos)) {
			l_out_bit = 0x80>>l_out_bit_pos;
		} else {
			l_out_bit = 0;
		}
		ucharp_out[
			yy * l_out_scan_ch_size +
			l_out_byte_pos
		] |= l_out_bit;
	  }
	 }
	} else if (IIP_ROT_CLOCKWORK_270 == this->_e_clockwork) {
	 for (yy = 0L; yy < l_height; ++yy) {
	  if (ON == this->get_i_cv_sw()) { pri_funct_cv_run(yy); }
	  for (xx = 0L; xx < l_width; ++xx) {
		l_in_byte_pos = yy/CHAR_BIT;
		l_in_bit_pos  = yy%CHAR_BIT;
		l_out_byte_pos = xx/CHAR_BIT;
		l_out_bit_pos  = xx%CHAR_BIT;
		if (ucharp_in[
			(l_width-1L-xx) * l_in_sca_ch_size +
			l_in_byte_pos
		] & (0x80>>l_in_bit_pos)) {
			l_out_bit = 0x80>>l_out_bit_pos;
		} else {
			l_out_bit = 0;
		}
		ucharp_out[
			yy * l_out_scan_ch_size +
			l_out_byte_pos
		] |= l_out_bit;
	  }
	 }
	}
}
