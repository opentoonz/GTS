#ifndef calc_trace_by_hsv_h
#define calc_trace_by_hsv_h

#include <cmath>	// sin() ,cos() ,sqrt()
#include <vector>

namespace calc {

/* 直角二等辺三角形の直角点を中心とした回転角から、
中心の対辺上の位置を得る */
double line_len_from_rad( const double rad );

/*
[HSV色立体から各色区域分けをして目的の色を得る]

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
		T=calc::trace_by_hsv_params::slope_line_len
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


	T直線を上下に移動する変数をInterceptとすると
	Point位置を逆にIntercept掛ける
	T比	(1 - T) / T
	P比	(1 - V - Intercept) / (S * V)

	Pが黒味側であるかの判断は
	(1 - T) / T   <   (1 - V - Intercept) / (S * V) 

	(0 <= T) && (0 <= S) && (0 <= V)である場合は、
	(1 - T) * (S * V)  <   (1 - V - Intercept) * T

	(注) T=slope_line_len
*/
class trace_by_hsv_params {
public:
	bool	enable_sw;	/* 2値化処理実行sw(false=他の2値化処理へ) */

	double	 target_r	/* 0...1 結果色 */
		,target_g
		,target_b;

	double	thickness;	/* 0...1 色/黒線太さ */

	double	hue_min
		,hue_max;	/* 0...360 拾うべき色相範囲
				   Minusの場合は黒扱う */
	double	slope_line_len;	/* 0...1 =黒...色の境界傾き
	(sin,cos不使用で)高速化するため、角度でなく対辺の位置で表す */
	double	intercept;	/* 0...1 =黒...色の境界切片 */
	bool	display_sw;	/* 黒-色の境界で分別表示するsw */
	bool	rotate360_sw;	/* hue_min/hue_maxが同値の場合のo/c判断 */
};

/*
h(=0...<360),s(=0...1),v(=0...1)を入力値として、
hsv_paramsによって判断し、
トレス(2値化)したらr,g,b(=0...1)にトレス(2値化)値を入れてtrueを返す
トレス(2値化)しなかったら r,g,b(=1)(=白紙)を入れてfalseを返す */
bool trace_by_hsv_to_rgb(
	const double h, const double s, const double v
	,const std::vector<calc::trace_by_hsv_params>& hsv_params
	, double& r, double& g, double& b
);

} // namespace calc

#endif /* !calc_trace_by_hsv_h */
