#include <iostream>
#include <stdexcept> /* std::domain_error */
#include <sstream> /* std::ostringstream */
#include "image_tif_common.h"
#include "image_tif_write_handle.h"

/* libtiffのTIFFヘッダ用スマートクラス定義 */
//------------------------------------------------------------
using image::tif::write_handle;
write_handle::write_handle(const std::string& file_path):
	p_(nullptr)
{
	TIFFSetErrorHandler( image::tif::error_handler );

	const char *const mode = "w";
	/* mode "r"	読みこみ
		"w"	書き出し --> CPU byte order 依存
		"wl"	littleendianで書き出し --> 使わない
		"wb"	bigendianで書き出し --> 使わない
	*/
	this->p_ = TIFFOpen( file_path.c_str() ,mode);
	/* ファイルがない等のときはエラーとなりハンドラから例外を投げる */
}
void write_handle::close(void)
{ if ( this->p_ != nullptr ) { TIFFClose(this->p_); this->p_ = nullptr; } } 
write_handle::~write_handle()
{ try { this->close(); } catch(...) {} } /* destractorの例外を無効化 */
//------------------------------------------------------------
void write_handle::set_uint16_throw( ttag_t tag ,const unsigned int val ) {
	TIFFSetField( this->p_ ,tag ,static_cast<uint16>(val) );
}
void write_handle::set_uint32_throw( ttag_t tag ,const unsigned int val ) {
	TIFFSetField( this->p_ ,tag ,static_cast<uint32>(val) );
}
void write_handle::set_float_throw( ttag_t tag ,const double val ) {
	TIFFSetField( this->p_ ,tag ,static_cast<float>(val) );
}
//------------------------------------------------------------
#ifdef DEBUG_IMAGE_TIF_WRITE_HANDLE
#include <iostream> /* std::cout */
#include "image_common.h"
#include "image_tif_common.cpp"

int main(int argc , char *argv[])
{
	if (argc != 2) {
		std::cout << argv[0] << " tif_path\n";
		return 1;
	}
	std::cout << "file_path " << argv[1] << std::endl;

 try {
	image::tif::write_handle hdl(argv[1]);

	image::common::properties props;

	props.height = 1980;
	props.width = 1080;
	props.channels = 3;
	props.bits = 16;
	props.reso_x = 300.0;
	props.reso_y = 300.0;
	//props.orie_side = 100;

	hdl.set_uint32_throw( TIFFTAG_IMAGELENGTH     , props.height );
	hdl.set_uint32_throw( TIFFTAG_IMAGEWIDTH      , props.width );
	hdl.set_uint16_throw( TIFFTAG_SAMPLESPERPIXEL , props.channels );
	hdl.set_uint16_throw( TIFFTAG_BITSPERSAMPLE   , props.bits );

	hdl.set_uint16_throw( TIFFTAG_ORIENTATION  , ORIENTATION_TOPLEFT );
	hdl.set_uint16_throw( TIFFTAG_PLANARCONFIG , PLANARCONFIG_CONTIG );
	hdl.set_uint16_throw( TIFFTAG_PHOTOMETRIC  , PHOTOMETRIC_RGB );

	hdl.set_uint16_throw( TIFFTAG_RESOLUTIONUNIT  , RESUNIT_INCH );
	hdl.set_float_throw(  TIFFTAG_XRESOLUTION     , props.reso_x );
	hdl.set_float_throw(  TIFFTAG_YRESOLUTION     , props.reso_y );

	/* わざとエラーを起す */
	hdl.set_uint16_throw( TIFFTAG_ORIENTATION, 100 );

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
rem :121,122 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /DDEBUG_IMAGE_TIF_WRITE_HANDLE /I. /I../../thirdparty/libtiff/tiff-4.0.9/libtiff image_tif_write_handle.cpp ../../thirdparty/libtiff/tiff-4.0.9/libtiff/libtiff.lib /Fea
del image_tif_write_handle.obj
# :445,445 w! make.sh
g++ -Wall -std=c++11 image_tif_write_handle.cpp -DDEBUG_IMAGE_TIF_WRITE_HANDLE -I. -ltiff
*/
