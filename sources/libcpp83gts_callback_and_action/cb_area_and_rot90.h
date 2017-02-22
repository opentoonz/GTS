#ifndef cb_area_and_rot90_h
#define cb_area_and_rot90_h

class cb_area_and_rot90 {
public:
	cb_area_and_rot90()
	:previous_choice_rot90_(-1)
	,dpi_when_cropped_(0.0)
	{}

	/*
		Scan
	*/

	void cb_scan_full_area_and_crop( void );

	/*
		Preset
	*/

	void cb_area_selecter( void );
	void cb_area_aspect_ratio_selecter( void );

	/*
		Area
	*/
	void cb_area_x_pos( void );
	void cb_area_y_pos( void );
	void cb_area_x_size( void );
	void cb_area_y_size( void );
	void cb_area_x_pixel_size( void );
	void cb_area_y_pixel_size( void );
	void cb_area_reso( void );

	/*
		Rot90
	*/

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

	void copy_opengl_to_value( void );
	void copy_value_to_opengl( void );

	void getset_x_pixel_from_x_size( void );
	void getset_y_pixel_from_y_size( void );

private:
	int previous_choice_rot90_;
	double dpi_when_cropped_; /* 画像表示上のCropエリアはこの値で計算 */

	/*
		変換
	*/

	/* pixel単位をcm単位に変換 */
	double cm_from_pixel_( const double pixel , const double dpi );

	/* cm単位をpixel単位に変換 */
	double pixel_from_cm_( const double cm , const double dpi );

	void getset_y_size_from_x_size_( void );
	void getset_x_size_from_y_size_( void );

	void getset_x_size_from_x_pixel_( void );
	void getset_y_size_from_y_pixel_( void );
};

#endif /* !cb_area_and_rot90_h */
