#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l3_dsi.h"

/* state 6、あるいはstate 5で戻る */
int tw_win_l3_dsi::_state6to7to6native( void )
{
	TW_UINT16 rc;
	TW_PENDINGXFERS twPendingXfer;

	/* この method は state 6 で動作する */
	if (TWAIN_STATE6_TRANSFER_READY != this->twain_state) {
		return OK;
	}

	this->_free_dib_mem();

	if (ON == this->get_i_mv_sw()) {
	 pri_funct_msg_ttvr( "tw_win_l3_dsi::_state6to7to6native()" );
	}

	/*
	twPendingXfer.Count の値
	 ゼロより大きい : Count に指定された枚数の画像が転送待ちです
	 ゼロ           : 転送されるべきデータはもうありません
				自動的に State5 へ移行します
	 マイナス１     : 不定個のデータが転送待ちです
				ADFなどで残り枚数が分からないときなど
				にこの値となります
	*/

	twPendingXfer.Count = static_cast<TW_UINT16>(-1);
	while ( 0 != twPendingXfer.Count ) {

		/* DIB画像を取得する */
		if (ON == this->get_i_mv_sw()) {
			pri_funct_msg_ttvr(
				"twain state 6 --> 7 : Transferring" );
		}
		this->twain_state = TWAIN_STATE7_TRANSFERRING;

		rc = this->ds_entry(
			DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET,
			(TW_MEMREF)&(this->_h_dib_image)
		);

		if (TWRC_FAILURE == rc) {
			/*
			画像転送を失敗しました。
			メモリは確保せず、アドレス(hBitmap)は無効です。
			エラーの状況は、Condition Codeで確認します。
			状態は変化せず６のままです。
			画像データは止まっています。
			アプリケーションは転送を異常終了させてください。
			*/
			if (OK != this->ds_pri_error(
			"DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET", rc
			)) {
				pri_funct_err_bttvr(
			 "Error : this->ds_pri_error(-) returns NG." );
			}

			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
		"twain state --> 6 : because transfer failure" );
			}
			this->twain_state = TWAIN_STATE6_TRANSFER_READY;
			return NG;
		}

		/* 画像の転送をユーザがキャンセルした */
		else if (TWRC_CANCEL == rc) {
/*
ユーザーが画像転送をキャンセルしました。
メモリを確保しますが、アドレス(hBitmap)は無効なハンドルが入ります。
そして、この画像メモリの開放はアプリケーションがしなければなりません。
Sourceの状態はまだ７です。
転送保留の画像を確認し、Data Sourceを終了しなければなりません。
*/
			/* 転送の後処理を行う */
			rc = this->ds_entry(
			 DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER,
			 (TW_MEMREF)&twPendingXfer
			);

			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
	"twain state 7 --> 6 : because user click cancel" );
			}
			this->twain_state = TWAIN_STATE6_TRANSFER_READY;

			if (TWRC_FAILURE == rc) {
				if (OK != this->ds_pri_error(
			"DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER", rc
				)) {
					pri_funct_err_bttvr(
			"Error : this->ds_pri_error(-) returns NG." );
				}
				return NG;
			}
	
			if (0 == twPendingXfer.Count) {
				if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
	"twain state 6 --> 5 : because pending transfer is zero" );
				}
				this->twain_state =
					TWAIN_STATE5_SOURCE_ENABLE;
			}

			pri_funct_msg_ttvr(
	"DG_IMAGE,DAT_IMAGENATIVEXFER,MSG_GET --> TWRC_CANCEL" );

			/* キャンセルにより取り込み中止なので、
			画像転送ループ処理から抜ける 2017-02-01 */
			return OK;
		}

		/* 画像の転送が完了した */
		else if (TWRC_XFERDONE == rc) {
/*
画像転送を終了しました
メモリを確保し、画像(DIB(Windows)あるいはPICT(Mac))を格納、
そのアドレス(hBitmap)を返します
そして、この画像メモリの開放はアプリケーションがしなければなりません。
Sourceの現在の状態は７です。
この状態で、画像転送の終了を確認し、
他に転送画像があるのか、Data Sourceを終了するのか決めます
*/
			/* 転送の後処理を行う */
			rc = this->ds_entry(
			 DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER,
			 (TW_MEMREF)&twPendingXfer
			);

			if (ON == this->get_i_mv_sw()) {
				pri_funct_msg_ttvr(
			"twain state 7 --> 6 : because transfer done" );
			}
			this->twain_state = TWAIN_STATE6_TRANSFER_READY;

			if (TWRC_FAILURE == rc) {
				if (OK != this->ds_pri_error(
			"DG_CONTROL,DAT_PENDINGXFERS,MSG_ENDXFER", rc
				)) {
					pri_funct_err_bttvr(
			 "Error : this->ds_pri_error(-) returns NG." );
				}
				return NG;
			}
		}
		else {
			/* TWRC_FAILURE,TWRC_CANCEL,TWRC_XFERDONEの
			   3つしか返さない。
			   それ以外はTWAIN規格から外れている */
			assert(0);
		}

		if (NULL != (this->_h_dib_image)) {
			/* p_dib_bmi_headにDIBへのポインタを格納する */
			this->_p_dib_bitmapinfo =
			(BITMAPINFO *)GlobalLock(
				(this->_h_dib_image)
			);
		}
	}

	/* Countが0で、loopから抜け、自動的に State5 へ移行する */
	if (ON == this->get_i_mv_sw()) {
		pri_funct_msg_ttvr(
 "twain state 6 --> 5 : loop break, because pending transfer is zero" );
	}
	this->twain_state = TWAIN_STATE5_SOURCE_ENABLE;
	return OK;
}

/********************************************************************/

void tw_win_l3_dsi::_free_dib_mem( void )
{
	if (NULL != this->_h_dib_image) {
		GlobalUnlock(	this->_h_dib_image );
		GlobalFree(	this->_h_dib_image );
				this->_h_dib_image = NULL;
	}
	this->_p_dib_bitmapinfo = NULL;
}

/********************************************************************/
