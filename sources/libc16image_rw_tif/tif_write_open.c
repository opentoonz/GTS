#include "ptbl_returncode.h"
#include "ptbl_funct.h"
#include "pri.h"
#include "tif.h"

int tif_write_open( char *cp_fname, int i_byte_swap_mode, TIF_IMAGE_RW *tp_write )
{
	char *cp_tiffopen_mode;

	switch (i_byte_swap_mode) {
	case  0  : cp_tiffopen_mode = "w";  break;
	case 'l' : cp_tiffopen_mode = "wl"; break;
	case 'b' : cp_tiffopen_mode = "wb"; break;
	default :
		pri_funct_err_bttvr(
			"Error : i_byte_swap_mode<%d> is bad.",
			i_byte_swap_mode);
		return NG;
	}

	/* オープン */
	if (NULL != tp_write->tp_tiff_head) {
		pri_funct_err_bttvr(
			"Error : file<%s> already opened.", cp_fname);
		return NG;
	}

#if defined _WIN32
	tp_write->tp_tiff_head = TIFFOpen(
	     ptbl_charcode_cp932_from_utf8(cp_fname) , cp_tiffopen_mode );
#else
	tp_write->tp_tiff_head = TIFFOpen( cp_fname , cp_tiffopen_mode );
#endif
	if (NULL == (tp_write->tp_tiff_head)) {
		pri_funct_err_bttvr(
			"Error : TIFFOpen(<%s>,w) returns NULL.",
			cp_fname);
		return NG;
	}

	return OK;
}
