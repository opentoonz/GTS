#ifndef _iip_rot90_h_
#define _iip_rot90_h_

#include "iip_canvas.h"

typedef enum {
IIP_ROT_CLOCKWORK_000,
IIP_ROT_CLOCKWORK_090,
IIP_ROT_CLOCKWORK_180,
IIP_ROT_CLOCKWORK_270,
} IIP_ROT_CLOCKWORK_PER_90;

class iip_rot90 : public iip_canvas {
public:
	iip_rot90()
	{
		this->set_ccp_object_name_of_mv("iip_rot90");
		this->_e_clockwork = IIP_ROT_CLOCKWORK_000;
	}

	void set_clockwork_000( void ) {
	this->_e_clockwork =
	 IIP_ROT_CLOCKWORK_000; }

	void set_clockwork_090( void ) {
	this->_e_clockwork =
	 IIP_ROT_CLOCKWORK_090; }

	void set_clockwork_180( void ) {
	this->_e_clockwork =
	 IIP_ROT_CLOCKWORK_180; }

	void set_clockwork_270( void ) {
	this->_e_clockwork =
	 IIP_ROT_CLOCKWORK_270; }

	/* _e_clockworkの設定に合わせて画像サイズを回転する */
	void rot_canvas_size( void );

	/* 画像サイズよりメモリーを確保 */
	int set_canvas( void );

	/* 回転実行 */
	void exec( void );

private:
	IIP_ROT_CLOCKWORK_PER_90	_e_clockwork;

	void _exec_bitbw( long l_width,long l_height, long l_in_sca_ch_size, unsigned char *ucharp_in, long l_out_scan_ch_size, unsigned char *ucharp_out );
	void _exec_uchar( long l_width,long l_height,long l_channels, unsigned char *ucharp_in, unsigned char *ucharp_out );
	void _exec_ushrt( long l_width,long l_height,long l_channels, unsigned short *ushrtp_in, unsigned short *ushrtp_out );
	void _exec_ulong( long l_width,long l_height,long l_channels, unsigned long *ulongp_in, unsigned long *ulongp_out );
	void _exec_doubl( long l_width,long l_height,long l_channels, double *doublp_in, double *doublp_out );
};

#endif /* !_iip_rot90_h_ */
