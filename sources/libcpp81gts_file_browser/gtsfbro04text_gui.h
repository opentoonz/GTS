#ifndef __gtsfbro04text_gui_h__
#define __gtsfbro04text_gui_h__

#include <FL/Fl_Text_Buffer.H>
#include "gtsfbro03list_gui.h"

class gtsfbro04text_gui : public gtsfbro03list_gui {
public:
protected:
	int view_gui_text( Fl_Text_Buffer *flp_text_buf );
private:
};

#endif /* !__gtsfbro04text_gui_h__ */
