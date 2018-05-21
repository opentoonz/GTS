#ifndef cppl_file_system_h
#define cppl_file_system_h

#include <string>
#include <vector>
#include "cppl_file_system_path.h"

namespace cppl {

/*
	[WIP]利用検討用の実装です、実利用はまだ

	ファイルあるいはフォルダーに対する操作関数群
	エラー時は例外が飛ぶことを前提に利用すること
	(Windowsでは飛んでこなかったりするが...全部調べてない...)

	以下、vc2013 & g++ 5.4.0(ubuntu16.04.9) にて確認した機能
	----------------------------------------//------------------------
	const cppl::file_system_path pa;	// 引数(パスの格納)
	----------------------------------------//------------------------
	cppl::file_system::exists(pa);		// 存在の有無(フォルダでも)
	cppl::file_system::is_directory(pa);	// フォルダーか否か
	cppl::file_system::file_size(pa);	// ファイル大きさ(bytes)
	cppl::get_directory_list(pa);		// フォルダー内のリスト
	cppl::file_system::create_directory(pa);// フォルダー生成
	cppl::file_system::rename(pa,pa2);	// 名前変更
	----------------------------------------//------------------------
	注意:remove()は存在しないフォルダーを指定すると例外を投げてくる
*/
#if defined(_WIN32) && (_MSC_VER < 1910)	/* vc2017より前のMS-C */
namespace file_system = std::tr2::sys;
#elif defined(_MACOS)
namespace file_system = boost::filesystem;
#else
namespace file_system = std::experimental::filesystem;
#endif

// std::vector<std::string> get_directory_list( const cppl::file_system_path& pa );

} // cppl

#endif /* !cppl_file_system_h */
