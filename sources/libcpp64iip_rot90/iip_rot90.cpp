#include <climits>	/* CHAR_BIT */
#include "ptbl_returncode.h"	/* NG,OK */
#include "pri.h"		/* pri_funct_err_bttvr(-) */
#include "iip_rot90.h"

namespace {

bool fx_rot90_image_bitbw_(
	const int width , const int height
	, const int in_sl_ch_size , const unsigned char *inn
	, const IIP_ROT_CLOCKWORK_PER_90 cwp90
	, const int out_sl_ch_size , unsigned char *out )
{
	/* 元絵(inn)のbitから、カレント絵(out)のbitとの
	orを取っているので、
	カレント絵(out)はゼロクリアしなければいけない
	2005.07.12.tue */
	memset( static_cast<void *>(out) ,0 ,height * out_sl_ch_size );

	switch (cwp90) {
	case IIP_ROT_CLOCKWORK_000:
		if ( inn != nullptr && out != nullptr && inn != out) {
			memcpy(  static_cast<void *>(out)
				,static_cast<const void *>(inn)
				,width*height
	*((in_sl_ch_size<out_sl_ch_size)? in_sl_ch_size :out_sl_ch_size));
		} else { return false; }
		break;
	case IIP_ROT_CLOCKWORK_090:
		inn += (height-1)/CHAR_BIT;
		for ( int yy = 0; yy < height; ++yy ) {
			int in_bit_pos  = (height-1-yy)%CHAR_BIT;
			int in_and_bit  = 0x80>>in_bit_pos;
			const unsigned char *ucharp_in_x = inn;
			unsigned char *ucharp_out_x = out;
		 for ( int xx = 0; xx < width; ++xx ) {
			int out_bit_pos = xx%CHAR_BIT;
			int out_and_bit = 0x80>>out_bit_pos;
			if ((*ucharp_in_x) & in_and_bit) {
				*ucharp_out_x |= out_and_bit;
			} else {
				*ucharp_out_x &= ~out_and_bit;
			}
			ucharp_in_x += in_sl_ch_size;
			if ((CHAR_BIT-1) == out_bit_pos) { ++ucharp_out_x; }
		 }
		 if (0 == in_bit_pos) { --inn; }
		 out += out_sl_ch_size;
		}
		break;
	case IIP_ROT_CLOCKWORK_180:
		for ( int yy = 0; yy < height; ++yy ) {
		for ( int xx = 0; xx < width; ++xx ) {
			int in_byte_pos  = (width -1-xx)/CHAR_BIT;
			int in_bit_pos   = (width -1-xx)%CHAR_BIT;
			int out_byte_pos = xx/CHAR_BIT;
			int out_bit_pos  = xx%CHAR_BIT;
			int out_bit = 0;
			if (inn[
				(height-1-yy)* in_sl_ch_size +
				in_byte_pos
			] & (0x80>>in_bit_pos)) {
				out_bit = 0x80>>out_bit_pos;
			}
			out[
				yy * out_sl_ch_size +
				out_byte_pos
			] |= out_bit;
		}
		}
		break;
	case IIP_ROT_CLOCKWORK_270:
		for ( int yy = 0; yy < height; ++yy ) {
		for ( int xx = 0; xx < width; ++xx ) {
			int in_byte_pos  = yy/CHAR_BIT;
			int in_bit_pos   = yy%CHAR_BIT;
			int out_byte_pos = xx/CHAR_BIT;
			int out_bit_pos  = xx%CHAR_BIT;
			int out_bit = 0;
			if (inn[
				(width-1-xx) * in_sl_ch_size +
				in_byte_pos
			] & (0x80>>in_bit_pos)) {
				out_bit = 0x80>>out_bit_pos;
			}
			out[
				yy * out_sl_ch_size +
				out_byte_pos
			] |= out_bit;
		}
		}
		break;
	}
	return true;
}

} // namespace

int iip_rot90::set_canvas( void )
{
	/* 画像メモリは独立していなければいけません */
	if (OK != this->mem_alloc_canvas()) {
		pri_funct_err_bttvr(
	 "Error : this->mem_alloc_canvas() returns NG." );
		return NG;
	}

	return OK;
}

/* 元サイズ(w,h,c,type)を設定してから実行(rot_canvas_size())すること */
void iip_rot90::rot_canvas_size( void )
{
	long	l_val;

	switch (this->cwp90_) {
	case IIP_ROT_CLOCKWORK_000:
		break;
	case IIP_ROT_CLOCKWORK_090:
		l_val = this->get_l_width();
		this->set_l_width( this->get_l_height() );
		this->set_l_height( l_val );
		break;
	case IIP_ROT_CLOCKWORK_180:
		break;
	case IIP_ROT_CLOCKWORK_270:
		l_val = this->get_l_width();
		this->set_l_width( this->get_l_height() );
		this->set_l_height( l_val );
		break;
	}
}

void iip_rot90::exec( void )
{
	iip_canvas	*clpp = this->get_clp_parent();

	/*
	ユーザーによるノーアクションの指定、つまりゼロ度回転
	の時は処理せず、親をコピーする */
	if (IIP_ROT_CLOCKWORK_000 == this->cwp90_) {
		(void)memcpy(
			this->get_vp_canvas(),
			clpp->get_vp_canvas(),
			this->get_l_height() *
			this->get_l_channels() *
			this->get_l_scanline_channel_bytes() );
		return;
	}

	switch ( this->cl_ch_info.get_e_ch_num_type() ) {
	case E_CH_NUM_UCHAR:
		(void)fx_rot90_image_(
			this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
			,static_cast<unsigned char *>(clpp->get_vp_canvas())
			,this->cwp90_
			,static_cast<unsigned char *>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_USHRT:
		(void)fx_rot90_image_(
			this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
		,static_cast<unsigned short *>(clpp->get_vp_canvas())
			,this->cwp90_
		,static_cast<unsigned short *>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_ULONG:
		(void)fx_rot90_image_(
			this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
			,static_cast<unsigned long *>(clpp->get_vp_canvas())
			,this->cwp90_
			,static_cast<unsigned long *>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_FLOAT:
		(void)fx_rot90_image_(
			this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
			,static_cast<float *>(clpp->get_vp_canvas())
			,this->cwp90_
			,static_cast<float *>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_DOUBL:
		(void)fx_rot90_image_(
			this->get_l_width()
			,this->get_l_height()
			,this->get_l_channels()
			,static_cast<double *>(clpp->get_vp_canvas())
			,this->cwp90_
			,static_cast<double *>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_BITBW:
		(void)fx_rot90_image_bitbw_(
			this->get_l_width()
			,this->get_l_height()
			,clpp->get_l_scanline_channel_bytes()
			,static_cast<unsigned char *>(clpp->get_vp_canvas())
			,this->cwp90_
			,this->get_l_scanline_channel_bytes()
			,static_cast<unsigned char *>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_EMPTY:
		break; /* for no warning */
	}
}
