#include "image_common.h"

namespace image { /* 画像に関する */
namespace common {

/* CPUのバイトオーダ */
std::string get_byte_order(void) {
	union { unsigned short us; unsigned char uc[2]; } order_box;
	order_box.us = 1;
	if (1 == order_box.uc[0]) {
	 return "cpu byte order is little endian\n";
	}
	 return "cpu byte order is big endian\n";
}

} // namespace common
} // namespace image

#ifdef DEBUG_IMAGE_COMMON
#include <iostream>
int main() 
{
	std::cout << "properties size="
		<< sizeof(image::common::properties) << "\n";

	image::common::properties pp;
	pp.height = 2000;
	pp.width = 1000;
	pp.channels = 4;
	pp.bits = 8;

	std::cout << image::common::get_byte_order();

	return 0;
}
#endif /* !DEBUG_IMAGE_COMMON */
/*
rem :39,40 w! make.bat
cl /W4 /WX /MD /EHa /O2 /source-charset:utf-8 /DUNICODE /DDEBUG_IMAGE_COMMON /I. image_common.cpp /Fea
del image_common.obj
# :42,42 w! make.sh
g++ -Wall -std=c++11 image_common.cpp -DDEBUG_IMAGE_COMMON -I.
*/
