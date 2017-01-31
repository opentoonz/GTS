#ifndef ids_path_fltk_native_browse_h
#define ids_path_fltk_native_browse_h

#include <string>
#include <vector>

namespace ids {
namespace path {

/*
ファイルを一つ開くためのブラウザーを開きファイルパスを得る
エラーの場合例外処理を投げる
Cancelの場合1番目のパスがempty()
*/
const std::vector<std::string> fltk_native_browse_open(
	const std::string& title
	,const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter
	,const int filter_current
);

/*
ファイルを一つ保存するためのブラウザーを開きファイルパスを得る
エラーの場合例外処理を投げる
Cancelの場合1番目のパスがempty()
*/
const std::vector<std::string> fltk_native_browse_save(
	const std::string& title
	,const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter
	,const int filter_current
);

/*
ファイルを複数開くためのブラウザーを開き複数ファイルパスを得る
エラーの場合例外処理を投げる
Cancelの場合1番目のパスがempty()
*/
const std::vector<std::string> fltk_native_browse_open_files(
	const std::string& title
	,const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter_str
	,const int filter_current
);

} // path
} // igs

#endif /* !ids_path_fltk_native_browse_h */
