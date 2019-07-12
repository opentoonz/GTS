#ifndef cb_area_and_rot90_h
#define cb_area_and_rot90_h

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Widget.H>
#include "iip_opengl_l1edit.h" // E_SELECT_PART

class cb_area_and_rot90 {
public:
	cb_area_and_rot90()
	:previous_choice_rot90_(-1)
	,dpi_when_cropped_(0.0)
	,dpi_before_change_(0.0)
	{}

	/*
		Initial/Reset
	*/
	void set_dpi_before_change( const double dpi ) {
		this->dpi_before_change_ = dpi; }
	void reset_dpi_to_zero_by_scan_or_preview(void) {
		this->dpi_when_cropped_ = 0.0; }

	/*
		Scan
	*/

	void cb_scan_full_area_and_crop( void );

	/*
		Area
	*/
	void cb_area_set_max( void );
	void cb_area_offset_cm_x( void );
	void cb_area_offset_cm_y( void );
	void cb_area_size_cm_w( void );
	void cb_area_size_cm_h( void );
	void cb_area_size_pixel_w( void );
	void cb_area_size_pixel_h( void );
	void cb_area_reso( void );

	void cb_dialog_set_aspect_ratio(
		Fl_Double_Window* flwin
		,Fl_Widget* flout
	);
	void cb_ok_aspect_ratio(void);

	/*
		Rot90
	*/

	enum enum_choice_rot90_type_value {
		 cw270_type_value	// 0 (-90)
		,cw000_type_value	// 1 (0)
		,cw090_type_value	// 2 (90)
		,cw180_type_value	// 3 (180)
	};

	/* Scanの場合のみ、数値(Offset、Size),画像,表示Area、を回転する */
	void cb_rotate_per_90_when_scan( void );

	/* Rot90を変更するときの元のRot90を保持する仕組み */
	void set_previous_choice_rot90( const int rot90 ) {
	   this->previous_choice_rot90_ = rot90;
	}

	/* 回転計算 pos(x2,y2),size(w2,h2) */
	void calc_rot90_offset_and_size(
		int choice_rot90
		, const double x , const double y
		, const double w , const double h
		, const double maxw , const double maxh
		, double *x2 , double *y2 , double *w2 , double *h2
	);

	/* 回転計算 size(w2,h2) */
	void calc_rot90_size(
		int choice_rot90
		, const double w , const double h , double *w2 , double *h2
	);

	/*
		変換
	*/

	void copy_opengl_to_value( const E_SELECT_PART sel_num );
	void copy_value_to_opengl( void );

	void getset_x_pixel_from_x_size( void );
	void getset_y_pixel_from_y_size( void );

private:
	int previous_choice_rot90_;
	double dpi_when_cropped_; /* 画像表示上のCropエリアはこの値で計算 */
	double dpi_before_change_;

	/*
		変換
	*/

	/* pixel単位をcm単位に変換 */
	double cm_from_pixel_( const double pixel , const double dpi );

	/* cm単位をpixel単位に変換 */
	double pixel_from_cm_( const double cm , const double dpi );

	/* cmサイズと対応するpixelサイズからdpiを得る */
	double dpi_from_cm_per_pixel_(const double cm ,const double pixel);

	void getset_x_size_from_x_pixel_( void );
	void getset_y_size_from_y_pixel_( void );

	const bool check_dpi_or_size_from_pixel_( void );

	void cb_valinp_area_aspect_ratio_w_( void );
	void cb_valinp_area_aspect_ratio_h_( void );
};

//--------------------

#include <FL/Fl.H>
#include <FL/Fl_Button.H>

class fltk_button_area_and_rot90 : public Fl_Button {
public:
	fltk_button_area_and_rot90(
	int x,int y,int w,int h,const char *l=0)
	: Fl_Button(x,y,w,h,l)
	{}
private:
	void draw();    
	int handle(int);
};

#endif /* !cb_area_and_rot90_h */
