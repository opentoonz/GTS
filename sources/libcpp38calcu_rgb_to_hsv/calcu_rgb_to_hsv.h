#ifndef __calcu_rgb_to_hsv_h__
#define __calcu_rgb_to_hsv_h__

class calcu_rgb_to_hsv {
public:
	void to_hsv(double r, double g, double b, double *h, double *s, double *v);
	void from_hsv(double h, double s, double v, double *r, double *g, double *b);
private:
};

#endif /* !__calcu_rgb_to_hsv_h__ */
