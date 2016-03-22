#include "tga.h"

void tga_write_init( TGA_WRITE *tp_write )
{
	bwrite_init_head( &(tp_write->t_bwrite) );
	tga_init_file_header( &(tp_write->t_tga_file_header) );
}
