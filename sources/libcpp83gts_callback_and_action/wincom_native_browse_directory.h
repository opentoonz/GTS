#ifndef wincom_native_browse_directory
#define wincom_native_browse_directory

#include <windows.h>
#include <string>

namespace wincom {
	std::wstring native_browse_directory_w(
		const std::wstring& title
		, const std::wstring& dir_path
		, HWND hParentWnd
	);
	std::string native_browse_directory_m(
		const std::string& title
		, const std::string& dir_path
		, HWND hParentWnd
	);
} // wincom

#endif /* !wincom_native_browse_directory */
