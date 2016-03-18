#ifndef memory_short_cut_key_h
#define memory_short_cut_key_h

class memory_short_cut_key {
public:
	memory_short_cut_key();

	void setup_start_scan( const char *key );
	void setup_rescan( const char *key );
	void setup_next_scan( const char *key );
	void setup_stop_scan( const char *key );

	void set_space_key_focus_in_next_scan( void );
	void set_shortcut( void );
private:
	int start_scan_code_;
	int rescan_code_;
	int next_scan_code_;
	int stop_scan_code_;

	std::string rescan_label_key_;
	std::string next_scan_label_key_;
	std::string stop_scan_label_key_;

	std::string rescan_label_all_;
	std::string next_scan_label_all_;
	std::string stop_scan_label_all_;

	enum e_foc_num {
		f_n_nothing_ = -1
		,f_n_rescan_
		,f_n_next_scan_
		,f_n_stop_scan_
	};
	e_foc_num focus_number_;
};

#endif /* !memory_short_cut_key_h */
