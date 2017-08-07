#include "calcu_color_trace_sep_hsv.h"

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
			if (area.thickness < (1.-ss)) { continue; }

			/* 黒である(色味がない)ので次ループへ */
			if (vv <= 0.) { continue; }

			/* 色味がないので次ループへ */
			if (ss <= 0.) { continue; }

			/* 計算のため反転する */
			const double tt = 1.-area.threshold_to_black;

			/* 黒味範囲のときは次ループへ */
			if ( (0. < tt)
			&&   ((1.-tt)/tt) < ((1.-vv)/(ss*vv))) { continue; }
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
