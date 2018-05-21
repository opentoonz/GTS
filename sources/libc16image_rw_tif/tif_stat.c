#include <string.h>	/* for strrchr() */

#include "tiffio.h"

#include "ptbl_returncode.h"
#include "pri.h"

#include "cpu_byte_order_is_little_endian.h"
#include "tif.h"
#include "tif_stat.h"

static void _tif_stat_detail_reading_byte_swap_info( int i_read_is_byte_swap )
{
	int	i_file_is_swapped_order;

	int is_little_endian = cpu_byte_order_is_little_endian();

	/* ファイルのバイトオーダーは? */
	i_file_is_swapped_order =
		/* CPUがbig endianで、swapして読んでる */
		( !is_little_endian && i_read_is_byte_swap )||
		/* CPUがlittle endianで、orderどおり読んでる */
		( is_little_endian && !i_read_is_byte_swap );

	(void)fprintf(stdout,
		"          cpu byte order            %s",
		is_little_endian ?"little endian" :"big endian" );
	(void)fprintf(stdout,
		" 0:big_endian(MIPS),1:little_endian(Intel)\n" );

	(void)fprintf(stdout,
		"          TIFFIsByteSwapped(-)      %d",
		i_read_is_byte_swap );
	(void)fprintf(stdout,
		" 0:order,1:read_with_swapping\n" );

	(void)fprintf(stdout,
		"bo        file byte order           %d",
		i_file_is_swapped_order);
	(void)fprintf(stdout,
		" 0:order(big endian),1:swap(little endian)\n");
}

static void _tif_stat_detail_body( char *cp_filepath, TIF_IMAGE_RW *tp_read )
{

 TIFFPrintDirectory( tp_read->tp_tiff_head, stdout,
	/*TIFFPRINT_STRIPS|*/TIFFPRINT_CURVES|TIFFPRINT_COLORMAP
	/*|TIFFPRINT_JPEGQTABLES|TIFFPRINT_JPEGACTABLES|TIFFPRINT_JPEGDCTABLES*/ );

	/* ファイル名 */
	(void)fprintf(stdout,
		"filename  filepath                  '%s'\n",
		cp_filepath );

	/* TIFFポインタ */
	(void)fprintf( stdout,
		"          tp_read->tp_tiff_head     %p\n",
		tp_read->tp_tiff_head );

	/****(void)fprintf( stdout,
		"          tif_header.tiff_magic  0x%x",
		tp_read->tp_tiff_head->tif_header.tiff_magic );
	(void)fprintf( stdout,
		" 0x%x:big endian(68k) 0x%x:little endian(x86)\n",
		TIFF_BIGENDIAN,
		TIFF_LITTLEENDIAN);***/

	/* Read時の byte swap 情報 */
	_tif_stat_detail_reading_byte_swap_info(
		TIFFIsByteSwapped( tp_read->tp_tiff_head )
	);

	(void)fprintf( stdout,
		"compressi ui16_compression          %u",
		  tp_read->ui16_compression );
	(void)fprintf( stdout,
		" %d:dump %d:ccittrle %d:ccittfax3 %d:ccittfax4",
		COMPRESSION_NONE,
		COMPRESSION_CCITTRLE,
		COMPRESSION_CCITTFAX3,
		COMPRESSION_CCITTFAX4 );
	(void)fprintf( stdout,
		" %d:lzw %d:ojpeg %d:jpegdct %d:next %d:ccittlew",
		COMPRESSION_LZW,
		COMPRESSION_OJPEG,
		COMPRESSION_JPEG,
		COMPRESSION_NEXT,
		COMPRESSION_CCITTRLEW );
	(void)fprintf( stdout,
		"%d:packbits<max rle> %d:thunderscanrle\n",
		COMPRESSION_PACKBITS,
		COMPRESSION_THUNDERSCAN );

	(void)fprintf( stdout,
		"bi        ui16_bits_per_sample      %u\n",
		  tp_read->ui16_bits_per_sample );
	(void)fprintf( stdout,
		"width     ui32_image_width          %u\n",
		  tp_read->ui32_image_width );
	(void)fprintf( stdout,
		"heigh     ui32_image_length         %u\n",
		  tp_read->ui32_image_length );
	(void)fprintf( stdout,
		"c         ui16_samples_per_pixel    %u\n",
		  tp_read->ui16_samples_per_pixel );
	(void)fprintf( stdout,
		"t         i_tile_sw                 %d\n",
		  tp_read->i_tile_sw );
	(void)fprintf( stdout,
		"twidt     ui32_tile_width           %u\n",
		  tp_read->ui32_tile_width );
	(void)fprintf( stdout,
		"theig     ui32_tile_length          %u\n",
		  tp_read->ui32_tile_length );
	(void)fprintf( stdout,
		"orientati ui16_orientation          %u",
		  tp_read->ui16_orientation );
	(void)fprintf( stdout,
		" %d:TL %d:TR %d:LT %d:RT %d:BR %d:BL %d:RB %d:LB\n",
		ORIENTATION_TOPLEFT,
		ORIENTATION_TOPRIGHT,
		ORIENTATION_LEFTTOP,
		ORIENTATION_RIGHTTOP,
		ORIENTATION_BOTRIGHT,
		ORIENTATION_BOTLEFT,
		ORIENTATION_RIGHTBOT,
		ORIENTATION_LEFTBOT );
	(void)fprintf( stdout,
		"photo     ui16_photometric          %u",
		tp_read->ui16_photometric );
	(void)fprintf( stdout,
		" %d:miniswhite %d:minisblack %d:rgb %d:palette\n",
		PHOTOMETRIC_MINISWHITE,
		PHOTOMETRIC_MINISBLACK,
		PHOTOMETRIC_RGB,
		PHOTOMETRIC_PALETTE );
	(void)fprintf( stdout,
		"pconf     ui16_planar_configuration %u",
		tp_read->ui16_planar_configuration );
	(void)fprintf( stdout,
		" %d:contiguity %d:separete\n",
		PLANARCONFIG_CONTIG,
		PLANARCONFIG_SEPARATE );
	(void)fprintf( stdout,
		"resol_x_y f_dpi_x                   %g\n",
		  tp_read->f_dpi_x );
	(void)fprintf( stdout,
		"          f_dpi_y                   %g\n",
		  tp_read->f_dpi_y );
	(void)fprintf( stdout,
		"          vp_tile                   %p\n",
		  tp_read->vp_tile );
 	(void)fflush( stdout );
}

int tif_stat_detail( int i_count, char **cpp_name )
{
	int	ii;
	TIF_IMAGE_RW	t_read;

	tif_init_rw_header( &t_read );

	for (ii = 0; ii < i_count; ++ii) {
		if (OK != tif_read_open( cpp_name[ii], &t_read )) {
			pri_funct_err_bttvr(
			"Error : tif_read_open(%s,) returns NG.",
				ii,cpp_name[ii] );
			tif_read_close( &t_read );
			return NG;
		}

		_tif_stat_detail_body( cpp_name[ii], &t_read );

		tif_read_close( &t_read );
	}

	return OK;
}

/********************************************************************/

static void _tif_stat_column_head( void )
{
(void)fprintf(stdout,
"bo  compressi bi width heigh c orientati photo pconf resol_x_y filename\n" );
}
static int _tif_stat_column_body( TIF_IMAGE_RW *tp_read, char *cp_path )
{
	char	*cp_byte_order,
		*cp_compre,
		*cp_orienta,
		*cp_photom,
		*cp_planec;
	int	i_byte_swapped;

	int is_little_endian = cpu_byte_order_is_little_endian();

	/* ファイル読み込み時バイトスワップしたか */
	i_byte_swapped = TIFFIsByteSwapped( tp_read->tp_tiff_head );

	/* ファイルのバイトオーダーは？ */
	if (
		/* CPUがbigでorderどおり */
		( !is_little_endian && !i_byte_swapped ) ||

		/* CPUがlittleでswapした  */
		( is_little_endian && i_byte_swapped )
	) {
		cp_byte_order = "big";
	}
	else {
		cp_byte_order = "lit";
	}

	switch ( tp_read->ui16_compression ) {
	case COMPRESSION_NONE:		cp_compre = "dmp"; break;
	case COMPRESSION_CCITTRLE:	cp_compre = "crl"; break;
	case COMPRESSION_CCITTFAX3:	cp_compre = "cf3"; break;
	case COMPRESSION_CCITTFAX4:	cp_compre = "cf4"; break;
	case COMPRESSION_LZW:		cp_compre = "lzw"; break;
	case COMPRESSION_OJPEG:		cp_compre = "ojp"; break;
	case COMPRESSION_JPEG:		cp_compre = "jpg"; break;
	case COMPRESSION_NEXT:		cp_compre = "nex"; break;
	case COMPRESSION_CCITTRLEW:	cp_compre = "crw"; break;
	case COMPRESSION_PACKBITS:	cp_compre = "rle"; break;
	case COMPRESSION_THUNDERSCAN:	cp_compre = "thu"; break;
	default:
		cp_compre = "?";
		break;
	}
	switch ( tp_read->ui16_orientation ) {
	case ORIENTATION_TOPLEFT:	cp_orienta = "top-lef"; break;
	case ORIENTATION_TOPRIGHT:	cp_orienta = "top-rig"; break;
	case ORIENTATION_LEFTTOP:	cp_orienta = "lef-top"; break;
	case ORIENTATION_RIGHTTOP:	cp_orienta = "rig-top"; break;
	case ORIENTATION_BOTRIGHT:	cp_orienta = "bot-rig"; break;
	case ORIENTATION_BOTLEFT:	cp_orienta = "bot-lef"; break;
	case ORIENTATION_RIGHTBOT:	cp_orienta = "rig-bot"; break;
	case ORIENTATION_LEFTBOT:	cp_orienta = "lef-bot"; break;

	/* zero is made in photoshop does it? */
	case 0:				cp_orienta = "not-set"; break;

	default:
		cp_orienta = "?";
		break;
	}
	switch ( tp_read->ui16_photometric ) {
	case PHOTOMETRIC_MINISWHITE:	cp_photom = "mw "; break;
	case PHOTOMETRIC_MINISBLACK:	cp_photom = "mb "; break;
	case PHOTOMETRIC_RGB:		cp_photom = "rgb"; break;
	case PHOTOMETRIC_PALETTE:	cp_photom = "plt"; break;
	default:
		cp_photom = "?";
		break;
	}
	switch ( tp_read->ui16_planar_configuration ) {
	case PLANARCONFIG_CONTIG:	cp_planec = "con"; break;
	case PLANARCONFIG_SEPARATE:	cp_planec = "sep"; break;
	default:
		cp_planec = "?";
		break;
	}

/***(void)fprintf(stdout, "0x%x ", tp_read->tp_tiff_head->tif_header.tiff_magic);***/
	(void)fprintf(stdout, "%3s ", cp_byte_order );
	(void)fprintf(stdout, "%5u ", tp_read->ui16_compression ); 
	(void)fprintf(stdout, "%3s ",  cp_compre ); 
	(void)fprintf(stdout, "%2u ", tp_read->ui16_bits_per_sample );
	(void)fprintf(stdout, "%5u ", tp_read->ui32_image_width );
	(void)fprintf(stdout, "%5u ", tp_read->ui32_image_length );
	(void)fprintf(stdout, "%1u ", tp_read->ui16_samples_per_pixel );

	(void)fprintf(stdout, "%1u ", tp_read->ui16_orientation );
	(void)fprintf(stdout, "%-7s ", cp_orienta );
	(void)fprintf(stdout, "%1u ", tp_read->ui16_photometric );
	(void)fprintf(stdout, "%3s ", cp_photom );
	(void)fprintf(stdout, "%1u ", tp_read->ui16_planar_configuration );
	(void)fprintf(stdout, "%3s ", cp_planec );
	(void)fprintf(stdout, "%g ", tp_read->f_dpi_x );
	(void)fprintf(stdout, "%g ", tp_read->f_dpi_y );
	(void)fprintf(stdout, "%s", cp_path );

	if (tp_read->i_tile_sw) {
	 (void)fprintf(stdout, "(tiled %u %u)", 
		tp_read->ui32_tile_width,
		tp_read->ui32_tile_length );
	}

	(void)fprintf(stdout, "\n" );

	(void)fflush( stdout );

	return OK;

}

int tif_stat_column( int i_count, char **cpp_name )
{
	int	ii;
	TIF_IMAGE_RW	t_read;

	tif_init_rw_header( &t_read );

	_tif_stat_column_head();

	for (ii = 0; ii < i_count; ++ii) {
		if (OK != tif_read_open( cpp_name[ii], &t_read )) {
			pri_funct_err_bttvr(
		 "Error : tif_read_open(%s,) returns NG.",
				cpp_name[ii] );
			(void)tif_read_close( &t_read );
			return NG;
		}
		if (OK != _tif_stat_column_body(&t_read,cpp_name[ii])) {
			pri_funct_err_bttvr(
 		 "Error : _tif_stat_column_body(,%s) returns NG.\n",
				cpp_name[ii] );
			(void)tif_read_close( &t_read );
			return NG;
		}
		tif_read_close( &t_read );
	}

	if (24 <= i_count) { _tif_stat_column_head(); }

	return OK;
}

/********************************************************************/

void tif_stat_for_pv( TIF_IMAGE_RW *tp_read )
{
	char *cp_endian, *cp_comp;
	int	i_read_is_byte_swap,
		i_file_is_swapped_order;

	int is_little_endian = cpu_byte_order_is_little_endian();
	i_read_is_byte_swap = TIFFIsByteSwapped(tp_read->tp_tiff_head);

	/* ファイルのバイトオーダーは? */
	i_file_is_swapped_order =
		/* CPUがbig endianで、swapして読んでる */
		( !is_little_endian && i_read_is_byte_swap )||
		/* CPUがlittle endianで、orderどおり読んでる */
		( is_little_endian && !i_read_is_byte_swap );

	if (i_file_is_swapped_order) {
		cp_endian = "little-endian";
	}
	else {
		cp_endian = "big-endian";
	}

	/* 圧縮タイプ */
	switch ( tp_read->ui16_compression ) {
	case COMPRESSION_NONE:      cp_comp = "Dump"; break;
	case COMPRESSION_LZW:       cp_comp = "LZW";break;
	case COMPRESSION_PACKBITS:  cp_comp = "Packbits"; break;
	case COMPRESSION_CCITTFAX4: cp_comp = "CCITT G4 fax"; break;
	default:                    cp_comp = "Unknown Encode";  break;
	}

	if (tp_read->i_tile_sw) {
		pri_funct_msg_vr(
 "TIFF image data, %s, %s, %u width, %u height, %u channels, %u bits, tile %u %u",
		cp_endian,
		cp_comp,
		tp_read->ui32_image_width,
		tp_read->ui32_image_length,
		tp_read->ui16_samples_per_pixel,
		tp_read->ui16_bits_per_sample,
		tp_read->ui32_tile_width,
		tp_read->ui32_tile_length
		);
	} else {
		pri_funct_msg_vr(
 "TIFF image data, %s, %s, %u width, %u height, %u channels, %u bits",
		cp_endian,
		cp_comp,
		tp_read->ui32_image_width,
		tp_read->ui32_image_length,
		tp_read->ui16_samples_per_pixel,
		tp_read->ui16_bits_per_sample
		);
	}
}

