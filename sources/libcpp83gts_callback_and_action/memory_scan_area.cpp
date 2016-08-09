#include <string.h>
#include <fstream>
#include <sstream>
#include "ptbl_funct.h" // ptbl_getenv(-)
#include "memory_scan_area.h"
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
}
//----------------------------------------------------------------------
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

 void file_path_from_dir_(std::string& dir_path, const char *file_name) {
	if (dir_path.empty()) {
		return;
	}

	dir_path += ptbl_get_cp_path_separeter();
	dir_path += file_name;
	if (!exist_file(dir_path.c_str())) {
		dir_path = std::string();
	}
 }

 std::string get_dexe_home_(const char *comm) {
	std::string path(comm);
	std::string::size_type index = path.find_last_of("/\\");
	if (std::string::npos != index) {
		path.erase(index);
	}
	return path;
 }
}

void ptbl_getenv(const char *name, std::string& env) {
	char *value = ptbl_getenv(name);
	env = value;
	free(value);
}

void ptbl_get_user_home(std::string& user_home)
{
# ifdef _WIN32
	std::string homedrive, homepath;
	ptbl_getenv("HOMEDRIVE", homedrive);
	ptbl_getenv("HOMEPATH" , homepath);
	if (!homedrive.empty() && !homepath.empty()) {
		user_home = homedrive;
		user_home += homepath;
	}
# else
	ptbl_getenv("HOME", user_home);
# endif
}

std::string gts_file_path(const char *comm, const char *file_name) {
	/* 優先度A  各ユーザーのホームにあるなら
	--> %HOMEDRIVE%%HOMEPATH%\_gts-scan_area.txt"
	=         "C:\Users\user1\_gts-scan_area.txt"
	*/
	std::string fpath_user;
	ptbl_get_user_home(fpath_user);
# ifndef _WIN32
	fpath_user += ptbl_get_cp_path_separeter();
	fpath_user += STR_DESKTOP_DIR;
	if(!ptbl_dir_or_file_is_exist((char *)fpath_user.c_str())) {
		ptbl_mkdir(fpath_user.c_str());
	}
# endif
	file_path_from_dir_(fpath_user, file_name);
	if(!fpath_user.empty()) {
		return fpath_user;
	}

# ifdef PKGDATADIR
	std::string fpath_data(PKGDATADIR);
	file_path_from_dir_(fpath_data, file_name);
	if(!fpath_data.empty()) {
		return fpath_data;
	}
# endif

	/* 優先度B  全ユーザープロファイルのホームにあるなら
 	--> %ALLUSERSPROFILE%\_gts-scan_area.txt"
	= "C:\Users\All Users\_gts-scan_area.txt" at WindowsXp 
	=     "C:\ProgramData\_gts-scan_area.txt" at Windows7  
		Windows7では一般ユーザーが書き込めないので使えない
	*/
	std::string fpath_prof;
	ptbl_getenv("ALLUSERSPROFILE", fpath_prof);
	file_path_from_dir_(fpath_prof, file_name);
	if (!fpath_prof.empty()) {
		return fpath_prof;
	}

	/* 優先度C  共有のホームにあるなら
	-->	%PUBLIC%\_gts-scan_area.txt"
	= "C:\Users\Public\_gts-scan_area.txt" at Windows7
	*/
	std::string fpath_publ;
	ptbl_getenv("PUBLIC", fpath_publ);
	file_path_from_dir_(fpath_publ, file_name);
	if (!fpath_publ.empty()) {
		return fpath_publ;
	}

	/* 優先度D  .exeと同じ場所にあるなら */
	std::string fpath_dexe(get_dexe_home_(comm));
	file_path_from_dir_(fpath_dexe, file_name);
	if(!fpath_dexe.empty()) {
		return fpath_dexe;
	}

	/* A,B,Cどれのファイルもないならなにもしない */
	return std::string();
}

std::string gts_scan_area_file_path_( const char *comm ) {
	const char *file_name = "_gts-scan_area.txt";
	return gts_file_path(comm, file_name);
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
