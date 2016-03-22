#include "pri.h"
#include "tw_win_l4_scan.h"

/* DIB(Device Independent Bitmap) */
void iip_scan::_pri_bitmapinfoheader( BITMAPINFOHEADER *tp_bmih )
{
	pri_funct_msg_ttvr(
	"BITMAPINFOHEADER ..." );
	pri_funct_msg_vr(
	" DWORD biSize         %d : must be 40(0x28)",
		tp_bmih->biSize );
	pri_funct_msg_vr(
	" LONG biWidth         %d",
		tp_bmih->biWidth );
	pri_funct_msg_vr(
	" LONG biHeight        %d",
		tp_bmih->biHeight );
	pri_funct_msg_vr(
	" WORD biPlanes        %d : must be 1",
		tp_bmih->biPlanes );
	pri_funct_msg_vr(
	" WORD biBitCount      %d : 1,4,8,16,24,32",
		tp_bmih->biBitCount );
	pri_funct_msg_vr(
	" DWORD biCompression  %d : 0(dump),1(rle8),2(rle4)",
		tp_bmih->biCompression );
	pri_funct_msg_vr(
	" DWORD biSizeImage    %d : for compression",
		tp_bmih->biSizeImage );
	pri_funct_msg_vr(
	" LONG biXPelsPerMeter %d : Pixel/Meter",
		tp_bmih->biXPelsPerMeter );
	pri_funct_msg_vr(
	" LONG biYPelsPerMeter %d : Pixel/Meter",
		tp_bmih->biYPelsPerMeter );
	pri_funct_msg_vr(
	" DWORD biClrUsed      %d",
		tp_bmih->biClrUsed );
	pri_funct_msg_vr(
	" DWORD biClrImportant %d",
		tp_bmih->biClrImportant );
}

void iip_scan::_pri_rgbquad_table( int i_count, RGBQUAD *tp_bmic )
{
	int	ii;

	pri_funct_msg_vr( "color table %d", i_count );
	for (ii = 0; ii < i_count; ++ii) {
		pri_funct_msg_vr(
			" %03d/%03d R %3d G %3d B %3d Reserved %3d",
			ii, i_count,
			tp_bmic[ii].rgbRed,
			tp_bmic[ii].rgbGreen,
			tp_bmic[ii].rgbBlue,
			tp_bmic[ii].rgbReserved
		);
	}
}

void iip_scan::_pri_rgbquad( BITMAPINFO *tp_bmi )
{
	BITMAPINFOHEADER *tp_bmih;

	tp_bmih = &(tp_bmi->bmiHeader);

	switch (tp_bmih->biBitCount) {
	case 1:
	case 4:
	case 8:
		this->_pri_rgbquad_table(
			(1<<(tp_bmih->biBitCount)),
			tp_bmi->bmiColors );
		break;
	}
}
