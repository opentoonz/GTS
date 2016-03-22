#ifndef __list_access_h__
#define __list_access_h__

class list_access {
public:
	list_access()
	{
		this->_i_crnt_list_num = -1;
		this->_i_crnt_file_num = -1;
		this->_i_next_list_num = -1;
		this->_i_next_file_num = -1;
		this->_i_crnt_list_num_backup = -1;
		this->_i_crnt_file_num_backup = -1;
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
private:
	int	_i_crnt_list_num,
		_i_crnt_file_num,
		_i_next_list_num,
		_i_next_file_num,
		_i_crnt_list_num_backup,
		_i_crnt_file_num_backup;

	int _next_selected( int i_list_num );
};

#endif /* !__list_access_h__ */
