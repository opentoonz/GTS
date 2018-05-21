#ifndef cppl_path_h
#define cppl_path_h

#ifdef _WIN32
#include <filesystem>	/* std::tr2::sys::path */
#else
#include <experimental/filesystem> /* std::experimental::filesystem::path */
#endif

namespace cppl {

/*
	[WIP]利用検討用の実装です、実利用はまだ
		(cppl_file_system.hに含める予定)

	ファイルあるいは、フォルダーへのパスを保持するクラス

	vc2013は使えない

	vc2017で対応した?
 https://docs.microsoft.com/ja-jp/cpp/cpp-conformance-improvements-2017
	文字コードの扱いに注意が必要
---
	注意：2018-04-20

	vc2013 C++17における仕様と違う
		utf-8文字コードを入れると.string()でutf-8が返る
		WindowsAPIに渡す時はcp932に変換する必要あり

		入力した文字コードはそのまま保持している様子
		Multi Byte Codeとして使う

		文字コードとして utf8 で保持する
		理由1： 日本語Windowsではcp932が基本にあるが、
			S-JIS(cp932)だと'ソ','構','能','表',等の文字が、
			2バイト目に`\`=0x5cを含むため、
			Windowsではパスの区切り文字と判断してしまう。
			(vc2013まで?)
		理由2： "char* str=u8"UTF-8エンコード";"で、
			utf8文字コードで埋め込みができる
			(vc2015以後)

	vc2017 C++17における仕様(?)
		utf-8文字コードを入れても.string()でcp932が返る
		WindowsAPIに渡す時は.string()メソッドでcp932が返る
		fltkに渡す(utf-8にしたい)ときはgeneric_u8string()で渡す
*/
#if defined(_WIN32) && (_MSC_VER < 1910)	/* vc2017より前のMS-C */
using file_system_path = std::tr2::sys::path;
#else
using file_system_path = std::experimental::filesystem::path;
#endif

} // cppl

#endif /* !cppl_path_h */
