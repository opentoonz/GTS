#ifndef cb_pixel_type_and_bright_h
#define cb_pixel_type_and_bright_h

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class cb_pixel_type_and_bright {
public:
	cb_pixel_type_and_bright()
	{}

	void cb_choice_pixel_type_title( const int number );
	void cb_choice_pixel_type_menu( void );

	const int get_bw_type_value(void) const {
   return this->bw_type_value_; }
	const int get_grayscale_type_value(void) const {
   return this->grayscale_type_value_; }
	const int get_rgb_type_value(void) const {
   return this->rgb_type_value_; }
private:
	enum choice_pixel_type_value_ {
		bw_type_value_		// 0
		,grayscale_type_value_	// 1
		,rgb_type_value_	// 2
	};
};

class fltk_button_pixel_type_and_bright : public Fl_Button {
public:
	fltk_button_pixel_type_and_bright(
	int x,int y,int w,int h,const char *l=0)
	: Fl_Button(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !cb_pixel_type_and_bright_h */
