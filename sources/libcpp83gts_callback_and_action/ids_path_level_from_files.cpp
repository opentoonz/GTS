#include <iostream>
#include <sstream> // std::ostringstream
#include <iomanip> // std::setw()
#include <algorithm>    // std::sort()
#include <vector>
#include <string>
#include "FL/Fl.H"
#include "FL/filename.H" // fl_filename_list()
#include "ids_path_level_from_files.h"

/* ファイルパスをディレクトリパスとファイル名に分割する */
void ids::path::from_fpath_to_dpath_fname(
	const std::string& fpath
	,std::string& dpath
	,std::string& fname
)
{
	/* 一番後ろのパス区切り位置
		例１ パス区切り通常
		C:\user\public\A.0001.tif
		01234567890123456789012345
		              |
			      pos =14
		例２ パス区切り2文字ある
		C:\user\public/\A.0001.tif
		01234567890123456789012345
		               |
			       pos =15
	*/
	std::string::size_type pos = fpath.find_last_of("/\\");
	if (std::string::npos == pos) {
		fname = fpath; /* パス区切りがないので全体がファイル名 */
		return; /* ディレクトリパスはない */
	}

	/* ファイル名をセット */
	if ((pos+1) < fpath.size()) { /* パスの最後が区切りでなければ */
		fname = fpath.substr(pos+1);
	}

	/* 一番後ろのパス区切りの直前文字位置
		例１ パス区切り通常
		C:\user\public\A.0001.tif
		01234567890123456789012345
		             |
			     pos = 13
		例２ パス区切り2文字ある
		C:\user\public/\A.0001.tif
		01234567890123456789012345
		             |
			     pos = 13
	*/
	pos = fpath.find_last_not_of("/\\" ,pos);
	if (std::string::npos == pos) { /* パス区切りの前に文字がない */
		return; /* ディレクトリパスはない */
	}

	/* ディレクトリパスをセット */
	dpath = fpath.substr(0,pos+1);
}

/* ディレクトリパスとファイル名をファイルパスにする */
const std::string ids::path::fpath_from_dpath_fname(
	const std::string& dpath
	,const std::string& fname
)
{
	std::string fpath;
	fpath = dpath;
	fpath += '/';
	fpath += fname;
	return fpath;
}

namespace {

void from_fname_to_head_num_ext_(
	const std::string& fname
	,std::string& head
	/* head:数値&区切子(".0001")以前にある文字、なければempty() */
	,std::string& num_form
	/* num_form:拡張子以前にある数値&区切子(".0001")得る、なければempty() */
	,int& number
	,std::string& ext
	/* ext:一番後ろのdotの区切りあれば(".tif")セット、なければempty() */
)
{
	/* ファイル名の一番後ろがパス区切子の場合はdirectoryと判断 */
	if (fname.back() == '/' || fname.back() == '\\') {
		return;
	}

	/* ファイル名の後ろから拡張子の先頭位置を得る
		例１ 拡張子がある
		A.0001.tif
		0123456789
		      |
		      pos =6
		例２ 拡張子がない場合
		A_0001
		012345
		|
		pos =npos
	*/
	std::string::size_type pos = fname.rfind(".");
	std::string head_num;
	if (std::string::npos == pos) {
		head_num = fname; /* 拡張子がないので全体がヘッドと番号 */
	}
	else {
		ext = fname.substr(pos); /* 拡張子をセット(".tif") */
		head_num = fname.substr(0,pos);/* ヘッドと番号("A.0001") */
	}

	if (head_num.empty()) {
		return;
	}

	/* 数値とその前にある区切子を得る(".0001") */
	pos = head_num.find_last_not_of("0123456789");
	if (std::string::npos==pos) { /* 全部数値 */
		if (pos==0 && !isalpha(head_num.at(pos))) { /* 区切子と数値のみ */
			number = std::stoi( head_num.substr(1) );
		}
		else {
			number = std::stoi( head_num );
		}
		num_form = head_num;
	}
	else if ((head_num.size()-1) <= pos) { /* 数値がない */
		head = head_num;
	}
	else {
		number = std::stoi( head_num.substr(pos+1) );
		if (isalpha(head_num.at(pos))) {
			++pos; /* 区切子ならば数値に含む */
		}
		num_form = head_num.substr(pos);
		head = head_num.substr(0 ,pos);
	}
}
void pr_filename_(
	const int pos
	,const int len
	,const std::string& fname
	,const std::string& head
	,const std::string& num_form
	,const int number
	,const std::string& ext
)
{
	std::cout
		<< std::setw(2) << pos << "/"
		<< std::setw(2) << len
		<< " fname=\""	<< std::setw(14) << fname << "\""
		<< " he=\""	<< std::setw(10) << head << "\""
		<< " nu_f=\""	<< std::setw(6) << num_form << "\""
		<< " n=\""	<< std::setw(5) << number << "\""
		<< " ex=\""	<< ext << "\""
		<< std::endl;
}
bool save_as_num_form_(
	const std::string& num_src
	,const std::string& num_tgt
)
{
	if (num_src.size() != num_tgt.size()) {
		return false; /* 数値の文字表記の文字数が違う */
	}
	for (size_t ii=0 ; ii < num_src.size() ;++ii) {
		if (isdigit( num_src.at(ii) )) { /* 数値であるとき... */
			if (!isdigit( num_tgt.at(ii) )) {
				return false; /* 同じ位置に数値でない */
			}
		}
		else { /* 数値でないとき... */
			if (num_src.at(ii) != num_tgt.at(ii)) {
				return false; /* 同じ文字でない */
			}
		}
	}
	return true;
}

void from_dpath_head_num_ext_to_nums_(
	const std::string& dpath
	,const std::string& head
	,const std::string& num
	,const std::string& ext
	,std::vector<int>& nums
)
{
	dirent** list_pp = nullptr;
	const int list_count= ::fl_filename_list( dpath.c_str() ,&list_pp );
	if (list_count <= 0) {
		return;
	}
	for (int ii=0 ;ii<list_count ;++ii) {
		std::string he ,nu ,ex;
		int number=-1;
		from_fname_to_head_num_ext_(
			list_pp[ii]->d_name ,he,nu,number,ex
		);
	/* WindowsではDirectoryの場合d_nameの最後に/が付く、Fileは付かない
	   "../"が始めに来て、"./"が２番目に来る
	*/
#if DEBUG_INO
pr_filename_( ii ,list_count ,list_pp[ii]->d_name ,he ,nu ,number ,ex );
#endif //DEBUG_INO
		if (	0 <= number && he == head && ex == ext
			&& save_as_num_form_(num,nu)
		) {
			nums.push_back(number);
		}
	}
	::fl_filename_free_list( &list_pp ,list_count );
}

} // namespace

//----------------------------------------------------------------------

void ids::path::level_from_files(
	const std::string& fpath
	, std::string& dpath
	, std::string& head
	, std::string& num
	, int& number
	, std::string& ext
	, std::vector<int>& nums
)
{
	std::string fname;
	ids::path::from_fpath_to_dpath_fname( fpath ,dpath ,fname );
	from_fname_to_head_num_ext_(fname,head,num,number,ext);

#if DEBUG_INO
std::cout << "--------------------------------------------------\n";
std::cout << "dpath=\"" << dpath << "\"\n";
std::cout << "--------------------------------------------------\n";
	pr_filename_( 0 ,1 ,fname ,head ,num ,number ,ext );
std::cout << "--------------------------------------------------\n";
#endif //DEBUG_INO

	from_dpath_head_num_ext_to_nums_(dpath,head,num,ext,nums);
	std::sort( nums.begin() ,nums.end() ); /* 昇順ソート */

#if DEBUG_INO
std::cout << "--------------------------------------------------\n";
for( const int& num : nums ) {
std::cout << num << "\n";
}
std::cout << "--------------------------------------------------\n";
#endif //DEBUG_INO
}

const std::string ids::path::str_from_number(
	const int number
	, const std::string& num_form
)
{
	int ww = num_form.size();
	std::string sep;
	if (!isalpha( num_form.at(0) )) {
		--ww;
		sep = num_form.at(0);
	}
	std::ostringstream ost;
	ost << sep << std::setfill('0') << std::setw( ww ) << number;
	return ost.str();
}

//----------------------------------------------------------------------
#if DEBUG_INO
int main(int argc ,const char* argv[])
{
	if (argc < 2) {
		return 1;
	}

	std::string dpath ,head ,num_form ,ext;
	int number=-1;
	std::vector<int> nums;

	ids::path::level_from_files(
		argv[1] ,dpath ,head ,num_form ,number ,ext ,nums
	);

	pr_filename_( 0 ,1 ,"Result" ,head ,num_form ,number ,ext );
std::cout << "--------------------------------------------------\n";
	for( const int& num : nums ) {
		std::cout
			<< "num=" << std::setw(4) << num
			<< " num_form=\""
			<< ids::path::str_from_number(num ,num_form)
			<< "\"\n";
	}
std::cout << "--------------------------------------------------\n";

	return 0;
}
/*
:262,264 w! make.bat
rem windows make
cl /W3 /MD /EHa /O2 /wd4819 /DWIN32 /DDEBUG_INO /I..\..\thirdparty\fltk\fltk-1.3.3 ..\..\thirdparty\fltk\fltk-1.3.3\lib\fltk-1.3.3-vc2013-32.lib ids_path_level_from_files.cpp /Fet
del ids_path_level_from_files.obj

:270,270 w! make.csh
# linux make
g++ -DDEBUG_INO -std=c++11 ids_path_level_from_files.cpp -lfltk
*/
#endif //DEBUG_INO
