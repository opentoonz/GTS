#ifndef igs_path_filepath_number_list_h
#define igs_path_filepath_number_list_h

#include <vector>
#include <string>

/*
igs::path::filepath_number_list(-)
fpathからdpath,head,num,number,extをセット
dpathから、head,num書式,extの一致する連番のファイルを探し、numsにセット
num書式の一致は、文字数の一致、同位置に数値文字、区切子の文字一致
fpathのファイル名に数値がない場合、num,nums=empty()、number=-1となる
*/
namespace igs {
namespace path {
void filepath_number_list(
	const std::string& fpath
	, std::string& dpath
	, std::string& head
	, std::string& num
	, int& number
	, std::string& ext
	, std::vector<int>& nums
);
} // path
} // igs

#endif /* !igs_path_filepath_number_list_h */
