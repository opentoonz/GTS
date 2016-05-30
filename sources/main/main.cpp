#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>

#include <string.h>	/* strcmp() */
#include <stdlib.h>	/* exit() */
#include "ptbl_funct.h"
#include "pri.h"
#include "gts_master.h"
#include "gts_gui.h"

static void print_version( char *title )
{
pri_funct_msg_vr( "%s  %s  %s",
	title,
	cl_gts_master.cp_release_date(),
	cl_gts_master.cp_release_number()
);
}

static void print_help( char *title, gts_master *clp_master )
{
pri_funct_msg_vr( "Usage : %s [option]", title );
pri_funct_msg_vr( "Option");
pri_funct_msg_vr( " -version : print VERSION");
pri_funct_msg_vr( " -help    : print HELP");
pri_funct_msg_vr( " -bv      : Basic Verbose on");
pri_funct_msg_vr( " -cv      : Counter Verbose on");
pri_funct_msg_vr( "File Format");
pri_funct_msg_vr( " TIFF          (8,16bits)(.tif)" );
pri_funct_msg_vr( " Targa            (8bits)(.tga,.TGA)" );
}

static int argument_analyzer( int argc, char *argv[], char *cp_comm, gts_master *clp_master )
{
	int	ii;

	for (ii = 1; ii < argc; ++ii) {
		if      (!strcmp( argv[ii], "-version" )) {
			print_version( cp_comm ); exit (0);
		}
		else if (!strcmp( argv[ii], "-help"    )) {
			print_help( cp_comm, clp_master ); exit (0);
		}
		else if (!strcmp( argv[ii], "-bv" )) {
			clp_master->i_pv_sw( ON );
			clp_master->i_mv_sw( ON );
		}
		else if (!strcmp( argv[ii], "-cv" )) {
			clp_master->i_cv_sw( ON );
		}

		else if ('-' == argv[ii][0]) {
			pri_funct_err_bttvr(
				"Error: bad option<%s>", argv[ii]  );
			print_help( cp_comm, clp_master );
			return NG;
		}
		else {
			pri_funct_err_bttvr(
				"Error: bad argument<%s>",argv[ii] );
			print_help( cp_comm, clp_master );
			return NG;
		}
	}
	return OK;
}
#include "igs_lex_white_space_and_double_quote.h"
namespace {
 void setup_gts_( const char *comm ) {
	std::string path(comm);
	const char *const setup_file = "gts_install_setup.txt";
	std::string::size_type index = path.find_last_of("/\\");
	if (std::string::npos != index) {
		path.erase(index+1);
		path += setup_file;
	} else {
		path  = setup_file;
	}

	std::ifstream ifs( path.c_str() );
	if (!ifs) { return; } /* ファイルがないのでなにもしない */
	while (ifs) {
		char buf[1000];
		buf[0] = '\0';
		ifs.getline(buf,1000);
		if ('#' == buf[0]) { continue; }
		if ('\0' == buf[0]) { continue; }

		std::vector< std::string > words;
		igs::lex::white_space_and_double_quote(buf,words);

		if (words.size() == 2) {
			if (words.at(0) == "browser_directory_path") {
	cl_gts_master.cl_bro_config.setup_path(words.at(1).c_str());
	cl_gts_master.cl_bro_level.setup_path(words.at(1).c_str());
	cl_gts_master.cl_bro_trace_batch.setup_path(words.at(1).c_str());

			} else
			if (words.at(0) == "image_file_format") {
				if (words.at(1) == "TIFF") {
	cl_gts_master.cl_bro_level.set_current_imagefile_extension(0);
				} else if (words.at(1) == "TGA") {
	cl_gts_master.cl_bro_level.set_current_imagefile_extension(1);
				}
			} else
			if (words.at(0) == "short_cut_key_start_scan") {
				// start_scan	Enter(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_start_scan(words.at(1).c_str());
			} else
			if (words.at(0) == "short_cut_key_rescan") {
				// rescan	Space(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_rescan(words.at(1).c_str());
			} else
			if (words.at(0) == "short_cut_key_next_scan") {
				// next_scan	Enter(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_next_scan(words.at(1).c_str());
			} else
			if (words.at(0) == "short_cut_key_stop_scan") {
				// stop_scan	Esc(Default)
 cl_gts_master.cl_memo_short_cut_key.setup_stop_scan(words.at(1).c_str());
			}
		}
	}
	ifs.close();
 }
}

/* リリース名、版、日付 */
gts_master cl_gts_master( "gts" ,"2.3.3" ,"2016-5-30" );

int main( int argc, char **argv )
{
	/* 以後のプリント表示にコマンド名を付加する */
	pri_funct_set_cp_title( (char *)cl_gts_master.cp_release_name() );

	/* 初期化設定を設定ファイルから行なう */
	setup_gts_( argv[0] );

	/* 引数による設定や実行 */
	if (OK != argument_analyzer(
	argc, argv,
	(char *)cl_gts_master.cp_release_name(), &cl_gts_master )) {
		pri_funct_err_bttvr(
	 "Error : argument_analyzer(-) returns NG"  );
		return 2;
	}

	/* 全実行 */
	return cl_gts_master.exec( argv[0] );
}

