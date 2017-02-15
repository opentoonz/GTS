#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* State 5 -> 6 -> 5  アプリケーションに転送準備が整ったことを通知 */
int tw_win_l3_dsi::state5to6to5event( void )
{
	TW_UINT16 rc;
	int	i_ret;
	MSG msg;
	TW_EVENT twEvent;
	TW_PENDINGXFERS twPendingXfer;

	while (GetMessage((LPMSG)&msg,NULL,0,0) != 0) {
	 /* TWAIN以外のWindowsイベントとして初期化 */
	 rc = TWRC_NOTDSEVENT;

	 if (TWAIN_STATE5_SOURCE_ENABLE == this->twain_state) {
	  twEvent.TWMessage = MSG_NULL;
	  twEvent.pEvent = (TW_MEMREF)&msg;
	  rc = this->ds_entry(
		DG_CONTROL,DAT_EVENT,MSG_PROCESSEVENT,
		(TW_MEMREF)&twEvent
	  );
	  switch (twEvent.TWMessage) {
	  case MSG_XFERREADY:
		/* ユーザがGUIのスキャン「取り込み」ボタンを押したとき、
		GUI表示しない場合は、(たぶん)いきなり、
		このイベント(MSG_XFERREADY)がくる */

	  	/* MSG_XFERREADYを受信したアプリはState5から6へ進む */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
	"twain state 5 --> 6 : because receive MSG_XFERREADY event" );
		}
		this->twain_state = TWAIN_STATE6_TRANSFER_READY;


		/* 画像転送 戻ってからstate 6、state 5の場合あり */
		i_ret = this->_state6to7to6select();


		/* のこりの転送を強制終了しState 6から5へ戻る */
		if (TWAIN_STATE6_TRANSFER_READY == this->twain_state) {
			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
	"twain state 6 --> 5 : because transfer error or cancel" );
			}
			this->twain_state = TWAIN_STATE5_SOURCE_ENABLE;

			rc = this->ds_entry(
				DG_CONTROL,DAT_PENDINGXFERS,MSG_RESET,
				(TW_MEMREF)&twPendingXfer
	  		);
			if (TWRC_SUCCESS != rc) {
				if (OK != this->ds_pri_error(
				"DG_CONTROL,DAT_PENDINGXFERS,MSG_RESET", rc
				)) {
					pri_funct_err_bttvr(
			 "Error : this->ds_pri_error(-) returns NG." );
				}
				/* return NG; */
			}
		}

		/* 画像転送でエラーだったときは、
		MSG_RESETしてからエラーリターン */
		if (NG == i_ret) {
			pri_funct_err_bttvr(
		 "Error : this->state6to7select() returns NG." );
			return NG;
		}
		if (CANCEL == i_ret) {
			return CANCEL;
		}

		/* GUIを使わないときこのイベントループから抜ける */
		if (FALSE == this->_tw_ui.ShowUI) {
			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
			"break GetMessage(-) loop, when no GUI" );
			}
			return OK;
		}
		break;

	  case MSG_CLOSEDSREQ:
		/* ユーザがGUIのcloseボタンを押すと
		このイベント(MSG_CLOSEDSREQ)がくる(2004.11.10) */
		if (ON == this->get_i_mv_sw()) {
 			pri_funct_msg_ttvr(
		"close TWAIN GUI,(get MSG_CLOSEDSREQ event)" );
		}
		return OK;
		break;

	  case MSG_CLOSEDSOK:
		/* DG_CONTROL/DAT_USERINTERFACE/MSG_ENABLEDSUIONLY
		を使ったとき(意味不明...) */
		if (ON == this->get_i_mv_sw()) {
 			pri_funct_msg_ttvr( "get MSG_CLOSEDSOK event" );
		}
		return OK;
		break;

	  case MSG_NULL:
		/* GUIを表示したままなにもしないと
		一定時間ごとこのイベント(MSG_NULL)がくる */
		break;/* 次のイベントループへ続く */
	  }
	 }

	 /* TWAIN以外のWindowsイベント */
	 if (TWRC_NOTDSEVENT == rc) {
		TranslateMessage( (LPMSG)&msg );
		DispatchMessage( (LPMSG)&msg );
	 }
	}
	return OK;
}
