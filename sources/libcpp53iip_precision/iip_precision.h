#ifndef __iip_precision_h__
#define __iip_precision_h__

#include "iip_canvas.h"

class iip_precision : public iip_canvas {
public:
	iip_precision()
	{
		this->set_ccp_object_name_of_mv("iip_precision");
	}

	/* 親子接続し、親の画像大きさをセット
	this->set_clp_parent(clp);
	this->set_canvas_size(clp); ******/
	/* 子の画像のサンプリング数と整数、浮動小数点の種類をセット
	this->set_l_bytes(ll);
	this->set_e_iip_pix_ch_num_form(ee) ******/

	/* カンバス(メモリ)セット */
	int set_canvas( void );

	/* 実行 */
	void exec( void );
private:
	void _bw_to_uchargray( long l_width, long l_height, long l_max, unsigned char *ucharp_in_bw, unsigned char *ucharp_out_gray );
};

#endif /* !__iip_precision_h__ */
