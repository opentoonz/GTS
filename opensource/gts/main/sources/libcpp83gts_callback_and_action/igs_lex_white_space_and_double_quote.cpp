#include <stdexcept> /* std::domain_error(-) */
#include <sstream>
#include "igs_lex_white_space_and_double_quote.h"

void igs::lex::white_space_and_double_quote(
	const std::string&line
	, std::vector< std::string >&words
) {
	std::string::size_type end = 0;
	while (std::string::npos != end) {
	 std::string::size_type sta=line.find_first_not_of("\t\n ",end);
	 if (std::string::npos==sta)  { return; } // no word in rest
	 if ('#' ==     line.at(sta)) { return; } // comment in rest

	 if ('\"' == line.at(sta)) {
	  end = line.find_first_of('\"',sta+1);
	  if (std::string::npos==end) {
		std::string err("not close of double quote [");
		err += line;
		err += "]";
		throw std::domain_error(err);
	  }
	  words.push_back(line.substr(sta+1,end-sta-1));
	  ++end;
	 } else {
	  end = line.find_first_of("\t\n ",sta);
	  if (std::string::npos==end) {
		words.push_back(line.substr(sta));
	  } else {
		words.push_back(line.substr(sta,end-sta));
	  }
	 }
	}
}

