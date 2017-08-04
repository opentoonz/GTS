#include "calcu_color_trace_sep_hsv.h"

void calcu_color_trace_sep_hsv::exec( double hh, double ss, double vv, double *rr, double *gg, double *bb )
{
	for (unsigned ii = 0; ii < this->cla_area_param.size(); ++ii) {
		calcu_sep_hsv& area =  this->cla_area_param.at(ii);

		if (area.src_hmin < 0) {	/* 黒線 */
			/* 太さ外のときはループの外へ */
			if (area.src_thickness < vv) { continue; }
		}
		else {				/* 色線 */
			/* 色の範囲外の時は次ループへ */
			if (hh < area.src_hmin) { continue; }
			if (area.src_hmax < hh) { continue; }

			/* 太さ外のときは次ループへ */
			if (area.src_thickness < (1.-ss)) { continue; }

			/* 黒である(色味がない)ので次ループへ */
			if (vv <= 0.) { continue; }

			/* 色味がないので次ループへ */
			if (ss <= 0.) { continue; }

			/* 計算のため反転する */
			const double tt = 1.-area.src_threshold_to_black;

			/* 黒味範囲のときは次ループへ */
			if ( (0. < tt)
			&&   ((1.-tt)/tt) < ((1.-vv)/(ss*vv))) { continue; }
		}

		/* 色の範囲内だけど、実行OFFのとき白色(紙の地の色)にする */
		if (area.tgt_line_color_sw == false) { break; }

		/* habの指定範囲の色で、トレススイッチONなら、
		トレス(指定の色に)して、抜ける
		hab範囲が重複していたら先の指定を優先する */
		*rr = area.tgt_line_color_red;
		*gg = area.tgt_line_color_green;
		*bb = area.tgt_line_color_blue;
		return;
	}
	/* トレスをしない部分は白色(紙の地の色)にする */
	*rr = this->tgt_bg_red_;
	*gg = this->tgt_bg_green_;
	*bb = this->tgt_bg_blue_;
}
