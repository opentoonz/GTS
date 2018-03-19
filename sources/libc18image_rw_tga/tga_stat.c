#include <string.h>	/* strncpy() */
#include "ptbl_returncode.h"
#include "pri.h"

#include "cpu_byte_order_is_little_endian.h"
#include "tga_stat.h"

static void _tga_stat_detail_reading_byte_swap_info( int i_read_is_byte_swap )
{
	int i_file_is_swapped_order;

	int is_little_endian = cpu_byte_order_is_little_endian();

	/* ファイルのバイトオーダーは? */
	i_file_is_swapped_order = 
		/* CPUがbig endianで、swapして読んでる */
		( !is_little_endian && i_read_is_byte_swap )||

		/* CPUがlittle endianで、orderどおり読んでる */
		( is_little_endian && !i_read_is_byte_swap );

	(void)fprintf(stdout,
		"          cpu byte order         %s",
		is_little_endian ?"little endian" :"big endian" );
	(void)fprintf(stdout,
		" 0:big_endian(MIPS),1:little_endian(Intel)\n" );

	(void)fprintf(stdout,
		"          bread i_byte_swap_sw   %5d",
		i_read_is_byte_swap );
	(void)fprintf(stdout,
		" 0:order,1:read_with_swapping\n" );

	(void)fprintf(stdout,
		"bo        file byte order        %5d",
		i_file_is_swapped_order);
	(void)fprintf(stdout,
		" 0:order(big endian),1:swap(little endian)\n");
}

static void _tga_stat_detail_file_header( TGA_FILE_HEADER *tp_tga )
{
	(void)fprintf( stdout,
		"num       head uc_numid          %5d\n",
		tp_tga->uc_numid);
	(void)fprintf( stdout,
		"map       head uc_maptyp         %5d\n",
		tp_tga->uc_maptyp);
	(void)fprintf( stdout,
		"img       head uc_imgtyp         %5d\n",
		tp_tga->uc_imgtyp);
	(void)fprintf( stdout,
		"mapor     head us_maporig        %5d\n",
		tp_tga->s_maporig);
	(void)fprintf( stdout,
		"mapsi     head us_mapsize        %5d\n",
		tp_tga->s_mapsize);
	(void)fprintf( stdout,
		"mbi       head uc_mapbits        %5d\n",
		tp_tga->uc_mapbits);
	(void)fprintf( stdout,
		"xorig     head us_xorig          %5d\n",
		tp_tga->s_xorig);
	(void)fprintf( stdout,
		"yorig     head us_yorig          %5d\n",
		tp_tga->s_yorig);
	(void)fprintf( stdout,
		"xsize     head us_xsize          %5d\n",
		tp_tga->s_xsize);
	(void)fprintf( stdout,
		"ysize     head us_ysize          %5d\n",
		tp_tga->s_ysize);
	(void)fprintf( stdout,
		"pix       head uc_pixsize        %5d\n",
		tp_tga->uc_pixsize);
	(void)fprintf( stdout,
		"img       head uc_imgdes         %5d\n",
		tp_tga->uc_imgdes);
}

static void _tga_stat_detail_body( char *cp_filepath, TGA_READ *tp_read )
{
	/* ファイル名 */
	(void)fprintf(stdout,
		"filename  filepath '%s'\n", cp_filepath );

	/* ファイルポインタ */
	(void)fprintf(stdout,
		"          bread _fp          %p\n",
		tp_read->t_bread._fp );

	/* Read時の byte swap 情報 */
	_tga_stat_detail_reading_byte_swap_info(
		bread_get_byte_swap_sw(&(tp_read->t_bread)) == ON
	);

	/* tgaファイルのヘッダー部分 */
	_tga_stat_detail_file_header( &(tp_read->t_tga_file_header) );
}

int tga_stat_detail( int i_count, char **cpp_name)
{
	int	ii;
	TGA_READ	t_read;

	tga_read_init( &t_read );

	for (ii = 0; ii < i_count; ++ii) {
		if (OK != tga_read_open( cpp_name[ii], &t_read )) {
			pri_funct_err_bttvr(
			"Error : tga_read_open(%s,) returns NG.",
			cpp_name[ii] );
			return NG;
		}
		_tga_stat_detail_body( cpp_name[ii], &t_read );
		if (OK != tga_read_close( &t_read ) ) {
			pri_funct_err_bttvr(
			"Error : tga_read_close(-) returns NG.");
			return NG;
		}
	}

	return OK;
}

/********************************************************************/

static void _tga_stat_column_head( void )
{
	pri_funct_msg_vr(
 "bo  num map img mapor mapsi mbi xorig yorig xsize ysize pix img filename" );
}

static void _tga_stat_column_body( TGA_READ *tp_read, char *cp_filepath )
{
	int i_read_is_byte_swap;
	TGA_FILE_HEADER *tp_tga;
	char	*cp_byte_order;

	int is_little_endian = cpu_byte_order_is_little_endian();

	i_read_is_byte_swap =
		(bread_get_byte_swap_sw(&(tp_read->t_bread)) == ON);

	if (
		/* CPUがbig endianで、swapして読んでる */
		( !is_little_endian && i_read_is_byte_swap )||

		/* CPUがlittle endianで、orderどおり読んでる */
		( is_little_endian && !i_read_is_byte_swap )
	) {
		cp_byte_order = "lit";
	}
	else {
		cp_byte_order = "big";
	}
	tp_tga = &(tp_read->t_tga_file_header);

	(void)fprintf(stdout,
	"%3s %3d %3d %3d %5d %5d %3d %5d %5d %5d %5d %3d %3d %s\n",
	cp_byte_order,
	tp_read->t_tga_file_header.uc_numid,
	tp_read->t_tga_file_header.uc_maptyp,
	tp_read->t_tga_file_header.uc_imgtyp,
	tp_read->t_tga_file_header.s_maporig,
	tp_read->t_tga_file_header.s_mapsize,
	tp_read->t_tga_file_header.uc_mapbits,
	tp_read->t_tga_file_header.s_xorig,
	tp_read->t_tga_file_header.s_yorig,
	tp_read->t_tga_file_header.s_xsize,
	tp_read->t_tga_file_header.s_ysize,
	tp_read->t_tga_file_header.uc_pixsize,
	tp_read->t_tga_file_header.uc_imgdes,
	cp_filepath );

	(void)fflush(stdout);
}

int tga_stat_column( int i_count, char **cpp_name )
{
	int	ii;
	TGA_READ	t_read;

	tga_read_init( &t_read );

	_tga_stat_column_head();

	for (ii = 0; ii < i_count; ++ii) {
		if (OK != tga_read_open( cpp_name[ii], &t_read )) {
			pri_funct_err_bttvr(
		 "Error : tga_read_open(%s,) returns NG.",
				cpp_name[ii] );
			return NG;
		}

		_tga_stat_column_body( &t_read, cpp_name[ii] );

		if (OK != tga_read_close( &t_read )) {
			pri_funct_err_bttvr(
		 "Error : tga_read_close(-) returns NG.");
			return NG;
		}
	}
	if (24 <= i_count) { _tga_stat_column_head(); }

	return OK;
}

/********************************************************************/

void tga_stat_for_pv( TGA_FILE_HEADER *tp_tga )
{
	pri_funct_msg_vr(
	"Targa image data, %d width, %d height, %u channels",
		tp_tga->s_xsize,
		tp_tga->s_ysize,
		tp_tga->uc_pixsize/8
	);
}
