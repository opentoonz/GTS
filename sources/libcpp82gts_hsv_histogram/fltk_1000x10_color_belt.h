#ifndef fltk_1000x10_color_belt_h
#define fltk_1000x10_color_belt_h

#include <FL/Fl_Box.H>

class fltk_1000x10_color_belt : public Fl_Box {
public:
	fltk_1000x10_color_belt(int x,int y,int w,int h,const char *l=0);
	void set_right_color( const int r ,const int g ,const int b );
	void draw();

	int get_left_r(void) const { return this->left_r_; }
	int get_left_g(void) const { return this->left_g_; }
	int get_left_b(void) const { return this->left_b_; }
	int get_right_r(void) const { return this->right_r_; }
	int get_right_g(void) const { return this->right_g_; }
	int get_right_b(void) const { return this->right_b_; }
private:
	int	 left_r_  ,left_g_  ,left_b_
		,right_r_ ,right_g_ ,right_b_
	;
};

#endif /* !fltk_1000x10_color_belt_h */
