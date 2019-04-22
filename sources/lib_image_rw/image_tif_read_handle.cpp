#include <limits> /* std::numeric_limits */
#include <stdexcept> /* std::runtime_error */
#include <sstream> /* std::ostringstream */
#include "image_tif_common.h"
#include "image_tif_read_handle.h"

/* libtiffのTIFFヘッダ用スマートクラス定義 */
//------------------------------------------------------------
using image::tif::read_handle;
read_handle::read_handle(const std::string& file_path)
	:p_(nullptr)
{
	TIFFSetErrorHandler( image::tif::error_handler );

	const char *const mode = "r";
	/* mode "r"	読みこみ
		"w"	書き出し
		"wl"	LittleEndianで書き出し --> 使わない
		"wb"	BigEndianで書き出し --> 使わない
	*/
//try {
	this->p_ = TIFFOpen( file_path.c_str() ,mode );
//}
//catch (std::exception& e) {
//	std::cout << "---" << e.what() << "---" << std::endl;
//}
//std::cout << __FILE__ << " " << __LINE__ << " end" << std::endl;
	/* ファイルがない等のときはエラーとなりハンドラから例外を投げる */
}
void read_handle::close(void)
{ if (this->p_ != nullptr) { TIFFClose(this->p_); this->p_ = nullptr; } } 
read_handle::~read_handle()
{ try { this->close(); } catch(...) {} } /* destractorの例外を無効化 */
//------------------------------------------------------------
/* 必須タグのTIFF情報を得る
	必須タグが存在せずデフォルト値もないとエラー例外投げる
	戻り値は情報が存在するならtrue存在しなければfalseを返す

	タグ(define)		タグ(10進数)	デフォルト値
	TIFFTAG_IMAGEWIDTH	0100H(256)	なし
	TIFFTAG_IMAGELENGTH	0101H(257)	なし
	TIFFTAG_BITSPERSAMPLE	0102H(258)	1
	TIFFTAG_COMPRESSION	0103H(259)	1
	TIFFTAG_PHOTOMETRIC	0106H(262)	なし

	0111H(273)	StripOffsets	なし
	0116H(278)	RowsPerStrip	(２32 - 1)
	0117H(279)	StripByteCounts	なし

	TIFFTAG_XRESOLUTION	011AH(282)	なし
	TIFFTAG_YRESOLUTION	011BH(283)	なし
	TIFFTAG_RESOLUTIONUNIT	0128H(296)	2

	0140H(320)	ColorMap	なし

*/
uint32 read_handle::imagewidth( bool& isexist ) {
	uint32 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_IMAGEWIDTH ,&val) == 1 ?true :false);
	if ( !isexist ) {
		/* この必須タグが存在せずデフォルト値もないのでエラー */
		std::ostringstream os; os << "Not exist Tag"
	   "TIFFTAG_IMAGEWIDTH and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
uint32 read_handle::imagelength( bool& isexist ) {
	uint32 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_IMAGELENGTH ,&val) == 1 ?true :false);
	if ( !isexist ) {
		/* この必須タグが存在せずデフォルト値もないのでエラー */
		std::ostringstream os; os << "Not exist Tag"
	   "TIFFTAG_IMAGELENGTH and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
uint16 read_handle::bitspersample( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_BITSPERSAMPLE ,&val) == 1 ?true :false);
	if ( !isexist ) { /* この必須タグが存在しないときのデフォルト値 */
		val = 1;
	}
	return val;
}
uint16 read_handle::compression( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_COMPRESSION ,&val) == 1 ?true :false);
	if ( !isexist ) { /* この必須タグが存在しないときのデフォルト値 */
		val = COMPRESSION_NONE;
	}
	return val;
}
uint16 read_handle::photometric( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_PHOTOMETRIC ,&val) == 1 ?true :false);
	if ( !isexist ) {
		/* この必須タグが存在せずデフォルト値もないのでエラー */
		std::ostringstream os; os << "Not exist Tag"
	   "TIFFTAG_PHOTOMETRIC and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
float read_handle::xresolution( bool& isexist ) {
	float val = 0; isexist = (TIFFGetField(this->p_
	,  TIFFTAG_XRESOLUTION ,&val) == 1 ?true :false);
	if ( !isexist ) {
		/* この必須タグが存在せずデフォルト値もないのでエラー */
		std::ostringstream os; os << "Not exist Tag"
	  "TIFFTAG_XRESOLUTION and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
float read_handle::yresolution( bool& isexist ) {
	float val = 0; isexist = (TIFFGetField(this->p_
	,  TIFFTAG_YRESOLUTION ,&val) == 1 ?true :false);
	if ( !isexist ) {
		/* この必須タグが存在せずデフォルト値もないのでエラー */
		std::ostringstream os; os << "Not exist Tag"
	  "TIFFTAG_YRESOLUTION and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
uint16 read_handle::resolutionunit( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_RESOLUTIONUNIT ,&val) == 1 ?true :false);
	if ( !isexist ) {
		/* この必須タグが存在しないときのデフォルト値 */
		val = RESUNIT_INCH;
	}
	return val;
}

/* 選択タグのTIFF情報を得る
	タグ(define)		タグ(10進数)	デフォルト値
	TIFFTAG_FILLORDER	266		なし
	TIFFTAG_ORIENTATION	274		なし
	TIFFTAG_SAMPLESPERPIXEL	277		なし
	TIFFTAG_PLANARCONFIG	284		なし
*/
uint16 read_handle::fillorder( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_FILLORDER ,&val) == 1 ?true :false);
	if ( !isexist	/* 存在しないとき */
	||  val == (uint16)0xffff	/* Saved Adobe Photoshop CS2 ??? */
	||  val == (uint16)0
	) {
		/* デフォルト値をimage::tif::read_handle独自に決める */
		val = FILLORDER_MSB2LSB;	/* =1 */
	}
	return val;
}
uint16 read_handle::orientation( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_ORIENTATION ,&val) == 1 ?true :false);
	if ( !isexist	/* 存在しないとき */
	||  val == (uint16)0xffff
	||  val == (uint16)0
	) {
		/* デフォルト値をimage::tif::read_handle独自に決める */
		val = ORIENTATION_TOPLEFT;	/* =1 */
	}
	return val;
}
uint16 read_handle::samplesperpixel( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_SAMPLESPERPIXEL ,&val) == 1 ?true :false);
	return val;
}
uint16 read_handle::planarconfig( bool& isexist ) {
	uint16 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_PLANARCONFIG ,&val) == 1 ?true :false);
	if ( !isexist	/* 存在しないとき */
	||  val == (uint16)0xffff
	||  val == (uint16)0
	) {
		/* デフォルト値をimage::tif::read_handle独自に決める */
		val = PLANARCONFIG_CONTIG; /* =1 =RGBRGB... */
	}
	return val;
}
/* Tile情報
	tilewidth()とtilelength()は
	istiled()によって必ずあるはずのときに呼ぶので、
	存在しないときはエラー例外を投げる

	タグ(define)		タグ(10進数)	デフォルト値
	TIFFTAG_TILEWIDTH	322		なし
	TIFFTAG_TILELENGTH	323		なし
*/
bool read_handle::istiled(void) {
	return TIFFIsTiled(this->p_) != 0 ?true :false;
}
uint32 read_handle::tilewidth( bool& isexist ) {
	uint32 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_TILEWIDTH ,&val) == 1 ?true :false);
	if ( !isexist ) {
		std::ostringstream os; os << "Not exist Tag"
	   "TIFFTAG_TILEWIDTH and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
uint32 read_handle::tilelength( bool& isexist ) {
	uint32 val = 0; isexist = (TIFFGetField(this->p_
	,   TIFFTAG_TILELENGTH ,&val) == 1 ?true :false);
	if ( !isexist ) {
		std::ostringstream os; os << "Not exist Tag"
	   "TIFFTAG_TILELENGTH and no default";
		throw std::runtime_error(os.str());
	}
	return val;
}
//------------------------------------------------------------
void
read_handle::check_parameters(void) {
	bool isexist = false;
	const unsigned int photomet = this->photometric(isexist);
	const unsigned int bitspers = this->bitspersample(isexist);
	const unsigned int samplesp = this->samplesperpixel(isexist);

/* pixelタイプ
画像種類	pixel channels	sampleing bits
---------------+--------------+---------------
RGBA		4		by_bi * sizeof(unsigned char)
				by_bi * sizeof(unsigned short)
RGB		3		by_bi * sizeof(unsigned char)
				by_bi * sizeof(unsigned short)
grayscale	1		by_bi * sizeof(unsigned char)
				by_bi * sizeof(unsigned short)
B/W		1		1
---------------+--------------+---------------
(※1) by_bi means std::numeric_limits<unsigned char>::digits
*/
	switch (photomet) {
	/* photometricが単チャンネルの場合 */
	case PHOTOMETRIC_MINISWHITE:
	case PHOTOMETRIC_MINISBLACK:
		/* サンプル数は一つでなければならない */
		if (1 != samplesp) {
			std::ostringstream os;
			os 	<< "mono must be 1channel,but "
				<< samplesp;
			throw std::runtime_error(os.str());
		}
		/* ビット数(1サンプルあたり)が、1,8,16のどれかで
		なければならない */
		switch (bitspers) {
		case 1:
		case std::numeric_limits<unsigned char>::digits:
		case std::numeric_limits<unsigned short>::digits:
			break;
		default:
			std::ostringstream os;
			os
			<< "mono channel must be "
			<< "1 or "
			<< std::numeric_limits<unsigned char>::digits
			<< " or "
			<< std::numeric_limits<unsigned short>::digits
			<< "bits,but "
			<< bitspers;
			throw std::runtime_error(os.str());
		}
		/*
		MonoBWのとき、MSB(最上位ビット)-->LSB(最下位ビット)
		の並びでなければならない
		Adobe Photoshop CS2 Windowsで保存したMonoBW画像には
		TIFFTAG_FILLORDERがない、ないときはMSB-LSBで扱う
		*/
		if (1 == bitspers) {
		 const unsigned int  u_fill = this->fillorder(isexist);
		 if ((
			std::numeric_limits<unsigned int>::max()!=u_fill
		 ) && (
			FILLORDER_MSB2LSB != u_fill
		 )) {
			std::ostringstream os;
			os	<< "TIFFTAG_FILLORDER(" << u_fill
				<< ") is not support";
			throw std::runtime_error(os.str());
		 }
		}
		break;

	/* photometricが複数チャンネル(フルカラー)の場合 */
	case PHOTOMETRIC_RGB:
		/* サンプル数が、3(RGB)か4(RGBA)でなければならない */
		if ((3 != samplesp) && (4 != samplesp)) {
			std::ostringstream os;
			os	<< "rgb(a) must be 3 or 4samples,but "
				<< samplesp;
			throw std::runtime_error(os.str());
		}
		/* ビット数(1サンプルあたり)が、8,16のどれかで
		なければならない */
		switch (bitspers) {
		case std::numeric_limits<unsigned char>::digits:
		case std::numeric_limits<unsigned short>::digits:
			break;
		default:
			std::ostringstream os;
			os
			<< "rgb(a) must be "
			<< std::numeric_limits<unsigned char>::digits
			<< " or "
			<< std::numeric_limits<unsigned short>::digits
			<< "bits,but "
			<< bitspers;
			throw std::runtime_error(os.str());
		}
		/* RGBRGBRGBの並びでなければならない */
		{
			const unsigned int u_plco = this->planarconfig(
							isexist);
			if (PLANARCONFIG_CONTIG != u_plco) {
/*			if ((PLANARCONFIG_CONTIG   != u_plco)
			&&  (PLANARCONFIG_SEPARATE != u_plco)) {
*/
				std::ostringstream os;
				os << "TIFFTAG_PLANARCONFIG(" << u_plco
				   << ") is not support";
				throw std::runtime_error(os.str());
			}
		}

		break;
	default:
		std::ostringstream os;
		os	<< "TIFFTAG_PHOTOMETRIC(" << photomet
			<< ") is not support";
		throw std::runtime_error(os.str());
	}

	/* 原点位置モード */
}
/* TIFF各パラメータの意味 */
std::string
read_handle::get_formed_parameter(void) {

	std::ostringstream ost;
	bool isexist = false;
	uint32 widt = this->imagewidth( isexist );
	uint32 leng = this->imagelength( isexist );
	uint16 samp = this->samplesperpixel( isexist );
	uint16 bits = this->bitspersample( isexist );
	uint16 orie = this->orientation( isexist );
	ost
	<< "--- Geometry ---" << std::endl
	<< "height         =" << leng << std::endl
	<< "width          =" << widt << std::endl
	<< "channels       =" << samp << std::endl
	<< "bits           =" << bits << std::endl
	<< "orientation    =" << orie << "\t" ;
	switch (this->orientation(isexist)) {
	case 0:
		ost  << "top_left(Saved old photoshop)"; break;
	case ORIENTATION_TOPLEFT:  /* =1 左上原点0度回転 TIFF,SGI */
		ost  << "top_left(default)"; break;
	case ORIENTATION_BOTLEFT:  /* =4 左下原点0度回転 OpenGL */
		ost  << "bot_left(save as OpenGL)"; break;
	case ORIENTATION_TOPRIGHT: /* =2 */
		ost  << "top_right"; break;
	case ORIENTATION_BOTRIGHT: /* =3 左上原点180度回転 */
		ost  << "bot_right"; break;
	case ORIENTATION_LEFTTOP:  /* =5 */
		ost  << "left_top"; break;
	case ORIENTATION_RIGHTTOP: /* =6 左上原点270度回転 */
		ost  << "right_top"; break;
	case ORIENTATION_RIGHTBOT: /* =7 */
		ost  << "right_bot"; break;
	case ORIENTATION_LEFTBOT:  /* =8 左上原点90度回転 */
		ost  << "left_bot"; break;
	default:
		ost << "bad orientation"; break;
	}
	ost << std::endl; 
	ost
	<< "resolution_unit=" << this->resolutionunit(isexist) << "\t";
	switch (this->resolutionunit(isexist)) {
	case RESUNIT_NONE:	ost << "none"; break;
	case RESUNIT_INCH:	ost << "inch"; break;
	case RESUNIT_CENTIMETER:ost << "centimeter"; break;
	default:
		ost << "bad resolution unit"; break;
	}
	ost << std::endl;
	ost
	<< "resolution_x   =" << this->xresolution(isexist) << std::endl
	<< "resolution_y   =" << this->yresolution(isexist) << std::endl
	;

	ost
	<< "--- Pixel means ---" << std::endl;
	ost
	<< "photometric    =" << this->photometric(isexist) << "\t";
	switch (this->photometric(isexist)) {
	/* photometricが単チャンネルの場合 */
	case PHOTOMETRIC_MINISWHITE:
		ost << "min_is_white"; break;
	case PHOTOMETRIC_MINISBLACK:
		ost << "min_is_black"; break;
	case PHOTOMETRIC_RGB:
		ost << "rgb"; break;
	default:
		ost << "bad photometric"; break;
	}
	ost << std::endl;

	ost
	<< "--- FileForm ---" << std::endl;
	ost
	<< "compression    =" << this->compression(isexist) << "\t";
	switch (this->compression(isexist)) {
	case COMPRESSION_NONE:      /* =1 default */
		ost << "dump"; break;
	case COMPRESSION_CCITTRLE:  /* =2 BWのみ有効 */
		ost<<"bw:ccittrle"; break;
	case COMPRESSION_CCITTFAX3: /* =3 BWのみ有効 */
		ost<<"bw:ccittfax3"; break;
	case COMPRESSION_CCITTFAX4: /* =4 BWのみ有効 */
		ost<<"bw:ccittfax4"; break;
	case COMPRESSION_LZW:       /* =5 */
		ost<<"lzw"; break;
	case COMPRESSION_PACKBITS:  /* =32773 Macintosh RLE */
		ost  << "packbits(Macintosh RLE)"; break;
	case COMPRESSION_DEFLATE:   /* =32946 zip,gzip,PNG等で使用
	                        お薦めだがlibtiff-v3.5.7では使えない */
		ost  << "deflate"; break;
	default: ost << "bad compression"; break;
	}
	ost << std::endl;
	ost
	<< "planarconfig   =" << this->planarconfig(isexist) << "\t";
	switch (this->planarconfig(isexist)) {
	case PLANARCONFIG_CONTIG:
		ost << "RGBRGB... default"; break;
	case PLANARCONFIG_SEPARATE:
		ost << "RRRGGGBBB not Baseline TIFF"; break;
	default: ost << "bad planarconfig"; break;
	}
	ost << std::endl;
	if (this->istiled()) {
	 ost
	<< "tileheight     =" << this->tilelength(isexist) << std::endl
	<< "tilewidth      =" << this->tilewidth(isexist) << std::endl;
	} else {
	 ost
	<< "stripsize      =" << TIFFStripSize(this->p_) << std::endl
	<< "stripcount     =" << TIFFNumberOfStrips(this->p_)<<std::endl;
	}
	ost
	<< "fillorder      =" << this->fillorder(isexist) << "\t";
	switch (static_cast<unsigned int>(this->fillorder(isexist))) {
	case static_cast<unsigned int>(0xffffffff):
 		ost << "Saved Adobe Photoshop CS2 --> MSB2LSB";break;
	case static_cast<unsigned int>(FILLORDER_MSB2LSB):
		ost << "most significant bit -> least sig. default";break;
	case static_cast<unsigned int>(FILLORDER_LSB2MSB):
		ost << "least significant bit -> most sig.";break;
	default: ost << "bad fillorder"; break;
	}
	ost << std::endl;
	return ost.str();
}

//------------------------------------------------------------
#ifdef DEBUG_IMAGE_TIF_READ_HANDLE
#include <iostream> /* std::cout */
int main(int argc , char *argv[])
{
	if (argc != 2) {
		std::cout << argv[0] << " tif_path\n";
		return 1;
	}
	std::cout << "file_path " << argv[1] << std::endl;

 try {
	image::tif::read_handle hdl(argv[1]);

	std::cout << hdl.get_formed_parameter();
	hdl.check_parameters();

	hdl.close();
 }
 catch (std::exception& e) {
 	std::cerr << "Error : exception \"" << e.what() << "\"\n";
 }
 catch (...) {
 	std::cerr << "Error : other exception\n";
 }
	return 0;
}
#endif
/*
rem :541,542 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /DDEBUG_IMAGE_TIF_READ_HANDLE /I. /I../../thirdparty/libtiff/tiff-4.0.9/libtiff image_tif_read_handle.cpp image_tif_common.cpp ../../thirdparty/libtiff/tiff-4.0.9/libtiff/libtiff.lib /Fea
del image_tif_read_handle.obj image_tif_common.obj
# :445,445 w! make.sh
g++ -Wall -std=c++11 image_tif_read_handle.cpp image_tif_common.cpp -DDEBUG_IMAGE_TIF_READ_HANDLE -I. -ltiff
*/
