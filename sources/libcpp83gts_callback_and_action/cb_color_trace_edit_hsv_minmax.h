#ifndef cb_color_trace_edit_hsv_minmax_h
#define cb_color_trace_edit_hsv_minmax_h

class cb_color_trace_edit_hsv_minmax {
public:
	cb_color_trace_edit_hsv_minmax()
	{
	}
	void cb_hh_minmax( double minval, double maxval );
	void cb_aa_minmax( double minval, double maxval );
	void cb_bb_minmax( double minval, double maxval );

	void cb_hh_min( double minval );
	void cb_hh_max( double maxval );
	void cb_aa_min( double minval );
	void cb_aa_max( double maxval );
	void cb_bb_min( double minval );
	void cb_bb_max( double maxval );
private:
};

#endif /* !cb_color_trace_edit_hsv_minmax_h */
