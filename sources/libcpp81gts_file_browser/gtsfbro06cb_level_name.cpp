// #include <iostream>
#include <string>
#include "gtsfbro06cb_level.h"
#include "gts_gui.h"

void gtsfbro06cb_level::cb_level_name( void )
{
	std::string level_name( cl_gts_gui.strinp_level_file->value() );

// std::cout << "level_name=" << level_name << std::endl;

	bool overwrite_sw = false;

	if (0 < level_name.size()) {
	 for (int ii=0 ;; ++ii) {
		const char *name = this->cp_dir_or_level_name(ii);
		if (name == 0) { break; } /* 終了 */

// std::cout << ii << " \"" << name << "\"" << std::endl;
		if (level_name == name) {	/* 上書き */
			overwrite_sw = true;
			break;
		}
	 }
	}

	if (overwrite_sw) {	/* 上書き */
		Fl_Color col = FL_YELLOW;
		//Fl_Color col = (Fl_Color)92;
		//Fl_Color col = (Fl_Color)213;/* satsuei list checkに近い色 */
		cl_gts_gui.strinp_level_file->color(col);
		cl_gts_gui.strinp_level_file->redraw();
// std::cout << "overwrite" << std::endl;
	} else {	/* 新規ファイル */
		Fl_Color col = FL_WHITE;
		cl_gts_gui.strinp_level_file->color(col);
		cl_gts_gui.strinp_level_file->redraw();
// std::cout << "new file" << std::endl;
	}
}
