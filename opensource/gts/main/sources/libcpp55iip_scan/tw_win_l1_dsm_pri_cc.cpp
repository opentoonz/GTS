#include "ptbl_returncode.h"
#include "pri.h"
#include "tw_win_l1_dsm.h"

/*
条件コード(Condition Code)からエラーの詳細情報を表示する

this->_p_dsm_entry(-)がエラー(TWRC_FAILURE)を返し、
さらに情報が必要で、
再びthis->_p_dsm_entry(-)を読んでもよい場合、
使用する。
*/
int tw_win_l1_dsm::_pri_cc( TW_UINT16 ui16_cc )
{
	switch ( ui16_cc ) {
	case TWCC_CUSTOMBASE:
		pri_funct_err_bttvr(
	"TWCC_CUSTOMBASE : 0x8000 : costom base" );
		break;
	case TWCC_SUCCESS:
		pri_funct_err_bttvr(
	"TWCC_SUCCESS : 0 : It worked!" );
		break;
	case TWCC_BUMMER:
		pri_funct_err_bttvr(
	"TWCC_BUMMER : 1 : Failure due to unknown causes" );
		break;
	case TWCC_LOWMEMORY:
		pri_funct_err_bttvr(
	"TWCC_LOWMEMORY : 2 : Not enough memory to perform operation" );
		break;
	case TWCC_NODS:
		pri_funct_err_bttvr(
	"TWCC_NODS : 3 : No Data Source" );
		break;
	case TWCC_MAXCONNECTIONS:
		pri_funct_err_bttvr(
	"TWCC_MAXCONNECTIONS : 4 : DS is connected to max possible applications" );
		break;
	case TWCC_OPERATIONERROR:
		pri_funct_err_bttvr(
	"TWCC_OPERATIONERROR : 5 : DS or DSM reported error, application shouldn't" );
		break;
	case TWCC_BADCAP:
		pri_funct_err_bttvr(
	"TWCC_BADCAP : 6 : Unknown capability" );
		break;
	case TWCC_BADPROTOCOL:
		pri_funct_err_bttvr(
	"TWCC_BADPROTOCOL : 9 : Unrecognized MSG DG DAT combination" );
		break;
	case TWCC_BADVALUE:
		pri_funct_err_bttvr(
	"TWCC_BADVALUE : 10 : Data parameter out of range" );
		break;
	case TWCC_SEQERROR:
		pri_funct_err_bttvr(
	"TWCC_SEQERROR : 11 : DG DAT MSG out of expected sequence" );
		break;
	case TWCC_BADDEST:
		pri_funct_err_bttvr(
	"TWCC_BADDEST : 12 : Unknown destination Application/Source in DSM_Entry" );
		break;
	case TWCC_CAPUNSUPPORTED:
		pri_funct_err_bttvr(
	"TWCC_CAPUNSUPPORTED : 13 : Capability not supported by source" );
		break;
	case TWCC_CAPBADOPERATION:
		pri_funct_err_bttvr(
	"TWCC_CAPBADOPERATION : 14 : Operation not supported by capability" );
		break;
	case TWCC_CAPSEQERROR:
		pri_funct_err_bttvr(
	"TWCC_CAPSEQERROR : 15 : Capability has dependancy on other capability(Added 1.8)" );
		break;
	case TWCC_DENIED:
		pri_funct_err_bttvr(
	"TWCC_DENIED : 16 : File System operation is denied (file is protected)" );
		break;
	case TWCC_FILEEXISTS:
		pri_funct_err_bttvr(
	"TWCC_FILEEXISTS : 17 : Operation failed because file already exists." );
		break;
	case TWCC_FILENOTFOUND:
		pri_funct_err_bttvr(
	"TWCC_FILENOTFOUND : 18 : File not found" );
		break;
	case TWCC_NOTEMPTY:
		pri_funct_err_bttvr(
	"TWCC_NOTEMPTY : 19 : Operation failed because directory is not empty" );
		break;
	case TWCC_PAPERJAM:
		pri_funct_err_bttvr(
	"TWCC_PAPERJAM : 20 : The feeder is jammed" );
		break;
	case TWCC_PAPERDOUBLEFEED:
		pri_funct_err_bttvr(
	"TWCC_PAPERDOUBLEFEED : 21 : The feeder detected multiple pages" );
		break;
	case TWCC_FILEWRITEERROR:
		pri_funct_err_bttvr(
	"TWCC_FILEWRITEERROR : 22 : Error writing the file (meant for things like disk full conditions)" );
		break;
	case TWCC_CHECKDEVICEONLINE:
		pri_funct_err_bttvr(
	"TWCC_CHECKDEVICEONLINE : 23 : The device went offline prior to or during this operation" );
		break;
	default:
		pri_funct_err_bttvr(
	"TWCC : %d : unknown at TWAIN v1.9 condition code",
			ui16_cc );
		return NG;
		break;
	}
	return OK;
}
