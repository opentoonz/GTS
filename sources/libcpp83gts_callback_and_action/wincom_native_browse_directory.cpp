//#include <windows.h>
#include <shobjidl.h>
#include "osapi_mbs_wcs_win.h"
#include "wincom_native_browse_directory.h"

namespace wincom {
std::wstring native_browse_directory_w(
	const std::wstring& title
	, const std::wstring& dir_path
	, HWND hParentWnd
) {
	CoInitialize(nullptr);

	IFileDialog *fdlgIf = nullptr;
	HRESULT hr = ::CoCreateInstance(
		CLSID_FileOpenDialog
		,nullptr
		,CLSCTX_INPROC_SERVER
		,IID_PPV_ARGS(&fdlgIf)
	);
	if (FAILED(hr)) {
		::CoUninitialize();
		return std::wstring();
	}

	/* ファイル開くブラウザーをフォルダー選択ブラウザーにする */
	DWORD	flags=0;
	hr = fdlgIf->GetOptions(&flags);
	if (FAILED(hr)) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	}

	hr = fdlgIf->SetOptions( flags | FOS_PICKFOLDERS );
	if (FAILED(hr)) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	}

	/* タイトル文字を設定 */
	hr = fdlgIf->SetTitle(title.c_str());
	if (FAILED(hr)) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	}

	/* 初期フォルダパスを設定 */
	if (!dir_path.empty()) {
	 HMODULE shell32_handle = ::GetModuleHandle(TEXT("shell32.dll"));
	 if (shell32_handle == nullptr) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	 }
	 typedef HRESULT (STDAPICALLTYPE SHCreateItemFromParsingNameProc)(
	 PCWSTR pszPath, IBindCtx *pbc, REFIID riid, void **ppv);
	 SHCreateItemFromParsingNameProc *SHCreateItemFromParsingName=
	 (SHCreateItemFromParsingNameProc*)::GetProcAddress(
	  shell32_handle, "SHCreateItemFromParsingName"
	 );
	 if (SHCreateItemFromParsingName == nullptr) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	 }

	 IShellItem *dirIf = nullptr;
	 hr = SHCreateItemFromParsingName(
		dir_path.c_str()
		, nullptr
		,IID_PPV_ARGS(&dirIf)
	 );
	 if (SUCCEEDED(hr)) {
		fdlgIf->SetFolder(dirIf);
		dirIf->Release();
	 }
	}

	/* 初期フォルダ名をセット */
	hr = fdlgIf->SetFileName(L"");
	if (FAILED(hr)) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	}

	/* GUIダイオローグ表示 */
	hr = fdlgIf->Show(hParentWnd);
	if (FAILED(hr)) {
		fdlgIf->Release();
		::CoUninitialize();
		return std::wstring();
	}

	/* パスを得る */
	IShellItem *resultIf=nullptr;
	std::wstring wstr;
	hr = fdlgIf->GetResult(&resultIf);
	if (SUCCEEDED(hr)) {
		if (resultIf == nullptr) {
			fdlgIf->Release();
			::CoUninitialize();
			return std::wstring();
		}
		LPWSTR wstr_p=nullptr;
		hr = resultIf->GetDisplayName(SIGDN_FILESYSPATH, &wstr_p);
		if (SUCCEEDED(hr)) {
			wstr = wstr_p;
			::CoTaskMemFree(wstr_p);
		}
		resultIf->Release();
	}

	/* 後始末 */
	fdlgIf->Release();
	::CoUninitialize();

	return wstr;
}
std::string native_browse_directory_m(
	const std::string& title
	, const std::string& dir_path
	, HWND hParentWnd
) {
	return osapi::utf8_from_cp932( osapi::mbs_from_wcs(
		native_browse_directory_w(
			osapi::wcs_from_mbs(title)
			,osapi::wcs_from_mbs(dir_path)
			,hParentWnd
		)
	) );
}
} // wincom

#if DEBUG_WINCOM_NATIVE_BROWSE_DIRECTORY
#include <iostream>
#include "../lib_util/osapi_mbs_wcs_win.cpp"
int main(int argc ,const char* argv[])
{
	if (argc!=3) {
		std::cout << "Usage : " << argv[0] << " title dirpath\n";
		return 1;
	}
	std::string title = argv[1];
	std::string dirpa = argv[2];

	//std::cout.imbue( std::locale( "", std::locale::ctype ) );
	std::cout << "title \"" << title.c_str() << "\"\n";
	std::cout << "dpath \"" << dirpa.c_str() << "\"\n";
	std::string resul = wincom::native_browse_directory_m(
		title ,dirpa, nullptr
	);
	/*
		HWND fl_xid(const Fl_Window *)
		HWND hwnd = fl_xid( cl_gts_gui.window_main_view );
	*/
	std::cout << "dpath \"" << resul.c_str() << "\"\n";
	return 0;
}
#endif /* !DEBUG_WINCOM_NATIVE_BROWSE_DIRECTORY */
/*
rem :160,161 w! make.bat
cl /W4 /MD /EHa /O2 /source-charset:utf-8 /DDEBUG_WINCOM_NATIVE_BROWSE_DIRECTORY /I../lib_util glu32.lib advapi32.lib shlwapi.lib opengl32.lib comctl32.lib wsock32.lib user32.lib gdi32.lib shell32.lib ole32.lib comdlg32.lib wincom_native_browse_directory.cpp /Fea
del wincom_native_browse_directory.obj
*/
