#include <cstdlib>	/* getenv_s(-) getenv(-) */
#include <stdexcept>	/* std::invalid_argument(-) */

#ifdef _WIN32
#else
#include <cstring>
#endif

#include "rsrc_getenv.h"

namespace rsrc {

std::string getenv(const std::string& name)
{
#ifdef _WIN32
	size_t length = 0;
	char env_array[_MAX_ENV];
	/* _MAX_ENV is 32767 at VS2013 */
	/* _MAX_ENVはVisualStudio C++のみらしい */
	/* getenv_s() supported vc2010 or higher */
	errno_t err_no = getenv_s(&length,env_array,_MAX_ENV,name.c_str());

	if (err_no != 0) { /* getenv_s(-)の引数問題ある */
		return std::string();
	}
	if (length <= 0) { /* 対象の環境変数がない */
		return std::string();
	}
#else
	const char* env_array = ::getenv(name.c_str());

	if (env_array == nullptr) {
		return std::string();
	}
	size_t length = strlen(env_array);
	if (length <= 0) { /* 対象の環境変数がない */
		return std::string();
	}
#endif
	return std::string( env_array );
}

} // namespace rsrc

#if DEBUG_RSRC_GETENV
#include <iostream>
int main(void)
{
try {
	std::string homedriv( rsrc::getenv("HOMEDRIVE") );
	std::string homepath( rsrc::getenv("HOMEPATH") );
//std::string homedrpa(  rsrc::getenv("HOME") ); // unix 
	std::string allusers( rsrc::getenv("ALLUSERSPROFILE") );
	std::string public_p( rsrc::getenv("PUBLIC") );

	std::cout << "homehriv=\"" << homedriv << "\"\n";
	std::cout << "homepath=\"" << homepath << "\"\n";
//std::cout << "homedrpa=\"" << homedrpa << "\"\n";
	std::cout << "allusers=\"" << allusers << "\"\n";
	std::cout << "public_p=\"" << public_p << "\"\n";
}
catch (std::exception& e) {
	std::cerr << e.what();
}
catch (...) {
	std::cerr << "other exception\n";
}

	return 0;
}
#endif
/*
cl /W4 /EHsc rsrc_getenv.cpp /DDEBUG_RSRC_GETENV /Fea
*/
