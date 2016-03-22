#include "ptbl_returncode.h"
#include "pri.h"
#include "gts_master.h"

/* 画像カンバスに、回転情報を加えて、指定の名前で、保存 */
int gts_master::_iipg_save( iip_canvas *clp_canvas, char *cp_path, double d_dpi, int i_rot90, iip_read *clp_read )
{
	if (ON == this->i_mv_sw()) {
		pri_funct_msg_ttvr( "gts_master::_iipg_save()" );
	}

	/* 親と接続 */
	this->cl_iip_writ.set_clp_parent( clp_canvas );

	/* 親の大きさを得る */
	this->cl_iip_writ.set_canvas_size( clp_canvas );

	/* 親のカンバスを参照する(自分にメモリがあるなら開放する) */
	this->cl_iip_writ.set_vp_reference_canvas(
		clp_canvas->get_vp_canvas() );

	/* ファイルパス名設定 */
	if (OK != this->cl_iip_writ.cl_name.set_name(cp_path)) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_writ.cl_name.set_name(%s) returns NG",
			cp_path);
		return NG;
	}

	/*
	 * 以下属性設定
	 */

	/* DPI情報を埋め込む */
	this->cl_iip_writ.set_d_tif_dpi_x( d_dpi );
	this->cl_iip_writ.set_d_tif_dpi_y( d_dpi );

	/* 回転情報付加
		時計周りに90度回転(i_rot90=1)すると正対するということは、
		正対から時計周りに270度回転(...rot270())している
	*/
	switch (i_rot90) {
	case 0: this->cl_iip_writ.set_l_tif_orientation_rot0(); break;
	case 1: this->cl_iip_writ.set_l_tif_orientation_rot270(); break;
	case 2: this->cl_iip_writ.set_l_tif_orientation_rot180(); break;
	case 3: this->cl_iip_writ.set_l_tif_orientation_rot90(); break;
	default:
		pri_funct_err_bttvr( "Error : bad i_rot90<%d>",i_rot90);
		return NG;
	}

	/* BWの場合の圧縮 */
	if (	(0 == this->cl_iip_writ.cl_ch_info.get_l_bytes()) &&
		(1 == this->cl_iip_writ.cl_ch_info.get_l_bits())
	) {
		this->cl_iip_writ.set_tif_compression_faxg4();
	}
	/* その他(Grayscale,RGB)の場合の圧縮 */
	else {
		this->cl_iip_writ.set_tif_compression_lzw();
	}

	/* TIFFバイトオーダーをCPUに依存とする */
	this->cl_iip_writ.set_tif_byte_order_depend_cpu();

	/* 読み込み画像があれば、ファイル属性情報
		clp->get_d_tif_dpi_x();
		clp->get_d_tif_dpi_y();
		clp->get_l_tif_compression();
		clp->get_l_tif_orientation();
	を上書きする */
	if (NULL != clp_read) {
	 this->cl_iip_writ.set_file_attrbute_from_read(clp_read);
	}

	/*
	 * 保存
	 */

	if (OK != this->cl_iip_writ.file()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_iip_writ.file() returns NG" );
		return NG;
	}

	return OK;
}
