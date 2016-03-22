#ifndef __iip_erase_dot_noise_h__
#define __iip_erase_dot_noise_h__

#include "iip_canvas.h"

class iip_erase_dot_noise : public iip_canvas {
public:
	iip_erase_dot_noise()
	{
		this->set_ccp_object_name_of_mv("iip_erase_dot_noise");
		this->_l_area_xpos = 0L;
		this->_l_area_ypos = 0L;
		this->_l_area_xsize = 0L;
		this->_l_area_ysize = 0L;
	}

	void set_l_area_xpos( long ll ) { this->_l_area_xpos = ll; }
	void set_l_area_ypos( long ll ) { this->_l_area_ypos = ll; }
	void set_l_area_xsize( long ll ) { this->_l_area_xsize = ll; }
	void set_l_area_ysize( long ll ) { this->_l_area_ysize = ll; }
	long get_l_area_xpos( void ) { return this->_l_area_xpos; }
	long get_l_area_ypos( void ) { return this->_l_area_ypos; }
	long get_l_area_xsize( void ) { return this->_l_area_xsize; }
	long get_l_area_ysize( void ) { return this->_l_area_ysize; }

	void exec( void );
private:
	long	_l_area_xpos,
		_l_area_ypos,
		_l_area_xsize,
		_l_area_ysize;

	void _exec_uchar( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned char *ucharp_in, unsigned char *ucharp_out );
};

#endif /* !__iip_erase_dot_noise_h__ */
