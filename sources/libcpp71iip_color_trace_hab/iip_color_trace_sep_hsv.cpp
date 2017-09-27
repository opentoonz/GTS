#include <cassert>
#include <iostream>	// std::cerr
#include <string>	// std::string
#include <sstream>	// std::ostringstream
#include <random>	/* mt19937 */

//#include "ptbl_returncode.h"
//#include "pri.h"
//#include "calcu_precision.h"
#include "calcu_rgb_to_hsv.h"
#include "gts_gui.h"
#include "iip_color_trace_sep_hsv.h"

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
void iip_color_trace_sep_hsv_exec_(
	int width , int channels , TINN* image_inn_top
	, int area_xpos , int area_ypos , int area_xsize , int area_ysize
	, calcu_color_trace_sep_hsv& calcu_sep_hsv
	, TOUT* image_out_top
)
{
  if ( cl_gts_gui.hsv_view->vbo.get_hsv_view_start_sw() ) {
  /*--- hsv viewウインドウのOpenGL初期化済 --> image view及びhsv view ---*/
//std::cout << __FILE__ << " " << __LINE__ << " " << "VBO Start" << " xsize=" << area_xsize << " ysize=" << area_ysize << std::endl;

	/* vbo初期化 */
	if ( cl_gts_gui.hsv_view->vbo.open_or_reopen(
		area_xsize * area_ysize
	) ) {
std::cerr << "Error:" << __FILE__ << " " << __LINE__ << "vbo" << std::endl;
		return; // by Error
	}

	/* 初期パラメータ設定 */
	calcu_rgb_to_hsv rgb2hsv;
	const int scan_size = width * channels;
	const int start_pos = area_ypos * scan_size + area_xpos * channels;

	/* windows.hのmax()マクロが先にきいてしまいエラーとなる */
	const auto max_val_inn = (std::numeric_limits<TINN>::max)();
	const auto max_val_out = (std::numeric_limits<TOUT>::max)();
	const auto max_glub_out = (std::numeric_limits<GLubyte>::max)();
	const double max_val_out_f = max_val_out + 0.999999;
	const int shift_bit = std::numeric_limits<TINN>::digits - 8;

	/* Colorデータ書き込み */
	{
	  GLubyte* rgb = cl_gts_gui.hsv_view->vbo.start_color();
	  if (rgb == nullptr) { /* open出来ていればここはこないはず */
		assert(!"Error:vbo.start_color() return null");
	  }

	  if (cl_gts_gui.menite_hsv_dot_white->value() != 0) {
	    for (int ii = 0; ii < area_ysize * area_xsize; ++ii ,rgb+=3) {
		rgb[CH_RED] = max_glub_out;
		rgb[CH_GRE] = max_glub_out;
		rgb[CH_BLU] = max_glub_out;
	    }
	  }
	  else
	  if (cl_gts_gui.menite_hsv_dot_black->value() != 0) {
	    for (int ii = 0; ii < area_ysize * area_xsize; ++ii ,rgb+=3) {
		rgb[CH_RED] = 0;
		rgb[CH_GRE] = 0;
		rgb[CH_BLU] = 0;
	    }
	  }
	  else {
	    TINN *image_inn = image_inn_top + start_pos;
	    for (int yy = 0; yy < area_ysize ; ++yy
	    ,image_inn += scan_size) {

	      TINN* inn_x = image_inn;
	      for (int xx = 0; xx < area_xsize ;++xx
	      ,inn_x += channels ,rgb+=3) {
	    	rgb[CH_RED] = inn_x[CH_RED] >> shift_bit;
	    	rgb[CH_GRE] = inn_x[CH_GRE] >> shift_bit;
	    	rgb[CH_BLU] = inn_x[CH_BLU] >> shift_bit;

		/* 2値化しない場合白点で表示する処理 */
		double	hh=0., ss=0., vv=0.;
		rgb2hsv.to_hsv(
		 static_cast<double>(inn_x[CH_RED] >> shift_bit)/max_val_inn
		,static_cast<double>(inn_x[CH_GRE] >> shift_bit)/max_val_inn
		,static_cast<double>(inn_x[CH_BLU] >> shift_bit)/max_val_inn
		,&hh, &ss, &vv );
		/* 2値化するかどうか判断 */
		if (cl_gts_gui.menite_hsv_dot_trace_area->value() != 0) {
		  double	rr=0., gg=0., bb=0.;
		  if (!calcu_sep_hsv.exec( hh, ss, vv, &rr, &gg, &bb )) {
	    		rgb[CH_RED] = max_glub_out;
	    		rgb[CH_GRE] = max_glub_out;
	    		rgb[CH_BLU] = max_glub_out;
		  }
		}
	      }
	    }
 	  }
	  cl_gts_gui.hsv_view->vbo.end_color();
	}
	
	/* 2値化out & Vertexデータ書き込み */
	{
	  gts::opengl_vbo::vbo_float* xyz =
				cl_gts_gui.hsv_view->vbo.start_vertex();
	  if (xyz == nullptr) { /* open出来ていればここはこないはず */
		assert(!"Error:vbo.start_vertex() return null");
	  }
	  //GLubyte* rgb = cl_gts_gui.hsv_view->vbo.start_color();

	  std::mt19937 engine;
	  std::uniform_real_distribution<> dist( -0.5 ,0.499999 );

	  TINN *image_inn = image_inn_top + start_pos;
	  TOUT *image_out = image_out_top + start_pos;
	  for (int yy = 0; yy < area_ysize ; ++yy
	  ,image_inn += scan_size ,image_out += scan_size) {

	    TINN* inn_x = image_inn;
	    TOUT* out_x = image_out;
	    for (int xx = 0; xx < area_xsize ;++xx
	    ,inn_x+=channels ,out_x+=channels ,xyz+=3/* ,rgb+=3*/) {
		double	hh=0., ss=0., vv=0.;
		rgb2hsv.to_hsv(
		 static_cast<double>(inn_x[CH_RED] >> shift_bit)/max_val_inn
		,static_cast<double>(inn_x[CH_GRE] >> shift_bit)/max_val_inn
		,static_cast<double>(inn_x[CH_BLU] >> shift_bit)/max_val_inn
		,&hh, &ss, &vv );

		/* 2値化 */
		double	rr=0., gg=0., bb=0.;
		calcu_sep_hsv.exec( hh,  ss,  vv, &rr, &gg, &bb );

		/* 出力 */
		out_x[CH_RED] = static_cast<TOUT>(rr * max_val_out_f);
		out_x[CH_GRE] = static_cast<TOUT>(gg * max_val_out_f);
		out_x[CH_BLU] = static_cast<TOUT>(bb * max_val_out_f);

		/* xyz位置は別途計算
		RGB256段階のため幾何学的に並び気持ち悪いため
		ランダムにずらす */
		if (cl_gts_gui.menite_hsv_random_position->value()==0) {
			rgb2hsv.to_hsv(
 (static_cast<double>(inn_x[CH_RED] >> shift_bit))/max_val_inn
,(static_cast<double>(inn_x[CH_GRE] >> shift_bit))/max_val_inn
,(static_cast<double>(inn_x[CH_BLU] >> shift_bit))/max_val_inn
,&hh, &ss, &vv
			);
		}
		else {
			rgb2hsv.to_hsv(
 (static_cast<double>(inn_x[CH_RED] >> shift_bit)+dist(engine))/max_val_inn
,(static_cast<double>(inn_x[CH_GRE] >> shift_bit)+dist(engine))/max_val_inn
,(static_cast<double>(inn_x[CH_BLU] >> shift_bit)+dist(engine))/max_val_inn
,&hh, &ss, &vv
			);
		}

		/* hsvからxyz座標値を生成 */
		cl_gts_gui.hsv_view->vbo.hsv_to_xyz( hh ,ss ,vv ,xyz );
	    }
	  }
	  //cl_gts_gui.hsv_view->vbo.end_color();
	  cl_gts_gui.hsv_view->vbo.end_vertex();
	}
	//cl_gts_gui.hsv_view->redraw();
  }
  else {
  /*--- hsv viewウインドウのOpenGL初期化してないのでimage viewのみ ---*/
//std::cout << __FILE__ << " " << __LINE__ << " " << "VBO Off" << " xsize=" << area_xsize << " ysize=" << area_ysize << std::endl;
	/* 初期パラメータ設定 */
	calcu_rgb_to_hsv rgb2hsv;
	const int scan_size = width * channels;
	const int start_pos = area_ypos * scan_size + area_xpos * channels;

	/* windows.hのmax()マクロが先にきいてしまいエラーとなる */
	const auto max_val_inn = (std::numeric_limits<TINN>::max)();
	const auto max_val_out = (std::numeric_limits<TOUT>::max)();
	const double max_val_out_f = max_val_out + 0.999999;

	/* 2値化out & Vertexデータ書き込み */
	{
	  TINN *image_inn = image_inn_top + start_pos;
	  TOUT *image_out = image_out_top + start_pos;
	  for (int yy = 0; yy < area_ysize ; ++yy
	  ,image_inn += scan_size ,image_out += scan_size) {

	    TINN* inn_x = image_inn;
	    TOUT* out_x = image_out;
	    for (int xx = 0; xx < area_xsize ;++xx
	    ,inn_x += channels ,out_x += channels ) {
		double	hh=0., ss=0., vv=0.;
		rgb2hsv.to_hsv(
			static_cast<double>(inn_x[CH_RED])/max_val_inn,
			static_cast<double>(inn_x[CH_GRE])/max_val_inn,
			static_cast<double>(inn_x[CH_BLU])/max_val_inn,
			&hh, &ss, &vv );

		/* 2値化 */
		double	rr=0., gg=0., bb=0.;
		calcu_sep_hsv.exec( hh,  ss,  vv, &rr, &gg, &bb );

		/* 出力 */
		out_x[CH_RED] = static_cast<TOUT>(rr * max_val_out_f);
		out_x[CH_GRE] = static_cast<TOUT>(gg * max_val_out_f);
		out_x[CH_BLU] = static_cast<TOUT>(bb * max_val_out_f);
	    }
	  }
	}
  }
}

//--------------------------------------------------

/* 親のカンバスも自分のカンバスも必要、また同じ大きさであること */
void iip_color_trace_sep_hsv::exec( calcu_color_trace_sep_hsv& calcu_sep_hsv )
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
		iip_color_trace_sep_hsv_exec_<unsigned char,unsigned char>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned char*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,calcu_sep_hsv
			,static_cast<unsigned char*>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_USHRT:
		iip_color_trace_sep_hsv_exec_<unsigned short,unsigned short>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned short*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,calcu_sep_hsv
			,static_cast<unsigned short*>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_ULONG:
		iip_color_trace_sep_hsv_exec_<unsigned long,unsigned long>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned long*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,calcu_sep_hsv
			,static_cast<unsigned long*>(this->get_vp_canvas())
		);
		break;
	case E_CH_NUM_DOUBL: break; /* Not support */
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}
}
