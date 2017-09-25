#ifndef calcu_color_trace_sep_hsv_h
#define calcu_color_trace_sep_hsv_h

/*
HSV色立体から各色区域分けをして目的の色を得る

○Hue
	R - Y - G - C - B - M - R
	赤  黄  緑  水  青  紫  赤

○min,max的考えから、各色区域分け
	色
		hue min.	0...360 色相のサイクリック範囲の最小値
		hue max.	0...360 色相のサイクリック範囲の最大値
		saturation min.	太さを表す
		saturation max.	1固定
		value min.	調整値(0.5等)
		value max.	1固定

	黒(色とは範囲計算方法は違う)
		hue min.	0
		hue max.	360
		saturation min.	0固定
		saturation max.	調整値(0.3等)
		value min.	0固定
		value max.	太さを表す

○色と黒を区切るのを、"色value min."黒saturation max." から ななめ切断
  にする方法

 1 HSV立体のSV断面
	S=0,V=0からS=1,V=1への直線上をたどるパラメータをTとする
		T=calcu_sep_hsv::threshold_slope_deg
	Tの位置からS=0,V=1位置へ直線を引き、この直線で上下に分けることで、
	色領域か黒領域か判断を行う
		T=0	色味なし
		T=1	全て色味

	0 |---- S --->| 1
      1 - +-----------+
	^ |          /  1
	| |        /
	V |  P   +
	| |    /   T
	| |  /
      0 - +
	     0
		※ T 色味と黒味を切断するための位置
		※ P 各ピクセル

 2 左下原点のまま、直行座標系における位置

	T位置	( T      , T )
	P位置	( S * V  , V )

 3 左上原点座標系に(上下反転)したときの位置

	0 |---- S --->| 1
      0 - +-----------+
	| | \        /  1
	| |    \   /
	V |  P   +
	| |    /   T
	v |  /
      1 - +
	     0

	T位置	( T      , 1 - T )
	P位置	( S * V  , 1 - V )

 4 左上原点座標系にて、原点とTを結ぶ直線とP位置との関係で、
   色味か黒味かを判断する。
   そのため、T比とP比の比較で位置関係を見る

	T比	(1 - T) / T
	P比	(1 - V) / (S * V)

	T比 <  P比	黒味側である
	T比 => P比	色味側である

	よって、黒味側であるかの判断は
	(1 - T) / T   <   (1 - V) / (S * V) 


	T直線を上下に移動する変数をOffsetとすると
	Point位置を逆にOffset掛ける
	T比	(1 - T) / T
	P比	(1 - V - Offset) / (S * V)

	Pが黒味側であるかの判断は
	(1 - T) / T   <   (1 - V - Offset) / (S * V) 
*/

#include <vector>

class calcu_sep_black_and_color {
public:
	calcu_sep_black_and_color(const double s ,const double v)
		:one_minus_v_(0.)
		,s_mul_v_(0.)
	{
		this->one_minus_v_ = (1. - v);
		this->s_mul_v_ = (s * v);
	}
	inline bool is_black_side(
		const double threshold_slope_line ,const double offset
	) {
		if ( threshold_slope_line == 0.) { /* threshold_slope_degが0なら全て色部分 */
			return false;
		}
		if (this->s_mul_v_ == 0.) {/* 色味か明度がゼロなら黒部分 */
			return true;
		}
		if ( ((1. - threshold_slope_line) / threshold_slope_line) <
		(this->one_minus_v_ - (1. - offset)) / this->s_mul_v_ ) {
			return true;	/* 斜め切断して黒味側 */
		}
		return false; /* 上以外は色側 */
	}
private:
	double one_minus_v_ ,s_mul_v_;
};
/*-------------------------------------------------------*/
class calcu_sep_hsv {
public:
	bool	enable_sw;	/* 2値化処理実行 false=他の2値化処理へ */

	double	 target_r	/* 0...1 結果色 */
		,target_g
		,target_b;

	double	thickness;	/* 0...1 色/黒線太さ(=彩度最小値) */

	double	hue_min , hue_max;	/* 0...360 拾うべき色相範囲
					0より小さいなら色でなく黒扱う */
	double	threshold_slope_deg;/* 0...1 SV面上黒線との取合い境界 */
	double	threshold_intercept;/* 0...1 SV面上黒線との
				取合い境界線の原点位置のオフセット */
	bool	hsv_view_guide_sw;	/* hsv viewerで範囲を表示するsw */
};
/*-------------------------------------------------------*/
/* いままでのクラスと共存させるための一時的措置 --> 要refactering */
class calcu_color_trace_base {
public:
	virtual bool exec(
		const double hh, const double ss, const double vv
		, double *rr, double *gg, double *bb
	){
		(void)hh; (void)ss; (void)vv; (void)rr; (void)gg; (void)bb;
		return false;
	}
};

class calcu_color_trace_sep_hsv : public calcu_color_trace_base {
public:
	calcu_color_trace_sep_hsv()
	:target_paper_r_(1.)
	,target_paper_g_(1.)
	,target_parer_b_(1.)
	{}

	std::vector<calcu_sep_hsv> cla_area_param;

	void setup_default_area_param(void) {
		this->cla_area_param = {
 { true  ,0.,0.,0. ,0.7 , -1 , -1  ,45.,1. ,true  } /* 黒 */
,{ true  ,1.,0.,0. ,0.7 ,300., 60. ,45.,1. ,true  } /* 赤 */
,{ true  ,0.,0.,1. ,0.7 ,180.,300. ,45.,1. ,true  } /* 青 */
,{ true  ,0.,1.,0. ,0.7 , 60.,180. ,45.,1. ,true  } /* 緑 */
,{ false ,0.,1.,1. ,0.7 ,120.,240. ,45.,1. ,false } /* 水 */
,{ false ,1.,0.,1. ,0.7 ,240.,360. ,45.,1. ,false } /* 紫 */
,{ false ,1.,1.,0. ,0.7   ,0.,120. ,45.,1. ,false } /* 黄(or オレンジ) */
		};
	}

	/* hh = 0...360 , ss,vv,rr,gg,bb = 0...1 */
	bool exec(
		const double hh, const double ss, const double vv
		, double* rr, double* gg, double* bb
	);
private:
	double	 target_paper_r_
		,target_paper_g_
		,target_parer_b_;
};

#endif /* !calcu_color_trace_sep_hsv_h */
