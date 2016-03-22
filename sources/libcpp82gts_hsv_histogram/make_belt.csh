#
echo "static unsigned char _ucp_fltk_belt1000x10hue[] = {" > ! fltk_1000x10_hsv_belt_image.cpp
foreach f (0 1 2 3 4 5 6 7 8 9)
od -v -t uC -w8 -A n belt1000x1hue.raw | awk '{printf("\t0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",$1,$2,$3,$4,$5,$6,$7,$8);}' >> fltk_1000x10_hsv_belt_image.cpp
end
echo "};" >> fltk_1000x10_hsv_belt_image.cpp
#
echo "static unsigned char _ucp_fltk_belt1000x10sat[] = {" >> ! fltk_1000x10_hsv_belt_image.cpp
foreach f (0 1 2 3 4 5 6 7 8 9)
od -v -t uC -w8 -A n belt1000x1sat.raw | awk '{printf("\t0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",$1,$2,$3,$4,$5,$6,$7,$8);}' >> fltk_1000x10_hsv_belt_image.cpp
end
echo "};" >> fltk_1000x10_hsv_belt_image.cpp
#
echo "static unsigned char _ucp_fltk_belt1000x10val[] = {" >> ! fltk_1000x10_hsv_belt_image.cpp
foreach f (0 1 2 3 4 5 6 7 8 9)
od -v -t uC -w8 -A n belt1000x1val.raw | awk '{printf("\t0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,\n",$1,$2,$3,$4,$5,$6,$7,$8);}' >> fltk_1000x10_hsv_belt_image.cpp
end
echo "};" >> fltk_1000x10_hsv_belt_image.cpp
#
cat <<EOT >> fltk_1000x10_hsv_belt_image.cpp
#include <FL/Fl_Image.H>
#include "gts_master.h"
#include "gts_gui.h"
void gts_master::make_hab_belt_image( void )
{
	static Fl_RGB_Image image_belt1000x10hue(
		_ucp_fltk_belt1000x10hue, 1000, 10, 3, 0);
	cl_gts_gui.fltkp_hh_belt->image(image_belt1000x10hue);

	static Fl_RGB_Image image_belt1000x10sat(
		_ucp_fltk_belt1000x10sat, 1000, 10, 3, 0);
	cl_gts_gui.fltkp_aa_belt->image( image_belt1000x10sat);

	static Fl_RGB_Image image_belt1000x10val(
		_ucp_fltk_belt1000x10val, 1000, 10, 3, 0);
	cl_gts_gui.fltkp_bb_belt->image(image_belt1000x10val);
}
EOT
