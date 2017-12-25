#ifndef opengl_camera_eye_h
#define opengl_camera_eye_h

namespace opengl {

class camera_eye {
public:
	camera_eye();

	double get_eye_x() const { return this->eye_x_; }
	double get_eye_y() const { return this->eye_y_; }
	double get_eye_z() const { return this->eye_z_; }
	double get_cen_x() const { return this->cen_x_; }
	double get_cen_y() const { return this->cen_y_; }
	double get_cen_z() const { return this->cen_z_; }
	double get_upp_x() const { return this->upp_x_; }
	double get_upp_y() const { return this->upp_y_; }
	double get_upp_z() const { return this->upp_z_; }
	double get_fovy()  const { return this->fovy_; }
	double get_znear() const { return this->znear_; }
	double get_zfar()  const { return this->zfar_; }

	/* defaultに戻す */
	void reset_eye(void);

	/* カメラの視線vectorと頭上unitVectorから横方向unitVectorを得る */
	void camera_to_x_vector(
		double evx , double evy , double evz
		,const double uvx ,const double uvy ,const double uvz
		,double& vx ,double& vy ,double& vz
	);

	/* cen中心に回転 */
	void rotate( const double degree_x ,const double degree_y );

	/* カメラの上下左右移動 */
	void updownleftright( const double move_x ,const double move_y );

	/* カメラの前後移動 */
	void frontback( const double track_scale);

	/* cen中心に拡大縮小 */
	void scale_self( const double scale );
private:
	void set_full_range_about_near_far_(void);

	double	 eye_x_ ,eye_y_ ,eye_z_
		,cen_x_ ,cen_y_ ,cen_z_
		,upp_x_ ,upp_y_ ,upp_z_
		,fovy_  ,znear_ ,zfar_;
}; // class camera_eye

} // opengl

#endif /* !opengl_camera_eye_h */
