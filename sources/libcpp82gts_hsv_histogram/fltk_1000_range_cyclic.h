#ifndef __fltk_1000_range_cyclic_h__
#define __fltk_1000_range_cyclic_h__

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

class fltk_1000_range_cyclic : public Fl_Box {
public:
	fltk_1000_range_cyclic(int x,int y,int w,int h,const char *l=0);
	void draw();    

	void set_dd_minmax( double d_x_min, double d_x_max );
	void set_cp_title( char *cp_title );
	double get_d360_x_min( void );
	double get_d360_x_max( void );
	long get_l_x_min( void ) { return this->_l_x_min; }
	long get_l_x_max( void ) { return this->_l_x_max; }
protected:
	void _mouse_push( int i_mouse_button, long l_mouse_x, long l_mouse_y);
	void _mouse_drag( long l_mouse_x );
	void _mouse_release( int i_mouse_button );
	int _key_in(int key);
private:
	long _l_x_min, _l_x_max;
	char *_cp_title;

	long _l_x_min_at_push;
	long _l_x_max_at_push;

	long _l_x_min_at_drag;
	long _l_x_max_at_drag;

	long _l_x_min2, _l_x_max2;
	long _l_x_center, _l_x_center2;

	long _l_y_pos;
	long _l_term_radius;
	long _l_center_radius;

	E_MIN_MAX_SELECT_TYPE _e_select_type;
	long _l_x_drag_start;

	void _draw_term_mark( long l_x, long l_y, char *cp_name );
	void _draw_cent_mark( long l_x, long l_y );
	void _draw_all_mark( void );

	int _select_mark( long l_x_pos, long l_y_pos, long l_radius, long l_x_cursor, long l_y_cursor );
	void _select( long l_x, long l_y );

	void _set_min_center_max( long l_x_min, long l_x_max );
};

/*--------------------------------------------------------*/

class fltk_hh_cyclic : public fltk_1000_range_cyclic {
public:
	fltk_hh_cyclic(int x,int y,int w,int h,const char *l=0) : fltk_1000_range_cyclic(x,y,w,h,l) {};
	int handle(int);
};

#endif /* !__fltk_1000_range_cyclic_h__ */
