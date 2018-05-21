#ifndef gts_file_path_h
#define gts_file_path_h

#include <string>

#ifndef _WIN32
const char* get_desktop_dir_when_unix( void );
#endif

/* ユーザーのホームディレクトリパスを得る
--> 将来共通関数として独立するべき  */
void ptbl_get_user_home(std::string& user_home);

/* --> 将来アプリでの共通関数として独立するべき  */
std::string gts_file_path(const char *comm, const char *file_name);

#endif /* !gts_file_path_h */
