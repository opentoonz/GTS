#include <assert.h>
#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/*
VALID_HANDLEは、
TWAIN v1.9仕様書(Spec1_9_197.pdf Page41)のサンプルコードに
記載があるが、値の定義がない。
twain_sdk/twack/Dca_glue.hにはあるので、それを転載、使用する。
*/
#ifndef VALID_HANDLE
#define VALID_HANDLE 32 /* valid windows handle SB >= 32 */
#endif

/* ソースマネージャ(DSM)のロード */
int tw_win_l1_dsm::state1to2( void )
{
	char ca_path[MAX_PATH];
/***#if defined _WIN64
	char *cp_twain_dll_file_name = "twain.dll";
#else***/
	char *cp_twain_dll_file_name = "TWAIN_32.DLL";
/***#endif***/
	OFSTRUCT	st_ofstruct;

	/* 状態(state)が1でないときは何もしない */
	if (TWAIN_STATE1_PRE_SESSION != this->twain_state) {
		return OK;
	}

	assert(NULL == this->_hm_dsm_dll);
	assert(NULL == this->_p_dsm_entry);

	if (ON == this->_i_mv_sw) {
		pri_funct_msg_ttvr( "tw_win_l1_dsm::state1to2()" );
	}

	/* Windowsシステムへのディレクトリパスを得る */
	if (0 == GetWindowsDirectory( ca_path, sizeof(ca_path) )) {
		pri_funct_err_bttvr(
	"Error : GetWindowsDirectory() returns zero" );

		pri_funct_err_bttvr(
	"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}

	/* 得たディレクトリパスの終端に区切り文字を追加 */
	if ('\\' != ca_path[(strlen(ca_path) - 1)]){
		(void)strcat( ca_path, "\\" );
	}

	/* さらにファイル名を追加しdllへのファイルパスとする */
	(void)strcat( ca_path, cp_twain_dll_file_name );

	/* TWAIN DLLファイル存在の確認 */
	if (-1 == OpenFile( ca_path,&st_ofstruct,OF_EXIST )) {
		pri_funct_err_bttvr(
	 "Error : OpenFile(%s,,OF_EXIST) returns -1.",
			ca_path );
		return NG;
	}

	/* state 1-->2  ソースマネージャ(TWAIN DLLファイル)のロード */ 
	this->_hm_dsm_dll = LoadLibrary( cp_twain_dll_file_name );
	if (NULL == this->_hm_dsm_dll) {
		pri_funct_err_bttvr(
 		"Error : LoadLibrary() returns NULL" );
		pri_funct_err_bttvr(
 		"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}
	if (this->_hm_dsm_dll < (HANDLE)VALID_HANDLE) {
		pri_funct_err_bttvr(
			"Error : LoadLibrary() returns invalid<%p>.",
			this->_hm_dsm_dll );
		return NG;
	}

	/* TWAIN DLLから関数ポインタの取得 */
	this->_p_dsm_entry = (DSMENTRYPROC)GetProcAddress(
		this->_hm_dsm_dll,
		MAKEINTRESOURCE(1) /* TWAIN spec 1.9に記載のやり方 */
				   /* "DSM_Entry"として動作する */
	);
	if (NULL == this->_p_dsm_entry) {
		pri_funct_err_bttvr(
			"Error : GetProcAddress() returns zero" );
		pri_funct_err_bttvr(
 		"         and GetLastError() is %u.", GetLastError() );
		return NG;
	}

	/* 状態(state)を2に進める */
	this->twain_state = TWAIN_STATE2_SOURCE_MANAGER_LOADED;
	if (ON == this->_i_pv_sw) {
		pri_funct_msg_ttvr(
		"twain state 1 --> 2 : source manager loaded" );
	}

	return OK;
}
