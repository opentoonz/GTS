#ifndef __fltk_1000_range_minmax_h__
#define __fltk_1000_range_minmax_h__

#include <FL/Fl_Box.H>

#ifndef _E_MIN_MAX_SELECT_TYPE_
#define _E_MIN_MAX_SELECT_TYPE_
typedef enum {
	E_NO_SELECT_TYPE,
	E_MIN_SELECT_TYPE,
	E_CENTER_SELECT_TYPE,
	E_MAX_SELECT_TYPE
} E_MIN_MAX_SELECT_TYPE;
#endif

class fltk_1000_range_minmax : public Fl_Box {
public:
	fltk_1000_range_minmax(int x,int y,int w,int h,const char *l=0);
	void draw();    

	void set_dd_minmax( double d_min, double d_max );
	void set_cp_title( char *cp_title );
	double get_d_x_min( void );
	double get_d_x_max( void );
	long get_l_x_min( void ) { return this->_l_x_min; }
	long get_l_x_max( void ) { return this->_l_x_max; }

protected:
	int _key_in(int key);
	void _mouse_push( int i_mouse_button, long l_mouse_x, long l_mouse_y);
	void _mouse_drag( long l_mouse_x, long l_mouse_y );
	void _mouse_release( int i_mouse_button );
private:
	long _l_x_min, _l_x_max;
	char *_cp_title;

	long _l_y_pos;
	long _l_x_min_backup;
	long _l_x_max_backup;
	long _l_minmax_radius;
	long _l_center_radius;

	E_MIN_MAX_SELECT_TYPE _e_select_type;
	long _l_x_drag_start;

	void _draw_minmax( long l_x, long l_y, char *cp_name );
	void _draw_center( long l_x, long l_y );
	int _select_minmax( long l_x_mouse, long l_y_mouse, long l_x_pos, long l_y_pos );
	int _select_center( long l_x_mouse, long l_y_mouse, long l_x_pos, long l_y_pos );
};

/*--------------------------------------------------------*/

class fltk_aa_minmax : public fltk_1000_range_minmax {
public:
	fltk_aa_minmax(int x,int y,int w,int h,const char *l=0) : fltk_1000_range_minmax(x,y,w,h,l) {};
	int handle(int);
};
class fltk_bb_minmax : public fltk_1000_range_minmax {
public:
	fltk_bb_minmax(int x,int y,int w,int h,const char *l=0) : fltk_1000_range_minmax(x,y,w,h,l) {};
	int handle(int);
};

#endif /* !__fltk_1000_range_minmax_h__ */
