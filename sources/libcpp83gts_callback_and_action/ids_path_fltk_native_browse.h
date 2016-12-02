#ifndef ids_path_fltk_native_browse_h
#define ids_path_fltk_native_browse_h

#include <string>

namespace ids {
namespace path {

/*
ファイルを一つ開くためのブラウザーを開きファイルパスを得る
エラーの場合例外処理を投げる
Cancelの場合パスがempty()
*/
const std::string fltk_native_browse_open(
	const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter
	,const int filter_current
);

/*
ファイルを一つ保存するためのブラウザーを開きファイルパスを得る
エラーの場合例外処理を投げる
Cancelの場合パスがempty()
*/
const std::string fltk_native_browse_save(
	const std::string& dpath
	,const std::string& preset_file
	,const std::string& filter
	,const int filter_current
);

} // path
} // igs

#endif /* !ids_path_fltk_native_browse_h */
