#ifndef calcu_color_trace_sep_hsv_h
#define calcu_color_trace_sep_hsv_h

/*
  HSV色立体から各色区域分けをして目的の色を得る

    ○Hue
	R - Y - G - C - B - M - R
	赤  黄  緑  水  青  紫  赤

    ○min,max的考えから、各色区域分け方法
	色
		hue min. max.	0...360 各区域の色相の範囲
		saturation min.	太さを表す
		saturation max.	1固定
		value min.	使わない
		value max.	1固定
		smin,smax,vmin,vmaxで計算利用

	黒(色とは範囲計算方法は違う)
		hue min. max.	0より小(-1)は黒を扱うことを示す。
		saturation min.	使わない(色味の残りで取る)
		saturation max.	使わない(色味の残りで取る)
		value min.	0固定
		value max.	太さを表す

    ○色と黒との分離方法 (T = calcu_sep_hsv::threshold_to_black)

	  0 ----- S ----->1
	1 +---------------+
	^ |             /
	| |           /
	| |         /
	V |       /  T
	| |     /
	| |   /
	  | /
	0 +

	S=0,V=0からS=1,V=1への直線上をたどるパラメータをTとする
	Tの位置からS=0,V=1位置へ直線を引き、この直線で上下に分けることで、
	色領域か黒領域か判断を行う
		Tについて
			T=0	色味なし
			T=1	全て色味
			上記値を反転してパラメーターとして使う
		Pixel位置
			p=( S * T , V )	※ "S * T"で正方座標に変換
		判断位置
			t=( T     , T )
		上下反転して左上を原点にする
			p=( S*T , 1-V )
			t=( T   , 1-T )
		比で位置を判断
			1<=V	--> 白〜色 --> 色
			1<=T	--> 色
			pd= (1-V) / S*T
			td= (1-T) / T    
			pd < td	--> 上側 --> 色
			td < pd	--> 下側 --> 黒
		計算式考察 --> マイナスが入るとだめか?!
			(1-T) / T     <  (1-V) / S*T
			(1-T) * S * T <  (1-V) * T
*/

#include <vector>

class calcu_sep_hsv {
public:
	bool	enable_sw;	/* 2値化処理実行 false=他の2値化処理へ */

	double	 target_r	/* 0...1 結果色 */
		,target_g
		,target_b;

	double	thickness;	/* 0...1 色/黒線太さ(=彩度最小値) */

	double	hmin , hmax;	/* 0...360 拾うべき色相範囲
					0より小さいなら色でなく黒扱う */
	double	threshold_to_black;/* 0...1 SV面上黒線との取合い境界 */
	double	threshold_offset;/* 0...1 SV面上黒線との
				取合い境界線の原点位置のオフセット */
	bool	hsv_view_guide_sw;	/* hsv viewerで範囲を表示するsw */
};

/*-------------------------------------------------------*/
/* いままでのクラスと共存させるための一時的措置 --> 要refactering */
class calcu_color_trace_base {
public:
	virtual bool exec(
	double hh, double ss, double vv, double *rr, double *gg, double *bb
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
 { true  ,0.,0.,0. ,0.7 , -1 , -1  ,0.8,0.0 ,true } /* 黒 */
,{ true  ,1.,0.,0. ,0.7 ,300., 60. ,0.8,0.0 ,true } /* 赤 */
,{ true  ,0.,0.,1. ,0.7 ,180.,300. ,0.8,0.0 ,true } /* 青 */
,{ true  ,0.,1.,0. ,0.7 , 60.,180. ,0.8,0.0 ,true } /* 緑 */
,{ false ,0.,1.,1. ,0.7 ,120.,240. ,0.8,0.0 ,false } /* 水 */
,{ false ,1.,0.,1. ,0.7 ,240.,360. ,0.8,0.0 ,false } /* 紫 */
,{ false ,1.,1.,0. ,0.7   ,0.,120. ,0.8,0.0 ,false } /* 黄(or オレンジ) */
		};
	}

	/* hh = 0...360 , ss,vv,rr,gg,bb = 0...1 */
	bool exec(
	double hh, double ss, double vv, double *rr, double *gg, double *bb
	);
private:
	double	 target_paper_r_
		,target_paper_g_
		,target_parer_b_;
};

#endif /* !calcu_color_trace_sep_hsv_h */
