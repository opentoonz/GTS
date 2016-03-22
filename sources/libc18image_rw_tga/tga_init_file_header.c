#include "tga.h"

void tga_init_file_header( TGA_FILE_HEADER *tp_tga_head )
{
	tp_tga_head->uc_numid = 0;
	tp_tga_head->uc_maptyp = 0;
	tp_tga_head->uc_imgtyp = 0;
	tp_tga_head->s_maporig = 0;
	tp_tga_head->s_mapsize = 0;
	tp_tga_head->uc_mapbits = 0;
	tp_tga_head->s_xorig = 0;
	tp_tga_head->s_yorig = 0;
	tp_tga_head->s_xsize = 0;
	tp_tga_head->s_ysize = 0;
	tp_tga_head->uc_pixsize = 0;
	tp_tga_head->uc_imgdes = 0;
}
