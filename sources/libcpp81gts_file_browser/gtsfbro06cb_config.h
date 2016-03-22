#ifndef __gtsfbro06cb_config_h__
#define __gtsfbro06cb_config_h__

#include "gtsfbro05list_config.h"

class gtsfbro06cb_config : public gtsfbro05list_config {
public:
	gtsfbro06cb_config()
	{
		this->_ca_save_as_filename_memory[0] = '\0';
	}
	int i_init( void );

	void cb_load_dir( void );
	void cb_load_dir_up( void );
	void cb_load_list( void );
	void cb_load_ok( void );
	void cb_load_cancel( void );
	void cb_load_wintgl( void );

	void cb_save_as_dir( void );
	void cb_save_as_dir_up( void );
	void cb_save_as_list( void );
	void cb_save_as_ok( void );
	void cb_save_as_cancel( void );
	void cb_save_as_wintgl( void );

	void cb_save_as_file( void ); // add 2013-10-04
protected:
private:
	void _load_cancel( void );
	void _save_as_cancel( void );
	void _save_as_filename_memory( const char *ccp_fname );

	char _ca_save_as_filename_memory[PTBL_PATH_MAX];
};

#endif /* !__gtsfbro06cb_config_h__ */
