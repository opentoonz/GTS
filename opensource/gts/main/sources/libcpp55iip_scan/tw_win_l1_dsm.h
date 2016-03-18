#ifndef __tw_win_l1_dsm_h__
#define __tw_win_l1_dsm_h__

#include <windows.h> /* for twain.h */
#include "twain.h"

#include "ptbl_returncode.h"

typedef enum {
	TWAIN_STATE1_PRE_SESSION=1,
	TWAIN_STATE2_SOURCE_MANAGER_LOADED,
	TWAIN_STATE3_SOURCE_MANAGER_OPENED,
	TWAIN_STATE4_SOURCE_OPENED,
	TWAIN_STATE5_SOURCE_ENABLE,
	TWAIN_STATE6_TRANSFER_READY,
	TWAIN_STATE7_TRANSFERRING
} TWAIN_STATE;

/* Data Source Maneger */
class tw_win_l1_dsm {
public:
	tw_win_l1_dsm()
	{
		this->_i_mv_sw = OFF;
		this->_i_pv_sw = OFF;
		this->_i_cv_sw = OFF;

		this->_hm_dsm_dll = NULL;
		this->_p_dsm_entry = NULL;
		this->_hw_parent = NULL;
		this->twain_state = TWAIN_STATE1_PRE_SESSION;

		this->_init_tw_id( &(this->_AppID) );
		this->_init_tw_id( &(this->_SourceID) );
	}
	~tw_win_l1_dsm()
	{
		(void)this->state4to3();
		(void)this->state3to2();
		(void)this->state2to1();
	}

	void set_i_mv_sw( int sw ) {      this->_i_mv_sw = sw; }
	int  get_i_mv_sw( void ) { return this->_i_mv_sw; }
	void set_i_pv_sw( int sw ) {      this->_i_pv_sw = sw; }
	int  get_i_pv_sw( void ) { return this->_i_pv_sw; }
	void set_i_cv_sw( int sw ) {      this->_i_cv_sw = sw; }
	int  get_i_cv_sw( void ) { return this->_i_cv_sw; }

	void set_hw_parent( HWND hw ) { this->_hw_parent = hw; }

	char *get_cp_machine_type( void )
	{ return this->_SourceID.ProductName; }

protected:
	int state1to2( void ); /* ソースマネージャ(DSM)のロード */
	int state2to3( void ); /* ソースマネージャ(DSM)のオープン */
	int state3to4( unsigned long ul_id = 0UL, char *cp_str32="" );
				/* デバイス選択しソース(DS)のオープン */
	TW_UINT16 ds_entry( TW_UINT32 ui32_dg, TW_UINT16 ui16_dat,
		TW_UINT16 ui16_msg, TW_MEMREF p_data
		);	/* ソース(DS)へのアクセス(エラー処理なし) */
	int ds_pri_error( char *cp_tri, TW_UINT16 rc
		);	/* エラーメッセージの表示 */
	int state4to3( void ); /* ソース(DS)のクローズ */
	int state3to2( void ); /* ソースマネージャ(DSM)のクローズ */
	int state2to1( void ); /* ソースマネージャ(DSM)のアンロード */

	TWAIN_STATE	twain_state;

	/* state 2to3, 3to2, 4to5 */
	HWND	_hw_parent;	/* ソースの親のウインドウハンドル */
private:
	int	_i_mv_sw,
		_i_pv_sw,
		_i_cv_sw;

	/* state 1to2, 2to1 */
	HMODULE		_hm_dsm_dll;	/* DSM DLLへの参照 */
	DSMENTRYPROC	_p_dsm_entry;	/* 関数のポインター */

	/* state 3to4, 4to3 */
	TW_IDENTITY	_SourceID;

	/* state 1,2,3,4 */
	TW_IDENTITY	_AppID;		/* アプリケーション固有の属性 */

	void _init_tw_id( TW_IDENTITY *p_tw_id );

	TW_UINT16 _dsm_entry( TW_UINT32 ui32_dg, TW_UINT16 ui16_dat, TW_UINT16 ui16_msg, TW_MEMREF p_data );
	int _get_dsm_cc( TW_UINT16 *ui16p_cc );
	int _get_ds_cc( TW_UINT16 *ui16p_cc );
	int _pri_cc( TW_UINT16 ui16_cc );
	int _dsm_pri_error( char *cp_msg, TW_UINT16 rc );
};

#endif /* !__tw_win_l1_dsm_h__ */
