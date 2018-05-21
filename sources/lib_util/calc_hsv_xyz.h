#ifndef calc_hsv_xyz_h
#define calc_hsv_xyz_h

namespace calc {

void hsv_to_xyz(
	const double h , const double s , const double v
	,double& x , double& y , double& z
);
void hsv_to_xyz( /* 関数オーバーロード */
	const double h , const double s , const double v
	,float& x , float& y , float& z
);

}
#endif /* !calc_hsv_xyz_h */
