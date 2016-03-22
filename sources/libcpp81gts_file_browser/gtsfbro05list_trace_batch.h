#ifndef __gtsfbro05list_trace_batch_h__
#define __gtsfbro05list_trace_batch_h__

#include <FL/Fl_Text_Buffer.H>
#include "gtsfbro04text_gui.h"

class gtsfbro05list_trace_batch : public gtsfbro04text_gui {
public:
	gtsfbro05list_trace_batch()
	{
	}
	~gtsfbro05list_trace_batch()
	{
		this->_end();
	}
	int init_trace_batch_dir( const char *ccp_dir );

protected:
	void init_text_buffer( void );
	int change_trace_batch_list( void );
	void change_trace_batch_dir( const char *ccp_dir = NULL );
	int view_text( void );
	int get_i_1st_selected( void );
private:
	Fl_Text_Buffer	_cl_fl_text_buffer;


	void _end( void );
};

#endif /* !__gtsfbro05list_trace_batch_h__ */
