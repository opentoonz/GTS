#include <cassert>
#include <iostream>	// std::cerr
#include <string>	// std::string
#include <sstream>	// std::ostringstream
#include <random>	/* mt19937 */

#include "calc_hsv_rgb.h"
#include "util_stop_watch.h"    /* util::stop_watch */
#include "iip_trace_by_hsv.h"

/*
	template
	TINN,TOUTについて
		unsigned char
		unsigned short
		unsigned long
		unsigned int	(=unsigned)
	のみサポート
		float
		double
	は処理できない
*/
template <class TINN , class TOUT>
std::string iip_trace_by_hsv_tplt_(
	int width , int channels , TINN* image_inn_top
	,int area_xpos , int area_ypos , int area_xsize , int area_ysize
	,const std::vector<calc::trace_by_hsv_params>& hsv_params
	,TOUT* image_out_top
	,const bool white_out_of_area_sw
	,const bool random_position_sw
	,opengl::vertex_buffer_object& vbo
)
{
util::stop_watch stwa; stwa.start();
	const bool ready_to_vbo_sw = vbo.get_hsv_view_start_sw();
	/* ----- hsv3d表示のrgb値セット ----- */
  if ( ready_to_vbo_sw ) { /* vboを使うにはOpenGL初期化済であること */ 
	/* vbo初期化 */
	std::string err_msg( vbo.open_or_reopen(
		area_xsize * area_ysize
	) );
	if (!err_msg.empty()) {
		return err_msg;
	}
  }

	/* 初期パラメータ設定 */
	const int scan_size = width * channels;
	const int start_pos = area_ypos * scan_size + area_xpos * channels;

	/* windows.hのmax()マクロが先にきいてしまいエラーとなる */
	const auto max_val_inn = (std::numeric_limits<TINN>::max)();
	const auto max_val_out = (std::numeric_limits<TOUT>::max)();
	const double max_val_out_f = max_val_out + 0.999999;

  if ( ready_to_vbo_sw ) {
	const auto max_glub_out = (std::numeric_limits<GLubyte>::max)();
	const int shift_bit = std::numeric_limits<TINN>::digits - 8;

	/* Colorデータ書き込み */
	GLubyte* rgb = vbo.start_color();
	if (rgb == nullptr) { /* open出来ていればここはこないはず */
		assert(!"Error:vbo.start_color() return null");
	}

	TINN *image_inn = image_inn_top + start_pos;
	for (int yy = 0; yy < area_ysize ; ++yy ,image_inn += scan_size) {

	  TINN* inn_x = image_inn;
	  for (int xx = 0; xx < area_xsize ;++xx ,inn_x+=channels ,rgb+=3) {
		rgb[CH_RED] = inn_x[CH_RED] >> shift_bit;
		rgb[CH_GRE] = inn_x[CH_GRE] >> shift_bit;
		rgb[CH_BLU] = inn_x[CH_BLU] >> shift_bit;

		if ( white_out_of_area_sw ) {
			/* 2値化しない場合白点で表示する処理 */
			double hh=0. ,ss=0. ,vv=0.;
			calc::rgb_to_hsv(
			 static_cast<double>(inn_x[CH_RED])/max_val_inn
			,static_cast<double>(inn_x[CH_GRE])/max_val_inn
			,static_cast<double>(inn_x[CH_BLU])/max_val_inn
			,hh, ss, vv );
			/* 2値化するかどうか判断 */
			double rr=0. ,gg=0. ,bb=0.;
			if (!calc::trace_by_hsv_to_rgb(
				hh,ss,vv, hsv_params ,rr,gg,bb
			)) {	/* 2値化しないpixelは白表示 */
				rgb[CH_RED] = max_glub_out;
				rgb[CH_GRE] = max_glub_out;
				rgb[CH_BLU] = max_glub_out;
			}
		}
	  }
	}
	vbo.end_color();
  }

std::cout << "rgb:" << stwa.stop_ms().count() << "milisec\n";
stwa.start();

	/* ----- 画像のpixel値と、hsv3d表示のxyz値セット(要高速化) ----- */
	opengl::vertex_buffer_object::vbo_float* xyz = nullptr;
  if ( ready_to_vbo_sw ) {
	xyz = vbo.start_vertex();
	if (xyz == nullptr) { /* open出来ていればここはこないはず */
		assert(!"Error:vbo.start_vertex() return null");
	}
  }
	std::mt19937 engine;
	std::uniform_real_distribution<> dist( -0.5 ,0.499999 );
  {
	TINN *image_inn = image_inn_top + start_pos;
	TOUT *image_out = image_out_top + start_pos;
	for (int yy = 0; yy < area_ysize ; ++yy
	,image_inn += scan_size ,image_out += scan_size) {

	    TINN* inn_x = image_inn;
	    TOUT* out_x = image_out;
	    for (int xx = 0; xx < area_xsize ;++xx
	    ,inn_x+=channels ,out_x+=channels) {
		double	hh=0., ss=0., vv=0.;
		calc::rgb_to_hsv(
		 static_cast<double>(inn_x[CH_RED])/max_val_inn
		,static_cast<double>(inn_x[CH_GRE])/max_val_inn
		,static_cast<double>(inn_x[CH_BLU])/max_val_inn
		,hh,ss,vv );

		/* 2値化 */
		double	rr=0., gg=0., bb=0.;
		calc::trace_by_hsv_to_rgb( hh,ss,vv, hsv_params ,rr,gg,bb );

		/* 出力 */
		out_x[CH_RED] = static_cast<TOUT>(rr * max_val_out_f);
		out_x[CH_GRE] = static_cast<TOUT>(gg * max_val_out_f);
		out_x[CH_BLU] = static_cast<TOUT>(bb * max_val_out_f);

  if ( ready_to_vbo_sw ) {
		/* xyz位置は別途計算
		RGB256段階のため幾何学的に並び気持ち悪いため
		ランダムにずらす */
		if ( random_position_sw ) {
			calc::rgb_to_hsv(
	 (static_cast<double>(inn_x[CH_RED])+dist(engine))/max_val_inn
	,(static_cast<double>(inn_x[CH_GRE])+dist(engine))/max_val_inn
	,(static_cast<double>(inn_x[CH_BLU])+dist(engine))/max_val_inn
			,hh,ss,vv
			);
		}
		/*else {
			calc::rgb_to_hsv(
			 (static_cast<double>(inn_x[CH_RED]))/max_val_inn
			,(static_cast<double>(inn_x[CH_GRE]))/max_val_inn
			,(static_cast<double>(inn_x[CH_BLU]))/max_val_inn
			,hh,ss,vv
			);
		}*/

		/* hsvからxyz座標値を生成 */
		vbo.hsv_to_xyzarray( hh ,ss ,vv ,xyz );

		xyz += 3;
  }
	    }
	}
  if ( ready_to_vbo_sw ) {
	  vbo.end_vertex();
  }
  }
std::cout << "xyz:" << stwa.stop_ms().count() << "milisec\n";
	return std::string();
}

//--------------------------------------------------

/* 親のカンバスも自分のカンバスも必要、また同じ大きさであること */
std::string iip_trace_by_hsv::exec( 
	const std::vector<calc::trace_by_hsv_params>& hsv_params
	,const bool white_out_of_area_sw
	,const bool random_position_sw
	,opengl::vertex_buffer_object& vbo
)
{
	/*
	 * 処理のためのデータチェック
	 */

	iip_canvas* pare = this->get_clp_parent();
	assert(NULL != pare); /* 親が必要 */
	assert(NULL != pare->get_vp_canvas());/* 親が画像をもっていること */

	/* 自分が独立したカンバスメモリをもっていること */
	assert(ON == this->get_i_must_be_free_self_sw());

	/* 親と同じサイズであること */
	assert(this->get_l_width() == pare->get_l_width());
	assert(this->get_l_height() == pare->get_l_height());
	assert(this->get_l_channels() == pare->get_l_channels());
	assert( this->cl_ch_info.get_l_bytes() ==
		pare->cl_ch_info.get_l_bytes());

	/* channel数は3(RGB)か4(RGBA) */
	assert(SZ_RGB <= this->get_l_channels());

	/* channel毎のサイズは(uchar,ushrt,ulong,double)のみ */
	assert(E_CH_NUM_BITBW != this->cl_ch_info.get_e_ch_num_type());

	/* 処理エリアの確認、実際の画像をはみだしたらだめ */
	assert( 0 <= this->area_xpos_ );
	assert( 0 <= this->area_ypos_ );

	/* areaが画像範囲をはみ出していたときの対処
	ホントはあってはならないエラー */
	if (	this->get_l_width() <
		(this->area_xpos_ + this->area_xsize_)
	) {
		// for debug
std::string str;
str += "this->area_xpos_<";
{ std::ostringstream ost; ost<<this->area_xpos_; str+=ost.str(); }
str += "> + this->area_xsize_<";
{ std::ostringstream ost; ost<<this->area_xsize_; str+=ost.str(); }
str += "> <= this->get_l_width()<";
{ std::ostringstream ost; ost<<this->get_l_width(); str+=ost.str(); }
str += ">";
std::cerr << str << std::endl;

		this->area_xsize_ =
			this->get_l_width() - this->area_xpos_;
	}

	if (	this->get_l_height() <
		(this->area_ypos_ + this->area_ysize_)
	) {
		// for debug
std::string str;
str += "this->area_ypos_<";
{ std::ostringstream ost; ost<<this->area_ypos_; str+=ost.str(); }
str += "> + this->area_ysize_<";
{ std::ostringstream ost; ost<<this->area_ysize_; str+=ost.str(); }
str += "> <= this->get_l_height()<";
{ std::ostringstream ost; ost<<this->get_l_height(); str+=ost.str(); }
str += ">";
std::cerr << str << std::endl;

		this->area_ysize_ =
			this->get_l_height() - this->area_ypos_;
	}

	/*
	 * 処理
	 */

	switch (this->cl_ch_info.get_e_ch_num_type()) {
	case E_CH_NUM_UCHAR:
		return iip_trace_by_hsv_tplt_<unsigned char,unsigned char>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned char*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,hsv_params
			,static_cast<unsigned char*>(this->get_vp_canvas())
			,white_out_of_area_sw
			,random_position_sw
			,vbo
		);
	case E_CH_NUM_USHRT:
		return iip_trace_by_hsv_tplt_<unsigned short,unsigned short>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned short*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,hsv_params
			,static_cast<unsigned short*>(this->get_vp_canvas())
			,white_out_of_area_sw
			,random_position_sw
			,vbo
		);
	case E_CH_NUM_ULONG:
		return iip_trace_by_hsv_tplt_<unsigned long,unsigned long>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned long*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,hsv_params
			,static_cast<unsigned long*>(this->get_vp_canvas())
			,white_out_of_area_sw
			,random_position_sw
			,vbo
		);
	case E_CH_NUM_DOUBL: break; /* Not support */
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	return std::string();
}
