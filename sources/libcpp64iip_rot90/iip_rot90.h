#ifndef iip_rot90_h
#define iip_rot90_h

#include <cstring>	/* memcpy() */
#include "iip_canvas.h"

typedef enum {
	IIP_ROT_CLOCKWORK_000,
	IIP_ROT_CLOCKWORK_090,
	IIP_ROT_CLOCKWORK_180,
	IIP_ROT_CLOCKWORK_270,
}	IIP_ROT_CLOCKWORK_PER_90;

/*
処理したら true しない場合 false を返す
T is unsigned char , unsigned short , unsigned long , float , double
monoBW(bits)については別処理
*/
template <typename T>
bool fx_rot90_image_(
	const int width , const int height , const int channels
	, const T* inn , const IIP_ROT_CLOCKWORK_PER_90 cwp90 , T* out
) {
	switch (cwp90) {
	case IIP_ROT_CLOCKWORK_000:
		if ( inn != nullptr && out != nullptr && inn != out ) {
			memcpy(	 static_cast<void *>(out)
				,static_cast<const void *>(inn)
				,width*height*channels*sizeof(T) );
		} else { return false; }
		break;
	case IIP_ROT_CLOCKWORK_090:
		for (int yy = 0 ; yy < height ; ++yy) {
		for (int xx = 0 ; xx < width ; ++xx) {
		for (int zz = 0 ; zz < channels ; ++zz) {
		 out[	yy * channels * width +
			xx * channels +
			zz
		 ]=inn[	xx * channels * height +
			(height - 1 - yy) * channels +
			zz
		 ];
		} } }
		break;
	case IIP_ROT_CLOCKWORK_180:
		for (int yy = 0 ; yy < height ; ++yy) {
		for (int xx = 0 ; xx < width ; ++xx) {
		for (int zz = 0 ; zz < channels ; ++zz) {
		 out[	yy * channels * width +
			xx * channels +
			zz
		 ]=inn[ (height - 1 - yy) * channels * width +
			(width  - 1 - xx) * channels +
			zz
		 ];
		} } }
		break;
	case IIP_ROT_CLOCKWORK_270:
		for (int yy = 0 ; yy < height ; ++yy) {
		for (int xx = 0 ; xx < width ; ++xx) {
		for (int zz = 0 ; zz < channels ; ++zz) {
		 out[	yy * channels * width +
			xx * channels +
			zz
		 ]=inn[	(width - 1 - xx) * channels * height +
			yy * channels +
			zz
		 ];
		} } }
		break;
	}
	return true;
}

class iip_rot90 : public iip_canvas {
public:
	iip_rot90()
	{
		this->set_ccp_object_name_of_mv("iip_rot90");
		this->cwp90_ = IIP_ROT_CLOCKWORK_000;
	}

	void set_clockwork_000(void) { this->cwp90_=IIP_ROT_CLOCKWORK_000; }
	void set_clockwork_090(void) { this->cwp90_=IIP_ROT_CLOCKWORK_090; }
	void set_clockwork_180(void) { this->cwp90_=IIP_ROT_CLOCKWORK_180; }
	void set_clockwork_270(void) { this->cwp90_=IIP_ROT_CLOCKWORK_270; }

	/* cwp90_の設定に合わせて画像サイズを回転する */
	void rot_canvas_size( void );

	/* 画像サイズよりメモリーを確保 */
	int set_canvas( void );

	/* 回転実行 */
	void exec( void );

private:
	IIP_ROT_CLOCKWORK_PER_90	cwp90_;

/*	void _exec_bitbw( long l_width,long l_height, long l_in_sca_ch_size, unsigned char *ucharp_in, long l_out_scan_ch_size, unsigned char *ucharp_out );
	void _exec_uchar( long l_width,long l_height,long l_channels, unsigned char *ucharp_in, unsigned char *ucharp_out );
	void _exec_ushrt( long l_width,long l_height,long l_channels, unsigned short *ushrtp_in, unsigned short *ushrtp_out );
	void _exec_ulong( long l_width,long l_height,long l_channels, unsigned long *ulongp_in, unsigned long *ulongp_out );
	void _exec_doubl( long l_width,long l_height,long l_channels, double *doublp_in, double *doublp_out );*/
};

#endif /* !iip_rot90_h */
