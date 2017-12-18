#include <cassert>
#include <iostream>	// std::cerr
#include <vector>
#include <string>	// std::string
#include <sstream>	// std::ostringstream
#include <random>	/* mt19937 */
#include <thread>

#include "calc_hsv_rgb.h"
#include "util_stop_watch.h"    /* util::stop_watch */
#include "iip_trace_by_hsv.h"

/*
	template
	TINN,TOUTについて
		unsigned char
		unsigned short
		unsigned long
		unsigned int	(= unsigned)
	のみサポート
		float
		double
	は処理できない
*/
namespace {

template <class TINN , class TOUT>
class xyz_thread_job {
public:
	xyz_thread_job()
	:image_inn_(nullptr)
	,xyz_(nullptr)
	,scan_size_(0)
	,area_xsize_(0)
	,channels_(0)
	,seg_ysize_(0)
	,max_val_inn_(0)
	,random_position_sw_(0)
	,vbo_(nullptr)
	{}
	void set(
	 TINN* image_inn		/* 入力画像位置 */
	,opengl::vertex_buffer_object::vbo_float* xyz /* xyzメモリ */
	,int scan_size			/* 横データサイズ */
	,int area_xsize			/* 横処理サイズ */
	,int channels			/* pixelデータchannelsサイズ */
	,int seg_ysize			/* yサイズ */
	,int max_val_inn		/* 入力画像値正規化用Range */
	,bool random_position_sw
	,opengl::vertex_buffer_object* vbo
	) {
		this->image_inn_ = image_inn;
		this->xyz_ = xyz;
		this->scan_size_ = scan_size;
		this->area_xsize_ = area_xsize;
		this->channels_ = channels;
		this->seg_ysize_ = seg_ysize;
		this->max_val_inn_ = max_val_inn;
		this->random_position_sw_ = random_position_sw;
		this->vbo_ = vbo;
	}

	void work(void) {
	 std::mt19937 engine;
	 std::uniform_real_distribution<> dist( -0.5 ,0.499999 );
	 for (int yy = 0; yy < this->seg_ysize_
	 ; ++yy ,this->image_inn_ += this->scan_size_) {

	  TINN* inn_x = this->image_inn_;
	  for (int xx = 0; xx < this->area_xsize_
	  ;++xx ,inn_x+=this->channels_ ,this->xyz_+=3) {
		double	hh=0., ss=0., vv=0.;
		if ( !this->random_position_sw_ ) {
			calc::rgb_to_hsv(
	 static_cast<double>(inn_x[CH_RED])/this->max_val_inn_
	,static_cast<double>(inn_x[CH_GRE])/this->max_val_inn_
	,static_cast<double>(inn_x[CH_BLU])/this->max_val_inn_
			,hh,ss,vv );
		} else {
		/* RGB256段階で幾何学的並び気持ち悪いためランダムにずらす */
			calc::rgb_to_hsv(
 (static_cast<double>(inn_x[CH_RED])+dist(engine))/this->max_val_inn_
,(static_cast<double>(inn_x[CH_GRE])+dist(engine))/this->max_val_inn_
,(static_cast<double>(inn_x[CH_BLU])+dist(engine))/this->max_val_inn_
			,hh,ss,vv );
		}

		/* hsvからxyz座標値を生成 */
		this->vbo_->hsv_to_xyzarray( hh ,ss ,vv ,this->xyz_ );
	  }
	 }
	}
private:
	TINN* image_inn_;		/* 入力画像位置 */
	opengl::vertex_buffer_object::vbo_float* xyz_;
					/* OpenGL VBO xyzメモリ */
	int scan_size_;			/* 横データサイズ */
	int area_xsize_;		/* 横処理サイズ */
	int channels_;			/* pixelデータchannelsサイズ */
	int seg_ysize_;			/* yサイズ */
	int max_val_inn_;		/* 入力画像値正規化用Range */
	bool random_position_sw_;	/* 範囲外を白点表示するか */
	opengl::vertex_buffer_object* vbo_;
	std::mt19937* engine_;
	std::uniform_real_distribution<>* dist_;
};

template <class TINN , class TOUT>
struct xyz_worker {
void operator() (xyz_thread_job<TINN,TOUT>& oj ,const int id) {
	id;
	//std::cout << "id=" << id << " thread start" << std::endl; 
	oj.work();
	//std::cout << "id=" << id << " thread end" << std::endl;
}
};

template <class TINN , class TOUT>
std::string trace_xyz_(
	int width
	,int channels
	,TINN* image_inn_top
	,int area_xpos
	,int area_ypos
	,int area_xsize
	,int area_ysize
	,const bool random_position_sw
	,opengl::vertex_buffer_object& vbo
)
{
//util::stop_watch stwa; stwa.start();
  if ( vbo.get_hsv_view_start_sw() ) {
	/* ---------- xyz:初期パラメータ設定 ------------------ */
	const int scan_size = width * channels;
	const int start_pos = area_ypos * scan_size + area_xpos * channels;

	const auto max_val_inn = (std::numeric_limits<TINN>::max)();
		/* 注意:windows.hのmax()マクロを回避するためカッコで囲う */

	/* hsv3d表示のxyz値セット(要高速化) */
	opengl::vertex_buffer_object::vbo_float* xyz = vbo.start_vertex();
	if (xyz == nullptr) { /* vboがopen出来ていればここはこないはず */
		return "Error:vbo.start_vertex() return null";
	}
	std::mt19937 engine;
	std::uniform_real_distribution<> dist( -0.5 ,0.499999 );

	TINN *image_inn = image_inn_top + start_pos;

	/* ---------- xyz:分割数を決める ---------------------- */
	int thread_count = 1;
	const int pixel_count = area_xsize * area_ysize;
	const int pixel_max = 1000*100;
	if (pixel_max < pixel_count) {
		thread_count = static_cast<int>(ceil(
			static_cast<double>(pixel_count) / pixel_max));

		const int hw_concu = std::thread::hardware_concurrency();
		if (hw_concu < thread_count) {
			thread_count = hw_concu;
		}
	}

	/* ---------- xyz:スレッド毎のパラメータを設定する ---- */
	std::vector<std::thread> ths(thread_count);
	std::vector<xyz_thread_job<TINN,TOUT>> xyz_otj(thread_count);

	int y1=0, y2=0;
	for (int ii = 0 ;ii < thread_count ;++ii , y1 = y2) {
		y2 = area_ysize * (ii+1) / thread_count;

		/* set */
		xyz_otj.at(ii).set(
		 image_inn+y1*scan_size	/* 入力画像位置 */
		,xyz+y1*area_xsize*3	/* OpenGL VBO xyzメモリ */
		,scan_size		/* 横データサイズ */
		,area_xsize		/* 横処理サイズ */
		,channels		/* pixelデータchannelsサイズ */
		,y2 - y1		/* yサイズ */
		,max_val_inn		/* 入力画像値正規化用Range */
		,random_position_sw	/* 範囲外を白点表示するか */
		,&vbo
		);
	}

	/* ---------- xyz:マルチスレッド実行開始 -------------- */
	int id = 0;
	for (std::thread& th : ths) {
	 th = std::thread( xyz_worker<TINN,TOUT>() ,xyz_otj.at(id) ,id );
	 ++id;
	}

	/* ---------- xyz:マルチスレッド終了待ち -------------- */
	for (std::thread& th : ths) { th.join(); }

#if 0
	for (int yy = 0; yy < area_ysize ; ++yy ,image_inn += scan_size) {

	  TINN* inn_x = image_inn;
	  for (int xx = 0; xx < area_xsize ;++xx ,inn_x+=channels ,xyz+=3) {
		double	hh=0., ss=0., vv=0.;
		if ( !random_position_sw ) {
			calc::rgb_to_hsv(
	 static_cast<double>(inn_x[CH_RED])/max_val_inn
	,static_cast<double>(inn_x[CH_GRE])/max_val_inn
	,static_cast<double>(inn_x[CH_BLU])/max_val_inn
			,hh,ss,vv );
		} else {
		/* RGB256段階で幾何学的並び気持ち悪いためランダムにずらす */
			calc::rgb_to_hsv(
	 (static_cast<double>(inn_x[CH_RED])+dist(engine))/max_val_inn
	,(static_cast<double>(inn_x[CH_GRE])+dist(engine))/max_val_inn
	,(static_cast<double>(inn_x[CH_BLU])+dist(engine))/max_val_inn
			,hh,ss,vv );
		}

		/* hsvからxyz座標値を生成 */
		vbo.hsv_to_xyzarray( hh ,ss ,vv ,xyz );
	  }
	}
#endif
	vbo.end_vertex();
//std::cout << "xyz=" << stwa.stop_ms().count() << "milisec" << "mt=" << thread_count << std::endl;
  }
  	return std::string();
}

template <class TINN , class TOUT>
class rgb_thread_job {
public:
	rgb_thread_job()
	:image_inn_(nullptr)
	,image_out_(nullptr)
	,rgb_(nullptr)
	,scan_size_(0)
	,area_xsize_(0)
	,channels_(0)
	,seg_ysize_(0)
	,max_val_inn_(0)
	,hsv_params_(nullptr)
	,max_val_out_f_(0)
	,white_out_of_area_sw_(0)
	,hsv_view_start_sw_(0)
	,shift_bit_(0)
	,max_glub_out_(0)
	{}
	void set(
	 TINN* image_inn		/* 入力画像位置 */
	,TOUT* image_out		/* 出力画像位置 */
	,GLubyte* rgb			/* OpenGL VBO rgbメモリ */
	,int scan_size			/* 横データサイズ */
	,int area_xsize			/* 横処理サイズ */
	,int channels			/* pixelデータchannelsサイズ */
	,int seg_ysize			/* yサイズ */
	,int max_val_inn		/* 入力画像値正規化用Range */
	,std::vector<calc::trace_by_hsv_params>* hsv_params
	,double max_val_out_f		/* 出力画像値展開用Range */
	,bool white_out_of_area_sw	/* 範囲外を白点表示するか */
	,bool hsv_view_start_sw		/* vbo表示するか */
	,int shift_bit			/* in画像を8bitにするshift値 */
	,GLubyte max_glub_out		/* 白の数値 */
	) {
		this->image_inn_ = image_inn;
		this->image_out_ = image_out;
		this->rgb_ = rgb;
		this->scan_size_ = scan_size;
		this->area_xsize_ = area_xsize;
		this->channels_ = channels;
		this->seg_ysize_ = seg_ysize;
		this->max_val_inn_ = max_val_inn;
		this->hsv_params_ = hsv_params;
		this->max_val_out_f_ = max_val_out_f;
		this->white_out_of_area_sw_ = white_out_of_area_sw;
		this->hsv_view_start_sw_ = hsv_view_start_sw;
		this->shift_bit_ = shift_bit;
		this->max_glub_out_ = max_glub_out;
	}

	void work(void) {
	  for (int yy = 0; yy < this->seg_ysize_ ; ++yy
	  ,this->image_inn_ += this->scan_size_
	  ,this->image_out_ += this->scan_size_) {

	    TINN* inn_x = this->image_inn_;
	    TOUT* out_x = this->image_out_;
	    for (int xx = 0; xx < this->area_xsize_ ;++xx
	    ,inn_x+=this->channels_ ,out_x+=this->channels_) {
		double	hh=0., ss=0., vv=0.;
		calc::rgb_to_hsv(
		 static_cast<double>(inn_x[CH_RED])/this->max_val_inn_
		,static_cast<double>(inn_x[CH_GRE])/this->max_val_inn_
		,static_cast<double>(inn_x[CH_BLU])/this->max_val_inn_
		,hh,ss,vv );

		/* 2値化 */
		double	rr=0., gg=0., bb=0.;
		const bool trace_sw = calc::trace_by_hsv_to_rgb(
			hh,ss,vv, *(this->hsv_params_) ,rr,gg,bb );

		/* 出力 */
		out_x[CH_RED] = static_cast<TOUT>(rr*this->max_val_out_f_);
		out_x[CH_GRE] = static_cast<TOUT>(gg*this->max_val_out_f_);
		out_x[CH_BLU] = static_cast<TOUT>(bb*this->max_val_out_f_);

	      if ( this->hsv_view_start_sw_ ) {
		if ( trace_sw || !this->white_out_of_area_sw_) {
		  this->rgb_[CH_RED] = static_cast<GLubyte>(
		  	inn_x[CH_RED] >> this->shift_bit_);
		  this->rgb_[CH_GRE] = static_cast<GLubyte>(
		  	inn_x[CH_GRE] >> this->shift_bit_);
		  this->rgb_[CH_BLU] = static_cast<GLubyte>(
		  	inn_x[CH_BLU] >> this->shift_bit_);
		} else {
		  /* 2値化しない、かつ、範囲外を白表示モードのとき
		  pixelは白表示 */
		  this->rgb_[CH_RED] = this->max_glub_out_;
		  this->rgb_[CH_GRE] = this->max_glub_out_;
		  this->rgb_[CH_BLU] = this->max_glub_out_;
		}
		this->rgb_ +=3;
	      }
	    }
	  }
	}
private:
	TINN* image_inn_;		/* 入力画像位置 */
	TOUT* image_out_;		/* 出力画像位置 */
	GLubyte* rgb_;			/* OpenGL VBO rgbメモリ */
	int scan_size_;			/* 横データサイズ */
	int area_xsize_;		/* 横処理サイズ */
	int channels_;			/* pixelデータchannelsサイズ */
	int seg_ysize_;			/* yサイズ */
	int max_val_inn_;		/* 入力画像値正規化用Range */
	std::vector<calc::trace_by_hsv_params>* hsv_params_;
	double max_val_out_f_;		/* 出力画像値展開用Range */
	bool white_out_of_area_sw_;	/* 範囲外を白点表示するか */
	bool hsv_view_start_sw_;	/* vbo表示するか */
	int shift_bit_;			/* in画像を8bitにするshift値 */
	GLubyte max_glub_out_;		/* 白の数値 */
};

template <class TINN , class TOUT>
struct rgb_worker {
void operator() (rgb_thread_job<TINN,TOUT>& oj ,const int id) {
	id;
	//std::cout << "id=" << id << " thread start" << std::endl; 
	oj.work();
	//std::cout << "id=" << id << " thread end" << std::endl;
}
};

template <class TINN , class TOUT>
std::string trace_out_and_rgb_(
	int width
	,int channels
	,TINN* image_inn_top
	,int area_xpos
	,int area_ypos
	,int area_xsize
	,int area_ysize
	,const std::vector<calc::trace_by_hsv_params>& hsv_params
	,TOUT* image_out_top
	,const bool white_out_of_area_sw
	,opengl::vertex_buffer_object& vbo
)
{
//util::stop_watch stwa; stwa.start();
	/* ---------- rgb:初期パラメータ設定 ------------------ */
	const int scan_size = width * channels;
	const int start_pos = area_ypos * scan_size + area_xpos * channels;

	const auto max_val_inn = (std::numeric_limits<TINN>::max)();
		/* 注意:windows.hのmax()マクロを回避するためカッコで囲う */

	const double max_val_out_f = (std::numeric_limits<TOUT>::max)() + 0.999999;
	const int shift_bit =	std::numeric_limits<TINN>::digits - 
				std::numeric_limits<GLubyte>::digits;
	const auto max_glub_out = (std::numeric_limits<GLubyte>::max)();

	/* 画像のpixel値と、hsv3d表示のrgb値セット(要高速化) */
	GLubyte* rgb = nullptr;
  if ( vbo.get_hsv_view_start_sw() ) {
	rgb = vbo.start_color();
	if (rgb == nullptr) { /* open出来ていればここはこないはず */
		return "Error:vbo.start_color() return null";
	}
  }
	TINN *image_inn = image_inn_top + start_pos;
	TOUT *image_out = image_out_top + start_pos;

	/* ---------- rgb:分割数を決める ---------------------- */
	int thread_count = 1;
	const int pixel_count = area_xsize * area_ysize;
	const int pixel_max = 1000*100;
	if (pixel_max < pixel_count) {
		thread_count = static_cast<int>(ceil(
			static_cast<double>(pixel_count) / pixel_max));

		const int hw_concu = std::thread::hardware_concurrency();
		if (hw_concu < thread_count) {
			thread_count = hw_concu;
		}
	}

	/* ---------- rgb:スレッド毎のパラメータを設定する ---- */
	std::vector<std::thread> ths(thread_count);
	std::vector<rgb_thread_job<TINN,TOUT>> rgb_otj(thread_count);

	int y1=0, y2=0;
	for (int ii = 0 ;ii < thread_count ;++ii , y1 = y2) {
		y2 = area_ysize * (ii+1) / thread_count;

		/* set */
		rgb_otj.at(ii).set(
		 image_inn+y1*scan_size	/* 入力画像位置 */
		,image_out+y1*scan_size	/* 出力画像位置 */
		,rgb+y1*area_xsize*3	/* OpenGL VBO rgbメモリ */
		,scan_size		/* 横データサイズ */
		,area_xsize		/* 横処理サイズ */
		,channels		/* pixelデータchannelsサイズ */
		,y2 - y1		/* yサイズ */
		,max_val_inn		/* 入力画像値正規化用Range */
	,const_cast<std::vector<calc::trace_by_hsv_params> *>(&hsv_params)
					/* 2値化処理パラメータ */
		,max_val_out_f		/* 出力画像値展開用Range */
		,white_out_of_area_sw	/* 範囲外を白点表示するか */
		,vbo.get_hsv_view_start_sw()
		,shift_bit		/* in画像を8bitにするshift値 */
		,max_glub_out		/* 白の数値 */
		);
	}

	/* ---------- rgb:マルチスレッド実行開始 -------------- */
	int id = 0;
	for (std::thread& th : ths) {
	 th = std::thread( rgb_worker<TINN,TOUT>() ,rgb_otj.at(id) ,id );
	 ++id;
	}

	/* ---------- rgb:マルチスレッド終了待ち -------------- */
	for (std::thread& th : ths) { th.join(); }

	//-----------------------------------------------------
#if 0
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
		const bool trace_sw = calc::trace_by_hsv_to_rgb(
			hh,ss,vv, hsv_params ,rr,gg,bb );

		/* 出力 */
		out_x[CH_RED] = static_cast<TOUT>(rr * max_val_out_f);
		out_x[CH_GRE] = static_cast<TOUT>(gg * max_val_out_f);
		out_x[CH_BLU] = static_cast<TOUT>(bb * max_val_out_f);

  if ( vbo.get_hsv_view_start_sw() ) {
		if ( trace_sw || !white_out_of_area_sw ) {
			rgb[CH_RED] = inn_x[CH_RED] >> shift_bit;
			rgb[CH_GRE] = inn_x[CH_GRE] >> shift_bit;
			rgb[CH_BLU] = inn_x[CH_BLU] >> shift_bit;
		} else {
			/* 2値化しない、かつ、範囲外を白表示モードのとき
			pixelは白表示 */
			rgb[CH_RED] = max_glub_out;
			rgb[CH_GRE] = max_glub_out;
			rgb[CH_BLU] = max_glub_out;
		}
		rgb+=3;
  }
	    }
	}
#endif
	//-----------------------------------------------------
  if ( vbo.get_hsv_view_start_sw() ) {
	vbo.end_color();
  }
//std::cout << "rgb=" << stwa.stop_ms().count() << "milisec" << "mt=" << thread_count << std::endl;
	return std::string();
}
} // namespace

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

	if ( vbo.get_hsv_view_start_sw() ) {
  		/* vboを使うにはOpenGL初期化済であること */ 
		/* vbo初期化あるいは再設定 */
		std::string err_msg( vbo.open_or_reopen(
			this->area_xsize_ * this->area_ysize_
		) );
		if (!err_msg.empty()) {
			return err_msg;
		}
	}

	std::string err_msg;
	switch (this->cl_ch_info.get_e_ch_num_type()) {
	case E_CH_NUM_UCHAR:
		err_msg = trace_xyz_<unsigned char,unsigned char>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned char*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,random_position_sw
			,vbo
		);
		if (!err_msg.empty()) { return err_msg; }
		err_msg = trace_out_and_rgb_<unsigned char,unsigned char>(
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
			,vbo
		);
		return err_msg;
	case E_CH_NUM_USHRT:
		err_msg = trace_xyz_<unsigned short,unsigned short>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned short*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,random_position_sw
			,vbo
		);
		if (!err_msg.empty()) { return err_msg; }
		err_msg = trace_out_and_rgb_<unsigned short,unsigned short>(
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
			,vbo
		);
		return err_msg;
	case E_CH_NUM_ULONG:
		err_msg = trace_xyz_<unsigned long,unsigned long>(
			this->get_l_width()
			,this->get_l_channels()
			,static_cast<unsigned long*>(pare->get_vp_canvas())
			,this->area_xpos_
			,this->area_ypos_
			,this->area_xsize_
			,this->area_ysize_
			,random_position_sw
			,vbo
		);
		if (!err_msg.empty()) { return err_msg; }
		err_msg = trace_out_and_rgb_<unsigned long,unsigned long>(
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
			,vbo
		);
		return err_msg;
	case E_CH_NUM_DOUBL: break; /* Not support */
	case E_CH_NUM_BITBW: break; /* for no warning */
	case E_CH_NUM_EMPTY: break; /* for no warning */
	}

	return std::string();
}
