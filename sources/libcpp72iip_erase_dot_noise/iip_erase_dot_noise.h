#ifndef __iip_erase_dot_noise_h__
#define __iip_erase_dot_noise_h__

#include "iip_canvas.h"

class iip_erase_dot_noise : public iip_canvas {
public:
	iip_erase_dot_noise()
	{
		this->set_ccp_object_name_of_mv("iip_erase_dot_noise");
		this->area_xpos_ = 0L;
		this->area_ypos_ = 0L;
		this->area_xsize_ = 0L;
		this->area_ysize_ = 0L;
	}

	void set_area_xpos( int ll ) { this->area_xpos_ = ll; }
	void set_area_ypos( int ll ) { this->area_ypos_ = ll; }
	void set_area_xsize( int ll ) { this->area_xsize_ = ll; }
	void set_area_ysize( int ll ) { this->area_ysize_ = ll; }
	/*long get_l_area_xpos( void ) { return this->area_xpos_; }
	long get_l_area_ypos( void ) { return this->area_ypos_; }
	long get_l_area_xsize( void ) { return this->area_xsize_; }
	long get_l_area_ysize( void ) { return this->area_ysize_; }*/

	void exec( void );
private:
	int	area_xpos_,
		area_ypos_,
		area_xsize_,
		area_ysize_;

	void _exec_uchar( long l_width, long l_height, long l_area_xpos, long l_area_ypos, long l_area_xsize, long l_area_ysize, long l_channels, unsigned char *ucharp_in, unsigned char *ucharp_out );
};

#endif /* !__iip_erase_dot_noise_h__ */
