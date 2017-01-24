#include "pri.h"
#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_scan_and_preview( void )
{
	/* スキャンを実行 */
	iip_canvas* clp_scan = this->iipg_scan();
	if (NULL == clp_scan) {
		pri_funct_err_bttvr(
		      "Error : this->iipg_scan() returns NULL" );
		return;
	}

	this->rot_and_trace_and_enoise_and_preview_(
		clp_scan
		, cl_gts_gui.choice_rot90->value()
	);
}
