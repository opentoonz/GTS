#ifndef __list_access_h__
#define __list_access_h__

class list_access {
public:
	list_access()
		:_i_crnt_list_num(-1)
		,_i_crnt_file_num(-1)
		,_i_next_list_num(-1)
		,_i_next_file_num(-1)
		,_i_crnt_list_num_backup(-1)
		,_i_crnt_file_num_backup(-1)
		,endress_sw_(false)
	{
	}
	int set_first_number( void );

	void reset_next_number( void );
	int set_next_number( void );

	void reset_next_to_crnt_number( void );
	void set_next_to_crnt_number( void );

	int get_i_crnt_list_num(void) { return this->_i_crnt_list_num; }
	int get_i_crnt_file_num(void) { return this->_i_crnt_file_num; }
	int get_i_next_file_num(void) { return this->_i_next_file_num; }

	int marking_src( int i_num );
	int marking_tgt( int i_num );

	void unselect( int i_num );

	void remove_all( void );
	void select_all( void );

	void set_endress_sw( bool sw ) { this->endress_sw_ = sw; }

private:
	int	_i_crnt_list_num,
		_i_crnt_file_num,
		_i_next_list_num,
		_i_next_file_num,
		_i_crnt_list_num_backup,
		_i_crnt_file_num_backup;
	bool endress_sw_;

	int _next_selected( int i_list_num );
};

#endif /* !__list_access_h__ */
