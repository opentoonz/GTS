#include "pri.h"
#include "tw_win_l2_dss.h"

void tw_win_l2_dss::_imageinfo_pri( TW_IMAGEINFO *p_tw_imageinfo )
{
	TW_FIX32	*p_tw_fix32;
	double	d_val;

	pri_funct_msg_vr(
	"------ TW_IMAGEINFO ------" );

	pri_funct_msg_vr(
	"01/12 type      parameter        value : description");

	p_tw_fix32 = &(p_tw_imageinfo->XResolution);
	this->_fix32_to_double( p_tw_fix32, &d_val );

	pri_funct_msg_vr(
	"02/12 TW_FIX32  XResolution      %lf : (While %d,Frac %d)",
		d_val, p_tw_fix32->Whole, p_tw_fix32->Frac );

	p_tw_fix32 = &(p_tw_imageinfo->YResolution);
	this->_fix32_to_double( p_tw_fix32, &d_val );

	pri_funct_msg_vr(
	"03/12 TW_FIX32  YResolution      %lf : (While %d,Frac %d)",
		d_val, p_tw_fix32->Whole, p_tw_fix32->Frac );

	pri_funct_msg_vr(
	"04/12 TW_INT32  ImageWidth       %d",
		p_tw_imageinfo->ImageWidth );
	pri_funct_msg_vr(
	"05/12 TW_INT32  ImageLength      %d : height",
		p_tw_imageinfo->ImageLength );
	pri_funct_msg_vr(
	"06/12 TW_INT16  SamplesPerPixel  %d",
		p_tw_imageinfo->SamplesPerPixel );
	pri_funct_msg_vr(
	"07/12 TW_INT16  BitsPerSample[8] %d %d %d %d %d %d %d %d",
		p_tw_imageinfo->BitsPerSample[0],
		p_tw_imageinfo->BitsPerSample[1],
		p_tw_imageinfo->BitsPerSample[2],
		p_tw_imageinfo->BitsPerSample[3],
		p_tw_imageinfo->BitsPerSample[4],
		p_tw_imageinfo->BitsPerSample[5],
		p_tw_imageinfo->BitsPerSample[6],
		p_tw_imageinfo->BitsPerSample[7]
	);
	pri_funct_msg_vr(
	"08/12         : Number of bits for each sample" );
	pri_funct_msg_vr(
	"09/12 TW_INT16  BitsPerPixel     %d",
		p_tw_imageinfo->BitsPerPixel );
	pri_funct_msg_vr(
	"10/12 TW_BOOL   Planar           %d : TRUE is Planar,FALSE is chunky",
		p_tw_imageinfo->Planar );
	pri_funct_msg_vr(
	"11/12 TW_INT16  PixelType        %d : TWPT_XXXX",
		p_tw_imageinfo->PixelType );
	pri_funct_msg_vr(
	"12/12 TW_UINT16 Compression      %d : TWCP_XXXX",
		p_tw_imageinfo->Compression );
}
