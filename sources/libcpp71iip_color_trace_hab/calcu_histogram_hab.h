#ifndef __calcu_histogram_hab_h__
#define __calcu_histogram_hab_h__

#ifndef	CALCU_HISTOGRAM_SIZE
#define	CALCU_HISTOGRAM_SIZE 1000
#endif

class data_histogram_hab {
public:
	data_histogram_hab()
	{
		this->init();
	}

	void init( void );
	void add( double d_ratio );

	long l_max;
	long la1000[CALCU_HISTOGRAM_SIZE];
};

/*--------------------------------------------------------*/

typedef enum {
	E_HAB_FREE=1,
	E_HH,
	E_AA,
	E_BB,
} E_HAB_TYPE;

class calcu_histogram_hab {
public:
	calcu_histogram_hab()
	{
		this->init(0,0);

		this->e_hab_is = E_HH;

		this->d_hh_min = 0.0;
		this->d_hh_max = 360.0;
		this->d_aa_min = 0.0;
		this->d_aa_max = 0.0;
		this->d_bb_min = 0.0;
		this->d_bb_max = 0.0;
	}

	void init( long l_w, long l_h );
	void add( double d_hh, double d_aa, double d_bb );

	long l_add_pixel_w;
	long l_add_pixel_h;

	long l_hh_count;
	long l_aa_count;
	long l_bb_count;

	E_HAB_TYPE e_hab_is;
	double	d_hh_min,d_hh_max,
		d_aa_min,d_aa_max,
		d_bb_min,d_bb_max;

	data_histogram_hab
		cl_hh,
		cl_aa,
		cl_bb;
};

#endif /* !__calcu_histogram_hab_h__ */
