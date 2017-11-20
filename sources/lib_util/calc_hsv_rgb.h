#ifndef calc_hsv_rgb_h
#define calc_hsv_rgb_h

namespace calc {
	/* 〜-1〜0〜359.999...〜 --> 0〜359.999... */
	double clamp_cyclic360( double h360 );

	/*
	*** In  ***
	h	色相(Hue)	0.0〜359.999...
	s	彩度(Saturation)0.0〜1.0
	v	明度(Value)	0.0〜1.0
	*** Out ***
	r	赤(Red)		0.0...1.0
	g	緑(Green)	0.0...1.0
	b	青(Blue)	0.0...1.0
	*/
	void hsv_to_rgb(
		const double h, const double s, const double v
		, double& r, double& g, double& b
	);

	/*
	*** In  ***
	r	赤(Red)		0.0...1.0
	g	緑(Green)	0.0...1.0
	b	青(Blue)	0.0...1.0
	*** Out ***
	h6	色相(Hue)	0.0〜359.999...
	s	彩度(Saturation)0.0〜1.0
	v	明度(Value)	0.0〜1.0
	*/
	void rgb_to_hsv(
		const double r, const double g, const double b
		, double& h, double& s, double& v
	);
}
#endif /* !calc_hsv_rgb_h */
