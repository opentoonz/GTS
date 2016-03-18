#include "tga.h"

void tga_read_init( TGA_READ *tp_read )
{
	bread_init_head( &(tp_read->t_bread) );
	tga_init_file_header( &(tp_read->t_tga_file_header) );
}
