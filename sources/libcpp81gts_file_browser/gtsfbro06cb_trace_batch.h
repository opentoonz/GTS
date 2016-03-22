#ifndef __gtsfbro06cb_trace_batch_h__
#define __gtsfbro06cb_trace_batch_h__

#include "gtsfbro05list_trace_batch.h"

class gtsfbro06cb_trace_batch : public gtsfbro05list_trace_batch {
public:
	int i_init( void );

	void cb_dir( void );
	void cb_dir_up( void );
	void cb_list( void );
	void cb_run( void );
	void cb_cancel( void );
	void cb_close( void );
	void cb_wintgl( void );
	void cb_add( void );
	void cb_alladd( void );
protected:
private:
	void _cancel( void );
	int _mark_or_add_from_list( int i_selected );
	void _trace_a_level( char *cp_path );
};

#endif /* !__gtsfbro06cb_trace_batch_h__ */
