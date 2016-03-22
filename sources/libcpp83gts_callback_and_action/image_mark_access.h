#ifndef __image_mark_access_h__
#define __image_mark_access_h__

class image_mark_access {
public:
	void append_fnum_list_with_chk_mark( int i_file_num );
	void make_fnum_list_with_chk_mark( int i_start, int i_end );
	char *get_cp_mark_with_checked( int i_file_num );
private:
	int _get_file_header_from_path( char *cp_file, iip_read *clp_read );
	int _get_file_header_from_num( int i_num, iip_read *clp_read );
	int _get_rgbscan_header_from_num( int i_num, iip_read *clp_read );
};

#endif /* !__image_mark_access_h__ */
