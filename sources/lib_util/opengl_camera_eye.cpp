#include <cassert>	/* assert(-) */
#include <cmath>	/* sin(-) cos(-) sqrt(-) */
#include "calc_rad_deg.h"	/* calc::rad_from_deg() */
#include "opengl_camera_eye.h"

/*---------- opengl::camera_eye関数 ----------*/

namespace {
void rotate3d_vector_(
 const double x  ,const double y  ,const double z
,const double ox ,const double oy ,const double oz /* 回転の中心 */
,const double nx ,const double ny ,const double nz /* 回転の軸ベクトル */
,const double rad
,double& x2 ,double& y2 ,double& z2 )
{
	const double x_ = x - ox;
	const double y_ = y - oy;
	const double z_ = z - oz;
	const double cosrad = cos(rad);
	const double sinrad = sin(rad);
	const double one_minus_cosrad = 1. - cosrad;
	x2 =	  ( nx * nx * one_minus_cosrad +      cosrad ) * x_
		+ ( nx * ny * one_minus_cosrad - nz * sinrad ) * y_
		+ ( nz * nx * one_minus_cosrad + ny * sinrad ) * z_;
	y2 =	  ( nx * ny * one_minus_cosrad + nz * sinrad ) * x_
		+ ( ny * ny * one_minus_cosrad +      cosrad ) * y_
		+ ( ny * nz * one_minus_cosrad - nx * sinrad ) * z_;
	z2 =	  ( nz * nx * one_minus_cosrad - ny * sinrad ) * x_
		+ ( ny * nz * one_minus_cosrad + nx * sinrad ) * y_
		+ ( nz * nz * one_minus_cosrad +      cosrad ) * z_;
	x2 += ox;
	y2 += oy;
	z2 += oz;
}
void cross_product_( /* 外積 */
 const double vx1 ,const double vy1 ,const double vz1
,const double vx2 ,const double vy2 ,const double vz2
,double& vx ,double& vy ,double& vz
)
{
	vx = vy1*vz2 - vz1*vy2;
	vy = vz1*vx2 - vx1*vz2;
	vz = vx1*vy2 - vy1*vx2;
}
void vector_to_unit_( double& vx ,double& vy ,double& vz )
{
	const double len = sqrt( vx*vx + vy*vy + vz*vz );
	vx /= len;
	vy /= len;
	vz /= len;
}
} // namespace

namespace opengl {

camera_eye::camera_eye()
	:eye_x_(0.) ,eye_y_(0.) ,eye_z_(10.)
	,cen_x_(0.) ,cen_y_(0.) ,cen_z_(0.)
	,upp_x_(0.) ,upp_y_(1.) ,upp_z_(0.)
	,fovy_(30.) ,znear_(9.) ,zfar_(-11.)
{
	assert (0. < this->fovy_); /* ゼロ以下は致命的エラー */
	this->reset_eye();
}

void camera_eye::set_full_range_about_near_far_(void)
{
	double x = this->eye_x_ - this->cen_x_;
	double y = this->eye_y_ - this->cen_y_;
	double z = this->eye_z_ - this->cen_z_;
	const double len = sqrt( x * x + y * y + z * z );
	this->znear_ = len / 100.0;
	this->zfar_  = len * 2.0 - len / 100.0;
}

void camera_eye::reset_eye(void)
{
	/* 視点 注視点 の距離
	視野角がfovy_で、(0,0,0)を注視点としたとき、
	注視点を中心とした半径1の球全体がピッタリ入るような視点の位置 */
	const double zlen= 1. / sin( calc::rad_from_deg(this->fovy_) / 2. );

	/*	視点位置	(0,0,z)
		注視点位置	(0,0,0)
		頭上ベクトル	(0,1,0) */
	this->eye_x_ = 0.; this->eye_y_ = 0.; this->eye_z_ = zlen;// Pos.
	this->cen_x_ = 0.; this->cen_y_ = 0.; this->cen_z_ = 0.;  // Pos.
	this->upp_x_ = 0.; this->upp_y_ = 1.; this->upp_z_ = 0.;  // Vector

	/* z depth値再設定 */
	this->set_full_range_about_near_far_();
}

void camera_eye::camera_to_x_vector(
 double evx , double evy , double evz
,const double uvx ,const double uvy ,const double uvz
,double& vx ,double& vy ,double& vz
)
{
	/* 視線ベクトル単位化 */
	vector_to_unit_( evx ,evy ,evz );

	/* カメラ横方向ベクトル */
	cross_product_( uvx ,uvy ,uvz ,evx ,evy ,evz ,vx ,vy ,vz );

	/* カメラ横方向ベクトル単位化 */
	vector_to_unit_( vx ,vy ,vz );
}

void camera_eye::rotate( const double degree_x ,const double degree_y )
{
  if (degree_x != 0) {
	/* x方向マウス移動は視点をカメラ座標系y軸回転 */
	rotate3d_vector_(
	 this->eye_x_ ,this->eye_y_ ,this->eye_z_
	,this->cen_x_ ,this->cen_y_ ,this->cen_z_/* 回転の中心 */
	,this->upp_x_ ,this->upp_y_ ,this->upp_z_/* 回転軸ベクトル */
	, - calc::rad_from_deg(degree_x)
	, this->eye_x_ , this->eye_y_ , this->eye_z_
	);
  }
  if (degree_y != 0) {
	/* y方向マウス移動はx軸回転 */
	const double xr=calc::rad_from_deg(degree_y);

	/* カメラ横方向ベクトル */
	double lr_x = 0.;
	double lr_y = 0.;
	double lr_z = 0.;
	this->camera_to_x_vector(
		this->cen_x_ - this->eye_x_
		,this->cen_y_ - this->eye_y_
		,this->cen_z_ - this->eye_z_
		,this->upp_x_ ,this->upp_y_ ,this->upp_z_
		,lr_x ,lr_y ,lr_z
	);

	rotate3d_vector_(
		 this->eye_x_ , this->eye_y_ , this->eye_z_
		,this->cen_x_ , this->cen_y_ , this->cen_z_/* 回転の中心 */
		, lr_x , lr_y , lr_z /* 回転の軸ベクトル */
		, xr
		, this->eye_x_ , this->eye_y_ , this->eye_z_
	);
	rotate3d_vector_(
		 this->upp_x_ , this->upp_y_ , this->upp_z_
		,0. ,0. ,0./* 回転の中心 */
		, lr_x , lr_y , lr_z /* 回転の軸ベクトル */
		, xr
		, this->upp_x_ , this->upp_y_ , this->upp_z_
	);
	vector_to_unit_( this->upp_x_ ,this->upp_y_ ,this->upp_z_ );
  }
} 
void camera_eye::updownleftright(
	const double scale_camera_x ,const double scale_camera_y
)
{
	/* カメラ横方向ベクトル */
	double lr_x = 0.;
	double lr_y = 0.;
	double lr_z = 0.;
	this->camera_to_x_vector(
		this->cen_x_ - this->eye_x_
		,this->cen_y_ - this->eye_y_
		,this->cen_z_ - this->eye_z_
		,this->upp_x_ ,this->upp_y_ ,this->upp_z_
		,lr_x ,lr_y ,lr_z
	);

	this->eye_x_ += lr_x * scale_camera_x;
	this->eye_y_ += lr_y * scale_camera_x;
	this->eye_z_ += lr_z * scale_camera_x;
	this->cen_x_ += lr_x * scale_camera_x;
	this->cen_y_ += lr_y * scale_camera_x;
	this->cen_z_ += lr_z * scale_camera_x;

	this->eye_x_ += this->upp_x_ * scale_camera_y;
	this->eye_y_ += this->upp_y_ * scale_camera_y;
	this->eye_z_ += this->upp_z_ * scale_camera_y;
	this->cen_x_ += this->upp_x_ * scale_camera_y;
	this->cen_y_ += this->upp_y_ * scale_camera_y;
	this->cen_z_ += this->upp_z_ * scale_camera_y;
}

void camera_eye::frontback( const double scale_camera_z)
{
	/* 視線ベクトル */
	double fb_x = this->cen_x_ - this->eye_x_;
	double fb_y = this->cen_y_ - this->eye_y_;
	double fb_z = this->cen_z_ - this->eye_z_;
	vector_to_unit_( fb_x ,fb_y ,fb_z );

	/* 視線ベクトルでカメラ移動 */
	this->eye_x_ += fb_x * scale_camera_z;
	this->eye_y_ += fb_y * scale_camera_z;
	this->eye_z_ += fb_z * scale_camera_z;
	this->cen_x_ += fb_x * scale_camera_z;
	this->cen_y_ += fb_y * scale_camera_z;
	this->cen_z_ += fb_z * scale_camera_z;
}

void camera_eye::scale_self( const double scale )
{
	/* 注視点から視点へのベクトル */
	double vx = this->eye_x_ - this->cen_x_;
	double vy = this->eye_y_ - this->cen_y_;
	double vz = this->eye_z_ - this->cen_z_;

	/* 注視点を中心にして、ベクトルを拡大縮小 */
	vx *= scale;
	vy *= scale;
	vz *= scale;

	/* 拡大縮小したベクトルを元にした視点 */
	this->eye_x_ = vx + this->cen_x_;
	this->eye_y_ = vy + this->cen_y_;
	this->eye_z_ = vz + this->cen_z_;

	this->set_full_range_about_near_far_();
}

} // namespace opengl
