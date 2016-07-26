#include "calcu_histogram_hab.h"

void data_histogram_hab::init( void )
{
	long ii;
	for (ii = 0L; ii < CALCU_HISTOGRAM_SIZE; ++ii) {
		this->la1000[ii] = 0L;
	}
	this->l_max = 0L;
}

void data_histogram_hab::add( double d_ratio )
{
	long	l_pos;

	/* 0...1でlimit */
	if (d_ratio < 0.0) { d_ratio = 0.0; }
	if (1.0 < d_ratio) { d_ratio = 1.0; }

	/* l_posは
		CALCU_HISTOGRAM_SIZE個で、
		0...CALCU_HISTOGRAM_SIZE-1の範囲
	となる */
	l_pos = (long)(d_ratio*(CALCU_HISTOGRAM_SIZE-1.0+0.999999));

	++ this->la1000[l_pos];
	if (this->l_max < this->la1000[l_pos]) {
		this->l_max = this->la1000[l_pos];
	}
}

/*--------------------------------------------------------*/

void calcu_histogram_hab::init( long l_w, long l_h )
{
	this->l_add_pixel_w = l_w;
	this->l_add_pixel_h = l_h;
	this->l_hh_count = 0L;
	this->l_aa_count = 0L;
	this->l_bb_count = 0L;

	this->cl_hh.init();
	this->cl_aa.init();
	this->cl_bb.init();
}

void calcu_histogram_hab::add( bool gray_sw ,double d_hh, double d_aa, double d_bb )
{
	switch (this->e_hab_is) {
	case E_HAB_FREE:
		if (!gray_sw) {/* 色味がある時のみ色相histogramに追加する */
		 this->cl_hh.add(d_hh / 360.0); ++ this->l_hh_count;
		}
		this->cl_aa.add(d_aa); ++ this->l_aa_count;
		this->cl_bb.add(d_bb); ++ this->l_bb_count;
		break;
	case E_HH:
		if (!gray_sw) {/* 色味がある時のみ色相histogramに追加する */
		 this->cl_hh.add(d_hh / 360.0); ++ this->l_hh_count;
		}
		if (this->d_hh_min < this->d_hh_max){	/* min<maxの時 */
		 if (gray_sw ||				/* 色味なし or */
		 (this->d_hh_min<=d_hh) && (d_hh<=this->d_hh_max) ) {
		 		/* 色味があってかつ min<hh<max */
		  this->cl_aa.add(d_aa); ++ this->l_aa_count;
		  this->cl_bb.add(d_bb); ++ this->l_bb_count;
		 }
		}
		else {					/* max<minの時 */
		 if (gray_sw ||				/* 色味なし or */
		 (d_hh<=this->d_hh_max) || (this->d_hh_min<=d_hh) ) {
		 		/* 色味があってかつ hh<max||min<hh */
		  this->cl_aa.add(d_aa); ++ this->l_aa_count;
		  this->cl_bb.add(d_bb); ++ this->l_bb_count;
		 }
		}
		break;
	case E_AA:
		this->cl_aa.add(d_aa); ++ this->l_aa_count;
		if ( (this->d_aa_min<=d_aa) && (d_aa<=this->d_aa_max) ) {
		 if (!gray_sw){/* 色味がある時のみ色相histogramに追加する */
		  this->cl_hh.add(d_hh / 360.0); ++ this->l_hh_count;
		 }
		 this->cl_bb.add(d_bb); ++ this->l_bb_count;
		}
		break;
	case E_BB:
		this->cl_bb.add(d_bb); ++ this->l_bb_count;
		if ((this->d_bb_min<=d_bb)&&(d_bb<=this->d_bb_max)){
		 if (!gray_sw){/* 色味がある時のみ色相histogramに追加する */
		  this->cl_hh.add(d_hh / 360.0); ++ this->l_hh_count;
		 }
		 this->cl_aa.add(d_aa); ++ this->l_aa_count;
		}
		break;
	}
}
