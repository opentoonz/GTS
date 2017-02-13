#ifndef cb_area_and_rot90_h
#define cb_area_and_rot90_h

class cb_area_and_rot90 {
public:
	cb_area_and_rot90()
	:previous_choice_rot90_(-1)
	{}

	/*
		Rot90
	*/

	/* Scanの場合のみ、数値(Offset、Size),画像,表示Area、を回転する */
	void cb_rotate_per_90_when_scan( void );

	/* Rot90を変更するときの元のRot90を保持する仕組み */
	void set_previous_choice_rot90_( const int rot90 ) {
	   this->previous_choice_rot90_ = rot90;
	}

	/* 回転計算 pos(x2,y2),size(w2,h2) */
	template <class T> void calc_rot90_offset_and_size(
		int choice_rot90 , T x , T y , T w , T h , T maxw , T maxh
		, T *x2 , T *y2 , T *w2 , T *h2
	)
	{
		/* 回転差計算をしてマイナスの場合の値をプラスにする
		0	 #   0       degree clock works
		1 = -3+4 #  90(-270) degree clock works
		2 = -2+4 # 180(-180) degree clock works
		3 = -1+4 # 270( -90) degree clock works
		*/
		if (choice_rot90 < 0) { choice_rot90 += 4; }

		/* 左上原点で90degree単位回転計算 */
		switch (choice_rot90) {
		case 0: *x2=x;		*y2=y;          *w2=w; *h2=h; break;
		case 1: *x2=maxh-(y+h); *y2=x;          *w2=h; *h2=w; break;
		case 2: *x2=maxw-(x+w); *y2=maxh-(y+h); *w2=w; *h2=h; break;
		case 3: *x2=y;		*y2=maxw-(x+w); *w2=h; *h2=w; break;
		}
	}

	/* 回転計算 size(w2,h2) */
	void calc_rot90_size(
	 int choice_rot90 , double w , double h , double *w2 , double *h2
	);
private:
	int previous_choice_rot90_;

	/* 表示値を回転する */
	void rot90_about_area_GUI_values_( const int rot90_diff );
};

#endif /* !cb_area_and_rot90_h */
