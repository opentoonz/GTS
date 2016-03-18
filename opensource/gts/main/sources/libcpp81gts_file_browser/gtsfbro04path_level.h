#ifndef __gtsfbro04path_level_h__
#define __gtsfbro04path_level_h__

#include "gtsfbro03list_gui.h"

class gtsfbro04path_level : public gtsfbro03list_gui {
public:
protected:
	int i_lpath_cat_file_by_num(
	 const char *ccp_file, int i_num, int i_file_head_cut_sw=OFF );

	int i_lpath_cat_file_for_full(
	 const char *ccp_file, int i_num, int i_file_head_cut_sw=OFF );

	int i_lpath_cpy_head_means_level(
	 const char *ccp_file, int i_file_head_cut_sw=OFF );
private:
};

#endif /* !__gtsfbro04path_level_h__ */
