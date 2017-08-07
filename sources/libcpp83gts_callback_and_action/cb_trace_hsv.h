#ifndef cb_trace_hsv_h
#define cb_trace_hsv_h

class cb_trace_hsv {
public:
	cb_trace_hsv()
	{
	}
	void cb_r_enable_sw( void );
	void cb_r_target_r( void );
	void cb_r_target_g( void );
	void cb_r_target_b( void );
	void cb_r_thickness( void );
	void cb_r_hmin( void );
	void cb_r_hmax( void );
	void cb_r_threshold_to_black( void );
	void cb_r_threshold_offset( void );

	void cb_g_enable_sw( void );
	void cb_g_target_r( void );
	void cb_g_target_g( void );
	void cb_g_target_b( void );
	void cb_g_thickness( void );
	void cb_g_hmin( void );
	void cb_g_hmax( void );
	void cb_g_threshold_to_black( void );
	void cb_g_threshold_offset( void );

	void cb_b_enable_sw( void );
	void cb_b_target_r( void );
	void cb_b_target_g( void );
	void cb_b_target_b( void );
	void cb_b_thickness( void );
	void cb_b_hmin( void );
	void cb_b_hmax( void );
	void cb_b_threshold_to_black( void );
	void cb_b_threshold_offset( void );

	void cb_bl_enable_sw( void );
	void cb_bl_target_r( void );
	void cb_bl_target_g( void );
	void cb_bl_target_b( void );
	void cb_bl_thickness( void );
	void cb_bl_threshold_to_black( void );
	void cb_bl_threshold_offset( void );

class cb_trace_hsv {
public:
	cb_trace_hsv()
	{}
	std::vector<cl_range> cla_range;
private:
};

#endif /* !cb_trace_hsv_h */
