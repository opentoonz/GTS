#include "pri.h"
#include "fltk_opengl.h"
#include "gts_master.h"

fltk_opengl::fltk_opengl(int x,int y,int w,int h,const char *l)
	: Fl_Gl_Window(x,y,w,h,l)
{
}

void fltk_opengl::draw()
{
	static int i_only_one_time_sw = 1;

	/* reshape(windowサイズの変更か再表示の場合) */
	if (!(this->valid())) {
		/* Fl_Gl_Window widget,
		The default mode is FL_RGB|FL_DOUBLE|FL_DEPTH. */

		/* OpenGL初期化(アプリの生成後一回のみ実行) */
		if (i_only_one_time_sw) {
			cl_gts_master.cl_ogl_view.init_opengl();
			i_only_one_time_sw = 0;
		}

		/* viewport()とortho()を平行投影に設定する */
		//this->ortho();

		/* 画像データがあるとき */
		if (cl_gts_master.cl_ogl_view.is_main_canvas()) {
			cl_gts_master.cl_ogl_view.reshape_opengl(
				(long)(this->w()),
				(long)(this->h())
			);
			cl_gts_master.set_scrollbar();
		}
		/* 画像データがないとき */
		else {
			cl_gts_master.cl_ogl_view.clear_opengl(
				(long)(this->w()),
				(long)(this->h())
			);
		}
	}

	if (cl_gts_master.cl_ogl_view.is_main_canvas()) {

		/* subエリアのカラートレス処理
		と(指定にあれば)ドットノイズ除去 */
		cl_gts_master.color_trace_in_view_area();

		/* OpenGL全表示 */
		cl_gts_master.cl_ogl_view.draw_opengl();
	}
}
