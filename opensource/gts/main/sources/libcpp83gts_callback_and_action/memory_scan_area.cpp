#include "gts_gui.h"
#include "gts_master.h"

void gts_master::cb_area_selecter( void ) {
	/* Areaセレクターで先頭のゼロを選択したときは"Custom" */
	if (0 == cl_gts_gui.choice_area_selecter->value()) {
		/* 各項目入力できるようにする */
		cl_gts_gui.group_area_crop->activate();
	}
	/* Areaセレクターで2番目以後を選択したとき */
	else {
		/* 現在選択位置からArea情報をコピーで得る */
		preset_axywhr area =
		cl_gts_master.cl_memo_scan_area.areas.at(
			cl_gts_gui.choice_area_selecter->value()-1
		);

		/* Start X Y cm */
		cl_gts_gui.valinp_area_x_pos->value( area.x );
		cl_gts_gui.valinp_area_y_pos->value( area.y );

		/* Screen Aspect Ratio選択位置 */
		cl_gts_gui.choice_area_aspect_ratio_selecter->value(
		cl_gts_gui.choice_area_aspect_ratio_selecter->find_item(area.r.c_str())
		);

		/* Size W H cm */
		cl_gts_gui.valinp_area_x_size->value( area.w );
		cl_gts_gui.valinp_area_y_size->value( area.h );

		/* Size W H pixel */
		cl_gts_gui.valinp_area_x_pixel->value( 
		 cl_gts_gui.valinp_area_x_size->value()
		 * cl_gts_gui.valinp_area_reso->value() / 2.54
		);
		cl_gts_gui.valinp_area_y_pixel->value( 
		 cl_gts_gui.valinp_area_y_size->value()
		 * cl_gts_gui.valinp_area_reso->value() / 2.54
		);

		/* 各項目入力できなくする */
		cl_gts_gui.group_area_crop->deactivate();

		/* Cropエリア(OpenGL)再表示 */
		this->_from_area_val_to_opengl_rect();
	}
}
void gts_master::cb_area_aspect_ratio_selecter( void ) {
	/* Areaセレクターで先頭のゼロを選択したときは"Custom" */
	if (0 ==
	cl_gts_gui.choice_area_aspect_ratio_selecter->value()) {
		return;
	}
	/* Areaセレクターで2番目以後を選択したとき */
	else {
		/* 現在選択位置からArea情報をコピーで得る */
		preset_rwh ratio =
	cl_gts_master.cl_memo_scan_area.aspect_ratios.at(
	cl_gts_gui.choice_area_aspect_ratio_selecter->value()-1
		);

		/* Size H cm */
		cl_gts_gui.valinp_area_y_size->value(
		cl_gts_gui.valinp_area_x_size->value() * ratio.h / ratio.w
		);

		/* Size H pixel */
		cl_gts_gui.valinp_area_y_pixel->value( 
		 cl_gts_gui.valinp_area_y_size->value()
		 * cl_gts_gui.valinp_area_reso->value() / 2.54
		);

		/* Cropエリア(OpenGL)再表示 */
		this->_from_area_val_to_opengl_rect();
	}
}
//--------------------------------------------------------------------
#include <fstream>
#include <sstream>
#include <cstdlib> /* getenv_s() */
namespace {
 double dbl_from_str_( const std::string&str) {
	std::istringstream ist(str);
	double val = 0.0;
	ist >> val;
	return val;
 }
 void set_aspect_ratios_(
	const std::vector< std::string >&words
	,std::vector<preset_rwh>&aspect_ratios
 ) {
	preset_rwh ratio;
	if (1 < words.size()) {
		cl_gts_gui.choice_area_aspect_ratio_selecter->add(
			words.at(1).c_str()
		);
	}
	if (2 < words.size()) { ratio.w = dbl_from_str_(words.at(2)); }
	if (3 < words.size()) { ratio.h = dbl_from_str_(words.at(3)); }
	aspect_ratios.push_back( ratio );
 }
 void set_areas_(
	const std::vector< std::string >&words
	,std::vector<preset_axywhr>&areas
 ) {
	preset_axywhr area;
	if (0 < words.size()) {
		cl_gts_gui.choice_area_selecter->add( words.at(0).c_str() );
	}
	if (1 < words.size()) { area.x = dbl_from_str_(words.at(1)); }
	if (2 < words.size()) { area.y = dbl_from_str_(words.at(2)); }
	if (3 < words.size()) { area.w = dbl_from_str_(words.at(3)); }
	if (4 < words.size()) { area.h = dbl_from_str_(words.at(4)); }
	if (5 < words.size()) { area.r = words.at(5); }
	areas.push_back( area );
 }
 void set_line_to_words_(
	const std::string&line
	,std::vector< std::string >&words
 ) {
	std::istringstream ist(line);
	for (unsigned ii=0;;++ii) {
		std::string item;
		ist >> item;
		if (item.empty()) {break;}
		words.push_back(item);
	}
 }
 void load_by_fname_( const char *file_path ,memory_scan_area&scan_area) {
	/*--- ファイル開く ---*/
	std::cout
		<< "Preset scan area from \"" << file_path << "\""
		<< std::endl;
	std::ifstream ifs( file_path );
	if (!ifs) {
		std::string str("Can not open \"");str+=file_path;str+="\"";
		throw std::domain_error( str );
	}
	/*--- 1行づつ読込 ---*/
	std::string line;
	while (std::getline(ifs,line)) {
		/*--- 読み込みエラーチェック ---*/
		if (ifs.bad()) {
			std::string str("Can not read \"");
			str += file_path; str += "\"";
			throw std::domain_error( str );
		}
		/*--- キャンセル行 ---*/
		//if ( ifs.fail()) { continue; } /* 次の演算は失敗する */
		//if (!ifs.good()) { continue; } /* 次の演算はnull演算 */
		if (line.size() <= 0) { continue; }	/* 空行 */
		{
			/* 頭の空白文字をとり */
			std::istringstream ist(line);
			std::string str;
			ist >> str;
			if (str.size() <= 0) { continue; } /* 空白行 */
			if ('#' == str.at(0)) { continue;} /* コメント行 */
		}
		/*--- 文字行の整形 ---*/
		/* unix(0x0a)でwindows(0x0d0x0a)の改行コード問題の対処
		(0x0d)が行の終わりに残ってしまうので削除する
		なお、windowsでunixの改行コードは問題なく読む */
		if (0x0d == line.at(line.size()-1)) {
			line.erase( line.size()-1 );
		}
		/*--- 行の分解 ---*/
		std::vector< std::string > words;
 		set_line_to_words_( line ,words );
		/*--- 設定 ---*/
		if ("aspect_ratio" == words.at(0)) {
			set_aspect_ratios_( words ,scan_area.aspect_ratios);
		} else {
			set_areas_( words ,scan_area.areas );
		}
	}
	/*--- ファイル閉じる ---*/
	ifs.close();
 }
 //--------------------------------------------------------------------
 std::string getenv_(const char *const key) {
	size_t length=0;
	char ca_env[_MAX_ENV];	// _MAX_ENV is 32,767 at vc2005 stdlib.h
	ca_env[0] = '\0';
	errno_t err_no = getenv_s(&length,ca_env,_MAX_ENV,key);
	/* getenv_s(-)は環境変数がない場合、正常終了し、lengthゼロとなる */
	if (err_no != 0) {
		std::ostringstream ost;
		ost<<"getenv_s(,,,"<<key<<") returns error("<<err_no<<")";
		throw std::domain_error( ost.str() );
	}
	if (length >= _MAX_ENV) {
		std::ostringstream ost;
		ost	<< "getenv_s(,,," << key
			<< ") get too long length(" << err_no << ")";
		throw std::domain_error( ost.str() );
	}
	ca_env[length] = '\0';
	return std::string(ca_env);
 }
 std::string get_user_home_( void ) {
	std::string home_drive( getenv_("HOMEDRIVE") );
	if	   (home_drive.empty()) { return std::string(); }
	std::string home_path( getenv_("HOMEPATH") );
	if	   (home_path.empty()) { return std::string(); }
	home_drive += home_path;
	return home_drive;
 }
 std::string get_profile_home_(void) { return getenv_("ALLUSERSPROFILE"); }
 std::string get_public_home_( void) { return getenv_("PUBLIC"); }
}
//----------------------------------------------------------------------
#include "ptbl_funct.h"
namespace {
 bool exist_file(const char *filename) {
	/*FILE  *fp;
	if ((fp = ::fopen(filename, "r")) == NULL) {
		return false;
	}
	::fclose(fp);
	return true;*/

	std::ifstream ifs( filename );
	if (ifs) { return true; }
	return false;
 }

 std::string file_path_from_home_( const std::string&dir_path ) {
	if (dir_path.empty()) { return std::string(); }

	const char *const file_name = "_gts-scan_area.txt";

	std::string file_path( dir_path );
	file_path += ptbl_get_cp_path_separeter();
	file_path += file_name;
	if (exist_file(file_path.c_str())) {
		return file_path;
	}
	return std::string();
 }
 std::string get_dexe_home_(const char *comm) {
	std::string path(comm);
	std::string::size_type index = path.find_last_of("/\\");
	if (std::string::npos != index) {
		path.erase(index);
	}
	return path;
 }
 std::string gts_scan_area_file_path_( const char *comm ) {

	/* 優先度A  各ユーザーのホームにあるなら
	--> %HOMEDRIVE%%HOMEPATH%\_gts-scan_area.txt"
	=         "C:\Users\user1\_gts-scan_area.txt"
	*/
	std::string fpath_user( file_path_from_home_(get_user_home_()) );
	if        (!fpath_user.empty()) { return fpath_user; }

	/* 優先度B  全ユーザープロファイルのホームにあるなら
 	--> %ALLUSERSPROFILE%\_gts-scan_area.txt"
	= "C:\Users\All Users\_gts-scan_area.txt" at WindowsXp 
	=     "C:\ProgramData\_gts-scan_area.txt" at Windows7  
		Windows7では一般ユーザーが書き込めないので使えない
	*/
	std::string fpath_prof( file_path_from_home_(get_profile_home_()) );
	if        (!fpath_prof.empty()) { return fpath_prof; }

	/* 優先度C  共有のホームにあるなら
 	-->       %PUBLIC%\_gts-scan_area.txt"
	= "C:\Users\Public\_gts-scan_area.txt" at Windows7
	*/
	std::string fpath_publ( file_path_from_home_(get_public_home_()) );
	if        (!fpath_publ.empty()) { return fpath_publ; }

	/* 優先度D  .exeと同じ場所にあるなら */
	std::string fpath_dexe( file_path_from_home_(get_dexe_home_(comm)));
	if        (!fpath_dexe.empty()) { return fpath_dexe; }

	/* A,B,Cどれのファイルもないならなにもしない */
	return std::string();
 }
}
//----------------------------------------------------------------------
int memory_scan_area::load( const char *comm ) {
 try {
	/* ファイルパスを得る */
	std::string file_path( gts_scan_area_file_path_(comm) );

	/* ファイル存在しなければなにもしない */
	if (file_path.empty()) { return OK; }

	/* 読み込む */
 	load_by_fname_( file_path.c_str() ,*this );
 }
 catch (std::exception&e) {
	std::cerr << e.what() << std::endl;
	return NG;
 }
 catch (...) {
	std::cerr << "other exception of memory_scan_area::load()"
		<< std::endl;
	return NG;
 }
	return OK;
}
