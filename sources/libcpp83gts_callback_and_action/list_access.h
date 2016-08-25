#ifndef __list_access_h__
#define __list_access_h__

class list_access {
public:
	list_access()
		:crnt_list_num_(-1)
		,crnt_file_num_(-1)
		,next_list_num_(-1)
		,next_file_num_(-1)
		,crnt_list_num_for_reset_(-1)
		,crnt_file_num_for_reset_(-1)
		,endress_sw_(false)
	{
	}
	int set_first_number( void );

	void reset_next_number( void );
	int set_next_number( void );

	void reset_next_to_crnt_number( void );
	void set_next_to_crnt_number( void );

	int get_i_crnt_list_num(void) { return this->crnt_list_num_; }
	int get_i_crnt_file_num(void) { return this->crnt_file_num_; }
	int get_i_next_file_num(void) { return this->next_file_num_; }

	int marking_src( int i_num );
	int marking_tgt( int i_num );

	void unselect( int i_num );

	void remove_all( void );
	void select_all( void );

	void set_endress_sw( bool sw ) { this->endress_sw_ = sw; }

private:
	int	crnt_list_num_
		, crnt_file_num_
		, next_list_num_
		, next_file_num_
		, crnt_list_num_for_reset_
		, crnt_file_num_for_reset_
		;
	bool endress_sw_;

	int _next_selected( int i_list_num );
};

#endif /* !__list_access_h__ */
