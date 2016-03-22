#include "pri.h"
#include "iip_opengl_l3event.h"

/* 画像データの設定
	1.表示画像データ設定
	2.表示クラス指示
	3.Channel表示param設定
	4.表示クラスの有無による、表示設定(this->_e_wview_type)
表示が１枚か２枚かにかかわらず、指定のデータは設定しておく
*/
int iip_opengl_l3event::set_imagedata( iip_canvas *clp_parent_main, iip_canvas *clp_parent_sub )
{
	/* 表示データへのポインターを初期化(表示の有無) */
	this->_clp_main = NULL;
	this->_clp_sub  = NULL;

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_vr( "iip_opengl_l3event::set_imagedata(-)" );
	}

	/* main画像の指定があればmainを替える */
	if ((NULL != clp_parent_main) 
	&&  (NULL != clp_parent_main->get_vp_canvas())) {
		/* subの画像データをセッティング */
		if (OK != this->_cl_unt_view[0].set_imagedata(
			  clp_parent_main
		)) {
			pri_funct_err_bttvr(
	 "Error : this->_cl_unt_view[0].set_imagedata(-) returns NG."
			);
			return NG;
		}

		/* 画像データからチャンネル表示用param初期化 */
		this->_cl_unt_view[0].cl_iip_view.init_channel();
	}

	/* sub画像の指定があればsubを替える */
	if ((NULL != clp_parent_sub)
	&&  (NULL != clp_parent_sub->get_vp_canvas())) {
		/* subの画像データをセッティング */
		if (OK !=this->_cl_unt_view[1].set_imagedata(
			  clp_parent_sub
		)) {
			pri_funct_err_bttvr(
	 "Error : this->_cl_unt_view[1].set_imagedata(-) returns NG."
			);
			return NG;
		}

		/* 画像データからチャンネル表示用param初期化 */
		this->_cl_unt_view[1].cl_iip_view.init_channel();
	}

	/* 画像データの有無と、表示指定から、表示の設定をする */
	this->_wview( this->_e_wview_type );

	return OK;
}
