#ifndef memory_scan_area_h
#define memory_scan_area_h

#include <vector>
#include <string>

struct preset_axywhr {
	preset_axywhr():x(0.0),y(0.0),w(0.0),h(0.0){}
	//std::string a; /* Area name -->GUI */
	double x,y,w,h;	/* Start x y , Size w h */
	std::string r; /* screen aspect Ratio name */
};

struct preset_rwh {
	preset_rwh():w(0.0),h(0.0){}
	// std::string r; /* screen aspect Ratio name -->GUI */
	double w,h; /* Screen w h */
};

class memory_scan_area {
public:
	std::vector<preset_axywhr> areas;
	std::vector<preset_rwh> aspect_ratios;
	int load( const char *comm );
};

#endif /* !memory_scan_area_h */
