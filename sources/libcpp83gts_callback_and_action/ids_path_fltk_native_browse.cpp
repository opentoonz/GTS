#include <FL/Fl.H> // Fl_Window
#include <FL/fl_ask.H> // fl_alert()
#include <FL/Fl_Native_File_Chooser.H>
#include <iostream>
#include <sstream> // std::ostringstream
#include <algorithm> // std::replace(-)
#include "ids_path_fltk_native_browse.h"

namespace {

const std::vector<std::string> fltk_native_file_chooser_(
	const std::string& title
	,const int type_flag
	/* type_flag
	BROWSE_FILE		1つのファイルを選択
	BROWSE_DIRECTORY	1つのディレクトリを選択
	BROWSE_MULTI_FILE	複数のファイルを選択
	BROWSE_MULTI_DIRECTORY	複数のディレクトリを選択
	BROWSE_SAVE_FILE	ファイルを保存するためにブラウズ
	BROWSE_SAVE_DIRECTORY	ディレクトリを保存するためにブラウズ
	*/
	,std::string dpath
	,const std::string& preset_file
	,const int options_flag
	/* options_flag
	NO_OPTIONS	有効なオプションはありません
	SAVEAS_CONFIRM	ネイティブの上書き確認ダイアログを表示
	NEW_FOLDER	'新しいフォルダ'アイコンを表示する（サポートあれば）
	PREVIEW		プレビューモードを有効にする（サポートあれば）
	USE_FILTER_EXT	選択フィルタは出力ファイル拡張子をパイロットします（サポートあれば）
	*/
	,const std::string& filter_str /* 改行で2行目以後も記入可能 */
	,const int filter_current
)
{
#if _WIN32
	// path separater must be '\\' in Windows
	std::replace(dpath.begin(), dpath.end(), '/', '\\');
#endif

	::Fl_Native_File_Chooser native;
/*
注意：
Ubuntu16.04-desktopで::Fl_Native_File_Chooser単独で実行すると落ちる
他のfltkウィジェット(Fl_Window等)の表示が必要
*/
	if (!title.empty()) {
		native.title( title.c_str() );
	}
	if (type_flag != 0) {
		native.type( type_flag );
	}
	if (!dpath.empty()) {
		native.directory( dpath.c_str() );
	}
	if (!preset_file.empty()) {
		native.preset_file( preset_file.c_str() );
	}
	if (	(options_flag&(::Fl_Native_File_Chooser::NO_OPTIONS))
	==	::Fl_Native_File_Chooser::NO_OPTIONS
	) {
		native.options( options_flag );
	}
	if (!filter_str.empty()) {
		native.filter( filter_str.c_str() );
	}
	if (0 <= filter_current) {
		native.filter_value( filter_current );
	}

	const int ret = native.show();
	std::vector<std::string> vecstr;
	if ( ret == -1 ) {	/* Error */
		throw native.errmsg();
	}
	/* 正常終了しファイル名ある */
	else if (ret==0 && 0 < native.count() && native.filename()) {
		for (int ii = 0 ;ii < native.count() ;++ii) {
			vecstr.push_back(std::string(native.filename(ii)));
		}
		return vecstr;
	}
	vecstr.push_back( "" ); /* 一行目で判別するため空のパスを入れとく */
	return vecstr; // Cancel
}

} // namespace

const std::vector<std::string> ids::path::fltk_native_browse_open(
	const std::string& title
	,const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter_str
	,const int filter_current
)
{
	return fltk_native_file_chooser_(
		title
		,::Fl_Native_File_Chooser::BROWSE_FILE /* 開く */
		,dpath
		,preset_file
		,::Fl_Native_File_Chooser::PREVIEW
		|::Fl_Native_File_Chooser::USE_FILTER_EXT
		,filter_str
		,filter_current
	);
}

const std::vector<std::string> ids::path::fltk_native_browse_save(
	const std::string& title
	,const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter_str
	,const int filter_current
)
{
	return fltk_native_file_chooser_(
		title
		,::Fl_Native_File_Chooser::BROWSE_SAVE_FILE /* 名付け保存 */
		,dpath
		,preset_file
		,::Fl_Native_File_Chooser::SAVEAS_CONFIRM
		|::Fl_Native_File_Chooser::NEW_FOLDER
		|::Fl_Native_File_Chooser::PREVIEW
		|::Fl_Native_File_Chooser::USE_FILTER_EXT
		,filter_str
		,filter_current
	);
}

const std::vector<std::string> ids::path::fltk_native_browse_open_files(
	const std::string& title
	,const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter_str
	,const int filter_current
)
{
	return fltk_native_file_chooser_(
		title
		,::Fl_Native_File_Chooser::BROWSE_MULTI_FILE /* 開く */
		,dpath
		,preset_file
		,::Fl_Native_File_Chooser::PREVIEW
		|::Fl_Native_File_Chooser::USE_FILTER_EXT
		,filter_str
		,filter_current
	);
}

#if DEBUG_INO
#include <FL/Fl_Window.H>
int main(int argc ,const char* argv[])
{
	if (argc < 2) {
		return 1;
	}

 try {
	/* --- 注意 ---
	Windowsでは不要だが、Ubuntu16.04-desktopでは
	何か他のfltkウィジェット(Fl_Window等)を開いておかないと落ちる
	*/
	Fl_Window win(600, 100, "FLTK Window");
	win.show();

	/* open */
	std::cout << "open=\"" << ids::path::fltk_native_browse_open(
		"Open" /* 開く */
		,argv[1]
		, "A.tga"
		, "TIFF\t*.tif\n" "Targa\t*.tga"
		, 1 /* "Targe\t*.tga"を示す */
	).at(0) << "\"\n";

	/* save */
	std::cout << "save=\"" << ids::path::fltk_native_browse_save(
		"Save as" /* 名前を付けて保存 */
		,argv[1]
		, "tmpsave.tga"
		, "TIFF\t*.tif\n" "Targa\t*.tga"
		, 0 /* "TIFF\t*.tif"を示す */
	).at(0) << "\"\n";

	/* open files */
	std::vector<std::string> vecstr(
		ids::path::fltk_native_browse_open_files(
		"Open Files" /* 開く */
		,argv[1]
		, ""
		, "TEXT\t*.txt\n"
		, 0 /* "TEXT\t*.txt"を示す */
	));
	std::cout << "open_files=\n";
	for (auto ss : vecstr) {
		std::cout << "\"" << ss << "\"\n";
	}
 }
 catch (std::exception& e) {
	std::ostringstream ost;
	ost	<< "Error in saving"
		//<< " \"" << open_file_path << "\""
		<< "," << e.what() << std::endl;
	std::cerr << ost.str();
	fl_alert( ost.str().c_str() );/* ユーザーに知らせる */
	return 1;
 }
 catch (...) {
	fl_alert( "Error in saving." );/* ユーザーに知らせる */
	return 2;
 }

	return 0;
}
/*
:165,167 w! make.bat
rem windows make
cl /W3 /MD /EHa /O2 /wd4819 /DWIN32 /DDEBUG_INO /I..\..\thirdparty\fltk\fltk-1.3.4-1 ..\..\thirdparty\fltk\fltk-1.3.4-1\lib\fltk-1.3.4-1-vc2013-32.lib glu32.lib advapi32.lib shlwapi.lib opengl32.lib comctl32.lib wsock32.lib user32.lib gdi32.lib shell32.lib ole32.lib comdlg32.lib ids_path_fltk_native_browse.cpp /Fet
del ids_path_fltk_native_browse.obj

:270,270 w! make.csh
# linux make
#g++ -Ifltk-1.3.4-1/fltk-1.3.4-1 -DDEBUG_INO -std=c++11 ids_path_fltk_native_browse.cpp fltk-1.3.4-1/fltk-1.3.4-1/lib/libfltk.a -ldl -lX11 -lXext -lXcursor -lXfixes -lXinerama
g++ -DDEBUG_INO -std=c++11 ids_path_fltk_native_browse.cpp -lfltk
*/
#endif // DEBUG_INO
