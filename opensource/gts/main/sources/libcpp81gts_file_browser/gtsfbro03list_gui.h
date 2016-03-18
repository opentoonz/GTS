#ifndef __gtsfbro03list_gui_h__
#define __gtsfbro03list_gui_h__

#include <FL/Fl_Browser.H>
#include "gtsfbro02list_base.h"

class gtsfbro03list_gui : public gtsfbro02list_base {
public:
protected:
	void remove_gui_list( Fl_Browser *flp_selbro );
	void draw_gui_list( Fl_Browser *flp_selbro );
private:
};

#endif /* !__gtsfbro03list_gui_h__ */
