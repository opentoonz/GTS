#include "calcu_color_trace_sep_hsv.h"
#include "fl_gl_hsv_view.h"

bool calcu_color_trace_sep_hsv::exec(
	const double hh, const double ss, const double vv
	, double *rr, double *gg, double *bb
)
{
	calcu_sep_black_and_color sep_b_and_c(ss,vv);

	//for (unsigned ii = 0; ii < this->cla_area_param.size(); ++ii) {
	for (int ii = static_cast<int>(this->cla_area_param.size())-1
	;0<=ii ;--ii) {
		calcu_sep_hsv& area =  this->cla_area_param.at(ii);

		/* 有効でない範囲は無視して他の範囲を探す */
		if (area.enable_sw == false) { continue; }

		/* 黒線 */
		if (area.hue_min < 0. || area.hue_max < 0.) {
			/* 太さ外のときは次ループへ */
			if (area.thickness < vv) { continue; }

			/* 色味範囲のときは次ループへ */
			if ((0. < vv) && (0. < ss)
			&& (sep_b_and_c.is_black_side(
	gts::liner_from_rad(gts::rad_from_deg(area.threshold_slope_deg))
			,area.threshold_intercept
			) == false)) {
				continue;
			}
			/* vvがゼロあるいは、ssがゼロのときは黒線 */
		}

		/* 色線 */
		else {
			/* 色相の範囲外の時は次ループへ */
			if (area.hue_min < area.hue_max) {
				if (hh < area.hue_min) { continue; }
				if (area.hue_max < hh) { continue; }
			}
			else {
				if ((area.hue_max < hh)
				&&  (hh < area.hue_min)) { continue; }
			}

			/* 太さ外のときは次ループへ */
			if (area.thickness < (1. - ss)) { continue; }

			/* 黒である(色味がない)ので次ループへ */
			if (vv <= 0.) { continue; }

			/* 色味がないので次ループへ */
			if (ss <= 0.) { continue; }

			/* 黒味範囲のときは次ループへ */
			if (sep_b_and_c.is_black_side(
	gts::liner_from_rad(gts::rad_from_deg(area.threshold_slope_deg))
			,area.threshold_intercept
			)) {
				continue;
			}
		}

		/* 指定範囲の色で、トレススイッチONなら、
		トレス(指定の色に)して、抜ける
		範囲が重複していたらループで先の指定を優先する */
		*rr = area.target_r;
		*gg = area.target_g;
		*bb = area.target_b;
		return true;
	}
	/* 有効な範囲がなく2値化をしないなら白色(紙の地の色)にする */
	*rr = this->target_paper_r_;
	*gg = this->target_paper_g_;
	*bb = this->target_parer_b_;
	return false;
}
