#ifndef igs_lex_white_space_and_double_quote_h
#define igs_lex_white_space_and_double_quote_h

#include <vector>
#include <string>

namespace igs {
 namespace lex {
  void white_space_and_double_quote(
	const std::string&line
	, std::vector< std::string >&words
  );
 }
}

#endif /* !igs_lex_white_space_and_double_quote_h */
