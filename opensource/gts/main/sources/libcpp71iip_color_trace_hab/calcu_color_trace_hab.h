#ifndef __calcu_color_trace_hab_h__
#define __calcu_color_trace_hab_h__

#include "ptbl_returncode.h"

class calcu_col_area_hab {
public:
	calcu_col_area_hab()
	{
		this->i_exec_sw = OFF;
		this->d_hh_min = this->d_hh_max = 0.0;
		this->d_aa_min = this->d_aa_max = 0.0;
		this->d_bb_min = this->d_bb_max = 0.0;
		this->d_red = 0.0;
		this->d_gre = 0.0;
		this->d_blu = 0.0;
	}

	int	i_exec_sw;
	double	d_hh_min, d_hh_max,
		d_aa_min, d_aa_max,
		d_bb_min, d_bb_max;
	double	d_red,
		d_gre,
		d_blu;
};

/*-------------------------------------------------------*/

typedef enum {
	E_COLOR_TRACE_HAB_01=0,
	E_COLOR_TRACE_HAB_02,
	E_COLOR_TRACE_HAB_03,
	E_COLOR_TRACE_HAB_04,
	E_COLOR_TRACE_HAB_05,
	E_COLOR_TRACE_HAB_06,
	E_COLOR_TRACE_HAB_NOT_SELECT,
} E_COLOR_TRACE_HAB_COLORS;

class calcu_color_trace_hab {
public:
	calcu_color_trace_hab()
	{
		this->_d_bg_red = 1.0;
		this->_d_bg_gre = 1.0;
		this->_d_bg_blu = 1.0;
	}

	calcu_col_area_hab cla_area_param[E_COLOR_TRACE_HAB_NOT_SELECT];

	void exec( double d_hh, double d_aa, double d_bb, double *dp_red, double *dp_gre, double *dp_blu );
private:
	double	_d_bg_red,
		_d_bg_gre,
		_d_bg_blu;
};

#endif /* !__calcu_color_trace_hab_h__ */
