#ifndef __name_strings_h__
#define __name_strings_h__

#include <stdio.h> /* NULL */

class name_strings {
public:
	name_strings(void) { this->_cp_name = NULL; }
	~name_strings(void) { this->_mem_free(); }

	int set_name( char *cp_name );
	char *get_cp_name( void ) { return this->_cp_name; }
private:
	char *_cp_name; 
	void _mem_free( void );
};

#endif /* !__name_strings_h__ */
