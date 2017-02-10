#ifndef ids_path_level_from_files_h
#define ids_path_level_from_files_h

#include <vector>
#include <string>

namespace ids {
namespace path {

/* ファイルパスをディレクトリパスとファイル名に分割する */
void from_fpath_to_dpath_fname(
	const std::string& fpath
	,std::string& dpath
	,std::string& fname
);
/* ディレクトリパスとファイル名をファイルパスにする */
const std::string fpath_from_dpath_fname(
	const std::string& dpath
	,const std::string& fname
);

/* level_from_files(-)でファイル名のヘッドと数値との区切文字 */
const char*  get_separator_codes_for_level_from_files(void);
const char** get_separator_names_for_level_from_files(void);

/*
fpathからdpath,head,num,number,extをセットする
dpathから、head,num書式,extの一致する連番のファイルを探し、numsにセットする
fpathのファイル名に数値がない場合、num,number,numsには何も加えない
dpath,head,extも同様
numsはsort済
num書式の一致は、文字数の一致、頭の区切子あれば文字一致、同位置に数値文字
*/
void level_from_files(
	const std::string& fpath
	, std::string& dpath
	, std::string& head
	, std::string& num
	, int& number
	, std::string& ext
	, std::vector<int>& nums
);

/*
num_form
頭一文字が数字でないなら区切り子としてそのまま記述する
文字数分のゼロ詰め書式
*/
const std::string str_from_number(
	const int number
	, const std::string& num_form=".0000"
);

} // path
} // igs

#endif /* !ids_path_level_from_files_h */
