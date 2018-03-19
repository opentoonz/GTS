#ifndef cppl_path_h
#define cppl_path_h

#ifdef _WIN32
#include <filesystem>	/* std::tr2::sys::path */
#else
#include <experimental/filesystem> /* std::experimental::filesystem::path */
#endif

namespace cppl {

/*
	ファイルあるいは、フォルダーへのパスを保持するクラス

	Multi Byte Codeとして使う

	文字コードとして utf8 で保持する
	理由1： 日本語Windowsではcp932が基本にあるが、
		S-JIS(cp932)だと'ソ','構','能','表',等の文字が、
		2バイト目に`\`=0x5cを含むため、
		Windowsではパスの区切り文字と判断してしまう。
	理由2： "char* str=u8"UTF-8エンコード";"で、
		utf8文字コードで埋め込みができる(vc2015以後)
	使用上の注意：WindowsAPIにはcp932に変換して渡すこと
*/
#ifdef _WIN32
using file_system_path = std::tr2::sys::path;
#else
using file_system_path = std::experimental::filesystem::path;
#endif

} // cppl

#endif /* !cppl_path_h */
