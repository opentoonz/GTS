#ifndef cb_color_trace_thickness_h
#define cb_color_trace_thickness_h

#include "calcu_color_trace_hab.h"

class cb_color_trace_thickness {
public:
	cb_color_trace_thickness()
	{
	}
	void init( void );
	void cb_preset_01( const int choice );
	void cb_preset_02( const int choice );
	void cb_preset_03( const int choice );
	void cb_preset_04( const int choice );

	void cb_src_01( void );
	void cb_src_02( void );
	void cb_src_03( void );
	void cb_src_04( void );

	void cb_scrbar_01( const double value );
	void cb_scrbar_02( const double value );
	void cb_scrbar_03( const double value );
	void cb_scrbar_04( const double value );

	void cb_valinp_01( const double value );
	void cb_valinp_02( const double value );
	void cb_valinp_03( const double value );
	void cb_valinp_04( const double value );

	//-------------------------------------

	void cb_enh_01( void );
	void cb_enh_02( void );
	void cb_enh_03( void );
	void cb_enh_04( void );

	void set_scrbar_inpval( E_COLOR_TRACE_HAB_COLORS col_tra_num );

private:
	// BL
	double src_bl_hmin_=  0.;
	double src_bl_hmax_=360.;
	double src_bl_smin_=  0.;
	double src_bl_smax_=100.;
	double src_bl_vmin_=  0.;
	double src_bl_vmax_= 50.;
	const int tgt_bl_red_ =  0;
	const int tgt_bl_gre_ =  0;
	const int tgt_bl_blu_ =  0;

	// R
	double src_r_hmin_=300.;
	double src_r_hmax_= 60.;
	double src_r_smin_= 50.;
	double src_r_smax_=100.;
	double src_r_vmin_=  0.;
	double src_r_vmax_=100.;
	const int tgt_r_red_ =0xff;
	const int tgt_r_gre_ =  0;
	const int tgt_r_blu_ =  0;

	// G
	double src_g_hmin_= 60.;
	double src_g_hmax_=180.;
	double src_g_smin_= 50.;
	double src_g_smax_=100.;
	double src_g_vmin_=  0.;
	double src_g_vmax_=100.;
	const int tgt_g_red_ =  0;
	const int tgt_g_gre_ =0xff;
	const int tgt_g_blu_ =  0;

	// B
	double src_b_hmin_=180.;
	double src_b_hmax_=300.;
	double src_b_smin_= 50.;
	double src_b_smax_=100.;
	double src_b_vmin_=  0.;
	double src_b_vmax_=100.;
	const int tgt_b_red_ =  0;
	const int tgt_b_gre_ =  0;
	const int tgt_b_blu_ =0xff;

	/* "Color Trace Enhancement"ウインドウの各tgtボタン色設定し再表示 */
	void set_tgt_color_(
		const E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, const int color_choice_from_gui
	);

	/* "Color Trace Enhancement"ウインドウの各scr,val値を設定再表示 */
	void set_src_color_(
		const E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, const int color_choice_from_gui
	);

	/* "Color Trace Enhancement"ウインドウの各val値を、
	"Thickness"ウインドウの各値に移し再表示 */
	void set_thickness_(
		const E_COLOR_TRACE_HAB_COLORS trace_list_pos
		, const int color_choice_from_gui
	);
};

#endif /* !cb_color_trace_thickness_h */
