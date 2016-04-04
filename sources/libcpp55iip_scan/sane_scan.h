# ifndef SANE_SCAN_H
#  define SANE_SCAN_H

#include "iip_canvas.h"
#include <sane/sane.h>
#include <sane/saneopts.h>

typedef enum {
	E_PIXELTYPE_BW = 1,
	E_PIXELTYPE_GRAYSCALE,
	E_PIXELTYPE_RGB
} E_PIXELTYPE;

typedef struct {
    int num;
    const SANE_Option_Descriptor *desc;
} ScannerOption;

typedef struct {
    ScannerOption tl_x;
    ScannerOption tl_y;
    ScannerOption br_x;
    ScannerOption br_y;
    ScannerOption resolution;
    ScannerOption x_resolution;
    ScannerOption y_resolution;
    ScannerOption mode;
} ScannerOptionsInfo;

class iip_scan {
public:
	iip_scan()
	{
		this->_i_mv_sw = OFF;
		this->_i_pv_sw = OFF;
		this->_i_cv_sw = OFF;

		/* capture area and resolution */
		this->_i_units_centimeters_sw = OFF; /* OFF is inches */
		this->_d_left = 0.0;
		this->_d_right = 0.0;
		this->_d_bottom = 0.0;
		this->_d_top = 0.0;
		this->_d_x_resolution = 72.0;
		this->_d_y_resolution = 72.0;

		/* grayscale */
		this->_e_pixeltype = E_PIXELTYPE_BW;
		this->_d_threshold = 128.0; /* 0 ... 255 */

		this->_d_brightness = 0.0;
		this->_d_contrast = 0.0;
		this->_d_gamma = 2.2;

		/* 取り込み動作に関する */
		this->_i_twain_gui_sw = OFF;
		this->_i_indicators_sw = ON;  /* GUI OFF時のPROGRESS*/
		this->_i_xfermech_memory_sw = OFF; /* OFF is native */

		/* scanner information from SANE */
        this->sane_handle = NULL;
		this->_d_x_native_resolution = 0.0;
		this->_d_y_native_resolution = 0.0;
		this->_d_physical_width = 0.0;
		this->_d_physical_height = 0.0;
        this->_device_name = NULL;

		this->_cl_iip_canvas.set_ccp_object_name_of_mv(
			"iip_scan"
		);
	}

	/*
	 * same "tw_win_l1_dsm.h" public method
	 */

	void set_i_mv_sw( int sw ) {      this->_i_mv_sw = sw; }
	int  get_i_mv_sw( void ) { return this->_i_mv_sw; }
	void set_i_pv_sw( int sw ) {      this->_i_pv_sw = sw; }
	int  get_i_pv_sw( void ) { return this->_i_pv_sw; }
	void set_i_cv_sw( int sw ) {      this->_i_cv_sw = sw; }
	int  get_i_cv_sw( void ) { return this->_i_cv_sw; }

	// void set_hw_parent( HWND hw ) { this->_hw_parent = hw; }

	/*
	 * same "tw_win_l4_scan.h" public method
	 */

	/* capture area and resolution */
	int  i_centimeters_sw( void ) { return this->_i_units_centimeters_sw; }
	void i_centimeters_sw( int sw )	{ this->_i_units_centimeters_sw = sw; }
	double d_left( void ) { return this->_d_left; }
	void   d_left( double dd ) {   this->_d_left = dd; }
	double d_right( void ) { return this->_d_right; }
	void   d_right( double dd ) {   this->_d_right = dd; }
	double d_bottom( void ) { return this->_d_bottom; }
	void   d_bottom( double dd ) {   this->_d_bottom = dd; }
	double d_top( void ) { return this->_d_top; }
	void   d_top( double dd ) {   this->_d_top = dd; }
	double d_x_resolution( void ) { return this->_d_x_resolution; }
	void   d_x_resolution(double res);
	double d_y_resolution( void ) { return this->_d_y_resolution; }
	void   d_y_resolution(double res);

	/* grayscale */
	E_PIXELTYPE  e_pixeltype( void ) { return this->_e_pixeltype;}
	void e_pixeltype( E_PIXELTYPE tt ) { this->_e_pixeltype = tt;}
	double d_threshold( void ) { return this->_d_threshold; }
	void   d_threshold( double dd ) {   this->_d_threshold = dd; }

	double d_brightness( void ) { return this->_d_brightness; }
	void   d_brightness( double dd ) {   this->_d_brightness = dd; }
	double d_contrast( void ) { return this->_d_contrast; }
	void   d_contrast( double dd ) {   this->_d_contrast = dd; }
	double d_gamma( void ) { return this->_d_gamma; }
	void   d_gamma( double dd ) {   this->_d_gamma = dd; }

	/* 取り込み動作に関する */
	int  i_twain_gui_sw( void )
	{ return this->_i_twain_gui_sw; }
	void i_twain_gui_sw( int sw )
	{        this->_i_twain_gui_sw = sw;}
	int  i_indicators_sw( void )
	{ return this->_i_indicators_sw; }
	void i_indicators_sw( int sw )
	{        this->_i_indicators_sw = sw;}
	int  i_xfer_memory_sw( void )
	{ return this->_i_xfermech_memory_sw;}
	void i_xfer_memory_sw( int sw )
	{        this->_i_xfermech_memory_sw = sw;}

    /* scanner information from SANE */
	double d_x_native_resolution(void) {return this->_d_x_native_resolution;}
	double d_y_native_resolution(void) {return this->_d_y_native_resolution;}
	double d_physical_width(void) {return this->_d_physical_width;}
	double d_physical_height(void) {return this->_d_physical_height;}
    char* device_name(void) {return this->_device_name;}
    void device_name(char *s);

	/* access to the scanner */
	int open(void);
    int device_search(void);
	int setup_unit(void);
    void option_get_info();
    void* option_get_value(ScannerOption *option);
    void option_set_value(ScannerOption *option, void *value);
	int get_physical_param(void);
    double gts_coord_to_sane(double x, double res);
	int setup_action(void);
	int print_all(void);
    void adjust_resolution(ScannerOption *option, double *res);
	int read(void);
	int close(void);
	const char *get_cp_machine_type(void) { return this->_device_name; }

	/* captured image */
	iip_canvas *get_clp_canvas( void ) { return &(this->_cl_iip_canvas); }


private:
    /* verbose output */
	int	_i_mv_sw, // print method
		_i_pv_sw, // print parameter
		_i_cv_sw; // print countdown

    /* capture area and resolution */
	int	_i_units_centimeters_sw; /* OFF is inches */
	double	_d_left,
		_d_right,
		_d_bottom,
		_d_top;
	double	_d_x_resolution,
		_d_y_resolution;

    /* grayscale */
	E_PIXELTYPE _e_pixeltype;
	double	_d_threshold;         /* 0 ... 255 */

	double	_d_brightness,
		_d_contrast,
		_d_gamma;

	/* 取り込み動作に関する */
	int	_i_twain_gui_sw,
		_i_indicators_sw, /* def. indicators_on_when_gui_off */
		_i_xfermech_memory_sw;  /* def. xfermech_native */

    /* scanner information from SANE */
    SANE_Handle sane_handle;
	double	_d_x_native_resolution,
		_d_y_native_resolution,
		_d_physical_width,
		_d_physical_height;
    char *_device_name;
    SANE_Unit _coordinate_unit;
    ScannerOptionsInfo _option_info;

	/* captured image */
	iip_canvas	_cl_iip_canvas;

};

# endif /*SANE_SCAN_H*/

