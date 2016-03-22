#include "pri.h"
#include "tw_win_l2_dss.h"

/* 画像レイアウト情報の表示 */
void tw_win_l2_dss::_imagelayout_pri(TW_IMAGELAYOUT *p_tw_imagelayout)
{
	TW_FIX32	*p_tw_fix32;
	double	d_val;

	pri_funct_msg_vr(
	"------ TW_IMAGELAYOUT ------" );

	pri_funct_msg_vr(
	"01/09 type      parameter        value : description");

	pri_funct_msg_vr(
	"02/09 TW_FRAME  Frame : Frame coords within larger document" );

	p_tw_fix32 = &(p_tw_imagelayout->Frame.Left);
	this->_fix32_to_double( p_tw_fix32, &d_val);
	pri_funct_msg_vr(
	"03/09 TW_FIX32  Frame.Left       %lf : (While %d,Frac %d)",
		d_val, p_tw_fix32->Whole, p_tw_fix32->Frac );

	p_tw_fix32 = &(p_tw_imagelayout->Frame.Top);
	this->_fix32_to_double( p_tw_fix32, &d_val);
	pri_funct_msg_vr(
	"04/09 TW_FIX32  Frame.Top        %lf : (While %d,Frac %d)",
		d_val, p_tw_fix32->Whole, p_tw_fix32->Frac );

	p_tw_fix32 = &(p_tw_imagelayout->Frame.Right);
	this->_fix32_to_double( p_tw_fix32, &d_val);
	pri_funct_msg_vr(
	"05/09 TW_FIX32  Frame.Right      %lf : (While %d,Frac %d)",
		d_val, p_tw_fix32->Whole, p_tw_fix32->Frac );

	p_tw_fix32 = &(p_tw_imagelayout->Frame.Bottom);
	this->_fix32_to_double( p_tw_fix32, &d_val);
	pri_funct_msg_vr(
	"06/09 TW_FIX32  Frame.Bottom     %lf : (While %d,Frac %d)",
		d_val, p_tw_fix32->Whole, p_tw_fix32->Frac );

	pri_funct_msg_vr(
	"07/09 TW_UINT32  DocumentNumber  %u",
		p_tw_imagelayout->DocumentNumber );
	pri_funct_msg_vr(
	"08/09 TW_UINT32  PageNumber      %u : Reset when you go to next document",
		p_tw_imagelayout->PageNumber );
	pri_funct_msg_vr(
	"09/09 TW_UINT32  FrameNumber     %u : Reset when you go to next page",
		p_tw_imagelayout->FrameNumber );
}
