#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

/*--------------------------------------------------------*/

void gts_master::set_scrollbar( void )
{
	double	d_min, d_max, d_len;
	int	i_total, i_pos, i_size;
	iip_opengl_l1edit *clp_opengl_l1edit;

	d_min = this->cl_ogl_view.get_d_scrollbar_x_min();
	d_max = this->cl_ogl_view.get_d_scrollbar_x_max();
	d_len = d_max - d_min;

	/* 画像が画面より小さいときはスクロールバーは必要ない */
	if (1.0 < d_len) {
		cl_gts_gui.scrbar_view_x->value(0,1,0,1);
		this->cl_fltk_event.set_l_scrollbar_x_min(0);
		this->cl_fltk_event.set_l_scrollbar_x_max(1);
	} else {
		/* 画像が画面より大きいとき、バーのずれを戻す */
		if (d_min < 0.0) {
			d_max -= d_min;
			d_min = 0.0;
		}
		if (1.0 < d_max) {
			d_min -= d_max - 1.0;
			d_max = 1.0;
		}

		/* スクロールバーの大きさと位置を設定 */
		clp_opengl_l1edit=this->cl_ogl_view.get_clp_iip_view();
		i_total = clp_opengl_l1edit->get_l_view_x_size();
		i_pos = (int)(i_total * d_min);
		i_size = (int)(i_total * (d_max - d_min));
		cl_gts_gui.scrbar_view_x->value(
			i_pos,i_size,0,i_total
		);

		/* 設定したスクロールバーから最大値と最小値を記憶 */
		this->cl_fltk_event.set_l_scrollbar_x_min(
			    (long)(cl_gts_gui.scrbar_view_x->minimum())
		);
		this->cl_fltk_event.set_l_scrollbar_x_max(
			    (long)(cl_gts_gui.scrbar_view_x->maximum())
		);
	}

	d_min = this->cl_ogl_view.get_d_scrollbar_y_min();
	d_max = this->cl_ogl_view.get_d_scrollbar_y_max();
	d_len = d_max - d_min;

	/* 画像が画面より小さいときはスクロールバーは必要ない */
	if (1.0 < d_len) {
		cl_gts_gui.scrbar_view_y->value(0,1,0,1);
		this->cl_fltk_event.set_l_scrollbar_y_min(0);
		this->cl_fltk_event.set_l_scrollbar_y_max(1);
	} else {
		/* 画像が画面より大きいとき、バーのずれを戻す */
		if (d_min < 0.0) {
			d_max -= d_min;
			d_min = 0.0;
		}
		if (1.0 < d_max) {
			d_min -= d_max - 1.0;
			d_max = 1.0;
		}

		/* スクロールバーの大きさと位置を設定 */
		clp_opengl_l1edit=this->cl_ogl_view.get_clp_iip_view();
		i_total = clp_opengl_l1edit->get_l_view_y_size();
		i_pos = (int)(i_total * (1.0-d_max));
		i_size = (int)(i_total * (d_max - d_min));
		cl_gts_gui.scrbar_view_y->value(
			i_pos, i_size, 0, i_total
		);

		/* 設定したスクロールバーから最大値と最小値を記憶 */
		this->cl_fltk_event.set_l_scrollbar_y_min(
			    (long)(cl_gts_gui.scrbar_view_y->minimum())
		);
		this->cl_fltk_event.set_l_scrollbar_y_max(
			    (long)(cl_gts_gui.scrbar_view_y->maximum())
		);
	}
}
