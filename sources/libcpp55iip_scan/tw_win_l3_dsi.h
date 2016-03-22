#ifndef __tw_win_l3_dsi_h__
#define __tw_win_l3_dsi_h__

#include "tw_win_l2_dss.h"

/* Data Source Image */
class tw_win_l3_dsi : public tw_win_l2_dss {
public:
	tw_win_l3_dsi()
	{
		this->_tw_ui.ShowUI = FALSE;
		this->_tw_ui.ModalUI = FALSE;
		this->_tw_ui.hParent = NULL;
		this->_h_dib_image = NULL;
		this->_p_dib_bitmapinfo = NULL;
	}
	~tw_win_l3_dsi()
	{
		this->_free_dib_mem();
		this->state5to4();
	}

protected:
	int state4to5( HWND h_wnd = NULL, unsigned short us_show_ui = FALSE, unsigned short us_model_ui = FALSE );
	int state5to6to5event( void );
	int state5to4( void );

	BITMAPINFO	*_p_dib_bitmapinfo;

private:
	TW_USERINTERFACE	_tw_ui;
	HANDLE		_h_dib_image;

	int _state6to7to6select( void );
	int _state6to7to6native( void );
	void _free_dib_mem( void );
};

#endif /* !__tw_win_l3_dsi_h__ */
