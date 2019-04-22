#include <iostream>	// std::cout
#include <limits>	// std::numeric_limits
#include <sstream>	// std::ostringstream
#include <iomanip>	// std::setw(-)
#include "image_tif_read_handle.h"
#include "image_tif_read_handle_info.h"

namespace image {
namespace tif {

std::string get_info(
	  const std::string& name
	, const std::string& file_path
) {
	std::ostringstream os; 
	bool isexist = false;

	 os << name << '\n';

	image::tif::read_handle handler(file_path);

	 os << " Byte Order : ";
	union { unsigned short us; unsigned char uc[2]; } order_box;
	order_box.us = 1;
	const bool cpu_is_little_endian = (1==order_box.uc[0])?true:false;
	const bool byte_swap_sw = (TIFFIsByteSwapped(handler))?true:false;
	if (( (!cpu_is_little_endian) == (!byte_swap_sw) ) ||
	    (   cpu_is_little_endian  ==   byte_swap_sw   )) {
	     /*	CPUがbig    endian(false)でbyte swapしてない(false)か、
		CPUがlittle endian(true )でbyte swapした(true) */
	 os << "Big Endian";
	} else {
	 os << "Little Endian";
	}
	 os << "\n";

	 os << " Compression : ";
	const unsigned int u_compre = handler.compression(isexist);
	switch (u_compre) {
	case COMPRESSION_NONE:		os << "NONE"; break;
	case COMPRESSION_CCITTRLE:	os << "CCITTRLE"; break;
	case COMPRESSION_CCITTFAX3:	os << "CCITTFAX3"; break;
	case COMPRESSION_CCITTFAX4:	os << "CCITTFAX4"; break;
	case COMPRESSION_LZW:		os << "LZW"; break;
	case COMPRESSION_OJPEG:		os << "OJPEG"; break;
	case COMPRESSION_JPEG:		os << "JPEG"; break;
	case COMPRESSION_NEXT:		os << "NEXT"; break;
	case COMPRESSION_CCITTRLEW:	os << "CCITTRLEW"; break;
	case COMPRESSION_PACKBITS:	os << "PACKBITS"; break;
	case COMPRESSION_THUNDERSCAN:	os << "THUNDERSCAN"; break;
	/* codes 32895-32898 are reserved for ANSI IT8 TIFF/IT <dkelly@etsinc.com) */
	case COMPRESSION_IT8CTPAD:	os << "IT8CTPAD"; break;
	case COMPRESSION_IT8LW:		os << "IT8LW"; break;
	case COMPRESSION_IT8MP:		os << "IT8MP"; break;
	case COMPRESSION_IT8BL:		os << "IT8BL"; break;
	/* compression codes 32908-32911 are reserved for Pixar */
	case COMPRESSION_PIXARFILM:	os << "PIXARFILM"; break;
	case COMPRESSION_PIXARLOG:	os << "PIXARLOG"; break;
	case COMPRESSION_DEFLATE:	os << "DEFLATE"; break;
	case COMPRESSION_ADOBE_DEFLATE:	os << "ADOBE DEFLATE"; break;
	/* compression code 32947 is reserved for Oceana Matrix <dev@oceana.com> */
	case COMPRESSION_DCS:		os << "DCS"; break;
	case COMPRESSION_JBIG:		os << "JBIG"; break;
	case COMPRESSION_SGILOG:	os << "SGILOG"; break;
	case COMPRESSION_SGILOG24:	os << "SGILOG24"; break;
	default:
		{
			os	<< "Bad_Compression_Type"
				<< '(' << u_compre << ')';
		}
		break;
	}
	 os << "\n";

	//------------------------------------------------------------

	 os << "Image\n"
	    << " Size : "
	    << handler.imagewidth(isexist)
	    << " x "
	    << handler.imagelength(isexist)
	    << "  "
	    ;
	if      (1 == handler.samplesperpixel(isexist)) {
	 if (1 == handler.bitspersample(isexist)) { os << "MonoBW"; }
	 else				   { os << "Grayscale"; }
	}
	else if (3 == handler.samplesperpixel(isexist)) { os << "RGB"; }
	else if (4 == handler.samplesperpixel(isexist)) { os << "RGBA"; }
	else {
	 os << "Bad_Samples_Per_Pixel"
	    << '(' << handler.samplesperpixel(isexist) << ')';
	}

	 os
	    << ' '
	    << handler.bitspersample(isexist)
	    << " bit";
	if (1 < handler.bitspersample(isexist)) {
	 os << 's';
	}
	 os << '\n';

	 os << " Resolution : ";

	const unsigned int u_re = handler.resolutionunit(isexist);
	if (std::numeric_limits<unsigned int>::max() == u_re) {
		os << "Not Defined";
	} else {
		switch (u_re) {
		case RESUNIT_INCH:
		case RESUNIT_CENTIMETER:
			os << handler.xresolution(isexist);
		 if (handler.xresolution(isexist) != handler.yresolution(isexist)) {
			os << " x " << handler.yresolution(isexist);
		 }
			os << ' ';
		}
		switch (u_re) {
		case RESUNIT_NONE:       os << "Nothing"; break;
		case RESUNIT_INCH:       os << "Dot/Inch"; break;
		case RESUNIT_CENTIMETER: os << "Dot/Centimeter"; break;
		default: os	<< "Bad_Unit_Type"
				<< '(' << (int)u_re << ')';
			break;
		}
	}
	 os << '\n';

	 os << " Orientation(Row Column) : ";
	const unsigned int u_or = handler.orientation(isexist);
	if (std::numeric_limits<unsigned int>::max() == u_or) {
				    os << "Not Defined";
	} else {
	 switch (u_or) {
	 case 0:
	 case ORIENTATION_TOPLEFT:  os << "Top Left"; break;
	 case ORIENTATION_TOPRIGHT: os << "Top Right"; break;
	 case ORIENTATION_BOTRIGHT: os << "Bottom Right"; break;
	 case ORIENTATION_BOTLEFT:  os << "Bottom Left"; break;
	 case ORIENTATION_LEFTTOP:  os << "Left Top"; break;
	 case ORIENTATION_RIGHTTOP: os << "Right Top"; break;
	 case ORIENTATION_RIGHTBOT: os << "Right Bottom"; break;
	 case ORIENTATION_LEFTBOT:  os << "Left Bottom"; break;
	 default: os	<< "Bad_Orientation_Type"
			<< '(' << (int)u_or << ')';
	 }
	}
	 os << '\n';

	return os.str();
}
//--------------------------------------------------------------------
std::string get_line_head(void) {
	std::string line_head;
	line_head += "bo  compr width heigh c bi or pho pla bit";
	line_head += " reso x y (tile) file\n";
	return line_head;
}
std::string get_line_info(
	const std::string& file_path
) {
	/* TIFFファイル開く ------------------------------- */
	image::tif::read_handle handler(file_path.c_str());
	bool isexist = false;

	std::ostringstream os;

	/* TIFFファイルのバイトオーダ --------------------- */
	union { unsigned short us; unsigned char uc[2]; } order_box;
	order_box.us = 1;
	const bool cpu_is_little_endian = (1==order_box.uc[0])?true:false;
	const bool byte_swap_sw = (TIFFIsByteSwapped(handler))?true:false;
	if (( (!cpu_is_little_endian) == (!byte_swap_sw) ) ||
	    (   cpu_is_little_endian  ==   byte_swap_sw  )) {
	     /*	CPUがbig    endian(false)でbyte swapしてない(false)か、
		CPUがlittle endian(true )でbyte swapした(true) */
		os << "big";
	} else {
		os << "lit";
	}

	/* このライブラリで扱えるか否か ------------------- */
	bool b_canuse_sw = true;
 try {
	handler.check_parameters();
 }
 // catch (std::exception& e) {
	// std::cout << e.what() << '\n';
 catch (std::exception) {
	b_canuse_sw = false;
 }
	if (b_canuse_sw) { os << " "; }
	else             { os << "x"; }

	/* 圧縮タイプ ------------------------------------- */
#if 0 //------help------
標仕仕様
#define	COMPRESSION_NONE	1	/* dump mode */
#define	COMPRESSION_CCITTRLE	2	/* CCITT modified Huffman RLE */
#define	COMPRESSION_PACKBITS	32773	/* Macintosh RLE */

拡張仕様
#define	COMPRESSION_CCITTFAX3	3	/* CCITT Group 3 fax encoding */
#define	COMPRESSION_CCITT_T4	3       /* CCITT T.4 (TIFF 6 name) */
#define	COMPRESSION_CCITTFAX4	4	/* CCITT Group 4 fax encoding */
#define	COMPRESSION_CCITT_T6	4       /* CCITT T.6 (TIFF 6 name) */
#define	COMPRESSION_LZW		5       /* Lempel-Ziv  & Welch */
#define	COMPRESSION_JPEG	7	/* %JPEG DCT compression */
#endif //------help------
	const unsigned int u_compre = handler.compression(isexist);
	char *cp_compre = 0;
	switch (u_compre) {
	case COMPRESSION_NONE:		cp_compre = "dump "; break;
	case COMPRESSION_CCITTRLE:	cp_compre = "crle "; break;
	case COMPRESSION_CCITTFAX3:	cp_compre = "cfax3"; break;
	case COMPRESSION_CCITTFAX4:	cp_compre = "cfax4"; break;
	case COMPRESSION_LZW:		cp_compre = "lzw  "; break;
	case COMPRESSION_OJPEG:		cp_compre = "ojpeg"; break;
	case COMPRESSION_JPEG:		cp_compre = "jpeg "; break;
	case COMPRESSION_NEXT:		cp_compre = "next "; break;
	case COMPRESSION_CCITTRLEW:	cp_compre = "crlew"; break;
	case COMPRESSION_PACKBITS:	cp_compre = "packb"; break;
	case COMPRESSION_THUNDERSCAN:	cp_compre = "thund"; break;
	/* codes 32895-32898 are reserved for ANSI IT8 TIFF/IT <dkelly@etsinc.com) */
	case COMPRESSION_IT8CTPAD:	cp_compre = "it8ct"; break;
	case COMPRESSION_IT8LW:		cp_compre = "it8lw"; break;
	case COMPRESSION_IT8MP:		cp_compre = "it8mp"; break;
	case COMPRESSION_IT8BL:		cp_compre = "it8bl"; break;
	/* compression codes 32908-32911 are reserved for Pixar */
	case COMPRESSION_PIXARFILM:	cp_compre = "pixfi"; break;
	case COMPRESSION_PIXARLOG:	cp_compre = "pixlo"; break;
	case COMPRESSION_DEFLATE:	cp_compre = "defla"; break;
	case COMPRESSION_ADOBE_DEFLATE:	cp_compre = "adefl"; break;
	/* compression code 32947 is reserved for Oceana Matrix <dev@oceana.com> */
	case COMPRESSION_DCS:		cp_compre = "dcs  "; break;
	case COMPRESSION_JBIG:		cp_compre = "jbig "; break;
	case COMPRESSION_SGILOG:	cp_compre = "sgilo"; break;
	case COMPRESSION_SGILOG24:	cp_compre = "sgi24"; break;
	}
	if (0 == cp_compre) {
		os << std::setw(5) <<  u_compre; }
	else {			os << cp_compre; }

	/* 画像幅 ----------------------------------------- */
	os << ' ' << std::setw(5) << handler.imagewidth(isexist);
	/* 画像高さ --------------------------------------- */
	os << ' ' << std::setw(5) << handler.imagelength(isexist);
	/* チャンネル数 ----------------------------------- */
	os << ' ' << std::setw(1) << handler.samplesperpixel(isexist);
	/* サンプリングビット数 --------------------------- */
	os << ' ' << std::setw(2) << handler.bitspersample(isexist);
	/* 画像向き --------------------------------------- */
	const unsigned int u_orient = handler.orientation(isexist);
	char *cp_orient = 0;
/*
2008-04-17
VC8(vc2005)およびVC6で
std::numeric_limits<unsigned int>::max()
は
#include <windows.h>
があることで
#define max(a,b) ...
によってつぶされてしまうので
-DNOMINMAX
を指定してコンパイルするか
#define NOMINMAX
をソースコードに定義するか
(std::numeric_limits<unsigned int>::max)()
とする
http://support.microsoft.com/kb/143208/ja
*/
	if (std::numeric_limits<unsigned int>::max() == u_orient) {
					cp_orient = "nd"; }
	switch (u_orient) {
	case ORIENTATION_TOPLEFT:	cp_orient = "TL"; break;
	case ORIENTATION_TOPRIGHT:	cp_orient = "TR"; break;
	case ORIENTATION_LEFTTOP:	cp_orient = "LT"; break;
	case ORIENTATION_RIGHTTOP:	cp_orient = "RT"; break;
	case ORIENTATION_BOTRIGHT:	cp_orient = "BR"; break;
	case ORIENTATION_BOTLEFT:	cp_orient = "BL"; break;
	case ORIENTATION_RIGHTBOT:	cp_orient = "RB"; break;
	case ORIENTATION_LEFTBOT:	cp_orient = "LB"; break;
	}
	 /* zero is made in photoshop does it? */
	if (0 == cp_orient) {
		os << ' ' << std::setw(2) <<  u_orient; }
	else {			os << ' ' << cp_orient; }

	/* 画像種類 --------------------------------------- */
	const unsigned int u_photom = handler.photometric(isexist);
	char *cp_photom = 0;
	switch (u_photom) {
	case PHOTOMETRIC_MINISWHITE:	cp_photom = "mw "; break;
	case PHOTOMETRIC_MINISBLACK:	cp_photom = "mb "; break;
	case PHOTOMETRIC_RGB:		cp_photom = "rgb"; break;
	case PHOTOMETRIC_MASK:		cp_photom = "mas"; break;
	case PHOTOMETRIC_SEPARATED:	cp_photom = "sep"; break;
	case PHOTOMETRIC_YCBCR:		cp_photom = "ycb"; break;
	case PHOTOMETRIC_CIELAB:	cp_photom = "cie"; break;
	case PHOTOMETRIC_ITULAB:	cp_photom = "itu"; break;
	case PHOTOMETRIC_LOGL:		cp_photom = "log"; break;
	case PHOTOMETRIC_LOGLUV:	cp_photom = "lov"; break;
	}
	if (0 == cp_photom) {
		os << ' ' << std::setw(3) <<  u_photom; }
	else {			os << ' ' << cp_photom; }

	/* 画像格納順序 ----------------------------------- */
	const unsigned int u_planar = handler.planarconfig(isexist);
	char *cp_planar=0;
	switch (u_planar) {
	case PLANARCONFIG_CONTIG:	cp_planar = "con"; break;
	case PLANARCONFIG_SEPARATE:	cp_planar = "sep"; break;
	}
	if (0 == cp_planar) {
		os << ' ' << std::setw(1) <<  u_planar; }
	else {			os << ' ' << cp_planar; }

	/* データビットの向き ----------------------------- */
	const unsigned int u_fillor = handler.fillorder(isexist);
	char *cp_fillor = 0;
	if (std::numeric_limits<unsigned int>::max() == u_fillor) {
				cp_fillor = "nd "; }
	switch (u_fillor) {
	case FILLORDER_MSB2LSB: cp_fillor = "M2L"; break;
	case FILLORDER_LSB2MSB: cp_fillor = "L2M"; break;
	}
	if (0 == cp_fillor) {
		os << ' ' << std::setw(3) <<  u_fillor; }
	else {			os << ' ' << cp_fillor; }

	/* 画像解像度 ------------------------------------- */
	const unsigned int u_resolu = handler.resolutionunit(isexist);
	char *cp_resolu = 0;
	if (std::numeric_limits<unsigned int>::max() == u_resolu) {
				cp_resolu = "nd  "; }
	switch (u_resolu) {
	case RESUNIT_NONE:	cp_resolu = "noth"; break;
	case RESUNIT_INCH:	cp_resolu = "inch"; break;
	case RESUNIT_CENTIMETER:cp_resolu = "cent"; break;
	}
	if (0 == cp_resolu) {
		os << ' ' << std::setw(4) <<  u_resolu; }
	else {			os << ' ' << cp_resolu; }

	os << ' ' << handler.xresolution(isexist);
	os << ' ' << handler.yresolution(isexist);

	/* タイルformatの場合 ----------------------------- */
	if (TIFFIsTiled( handler )) {
		os
			<< " ("
			<< handler.tilewidth(isexist)
			<< ' '
			<< handler.tilelength(isexist)
			<< ')';
	}
	/* ファイル名(ディレクトリパスを除く) ------------- */
	std::string::size_type  index = file_path.rfind('/');
	if (std::string::npos == index) {
				index = file_path.rfind('\\');
	}
	if (std::string::npos == index) {
		os << ' ' << file_path;
	} else {
		os << ' ' << file_path.substr(index+1);
	}
	/* 改行コード ------------------------------------- */
	os << "\n";

	/* TIFFファイル閉じる ----------------------------- */
	// handler.v_close();

	return os.str();
}

} // namespace tif
} // namespace image

//--------------------------------------------------------------------
namespace {
 struct tif_help_list_ {
	char *short_name;
	char *define_name;
	int define_number;
	char *explain;
 };
 std::string get_tif_help_list_info_(
	const char *title
	, const char *tag_name
	, unsigned int each_size
	, tif_help_list_ *help_list
 ) {
	std::ostringstream os; 

	os	<< std::setw(6) << std::left << title << "\n"
		<< "  (" << tag_name << ")\n";
	for(size_t ii = 0; ii <each_size/sizeof(tif_help_list_); ++ii) {
		os	<< "    "
			<< std::setw(5) << std::left
			<< help_list[ii].short_name
			<< " ("
			<< std::setw(25) << std::left
			<< help_list[ii].define_name
			<< std::setw(5) << std::right
			<< help_list[ii].define_number
			<< ')'
			<< help_list[ii].explain
			<< '\n';
	}
	return os.str();
 }
} // namespace

namespace image {
namespace tif {

/* 圧縮種類のリスト */
std::string get_compression_list(void) {
	tif_help_list_ tif_compr_list[] = {
{ "dump ","COMPRESSION_NONE",	        1,"dump mode" },
{ "crle ","COMPRESSION_CCITTRLE",       2,"CCITT modified Huffman RLE" },
{ "cfax3","COMPRESSION_CCITTFAX3",      3,"CCITT Group 3 fax encoding" },
{ "cfax4","COMPRESSION_CCITTFAX4",      4,"CCITT Group 4 fax encoding" },
{ "lzw  ","COMPRESSION_LZW",	        5,"Lempel-Ziv  & Welch" },
{ "ojpeg","COMPRESSION_OJPEG",	        6,"!6.0 JPEG" },
{ "jpeg ","COMPRESSION_JPEG",	        7,"%JPEG DCT compression" },
{ "next ","COMPRESSION_NEXT",	    32766,"NeXT 2-bit RLE" },
{ "crlew","COMPRESSION_CCITTRLEW",  32771,"#1 w/ word alignment" },
{ "packb","COMPRESSION_PACKBITS",   32773,"Macintosh RLE" },
{ "thund","COMPRESSION_THUNDERSCAN",32809,"ThunderScan RLE" },
{ "it8ct","COMPRESSION_IT8CTPAD",   32895,"reserved for IT8 CT w/padding" },
{ "it8lw","COMPRESSION_IT8LW",      32896,"reserved for IT8 Linework RLE" },
{ "it8mp","COMPRESSION_IT8MP",      32897,"reserved for IT8 Monochrome picture" },
{ "it8bl","COMPRESSION_IT8BL",      32898,"reserved for IT8 Binary line art" },
{ "pixfi","COMPRESSION_PIXARFILM",  32908,"reserved for Pixar companded 10bit LZW" },
{ "pixlo","COMPRESSION_PIXARLOG",   32909,"reserved for Pixar companded 11bit ZIP" },
{ "defla","COMPRESSION_DEFLATE",    32946,"Deflate compression" },
{ "adefl","COMPRESSION_ADOBE_DEFLATE",  8,"Deflate compression, as recognized by Adobe" },
{ "dcs  ","COMPRESSION_DCS",        32947,"reserved for Kodak DCS encoding" },
{ "jbig ","COMPRESSION_JBIG",       34661,"ISO JBIG" },
{ "sgilo","COMPRESSION_SGILOG",     34676,"SGI Log Luminance RLE" },
{ "sgi24","COMPRESSION_SGILOG24",   34677,"SGI Log 24-bit packed" },
	};
 	return get_tif_help_list_info_(
		"compr"
		,"TIFFTAG_COMPRESSION"
		, sizeof(tif_compr_list)
		, tif_compr_list
	);
}
/* 画像向き種類のリスト */
std::string get_orientation_list(void) {
	tif_help_list_ tif_orient_list[] = {
{ "nd","not defined in file",	0,"" },
{ "TL","ORIENTATION_TOPLEFT",	1,"row 0 top, col 0 lhs" },
{ "TR","ORIENTATION_TOPRIGHT",	2,"row 0 top, col 0 rhs" },
{ "LT","ORIENTATION_BOTRIGHT",	3,"row 0 bottom, col 0 rhs" },
{ "RT","ORIENTATION_BOTLEFT",	4,"row 0 bottom, col 0 lhs" },
{ "BR","ORIENTATION_LEFTTOP",	5,"row 0 lhs, col 0 top" },
{ "BL","ORIENTATION_RIGHTTOP",	6,"row 0 rhs, col 0 top" },
{ "RB","ORIENTATION_RIGHTBOT",	7,"row 0 rhs, col 0 bottom" },
{ "LB","ORIENTATION_LEFTBOT",	8,"row 0 lhs, col 0 bottom" },
	};
	return get_tif_help_list_info_(
		"or"
		, "TIFFTAG_ORIENTATION"
		, sizeof(tif_orient_list)
		, tif_orient_list
	);
}
/* 画像種類リスト */
std::string get_photometric_list(void) {
	tif_help_list_ tif_photom_list[] = {
{ "mw ","PHOTOMETRIC_MINISWHITE",	0,"min value is white" },
{ "mb ","PHOTOMETRIC_MINISBLACK",	1,"min value is black" },
{ "rgb","PHOTOMETRIC_RGB",		2,"RGB color model" },
{ "mas","PHOTOMETRIC_MASK",		4,"$holdout mask" },
{ "sep","PHOTOMETRIC_SEPARATED",	5,"!color separations" },
{ "ycb","PHOTOMETRIC_YCBCR",		6,"!CCIR 601" },
{ "cie","PHOTOMETRIC_CIELAB",		8,"!1976 CIE L*a*b*" },
{ "itu","PHOTOMETRIC_ITULAB",		10,"ITU L*a*b*" },
{ "log","PHOTOMETRIC_LOGL",		32844,"CIE Log2(L)" },
{ "lov","PHOTOMETRIC_LOGLUV",		32845,"CIE Log2(L) (u',v')" },
	};
	return get_tif_help_list_info_(
		"pho"
		, "TIFFTAG_PHOTOMETRIC"
		, sizeof(tif_photom_list)
		, tif_photom_list
	);
}
/* 画像格納順序リスト */
std::string get_planarconfig_list(void) {
	tif_help_list_ tif_planar_list[] = {
{ "con","PLANARCONFIG_CONTIG",		1,"single image plan" },
{ "sep","PLANARCONFIG_SEPARATE",	2,"separate planes of data" },
	};
	return get_tif_help_list_info_(
		"pla"
		, "TIFFTAG_PLANARCONFIG"
		, sizeof(tif_planar_list)
		, tif_planar_list
	);
}
/* データビットの向きリスト */
std::string get_fillorder_list(void) {
	tif_help_list_ tif_fillor_list[] = {
{ "nd ","not defined in file",		0,"" },
{ "M2L","FILLORDER_MSB2LSB",	1,"most significant -> least" },
{ "L2M","FILLORDER_LSB2MSB",	2,"least significant -> most" },
	};
	return get_tif_help_list_info_(
		"bit"
		, "TIFFTAG_FILLORDER"
		, sizeof(tif_fillor_list)
		, tif_fillor_list
	);
}
void print_tiff_directory(int argc, char *argv[]) {
	for (int ii = 0; ii < argc; ++ii) {
		image::tif::read_handle handler(argv[ii]);
		std::cout << "File : " << argv[ii] << '\n';
		TIFFPrintDirectory(handler,stdout
			/***,TIFFPRINT_STRIPS |
			TIFFPRINT_CURVES |
			TIFFPRINT_COLORMAP |
			TIFFPRINT_JPEGQTABLES |
			TIFFPRINT_JPEGACTABLES |
			TIFFPRINT_JPEGDCTABLES***/
		);
	}
}

} // namespace image
} // namespace tif

#ifdef DEBUG_IMAGE_TIF_READ_HANDLE_INFO
#include "image_tif_common.cpp"
#include "image_tif_read_handle.cpp"
namespace {
 void print_column_(int argc, char *argv[]) {
	std::string info;
	info += image::tif::get_line_head();
	for (int ii = 0; ii < argc; ++ii) {
		info += image::tif::get_line_info( argv[ii] );
	}
	std::cout << info;
 }
 void print_info_(int argc, char *argv[]) {
	std::string info;
	for (int ii = 0; ii < argc; ++ii) {
		info += image::tif::get_info( "TIFF" ,argv[ii] );
	}
	std::cout << info;
 }
}

int main(int argc, char** argv) {
	if (argc <= 1) {
		std::cout
	<< "Usage : " << argv[0] << " [-tifinfo/-tifdir] image.tif ...\n"
	<< "Usage : " << argv[0] << " -tifhelp\n"
	<< "[Options]\n"
	<< "\t-tifdir  : tiff detail<.tif>\n"
		;
		return 0;
	}
 try {
	if (!strcmp( "-tifinfo", argv[1] ) ) {
		print_info_( argc-2, &argv[2] );
	}
	else if (!strcmp( "-tifdir", argv[1] ) ) {
		image::tif::print_tiff_directory( argc-2, &argv[2] );
	}
	else if (!strcmp( "-tifhelp", argv[1] ) ) {
		std::cout << image::tif::get_compression_list();
		std::cout << image::tif::get_orientation_list();
		std::cout << image::tif::get_photometric_list();
		std::cout << image::tif::get_planarconfig_list();
		std::cout << image::tif::get_fillorder_list();
	}
	else {
		print_column_( argc-1, &argv[1] );
	}
 }
 catch (std::exception& e) {
	std::cout << e.what() << '\n';
 }
	return 0;
}
#endif
/*
rem :596,597 w! maketiffinfo.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /DDEBUG_IMAGE_TIF_READ_HANDLE_INFO /I. /I../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff image_tif_read_handle_info.cpp ../../thirdparty/libtiff/tiff-4.0.9_x32/libtiff/libtiff.lib /Fetiffinfo
del image_tif_read_handle_info.obj
# :605,605 w! make.sh
g++ -Wall -std=c++11 image_tif_read_handle_info.cpp image_tif_common.cpp image_tif_read_handle.cpp -DDEBUG_IMAGE_TIF_READ_HANDLE_INFO -I. -ltiff
*/
