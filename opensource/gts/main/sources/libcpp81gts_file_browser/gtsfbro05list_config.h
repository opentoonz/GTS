#ifndef __gtsfbro05list_config_h__
#define __gtsfbro05list_config_h__

#include <FL/Fl_Text_Buffer.H>
#include "gtsfbro04text_gui.h"

class gtsfbro05list_config : public gtsfbro04text_gui {
public:
	gtsfbro05list_config()
	{
	}
	~gtsfbro05list_config()
	{
		this->_end();
	}
	int init_config_dir( const char *ccp_dir );

protected:
	void init_text_buffer( void );
	int view_text_for_load( void );
	int view_text_for_save_as( void );

	int change_config_list( void );
	void change_config_dir( const char *ccp_dir = NULL );
private:
	Fl_Text_Buffer	_cl_fl_text_buffer_load,
			_cl_fl_text_buffer_save_as;

	void _end( void );
};

#endif /* !__gtsfbro05list_config_h__ */
