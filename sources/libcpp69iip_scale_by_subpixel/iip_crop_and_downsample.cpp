#include <iostream>
#include <cassert>
#include "iip_crop_and_downsample.h"
#include "calcu_bresenham.cpp"

namespace {

/* child画像1pixelに対するparent画像1pixelのサンプリング数(subpixel)を返す */
int calcu_subpixel_division_(
	const int subp_min_div	/* 縮小(DownSample)時のサンプル最小数 */
	,const int subp_max_div /* 縮小(DownSample)時のサンプル最大数 */
	,const int parent_in
	,const int child_out
)
{
	/* どちらか大きさがないときは無効 */
	if ((parent_in <= 0) || (child_out <= 0)) {
		return -1;
	}
	/* 等倍 : 大きさが等しいときはsubpixelは1を返す */
	else if (parent_in == child_out) {
		return 1;
	}
	/* 拡大 : child_outのほうが解像度高いとき */
	else if (parent_in < child_out) {
		/* 拡大はニアレストネイバー法とする */
		return 1;
	}

	/* 縮小(DownSample) : child_outのほうが解像度低いとき(これが主) */

	/* 縮小が整数倍のときはその比
	   縮小が整数倍でないときは比を超える最小の整数地 */
	const int sp =
		((parent_in%child_out)==0)
		?(parent_in/child_out)
		:(parent_in/child_out+1);

	/* 縮小時のsubpixel数は範囲内にする */
	if (sp < subp_min_div) { return subp_min_div; }
	if (subp_max_div < sp) { return subp_max_div; }

	return sp;
}

/* 処理エンジン部分 */
template <class T>
void engine_(
	const T *in_image
	, const int out_width
	, const int out_height
	, const int out_channels
	, const int x_subpixel
	, const int y_subpixel
	, const int* array_x /* out_width*x_subpixel個 */
	, const int* array_y /* out_height*y_subpixel個 */
	, int* array_sl/* out_width*out_channels個 */
	, T *out_image
)
{
	const int xy_subpixel = y_subpixel * x_subpixel;

	/* 縦方向へ出力画像pixel毎移動 */
	for (int yy = 0; yy < out_height; ++yy) {
	    /* subpixel値の積算値をscanline積算配列へ */
	    for (int ys = 0; ys < y_subpixel; ++ys) {
		/* 縦のsubpixel毎にscanlineを積算する */
		const T* image_in_x = in_image; /* 入力画像Scanline位置 */
		int* array_sl_it = array_sl; /* 積算位置リセット */
		const int* array_x_it = array_x;

		/* 横方向へ出力画像pixel毎移動 */
		for (int xx = 0; xx < out_width; ++xx) {
		    /* 横方向へ出力画像のsubpixel毎移動 */
		    for (int xs = 0; xs < x_subpixel; ++xs) {
			/* 深さ方向の積算 */
			for (int zz = 0; zz < out_channels; ++zz) {
				array_sl_it[zz] += image_in_x[zz];/* 積算 */
			}
			image_in_x += *array_x_it; /* 入力画像横方向進め */
			++array_x_it;
		    }
		    array_sl_it += out_channels; /* 積算位置進め */
		}
		in_image += *array_y; /* 入力画像Scanline位置進め */
		++array_y;
	    }

	    /* scanline積算配列から画像配列へ移し変え */
	    int* array_sl_it = array_sl;
	    for (int xx = 0; xx < out_width; ++xx) {
		for (int zz = 0; zz < out_channels; ++zz) {
			*out_image = static_cast<T>(
				(*array_sl_it) / xy_subpixel
			);
			++out_image;
			*array_sl_it = 0; /* 次の積算ループのための初期化 */
			++array_sl_it;
		}
	    }
	}
}

} // namespace

bool iip_crop_and_downsample::reserve_max_memory(
	const int max_w
	,const int max_h
	,const int max_ch /* pa_chとの整合性!!!!!!!!!!!!!!!! */
	,const int max_by /* pa_chとの整合性!!!!!!!!!!!!!!!! */
)
{
	if (max_w  <= 0) { return true; }
	if (max_h  <= 0) { return true; }
	if (max_ch <= 0) { return true; }
	if (max_by <= 0) { return true; }

	this->max_w_  = max_w;
	this->max_h_  = max_h;
	this->max_ch_ = max_ch;
	this->max_by_ = max_by;

	this->array_x_.resize( max_w * this->subpixel_max_div_ );
	this->array_y_.resize( max_h * this->subpixel_max_div_ );
	this->array_sl_.resize( max_w * max_ch );
	this->child_out.resize( max_h * max_w * max_ch * max_by );

	return false;
}
void iip_crop_and_downsample::set_subpixel_min_div( const int subpixel_min_div )
{
	this->subpixel_min_div_ = subpixel_min_div;
}
void iip_crop_and_downsample::set_subpixel_max_div( const int subpixel_max_div )
{
	this->subpixel_max_div_ = subpixel_max_div;
}
int iip_crop_and_downsample::set_mapping(
	void *parent_data
	,const int pa_w , const int pa_h
	,const int pa_ch ,const int pa_by /* 元(parent)画像のデータサイズ */
	,const int pa_xo ,const int pa_yo
	,const int pa_xs ,const int pa_ys /* 元(parent)からの切取範囲 */
	,const int xs ,const int ys/* 結果画像の大きさ */
)
{
	/* 親(元)画像があるか */
	if (parent_data == nullptr) { return 1; }
	if (pa_w  <= 0) { return 2; }
	if (pa_h  <= 0) { return 3; }
	if (pa_ch <= 0) { return 4; }
	if (pa_by <= 0) { return 5; }

	/* 親画像からはみ出してないか */
	if ( pa_xo < 0 ) {  return 6; }
	if ( pa_yo < 0 ) {  return 7; }
	if ( pa_w  < (pa_xo + pa_xs) ) { return 8; }
	if ( pa_h < (pa_yo + pa_ys) ) { return 9; }

	/* 子画像の最大範囲内か */
	if ( this->max_w_ < xs ) { return 10; }
	if ( this->max_h_ < ys ) { return 11; }

	/* アンチエイリアスのためのサンプリング数(subpixel)をセット */
	const int x_subpixel = calcu_subpixel_division_(
		 this->subpixel_min_div_
		,this->subpixel_max_div_
		,pa_xs
		,xs
	);
	const int y_subpixel = calcu_subpixel_division_(
		 this->subpixel_min_div_
		,this->subpixel_max_div_
		,pa_ys
		,ys
	);
	if ( x_subpixel <= 0 ) { return 12; }
	if ( y_subpixel <= 0 ) { return 13; }

	/* 有効なので値をセット */
	this->parent_data_ = parent_data;
	this->pa_w_ = pa_w;
	this->pa_h_ = pa_h;
	this->pa_ch_ = pa_ch;
	this->pa_by_ = pa_by;
	this->pa_xo_ = pa_xo;
	this->pa_yo_ = pa_yo;
	this->pa_xs_ = pa_xs;
	this->pa_ys_ = pa_ys;
	this->xs_ = xs;
	this->ys_ = ys;

	this->x_subpixel_division_ = x_subpixel;
	this->y_subpixel_division_ = y_subpixel;

	return 0;
}

void iip_crop_and_downsample::exec( void )
{
	if (this->parent_data_ == nullptr) { return; }

	/* 配列設定 */
	calcu_bresenham_(
		this->pa_xs_
		,this->xs_ * this->x_subpixel_division_
		,this->pa_ch_
		,this->array_x_.data()
	);
	calcu_bresenham_(
		this->pa_ys_
		,this->ys_ * this->y_subpixel_division_
		,this->pa_ch_ * this->pa_w_
		,this->array_y_.data()
	);

	switch (this->pa_by_) {
	case sizeof(unsigned char):
		engine_(
		static_cast<unsigned char *>(this->parent_data_)
		+ this->pa_ch_ * this->pa_w_ * this->pa_yo_
		+ this->pa_ch_ * this->pa_xo_
		,this->xs_
		,this->ys_
		,this->pa_ch_
		,this->x_subpixel_division_
		,this->y_subpixel_division_
		,this->array_x_.data()
		,this->array_y_.data()
		,this->array_sl_.data()
		,static_cast<unsigned char *>(
			static_cast<void *>(this->child_out.data()))
		);
		break;
	case sizeof(unsigned short):
		engine_(
		static_cast<unsigned short *>(this->parent_data_)
		+ this->pa_ch_ * this->pa_w_ * this->pa_yo_
		+ this->pa_ch_ * this->pa_xo_
		,this->xs_
		,this->ys_
		,this->pa_ch_
		,this->x_subpixel_division_
		,this->y_subpixel_division_
		,this->array_x_.data()
		,this->array_y_.data()
		,this->array_sl_.data()
		,static_cast<unsigned short *>(
			static_cast<void *>(this->child_out.data()))
		);
		break;
	}
}

#ifdef DEBUG_IIP_CROP_AND_DOWNSAMPLE
#include <fstream>
#include <chrono>
int main( const int argc , const char** argv )
{
	if (argc != 13) {
		std::cout
	<< argv[0]
	<< " w h ch by inimage.raw xo yo xs ys wout hout outimage.raw"
	//   1 2  3  4           5  6  7  8  9   10   11           12
	<< std::endl;
		return 1;
	}

 	const int w  = atoi( argv[1] );
 	const int h  = atoi( argv[2] );
 	const int ch = atoi( argv[3] );
 	const int by = atoi( argv[4] );
	std::vector<char> parent_in(w * h * ch * by);
	{
		std::ifstream fst(
			argv[5] , std::ios_base::in | std::ios_base::binary
		);
		fst.read( parent_in.data() ,parent_in.size() );
	}

	const int xo = atoi( argv[6] );
	const int yo = atoi( argv[7] );
	const int xs = atoi( argv[8] );
	const int ys = atoi( argv[9] );
	const int wout = atoi( argv[10] );
	const int hout = atoi( argv[11] );

std::cout << "Initial\n";
	auto ms_start = std::chrono::system_clock::now();/* 開始時刻保存 */

	iip_crop_and_downsample iip_crop_and_samp;
	if (iip_crop_and_samp.reserve_max_memory( 1920  , 1200 )) {
		return 2;
	}
	iip_crop_and_samp.set_subpixel_max_div( 2 );

std::cout << "Setup&Start\n";
	if (int ret = iip_crop_and_samp.set_mapping(
		parent_in.data()
		,w ,h ,ch ,by	/* 元画像のデータサイズ */
		,xo ,yo ,xs ,ys	/* Cropエリア */
		,wout ,hout	/* 結果画像のサイズ */
	)) {
		return ret+10;
	}

	iip_crop_and_samp.exec();

	auto ms_end   = std::chrono::system_clock::now();/* 終了時刻保存 */
std::cout << "End\n";
	auto dur =
	std::chrono::duration_cast<std::chrono::milliseconds>(ms_end-ms_start).count();
std::cout << dur << "msec \n";

	{
 		std::ofstream fst(
			argv[12] ,std::ios_base::out | std::ios_base::binary
		);
		fst.write(
			iip_crop_and_samp.child_out.data()
			,wout * hout * ch * by );
	}
	return 0;
}

#endif // !DEBUG_IIP_CROP_AND_DOWNSAMPLE
/*
rem compile for test
cl iip_crop_and_downsample.cpp /DDEBUG_IIP_CROP_AND_DOWNSAMPLE /Fetes & del iip_crop_and_downsample.obj
rem
rem execute for test
rem
rem basic
rem .\tes.exe 176 128 3 1 i0176x0128x3x1.raw 0 0 176 128 176 128 tmp.raw
rem crop
rem .\tes.exe 176 128 3 1 i0176x0128x3x1.raw 10 10 100 100 100 100 tmp.raw
rem downsample 176x128 --> 1/2 --> 88x64
rem .\tes.exe 176 128 3 1 i0176x0128x3x1.raw 0 0 176 128 88 64 tmp.raw
rem downsample 176x128 --> 1/4 --> 44x32
rem .\tes.exe 176 128 3 1 i0176x0128x3x1.raw 0 0 176 128 44 32 tmp.raw
rem crop & downsample 176x128 --> 100x100 --> 1/2 --> 50x50
rem .\tes.exe 176 128 3 1 i0176x0128x3x1.raw 10 10 100 100 50 50 tmp.raw
rem crop & upsample 176x128 --> 100x100 --> x2 --> 200x200
rem .\tes.exe 176 128 3 1 i0176x0128x3x1.raw 10 10 100 100 200 200 tmp.raw
rem crop & downsample 1000x500 --> 200x100
rem .\tes.exe 1016 603 3 1 i1016x0603x3x1.raw 10 10 1000 500 200 100 tmp.raw
rem crop & downsample 10200x7020 --> 1/10 --> 1020x702
rem .\tes.exe 10200 7020 3 1 i10200x07020x3x1.raw 100 10 10000 7000 1000 700 tmp.raw
rem .\tes.exe 10200 7020 3 1 i10200x07020x3x1.raw 0 0 9600 6000 1920 1200 tmp.raw
rem .\tes.exe 10200 7020 3 1 i10200x07020x3x1.raw 0 0 9600 6000 800 500 tmp.raw
rem .\tes.exe 10200 7020 3 1 i10200x07020x3x1.raw 4000 6000 475 300 1900 1200 tmp.raw
.\tes.exe 10200 7020 3 1 i10200x07020x3x1.raw 0 0 10200 7020 1920 1200 tmp.raw
rem 101msec (by Windows7  Intel Core i7-4810MQ 2.8GHz)
*/
