#ifndef __tw_win_l2_dss_h__
#define __tw_win_l2_dss_h__

#include "tw_win_l1_dsm.h"

/* Data Source Setup */
class tw_win_l2_dss : public tw_win_l1_dsm {
protected:
	int cap_get_dp_x_native_resolution( double *dp_x_native_res );
	int cap_get_dp_y_native_resolution( double *dp_y_native_res );
	int cap_get_dp_physical_width( double *dp_width );
	int cap_get_dp_physical_height( double *dp_height );
	int cap_get_lp_uicontrollable_sw( long *lp_bool );
	int cap_getcrnt_lp_xfermech( long *lp_xfermech );
	int imageinfo_get_dp_reso( double *dp_dpi_x, double *dp_dpi_y );

	int cap_pri_brightness( void );
	int cap_pri_contrast( void );
	int cap_pri_gamma( void );
	int cap_pri_xresolution( void );
	int cap_pri_yresolution( void );

	int cap_pri_indicators( void );
	int cap_pri_units( void );
	int cap_pri_xfermech( void );
	int cap_pri_pixeltype( void );
	int cap_pri_bitdepth( void );
	int cap_pri_orientation( void );
	int cap_pri_threshold( void );
	int imageinfo_pri_all( void );
	int imagelayout_pri_all( void );
	int setupmemxfer_pri_all( void );

	int cap_set_d_brightness( double d_brightness );
	int cap_set_d_contrast( double d_contrast );
	int cap_set_d_gamma( double d_gamma );
	int cap_set_d_x_resolution( double d_x_reso );
	int cap_set_d_y_resolution( double d_y_reso );

	int cap_set_indicators_off_when_gui_off( void );
	int cap_set_indicators_on_when_gui_off( void );
	int cap_set_units_centimeters( void );
	int cap_set_units_inchs( void );
	int cap_set_xfermech_memory( void );
	int cap_set_xfermech_native( void );
	int cap_set_pixeltype_bw( void );
	int cap_set_pixeltype_gray( void );
	int cap_set_pixeltype_rgb( void );
	int cap_set_d_threshold( double d_threshold );
	int cap_set_i_bitdepth( int i_bitdepth );
	int cap_set_i_orientation( int i_orientation );

	int imagelayout_set_d_area( double d_lef, double d_rig, double d_bot, double d_top );

private:
	void _double_to_fix32(double d_val, TW_FIX32 *p_tw_fix32);
	void _fix32_to_double(TW_FIX32 *p_tw_fix32, double *dp_val);

	int _cap_get_ctnr( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability );
	int _cap_getcrnt_ctnr( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability );

	int _cap_get_ctnr_onevalue( TW_UINT16 ui16_cap, TW_ONEVALUE *p_tw_onevalue );
	int _cap_getcrnt_ctnr_onevalue( TW_UINT16 ui16_cap, TW_ONEVALUE *p_tw_onevalue );
	int _cap_get_ctnr_onevalue_bool( TW_UINT32 *ui32p_val, TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_get_ctnr_onevalue_fix32( double *dp_val, TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_getcrnt_ctnr_onevalue_ui16( TW_UINT16 *ui16p_val, TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_get_ctnr_range( TW_UINT16 ui16_cap, TW_RANGE *p_tw_range );
	int _cap_get_ctnr_enum_ui16_not_free( TW_UINT16 ui16_cap, TW_CAPABILITY *p_tw_capability, TW_ENUMERATION **pp_tw_enumration );

	int _cap_pri_ctnr_enum_ui16( TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_pri_ctnr_onevalue_bool( TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_pri_ctnr_onevalue_fix32( TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_pri_ctnr_range( TW_UINT16 ui16_cap, char *cp_cap_name );

	int _cap_set_ctnr( TW_CAPABILITY *p_tw_capability );
	int _cap_set_ctnr_onevalue( TW_UINT16 ui16_icap, TW_ONEVALUE tw_onevalue );
	int _cap_set_ctnr_onevalue_bool( TW_BOOL bo_val, TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_set_ctnr_onevalue_fix32( double d_val, TW_UINT16 ui16_cap, char *cp_cap_name );
	int _cap_set_ctnr_onevalue_ui16( TW_UINT16 ui16_val, TW_UINT16 ui16_cap, char *cp_cap_name );

	int _cap_set_indicators( TW_BOOL bo_val );
	int _cap_set_units( TW_UINT16 ui16_units );
	int _cap_set_xfermech( TW_UINT16 ui16_xfermech );
	int _cap_set_pixeltype( TW_UINT16 ui16_pixeltype );

	int _imageinfo_get( TW_IMAGEINFO *p_tw_imageinfo );
	void _imageinfo_pri( TW_IMAGEINFO *p_tw_imageinfo );

	int _imagelayout_get( TW_IMAGELAYOUT *p_tw_imagelayout );
	void _imagelayout_pri(TW_IMAGELAYOUT *p_tw_imagelayout);
	int _imagelayout_set( TW_IMAGELAYOUT *p_tw_imagelayout );

	int _setupmemxfer_get( TW_SETUPMEMXFER *p_tw_setupmemxfer );
	void _setupmemxfer_pri( TW_SETUPMEMXFER *p_tw_setupmemxfer );
};

#endif /* !__tw_win_l2_dss_h__ */
