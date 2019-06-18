#include <stdio.h>
#include <stdlib.h>
#include <FL/fl_ask.H>
#include "pri.h"
#include "gts_str_language.h" // gts_str::
#include "gts_master.h"

void gts_master::cb_quit( void )
{
	if (!fl_ask(
//		"Are you sure you want to quit?"
		gts_str::quit::ask_quit
	)) {
		return;
	}

	if (OK != this->cl_memo_desktop.save()) {
		pri_funct_err_bttvr(
	 "Error : this->cl_memo_desktop.save(-) returns NG" );
	}

	exit(0);
}
