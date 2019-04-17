#include <iostream> /* std::cout */
#include <limits> /* std::numeric_limits */
#include <cassert> /* assert(-) */
#include <vector>
#include <sstream> /* std::ostringstream */
#include <stdexcept> /* std::runtime_error */
#include "image_tif_common.h"
#include "image_tif_read_handle_info.h"
#include "image_tif_read_handle.h"
#include "image_tif_reader.h"

//------------------------------------------------------------
using image::tif::reader;

/* 01 GUI等に表示するファイル書式名 */
const char *const reader::format_name(void) const {
	return image::tif::format_name;
}

/* 02 利用可能な１個以上の拡張子の数 */
const size_t reader::ext_count(void) {
	return image::tif::ext_count();
}

/* 03 利用可能な１個以上の拡張子名のリスト */
const char *const reader::ext_name(size_t count) {
	return image::tif::ext_name(count);
}

/* 04 ファイルヘッダタグから書式に一致したファイルか調べる */
const bool reader::istag(
	const size_t bytes_count
	,const void*const tag_array
) {
	const uint8_t* const ui8_tag_array =
		static_cast<const uint8_t* const>(tag_array);
	if (	(2 <= bytes_count)
	 && (	(('I' == ui8_tag_array[0]) && ('I' == ui8_tag_array[1]))
	  ||	(('M' == ui8_tag_array[0]) && ('M' == ui8_tag_array[1]))
	)) { return true; }
	return false;
}

/* 05 情報を得る、詳細 */
void reader::get_info(
	const std::string& file_path
	, std::string& info
) {
	info += image::tif::get_info( this->format_name() ,file_path );
}

/* 06 情報を得る、表形式、ヘッド */
void reader::get_line_head(
	std::string& line_head
) {
	line_head += image::tif::get_line_head();
}

/* 07 情報を得る、表形式、１行 */
void reader::get_line_info(
	const std::string& file_path
	, std::string& line_info
) {
	line_info += image::tif::get_line_info( file_path );
}

/* 08 画像、作業情報をメモリに読むため用意すべきサイズを得る */
#if 0
namespace {
/* bitsサンプリングはTIFF以外にはなさそう(?)なので計算処理は埋め込み */
const size_t byte_of_scanline_(
	const size_t width , const size_t channels , const size_t bits
) {
	const size_t sl = width * channels * bits;
	return sl / std::numeric_limits<uint8_t>::digits
	+((0==(sl % std::numeric_limits<uint8_t>::digits))? 0: 1);
	/* モノクロ２階調TIFF保存 */
	// l_w_bytes = l_width/CHAR_BIT + ((l_width%CHAR_BIT)?1:0);
}
}
#endif

void
reader::get_size(
	const std::string& file_path,
	size_t& image_bytes,
	size_t& history_bytes
) {
	image::tif::read_handle r_handler( file_path );
	bool isexist = false;

	image_bytes = r_handler.imagelength(isexist) *
		image::tif::bytes_of_scanline(
			  r_handler.imagewidth(isexist)
			, r_handler.samplesperpixel(isexist)
			, r_handler.bitspersample(isexist)
		);

	history_bytes = 0;

	r_handler.close();
}

/* 09 画像情報、画像、ヒストリ情報をメモリに読む
	正常終了でも例外処理throw、(デストラクタ)、でも、
	内部メモリ解放し、ファイルを閉じるよう設計する */
namespace {
 void set_properties_(
	image::tif::read_handle& handle_ref,
	image::common::properties& props
 ) {
	bool isexist = false;
	props.height	= handle_ref.imagelength(isexist);
	props.width	= handle_ref.imagewidth(isexist);
	props.channels	= handle_ref.samplesperpixel(isexist);
	props.bits	= handle_ref.bitspersample(isexist);

	using namespace image::common;
	orientation::side or_si;
	const uint16 u_or = handle_ref.orientation(isexist);
	if (std::numeric_limits<uint16>::max() == u_or) {
				  or_si = orientation::not_defined; }
	else {
	 switch (u_or) {
	 case 0:
	 case ORIENTATION_TOPLEFT: or_si = orientation::topleft; break;
	 case ORIENTATION_TOPRIGHT:or_si = orientation::toprigh; break;
	 case ORIENTATION_BOTRIGHT:or_si = orientation::botrigh; break;
	 case ORIENTATION_BOTLEFT: or_si = orientation::botleft; break;
	 case ORIENTATION_LEFTTOP: or_si = orientation::lefttop; break;
	 case ORIENTATION_RIGHTTOP:or_si = orientation::rightop; break;
	 case ORIENTATION_RIGHTBOT:or_si = orientation::righbot; break;
	 case ORIENTATION_LEFTBOT: or_si = orientation::leftbot; break;
	 default:
		/* std::ostringstream os;
		os << "TIFFTAG_ORIENTATION(" << u_or << ") is not support";
		throw std::runtime_error(os.str());
		*/
		/* orientation値が規定値
			ORIENTATION_TOPLEFT
			ORIENTATION_BOTLEFT
			ORIENTATION_TOPRIGHT
			ORIENTATION_BOTRIGHT
			ORIENTATION_LEFTTOP
			ORIENTATION_RIGHTTOP
			ORIENTATION_RIGHTBOT
			ORIENTATION_LEFTBOT
		以外の値、
		1 std::numeric_limits<uint16>::max() --> not defined
		2 0 --> 古いphotoshopで作成したTIFFデータ --> topleftとする
		3 それ以外の規定値 --> not support --> でなく、
			default値のORIENTATION_TOPLEFTであるとして、
			受け入れることにする 2012-12-14
		*/
		or_si = orientation::topleft;
	 }
	}
	props.orie_side = or_si;

	resolution::unit re_un;
	const uint16 u_re = handle_ref.resolutionunit(isexist);
	if (std::numeric_limits<uint16>::max() == u_re) {
				  re_un = resolution::not_defined; }
	else {
	 switch (u_re) {
	 case 0:
	 /*
		TraceManで保存したtif画像のTIFFTAG_RESOLUTIONUNITの値が、
		0となってしまうが読取る必要があるためRESUNIT_INCHとして
		強制的に読む
	 */
	 case RESUNIT_NONE:       re_un = resolution::nothing;    break;
	 case RESUNIT_INCH:       re_un = resolution::inch;       break;
	 case RESUNIT_CENTIMETER: re_un = resolution::centimeter; break;
	 default:
		std::ostringstream os;
		os	<< "TIFFTAG_RESOLUTIONUNIT(" << u_re
			<< ") is not support";
		throw std::runtime_error(os.str());
	 }
	}
	props.reso_unit = re_un;

	props.reso_x = handle_ref.xresolution(isexist);
	props.reso_y = handle_ref.yresolution(isexist);
 }
 void set_history_(
	image::tif::read_handle& handle_ref,
	std::string& history_str
 ) {
	handle_ref;
	history_str;
 }

 /* 画像 strip圧縮からメモリデータへ */
 class read_strip_ {
 public:
	read_strip_(
		image::tif::read_handle& handle_ref
		, uint8_t* dest_top
		, const size_t dest_size
 	):
	strip_size_(static_cast<uint32>(TIFFStripSize(handle_ref)))
	, number_of_strip_(TIFFNumberOfStrips(handle_ref))
	, dest_size_(dest_size)
	, dest_current_(dest_top)
	, read_encoded_strip_bytes_(0)
 	{}

	size_t count(void) const /* segment_exec()実行回数 */
 	{ return this->number_of_strip_; }

	void segment_exec(
		image::tif::read_handle& handle_ref
		,size_t counter
	); /* 呼出毎順次(部分)処理 */
 private:
	read_strip_();

	const uint32  strip_size_;
	const tstrip_t number_of_strip_;

	const size_t dest_size_;
	uint8_t* dest_current_; /* 外部メモリ参照 */

	size_t read_encoded_strip_bytes_;
 };

 void read_strip_::segment_exec(
	image::tif::read_handle& handle_ref
	,size_t counter
 ) {
	/* 呼出回数チェック */
	if (this->number_of_strip_ <= counter) {
		std::ostringstream os;
		os	<< "over call TIFFReadEncodedStrip(,"
			<< counter
			<< ",p_data,"
			<< this->strip_size_
			<< ")";
		throw std::domain_error(os.str());
	}

	/* ファイルから単位(?)読み込み
	--> bufに置かれたデータの実際のバイト数を返す  */
	/* tsize_t TIFFReadEncodedStrip(
		TIFF* tif, tstrip_t strip, tdata_t buf, tsize_t size
	   );
	   typedef uint32 tstrip_t;
	   typedef void* tdata_t;
	   typedef int32 tsize_t;
	*/
	const tsize_t t_ret = TIFFReadEncodedStrip(
		handle_ref		// TIFF* tif
		, static_cast<tstrip_t>(counter)	// tstrip_t strip
		, this->dest_current_	// tdata_t buf   
		, this->strip_size_ // uint32 size  
	);
	// in TIFF.h
	// typedef uint32 tstrip_t;
	// typedef void*  tdata_t;
	// typedef int32  tsize_t;
	// typedef unsigned int uint32;
	// typedef int int32;

	/* 次の画像の置き場へ移動 */
	this->dest_current_ += t_ret;

	/* memory overチェック。
	!!!最期のstripのthis->strip_size_がわからないので、
	前もってサイズチェックができない!!! */
	this->read_encoded_strip_bytes_ += t_ret;
	if (this->dest_size_ < this->read_encoded_strip_bytes_) {
		std::ostringstream os;
		os	<< "overd memory<"
			<< this->dest_size_
			<< "> TIFFReadEncodedStrip(,"
			<< counter
			<< ",,"
			<< this->strip_size_
			<< ")";
		throw std::domain_error(os.str());
	}
 }

 /* 画像 tile圧縮からメモリデータへ */
 class read_tile_ {
 public:
	read_tile_(
		image::tif::read_handle& handle_ref,
		uint8_t *dest_top,
		const size_t dest_size
	):
		  tile_num_he_(0)
		, tile_num_wi_(0)
		, byte_per_pixel_(0)
		, read_bytes_size_(0)
		, read_bytes_crnt_(0)
		, current_count_(0)
		, current_x_image_(0)
		, current_y_image_(0)
		, dest_size_(dest_size)
		, dest_top_(dest_top)
 	{
		bool isexist = false;
		this->heig_	= handle_ref.imagelength(isexist);
		this->widt_	= handle_ref.imagewidth(isexist);
		this->bits_per_sample_ = handle_ref.bitspersample(isexist);
		this->tile_he_	= handle_ref.tilelength(isexist);
		this->tile_wi_	= handle_ref.tilewidth(isexist);

		switch (this->bits_per_sample_) {
		case std::numeric_limits<uint8_t>::digits:
		case std::numeric_limits<uint16_t>::digits: break;
		default:
		std::ostringstream os;
		os	<< "TIFFTAG_BITSPERSAMPLE must "
			<< std::numeric_limits<uint8_t>::digits
			<< " or "
			<< std::numeric_limits<uint16_t>::digits
			<< ",but " << this->bits_per_sample_;
		throw std::runtime_error(os.str());
		}
		this->tile_num_he_ = this->heig_ / this->tile_he_ +
				   ((this->heig_ % this->tile_he_)? 1: 0);
		this->tile_num_wi_ = this->widt_ / this->tile_wi_ +
				   ((this->widt_ % this->tile_wi_)? 1: 0);
		this->byte_per_pixel_ = this->bits_per_sample_ /
			std::numeric_limits<uint8_t>::digits *
			handle_ref.samplesperpixel(isexist);
		this->read_bytes_size_ =
		 this->heig_ * this->widt_ * this->byte_per_pixel_;

		this->memory_of_tile_.resize(
		 this->tile_he_ * this->tile_wi_ * this->byte_per_pixel_
		);
	}

	size_t count(void) const { /* v_segment()実行回数 */
		return this->tile_num_wi_ * this->tile_num_he_;
	}

	void segment_exec(
		image::tif::read_handle& handle_ref ,size_t counter
	); /* 呼出毎順次(部分)処理 */

	void clear(void) {
		this->memory_of_tile_.clear();
	}

	~read_tile_() {
		try { this->clear(); } catch(...) {}
	}
 private:
	read_tile_();

	size_t heig_ , widt_ , bits_per_sample_;
	size_t tile_he_ , tile_wi_;
	size_t tile_num_he_ , tile_num_wi_;
	size_t byte_per_pixel_;
	std::vector<uint8> memory_of_tile_;
	size_t	read_bytes_size_
		, read_bytes_crnt_
		, current_count_
		, current_x_image_
		, current_y_image_;
	size_t dest_size_;
	uint8_t* dest_top_; /* 外部メモリ参照 */

	size_t current_tile_w_(void) const {
	 if (   (this->widt_ - this->current_x_image_) < this->tile_wi_) {
	  return this->widt_ - this->current_x_image_;
	 }
	 return this->tile_wi_;
	}
	size_t current_tile_h_(void) const {
	 if (   (this->heig_ - this->current_y_image_) < this->tile_he_) {
	  return this->heig_ - this->current_y_image_;
	 }
	 return this->tile_he_;
	}
 };

 template <typename T1 , typename T2>
 size_t trcopy_tile_(
	size_t u_tile_wi
	, size_t w_expand_tile
	, size_t h_expand_tile
	, size_t byte_per_pixel
	, T1* top_tile
	, size_t width
	, T2* top_image
 ) {
	size_t   tile_scanline_size = u_tile_wi * byte_per_pixel,
		image_scanline_size = width * byte_per_pixel,
	  expand_tile_scanline_size = w_expand_tile * byte_per_pixel;
	T1* y_tile  = top_tile; // for TIFF memory
	T2* y_image = top_image;// for C++  memory

	for (size_t yy = 0; yy < h_expand_tile; ++yy
		, y_tile  += tile_scanline_size
		, y_image += image_scanline_size
	) {
		for (size_t xx = 0; xx < expand_tile_scanline_size; ++xx) {
			y_image[xx] = y_tile[xx];
		}
	}
	return h_expand_tile * expand_tile_scanline_size;
 }

 void read_tile_::segment_exec(
	image::tif::read_handle& handle_ref
	,size_t counter
 ) {
	/* 呼出回数チェック */
	if ((this->tile_num_wi_ * this->tile_num_he_) <= counter) {
		std::ostringstream os;
		os	<< "over call TIFFReadTile(,,"
			<< this->current_x_image_
			<< ","
			<< this->current_y_image_
			<< ",0,0)";
		throw std::domain_error(os.str());
	}
	/* memory overチェック */
	if (this->read_bytes_size_ <= this->read_bytes_crnt_) {
		std::ostringstream os;
		os	<< "over memory<"
			<< this->read_bytes_size_
			<< "> TIFFReadTile(,,"
			<< this->current_x_image_
			<< ","
			<< this->current_y_image_
			<< ",0,0)";
		throw std::domain_error(os.str());
	}

	/* ファイルからタイル読み込み
	tsize_t TIFFReadTile(
		TIFF* tif, tdata_t buf, uint32 x, uint32 y, uint32 z,
		tsample_t sample);
	typedef void* tdata_t;
	*/
	const tsize_t t_ret = TIFFReadTile(
		handle_ref
		, &this->memory_of_tile_.at(0)
		, static_cast<uint32>(this->current_x_image_)
		, static_cast<uint32>(this->current_y_image_)
		, 0
		, static_cast<tsample_t>(0)
	);

	/* タイルを画像にうつす */
	uint8_t* image_array =
		this->dest_top_ +
		this->byte_per_pixel_ * this->widt_ * this->current_y_image_
		+
		this->byte_per_pixel_ * this->current_x_image_;

	size_t bytes_of_copied;
	if (std::numeric_limits<unsigned char>::digits ==
	static_cast<int>(this->bits_per_sample_)) {
		bytes_of_copied = trcopy_tile_(
			  this->tile_wi_
			, this->current_tile_w_()
			, this->current_tile_h_()
			, this->byte_per_pixel_
			,&this->memory_of_tile_.at(0)
			, this->widt_
			, image_array
		);
	} else {
		void* tif_a = static_cast<void *>(
				&this->memory_of_tile_.at(0));
		void* ima_a = static_cast<void *>(image_array);
		bytes_of_copied = trcopy_tile_(
			this->tile_wi_
			, this->current_tile_w_()
			, this->current_tile_h_()
			, this->byte_per_pixel_
			, static_cast<uint16 *>(tif_a)
			, this->widt_
			, static_cast<uint16_t *>(ima_a)
		);
	}

	/* 次のタイル位置を計算するためカウントアップ */
	++ counter;

	/* 次のタイル位置を計算しとく */
	this->current_x_image_ =
		( counter % this->tile_num_wi_ ) * this->tile_wi_;
	this->current_y_image_ =
		( counter / this->tile_num_wi_ ) * this->tile_he_;

	/* 読み込み済の画像の大きさ */
	this->read_bytes_crnt_ += bytes_of_copied;
 }

 /* 白黒反転(mono画像のみ)
	TIFFTAG_PHOTOMETRICがPHOTOMETRIC_MINISWHITEの場合行なう
	TIFFTAG_PHOTOMETRICがPHOTOMETRIC_RGBの場合は関係ないのでやらない
 */
 void invert_image_(
	const size_t bitspersample
	, const size_t bytes_size
	, void *image_array
 ) {
	if (1 == bitspersample) {
		unsigned char* uchar_array =
			static_cast<unsigned char *>(image_array);
		for (size_t ii = 0; ii < bytes_size; ++ii) {
			uchar_array[ii] = ~uchar_array[ii];
		}
	} else
	if (std::numeric_limits<unsigned char>::digits == bitspersample) {
		unsigned char* uchar_array =
			static_cast<unsigned char *>(image_array);
		for (size_t ii = 0; ii < bytes_size; ++ii) {
			uchar_array[ii] = std::numeric_limits<
				unsigned char>::max() - uchar_array[ii];
		}
	} else
	if (std::numeric_limits<unsigned short>::digits == bitspersample){
		unsigned short *ushort_array =
			static_cast<unsigned short *>(image_array);
		for (size_t ii = 0; ii < bytes_size/sizeof(unsigned short)
		; ++ii) {
			ushort_array[ii] = std::numeric_limits<
				unsigned short>::max() - ushort_array[ii];
		}
	}
 }
}

void
reader::get_data(
	const std::string& file_path
	, image::common::properties& props
	, const size_t image_bytes
	, void* image_array
	, std::string& history_str
	, bool& break_sw /* 中断Switch。外からtureで中断 */
	, const size_t segment_bytes
			/* 分割読込の個々サイズ(tif以外で使用する) */
) {
	assert(0 < image_bytes);
	assert(image_array != nullptr);

	segment_bytes;

	/* ファイル開く */
	image::tif::read_handle r_handler(file_path);
	bool isexist = false;

	/* ヘッダチェックし情報のセット */
	r_handler.check_parameters();
	set_properties_(r_handler,props);

	/* historyデータを読む */
	if (0 < history_str.size()) {
		set_history_(r_handler,history_str);
	}

	/* 画像データを読む */
    if (0 < image_bytes) {
	/* ファイルから読み、OpenGL型画像データに変換する */
	if (r_handler.istiled()) {
		read_tile_ cl_r_tile(
			r_handler
			, static_cast<uint8_t*>(image_array)
			, image_bytes
		);
		for (size_t ii = 0; ii < cl_r_tile.count(); ++ii) {
			if (break_sw == true) { // Cancel by User
				break_sw = false;
				return;
			}
			cl_r_tile.segment_exec( r_handler ,ii );
		}
	} else {
		read_strip_ cl_r_strip(
			r_handler
			, static_cast<uint8_t*>(image_array)
			, image_bytes
		);
		for (size_t ii = 0; ii < cl_r_strip.count(); ++ii) {
			if (break_sw == true) { // Cancel by User
				break_sw = false;
				return;
			}
			cl_r_strip.segment_exec( r_handler ,ii );
		}
	}

	/* ファイル上ゼロ(MIN)が白なら、白黒反転し、ゼロ(MIN)を黒に */
	if (PHOTOMETRIC_MINISWHITE==r_handler.photometric(isexist)) {
		invert_image_(
			r_handler.bitspersample(isexist)
			, image_bytes
			, image_array
		);
	}

	/* ORIENTATIONがTL(左上原点)の場合BL(OpenGL座標系=左下原点)に補正 */
	/* 正しい正対処理をする!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	if (r_handler.orientation(isexist) == ORIENTATION_TOPLEFT) {
		image::tif::reverse_top_bottom(
			  r_handler.imagelength(isexist)
			, r_handler.imagewidth(isexist)
			, r_handler.samplesperpixel(isexist)
			, r_handler.bitspersample(isexist)
			, static_cast<unsigned char *>(image_array)
		);
	}

	/* FILLORDER_MSB2LSBの補正はいままでしなかったのでまだしない */
    }
	r_handler.close();
}
//------------------------------------------------------------
#ifdef DEBUG_IMAGE_TIF_READER
#include <iostream> /* std::cout */
#include <fstream> /* std::fstream */
#include "image_tif_common.cpp"
#include "image_tif_read_handle.cpp"
#include "image_tif_read_handle_info.cpp"
int main(int argc , char *argv[])
{
	if (argc != 2) {
		std::cout << argv[0] << " tif_path\n";
		return 1;
	}
	std::cout << "file_path=" << argv[1] << std::endl;

 try {
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

	size_t image_bytes=0;
	size_t history_bytes=0;
	rdr.get_size( argv[1] ,image_bytes ,history_bytes );
	std::cout << "get_size image_bytes=" << image_bytes
		<< " history_bytes=" << history_bytes
		<< std::endl;

	image::common::properties props;
	std::string history_str;
	std::vector<uint8_t> image(image_bytes);
	static bool break_sw=false;
	rdr.get_data( argv[1] , props
	, image_bytes , image.data() , history_str
	, break_sw /* 中断Switch。外からtureで中断 */
	, 0 /* 分割読込の個々サイズ(tif以外で使用する) */
	);

	std::ofstream ofs( "tmp.raw" ,std::ios_base::binary );
	ofs.write( (char *)(image.data()) ,image.size() );
	ofs.close();
 }
 catch (std::exception& e) {
 	std::cerr << "Error : exception \"" << e.what() << "\"\n";
 }
 catch (...) {
 	std::cerr << "Error : other exception\n";
 }
	return 0;
}
#endif /* !DEBUG_IMAGE_TIF_READER */
//------------------------------------------------------------
#ifdef PLUGIN_IMAGE_TIF_READER
#include "image_tif_common.cpp"
#include "image_tif_read_handle.cpp"
#include "image_tif_read_handle_info.cpp"
#if defined _WIN32
extern "C" __declspec(dllexport) void *get_plugin_instance_reader(void);
#endif
namespace {
	image::tif::reader reader_instance;
}
void *get_plugin_instance_reader(void) {
	return &reader_instance;
}
#endif /* !PLUGIN_IMAGE_TIF_READER */

/*
rem /DUNICODE /D_UNICODE
rem make .exe
rem :691,692 w! makerwdump.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_IMAGE_TIF_READER /I. /I../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff image_tif_reader.cpp ../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff/libtiff.lib /Fea
del image_tif_reader.obj
rem
rem make .dll
rem :683,684 w! makedll.bat
cl /W4 /WX /MD /EHa /O2 /LD /source-charset:utf-8 /DPLUGIN_IMAGE_TIF_READER /I. /I../../thirdparty/libtiff/tiff-4.0.9/libtiff image_tif_reader.cpp ../../thirdparty/libtiff/tiff-4.0.9/libtiff/libtiff.lib /Feplugin_image_tif_reader
del image_tif_reader.obj
#
# :674,675 w! make.sh
g++ -Wall -std=c++11 image_tif_reader.cpp image_tif_read_handle.cpp image_tif_read_handle_info.cpp image_tif_common.cpp -DDEBUG_IMAGE_TIF_READER -I. -ltiff
*/

