#include "calcu_color_trace_hab.h"

void calcu_color_trace_hab::exec( double d_hh, double d_aa, double d_bb, double *dp_red, double *dp_gre, double *dp_blu )
{
	int tt;
	calcu_col_area_hab *clp_hab;

	for (	tt = E_COLOR_TRACE_HAB_01;
		tt < E_COLOR_TRACE_HAB_NOT_SELECT; ++tt
	) {
		clp_hab = &(this->cla_area_param[tt]);

		/* 色の範囲外の時はループの次へ */
		if (clp_hab->d_hh_min <= clp_hab->d_hh_max) {
			if (d_hh < clp_hab->d_hh_min) { continue; }
			if (clp_hab->d_hh_max < d_hh) { continue; }
		} else {
			if (	(clp_hab->d_hh_max < d_hh) &&
				(d_hh < clp_hab->d_hh_min)
			) { continue; }
		}
		if (d_aa < clp_hab->d_aa_min) { continue; }
		if (clp_hab->d_aa_max < d_aa) { continue; }

		if (d_bb < clp_hab->d_bb_min) { continue; }
		if (clp_hab->d_bb_max < d_bb) { continue; }


		/* 色の範囲内だけど、実行OFFのときは
		白色(紙の地の色)にする */
		if (OFF == clp_hab->i_exec_sw) { break; }

		/* habの指定範囲の色で、トレススイッチONなら、
		トレス(指定の色に)して、抜ける
		hab範囲が重複していたら先の指定を優先する */
		*dp_red = clp_hab->d_red;
		*dp_gre = clp_hab->d_gre;
		*dp_blu = clp_hab->d_blu;
		return;
	}
	/* トレスをしない部分は白色(紙の地の色)にする */
	*dp_red = this->_d_bg_red;
	*dp_gre = this->_d_bg_gre;
	*dp_blu = this->_d_bg_blu;
}
