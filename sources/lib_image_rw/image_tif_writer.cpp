#include <limits> /* std::numeric_limits */
#include <sstream> /* std::ostringstream */
#include <stdexcept> /* std::runtime_error */
#include "image_common.h"
#include "image_tif_common.h"
#include "image_tif_write_handle.h"
#include "image_tif_writer.h"

using image::tif::writer;

writer::writer()
{}

const char *const writer::format_name(void) const {
	return image::tif::format_name;
}

const size_t writer::ext_count(void) {
	return image::tif::ext_count();
}
const char *const writer::ext_name(size_t count) {
	return image::tif::ext_name(count);
}

namespace {
const char *const compressions_names_[] = {
	"NONE(dump mode)"
	, "LZW(Lempel-Ziv & Welch)"
	, "PACKBITS(Macintosh RLE)"
	, "CCITT Group 4 fax encoding(Only monoBW)"
	, "CCITTRLE(CCITT modified Huffman RLE)(Only monoBW)"
};
}

/* 圧縮メニューリスト番号からwriter::put_data()に渡すTIFF圧縮番号を得る */
int writer::comp_num_from_name_num( const int name_num ) {
	int comp_num = 0;
	switch ( name_num ) {
	case 0:comp_num=COMPRESSION_NONE;     break;//=1 dump
	case 1:comp_num=COMPRESSION_LZW;      break;//=5 Not monoBW
	case 2:comp_num=COMPRESSION_PACKBITS; break;//=32773 NotmonoBW
	case 3:comp_num=COMPRESSION_CCITTFAX4;break;//=4 Only monoBW
	case 4:comp_num=COMPRESSION_CCITTRLE; break;//=2 Only monoBW
	}
	return comp_num;
}

/* 圧縮種類数 */
const size_t writer::compression_count(void) {
	return sizeof(compressions_names_)/sizeof(char *);
}
/* 圧縮名リスト */
const char *const writer::compression_name(size_t count) {
	return compressions_names_[count];
}

/* 保存可不可チェック */
/*
	.tif  RGBA/RGB/Grayscale  16/8/1(MonoBW)bits
*/
const bool writer::error_from_properties(
	const image::common::properties& props
	, const int ext_number
	, std::ostringstream& error_or_warning_msg
) {
	ext_number;

	bool error_sw = false;

	if (0 == props.width) {
		error_or_warning_msg
			<< "Error : width(0) Must Not be zero\n";
		error_sw = true;
	}
	if (0 == props.height) {
		error_or_warning_msg
			<< "Error : height(0) Must Not be zero\n";
		error_sw = true;
	}
	if (	(1 != props.channels) &&
		(3 != props.channels) &&
		(4 != props.channels)
	) {
		error_or_warning_msg
			<< "Error : channel(" << props.channels
			<< ") Must be 1 or 3 or 4\n";
		error_sw = true;
	}
	if ( (props.bits != 1)
	&&   (props.bits != std::numeric_limits<unsigned char>::digits)
	&&   (props.bits != std::numeric_limits<unsigned short>::digits)
	) {
		error_or_warning_msg
			<< "Error : sampling bits("
			<< props.bits
			<< ") Must be 1 or "
			<< std::numeric_limits<unsigned char>::digits
			<< " or "
			<< std::numeric_limits<unsigned short>::digits
			<< "\n";
		error_sw = true;
	}
	/* 画像の向き */
	/*
		TIFF 6.0 Specificationより、
		TIFFTAG_ORIENTATIONは、
		"Support for orientations other than 1 is not
		 a Baseline TIFF requirement."
		"1以外の方向のサポートは Baseline TIFFの要件ではない"
	*/
	/*if (props.orie_side != ORIENTATION_TOPLEFT) {
		error_or_warning_msg
			<< "Error : Orientation(" << props.orie_side
			<< ") Must be 1(ORIENTATION_TOPLEFT)\n";
		error_sw = true;
	}*/

	/* 解像度 */
	switch (props.reso_unit) {
	case image::common::resolution::not_defined:
		error_or_warning_msg
		<< "Warning : resolution unit is not defined\n";
		break;
	case image::common::resolution::nothing:
		error_or_warning_msg
		<< "Warning : resolution unit is nothing\n";
		break;
	case image::common::resolution::inch: break;
	case image::common::resolution::centimeter: break;
	case image::common::resolution::millimeter:
		error_or_warning_msg
		<< "Error : millimeter is not defined in TIFF\n";
		error_sw = true;
		break;
	case image::common::resolution::meter:
		error_or_warning_msg
		<< "Error : meter is not defined in TIFF\n";
		error_sw = true;
		break;
	}
	return error_sw;
}

/* strip書き出し */
namespace {
class write_strip_ {
public:
	write_strip_(
		image::tif::write_handle& handle_ref,
		const unsigned char *sour_top,
		const size_t sour_size
	);

	unsigned int count(void) const; /* segment_exec()実行回数 */
	void segment_exec(
		image::tif::write_handle& handle_ref
	); /* 呼出毎順次(部分)処理 */
private:
	write_strip_();

	const unsigned int number_of_strip_;
	unsigned int strip_counter_;
	const size_t sour_size_;
	const unsigned char *sour_current_; /* 外部参照 */
	size_t write_encoded_strip_bytes_;
};
}

write_strip_::write_strip_(
	image::tif::write_handle& handle_ref
	, const unsigned char *sour_top
	, const size_t sour_size
):
	number_of_strip_(1)/* ここは1のままでいいのか不明??? */
	, strip_counter_(0)
	, sour_size_(sour_size)
	, sour_current_(sour_top)
	, write_encoded_strip_bytes_(0)
{
	handle_ref;
}

unsigned int write_strip_::count(void) const
{ return this->number_of_strip_; }

void write_strip_::segment_exec( image::tif::write_handle& handle_ref )
{
	/* 呼出回数チェック */
	if (this->number_of_strip_ <= this->strip_counter_) {
		std::ostringstream os;
		os	<< "over call TIFFWriteEncodedStrip(,"
			<< this->strip_counter_
			<< ",p_data,"
			<< this->sour_size_
			<< ")";
		throw std::runtime_error(os.str());
	}
	/* memory overチェック */
	if (this->sour_size_ <= this->write_encoded_strip_bytes_) {
		std::ostringstream os;
		os	<< "over memory<"
			<< "> TIFFWriteEncodedStrip(,"
			<< this->strip_counter_
			<< ",,"
			<< this->sour_size_ 
			<< ")";
		throw std::runtime_error(os.str());
	}
/*
	tsize_t	TIFFWriteEncodedStrip(
		TIFF* tif, tstrip_t strip, tdata_t buf, tsize_t size);
	typedef	void* tdata_t;

	size is	h*(w/std::numeric_limits<unsigned char>::digits+(w%std::numeric_limits<unsigned char>::digits?1:0))	--> bw		
		h*w*b*ch			--> rgb/rgba	

	TIFFSetField(image, TIFFTAG_ROWSPERSTRIP, ...);
		をしておくことが必要???

	size is returned , when error then -1 is returned.
*/
	tsize_t t_ret = TIFFWriteEncodedStrip(
		handle_ref
		, this->strip_counter_
		, const_cast<unsigned char *>(this->sour_current_ )
		, static_cast<tsize_t>(this->sour_size_)
	);
	if (t_ret < 0) {
		throw std::runtime_error(
			"TIFFWriteEncodedStrip(-) returns minus");
	}

	/* 呼出回数カウントアップ */
	++ this->strip_counter_;

	/* 次の画像の置き場へ移動 */
	this->sour_current_ += t_ret;
	this->write_encoded_strip_bytes_ += t_ret;
}

/* 保存
正常終了、例外処理のcatch、で
内部メモリ解放し、ファイルを閉じること
*/
void
writer::put_data(
	const image::common::properties& props
	, const size_t image_bytes
	, const void* image_array
	, const int compression_number
	, const std::string& history_str
	, const std::string& file_path
) {
	history_str;

	/* ヘッダ設定 --------------------------------- */
	/* http://bb/watch.impress.co.jp/cda/bbword/15612.html
		RGBフルカラーの場合、Tagとして設定すべき項目は
		以下の12項目だけで、
		それ以外のTagはオプション扱いになります。
		・ImageLength
		・ImageWidth
		・SamplesPerPixel
		・BitsPerSample

		・Compression
		・PhotometricInterpretation
		・XResolution
		・YResolution
		・ResolutionUnit

		・StripOffsets
		・RowsPerStrip
		・StripByteCounts
	*/
	image::tif::write_handle w_handler(file_path.c_str());

	/* --- 大きさ --------------------------------- */
	w_handler.set_uint32_throw( TIFFTAG_IMAGELENGTH    ,props.height );
	w_handler.set_uint32_throw( TIFFTAG_IMAGEWIDTH     ,props.width );
	w_handler.set_uint16_throw( TIFFTAG_SAMPLESPERPIXEL,props.channels);
	w_handler.set_uint16_throw( TIFFTAG_BITSPERSAMPLE  ,props.bits );

	using namespace image::common;

	/* --- 画像の向き ----------------------------- */
	/*
	TIFF 6.0 Specificationより、
	"Support for orientations other than 1 is not
	a Baseline TIFF requirement."
	"Baseline TIFF"では1以外はサポートしない...とはいかに?

	--- ORIENTAIONタグがORIENTATION_RIGHTTOPとなっていた時の、
		各アプリの動作調べ 2019-04-11 ---
	Photoshop CC 2017.1.1
		時計回り90度回転して表示
		--> 正しい
	TVPaint Animation-11.0.8-64bits
		時計回り90度回転して、さらに上下逆さに表示
		--> 誤り
	OpenToonz-1.3.0
		左右反転して表示
		--> 誤り
	Windows7 Explorer プレビューウインドウ
	Windows7 フォトビューアー
	Windows7 付属ペイント-6.1
	Krita-3.0
		ORIENTATIONタグを無視して表示
		--> "Baseline TIFF"では正しいが、そうでなければ誤り(?)
	TraceMan-6.6.0
		--> LZW(Dump以外?)を表示できないため現状テスト不可
	*/
	uint16 ui16_orient=0;
	switch (props.orie_side) {
	case orientation::not_defined:
	/* 方向が指示してない場合、あえてdefault指定する 2012-12-14 */
				   ui16_orient=ORIENTATION_TOPLEFT; break;
	case orientation::topleft: ui16_orient=ORIENTATION_TOPLEFT; break;
	case orientation::toprigh: ui16_orient=ORIENTATION_TOPRIGHT;break;
	case orientation::botrigh: ui16_orient=ORIENTATION_BOTRIGHT;break;
	case orientation::botleft: ui16_orient=ORIENTATION_BOTLEFT; break;
	case orientation::lefttop: ui16_orient=ORIENTATION_LEFTTOP; break;
	case orientation::rightop: ui16_orient=ORIENTATION_RIGHTTOP;break;
	case orientation::righbot: ui16_orient=ORIENTATION_RIGHTBOT;break;
	case orientation::leftbot: ui16_orient=ORIENTATION_LEFTBOT; break;
	}
	/***if ((orientation::not_defined != props.orie_side) &&
	    (orientation::topleft     != props.orie_side)) {***/
	/* default指定もあえて保存する 2012-12-14 */

	 w_handler.set_uint16_throw( TIFFTAG_ORIENTATION, ui16_orient );
	/***}***/

	/* --- 画像の並び ----------------------------- */
	/*
	TIFFTAG_PLANARCONFIGはPLANARCONFIG_CONTIGがdefault
	Write時は指定が必要
	*/
	w_handler.set_uint16_throw(
			TIFFTAG_PLANARCONFIG , PLANARCONFIG_CONTIG );

	/* --- 画像の色定義 --------------------------- */
	uint16 ui16_photo=PHOTOMETRIC_RGB;
	if ((1==props.channels) && (1==props.bits)) {/* MonoBW画像 */
		/*
		モノクロ2階調画像TIFFファイルの問題
			Photoshop 8.0.1で白黒２値化画像を保存すると、
			ゼロを白、1を黒(PHOTOMETRIC_MINISWHITE)となる
			2007-12

			OpenGL表示でのMonoBW画像は、
			ゼロは黒、1は白(PHOTOMETRIC_MINISBLACK)だが、
			そのまま保存すると、
			Photoshop CS4(11.0.1)の表示でTagを感知せず、
			白黒反転してしまう
			2010-2-8
		解決方法
			画像を反転し、
			タグをPHOTOMETRIC_MINISWHITEで保存する
		*/
		ui16_photo = PHOTOMETRIC_MINISWHITE;/* ゼロが白として保存 */
	} else
	if ((1==props.channels) && (1<props.bits)) {/* Grayscale */
		ui16_photo = PHOTOMETRIC_MINISBLACK;/* ゼロを黒として保存 */
	} else
	if (1 < props.channels) {/* フルカラ(RGB,RGBA)画像 */
		ui16_photo = PHOTOMETRIC_RGB;
	}
	w_handler.set_uint16_throw( TIFFTAG_PHOTOMETRIC , ui16_photo );

	/* --- 表示解像度 ----------------------------- */
	uint16 ui16_un = RESUNIT_NONE;
	switch (props.reso_unit) {
	case resolution::not_defined: break;
	case resolution::nothing:     break;
	case resolution::inch:       ui16_un=RESUNIT_INCH;       break;
	case resolution::centimeter: ui16_un=RESUNIT_CENTIMETER; break;
	case resolution::millimeter:  break; /* tiff.hにない */
	case resolution::meter:       break; /* tiff.hにない */
	}
	if ( resolution::not_defined != props.reso_unit) {
	 w_handler.set_uint16_throw( TIFFTAG_RESOLUTIONUNIT , ui16_un );
	 w_handler.set_float_throw(  TIFFTAG_XRESOLUTION , props.reso_x );
	 w_handler.set_float_throw(  TIFFTAG_YRESOLUTION , props.reso_y );
	}

	/* --- 保存圧縮の定義 ------------------------- */
	/* 圧縮種類を設定
		monoBWの時と以外で圧縮タイプが違うので自動的に変更 */

	int comp_num = compression_number;

	if ((1==props.channels) && (1==props.bits)) {/* MonoBW画像 */
		/*
			monoBWの圧縮保存で、
				COMPRESSION_PACKBITS or
				COMPRESSION_LZW
			となっていた場合、
				COMPRESSION_CCITTFAX4
			として保存する。
		*/
		if ((COMPRESSION_PACKBITS == comp_num)
		||  (COMPRESSION_LZW == comp_num)) {
			comp_num = COMPRESSION_CCITTFAX4;
		}
	} else {/* Grayscale, フルカラー(RGB, RGBA)画像 */
		/*
			Grayscale or RGB(A)の圧縮保存で、
				COMPRESSION_CCITTRLE or
				COMPRESSION_CCITTFAX4
			となっていた場合、
				COMPRESSION_LZW
			として保存する。
		*/
		if (COMPRESSION_CCITTRLE  == comp_num
		||  COMPRESSION_CCITTFAX4 == comp_num) {
			comp_num = COMPRESSION_LZW;
		}
	}
	w_handler.set_uint16_throw( TIFFTAG_COMPRESSION , comp_num );

/* -----
	懸案事項1 TIFFTAG_PREDICTOR
	TIFFSetField(p_tif,TIFFTAG_COMPRESSION,COMPRESSION_LZW);
	TIFFSetField(p_tif,TIFFTAG_COMPRESSION,COMPRESSION_DEFLATE);
	で予測動作(圧縮効率をあげる)?
		TIFFSetField(w_handler,TIFFTAG_PREDICTOR,1);なし?
		TIFFSetField(w_handler,TIFFTAG_PREDICTOR,2);あり?
		default is 1???
	TIFFTAG_PREDICTORの問題点(2004.09.14 tue)
	-----------------------+---------------+---------------
	TIFF RGB各16btis sampling画像のときの保存画像の症状
				lzw prediction scheme
				1		2
	-----------------------+---------------+---------------
	libtiff version		中間色	一部黒	中間色	一部黒
	-----------------------+-------+-------+-------+-------
	libtiff-v3.5.7(rh9)	正常	正常	正常	でる
	libtiff-v3.6.1(rhel4)	でない	正常	でない	でる
	-----------------------+-------+-------+-------+-------
	"lzw_prediction_scheme = 2;"は16bits画像で使えない。


	懸案事項2 TIFFTAG_FILLORDER
	MonoBWにて
	TIFFSetField(p_tif, TIFFTAG_FILLORDER, FILLORDER_MSB2LSB);
	は指定いるのか?

	懸案事項3 TIFFTAG_ROWSPERSTRIP
	if (1 == props.bits) {
		TIFFSetField( w_handler, TIFFTAG_ROWSPERSTRIP,
			static_cast<uint32>(props.height) );
	}
	else {
		uint32 rowsperstrip = (uint32)-1;

		これがないと、
		正常終了するのに、読めないファイルになる
		(2000.04.05)
		TIFFSetField( w_handler,
			TIFFTAG_ROWSPERSTRIP,
			TIFFDefaultStripSize(
				w_handler, rowsperstrip
			)
		);
	}

	懸案事項4 TIFFTAG_SUBFILETYPE
	Example about imginfo : Page Size (x,y,z,c):    256, ?, 1, 3
	TIFFSetField( w_handler, TIFFTAG_SUBFILETYPE, 0);
	For same to photoshop_v3.0.1(IRIX)
-------- */

	/* --- 画像保存 ------------------------------- */
	/* 上下反転(BL(OpenGL座標系)-->TL)変換 */
	image::tif::reverse_top_bottom(
		  props.height
		, props.width
		, props.channels
		, props.bits
		, const_cast<unsigned char *>(
			static_cast<const unsigned char*>(image_array))
	);

	/* MonoBW画像なら ゼロ黒->ゼロ白(PHOTOMETRIC_MINISWHITE)に変換 */
	if ((1==props.channels) && (1==props.bits)) {
		unsigned char *uchar_array =
			const_cast<unsigned char *>(
			static_cast<const unsigned char*>(image_array));
		for (size_t ii = 0; ii < image_bytes; ++ii) {
			uchar_array[ii] = ~uchar_array[ii];
		}
	}
	/* ファイル書き出し */
	write_strip_ w_strip(
		w_handler
		, static_cast<const unsigned char*>(image_array)
		, image_bytes
	);
	for (unsigned int ii=0; ii < w_strip.count(); ++ii) {
		w_strip.segment_exec(w_handler);
	}

	/* MonoBW画像なら ゼロ白(PHOTOMETRIC_MINISWHITE)->ゼロ黒に戻す */
	if ((1==props.channels) && (1==props.bits)) {
		unsigned char *uchar_array =
			const_cast<unsigned char *>(
			static_cast<const unsigned char*>(image_array));
		for (size_t ii=0; ii<image_bytes; ++ii) {
			uchar_array[ii] = ~uchar_array[ii];
		}
	}

	/* 上下反転(TL-->BL(OpenGL座標系))変換 */
	image::tif::reverse_top_bottom(
		  props.height
		, props.width
		, props.channels
		, props.bits
		, const_cast<unsigned char *>(
			static_cast<const unsigned char*>(image_array))
	);
}

//------------------------------------------------------------
#ifdef DEBUG_IMAGE_TIF_WRITER
#include <iostream> /* std::cout */
#include <fstream> /* std::fstream */
#include "image_tif_common.cpp"
#include "image_tif_read_handle.cpp"
#include "image_tif_read_handle_info.cpp"
#include "image_tif_reader.cpp"
#include "image_tif_write_handle.cpp"
int main(int argc , char *argv[])
{
	if (argc != 3) {
		std::cout << argv[0] << " in_path_tif out_path_tif\n";
		return 1;
	}
	std::cout << "in_path_tif =" << argv[1] << std::endl;
	std::cout << "out_path_tif=" << argv[2] << std::endl;

 try {
	image::common::properties props;
	size_t image_bytes=0;
	std::string history_str;
	std::vector<uint8_t> image;

 	{
	image::tif::reader rdr;

	std::cout << "format_name=" << rdr.format_name() << std::endl;
	for (size_t ii=0 ;ii < rdr.ext_count() ;++ii) {
	 //const char *const *const lists = this->ext_name_lists();
	 //std::cout << "ext_name=" << lists[ii] << std::endl;
	 std::cout << ii << " ext_name=" << rdr.ext_name(ii) << std::endl;
	}

	std::string line_info;
	rdr.get_info( argv[1] , line_info );
	std::cout << "get_info=" << line_info;

	size_t history_bytes=0;
	rdr.get_size( argv[1] ,image_bytes ,history_bytes );
	std::cout << "get_size image_bytes=" << image_bytes
		<< " history_bytes=" << history_bytes
		<< std::endl;

	image.resize(image_bytes);
	static bool break_sw=false;
	rdr.get_data(
		argv[1]
		, props
		, image_bytes
		, image.data()
		, history_str
		, break_sw /* 中断Switch。外からtureで中断 */
		, 0 /* 分割読込の個々サイズ(tif以外で使用する) */
	);
	}

//	std::ofstream ofs( "tmp.raw" ,std::ios_base::binary );
//	ofs.write( (char *)(image.data()) ,image.size() );
//	ofs.close();

	{
	image::tif::writer wtr;
	std::ostringstream error_or_warning_msg;

	const bool w_chk = wtr.error_from_properties(
		props
		, 0
		, error_or_warning_msg
	);
	if (w_chk) {
		std::cerr << error_or_warning_msg.str();
		return 2;
	}
	wtr.put_data(
		props
		, image_bytes
		, image.data()
		, COMPRESSION_NONE
		, history_str
		, argv[2]
	);
	}

	return 0;
 }
 catch (std::exception& e) {
 	std::cerr << "Error : exception \"" << e.what() << "\"\n";
 }
 catch (...) {
 	std::cerr << "Error : other exception\n";
 }
	return 0;
}
#endif /* !DEBUG_IMAGE_TIF_WRITER */
//------------------------------------------------------------
#ifdef PLUGIN_IMAGE_TIF_WRITER
#include "image_tif_common.cpp"
#include "image_tif_write_handle.cpp"
#if defined _WIN32
extern "C" __declspec(dllexport) void *get_plugin_instance_writer(void);
#endif
namespace {
	image::tif::writer writer_instance;
}
void *get_plugin_instance_writer(void) {
	return &writer_instance;
}
#endif /* !PLUGIN_IMAGE_TIF_WRITER */
//------------------------------------------------------------

/*
rem /DUNICODE /D_UNICODE
rem make .exe
rem :639,640 w! makerw.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_IMAGE_TIF_WRITER /I. /I../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff image_tif_writer.cpp ../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff/libtiff.lib /Fea
del image_tif_writer.obj
rem
rem make .dll
rem :595,596 w! makedllw.bat
cl /W4 /WX /MD /EHa /O2 /LD /source-charset:utf-8 /DPLUGIN_IMAGE_TIF_WRITER /I. /I../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff image_tif_writer.cpp ../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff/libtiff.lib /Feplugin_image_tif_writer
del image_tif_writer.obj
#
# :674,675 w! make.sh
g++ -Wall -std=c++11 image_tif_writer.cpp -DDEBUG_IMAGE_TIF_WRITER -I. -ltiff
*/
