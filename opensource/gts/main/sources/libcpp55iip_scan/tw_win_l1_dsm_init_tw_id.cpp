#include "tw_win_l1_dsm.h"

/* 主に、AppIDに対する設定、
SourceIDはデータソースオープンの時ハードから読んで設定するので、
ダミー設定のとなる */
void tw_win_l1_dsm::_init_tw_id( TW_IDENTITY *p_tw_id )
{
	p_tw_id->Id = 0;
	p_tw_id->Version.MajorNum = 0;
	p_tw_id->Version.MinorNum = 1;
	p_tw_id->Version.Language = TWLG_JAPANESE;
	p_tw_id->Version.Country = TWCY_JAPAN;
	p_tw_id->ProtocolMajor = TWON_PROTOCOLMAJOR;
	p_tw_id->ProtocolMinor = TWON_PROTOCOLMINOR;
	p_tw_id->SupportedGroups = DG_IMAGE | DG_CONTROL;

	/* ここからはアプリケーションごとの設定 */

	strcpy(p_tw_id->Version.Info, "");

	/* 開発元(メーカー)(\0を含めて34文字) */
	strcpy(p_tw_id->Manufacturer, "");

	/* シリーズ名(製品ファミリー)(\0を含めて34文字) */
	strcpy(p_tw_id->ProductFamily, "");

	/* 製品名(\0を含めて34文字) */
	strcpy(p_tw_id->ProductName, "");
}
