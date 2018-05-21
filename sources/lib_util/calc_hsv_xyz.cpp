#include <cmath>		// sin(-) cos(-)
#include "calc_rad_deg.h"	// calc::rad_from_deg(-)

namespace calc {

void hsv_to_xyz(
	const double h , const double s , const double v
	,double& x , double& y , double& z
)
{
	const double r = calc::rad_from_deg(h);
	x = cos( r ) * s * v;
	y = sin( r ) * s * v;
	z = 1. - v;
}
void hsv_to_xyz(
	const double h , const double s , const double v
	,float& x , float& y , float& z
)
{
	const double r = calc::rad_from_deg(h);
	x = static_cast<float>( cos( r ) * s * v );
	y = static_cast<float>( sin( r ) * s * v );
	z = static_cast<float>( 1. - v );
}

} // namespace calc
