#include "calcu_color_trace_sep_hsv.h"

/*

 >> 色味と黒味を区切る方法 <<

 1 HSV立体のSV断面

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

	P位置	( S * V  , V )
	T位置	( T      , T )

 3 左上原点座標系にしたときの位置

	0 |---- S --->| 1
      0 - +-----------+
	| | \        /  1
	| |    \   /
	V |  P   +
	| |    /   T
	v |  /
      1 - +
	     0

	P位置	( S * V  , 1 - V )
	T位置	( T      , 1 - T )

 4 左上原点座標系にて、原点とTを結ぶ直線とP位置との関係で、
   色味か黒味かを判断する。
   そのため、T比とP比の比較で位置関係を見る

	P比	(1 - V) / (S * V)
	T比	(1 - T) / T

	P比 <= T比	色味側である
	P比 >  T比	黒味側である

	よって、色味側であるかの判断は
	(1 - V) / (S * V)  <=  (1 - T) / T
*/

void calcu_color_trace_sep_hsv::exec( double hh, double ss, double vv, double *rr, double *gg, double *bb )
{
	for (unsigned ii = 0; ii < this->cla_area_param.size(); ++ii) {
		calcu_sep_hsv& area =  this->cla_area_param.at(ii);

		if (area.hmin < 0. || area.hmax < 0.) {	/* 黒線 */
			/* 太さ外のときはループの外へ */
			if (area.thickness < vv) { continue; }
		}
		else {				/* 色線 */
			/* 色の範囲外の時は次ループへ */
			if (area.hmin < area.hmax) {
				if (hh < area.hmin) { continue; }
				if (area.hmax < hh) { continue; }
			}
			else {
				if ((area.hmax < hh)
				&&  (hh < area.hmin)) { continue; }
			}

			/* 太さ外のときは次ループへ */
			if (area.thickness < (1. - ss)) { continue; }

			/* 黒である(色味がない)ので次ループへ */
			if (vv <= 0.) { continue; }

			/* 色味がないので次ループへ */
			if (ss <= 0.) { continue; }

			/* 計算のため反転する */
			const double tt = 1.-area.threshold_to_black;

			/* 黒味範囲のときは次ループへ */
			if ( (0. < tt)
			&&   ((1. - tt)/tt) < ((1. - vv)/(ss * vv)) ) {
				continue;
			}
		}

		/* 色の範囲内だけど、実行OFFのとき白色(紙の地の色)にする */
		if (area.enable_sw == false) { break; }

		/* habの指定範囲の色で、トレススイッチONなら、
		トレス(指定の色に)して、抜ける
		hab範囲が重複していたら先の指定を優先する */
		*rr = area.target_r;
		*gg = area.target_g;
		*bb = area.target_b;
		return;
	}
	/* トレスをしない部分は白色(紙の地の色)にする */
	*rr = this->tgt_bg_red_;
	*gg = this->tgt_bg_green_;
	*bb = this->tgt_bg_blue_;
}
