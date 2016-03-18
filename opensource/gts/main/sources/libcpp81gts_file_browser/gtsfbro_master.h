#ifndef __gts_master_h__
#define __gts_master_h__

#include "gtsfbro06cb_config.h"
#include "gtsfbro06cb_level.h"
#include "gtsfbro06cb_trace_batch.h"

class gts_master {
public:
	gts_master( void )
	{
		this->_i_mv_sw = OFF;
		this->_i_pv_sw = OFF;
		this->_i_cv_sw = OFF;

		this->_cp_application_name = NULL;
		this->_cp_application_release_date = NULL;
		this->_cp_application_release_number = NULL;
	}
	int  i_mv_sw( void ) const;
	void i_mv_sw( int sw );
	int  i_pv_sw( void ) const;
	void i_pv_sw( int sw );
	int  i_cv_sw( void ) const;
	void i_cv_sw( int sw );

	const char *cp_application_name( void ) const;
	void        cp_application_name( char *cp_name );
	const char *cp_application_release_date( void ) const;
	void        cp_application_release_date( char *cp_date );
	const char *cp_application_release_number( void ) const;
	void        cp_application_release_number( char *cp_num );

	/* fltkウインドウ表示、イベントループへ */
	int exec( void );

	/* クラスコンポーネント */
	gtsfbro06cb_config	cl_bro_config;
	gtsfbro06cb_level	cl_bro_level;
	gtsfbro06cb_trace_batch	cl_bro_trace_batch;

	// iip_read	cl_iip_read;	/* 画像読込み */

private:
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	char	*_cp_application_name;
	char	*_cp_application_release_date;
	char	*_cp_application_release_number;
};
extern gts_master cl_gts_master;

#endif /* !__gts_master_h__ */
