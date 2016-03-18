#ifndef __calcu_erase_dot_noise_h__
#define __calcu_erase_dot_noise_h__

class calcu_erase_dot_noise {
public:
	unsigned char *get_ucharp(
		unsigned char *ucharp11,
		unsigned char *ucharp12,
		unsigned char *ucharp13,
		unsigned char *ucharp21,
		unsigned char *ucharp22,
		unsigned char *ucharp23,
		unsigned char *ucharp31,
		unsigned char *ucharp32,
		unsigned char *ucharp33
	);
private:
	void _setup_ip_equal(
		unsigned char *ucharp11,
		unsigned char *ucharp12,
		unsigned char *ucharp13,
		unsigned char *ucharp21,
		unsigned char *ucharp22,
		unsigned char *ucharp23,
		unsigned char *ucharp31,
		unsigned char *ucharp32,
		unsigned char *ucharp33,
		int	ip_equal[]
	);
	void _setup_ip_ucharp_histo(
		unsigned char *ucharp11,
		unsigned char *ucharp12,
		unsigned char *ucharp13,
		unsigned char *ucharp21,
		unsigned char *ucharp22,
		unsigned char *ucharp23,
		unsigned char *ucharp31,
		unsigned char *ucharp32,
		unsigned char *ucharp33,
		int	ip_equal[],
		int	ip_histo[],
		unsigned char *ucharpa_histo[]
	);
	int _is_whiteblack(
		int	ip_histo[],
		unsigned char *ucharpa_histo[],
		unsigned char *ucharp22
	);
	unsigned char *_get_ucharp_many_color(
		int	ip_equal[],
		int	ip_histo[],
		unsigned char *ucharpa_histo[]
	);
};

#endif /* !__calcu_erase_dot_noise_h__ */
